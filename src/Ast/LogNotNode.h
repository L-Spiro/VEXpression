#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <cassert>

namespace ve {

	/**
	 * Represents a logical NOT operation (!x).
	 **/
	class LogNotNode : public AstNode {
	public :
		LogNotNode(size_t child) : childIndex(child) {}

		
		// == Functions.
		/**
		 * Evaluates the logical inversion of the child node.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns a Signed Result of 1 if the value was conceptually false, or 0 if true.
		 * \throws			ErrorCode::Unknown_Numeric_Type if the resolved common type is not supported.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result val = context.getArena().nodes[childIndex]->evaluate(context);
			bool isTrue = false;

			if (val.type == NumericConstant::Floating) {
				isTrue = (val.value.doubleVal != 0.0);
			}
			else if (val.type == NumericConstant::Signed) {
				isTrue = (val.value.intVal != 0);
			}
			else if (val.type == NumericConstant::Unsigned) {
				isTrue = (val.value.uintVal != 0);
			}
			else {
				throw ErrorCode::Unknown_Numeric_Type;
			}

			Result out;
			out.type = NumericConstant::Signed;
			out.value.intVal = isTrue ? 0 : 1;

			return out;
		}

	protected :

	private :
		// == Members.
		size_t						childIndex;
	};

}	// namespace ve
