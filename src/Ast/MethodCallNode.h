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

			if (targetRes.type == NumericConstant::Invalid) { return targetRes; }

			std::vector<Result> evaluatedArgs;
			evaluatedArgs.reserve(argNodes.size() + 1);
			
			evaluatedArgs.push_back(targetRes);

			for (size_t i = 0; i < argNodes.size(); ++i) {
				evaluatedArgs.push_back(context.getArena().nodes[argNodes[i]]->evaluate(context));
			}

			FunctionDef funcDef;
			
			if (!context.getFunction(methodName, evaluatedArgs.size(), funcDef)) { return Result{}; }

			// If it can operate on every element in a vector and we are being passed exactly 1 vector.
			if (funcDef.operateOnVectorElements && evaluatedArgs.size() == 1) {
				if (evaluatedArgs[0].type == NumericConstant::Object && evaluatedArgs[0].value.objectVal && (evaluatedArgs[0].value.objectVal->type() & BuiltInType_Vector)) {
					Vector* vec = static_cast<Vector*>(evaluatedArgs[0].value.objectVal);
					DataType expectedType = funcDef.parameters.empty() ? DataType::Double : funcDef.parameters[0].type;
					
					std::vector<Result> singleArg(1);
					for (size_t i = 0; i < vec->arrayLength(); ++i ) {
						singleArg[0] = context.castArgument(vec->directAccess(i), expectedType);
						if (singleArg[0].type == NumericConstant::Invalid) { return Result{}; }
						vec->directAccess(i) = funcDef.callback(&context, singleArg);
					}
					return vec->createResult();
				}
			}

			// Cast all arguments to their expected types defined by the function signature.
			for (size_t i = 0; i < evaluatedArgs.size(); ++i) {
				if (i < funcDef.parameters.size()) {
					evaluatedArgs[i] = context.castArgument(evaluatedArgs[i], funcDef.parameters[i].type);
					if (evaluatedArgs[i].type == NumericConstant::Invalid) { 
						return Result{}; 
					}
				}
			}

			try {
				return funcDef.callback(&context, evaluatedArgs);
			}
			catch (...) {}

			return Result{};
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
