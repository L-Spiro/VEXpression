#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <cassert>

namespace ve {

	/**
	 * Represents a logical OR operation between two child nodes.
	 **/
	class LogOrNode : public AstNode {
	public :
		LogOrNode(size_t left, size_t right) : leftIndex(left), rightIndex(right) {}

		
		// == Functions.
		/**
		 * Evaluates the logical OR of the left and right child nodes, providing short-circuit evaluation.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns a Signed Result of 1 if true, 0 if false.
		 * \throws			ErrorCode::Unknown_Numeric_Type if either of the the resolved common types is not supported.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result leftVal = context.getArena().nodes[leftIndex]->evaluate(context);
			
			bool leftBool = false;
			if (leftVal.type == NumericConstant::Floating) {
				leftBool = (leftVal.value.doubleVal != 0.0);
			}
			else if (leftVal.type == NumericConstant::Signed) {
				leftBool = (leftVal.value.intVal != 0);
			}
			else if (leftVal.type == NumericConstant::Unsigned) {
				leftBool = (leftVal.value.uintVal != 0);
			}
			else {
				throw ErrorCode::Unknown_Numeric_Type;
			}

			Result out;
			out.type = NumericConstant::Signed;

			// Short-circuit.
			if (leftBool) {
				out.value.intVal = int64_t(leftBool);
				return out;
			}

			Result rightVal = context.getArena().nodes[rightIndex]->evaluate(context);
			
			bool rightBool = false;
			if (rightVal.type == NumericConstant::Floating) {
				rightBool = (rightVal.value.doubleVal != 0.0);
			}
			else if (rightVal.type == NumericConstant::Signed) {
				rightBool = (rightVal.value.intVal != 0);
			}
			else if (rightVal.type == NumericConstant::Unsigned) {
				rightBool = (rightVal.value.uintVal != 0);
			}
			else {
				throw ErrorCode::Unknown_Numeric_Type;
			}

			out.value.intVal = int64_t(rightBool);
			return out;
		}

	protected :

	private :
		// == Members.
		size_t						leftIndex;
		size_t						rightIndex;
	};

}	// namespace ve
