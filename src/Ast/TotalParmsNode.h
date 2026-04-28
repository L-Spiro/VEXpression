#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents the '$$' operator, which evaluates to the total number of parameters passed to the script.
	 **/
	class TotalParmsNode : public AstNode {
	public :
		/**
		 * Constructs a TotalParmsNode.
		 **/
		TotalParmsNode() = default;


		// == Functions.
		/**
		 * Retrieves the total number of script parameters from the context.
		 *
		 * \param context		The runtime execution context.
		 * \return				Returns a Result containing the total parameter count as a primitive integer.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			return Result::make(context.totalParms());
		}
	};

}	// namespace ve
