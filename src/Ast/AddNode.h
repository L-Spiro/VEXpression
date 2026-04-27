#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents an addition operation between two child nodes.
	 **/
	class AddNode : public AstNode {
	public :
		AddNode(size_t left, size_t right) : leftIndex(left), rightIndex(right) {}

		
		// == Functions.
		/**
		 * Evaluates the addition of the left and right child nodes.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the sum of the evaluated left and right nodes.
		 * \throws			ErrorCode::Unknown_Numeric_Type if the resolved common type is not supported.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result leftVal = context.getArena().nodes[leftIndex]->evaluate(context);
			Result rightVal = context.getArena().nodes[rightIndex]->evaluate(context);

			Result out;
			out = context.evaluateMath(leftVal, rightVal, ExprLexer::ADD);
			VE_DELETE_SWAP(out, lastObject);

			//if (leftVal.type == NumericConstant::Object) {
			//	if (!leftVal.value.objectVal) { return Result{ .type = NumericConstant::Invalid }; }
			//	out = (*leftVal.value.objectVal) + rightVal;

			//	// The operation probably created a new object.
			//	VE_DELETE_SWAP(out, lastObject);
			//	return out;
			//}

			//NumericConstant common = ExecutionContext::getCastType(leftVal.type, rightVal.type);
			//Result l = context.convertResult(leftVal, common);
			//Result r = context.convertResult(rightVal, common);

			//
			//out.type = common;

			//if (common == NumericConstant::Floating) {
			//	out.value.doubleVal = l.value.doubleVal + r.value.doubleVal;
			//}
			//else if (common == NumericConstant::Signed) {
			//	out.value.intVal = l.value.intVal + r.value.intVal;
			//}
			//else if (common == NumericConstant::Unsigned) {
			//	out.value.uintVal = l.value.uintVal + r.value.uintVal;
			//}
			//else if (common == NumericConstant::Object) {
			//	if (!l.value.objectVal) { return Result{ .type = NumericConstant::Invalid }; }
			//	if (!r.value.objectVal) { return Result{ .type = NumericConstant::Invalid }; }
			//	out = (*l.value.objectVal) + r;

			//	// The operation probably created a new object.
			//	VE_DELETE_SWAP(out, lastObject);
			//}
			//else {
			//	throw ErrorCode::Unknown_Numeric_Type;
			//}

			return out;
		}

	protected :

	private :
		// == Members.
		size_t						leftIndex;
		size_t						rightIndex;
		mutable Object*				lastObject = nullptr;
	};

}	// namespace ve
