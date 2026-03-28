#pragma once

#include "../Engine/Errors.h"
#include "AstNode.h"

#include <memory>
#include <new>
#include <utility>
#include <vector>

namespace ve {

	/**
	 * The central memory manager and storage for the Abstract Syntax Tree.
	 * Stores nodes in a flat vector to guarantee cache-friendly iteration and zero-leak cleanup.
	 **/
	class AstArena {
	public :
		// == Functions.
		/**
		 * Allocates a new AST node within the arena and returns its flat index.
		 * 
		 * \param args		The arguments to forward to the specified node's constructor.
		 * \return			Returns the size_t index of the newly created node within the arena.
		 * \throws			Throws ErrorCode::Out_Of_Memory if a standard library memory allocation fails.
		 **/
		template <typename T, typename... Args>
		size_t										addNode(Args&&... args) {
			try {
				nodes.push_back(std::make_unique<T>(std::forward<Args>(args)...));
				return nodes.size() - 1;
			}
			catch (const std::bad_alloc&) {
				throw ErrorCode::Out_Of_Memory;
			}
		}

		// == Members.
		/**
		 * A flat vector containing all allocated AST nodes. Memory is automatically
		 * freed when the arena is destroyed, preventing deeply nested recursive deallocation.
		 **/
		std::vector<std::unique_ptr<AstNode>>		nodes;

	protected :

	private :
	};

}	// namespace ve