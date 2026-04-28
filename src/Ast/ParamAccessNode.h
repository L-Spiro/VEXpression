#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents the '$' operator (e.g., $0, $1, $(i+2)), which retrieves a script parameter by its evaluated index.
	 **/
	class ParamAccessNode : public AstNode {
	public :
		/**
		 * Constructs a ParamAccessNode.
		 *
		 * \param exprId		The arena index of the child expression evaluating to the parameter index.
		 **/
		ParamAccessNode(size_t exprId) : exprIndex(exprId) {}


		// == Functions.
		/**
		 * Evaluates the index expression and retrieves the corresponding parameter from the context.
		 *
		 * \param context		The runtime execution context.
		 * \return				Returns the parameter Result. Returns an Invalid Result if the index evaluation fails or is out of bounds.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Result idxRes = context.getArena().nodes[exprIndex]->evaluate(context);

			if (idxRes.type == NumericConstant::Invalid) { return Result{}; }

			if (!idxRes.isPrimitive()) { return Result{}; }

			int64_t rawIdx = Object::arrayIndexToLinearIndex( context.convertResult(idxRes, NumericConstant::Signed).value.intVal, context.totalParms() );

			return context.getParm(static_cast<size_t>(rawIdx));
		}

	private :
		size_t						exprIndex;
	};

}	// namespace ve
