#pragma once

#include "AstNode.h"

namespace ve {

	/**
	 * Represents a do-while loop in the abstract syntax tree.
	 **/
	class DoWhileNode : public AstNode {
	public:
		/**
		 * Constructs a do-while node.
		 *
		 * \param blockNode		The node ID of the code block to execute.
		 * \param condNode		The node ID of the condition expression.
		 **/
		inline						DoWhileNode(size_t blockNode, size_t condNode) :
			blockIndex(blockNode),
			condIndex(condNode) {
		}

		/**
		 * Evaluates the do-while loop iteratively.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \return				Returns an empty Result upon loop completion.
		 **/
		virtual Result				evaluate(ExecutionContext& context) const override {
			Result out;
			do {
				if (blockIndex != static_cast<size_t>(-1)) {
					out = context.getArena().nodes[blockIndex]->evaluate(context);
				}
				
				Result condRes = context.getArena().nodes[condIndex]->evaluate(context);

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

				
				if (!condRes.isTruthy()) {
					if (blockIndex != static_cast<size_t>(-1)) { return out; }
					return condRes;
				}
				
			} while (true);
			
			return out;
		}

		/**
		 * Gets the node type.
		 *
		 * \return			Returns a NodeType enumeration indicating the type of the node.
		 **/
		virtual NodeType			type() const override { return NodeType::DoWhile; }

	protected:
		size_t						blockIndex;
		size_t						condIndex;
	};

}	// namespace ve
