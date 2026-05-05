#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <cmath>

namespace ve {

	/**
	 * Represents a bitwise left-shift operation between two child nodes.
	 **/
	class ShlNode : public AstNode {
	public :
		ShlNode(size_t left, size_t right) : leftIndex(left), rightIndex(right) {}

		
		// == Functions.
		/**
		 * Evaluates the left child node shifted left by the right child node.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the shifted result based on the left node's original type.
		 * \throws			ErrorCode::Unknown_Numeric_Type if either of the the resolved common types is not supported.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result leftVal = context.getArena().nodes[leftIndex]->evaluate(context);
			Result rightVal = context.getArena().nodes[rightIndex]->evaluate(context);
			
			Result out;
			out = context.evaluateMath(leftVal, rightVal, ExprLexer::SHL);
			VE_DELETE_SWAP(out, lastObject);

			return out;
		}

		/**
		 * Gets the node type.
		 * 
		 * \return			Returns a NodeType enumeration indicating the type of the node.
		 **/
		virtual NodeType			type() const { return NodeType::Shl; }

	protected :

	private :
		// == Members.
		size_t						leftIndex;
		size_t						rightIndex;
		mutable Object*				lastObject = nullptr;
	};

}	// namespace ve
