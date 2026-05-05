#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <cmath>

namespace ve {

	/**
	 * Represents a division operation between two child nodes.
	 **/
	class ModNode : public AstNode {
	public :
		ModNode(size_t left, size_t right) : leftIndex(left), rightIndex(right) {}

		
		// == Functions.
		/**
		 * Evaluates the division of the left child node by the right child node.
		 * Safely returns 0 if an integer division by zero is attempted.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the quotient of the evaluated left and right nodes.
		 * \throws			ErrorCode::Unknown_Numeric_Type if the resolved common type is not supported.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result leftVal = context.getArena().nodes[leftIndex]->evaluate(context);
			Result rightVal = context.getArena().nodes[rightIndex]->evaluate(context);
			
			Result out;
			out = context.evaluateMath(leftVal, rightVal, ExprLexer::MOD);
			VE_DELETE_SWAP(out, lastObject);

			return out;
		}

		/**
		 * Gets the node type.
		 * 
		 * \return			Returns a NodeType enumeration indicating the type of the node.
		 **/
		virtual NodeType			type() const { return NodeType::Mod; }

	protected :

	private :
		// == Members.
		size_t						leftIndex;
		size_t						rightIndex;
		mutable Object*				lastObject = nullptr;
	};

}	// namespace ve