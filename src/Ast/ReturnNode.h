#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a return statement, exiting the current function call and optionally returning a value.
	 **/
	class ReturnNode : public AstNode {
	public :
		ReturnNode(size_t expr) : exprIndex(expr) {}


		// == Functions.
		/**
		 * Evaluates the return statement and signals the execution context.
		 *
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the evaluated Result, or Invalid if no expression was provided.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result out = Result{};
			
			if (exprIndex != Object::InvalidIndex) {
				out = context.getArena().nodes[exprIndex]->evaluate(context);
			}

			context.setReturn(out);
			return out;
		}

		/**
		 * Gets the node type.
		 * 
		 * \return			Returns a NodeType enumeration indicating the type of the node.
		 **/
		virtual NodeType			type() const { return NodeType::Return; }

	protected :
		// == Members.
		size_t						exprIndex;
	};

}	// namespace ve
