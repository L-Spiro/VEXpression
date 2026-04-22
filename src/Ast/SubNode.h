#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a subtraction operation between two child nodes.
	 **/
	class SubNode : public AstNode {
	public :
		SubNode(size_t left, size_t right) : leftIndex(left), rightIndex(right) {}

		
		// == Functions.
		/**
		 * Evaluates the subtraction of the right child node from the left child node.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the difference of the evaluated left and right nodes.
		 * \throws			ErrorCode::Unknown_Numeric_Type if the resolved common type is not supported.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result leftVal = context.getArena().nodes[leftIndex]->evaluate(context);
			Result rightVal = context.getArena().nodes[rightIndex]->evaluate(context);

			if (leftVal.type == NumericConstant::Object) {
				if (!leftVal.value.objectVal) { return Result{ .type = NumericConstant::Invalid }; }
				return (*leftVal.value.objectVal) - rightVal;
			}

			NumericConstant common = ExecutionContext::getCastType(leftVal.type, rightVal.type);
			Result l = context.convertResult(leftVal, common);
			Result r = context.convertResult(rightVal, common);

			Result out;
			out.type = common;

			if (common == NumericConstant::Floating) {
				out.value.doubleVal = l.value.doubleVal - r.value.doubleVal;
			}
			else if (common == NumericConstant::Signed) {
				out.value.intVal = l.value.intVal - r.value.intVal;
			}
			else if (common == NumericConstant::Unsigned) {
				out.value.uintVal = l.value.uintVal - r.value.uintVal;
			}
			else if (common == NumericConstant::Object) {
				if (!l.value.objectVal) { return Result{ .type = NumericConstant::Invalid }; }
				if (!r.value.objectVal) { return Result{ .type = NumericConstant::Invalid }; }
				out = (*l.value.objectVal) - r;
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