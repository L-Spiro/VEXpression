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
		VectorNode(const std::vector<size_t>& elements) : elements(elements) {}

		/**
		 * Evaluates the vector initialization by evaluating all elements and storing them.
		 *
		 * \param context		The runtime execution context.
		 * \return				Returns an Object Result containing the newly allocated Vector.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Vector* newVec = context.allocateObject<Vector>();
			if (!newVec) { throw ErrorCode::Out_Of_Memory; }

			for (size_t node : elements) {
				newVec->pushBack(context.getArena().nodes[node]->evaluate(context));
			}
			
			Result out = newVec->createResult();
			VE_DELETE_SWAP(out, lastObject);

			return out;
		}

		/**
		 * Gets the node type.
		 * 
		 * \return			Returns a NodeType enumeration indicating the type of the node.
		 **/
		virtual NodeType			type() const { return NodeType::Vector; }

	protected :
		// == Members.
		/** The list of AST nodes representing the elements of the vector. **/
		std::vector<size_t>			elements;
		/** The object we create. */
		mutable Object*				lastObject = nullptr;
		
	};

}	// namespace ve
