#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/FunctionDef.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <vector>

namespace ve {

	/**
	 * Represents a compiled function call, holding its definition and evaluated argument nodes.
	 **/
	class FunctionCallNode : public AstNode {
	public :
		FunctionCallNode(const FunctionDef& func, const std::vector<size_t>& args) 
			: functionDefinition(func), arguments(args) {}

		
		// == Functions.
		/**
		 * Evaluates all arguments, casts them to the registered parameter types, and executes the callback.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the result of the intrinsic function.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			std::vector<Result> evaluatedArgs;
			evaluatedArgs.reserve(arguments.size());

			for (size_t i = 0; i < arguments.size(); ++i) {
				Result rawResult = context.getArena().nodes[arguments[i]]->evaluate(context);
				
				DataType expectedType = functionDefinition.parameters[i].type;
				evaluatedArgs.push_back(context.castArgument(rawResult, expectedType));
			}

			return functionDefinition.callback(&context, evaluatedArgs);
		}

	private :
		// == Members.
		FunctionDef					functionDefinition;
		std::vector<size_t>			arguments;
	};

}	// namespace ve
