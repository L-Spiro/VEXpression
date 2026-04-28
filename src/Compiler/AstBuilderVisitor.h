#pragma once

#include "../../generated/ExprLexer.h"
#include "../../generated/ExprParserBaseVisitor.h"
#include "../Ast/AddAssignNode.h"
#include "../Ast/AddNode.h"
#include "../Ast/ArrayAccessNode.h"
#include "../Ast/ArrayAccessExNode.h"
#include "../Ast/ArrayAssignNode.h"
#include "../Ast/ArrayExAssignNode.h"
#include "../Ast/AssignNode.h"
#include "../Ast/AstArena.h"
#include "../Ast/BitAndAssignNode.h"
#include "../Ast/BitAndNode.h"
#include "../Ast/BitNotNode.h"
#include "../Ast/BitOrAssignNode.h"
#include "../Ast/BitOrNode.h"
#include "../Ast/BitXorAssignNode.h"
#include "../Ast/BitXorNode.h"
#include "../Ast/BreakNode.h"
#include "../Ast/CastNode.h"
#include "../Ast/ConstantNode.h"
#include "../Ast/ContinueNode.h"
#include "../Ast/DivAssignNode.h"
#include "../Ast/DivNode.h"
#include "../Ast/EqNode.h"
#include "../Ast/ForNode.h"
#include "../Ast/ForRangeNode.h"
#include "../Ast/FunctionCallNode.h"
#include "../Ast/GeNode.h"
#include "../Ast/GtNode.h"
#include "../Ast/IfNode.h"
#include "../Ast/LeNode.h"
#include "../Ast/LogAndNode.h"
#include "../Ast/LogNotNode.h"
#include "../Ast/LogOrNode.h"
#include "../Ast/LtNode.h"
#include "../Ast/MapNode.h"
#include "../Ast/MethodCallNode.h"
#include "../Ast/ModAssignNode.h"
#include "../Ast/ModNode.h"
#include "../Ast/MulAssignNode.h"
#include "../Ast/MulNode.h"
#include "../Ast/NeNode.h"
#include "../Ast/ParamAccessNode.h"
#include "../Ast/PostDecNode.h"
#include "../Ast/PostIncNode.h"
#include "../Ast/PreDecNode.h"
#include "../Ast/PreIncNode.h"
#include "../Ast/ReturnNode.h"
#include "../Ast/SequenceNode.h"
#include "../Ast/ShlAssignNode.h"
#include "../Ast/ShlNode.h"
#include "../Ast/ShrAssignNode.h"
#include "../Ast/ShrNode.h"
#include "../Ast/SpaceshipNode.h"
#include "../Ast/SubAssignNode.h"
#include "../Ast/SubNode.h"
#include "../Ast/TernaryNode.h"
#include "../Ast/TotalParmsNode.h"
#include "../Ast/UnaryMinusNode.h"
#include "../Ast/UnaryPlusNode.h"
#include "../Ast/UserValueNode.h"
#include "../Ast/VarNode.h"
#include "../Ast/VectorNode.h"
#include "../Engine/ExecutionContext.h"
#include "../Engine/FunctionDef.h"
#include "../Engine/Map.h"
#include "../Engine/Result.h"
#include "../Engine/String.h"
#include "../Engine/Vector.h"
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
		 * Visits an if/else expression, extracting the condition and block contents.
		 * Empty blocks are safely detected and skipped, enforcing fallback logic.
		 *
		 * \param ctx		The parser context containing the if/else expression.
		 * \return			Returns an std::any containing the allocated AstNode index.
		 **/
		virtual std::any			visitIfElseStmt(ExprParser::IfElseStmtContext* ctx) override {
			size_t condNode = std::any_cast<size_t>(visit(ctx->expr()));
			
			size_t trueBlockNode = static_cast<size_t>(-1);
			if (ctx->block(0)) {
				// Structurally verify the block actually contains statements
				if (!dynamic_cast<ExprParser::ListEmptyContext*>(ctx->block(0)->statement_list())) {
					trueBlockNode = std::any_cast<size_t>(visit(ctx->block(0)));
				}
			}
			
			size_t falseBlockNode = static_cast<size_t>(-1);
			if (ctx->ELSE()) {
				if (ctx->block(1)) {
					// Structurally verify the block actually contains statements
					if (!dynamic_cast<ExprParser::ListEmptyContext*>(ctx->block(1)->statement_list())) {
						falseBlockNode = std::any_cast<size_t>(visit(ctx->block(1)));
					}
				}
			}
			
			return context.addNode<IfNode>(condNode, trueBlockNode, falseBlockNode);
		}

		/**
		 * Visits a standard for loop, parsing optional initialization, condition, and step expressions.
		 *
		 * \param ctx		The parser context containing the standard for loop.
		 * \return			Returns an std::any containing the allocated AstNode index.
		 **/
		virtual std::any			visitForStandardStmt(ExprParser::ForStandardStmtContext* ctx) override {
			size_t initNode = static_cast<size_t>(-1);
			if (ctx->init) {
				initNode = std::any_cast<size_t>(visit(ctx->init));
			}
			
			size_t condNode = static_cast<size_t>(-1);
			if (ctx->cond) {
				condNode = std::any_cast<size_t>(visit(ctx->cond));
			}
			
			size_t stepNode = static_cast<size_t>(-1);
			if (ctx->step) {
				stepNode = std::any_cast<size_t>(visit(ctx->step));
			}
			
			size_t blockNode = static_cast<size_t>(-1);
			if (ctx->block()) {
				if (!dynamic_cast<ExprParser::ListEmptyContext*>(ctx->block()->statement_list())) {
					blockNode = std::any_cast<size_t>(visit(ctx->block()));
				}
			}
			
			return context.addNode<ForNode>(initNode, condNode, stepNode, blockNode);
		}

		/**
		 * Visits a ranged for loop, parsing the identifier and the target range object.
		 *
		 * \param ctx		The parser context containing the ranged for loop.
		 * \return			Returns an std::any containing the allocated AstNode index.
		 **/
		virtual std::any			visitForRangeStmt(ExprParser::ForRangeStmtContext* ctx) override {
			std::string varName = ctx->IDENTIFIER()->getText();
			
			// Resolve the string to a numeric index using your compiler's existing symbol table logic.
			size_t varIdx = getOrCreateVariable(varName); 
			
			size_t objNode = std::any_cast<size_t>(visit(ctx->expr()));
			
			size_t blockNode = static_cast<size_t>(-1);
			if (ctx->block()) {
				if (!dynamic_cast<ExprParser::ListEmptyContext*>(ctx->block()->statement_list())) {
					blockNode = std::any_cast<size_t>(visit(ctx->block()));
				}
			}
			
			return context.addNode<ForRangeNode>(varIdx, objNode, blockNode);
		}

		/**
		 * Visits a C++ style ranged for loop (for (var : obj)), parsing the identifier and target range object.
		 *
		 * \param ctx		The parser context containing the C++ style ranged for loop.
		 * \return			Returns an std::any containing the allocated AstNode index.
		 **/
		virtual std::any			visitForCppRangeStmt(ExprParser::ForCppRangeStmtContext* ctx) override {
			std::string varName = ctx->IDENTIFIER()->getText();
			
			// Resolve the string to a numeric index using your compiler's existing symbol table logic.
			size_t varIdx = getOrCreateVariable(varName); 
			
			size_t objNode = std::any_cast<size_t>(visit(ctx->expr()));
			
			size_t blockNode = static_cast<size_t>(-1);
			if (ctx->block()) {
				if (!dynamic_cast<ExprParser::ListEmptyContext*>(ctx->block()->statement_list())) {
					blockNode = std::any_cast<size_t>(visit(ctx->block()));
				}
			}
			
			return context.addNode<ForRangeNode>(varIdx, objNode, blockNode);
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
		 * \throws			ErrorCode::Invalid_LValue if the target is a constant or an undeclared variable.
		 * \throws			ErrorCode::Unknown_Operator if the operator is not recognized.
		 **/
		virtual std::any			visitPostfix(ExprParser::PostfixContext* ctx) override {
			std::string varName = ctx->IDENTIFIER()->getText();
			size_t varId = getVariable(varName);
			if (size_t(-1) != varId) {
				if (ctx->op->getType() == ExprLexer::INC) {
					return context.addNode<PostIncNode>(varId);
				}
				else if (ctx->op->getType() == ExprLexer::DEC) {
					return context.addNode<PostDecNode>(varId);
				}
				throw ErrorCode::Unknown_Operator;
			}
			
			throw ErrorCode::Invalid_LValue;
		}

		/**
		 * Visits a prefix increment or decrement node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the prefix increment/decrement operation.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 * \throws			ErrorCode::Invalid_LValue if the target is a constant or an undeclared variable.
		 * \throws			ErrorCode::Unknown_Operator if the operator is not recognized.
		 **/
		virtual std::any			visitPrefixIncDec(ExprParser::PrefixIncDecContext* ctx) override {
			std::string varName = ctx->IDENTIFIER()->getText();
			size_t varId = getVariable(varName);
			if (size_t(-1) != varId) {
				if (ctx->op->getType() == ExprLexer::INC) {
					return context.addNode<PreIncNode>(varId);
				}
				else if (ctx->op->getType() == ExprLexer::DEC) {
					return context.addNode<PreDecNode>(varId);
				}
				throw ErrorCode::Unknown_Operator;
			}
			
			throw ErrorCode::Invalid_LValue;
		}

		/**
		 * Compiles a method call AST node.
		 * Evaluates the target expression, extracts the method identifier, evaluates the arguments, 
		 * and allocates a MethodCallNode in the runtime arena.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx	The ANTLR parser context for the method call.
		 * \return		Returns an std::any containing the allocated node index (size_t).
		 **/
		virtual std::any			visitMethodCall(ExprParser::MethodCallContext* ctx) override {
			size_t targetNode = std::any_cast<size_t>(visit(ctx->expr()));
			std::string methodName = ctx->IDENTIFIER()->getText();
			
			std::vector<size_t> args;
			
			if (ctx->exprList()) {
				for (auto* argCtx : ctx->exprList()->expr()) {
					args.push_back(std::any_cast<size_t>(visit(argCtx)));
				}
			}

			return context.addNode<MethodCallNode>(targetNode, methodName, args);
		}

		/**
		 * Visits a comma-separated list of expressions and compiles each one into the arena.
		 * 
		 * \param ctx		The ANTLR parser context for the expression list.
		 * \return			Returns an std::any containing a std::vector<size_t> of allocated node indices.
		 **/
		virtual std::any			visitExprList(ExprParser::ExprListContext* ctx) override {
			std::vector<size_t> args;
			
			for (auto* exprCtx : ctx->expr()) {
				args.push_back(std::any_cast<size_t>(visit(exprCtx)));
			}
			
			return args;
		}

		/**
		 * Visits a function call node in the parse tree and allocates the FunctionCallNode.
		 * Resolves the function name at compile-time and verifies argument counts.
		 * 
		 * \param ctx		The ANTLR parser context for the function call.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 * \throws			ErrorCode::Invalid_Function_Target if the target expression is not an identifier.
		 * \throws			ErrorCode::Unknown_Function if the function is not registered.
		 * \throws			ErrorCode::Invalid_Argument_Count if arity does not match the definition.
		 **/
		virtual std::any			visitFunctionCall(ExprParser::FunctionCallContext* ctx) override {
			auto* idCtx = dynamic_cast<ExprParser::IdentifierContext*>(ctx->expr());
			if (!idCtx) {
				throw ErrorCode::Invalid_Function_Target;
			}

			std::string funcName = idCtx->IDENTIFIER()->getText();

			std::vector<size_t> args;
			if (ctx->exprList()) {
				args = std::any_cast<std::vector<size_t>>(visit(ctx->exprList()));
			}

			FunctionDef funcDef;
			if (!context.getFunction(funcName, args.size(), funcDef)) {
				if (context.isFunction(funcName)) {
					throw ErrorCode::Invalid_Argument_Count;
				}
				throw ErrorCode::Unknown_Function;
			}

			return context.addNode<FunctionCallNode>(funcDef, args);
		}

		/**
		 * Visits a standard array access expression.
		 *
		 * \param ctx		The parser context for the expression.
		 * \return			Returns an AST node representing the access operation.
		 **/
		virtual std::any			visitArrayAccess(ExprParser::ArrayAccessContext* ctx) override {
			size_t targetIndex = std::any_cast<size_t>(visit(ctx->expr(0)));
			size_t argIndex = std::any_cast<size_t>(visit(ctx->expr(1)));
			
			return context.addNode<ArrayAccessNode>(targetIndex, argIndex);
		}

		/**
		 * Visits an extended (sliced) array access expression.
		 *
		 * \param ctx		The parser context for the expression.
		 * \return			Returns an AST node representing the slice operation.
		 **/
		virtual std::any			visitArrayAccessEx(ExprParser::ArrayAccessExContext* ctx) override {
			size_t targetIndex = std::any_cast<size_t>(visit(ctx->expr(0)));
			size_t startIndex = static_cast<size_t>(-1);
			size_t endIndex = static_cast<size_t>(-1);
			uint32_t mask = 0;

			if (ctx->start) {
				startIndex = std::any_cast<size_t>(visit(ctx->start));
				mask |= ArrayExFlags::ArrayExFlag_Start;
			}
			if (ctx->end) {
				endIndex = std::any_cast<size_t>(visit(ctx->end));
				mask |= ArrayExFlags::ArrayExFlag_End;
			}

			return context.addNode<ArrayAccessExNode>(targetIndex, startIndex, endIndex, mask);
		}

		/**
		 * Visits a parameter access expression node ('$expr') in the AST, evaluates the index expression, and allocates a ParamAccessNode.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The parser context containing the parameter access expression.
		 * \return			Returns an std::any containing the allocated node reference/index.
		 **/
		virtual std::any			visitParamAccessExpr(ExprParser::ParamAccessExprContext* ctx) override {
			// Evaluate the inner expression representing the desired parameter index
			size_t exprNode = std::any_cast<size_t>(visit(ctx->expr()));
			
			// Allocate a ParamAccessNode in the execution context arena
			return context.addNode<ParamAccessNode>(exprNode);
		}
		
		/**
		 * Visits a break expression.
		 *
		 * \param ctx		The parser context for the expression.
		 * \return			Returns an AST node representing the break operation.
		 **/
		virtual std::any			visitBreakExpr(ExprParser::BreakExprContext* ctx) override {
			return context.addNode<BreakNode>();
		}

		/**
		 * Visits a continue expression.
		 *
		 * \param ctx		The parser context for the expression.
		 * \return			Returns an AST node representing the continue operation.
		 **/
		virtual std::any			visitContinueExpr(ExprParser::ContinueExprContext* ctx) override {
			return context.addNode<ContinueNode>();
		}

		/**
		 * Visits a return expression.
		 *
		 * \param ctx		The parser context for the expression.
		 * \return			Returns an AST node representing the return operation.
		 **/
		virtual std::any			visitReturnExpr(ExprParser::ReturnExprContext* ctx) override {
			size_t exprIndex = Object::InvalidIndex;
			
			if (ctx->expr()) {
				exprIndex = std::any_cast<size_t>(visit(ctx->expr()));
			}
			
			return context.addNode<ReturnNode>(exprIndex);
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
		 * \throws			ErrorCode::Unknown_Operator if the unary operator is not recognized.
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
			
			throw ErrorCode::Unknown_Operator;
		}

		/**
		 * Visits a C-style cast expression node in the AST, evaluates its inner expression, and casts it to the target type.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The parser context containing the C-style cast expression.
		 * \return			Returns an std::any containing the allocated node reference/index.
		 **/
		virtual std::any			visitCCastExpr(ExprParser::CCastExprContext* ctx) override {
			// Extract the target type string (e.g., "uint32_t" or "u32") and resolve it to your internal DataType enum.
			std::string typeStr = ctx->type_name()->getText();
			DataType targetType = resolveDataType(typeStr); 
			
			// Evaluate the inner expression to get its node index.
			size_t exprNode = std::any_cast<size_t>(visit(ctx->expr()));
			
			// Allocate a CastNode in the execution context arena.
			return context.addNode<CastNode>(exprNode, targetType);
		}

		/**
		 * Visits an initialization-style cast expression node in the AST, evaluates its inner expression, and casts it to the target type.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The parser context containing the initialization-style cast expression.
		 * \return			Returns an std::any containing the allocated node reference/index.
		 **/
		virtual std::any			visitInitCastExpr(ExprParser::InitCastExprContext* ctx) override {
			// Extract the target type string (e.g., "uint32_t" or "u32") and resolve it to your internal DataType enum.
			std::string typeStr = ctx->type_name()->getText();
			DataType targetType = resolveDataType(typeStr); 
			
			// Evaluate the inner expression to get its node index.
			size_t exprNode = std::any_cast<size_t>(visit(ctx->expr()));
			
			// Allocate a CastNode in the execution context arena.
			return context.addNode<CastNode>(exprNode, targetType);
		}

		/**
		 * Visits a static_cast expression node in the AST, evaluates its inner expression, and casts it to the target type.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The parser context containing the static_cast expression.
		 * \return			Returns an std::any containing the allocated node reference/index.
		 **/
		virtual std::any			visitStaticCastExpr(ExprParser::StaticCastExprContext* ctx) override {
			// Extract the target type string (e.g., "uint32_t" or "u32") and resolve it to your internal DataType enum.
			std::string typeStr = ctx->type_name()->getText();
			DataType targetType = resolveDataType(typeStr); 
			
			// Evaluate the inner expression to get its node index.
			size_t exprNode = std::any_cast<size_t>(visit(ctx->expr()));
			
			// Allocate a CastNode in the execution context arena.
			return context.addNode<CastNode>(exprNode, targetType);
		}

		/**
		 * Visits a multiplication or division node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the mul/div operation.
		 * \return			Returns a std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitMulDiv(ExprParser::MulDivContext* ctx) override {
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
		virtual std::any			visitAddSub(ExprParser::AddSubContext* ctx) override {
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
		 * \throws			ErrorCode::Unknown_Operator if the shift operator is not recognized.
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
			
			throw ErrorCode::Unknown_Operator;
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
		 * \throws			ErrorCode::Unknown_Operator if the relational operator is not recognized.
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
			
			throw ErrorCode::Unknown_Operator;
		}

		/**
		 * Visits an equality comparison node in the parse tree and allocates the corresponding operation node.
		 * 
		 * \param ctx		The ANTLR parser context for the equality operation.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 * \throws			ErrorCode::Unknown_Operator if the equality operator is not recognized.
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
			
			throw ErrorCode::Unknown_Operator;
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
		 * Visits an assignment or compound assignment expression.
		 *
		 * \param ctx		The parser context for the assignment expression.
		 * \return			Returns an AST node representing the assignment.
		 **/
		virtual std::any			visitAssignment(ExprParser::AssignmentContext* ctx) override {
			std::string varName = ctx->IDENTIFIER()->getText();
			int opType = ctx->op->getType();

			if (context.isConstant(varName) || context.isFunction(varName)) {
				throw ErrorCode::Invalid_LValue;
			}

			size_t varId = (opType == ExprLexer::ASSIGN) ? getOrCreateVariable(varName) : getVariable(varName);
			if (size_t(-1) != varId) {
				size_t rightIndex = std::any_cast<size_t>(visit(ctx->expr()));

				if (opType == ExprLexer::ASSIGN) { return context.addNode<AssignNode>(varId, rightIndex); }
				else if (opType == ExprLexer::ADD_ASSIGN) { return context.addNode<AddAssignNode>(varId, rightIndex); }
				else if (opType == ExprLexer::SUB_ASSIGN) { return context.addNode<SubAssignNode>(varId, rightIndex); }
				else if (opType == ExprLexer::MUL_ASSIGN) { return context.addNode<MulAssignNode>(varId, rightIndex); }
				else if (opType == ExprLexer::DIV_ASSIGN) { return context.addNode<DivAssignNode>(varId, rightIndex); }
				else if (opType == ExprLexer::MOD_ASSIGN) { return context.addNode<ModAssignNode>(varId, rightIndex); }
				else if (opType == ExprLexer::AND_ASSIGN) { return context.addNode<BitAndAssignNode>(varId, rightIndex); }
				else if (opType == ExprLexer::XOR_ASSIGN) { return context.addNode<BitXorAssignNode>(varId, rightIndex); }
				else if (opType == ExprLexer::OR_ASSIGN)  { return context.addNode<BitOrAssignNode>(varId, rightIndex); }
				else if (opType == ExprLexer::SHL_ASSIGN) { return context.addNode<ShlAssignNode>(varId, rightIndex); }
				else if (opType == ExprLexer::SHR_ASSIGN) { return context.addNode<ShrAssignNode>(varId, rightIndex); }

				throw ErrorCode::Invalid_LValue;
			}
			throw ErrorCode::Invalid_LValue;
		}

		/**
		 * Visits an array index assignment expression.
		 *
		 * \param ctx		The parser context for the expression.
		 * \return			Returns an AST node representing the operation.
		 **/
		virtual std::any			visitArrayAssignment(ExprParser::ArrayAssignmentContext* ctx) override {
			size_t targetIndex = std::any_cast<size_t>(visit(ctx->expr(0)));
			size_t indexIndex = std::any_cast<size_t>(visit(ctx->expr(1)));
			size_t rightIndex = std::any_cast<size_t>(visit(ctx->expr(2)));
			int opType = ctx->op->getType();
			
			return context.addNode<ArrayAssignNode>(targetIndex, indexIndex, rightIndex, opType);
		}

		/**
		 * Visits an array slice assignment expression.
		 *
		 * \param ctx		The parser context for the expression.
		 * \return			Returns an AST node representing the operation.
		 **/
		virtual std::any			visitArrayExAssignment(ExprParser::ArrayExAssignmentContext* ctx) override {
			size_t targetIndex = std::any_cast<size_t>(visit(ctx->expr(0)));
			size_t startIndex = static_cast<size_t>(-1);
			size_t endIndex = static_cast<size_t>(-1);
			uint32_t mask = 0;

			if (ctx->start) {
				startIndex = std::any_cast<size_t>(visit(ctx->start));
				mask |= ArrayExFlags::ArrayExFlag_Start;
			}
			if (ctx->end) {
				endIndex = std::any_cast<size_t>(visit(ctx->end));
				mask |= ArrayExFlags::ArrayExFlag_End;
			}

			size_t rightIndex = std::any_cast<size_t>(visit(ctx->expr().back()));
			int opType = ctx->op->getType();

			return context.addNode<ArrayExAssignNode>(targetIndex, startIndex, endIndex, mask, rightIndex, opType);
		}

		/**
		 * Visits a parentheses node, simply passing the inner expression's index up the tree.
		 * 
		 * \param ctx		The ANTLR parser context for the parentheses.
		 * \return			Returns a std::any containing the size_t index of the inner evaluated node.
		 **/
		virtual std::any			visitParens(ExprParser::ParensContext* ctx) override {
			return visit(ctx->expr());
		}

		/**
		 * Visits a map literal expression node in the AST, evaluates its keys and values, and allocates a MapNode.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The parser context containing the map expression.
		 * \return			Returns an std::any containing the allocated node reference/index.
		 **/
		virtual std::any			visitMapExpr(ExprParser::MapExprContext* ctx) override {
			std::vector<std::pair<size_t, size_t>> elements;

			if (ctx->exprMapList()) {
				auto exprs = ctx->exprMapList()->expr();
				
				for (size_t i = 0; i < exprs.size(); i += 2) {
					size_t keyId = std::any_cast<size_t>(visit(exprs[i]));
					size_t valId = std::any_cast<size_t>(visit(exprs[i+1]));
					elements.push_back({ keyId, valId });
				}
			}

			return context.addNode<MapNode>(elements);
		}

		/**
		 * Visits a vector initializer list expression.
		 *
		 * \param ctx		The parser context for the vector expression.
		 * \return			Returns an AST node representing the vector.
		 **/
		virtual std::any			visitVectorExpr(ExprParser::VectorExprContext* ctx) override {
			std::vector<AstNode*> elements;
			
			if (ctx->exprList()) {
				for (auto* exprCtx : ctx->exprList()->expr()) {
					elements.push_back(std::any_cast<AstNode*>(visit(exprCtx)));
				}
			}
			
			return context.addNode<VectorNode>(elements);
		}

		/**
		 * Visits a block structure and routes it to the underlying statement_list logic.
		 *
		 * \param ctx		The parser context containing the block.
		 * \return			Returns an std::any containing the allocated block node index.
		 **/
		virtual std::any			visitBlock(ExprParser::BlockContext* ctx) override {
			return visit(ctx->statement_list());
		}

		/**
		 * Visits an identifier node. If the identifier is a registered constant, 
		 * it compiles down to a literal ConstantNode. Otherwise, it compiles as a VarNode.
		 * 
		 * \param ctx		The ANTLR parser context for the identifier.
		 * \return			Returns an std::any containing the size_t index of the allocated node.
		 **/
		virtual std::any			visitIdentifier(ExprParser::IdentifierContext* ctx) override {
			std::string varName = ctx->IDENTIFIER()->getText();

			Result constVal;
			if (context.getConstant(varName, constVal)) {
				return context.addNode<ConstantNode>(constVal);
			}

			size_t varId = getVariable(varName);
			if (size_t(-1) != varId) {
				return context.addNode<VarNode>(varId);
			}

			return static_cast<size_t>(0);
		}

		/**
		 * Visits a '$$' expression node in the AST and allocates a TotalParmsNode to resolve it at runtime.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The parser context containing the '$$' token.
		 * \return			Returns an std::any containing the allocated node reference/index.
		 **/
		virtual std::any			visitTotalParmsExpr(ExprParser::TotalParmsExprContext* ctx) override {
			return context.addNode<TotalParmsNode>();
		}


		// =========================================================================
		// Constant Node Visitors
		// =========================================================================
		/**
		 * Visits a boolean constant node in the AST, evaluates its logical value, and adds it to the context.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The parser context containing the boolean token.
		 * \return			Returns an std::any containing the allocated node reference/index.
		 **/
		virtual std::any			visitBool_constant(ExprParser::Bool_constantContext* ctx) override {
			Result res;

			if (ctx->KW_TRUE()) {
				res = Result::make(true);
			}
			else {
				res = Result::make(false);
			}
			
			return context.addNode<ConstantNode>(res);
		}

		/**
		 * Visits a user value node ('??') in the AST, retrieves the externally defined value, and adds it to the context.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The parser context containing the user value token.
		 * \return			Returns an std::any containing the allocated node reference/index.
		 **/
		virtual std::any			visitUser_val(ExprParser::User_valContext* ctx) override {
			return context.addNode<UserValueNode>();
		}

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

		/**
		 * Visits a character constant node, parsing its content into a UTF-8 code point.
		 * Handles both raw character sequences and escape sequences.
		 *
		 * \param ctx		The parser context containing the character literal.
		 * \return			Returns an std::any containing the allocated AstNode index.
		 **/
		virtual std::any			visitChar_constant(ExprParser::Char_constantContext* ctx) override {
			std::string text = ctx->CHAR_CONSTANT()->getText();
			
			std::string_view payload(text.data() + 1, text.length() - 2);
			
			uint64_t codePoint = 0;
			
			if (!payload.empty()) {
				size_t charsConsumed = 0;
				bool escapeFound = false;
					
				codePoint = Text::resolveEscape(payload.data(), payload.size(), charsConsumed, true, &escapeFound);
					
				if (!escapeFound) {
					size_t eaten = 0;
					codePoint = static_cast<uint64_t>(Text::nextUtf8Char(payload.data(), payload.size(), &eaten));
				}
			}
			
			Result res;
			res.type = NumericConstant::Unsigned;
			res.value.uintVal = codePoint;
			
			return context.addNode<ConstantNode>(res);
		}

		/**
		 * Visits a string_constant node, resolves string literals based on their specific prefixes,
		 * concatenates them, and allocates a runtime String object to be returned via a ConstantNode.
		 *
		 * \param ctx		The parser context for the string constant.
		 * \return			Returns an AST node containing the parsed string Result.
		 **/
		virtual std::any			visitString_constant(ExprParser::String_constantContext* ctx) override {
			std::string combinedUtf8;
			
			for (auto tokenCtx : ctx->string_token()) {
				antlr4::tree::TerminalNode* terminal = static_cast<antlr4::tree::TerminalNode*>(tokenCtx->children[0]);
				size_t tokenType = terminal->getSymbol()->getType();
				Text::StringFormat format = Text::StringFormat::Normal;

				switch (tokenType) {
					case ExprLexer::STRING_RAW : {
						format = Text::StringFormat::Raw;
						break;
					}
					case ExprLexer::STRING_UTF8 : {
						format = Text::StringFormat::Utf8;
						break;
					}
					case ExprLexer::STRING_UTF16 : {
						format = Text::StringFormat::Utf16;
						break;
					}
					case ExprLexer::STRING_UTF32 : {
						format = Text::StringFormat::Utf32;
						break;
					}
					case ExprLexer::STRING_WIDE : {
						format = Text::StringFormat::Wide;
						break;
					}
					case ExprLexer::STRING_C : {
						format = Text::StringFormat::CString;
						break;
					}
					default : {
						format = Text::StringFormat::Normal;
						break;
					}
				}

				combinedUtf8 += Text::parseStringLiteral(terminal->getText(), format);
			}
			
			String* strObj = context.allocateObject<String>();
			
			if (strObj) {
				strObj->assignUtf8(combinedUtf8.data(), combinedUtf8.length());
				strObj->incRef();
				return context.addNode<ConstantNode>(strObj->createResult());
			}
			else {
				return context.addNode<ConstantNode>(Result{});
			}
		}

		/**
		 * Resolves a type string representation into the corresponding DataType enum.
		 * 
		 * \param typeStr	The string representation of the type from the lexer (e.g., "uint32_t", "f64").
		 * \return			Returns the corresponding DataType. Returns DataType::Invalid if not matched.
		 **/
		static inline DataType		resolveDataType(const std::string& typeStr) {
			if (typeStr == "uint8_t"  || typeStr == "u8"  || typeStr == "ui8")  { return DataType::UInt8; }
			if (typeStr == "uint16_t" || typeStr == "u16" || typeStr == "ui16") { return DataType::UInt16; }
			if (typeStr == "uint32_t" || typeStr == "u32" || typeStr == "ui32") { return DataType::UInt32; }
			if (typeStr == "uint64_t" || typeStr == "u64" || typeStr == "ui64") { return DataType::UInt64; }
			
			if (typeStr == "int8_t"   || typeStr == "i8")  { return DataType::Int8; }
			if (typeStr == "int16_t"  || typeStr == "i16") { return DataType::Int16; }
			if (typeStr == "int32_t"  || typeStr == "i32") { return DataType::Int32; }
			if (typeStr == "int64_t"  || typeStr == "i64") { return DataType::Int64; }
			
			if (typeStr == "float"    || typeStr == "f32") { return DataType::Float; }
			if (typeStr == "double"   || typeStr == "f64") { return DataType::Double; }
			
			return DataType::Any; 
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

		/**
		 * Checks if a variable name exists in the compiler's map.
		 * If it does, returns its ID. If not, size_t(-1) is returned
		 *
		 * \param name		The string identifier of the variable to look up or create.
		 * \return			Returns the runtime index (ID) of the variable ir size_t(-1).
		 **/
		size_t						getVariable(const std::string& name) {
			auto it = variableMap.find(name);
			if (it != variableMap.end()) {
				return it->second;
			}
			
			return size_t(-1);
		}
	};

}	// namespace ve
