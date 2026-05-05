#pragma once

#include "../Engine/Errors.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents an extended (sliced) array or string access operation.
	 **/
	class ArrayAccessExNode : public AstNode {
	public :
		ArrayAccessExNode(size_t target, size_t start, size_t end, uint32_t mask) 
			: targetIndex(target), startIndex(start), endIndex(end), flagsMask(mask) {}


		// == Functions.
		/**
		 * Evaluates the sliced array access.
		 * 
		 * \param context	The execution context containing variables and runtime states.
		 * \return			Returns the sliced sub-array or sub-string.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			std::vector<const ve::AstNode*> chain;
			chain.push_back(this);

			ve::AstNode* currentBase = context.getArena().nodes[targetIndex].get();

			// Walk down the left spine, relying on static type identifiers instead of RTTI.
			while (true) {
				if (currentBase->type() == NodeType::ArrayAccess) {
					chain.push_back(currentBase);
					currentBase = context.getArena().nodes[static_cast<const ArrayAccessNode*>(currentBase)->targetIndex].get();
				}
				else if (currentBase->type() == NodeType::ArrayAccessEx) {
					chain.push_back(currentBase);
					currentBase = context.getArena().nodes[static_cast<const ArrayAccessExNode*>(currentBase)->targetIndex].get();
				}
				else {
					break;
				}
			}

			// We hit the bottom. Evaluate the root target.
			Result currentRes = currentBase->evaluate(context);

			// Walk back up, dynamically applying either standard or sliced accesses.
			for (auto it = chain.rbegin(); it != chain.rend(); ++it) {
				if (currentRes.type != NumericConstant::Object || !currentRes.value.objectVal) {
					return Result{};
				}

				if ((*it)->type() == NodeType::ArrayAccess) {
					const ArrayAccessNode* accNode = static_cast<const ArrayAccessNode*>(*it);
					Result indexRes = context.getArena().nodes[accNode->indexIndex]->evaluate(context);

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
				else if ((*it)->type() == NodeType::ArrayAccessEx) {
					const ArrayAccessExNode* sliceNode = static_cast<const ArrayAccessExNode*>(*it);
					
					if (currentRes.value.objectVal->type() & BuiltInType_Map) {
						return Result{};
					}

					int64_t startIdx = 0;
					int64_t endIdx = 0;

					if (sliceNode->flagsMask & ArrayExFlags::ArrayExFlag_Start) {
						Result sRes = context.getArena().nodes[sliceNode->startIndex]->evaluate(context);
						if (sRes.type == NumericConstant::Signed) {
							startIdx = sRes.value.intVal;
						}
						else if (sRes.type == NumericConstant::Unsigned) {
							startIdx = static_cast<int64_t>(sRes.value.uintVal);
						}
						else {
							return Result{};
						}
					}

					if (sliceNode->flagsMask & ArrayExFlags::ArrayExFlag_End) {
						Result eRes = context.getArena().nodes[sliceNode->endIndex]->evaluate(context);
						if (eRes.type == NumericConstant::Signed) {
							endIdx = eRes.value.intVal;
						}
						else if (eRes.type == NumericConstant::Unsigned) {
							endIdx = static_cast<int64_t>(eRes.value.uintVal);
						}
						else {
							return Result{};
						}
					}

					currentRes = currentRes.value.objectVal->arrayAccessEx(startIdx, endIdx, sliceNode->flagsMask);
					
					VE_DELETE_SWAP(currentRes, sliceNode->lastObject);
				}
			}

			return currentRes;
		}

		/**
		 * Gets the node type.
		 * 
		 * \return			Returns a NodeType enumeration indicating the type of the node.
		 **/
		virtual NodeType			type() const { return NodeType::ArrayAccessEx; }

	protected :
		// == Members.
		size_t						targetIndex;
		size_t						startIndex;
		size_t						endIndex;
		uint32_t					flagsMask;
		mutable Object*				lastObject = nullptr;
	};

}	// namespace ve
