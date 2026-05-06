#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <string>

namespace ve {

	/**
	 * Represents a scope resolution or member-access operation.
	 **/
	class ScopeNode : public AstNode {
	public :
		ScopeNode(size_t left, const std::string& memberName) : leftIndex(left), member(memberName) {}

		
		// == Functions.
		/**
		 * Evaluates the scope access by resolving the left child and calling the user callback.
		 * * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the result of the evaluated scope operation.
		 * \throws			Throws if the callback fails or is not assigned.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result leftVal = context.getArena().nodes[leftIndex]->evaluate(context);
			
			Result out;
			out = context.evaluateScope(leftVal, member);
			VE_DELETE_SWAP(out, lastObject);

			return out;
		}

		/**
		 * Gets the node type.
		 * * \return			Returns a NodeType enumeration indicating the type of the node.
		 **/
		virtual NodeType			type() const override { return NodeType::Scope; }

	private :
		// == Members.
		size_t						leftIndex;	/**< The arena index of the left expression node. */
		std::string					member;		/**< The string identifier on the right side of the scope operator. */
		mutable Object*				lastObject = nullptr;
	};

}	// namespace ve
