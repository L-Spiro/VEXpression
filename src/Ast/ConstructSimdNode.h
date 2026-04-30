#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "../Engine/SimdObject.h"
#include "AstNode.h"

#include <cstring>
#include <vector>

namespace ve {

	/**
	 * Represents a node that constructs and initializes a new SIMD register object.
	 **/
	class ConstructSimdNode : public AstNode {
	public :
		ConstructSimdNode(SimdRegisterType type, const std::vector<size_t>& arguments)
			: regType(type), args(arguments) {}


		// == Functions.
		/**
		 * Evaluates the node, allocating a new SimdObject and initializing its lanes.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns a Result containing the new SimdObject.
		 **/
		Result							evaluate(ExecutionContext& context) const override {
			SimdObject* obj = context.allocateObject<SimdObject>();
			if (!obj) { return Result{}; }

			obj->regType = regType;

			std::memset(&obj->reg, 0, sizeof(obj->reg));

			if (args.size() == 1) {
				Result argRes = context.getArena().nodes[args[0]]->evaluate(context);

				if (argRes.type == NumericConstant::Object && argRes.value.objectVal) {
					Vector* arrObj = static_cast<Vector*>(argRes.value.objectVal);
					size_t count = arrObj->arrayLength(); 
						
					for (size_t i = 0; i < count; ++i) {
						obj->arrayAssign(static_cast<int64_t>(i), arrObj->at(i));
					}
						
					return obj->createResult();
				}

				obj->arrayAssign(0, argRes);
				return obj->createResult();
			}

			for (size_t i = 0; i < args.size(); ++i) {
				Result argRes = context.getArena().nodes[args[i]]->evaluate(context);
				obj->arrayAssign(static_cast<int64_t>(i), argRes);
			}

			return obj->createResult();
		}

	private :
		SimdRegisterType				regType;
		std::vector<size_t>				args;
	};

}	// namespace ve
