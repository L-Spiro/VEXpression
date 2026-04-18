#pragma once

#include "../Engine/Result.h"

#include <cassert>
#include <cstdint>

namespace ve {

	class ExecutionContext;

	/**
	 * The pure virtual base class for all Abstract Syntax Tree nodes.
	 **/
	class AstNode {
	public :
		virtual ~AstNode() = default;
		
		
		// == Functions.
		/**
		 * Evaluates the current syntax tree node and computes its resulting value.
		 * 
		 * \param context	The master context holding runtime state and the node arena.
		 * \return			Returns the computed Result of the node.
		 **/
		virtual Result				evaluate(ExecutionContext& context) const = 0; 

	protected :

	private :
	};

}	// namespace ve
