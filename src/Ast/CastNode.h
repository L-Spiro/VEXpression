#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "../Engine/Vector.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a type cast operation (C-style, initialization-style, or static_cast).
	 **/
	class CastNode : public AstNode {
	public :
		/**
		 * Constructs a CastNode.
		 *
		 * \param exprId		The arena index of the child expression node to be evaluated.
		 * \param targetType	The internal DataType to cast the evaluated result to.
		 **/
		CastNode(size_t exprId, DataType targetType) : exprIndex(exprId), targetType(targetType) {}


		// == Functions.
		/**
		 * Evaluates the child expression and casts the result to the target type.
		 * Automatically broadcasts the cast across vector elements if the result is a vector.
		 *
		 * \param context		The runtime execution context.
		 * \return				Returns the casted Result (either primitive or a new Vector). Returns an Invalid Result if the cast fails.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result val = context.getArena().nodes[exprIndex]->evaluate(context);

			if (val.type == NumericConstant::Invalid) { return Result{}; }

			if (val.type == NumericConstant::Object && val.value.objectVal && (val.value.objectVal->type() & BuiltInType_Vector)) {
				Vector* srcVec = static_cast<Vector*>(val.value.objectVal);
				
				Vector* resVec = context.allocateObject<Vector>();
				if (!resVec) { return Result{}; }

				resVec->resize(srcVec->arrayLength());

				for (size_t i = 0; i < srcVec->arrayLength(); ++i) {
					Result castedElement = context.castArgument(srcVec->directAccess(i), targetType);
					
					if (castedElement.type == NumericConstant::Invalid) {
						context.deallocateObject(resVec);
						return Result{};
					}
					
					resVec->directAccess(i) = castedElement;
				}

				return resVec->createResult();
			}

			return context.castArgument(val, targetType);
		}

	private :
		size_t						exprIndex;
		DataType					targetType;
	};

}	// namespace ve
