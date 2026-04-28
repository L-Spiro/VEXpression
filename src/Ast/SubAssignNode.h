#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a compound subtraction assignment operation (-=).
	 **/
	class SubAssignNode : public AstNode {
	public :
		SubAssignNode(size_t var, size_t right) : varIndex(var), rightIndex(right) {}


		// == Functions.
		/**
		 * Evaluates the compound subtraction assignment of the variable and right child node.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the new assigned value.
		 * \throws			ErrorCode::Unknown_Numeric_Type if the resolved common type is not supported.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result leftVal = context.getVariable(varIndex);
			Result rightVal = context.getArena().nodes[rightIndex]->evaluate(context);

			Result out;
			out = context.evaluateMath(leftVal, rightVal, ExprLexer::SUB_ASSIGN);
			VE_DELETE_SWAP(out, lastObject);

			//if (leftVal.type == NumericConstant::Object) {
			//	if (!leftVal.value.objectVal) { return Result{}; }
			//	out = leftVal.value.objectVal->operator-=(rightVal);

			//	// Only trigger memory garbage-collecting tracking if operator-= allocated a completely new object.
			//	if (out.value.objectVal != leftVal.value.objectVal) {
			//		VE_DELETE_SWAP(out, lastObject);
			//	}
			//	
			//	context.setVariable(varIndex, out);
			//	return out;
			//}

			//NumericConstant common = ExecutionContext::getCastType(leftVal.type, rightVal.type);
			//Result l = context.convertResult(leftVal, common);
			//Result r = context.convertResult(rightVal, common);

			//out.type = common;

			//if (common == NumericConstant::Floating) {
			//	out.value.doubleVal = l.value.doubleVal - r.value.doubleVal;
			//}
			//else if (common == NumericConstant::Signed) {
			//	out.value.intVal = l.value.intVal - r.value.intVal;
			//}
			//else if (common == NumericConstant::Unsigned) {
			//	out.value.uintVal = l.value.uintVal - r.value.uintVal;
			//}
			//else if (common == NumericConstant::Object) {
			//	if (!l.value.objectVal || !r.value.objectVal) { return Result{}; }
			//	out = l.value.objectVal->operator-=(r);

			//	if (out.value.objectVal != l.value.objectVal) {
			//		VE_DELETE_SWAP(out, lastObject);
			//	}
			//}
			//else {
			//	return Result{};
			//}

			context.setVariable(varIndex, out);
			return out;
		}

	protected :
		// == Members.
		size_t						varIndex;
		size_t						rightIndex;
		mutable Object*				lastObject = nullptr;
	};

}	// namespace ve
