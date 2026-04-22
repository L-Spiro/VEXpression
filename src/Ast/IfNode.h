#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents an if/else branching structure in the AST.
	 * If a branch is empty, the result of the boolean condition is returned instead.
	 **/
	class IfNode : public AstNode {
	public :
		IfNode(size_t cond, size_t tb, size_t fb)
			: conditionNode(cond), trueBlockNode(tb), falseBlockNode(fb) {}


		// == Functions.
		/**
		 * Evaluates the condition and executes the appropriate branch.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the result of the executed branch, or the condition itself if empty.
		 **/
		Result							evaluate(ExecutionContext& context) const override {
			Result condRes = context.getArena().nodes[conditionNode]->evaluate(context);
			
			bool isTrue = false;
			
			if (condRes.type == NumericConstant::Floating) {
				if (condRes.value.doubleVal != 0.0) {
					isTrue = true;
				}
			}
			else if (condRes.type == NumericConstant::Object) {
				// False.
			}
			else if (condRes.type != NumericConstant::Invalid) {
				if (condRes.value.uintVal != 0) {
					isTrue = true;
				}
			}

			if (isTrue) {
				if (trueBlockNode != static_cast<size_t>(-1)) {
					return context.getArena().nodes[trueBlockNode]->evaluate(context);
				}
				else {
					return condRes;
				}
			}
			else {
				if (falseBlockNode != static_cast<size_t>(-1)) {
					return context.getArena().nodes[falseBlockNode]->evaluate(context);
				}
				else {
					return condRes;
				}
			}
		}

	protected :
		// == Members.
		/** The AST arena index for the condition expression. **/
		size_t							conditionNode;
		/** The AST arena index for the true block. -1 if the block is empty. **/
		size_t							trueBlockNode;
		/** The AST arena index for the false block. -1 if the block is empty. **/
		size_t							falseBlockNode;
	};

}	// namespace ve