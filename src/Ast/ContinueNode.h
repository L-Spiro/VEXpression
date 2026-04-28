#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a continue statement, skipping to the next iteration of the nearest enclosing loop.
	 **/
	class ContinueNode : public AstNode {
	public :
		ContinueNode() {}


		// == Functions.
		/**
		 * Evaluates the continue statement by signaling the execution context.
		 *
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns an Invalid Result.
		 **/
		Result					evaluate(ExecutionContext& context) const override {
			context.setContinue();
			return Result{};
		}
	};

}	// namespace ve
