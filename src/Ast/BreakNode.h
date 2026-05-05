#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a break statement, halting the nearest enclosing loop.
	 **/
	class BreakNode : public AstNode {
	public :
		BreakNode() {}


		// == Functions.
		/**
		 * Evaluates the break statement by signaling the execution context.
		 *
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns an Invalid Result.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			context.setBreak();
			return Result{};
		}

		/**
		 * Gets the node type.
		 * 
		 * \return			Returns a NodeType enumeration indicating the type of the node.
		 **/
		virtual NodeType			type() const { return NodeType::Break; }
	};

}	// namespace ve
