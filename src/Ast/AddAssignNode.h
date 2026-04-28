#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a compound addition assignment operation (+=).
	 **/
	class AddAssignNode : public AstNode {
	public :
		AddAssignNode(size_t var, size_t right) : varIndex(var), rightIndex(right) {}


		// == Functions.
		/**
		 * Evaluates the compound addition assignment of the variable and right child node.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the new assigned value.
		 * \throws			ErrorCode::Unknown_Numeric_Type if the resolved common type is not supported.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result leftVal = context.getVariable(varIndex);
			Result rightVal = context.getArena().nodes[rightIndex]->evaluate(context);

			Result out;
			out = context.evaluateMath(leftVal, rightVal, ExprLexer::ADD_ASSIGN);
			VE_DELETE_SWAP(out, lastObject);

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
