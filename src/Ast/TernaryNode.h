#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <cassert>

namespace ve {

	/**
	 * Represents a conditional (ternary) operation between a condition and two potential outcome nodes.
	 **/
	class TernaryNode : public AstNode {
	public :
		TernaryNode(size_t cond, size_t trueBranch, size_t falseBranch) 
			: condIndex(cond), trueIndex(trueBranch), falseIndex(falseBranch) {}

		
		// == Functions.
		/**
		 * Evaluates the condition node and subsequently evaluates only the chosen branch, providing short-circuiting.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the result of either the true or false branch.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result condVal = context.getArena().nodes[condIndex]->evaluate(context);
			
			bool isTrue = false;
			if (condVal.type == NumericConstant::Floating) {
				isTrue = (condVal.value.doubleVal != 0.0);
			}
			else if (condVal.type == NumericConstant::Signed) {
				isTrue = (condVal.value.intVal != 0);
			}
			else if (condVal.type == NumericConstant::Unsigned) {
				isTrue = (condVal.value.uintVal != 0);
			}
			else {
				assert(false);
			}

			if (isTrue) {
				return context.getArena().nodes[trueIndex]->evaluate(context);
			}
			
			return context.getArena().nodes[falseIndex]->evaluate(context);
		}

	protected :

	private :
		// == Members.
		size_t						condIndex;
		size_t						trueIndex;
		size_t						falseIndex;
	};

}	// namespace ve
