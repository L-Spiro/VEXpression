#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents an extended (sliced) array or string access operation.
	 **/
	class ArrayAccessExNode : public AstNode {
	public :
		ArrayAccessExNode(size_t target, size_t start, size_t end, uint32_t mask) 
			: targetIndex(target), startIndex(start), endIndex(end), flagsMask(mask) {}


		// == Functions.
		/**
		 * Evaluates the sliced array access.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the sliced sub-array or sub-string.
		 **/
		Result					evaluate(ExecutionContext& context) const override {
			Result target = context.getArena().nodes[targetIndex]->evaluate(context);

			if (target.type != NumericConstant::Object || !target.value.objectVal) {
				return Result{ .type = NumericConstant::Invalid };
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
					return Result{ .type = NumericConstant::Invalid };
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
					return Result{ .type = NumericConstant::Invalid };
				}
			}

			Result out = target.value.objectVal->arrayAccessEx(startIdx, endIdx, flagsMask);
			
			// A sliced string or vector creates a completely new object, requiring garbage collection tracking.
			VE_DELETE_SWAP(out, lastObject);
			
			return out;
		}

	protected :
		// == Members.
		size_t					targetIndex;
		size_t					startIndex;
		size_t					endIndex;
		uint32_t				flagsMask;
		mutable Object*			lastObject = nullptr;
	};

}	// namespace ve
