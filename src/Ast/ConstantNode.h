#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "AstNode.h"

namespace ve {

	/**
	 * Represents a parsed, hardcoded numeric value in the AST.
	 **/
	class ConstantNode : public AstNode {
	public :
		/**
		 * Constructs a ConstantNode with a specific parsed Result.
		 * 
		 * \param res		The parsed numeric result value.
		 **/
		ConstantNode(const Result& res) : value(res) {
			volatile int hghg  =0;
		}
		
		
		// == Functions.
		/**
		 * Evaluates the current syntax tree node and computes its resulting value.
		 * 
		 * \param context	The master context holding runtime state and the node arena.
		 * \return			Returns the hardcoded Result value.
		 **/
		Result						evaluate(ExecutionContext& context) const override {
			return value; 
		}

	protected :

	private :
		// == Members.
		/**
		 * The baked-in numeric value assigned during the compilation phase.
		 **/
		Result						value;
	};

}	// namespace ve
