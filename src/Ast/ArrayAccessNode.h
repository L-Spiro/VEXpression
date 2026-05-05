#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Map.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a standard array or string index access operation.
	 **/
	class ArrayAccessNode : public AstNode {
		friend class			ArrayAccessExNode;
	public :
		ArrayAccessNode(size_t target, size_t index) : targetIndex(target), indexIndex(index) {}


		// == Functions.
		/**
		 * Evaluates the array access.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the element at the specified index.
		 **/
		Result					evaluate(ExecutionContext& context) const override {
			std::vector<size_t> indexChain;
			const ArrayAccessNode* currentAccess = this;

			while (true) {
				indexChain.push_back(currentAccess->indexIndex);
				
				ve::AstNode* nextBase = context.getArena().nodes[currentAccess->targetIndex].get();
				
				if (nextBase->type() == NodeType::ArrayAccess) {
					currentAccess = static_cast<const ArrayAccessNode*>(nextBase);
				}
				else {
					break;
				}
			}

			// We hit the bottom. Evaluate the root target.
			Result currentRes = context.getArena().nodes[currentAccess->targetIndex]->evaluate(context);

			// Walk back up, applying each index sequentially.
			for (auto it = indexChain.rbegin(); it != indexChain.rend(); ++it) {
				if (currentRes.type != NumericConstant::Object || !currentRes.value.objectVal) {
					return Result{};
				}

				Result indexRes = context.getArena().nodes[*it]->evaluate(context);

				if (currentRes.value.objectVal->type() & BuiltInType_Map) {
					Map* mapObj = static_cast<Map*>(currentRes.value.objectVal);
					currentRes = mapObj->valueFromKey(indexRes);
				}
				else {
					int64_t idx = 0;
					if (indexRes.type == NumericConstant::Signed) {
						idx = indexRes.value.intVal;
					}
					else if (indexRes.type == NumericConstant::Unsigned) {
						idx = static_cast<int64_t>(indexRes.value.uintVal);
					}
					else {
						return Result{};
					}
					currentRes = currentRes.value.objectVal->arrayAccess(idx);
				}
			}

			return currentRes;
		}

		/**
		 * Gets the node type.
		 * 
		 * \return			Returns a NodeType enumeration indicating the type of the node.
		 **/
		virtual NodeType			type() const { return NodeType::ArrayAccess; }

	protected :
		// == Members.
		size_t						targetIndex;
		size_t						indexIndex;
	};

}	// namespace ve
