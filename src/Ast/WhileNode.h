#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a while loop statement.
	 **/
	class WhileNode : public AstNode {
	public :
		WhileNode(size_t cond, size_t body) : conditionIndex(cond), bodyIndex(body) {}

		
		// == Functions.
		/**
		 * Evaluates the while loop.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the result of the evaluated loop.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result out, cond;
			
			while ((cond = context.getArena().nodes[conditionIndex]->evaluate(context)).isTruthy()) {
				out = context.getArena().nodes[bodyIndex]->evaluate(context);

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

			if (out.type == NumericConstant::Invalid) { out = cond; }

			return out;
		}

		/**
		 * Gets the node type.
		 * 
		 * \return			Returns a NodeType enumeration indicating the type of the node.
		 **/
		virtual NodeType			type() const override { return NodeType::While; }

	private :
		// == Members.
		size_t						conditionIndex;		/**< The arena index of the condition expression. */
		size_t						bodyIndex;			/**< The arena index of the body block. */
	};

}	// namespace ve
