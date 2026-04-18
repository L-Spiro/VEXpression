#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <cassert>

namespace ve {

	/**
	 * Represents a variable identifier read operation.
	 **/
	class VarNode : public AstNode {
	public :
		VarNode(size_t varId) : varIndex(varId) {}

		
		// == Functions.
		/**
		 * Fetches the value of the variable from the execution context.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the current result stored in the variable slot.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			return context.getVariable(varIndex);
		}

	protected :

	private :
		// == Members.
		size_t						varIndex;
	};

}	// namespace ve
