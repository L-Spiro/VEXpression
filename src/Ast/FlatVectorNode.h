#pragma once

#include "../Engine/Vector.h"
#include "AstNode.h"

#include <vector>

namespace ve {

	/**
	 * Represents a fully evaluated, flat array of primitive constants.
	 * Bypasses AST child node traversal to dramatically reduce memory footprint 
	 * and evaluation time for large static data sets.
	 **/
	class FlatVectorNode : public AstNode {
	public :
		/**
		 * Constructs a flat vector node with pre-evaluated data.
		 *
		 * \param data		The pre-computed vector of results to adopt.
		 **/
		inline							FlatVectorNode(std::vector<Result>&& data) : preEvaluatedData(std::move(data)) {}

		/**
		 * Evaluates a pre-computed flat vector node in O(1) time.
		 *
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns an object containing the fully populated vector.
		 **/
		virtual Result					evaluate(ExecutionContext& context) const override {
			Vector* newVec = context.allocateObject<Vector>();
			if (!newVec) { throw ErrorCode::Out_Of_Memory; }
			
			newVec->setFlat(preEvaluatedData);
			Result out = newVec->createResult();

			VE_DELETE_SWAP(out, lastObject);
			
			return out;
		}

		/**
		 * Gets the node type.
		 * 
		 * \return			Returns a NodeType enumeration indicating the type of the node.
		 **/
		virtual NodeType				type() const override { return NodeType::FlatVector; }

	protected :
		// The pre-allocated, densely packed array of primitive results.
		std::vector<Result>				preEvaluatedData;
		mutable Object*					lastObject = nullptr;
	};

}	// namespace ve
