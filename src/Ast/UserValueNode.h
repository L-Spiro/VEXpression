#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a runtime evaluation of the external user-defined value ('??').
	 **/
	class UserValueNode : public AstNode {
	public :
		/**
		 * Constructs a UserValueNode.
		 **/
		UserValueNode() = default;


		// == Functions.
		/**
		 * Retrieves the user-defined value dynamically from the execution context at runtime.
		 *
		 * \param context		The runtime execution context.
		 * \return				Returns the Result containing the current external user value.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			return context.getUserValue();
		}
	};

}	// namespace ve
