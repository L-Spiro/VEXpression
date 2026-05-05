#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <vector>

namespace ve {

	/**
	 * Represents a sequential block of statements.
	 **/
	class SequenceNode : public AstNode {
	public :
		SequenceNode(const std::vector<size_t>& stmts) : statements(stmts) {}

		
		// == Functions.
		/**
		 * Evaluates each statement in sequence.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the result of the final statement in the sequence, or 0 if empty.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result lastResult;
			lastResult.type = NumericConstant::Invalid;
			lastResult.value.uintVal = 0;
			
			for (size_t stmtIndex : statements) {
				if (size_t(-1) == stmtIndex) { throw ErrorCode::Undefined_Identifier; }
				lastResult = context.getArena().nodes[stmtIndex]->evaluate(context);

				// Handle continue, break, or return.
				if (context.getFlowState() == FlowState::Return) {
					return context.getReturnValue();
				}
				if (context.getFlowState() != FlowState::Normal) {
					break;
				}
			}
			
			return lastResult;
		}

		/**
		 * Gets the node type.
		 * 
		 * \return			Returns a NodeType enumeration indicating the type of the node.
		 **/
		virtual NodeType			type() const { return NodeType::Sequence; }

	protected :

	private :
		// == Members.
		std::vector<size_t>			statements;
	};

}	// namespace ve
