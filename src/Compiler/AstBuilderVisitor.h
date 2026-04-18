#pragma once

#include "../../generated/ExprLexer.h"
#include "../../generated/ExprParserBaseVisitor.h"
#include "../Ast/AddNode.h"
#include "../Ast/AssignNode.h"
#include "../Ast/AstArena.h"
#include "../Ast/BitAndNode.h"
#include "../Ast/BitNotNode.h"
#include "../Ast/BitOrNode.h"
#include "../Ast/BitXorNode.h"
#include "../Ast/ConstantNode.h"
#include "../Ast/DivNode.h"
#include "../Ast/EqNode.h"
#include "../Ast/GeNode.h"
#include "../Ast/GtNode.h"
#include "../Ast/LeNode.h"
#include "../Ast/LogAndNode.h"
#include "../Ast/LogNotNode.h"
#include "../Ast/LogOrNode.h"
#include "../Ast/LtNode.h"
#include "../Ast/ModNode.h"
#include "../Ast/MulNode.h"
#include "../Ast/NeNode.h"
#include "../Ast/PostDecNode.h"
#include "../Ast/PostIncNode.h"
#include "../Ast/PreDecNode.h"
#include "../Ast/PreIncNode.h"
#include "../Ast/SequenceNode.h"
#include "../Ast/ShlNode.h"
#include "../Ast/ShrNode.h"
#include "../Ast/SpaceshipNode.h"
#include "../Ast/SubNode.h"
#include "../Ast/TernaryNode.h"
#include "../Ast/UnaryMinusNode.h"
#include "../Ast/UnaryPlusNode.h"
#include "../Ast/VarNode.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "../Foundation/Character.h"
#include "../Foundation/Text.h"

