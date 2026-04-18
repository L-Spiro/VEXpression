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
		ExecutionContext() {}

		
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
		 * \return				Returns the evaluated Result.
		 **/
		Result							execute();

		/**
		 * Determines the promotion type between two given numeric types.
		 * 
		 * \param left			The left operand type.
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
		 * Determines whether to treat all standard integers as hexadecimal or not.
		 * 
		 * \return				Returns true if unqualified integer constants should be parsed as hexadecimal.
		 **/
		inline bool						getTreatAllAsHex() const { return treatAllAsHex; }

		/**
		 * Sets whether to treat all unqualified standard integer strings as hexadecimal constants.
		 * 
		 * \param treatAsHex	If true, standard integer strings (333, 129, 88959, etc.) are parsed as hexadecimal integers.
		 **/
		inline void						setTreatAllAsHex(bool treatAsHex) { treatAllAsHex = treatAsHex; }

		/**
		 * Allocates a new AST node within the internal arena.
		 * 
		 * \param args			The arguments to forward to the specified node's constructor.
		 * \return				Returns the size_t index of the newly created node.
		 **/
		template <typename T, typename... Args>
		size_t							addNode(Args&&... args) {
			return arena.addNode<T>(std::forward<Args>(args)...);
		}

		/**
		 * Allocates a new variable slot and returns its runtime index.
		 **/
		size_t							allocateVariable() {
			variables.push_back(Result{}); // Pushes a default 0/Unsigned Result
			return variables.size() - 1;
		}

		/**
		 * Retrieves a reference to a variable by its runtime index.
		 **/
		inline Result&					getVariable(size_t index) {
			return variables[index];
		}

	protected :
		// == Members.
		/** The central storage arena containing all allocated AST nodes. **/
		AstArena						arena;
		/** The array of registered variables. */
		std::vector<Result>				variables;
		/** The arena index of the root AST node to execute. **/
		size_t							rootIndex = 0;
		/** Treat standard integers as hex? */
		bool							treatAllAsHex = false;


	private :
	};

}	// namespace ve
