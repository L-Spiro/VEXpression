#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <string>
#include <vector>

namespace ve {

	/**
	 * Represents a method call on an evaluated expression using the DOT operator.
	 * Syntactically transforms obj.method(args...) into method(obj, args...) for the function registry.
	 **/
	class MethodCallNode : public AstNode {
	public :
		MethodCallNode(size_t target, const std::string& method, const std::vector<size_t>& arguments)
			: targetNode(target), methodName(method), argNodes(arguments) {}


		// == Functions.
		/**
		 * Evaluates the target expression, prepends it to the evaluated arguments, and calls the intrinsic function.
		 *
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the result of the method call.
		 **/
		Result							evaluate(ExecutionContext& context) const override {
			Result targetRes = context.getArena().nodes[targetNode]->evaluate(context);

			if (targetRes.type == NumericConstant::Invalid) {
				return targetRes;
			}

			std::vector<Result> evaluatedArgs;
			evaluatedArgs.reserve(argNodes.size() + 1);
			
			evaluatedArgs.push_back(targetRes);

			for (size_t i = 0; i < argNodes.size(); ++i) {
				evaluatedArgs.push_back(context.getArena().nodes[argNodes[i]]->evaluate(context));
			}

			FunctionDef funcDef;
			
			if (!context.getFunction(methodName, evaluatedArgs.size(), funcDef)) {
				Result invalidRes;
				invalidRes.type = NumericConstant::Invalid;
				return invalidRes;
			}

			if (!funcDef.parameters.empty()) {
				if (funcDef.parameters[0].type == DataType::String) {
					if (targetRes.type != NumericConstant::Object || targetRes.value.objectVal == nullptr || !(targetRes.value.objectVal->type() & BuiltInType_String)) {
						Result invalidRes;
						invalidRes.type = NumericConstant::Invalid;
						return invalidRes;
					}
				}
			}

			try {
				return funcDef.callback(&context, evaluatedArgs);
			}
			catch (...) {}

			Result errorRes;
			errorRes.type = NumericConstant::Invalid;
			return errorRes;
		}

	protected :
		// == Members.
		/** The AST arena index for the target expression being called on. **/
		size_t							targetNode;
		/** The string name of the method being called. **/
		std::string						methodName;
		/** The AST arena indices for the arguments. **/
		std::vector<size_t>				argNodes;
	};

}	// namespace ve
