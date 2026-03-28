#include "ExecutionContext.h"
#include "../Compiler/AstBuilderVisitor.h"
#include "../../generated/ExprLexer.h"
#include "../../generated/ExprParser.h"
#include <iostream>

namespace ve {

	// == Functions.
	/**
	 * Compiles a string expression and populates the internal AST.
	 * 
	 * \param expression	The raw mathematical expression string.
	 * \param errorOut		Optional pointer to a string that will receive error details if compilation fails.
	 * \return				Returns true if compilation succeeded, false otherwise.
	 **/
	bool ExecutionContext::compile(const std::string& expression, std::wstring* errorOut) {
		// TODO: errorOut should go through a localizer.
		try {
			arena.nodes.clear();

			antlr4::ANTLRInputStream input(expression);
			ExprLexer lexer(&input);
			antlr4::CommonTokenStream tokens(&lexer);
			ExprParser parser(&tokens);

			antlr4::tree::ParseTree* tree = parser.prog();

			AstBuilderVisitor visitor(*this);
			std::any resultAny = visitor.visit(tree);

			if (resultAny.has_value()) {
				rootIndex = std::any_cast<size_t>(resultAny);
				return true;
			}
			else {
				if (errorOut) {
					(*errorOut) = L"Visitor failed to return a valid root node index.";
				}
				return false;
			}
		}
		catch (const std::bad_any_cast& e) {
			if (errorOut) {
				std::string tmp = e.what();
				(*errorOut) = std::wstring(L"AST visitor type mismatch: ") + std::wstring(tmp.begin(), tmp.end());
			}
			return false;
		}
		catch (const ErrorCode& e) {
			if (errorOut) {
				if (e == ErrorCode::Out_Of_Memory) {
					(*errorOut) = L"Memory allocation failed within the AstArena.";
				}
				else {
					(*errorOut) = L"An internal engine error occurred during compilation.";
				}
			}
			return false;
		}
		catch (const std::exception& e) {
			if (errorOut) {
				std::string tmp = e.what();
				(*errorOut) = std::wstring(L"Standard exception caught: ") + std::wstring(tmp.begin(), tmp.end());
			}
			return false;
		}
		catch (...) {
			if (errorOut) {
				(*errorOut) = L"An unknown critical error occurred during compilation.";
			}
			return false;
		}
	}

	Result ExecutionContext::execute() {
		if (arena.nodes.empty()) {
			Result emptyRes;
			emptyRes.type = NumericConstant::Invalid;
			return emptyRes;
		}
		return arena.nodes[rootIndex]->evaluate(*this);
	}

	/**
	 * Evaluates the currently compiled AST. Can be called multiple times.
	 * 
	 * \return			Returns the evaluated Result.
	 **/
	NumericConstant ExecutionContext::getCastType(NumericConstant left, NumericConstant right) {
		return left > right ? left : right;
	}

	/**
	 * Converts a result or object to a specified numeric type.
	 * 
	 * \param res			The source result to convert.
	 * \param target		The target numeric constant type.
	 * \return				Returns a new Result converted to the target type.
	 **/
	Result ExecutionContext::convertResult(const Result& res, NumericConstant target) {
		if (res.type == target) { return res; }

		Result out;
		out.type = target;

		if (res.type == NumericConstant::Floating) {
			switch (target) {
				case NumericConstant::Signed : {
					out.value.intVal = static_cast<int64_t>(res.value.doubleVal);
					break;
				}
				case NumericConstant::Unsigned : {
					out.value.uintVal = static_cast<uint64_t>(res.value.doubleVal);
					break;
				}
				case NumericConstant::Object : {
					out.type = NumericConstant::Invalid;
					break;
				}
				default : { break; }
			}
		}
		else if (res.type == NumericConstant::Signed) {
			switch (target) {
				case NumericConstant::Unsigned : {
					out.value.uintVal = static_cast<uint64_t>(res.value.intVal);
					break;
				}
				case NumericConstant::Floating : {
					out.value.doubleVal = static_cast<double>(res.value.intVal);
					break;
				}
				case NumericConstant::Object : {
					out.type = NumericConstant::Invalid;
					break;
				}
				default : { break; }
			}
		}
		else if (res.type == NumericConstant::Unsigned) {
			switch (target) {
				case NumericConstant::Floating : {
					out.value.doubleVal = static_cast<double>(res.value.uintVal);
					break;
				}
				case NumericConstant::Signed : {
					out.value.intVal = static_cast<int64_t>(res.value.uintVal);
					break;
				}
				case NumericConstant::Object : {
					out.type = NumericConstant::Invalid;
					break;
				}
				default : { break; }
			}
		}
		else if (res.type == NumericConstant::Object) {
			if (!res.value.objectVal) {
				out.type = NumericConstant::Invalid;
			}
			else {
				// TODO.
				out.type = NumericConstant::Invalid; 
			}
		}

		return out;
	}

}	// namespace ve
