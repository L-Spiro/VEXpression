#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <cassert>

namespace ve {

	/**
	 * Represents a bitwise AND operation between two child nodes.
	 **/
	class BitAndNode : public AstNode {
	public :
		BitAndNode(size_t left, size_t right) : leftIndex(left), rightIndex(right) {}

		
		// == Functions.
		/**
		 * Evaluates the bitwise AND of the left and right child nodes.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the bitwise product.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result leftVal = context.getArena().nodes[leftIndex]->evaluate(context);
			Result rightVal = context.getArena().nodes[rightIndex]->evaluate(context);

			NumericConstant common = ExecutionContext::getCastType(leftVal.type, rightVal.type);
			Result l = context.convertResult(leftVal, common);
			Result r = context.convertResult(rightVal, common);

			Result out;
			if (common == NumericConstant::Floating) {
				/*out.type = NumericConstant::Signed;
				out.value.intVal = static_cast<int64_t>(l.value.doubleVal) & static_cast<int64_t>(r.value.doubleVal);*/
				out.type = NumericConstant::Invalid;
			}
			else if (common == NumericConstant::Signed) {
				out.type = NumericConstant::Signed;
				out.value.intVal = l.value.intVal & r.value.intVal;
			}
			else if (common == NumericConstant::Unsigned) {
				out.type = NumericConstant::Unsigned;
				out.value.uintVal = l.value.uintVal & r.value.uintVal;
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
