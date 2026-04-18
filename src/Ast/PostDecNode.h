#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <cassert>

namespace ve {

	/**
	 * Represents a postfix decrement operation (x--).
	 **/
	class PostDecNode : public AstNode {
	public :
		PostDecNode(size_t varId) : varIndex(varId) {}

		
		// == Functions.
		/**
		 * Evaluates the postfix decrement by saving the current value, subtracting 1 from the variable, and returning the old value.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the original result before decrementing.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result val = context.getVariable(varIndex);
			Result out = val;

			if (val.type == NumericConstant::Floating) {
				val.value.doubleVal -= 1.0;
			}
			else if (val.type == NumericConstant::Signed) {
				val.value.intVal -= 1;
			}
			else if (val.type == NumericConstant::Unsigned) {
				val.value.uintVal -= 1;
			}
			else {
				assert(false);
			}

			context.getVariable(varIndex) = val;
			return out;
		}

	protected :

	private :
		// == Members.
		size_t						varIndex;
	};

}	// namespace ve
