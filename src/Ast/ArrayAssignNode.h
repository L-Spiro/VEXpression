#pragma once

#include "../../generated/ExprLexer.h"
#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents an assignment or compound assignment to an array index.
	 **/
	class ArrayAssignNode : public AstNode {
	public :
		ArrayAssignNode(size_t target, size_t index, size_t right, int op) 
			: targetIndex(target), indexIndex(index), rightIndex(right), opType(op) {}


		// == Functions.
		/**
		 * Evaluates the array assignment.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the assigned value.
		 **/
		Result					evaluate(ExecutionContext& context) const override {
			Result target = context.getArena().nodes[targetIndex]->evaluate(context);
			Result indexRes = context.getArena().nodes[indexIndex]->evaluate(context);
			Result rhs = context.getArena().nodes[rightIndex]->evaluate(context);

			if (target.type != NumericConstant::Object || !target.value.objectVal) {
				return Result{ .type = NumericConstant::Invalid };
			}

			int64_t idx = 0;
			if (indexRes.type == NumericConstant::Signed) { idx = indexRes.value.intVal; }
			else if (indexRes.type == NumericConstant::Unsigned) { idx = static_cast<int64_t>(indexRes.value.uintVal); }
			else { return Result{ .type = NumericConstant::Invalid }; }

			Result valToAssign = rhs;
			if (opType != ExprLexer::ASSIGN) {
				Result oldVal = target.value.objectVal->arrayAccess(idx);
				valToAssign = context.evaluateMath(oldVal, rhs, opType);
				
				// CRITICAL FIX: Prevent vector flattening/corruption if mutated in-place.
				if (oldVal.type == NumericConstant::Object && oldVal.value.objectVal == valToAssign.value.objectVal) {
					return valToAssign;
				}

				// Only swap memory if evaluateMath allocated a brand new dynamic object.
				if (valToAssign.type == NumericConstant::Object) {
					VE_DELETE_SWAP(valToAssign, lastObject);
				}
			}

			return target.value.objectVal->arrayAssign(idx, valToAssign);
		}

	protected :
		// == Members.
		size_t					targetIndex;
		size_t					indexIndex;
		size_t					rightIndex;
		int						opType;
		mutable Object*			lastObject = nullptr;
	};

}	// namespace ve
