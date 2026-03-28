#pragma once

#include "../../generated/ExprLexer.h"
#include "../../generated/ExprParserBaseVisitor.h"
#include "../Ast/AddNode.h"
#include "../Ast/AstArena.h"
#include "../Ast/ConstantNode.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"

#include <any>
#include <cstdint>
#include <string>

namespace ve {

	/**
	 * The compiler visitor that traverses the ANTLR parse tree and translates it 
	 * into a flat, index-based Abstract Syntax Tree within the provided execution context.
	 **/
	class AstBuilderVisitor : public ExprParserBaseVisitor {
	public :
		/**
		 * Constructs the visitor with a reference to the master execution context.
		 * 
		 * \param targetContext	The context where all compiled AST nodes will be allocated.
		 **/
		AstBuilderVisitor(ExecutionContext& targetContext) : context(targetContext) {}

		
		// == Functions.
		/**
		 * Visits the entry point of the grammar and returns the index of the root expression.
		 * 
		 * \param ctx		The ANTLR parser context for the program root.
		 * \return			Returns a std::any containing the size_t index of the root node.
		 **/
		std::any					visitProg(ExprParser::ProgContext* ctx) override {
			return visit(ctx->expr());
		}

		/**
		 * Visits a constant value node in the parse tree and allocates a ConstantNode.
		 * Evaluates the literal text to determine if it is Signed, Unsigned, or Floating.
		 * 
		 * \param ctx		The ANTLR parser context for the constant value.
		 * \return			Returns a std::any containing the size_t index of the allocated node.
		 **/
		std::any					visitConstValue(ExprParser::ConstValueContext* ctx) override {
			auto token = dynamic_cast<antlr4::tree::TerminalNode*>(ctx->constant()->children[0])->getSymbol();
			std::string text = token->getText();
			Result res;
			
			switch (token->getType()) {
				case ExprLexer::FLOAT_CONSTANT : {
					res.type = NumericConstant::Floating;
					res.value.doubleVal = std::stod(text);
					break;
				}
				case ExprLexer::HEX_CONSTANT : {
					res.type = NumericConstant::Unsigned;
					if (text.back() == 'h' || text.back() == 'H') {
						res.value.uintVal = std::stoull(text.substr(0, text.size() - 1), nullptr, 16);
					} else {
						res.value.uintVal = std::stoull(text, nullptr, 16);
					}
					break;
				}
				case ExprLexer::PUREDEC_CONSTANT : {
					res.type = NumericConstant::Unsigned;
					res.value.uintVal = std::stoull(text.substr(1), nullptr, 10);
					break;
				}
				case ExprLexer::BIN_CONSTANT : {
					res.type = NumericConstant::Unsigned;
					res.value.uintVal = std::stoull(text.substr(2), nullptr, 2);
					break;
				}
				case ExprLexer::OCT_CONSTANT : {
					res.type = NumericConstant::Unsigned;
					res.value.uintVal = std::stoull(text, nullptr, 8);
					break;
				}
				default : {
					res.type = NumericConstant::Signed;
					res.value.intVal = std::stoll(text, nullptr, 10);
					break;
				}
			}

			return context.addNode<ConstantNode>(res);
		}

		/**
		 * Visits an addition or subtraction node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the add/sub operation.
		 * \return			Returns a std::any containing the size_t index of the allocated node.
		 **/
		std::any					visitAddSub(ExprParser::AddSubContext* ctx) override {
			size_t leftIndex = std::any_cast<size_t>(visit(ctx->expr(0)));
			size_t rightIndex = std::any_cast<size_t>(visit(ctx->expr(1)));

			if (ctx->op->getType() == ExprLexer::ADD) {
				return context.addNode<AddNode>(leftIndex, rightIndex);
			}
			
			return static_cast<size_t>(0); 
		}

		/**
		 * Visits a parentheses node, simply passing the inner expression's index up the tree.
		 * 
		 * \param ctx		The ANTLR parser context for the parentheses.
		 * \return			Returns a std::any containing the size_t index of the inner evaluated node.
		 **/
		std::any					visitParens(ExprParser::ParensContext* ctx) override {
			return visit(ctx->expr());
		}

	protected :

	private :
		// == Members.
		/**
		 * A reference to the master context where the AST arena is managed.
		 **/
		ExecutionContext&			context;
	};

}	// namespace ve
