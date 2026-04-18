#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <cassert>

namespace ve {

	/**
	 * Represents an assignment operation (Identifier = Expression).
	 **/
	class AssignNode : public AstNode {
	public :
		AssignNode(size_t varId, size_t exprId) : varIndex(varId), exprIndex(exprId) {}

		
		// == Functions.
		/**
		 * Evaluates the expression and stores the result in the target variable slot.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the evaluated result of the expression.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result val = context.getArena().nodes[exprIndex]->evaluate(context);
			context.getVariable(varIndex) = val;
			return val;
		}

	protected :

	private :
		// == Members.
		size_t						varIndex;
		size_t						exprIndex;
	};

}	// namespace ve
