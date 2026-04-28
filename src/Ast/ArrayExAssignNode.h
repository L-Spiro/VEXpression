#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents an assignment or compound assignment to an array slice.
	 **/
	class ArrayExAssignNode : public AstNode {
	public :
		ArrayExAssignNode(size_t target, size_t start, size_t end, uint32_t mask, size_t right, int op) 
			: targetIndex(target), startIndex(start), endIndex(end), flagsMask(mask), rightIndex(right), opType(op) {}


		// == Functions.
		/**
		 * Evaluates the array slice assignment.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the assigned value.
		 **/
		Result					evaluate(ExecutionContext& context) const override {
			Result target = context.getArena().nodes[targetIndex]->evaluate(context);

			if (target.type != NumericConstant::Object || !target.value.objectVal) {
				return Result{};
			}

			if (target.value.objectVal->type() & BuiltInType_Map) {
				return Result{};
			}

			int64_t startIdx = 0;
			int64_t endIdx = 0;

			if (flagsMask & ArrayExFlags::ArrayExFlag_Start) {
				Result sRes = context.getArena().nodes[startIndex]->evaluate(context);
				if (sRes.type == NumericConstant::Signed) {
					startIdx = sRes.value.intVal;
				}
				else if (sRes.type == NumericConstant::Unsigned) {
					startIdx = static_cast<int64_t>(sRes.value.uintVal);
				}
				else {
					return Result{};
				}
			}

			if (flagsMask & ArrayExFlags::ArrayExFlag_End) {
				Result eRes = context.getArena().nodes[endIndex]->evaluate(context);
				if (eRes.type == NumericConstant::Signed) {
					endIdx = eRes.value.intVal;
				}
				else if (eRes.type == NumericConstant::Unsigned) {
					endIdx = static_cast<int64_t>(eRes.value.uintVal);
				}
				else {
					return Result{};
				}
			}

			Result rhs = context.getArena().nodes[rightIndex]->evaluate(context);

			if (opType == ExprLexer::ASSIGN) {
				return target.value.objectVal->arrayAssignEx(startIdx, endIdx, flagsMask, rhs);
			} 
			else {
				size_t outStart, outEnd;
				if (!Object::resolveSliceBounds(startIdx, endIdx, flagsMask, target.value.objectVal->arrayLength(), outStart, outEnd)) {
					return Result{};
				}

				for (size_t i = outEnd; i-- > outStart; ) {
					Result oldVal = target.value.objectVal->arrayAccess(i);
					Result newVal = context.evaluateMath(oldVal, rhs, opType);
					
					if (oldVal.type != NumericConstant::Object || oldVal.value.objectVal != newVal.value.objectVal) {
						target.value.objectVal->arrayAssign(i, newVal);
					}
				}
				
				return rhs;
			}
		}

	protected :
		// == Members.
		size_t					targetIndex;
		size_t					startIndex;
		size_t					endIndex;
		uint32_t				flagsMask;
		size_t					rightIndex;
		int						opType;
	};

}	// namespace ve
