#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "../Engine/Vector.h"
#include "AstNode.h"

#include <vector>

namespace ve {

	/**
	 * AST node representing an inline vector initialization.
	 **/
	class VectorNode : public AstNode {
	public :
		VectorNode(const std::vector<AstNode*>& elements) : elements(elements) {}

		/**
		 * Evaluates the vector initialization by evaluating all elements and storing them.
		 *
		 * \param context		The runtime execution context.
		 * \return				Returns an Object Result containing the newly allocated Vector.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Vector* newVec = context.allocateObject<Vector>();
			if (!newVec) { throw ErrorCode::Out_Of_Memory; }
			
			for (AstNode* node : elements) {
				newVec->pushBack(node->evaluate(context));
			}
			
			return newVec->createResult();
		}

	protected :
		// == Members.
		/** The list of AST nodes representing the elements of the vector. **/
		std::vector<AstNode*>			elements;
	};

}	// namespace ve
