#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a standard array or string index access operation.
	 **/
	class ArrayAccessNode : public AstNode {
	public :
		ArrayAccessNode(size_t target, size_t index) : targetIndex(target), indexIndex(index) {}


		// == Functions.
		/**
		 * Evaluates the array access.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the element at the specified index.
		 **/
		Result					evaluate(ExecutionContext& context) const override {
			Result target = context.getArena().nodes[targetIndex]->evaluate(context);
			Result indexRes = context.getArena().nodes[indexIndex]->evaluate(context);

			if (target.type != NumericConstant::Object || !target.value.objectVal) {
				return Result{ .type = NumericConstant::Invalid };
			}

			int64_t idx = 0;
			if (indexRes.type == NumericConstant::Signed) {
				idx = indexRes.value.intVal;
			}
			else if (indexRes.type == NumericConstant::Unsigned) {
				idx = static_cast<int64_t>(indexRes.value.uintVal);
			}
			else {
				return Result{ .type = NumericConstant::Invalid };
			}

			return target.value.objectVal->arrayAccess(idx);
		}

	protected :
		// == Members.
		size_t					targetIndex;
		size_t					indexIndex;
	};

}	// namespace ve
