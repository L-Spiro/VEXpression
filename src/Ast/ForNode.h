#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a standard for (init; cond; step) loop in the AST.
	 **/
	class ForNode : public AstNode {
	public :
		ForNode(size_t init, size_t cond, size_t step, size_t block)
			: initNode(init), condNode(cond), stepNode(step), blockNode(block) {}


		// == Functions.
		/**
		 * Evaluates the loop components and executes the block iteratively.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the result of the last statement, or the condition if empty.
		 **/
		Result							evaluate(ExecutionContext& context) const override {
			if (initNode != static_cast<size_t>(-1)) {
				context.getArena().nodes[initNode]->evaluate(context);
			}

			Result lastResult;
			lastResult.type = NumericConstant::Invalid;

			while (true) {
				Result condRes;
				condRes.type = NumericConstant::Signed;
				condRes.value.intVal = 1;

				if (condNode != static_cast<size_t>(-1)) {
					condRes = context.getArena().nodes[condNode]->evaluate(context);
				}

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

				if (!isTrue) {
					if (blockNode == static_cast<size_t>(-1) || lastResult.type == NumericConstant::Invalid) {
						return condRes;
					}
					return lastResult;
				}

				if (blockNode != static_cast<size_t>(-1)) {
					lastResult = context.getArena().nodes[blockNode]->evaluate(context);
				}

				if (stepNode != static_cast<size_t>(-1)) {
					context.getArena().nodes[stepNode]->evaluate(context);
				}
			}

			return lastResult;
		}

	protected :
		// == Members.
		/** The AST arena index for the initialization expression. -1 if omitted. **/
		size_t							initNode;
		/** The AST arena index for the condition expression. -1 if omitted. **/
		size_t							condNode;
		/** The AST arena index for the step expression. -1 if omitted. **/
		size_t							stepNode;
		/** The AST arena index for the block to execute. -1 if empty. **/
		size_t							blockNode;
	};

}	// namespace ve