#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <cassert>

namespace ve {

	/**
	 * Represents a three-way comparison (spaceship) operation between two child nodes.
	 **/
	class SpaceshipNode : public AstNode {
	public :
		SpaceshipNode(size_t left, size_t right) : leftIndex(left), rightIndex(right) {}

		
		// == Functions.
		/**
		 * Evaluates the three-way comparison of the left and right child nodes.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns a Signed Result of -1, 0, or 1 representing the relative ordering.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result leftVal = context.getArena().nodes[leftIndex]->evaluate(context);
			Result rightVal = context.getArena().nodes[rightIndex]->evaluate(context);

			NumericConstant common = ExecutionContext::getCastType(leftVal.type, rightVal.type);
			Result l = context.convertResult(leftVal, common);
			Result r = context.convertResult(rightVal, common);

			Result out;
			out.type = NumericConstant::Signed;

			if (common == NumericConstant::Floating) {
				//out.value.intVal = l.value.doubleVal <=> r.value.doubleVal;
				if (l.value.doubleVal < r.value.doubleVal) { out.value.intVal = -1; }
				else if (l.value.doubleVal > r.value.doubleVal) { out.value.intVal = 1; }
				else { out.value.intVal = 0; }
			}
			else if (common == NumericConstant::Signed) {
				//out.value.intVal = l.value.intVal <=> r.value.intVal;
				if (l.value.intVal < r.value.intVal) { out.value.intVal = -1; }
				else if (l.value.intVal > r.value.intVal) { out.value.intVal = 1; }
				else { out.value.intVal = 0; }
			}
			else if (common == NumericConstant::Unsigned) {
				//out.value.intVal = l.value.uintVal <=> r.value.uintVal;
				if (l.value.uintVal < r.value.uintVal) { out.value.intVal = -1; }
				else if (l.value.uintVal > r.value.uintVal) { out.value.intVal = 1; }
				else { out.value.intVal = 0; }
			}
			else {
				assert(false);
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
