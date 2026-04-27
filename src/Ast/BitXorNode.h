#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a bitwise XOR operation between two child nodes.
	 **/
	class BitXorNode : public AstNode {
	public :
		BitXorNode(size_t left, size_t right) : leftIndex(left), rightIndex(right) {}

		
		// == Functions.
		/**
		 * Evaluates the bitwise XOR of the left and right child nodes.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the bitwise exclusive OR.
		 * \throws			ErrorCode::Unknown_Numeric_Type if the resolved common type is not supported.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result leftVal = context.getArena().nodes[leftIndex]->evaluate(context);
			Result rightVal = context.getArena().nodes[rightIndex]->evaluate(context);

			Result out;
			out = context.evaluateMath(leftVal, rightVal, ExprLexer::BIT_XOR);
			VE_DELETE_SWAP(out, lastObject);

			//if (leftVal.type == NumericConstant::Object) {
			//	if (!leftVal.value.objectVal) { return Result{ .type = NumericConstant::Invalid }; }
			//	return (*leftVal.value.objectVal) ^ rightVal;
			//}

			//NumericConstant common = ExecutionContext::getCastType(leftVal.type, rightVal.type);
			//Result l = context.convertResult(leftVal, common);
			//Result r = context.convertResult(rightVal, common);

			//Result out;
			//if (common == NumericConstant::Floating) {
			//	/*out.type = NumericConstant::Signed;
			//	out.value.intVal = static_cast<int64_t>(l.value.doubleVal) ^ static_cast<int64_t>(r.value.doubleVal);*/
			//	out.type = NumericConstant::Invalid;
			//}
			//else if (common == NumericConstant::Signed) {
			//	out.type = NumericConstant::Signed;
			//	out.value.intVal = l.value.intVal ^ r.value.intVal;
			//}
			//else if (common == NumericConstant::Unsigned) {
			//	out.type = NumericConstant::Unsigned;
			//	out.value.uintVal = l.value.uintVal ^ r.value.uintVal;
			//}
			//else if (common == NumericConstant::Object) {
			//	if (!l.value.objectVal) { return Result{ .type = NumericConstant::Invalid }; }
			//	if (!r.value.objectVal) { return Result{ .type = NumericConstant::Invalid }; }
			//	out = (*l.value.objectVal) ^ r;
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
