#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Map.h"
#include "../Engine/Result.h"
#include "AstNode.h"

#include <utility>
#include <vector>

namespace ve {

	/**
	 * Represents a map initialization block (e.g., { key: value, ... }).
	 **/
	class MapNode : public AstNode {
	public :
		/**
		 * Constructs a MapNode.
		 *
		 * \param pairs		A vector of expression index pairs representing keys and values.
		 **/
		MapNode(const std::vector<std::pair<size_t, size_t>>& pairs) : elements(pairs) {}

		/**
		 * Evaluates the map literal, instantiating a Map object and populating it with the evaluated key-value pairs.
		 *
		 * \param context	The runtime execution context.
		 * \return			Returns a Result containing the new Map object, or Invalid if allocation or evaluation fails.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			Map* resMap = context.allocateObject<Map>();
			if (!resMap) {
				return Result{};
			}

			for (size_t i = 0; i < elements.size(); ++i) {
				Result keyRes = context.getArena().nodes[elements[i].first]->evaluate(context);
				Result valRes = context.getArena().nodes[elements[i].second]->evaluate(context);

				if (keyRes.type == NumericConstant::Invalid || valRes.type == NumericConstant::Invalid) {
					context.deallocateObject(resMap);
					return Result{};
				}

				resMap->insert(keyRes, valRes);
			}

			return resMap->createResult();
		}

	private :
		std::vector<std::pair<size_t, size_t>> elements;
	};

}	// namespace ve
