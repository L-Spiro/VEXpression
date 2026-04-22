#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a unary plus operation (+x).
	 **/
	class UnaryPlusNode : public AstNode {
	public :
		UnaryPlusNode(size_t child) : childIndex(child) {}

		
		// == Functions.
		/**
		 * Evaluates the unary plus operation.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the evaluated result of the child node unmodified.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			return context.getArena().nodes[childIndex]->evaluate(context);
		}

	protected :

	private :
		// == Members.
		size_t						childIndex;
	};

}	// namespace ve