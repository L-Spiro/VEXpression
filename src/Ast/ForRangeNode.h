#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a ranged for loop utilizing "in" or ":" in the AST.
	 **/
	class ForRangeNode : public AstNode {
	public :
		ForRangeNode(size_t varIdx, size_t obj, size_t block)
			: variableIndex(varIdx), objectNode(obj), blockNode(block) {}


		// == Functions.
		/**
		 * Evaluates the object and loops through its array length, binding the current index.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the result of the last statement, or false if empty.
		 **/
		Result							evaluate(ExecutionContext& context) const override {
			Result objRes = context.getArena().nodes[objectNode]->evaluate(context);

			Result lastResult;
			lastResult.type = NumericConstant::Invalid;

			if (objRes.type != NumericConstant::Object || objRes.value.objectVal == nullptr) {
				return lastResult;
			}

			size_t length = objRes.value.objectVal->arrayLength();

			for (size_t i = 0; i < length; ++i) {
				Result itemRes = objRes.value.objectVal->arrayAccess(i);

				context.setVariable(variableIndex, itemRes);

				if (blockNode != static_cast<size_t>(-1)) {
					lastResult = context.getArena().nodes[blockNode]->evaluate(context);
				}

				FlowState state = context.getFlowState();
				if (state == FlowState::Break) {
					context.clearFlowState();
					break;
				}
				else if (state == FlowState::Continue) {
					context.clearFlowState();
					continue;
				}
				else if (state == FlowState::Return) {
					return context.getReturnValue();
				}
			}

			if (blockNode == static_cast<size_t>(-1) || lastResult.type == NumericConstant::Invalid) {
				Result falseRes = Result::make(false);
				return falseRes;
			}

			return lastResult;
		}

	protected :
		// == Members.
		/** The resolved execution context index for the loop variable. **/
		size_t							variableIndex;
		/** The AST arena index for the target object being iterated over. **/
		size_t							objectNode;
		/** The AST arena index for the block to execute. -1 if empty. **/
		size_t							blockNode;
	};

}	// namespace ve
