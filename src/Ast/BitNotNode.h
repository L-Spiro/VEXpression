#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <cassert>

namespace ve {

	/**
	 * Represents a bitwise NOT operation (~x).
	 **/
	class BitNotNode : public AstNode {
	public :
		BitNotNode(size_t child) : childIndex(child) {}

		
		// == Functions.
		/**
		 * Evaluates the bitwise inversion of the child node.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the inverted bits.
		 * \throws			ErrorCode::Unknown_Numeric_Type if the resolved common type is not supported.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result val = context.getArena().nodes[childIndex]->evaluate(context);
			Result out;

			if (val.type == NumericConstant::Floating) {
				out.type = NumericConstant::Signed;
				out.value.intVal = ~static_cast<int64_t>(val.value.doubleVal);
			}
			else if (val.type == NumericConstant::Signed) {
				out.type = NumericConstant::Signed;
				out.value.intVal = ~val.value.intVal;
			}
			else if (val.type == NumericConstant::Unsigned) {
				out.type = NumericConstant::Unsigned;
				out.value.uintVal = ~val.value.uintVal;
			}
			else {
				throw ErrorCode::Unknown_Numeric_Type;
			}

			return out;
		}

	protected :

	private :
		// == Members.
		size_t						childIndex;
	};

}	// namespace ve
