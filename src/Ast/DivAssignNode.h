#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a compound division assignment operation (/=).
	 **/
	class DivAssignNode : public AstNode {
	public :
		DivAssignNode(size_t var, size_t right) : varIndex(var), rightIndex(right) {}


		// == Functions.
		/**
		 * Evaluates the compound division assignment of the variable and right child node.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the new assigned value.
		 * \throws			ErrorCode::Unknown_Numeric_Type if the resolved common type is not supported.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result leftVal = context.getVariable(varIndex);
			Result rightVal = context.getArena().nodes[rightIndex]->evaluate(context);

			Result out;
			out = context.evaluateMath(leftVal, rightVal, ExprLexer::DIV_ASSIGN);
			VE_DELETE_SWAP(out, lastObject);

			context.setVariable(varIndex, out);
			return out;
		}

		/**
		 * Gets the node type.
		 * 
		 * \return			Returns a NodeType enumeration indicating the type of the node.
		 **/
		virtual NodeType			type() const { return NodeType::DivAssign; }

	protected :
		// == Members.
		size_t						varIndex;
		size_t						rightIndex;
		mutable Object*				lastObject = nullptr;
	};

}	// namespace ve
