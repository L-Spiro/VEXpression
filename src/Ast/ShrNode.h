#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <cmath>

namespace ve {

	/**
	 * Represents a bitwise right-shift operation between two child nodes.
	 **/
	class ShrNode : public AstNode {
	public :
		ShrNode(size_t left, size_t right) : leftIndex(left), rightIndex(right) {}

		
		// == Functions.
		/**
		 * Evaluates the left child node shifted right by the right child node.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the shifted result based on the left node's original type.
		 * \throws			ErrorCode::Unknown_Numeric_Type if either of the resolved common types is not supported.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result leftVal = context.getArena().nodes[leftIndex]->evaluate(context);
			Result rightVal = context.getArena().nodes[rightIndex]->evaluate(context);

			uint64_t shift = 0;
			if (rightVal.type == NumericConstant::Floating) {
				shift = static_cast<uint64_t>(rightVal.value.doubleVal);
			}
			else if (rightVal.type == NumericConstant::Signed) {
				shift = static_cast<uint64_t>(rightVal.value.intVal);
			}
			else if (rightVal.type == NumericConstant::Unsigned) {
				shift = rightVal.value.uintVal;
			}
			else {
				throw ErrorCode::Unknown_Numeric_Type;
			}

			if (leftVal.type == NumericConstant::Object) {
				if (!leftVal.value.objectVal) { return Result{ .type = NumericConstant::Invalid }; }
				return (*leftVal.value.objectVal) >> Result{ .type = NumericConstant::Unsigned, .value { .uintVal = shift } };
			}

			Result out;
			if (leftVal.type == NumericConstant::Floating || rightVal.type == NumericConstant::Floating) {
				NumericConstant common = ExecutionContext::getCastType(leftVal.type, rightVal.type);
				Result l = context.convertResult(leftVal, common);
				Result r = context.convertResult(rightVal, common);

				out.type = NumericConstant::Floating;
				out.value.doubleVal = l.value.doubleVal / std::pow(2.0, r.value.doubleVal);
				/*out.type = NumericConstant::Signed;
				out.value.intVal = static_cast<int64_t>(leftVal.value.doubleVal) >> shift;*/
			}
			else if (leftVal.type == NumericConstant::Signed) {
				out.type = NumericConstant::Signed;
				out.value.intVal = leftVal.value.intVal >> shift;
			}
			else if (leftVal.type == NumericConstant::Unsigned) {
				out.type = NumericConstant::Unsigned;
				out.value.uintVal = leftVal.value.uintVal >> shift;
			}
			else {
				throw ErrorCode::Unknown_Numeric_Type;
			}

			return out;
		}

	protected :

	private :
		// == Members.
		size_t						leftIndex;
		size_t						rightIndex;
	};

}	// namespace ve
