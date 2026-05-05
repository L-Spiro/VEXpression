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
		 * Evaluates the method call node, iteratively unrolling left-recursive targets 
		 * to prevent stack exhaustion during deep execution chains.
		 *
		 * \param context	The execution context containing the AST arena and state.
		 * \return			The calculated Result of the method call chain.
		 **/
		Result					evaluate(ExecutionContext& context) const override {
			std::vector<const MethodCallNode*> chain;
			chain.push_back(this);

			ve::AstNode* currentBase = context.getArena().nodes[targetNode].get();

			while (currentBase->type() == NodeType::MethodCall) {
				const MethodCallNode* methodNode = static_cast<const MethodCallNode*>(currentBase);
				chain.push_back(methodNode);
				currentBase = context.getArena().nodes[methodNode->targetNode].get();
			}

			Result currentTargetRes = currentBase->evaluate(context);

			if (currentTargetRes.type == NumericConstant::Invalid) { return currentTargetRes; }

			for (auto it = chain.rbegin(); it != chain.rend(); ++it) {
				const MethodCallNode* callNode = *it;

				std::vector<Result> evaluatedArgs;
				evaluatedArgs.reserve(callNode->argNodes.size() + 1);
				
				evaluatedArgs.push_back(currentTargetRes);

				for (size_t i = 0; i < callNode->argNodes.size(); ++i) {
					auto idx = callNode->argNodes[i];
					if (size_t(-1) == idx) { throw ErrorCode::Undefined_Identifier; }
					evaluatedArgs.push_back(context.getArena().nodes[idx]->evaluate(context));
				}

				FunctionDef funcDef;
				
				if (!context.getFunction(callNode->methodName, evaluatedArgs.size(), funcDef)) { return Result{}; }

				if (funcDef.operateOnVectorElements && evaluatedArgs.size() == 1) {
					if (evaluatedArgs[0].type == NumericConstant::Object && evaluatedArgs[0].value.objectVal && (evaluatedArgs[0].value.objectVal->type() & BuiltInType_Vector)) {
						Vector* vec = static_cast<Vector*>(evaluatedArgs[0].value.objectVal);
						DataType expectedType = funcDef.parameters.empty() ? DataType::Double : funcDef.parameters[0].type;
						
						std::vector<Result> singleArg(1);
						bool vectorFailed = false;
						
						for (size_t i = 0; i < vec->arrayLength(); ++i ) {
							singleArg[0] = context.castArgument(vec->directAccess(i), expectedType);
							if (singleArg[0].type == NumericConstant::Invalid) { 
								vectorFailed = true;
								break; 
							}
							vec->directAccess(i) = funcDef.callback(&context, singleArg);
						}
						
						if (vectorFailed) { return Result{}; }

						currentTargetRes = vec->createResult();
						continue;
					}
				}

				bool castFailed = false;
				for (size_t i = 0; i < evaluatedArgs.size(); ++i) {
					if (i < funcDef.parameters.size()) {
						evaluatedArgs[i] = context.castArgument(evaluatedArgs[i], funcDef.parameters[i].type);
						if (evaluatedArgs[i].type == NumericConstant::Invalid) { 
							castFailed = true;
							break;
						}
					}
				}
				
				if (castFailed) { return Result{}; }

				try {
					currentTargetRes = funcDef.callback(&context, evaluatedArgs);
				}
				catch (...) {
					return Result{};
				}
			}

			return currentTargetRes;
		}

		/**
		 * Gets the node type.
		 * 
		 * \return			Returns a NodeType enumeration indicating the type of the node.
		 **/
		virtual NodeType			type() const { return NodeType::MethodCall; }

	protected :
		// == Members.
		/** The AST arena index for the target expression being called on. **/
		size_t						targetNode;
		/** The string name of the method being called. **/
		std::string					methodName;
		/** The AST arena indices for the arguments. **/
		std::vector<size_t>			argNodes;
	};

}	// namespace ve
