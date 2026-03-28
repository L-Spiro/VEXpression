#pragma once

#include "../Ast/AstArena.h"
#include "Result.h"

#include <string>

namespace ve {

	/**
	 * The master engine object. It parses text, holds the AST arena, 
	 * manages the lifetime of allocated objects, and provides conversion utilities.
	 **/
	class ExecutionContext {
	public :
		ExecutionContext() : rootIndex(0) {}

		
		// == Functions.
		/**
		 * Compiles a string expression and populates the internal AST.
		 * 
		 * \param expression	The raw mathematical expression string.
		 * \param errorOut		Optional pointer to a string that will receive error details if compilation fails.
		 * \return				Returns true if compilation succeeded, false otherwise.
		 **/
		bool							compile(const std::string& expression, std::wstring* errorOut = nullptr);

		/**
		 * Evaluates the currently compiled AST. Can be called multiple times.
		 * 
		 * \return			Returns the evaluated Result.
		 **/
		Result							execute();

		/**
		 * Determines the promotion type between two given numeric types.
		 * 
		 * \param left		The left operand type.
		 * \param right			The right operand type.
		 * \return				Returns the common cast type based on C++ promotion rules.
		 **/
		static NumericConstant			getCastType(NumericConstant left, NumericConstant right);

		/**
		 * Converts a result or object to a specified numeric type.
		 * 
		 * \param res			The source result to convert.
		 * \param target		The target numeric constant type.
		 * \return				Returns a new Result converted to the target type.
		 **/
		Result							convertResult(const Result& res, NumericConstant target);
		
		/**
		 * Provides access to the AstArena where nodes are allocated.
		 * 
		 * \return				Returns a constant reference to the arena object.
		 **/
		const AstArena &				getArena() const { return arena; }

		/**
		 * Allocates a new AST node within the internal arena.
		 * 
		 * \param args		The arguments to forward to the specified node's constructor.
		 * \return				Returns the size_t index of the newly created node.
		 **/
		template <typename T, typename... Args>
		size_t							addNode(Args&&... args) {
			return arena.addNode<T>(std::forward<Args>(args)...);
		}

	protected :
		// == Members.
		/**
		 * The central storage arena containing all allocated AST nodes.
		 **/
		AstArena						arena;

		/**
		 * The arena index of the root AST node to execute.
		 **/
		size_t							rootIndex;

	private :
	};

}	// namespace ve
