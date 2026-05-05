#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a continue statement, skipping to the next iteration of the nearest enclosing loop.
	 **/
	class ContinueNode : public AstNode {
	public :
		ContinueNode() {}


		// == Functions.
		/**
		 * Evaluates the continue statement by signaling the execution context.
		 *
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns an Invalid Result.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			context.setContinue();
			return Result{};
		}

		/**
		 * Gets the node type.
		 * 
		 * \return			Returns a NodeType enumeration indicating the type of the node.
		 **/
		virtual NodeType			type() const { return NodeType::Continue; }
	};

}	// namespace ve
