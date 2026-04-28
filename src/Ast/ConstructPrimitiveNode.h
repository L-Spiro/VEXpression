#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <vector>

namespace ve {

	/**
	 * Represents a node that constructs and initializes a primitive scalar type.
	 **/
	class ConstructPrimitiveNode : public AstNode {
	public :
		ConstructPrimitiveNode(DataType target, const std::vector<size_t>& arguments)
			: targetType(target), args(arguments) {}


		// == Functions.
		/**
		 * Evaluates the node, creating a primitive result of the target type.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \return				Returns the constructed and casted primitive Result.
		 **/
		Result							evaluate(ExecutionContext& context) const override {
			if (args.empty()) {
				return context.castArgument(Result::make(0ull), targetType);
			}

			Result val = context.getArena().nodes[args[0]]->evaluate(context);
			return context.castArgument(val, targetType);
		}

	private :
		DataType						targetType;
		std::vector<size_t>				args;
	};

}	// namespace ve
