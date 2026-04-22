#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a prefix increment operation (++x).
	 **/
	class PreIncNode : public AstNode {
	public :
		PreIncNode(size_t varId) : varIndex(varId) {}

		
		// == Functions.
		/**
		 * Evaluates the prefix increment by adding 1 to the variable, saving it, and returning the new value.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the incremented result.
		 * \throws			ErrorCode::Unknown_Numeric_Type if the resolved common type is not supported.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result val = context.getVariable(varIndex);

			if (val.type == NumericConstant::Floating) {
				val.value.doubleVal += 1.0;
			}
			else if (val.type == NumericConstant::Signed) {
				val.value.intVal += 1;
			}
			else if (val.type == NumericConstant::Unsigned) {
				val.value.uintVal += 1;
			}
			else {
				throw ErrorCode::Unknown_Numeric_Type;
			}

			context.getVariable(varIndex) = val;
			return val;
		}

	protected :

	private :
		// == Members.
		size_t						varIndex;
	};

}	// namespace ve
