#pragma once

#include "../Engine/Result.h"

#include <cstdint>

namespace ve {

	class							ExecutionContext;

	// == Enumerations.
	/**
	 * Defines the concrete type of an AstNode to enable fast, RTTI-free 
	 * downcasting during iterative execution and tree unrolling.
	 **/
	enum class NodeType : uint8_t {
		Add,
		AddAssign,
		ArrayAccess,
		ArrayAccessEx,
		ArrayAssign,
		ArrayExAssign,
		Assign,
		BitAnd,
		BitAndAssign,
		BitNot,
		BitOr,
		BitOrAssign,
		BitXor,
		BitXorAssign,
		Break,
		Cast,
		Constant,
		ConstructPrimitive,
		ConstructSimd,
		Continue,
		Div,
		DivAssign,
		DoWhile,
		Eq,
		FlatVector,
		For,
		ForRange,
		FunctionCall,
		Ge,
		Gt,
		If,
		Le,
		LogAnd,
		LogNot,
		LogOr,
		Lt,
		Map,
		MethodCall,
		Mod,
		ModAssign,
		Mul,
		MulAssign,
		Ne,
		ParamAccess,
		PostDec,
		PostInc,
		PreDec,
		PreInc,
		Return,
		Scope,
		Sequence,
		Shl,
		ShlAssign,
		Shr,
		ShrAssign,
		Spaceship,
		Sub,
		SubAssign,
		Ternary,
		TotalParms,
		UnaryMinus,
		UnaryPlus,
		UserValue,
		Var,
		Vector
	};

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

		/**
		 * Gets the node type.
		 * 
		 * \return			Returns a NodeType enumeration indicating the type of the node.
		 **/
		virtual NodeType			type() const = 0;

	protected :

	private :
	};

}	// namespace ve
