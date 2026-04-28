#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/FunctionDef.h"
#include "../Engine/Result.h"
#include "../Engine/Vector.h"
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

				// If it can operate on every element in a vector and we are being passed exactly 1 vector.
				if (functionDefinition.operateOnVectorElements && arguments.size() == 1) {
					if (rawResult.type == NumericConstant::Object && rawResult.value.objectVal && (rawResult.value.objectVal->type() & BuiltInType_Vector)) {
						Vector* vec = static_cast<Vector*>(rawResult.value.objectVal);
						evaluatedArgs.resize(1);
						for (size_t i = 0; i < vec->arrayLength(); ++i ) {
							evaluatedArgs[0] = context.castArgument(vec->directAccess(i), expectedType);
							if (evaluatedArgs[0].type == NumericConstant::Invalid) { return Result{}; }
							vec->directAccess(i) = functionDefinition.callback(&context, evaluatedArgs);
						}
						return vec->createResult();
					}
				}
				
				if (i >= functionDefinition.parameters.size()) {
					evaluatedArgs.push_back(rawResult);
				}
				else {
					evaluatedArgs.push_back(context.castArgument(rawResult, expectedType));
					if (evaluatedArgs[evaluatedArgs.size()-1].type == NumericConstant::Invalid) { return Result{}; }
				}
			}

			return functionDefinition.callback(&context, evaluatedArgs);
		}

	private :
		// == Members.
		FunctionDef					functionDefinition;
		std::vector<size_t>			arguments;
	};

}	// namespace ve
