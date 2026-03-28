#pragma once

#include "AstNode.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"

namespace ve {

	/**
	 * Represents an addition operation between two child nodes.
	 **/
	class AddNode : public AstNode {
	public :
		AddNode(size_t left, size_t right) : leftIndex(left), rightIndex(right) {}

		
		// == Functions.
		/**
		 * Evaluates the addition of the left and right child nodes.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the sum of the evaluated left and right nodes.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result leftVal = context.getArena().nodes[leftIndex]->evaluate(context);
			Result rightVal = context.getArena().nodes[rightIndex]->evaluate(context);

			NumericConstant common = ExecutionContext::getCastType(leftVal.type, rightVal.type);
			Result l = context.convertResult(leftVal, common);
			Result r = context.convertResult(rightVal, common);

			Result out;
			out.type = common;

			if (common == NumericConstant::Floating) {
				out.value.doubleVal = l.value.doubleVal + r.value.doubleVal;
			}
			else if (common == NumericConstant::Signed) {
				out.value.intVal = l.value.intVal + r.value.intVal;
			}
			else {
				out.value.uintVal = l.value.uintVal + r.value.uintVal;
			}

			return out;
		}

	protected :

	private :
		// == Members.
		size_t						leftIndex;
		size_t						rightIndex;
	};

}	// namespace ve