#include <any>
#include <cstdint>
#include <map>
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
		 * Visits the entry point of the program and resolves the statement list.
		 * 
		 * \param ctx		The ANTLR parser context for the program root.
		 * \return			Returns a std::any containing the size_t index of the root SequenceNode.
		 **/
		virtual std::any			visitProg(ExprParser::ProgContext* ctx) override {
			return visit(ctx->statement_list());
		}

		/**
		 * Visits a list of statements that concludes with an unterminated expression.
		 * 
		 * \param ctx		The ANTLR parser context for the list.
		 * \return			Returns a std::any containing the size_t index of the SequenceNode.
		 **/
		virtual std::any			visitListWithExpr(ExprParser::ListWithExprContext* ctx) override {
			std::vector<size_t> compiledStatements;

			for (auto* stmtCtx : ctx->statement()) {
				std::any stmtResult = visit(stmtCtx);
				if (stmtResult.has_value()) {
					compiledStatements.push_back(std::any_cast<size_t>(stmtResult));
				}
			}

			std::any lastResult = visit(ctx->expr());
			if (lastResult.has_value()) {
				compiledStatements.push_back(std::any_cast<size_t>(lastResult));
			}

			return context.addNode<SequenceNode>(compiledStatements);
		}

		/**
		 * Visits a list of statements that are all explicitly terminated by semicolons.
		 * 
		 * \param ctx		The ANTLR parser context for the list.
		 * \return			Returns a std::any containing the size_t index of the SequenceNode.
		 **/
		virtual std::any			visitListStatements(ExprParser::ListStatementsContext* ctx) override {
			std::vector<size_t> compiledStatements;

			for (auto* stmtCtx : ctx->statement()) {
				std::any stmtResult = visit(stmtCtx);
				if (stmtResult.has_value()) {
					compiledStatements.push_back(std::any_cast<size_t>(stmtResult));
				}
			}

			return context.addNode<SequenceNode>(compiledStatements);
		}

		/**
		 * Visits a program consisting of a single, unterminated expression.
		 * 
		 * \param ctx		The ANTLR parser context for the list.
		 * \return			Returns a std::any containing the size_t index of the SequenceNode.
		 **/
		virtual std::any			visitListExpr(ExprParser::ListExprContext* ctx) override {
			std::vector<size_t> compiledStatements;

			std::any lastResult = visit(ctx->expr());
			if (lastResult.has_value()) {
				compiledStatements.push_back(std::any_cast<size_t>(lastResult));
			}

			return context.addNode<SequenceNode>(compiledStatements);
		}

		/**
		 * Visits an entirely empty program.
		 * 
		 * \param ctx		The ANTLR parser context for the list.
		 * \return			Returns a std::any containing the size_t index of the SequenceNode.
		 **/
		virtual std::any			visitListEmpty(ExprParser::ListEmptyContext* ctx) override {
			// Returns a SequenceNode with 0 statements to gracefully return 0 at runtime.
			return context.addNode<SequenceNode>(std::vector<size_t>{});
		}

		/**
		 * Visits a standard expression statement.
		 * 
		 * \param ctx		The ANTLR parser context for the expression statement.
		 * \return			Returns a std::any containing the size_t index of the compiled expression.
		 **/
		virtual std::any			visitExprStmt(ExprParser::ExprStmtContext* ctx) override {
			return visit(ctx->expr());
		}

		/**
		 * Visits an empty statement (a lone semicolon) and discards it.
		 * 
		 * \param ctx		The ANTLR parser context for the empty statement.
		 * \return			Returns an empty std::any.
		 **/
		virtual std::any			visitEmptyStmt(ExprParser::EmptyStmtContext* ctx) override {
			return std::any(); 
		}

		/**
		 * Visits a postfix increment or decrement node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the postfix operation.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitPostfix(ExprParser::PostfixContext* ctx) override {
			std::string varName = ctx->IDENTIFIER()->getText();
			size_t varId = getOrCreateVariable(varName);

			if (ctx->op->getType() == ExprLexer::INC) {
				return context.addNode<PostIncNode>(varId);
			}
			else if (ctx->op->getType() == ExprLexer::DEC) {
				return context.addNode<PostDecNode>(varId);
			}
			
			return static_cast<size_t>(0);
		}

		/**
		 * Visits a prefix increment or decrement node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the prefix increment/decrement operation.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitPrefixIncDec(ExprParser::PrefixIncDecContext* ctx) override {
			std::string varName = ctx->IDENTIFIER()->getText();
			size_t varId = getOrCreateVariable(varName);

			if (ctx->op->getType() == ExprLexer::INC) {
				return context.addNode<PreIncNode>(varId);
			}
			else if (ctx->op->getType() == ExprLexer::DEC) {
				return context.addNode<PreDecNode>(varId);
			}
			
			return static_cast<size_t>(0);
		}

		/**
		 * Visits a constant value node in the parse tree.
		 * Because the grammar was broken down into specific rules, this function now simply delegates
		 * the execution to the appropriate sub-visitor, which will parse the text and allocate the ConstantNode.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The ANTLR parser context for the constant value.
		 * \return			Returns an std::any containing the allocated node reference/index.
		 **/
		virtual std::any			visitConstValue(ExprParser::ConstValueContext* ctx) override {
			return visitChildren(ctx);
		}

		/**
		 * Visits a unary prefix node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the unary operation.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitUnary(ExprParser::UnaryContext* ctx) override {
			size_t childIndex = std::any_cast<size_t>(visit(ctx->expr()));

			if (ctx->op->getType() == ExprLexer::ADD) {
				return context.addNode<UnaryPlusNode>(childIndex);
			}
			else if (ctx->op->getType() == ExprLexer::SUB) {
				return context.addNode<UnaryMinusNode>(childIndex);
			}
			else if (ctx->op->getType() == ExprLexer::BIT_NOT) {
				return context.addNode<BitNotNode>(childIndex);
			}
			else if (ctx->op->getType() == ExprLexer::LOG_NOT) {
				return context.addNode<LogNotNode>(childIndex);
			}
			
			return static_cast<size_t>(0);
		}

		/**
		 * Visits a multiplication or division node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the mul/div operation.
		 * \return			Returns a std::any containing the size_t index of the allocated node.
		 **/
		std::any					visitMulDiv(ExprParser::MulDivContext* ctx) override {
			size_t leftIndex = std::any_cast<size_t>(visit(ctx->expr(0)));
			size_t rightIndex = std::any_cast<size_t>(visit(ctx->expr(1)));

			if (ctx->op->getType() == ExprLexer::MUL) {
				return context.addNode<MulNode>(leftIndex, rightIndex);
			}
			else if (ctx->op->getType() == ExprLexer::DIV) {
				return context.addNode<DivNode>(leftIndex, rightIndex);
			}
			else if (ctx->op->getType() == ExprLexer::MOD) {
				return context.addNode<ModNode>(leftIndex, rightIndex);
			}
			
			return static_cast<size_t>(0); 
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
			else if (ctx->op->getType() == ExprLexer::SUB) {
				return context.addNode<SubNode>(leftIndex, rightIndex);
			}
			
			return static_cast<size_t>(0); 
		}

		/**
		 * Visits a bitwise shift node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the bit shift operation.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitBitShift(ExprParser::BitShiftContext* ctx) override {
			size_t leftIndex = std::any_cast<size_t>(visit(ctx->expr(0)));
			size_t rightIndex = std::any_cast<size_t>(visit(ctx->expr(1)));

			if (ctx->op->getType() == ExprLexer::SHL) {
				return context.addNode<ShlNode>(leftIndex, rightIndex);
			}
			else if (ctx->op->getType() == ExprLexer::SHR) {
				return context.addNode<ShrNode>(leftIndex, rightIndex);
			}
			
			return static_cast<size_t>(0);
		}

		/**
		 * Visits a spaceship (three-way comparison) node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the spaceship operation.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitSpaceship(ExprParser::SpaceshipContext* ctx) override {
			size_t leftIndex = std::any_cast<size_t>(visit(ctx->expr(0)));
			size_t rightIndex = std::any_cast<size_t>(visit(ctx->expr(1)));

			return context.addNode<SpaceshipNode>(leftIndex, rightIndex);
		}

		/**
		 * Visits a relational comparison node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the relational operation.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitRelational(ExprParser::RelationalContext* ctx) override {
			size_t leftIndex = std::any_cast<size_t>(visit(ctx->expr(0)));
			size_t rightIndex = std::any_cast<size_t>(visit(ctx->expr(1)));

			if (ctx->op->getType() == ExprLexer::LT) {
				return context.addNode<LtNode>(leftIndex, rightIndex);
			}
			else if (ctx->op->getType() == ExprLexer::LE) {
				return context.addNode<LeNode>(leftIndex, rightIndex);
			}
			else if (ctx->op->getType() == ExprLexer::GT) {
				return context.addNode<GtNode>(leftIndex, rightIndex);
			}
			else if (ctx->op->getType() == ExprLexer::GE) {
				return context.addNode<GeNode>(leftIndex, rightIndex);
			}
			
			return static_cast<size_t>(0);
		}

		/**
		 * Visits an equality comparison node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the equality operation.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitEquality(ExprParser::EqualityContext* ctx) override {
			size_t leftIndex = std::any_cast<size_t>(visit(ctx->expr(0)));
			size_t rightIndex = std::any_cast<size_t>(visit(ctx->expr(1)));

			if (ctx->op->getType() == ExprLexer::EQ) {
				return context.addNode<EqNode>(leftIndex, rightIndex);
			}
			else if (ctx->op->getType() == ExprLexer::NE) {
				return context.addNode<NeNode>(leftIndex, rightIndex);
			}
			
			return static_cast<size_t>(0);
		}

		/**
		 * Visits a bitwise AND node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the bitwise AND operation.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitBitAnd(ExprParser::BitAndContext* ctx) override {
			size_t leftIndex = std::any_cast<size_t>(visit(ctx->expr(0)));
			size_t rightIndex = std::any_cast<size_t>(visit(ctx->expr(1)));

			return context.addNode<BitAndNode>(leftIndex, rightIndex);
		}

		/**
		 * Visits a bitwise XOR node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the bitwise XOR operation.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitBitXor(ExprParser::BitXorContext* ctx) override {
			size_t leftIndex = std::any_cast<size_t>(visit(ctx->expr(0)));
			size_t rightIndex = std::any_cast<size_t>(visit(ctx->expr(1)));

			return context.addNode<BitXorNode>(leftIndex, rightIndex);
		}

		/**
		 * Visits a bitwise OR node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the bitwise OR operation.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitBitOr(ExprParser::BitOrContext* ctx) override {
			size_t leftIndex = std::any_cast<size_t>(visit(ctx->expr(0)));
			size_t rightIndex = std::any_cast<size_t>(visit(ctx->expr(1)));

			return context.addNode<BitOrNode>(leftIndex, rightIndex);
		}

		/**
		 * Visits a logical AND node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the logical AND operation.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitLogAnd(ExprParser::LogAndContext* ctx) override {
			size_t leftIndex = std::any_cast<size_t>(visit(ctx->expr(0)));
			size_t rightIndex = std::any_cast<size_t>(visit(ctx->expr(1)));

			return context.addNode<LogAndNode>(leftIndex, rightIndex);
		}

		/**
		 * Visits a logical OR node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the logical OR operation.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitLogOr(ExprParser::LogOrContext* ctx) override {
			size_t leftIndex = std::any_cast<size_t>(visit(ctx->expr(0)));
			size_t rightIndex = std::any_cast<size_t>(visit(ctx->expr(1)));

			return context.addNode<LogOrNode>(leftIndex, rightIndex);
		}

		/**
		 * Visits a ternary conditional node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the ternary operation.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitTernary(ExprParser::TernaryContext* ctx) override {
			size_t condIndex = std::any_cast<size_t>(visit(ctx->expr(0)));
			size_t trueIndex = std::any_cast<size_t>(visit(ctx->expr(1)));
			size_t falseIndex = std::any_cast<size_t>(visit(ctx->expr(2)));

			return context.addNode<TernaryNode>(condIndex, trueIndex, falseIndex);
		}

		/**
		 * Visits an assignment node in the parse tree and allocates the AssignNode.
		 * 
		 * \param ctx		The ANTLR parser context for the assignment operation.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitAssignment(ExprParser::AssignmentContext* ctx) override {
			std::string varName = ctx->IDENTIFIER()->getText();
			size_t varId = getOrCreateVariable(varName);
			
			size_t exprIndex = std::any_cast<size_t>(visit(ctx->expr()));

			return context.addNode<AssignNode>(varId, exprIndex);
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

		/**
		 * Visits an identifier node in the parse tree and allocates the VarNode for reading.
		 * 
		 * \param ctx		The ANTLR parser context for the identifier.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitIdentifier(ExprParser::IdentifierContext* ctx) override {
			std::string varName = ctx->IDENTIFIER()->getText();
			size_t varId = getOrCreateVariable(varName);

			return context.addNode<VarNode>(varId);
		}


		// =========================================================================
		// Constant Node Visitors
		// =========================================================================
		/**
		 * Visits a pure decimal constant node in the AST, evaluates its numeric value, and adds it to the context.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The parser context containing the pure decimal token.
		 * \return			Returns an std::any containing the allocated node reference/index.
		 **/
		virtual std::any			visitPuredec_constant(ExprParser::Puredec_constantContext* ctx) override {
			std::string text = ctx->getText();
			Result res;
			bool overflow = false;
			
			res.value.uintVal = Text::stoull(text.c_str() + 1, 10, nullptr, ~0ULL, &overflow);
			
			if (overflow) {
				res.type = NumericConstant::Floating;
				res.value.doubleVal = Text::atof(text.c_str() + 1);
			}
			else {
				res.type = Text::classifyString(text);
			}
			
			return context.addNode<ConstantNode>(res);
		}

		/**
		 * Visits a binary constant node in the AST, evaluates its numeric value, and adds it to the context.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The parser context containing the binary token.
		 * \return			Returns an std::any containing the allocated node reference/index.
		 **/
		virtual std::any			visitBin_constant(ExprParser::Bin_constantContext* ctx) override {
			std::string text = ctx->getText();
			Result res;

			res.value.uintVal = Text::stoull(text.c_str(), 2);
			res.type = Text::classifyString(text);
			
			return context.addNode<ConstantNode>(res);
		}

		/**
		 * Visits an octal constant node in the AST, evaluates its numeric value, and adds it to the context.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The parser context containing the octal token.
		 * \return			Returns an std::any containing the allocated node reference/index.
		 **/
		virtual std::any			visitOct_constant(ExprParser::Oct_constantContext* ctx) override {
			std::string text = ctx->getText();
			Result res;

			res.value.uintVal = Text::stoull(text.c_str(), 8);
			res.type = Text::classifyString(text);
			
			return context.addNode<ConstantNode>(res);
		}

		/**
		 * Visits a hexadecimal constant node in the AST, evaluates its numeric value, and adds it to the context.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The parser context containing the hexadecimal token.
		 * \return			Returns an std::any containing the allocated node reference/index.
		 **/
		virtual std::any			visitHex_constant(ExprParser::Hex_constantContext* ctx) override {
			std::string text = ctx->getText();
			Result res;

			res.value.uintVal = Text::stoull(text.c_str(), 16);
			res.type = Text::classifyString(text);
			
			return context.addNode<ConstantNode>(res);
		}

		/**
		 * Visits a decimal constant node in the AST, evaluates its numeric value, and adds it to the context.
		 * Routes to hexadecimal parsing if the system is configured to treat all inputs as hex.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The parser context containing the decimal token.
		 * \return			Returns an std::any containing the allocated node reference/index.
		 **/
		virtual std::any			visitDec_constant(ExprParser::Dec_constantContext* ctx) override {
			std::string text = ctx->getText();
			Result res;

			if (context.getTreatAllAsHex()) {
				res.value.uintVal = Text::stoull(text.c_str(), 16);
				res.type = Text::classifyString(text);
			}
			else {
				bool overflow = false;
				res.value.uintVal = Text::stoull(text.c_str(), 10, nullptr, ~0ULL, &overflow);
				
				if (overflow) {
					res.type = NumericConstant::Floating;
					res.value.doubleVal = Text::atof(text.c_str());
				}
				else {
					res.type = Text::classifyString(text);
				}
			}
			
			return context.addNode<ConstantNode>(res);
		}

		/**
		 * Visits a floating-point constant node in the AST, evaluates its numeric value, and adds it to the context.
		 * Routes to hexadecimal parsing if the system configuration overrides float evaluation.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The parser context containing the floating-point token.
		 * \return			Returns an std::any containing the allocated node reference/index.
		 **/
		virtual std::any			visitFloat_constant(ExprParser::Float_constantContext* ctx) override {
			std::string text = ctx->getText();
			Result res;

			auto isEntirelyHex = [](const std::string& str) {
				for (char c : str) {
					if (!Character::validHex(c)) { return false; }
				}
				return true;
			};

			if (context.getTreatAllAsHex() && isEntirelyHex(text)) {
				res.value.uintVal = Text::stoull(text.c_str(), 16);
				res.type = NumericConstant::Unsigned;
			}
			else {
				res.value.doubleVal = Text::atof(text.c_str());
				res.type = NumericConstant::Floating;
			}
			
			return context.addNode<ConstantNode>(res);
		}

	protected :

	private :
		// == Members.
		/**
		 * A reference to the master context where the AST arena is managed.
		 **/
		ExecutionContext&			context;
		/**
		 * Maps variable string names to their corresponding indices in the runtime ExecutionContext.
		 * Used exclusively during the compilation phase to resolve identifiers to fast array offsets.
		 **/
		std::map<std::string, size_t> 
									variableMap;


		// == Functions.
		/**
		 * Checks if a variable name exists in the compiler's map.
		 * If it does, returns its ID. If not, allocates a new slot in the runtime context and maps it.
		 *
		 * \param name		The string identifier of the variable to look up or create.
		 * \return			Returns the runtime index (ID) of the variable.
		 **/
		size_t						getOrCreateVariable(const std::string& name) {
			auto it = variableMap.find(name);
			if (it != variableMap.end()) {
				return it->second;
			}
			
			size_t newId = context.allocateVariable();
			variableMap[name] = newId;
			return newId;
		}
	};

}	// namespace ve
