#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <cassert>

namespace ve {

	/**
	 * Represents a unary minus (negation) operation (-x).
	 **/
	class UnaryMinusNode : public AstNode {
	public :
		UnaryMinusNode(size_t child) : childIndex(child) {}

		
		// == Functions.
		/**
		 * Evaluates the mathematical negation of the child node.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the negated result.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result val = context.getArena().nodes[childIndex]->evaluate(context);
			Result out;

			if (val.type == NumericConstant::Floating) {
				out.type = NumericConstant::Floating;
				out.value.doubleVal = -val.value.doubleVal;
			}
			else if (val.type == NumericConstant::Signed) {
				out.type = NumericConstant::Signed;
				out.value.intVal = -val.value.intVal;
			}
			else if (val.type == NumericConstant::Unsigned) {
				out.type = NumericConstant::Unsigned;
				out.value.uintVal = -val.value.uintVal;
			}
			else {
				assert(false);
			}

			return out;
		}

	protected :

	private :
		// == Members.
		size_t						childIndex;
	};

}	// namespace ve
