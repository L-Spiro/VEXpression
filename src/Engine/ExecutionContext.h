#pragma once

#include "../Ast/AstArena.h"
#include "FunctionDef.h"
#include "Object.h"
#include "Result.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace ve {

	// A helper macro for memory management.
#define VE_DELETE_SWAP( oldPtr, newPtr )																\
	if (oldPtr.type == NumericConstant::Object) {														\
		if (oldPtr.value.objectVal != newPtr && newPtr) {												\
			if (!newPtr->getRef()) { context.deallocateObject(newPtr); }								\
		}																								\
		newPtr = oldPtr.value.objectVal;																\
	}

	// == Enumerations.
	/**
	 * Represents the current control flow state of the execution context.
	 **/
	enum class FlowState : uint8_t {
		Normal,							/**< Standard sequential execution. */
		Break,							/**< A break statement was encountered, seeking the nearest loop exit. */
		Continue,						/**< A continue statement was encountered, seeking the nearest loop start. */
		Return							/**< A return statement was encountered, seeking the function exit. */
	};

	/**
	 * The master engine object. It parses text, holds the AST arena, 
	 * manages the lifetime of allocated objects, and provides conversion utilities.
	 **/
	class ExecutionContext {
	public :
		ExecutionContext() {}
		~ExecutionContext() {
			reset();
		}

		
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
		 * Resets the object back to scratch.
		 **/
		void							reset();

		/**
		 * Converts a Result into its string representation.
		 * Must be called within a try/catch block.
		 *
		 * \param res			The Result to convert.
		 * \param depth			The recursion depth for stringifying nested objects (defaults to 1).
		 * \param flags			Bitmask defining formatting rules (defaults to 0).
		 * \return				Returns the string representation of the Result.
		 **/
		std::string						toString(const Result& res, int32_t depth = 1, uint32_t flags = 0) const;

		/**
		 * Converts a Result into its formatted string representation.
		 * Must be called within a try/catch block.
		 *
		 * \param res			The Result to convert.
		 * \param formatStr		The format string to apply.
		 * \param flags			Bitmask defining formatting rules (defaults to 0).
		 * \return				Returns the formatted string representation of the Result.
		 **/
		std::string						formattedString(const Result& res, const std::string& formatStr, uint32_t flags = 0) const;

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
		 * Casts a raw evaluated Result into the specific C-type expected by a function parameter.
		 * Applies standard C-truncation (e.g., 64-bit to 8-bit) and precision loss (double to float).
		 * 
		 * \param rawVal		The original 64-bit evaluated result.
		 * \param targetType	The explicit C data type to cast into.
		 * \return				Returns a newly formatted Result containing the truncated/casted value.
		 **/
		Result							castArgument(const Result& rawVal, DataType targetType) const;

		/**
		 * Retrieves the current control flow state.
		 *
		 * \return				Returns the active FlowState.
		 **/
		inline FlowState				getFlowState() const { return flowState; }

		/**
		 * Triggers a break signal.
		 **/
		inline void						setBreak() { flowState = FlowState::Break; }

		/**
		 * Triggers a continue signal.
		 **/
		inline void						setContinue() { flowState = FlowState::Continue; }

		/**
		 * Triggers a return signal and stores the result.
		 *
		 * \param res			The result to return from the function.
		 **/
		inline void						setReturn(const Result& res) { 
			flowState = FlowState::Return; 
			returnValue = res; 
		}

		/**
		 * Clears the current control flow signal, restoring normal execution.
		 **/
		inline void						clearFlowState() { flowState = FlowState::Normal; }

		/**
		 * Retrieves the value stored by a return statement.
		 *
		 * \return				Returns the stored return Result.
		 **/
		inline Result					getReturnValue() const { return returnValue; }

		/**
		 * Centralized evaluation helper for all math and compound operations.
		 *
		 * \param leftVal		The left operand.
		 * \param rightVal		The right operand.
		 * \param opType		The ExprLexer token representing the operation (e.g. ADD_ASSIGN).
		 * \return				Returns the resulting evaluation.
		 **/
		Result							evaluateMath(const Result& leftVal, const Result& rightVal, int opType) const;
		
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

		/**
		 * Assigns a result to a variable at the specified index.
		 *
		 * \param index		The resolved index of the variable.
		 * \param value		The Result to assign.
		 **/
		inline void						setVariable(size_t index, const Result& value) {
			if (index < variables.size()) {
				variables[index] = value;
			}
		}

		/**
		 * Registers a custom constant with the execution context.
		 * 
		 * \param name		The string identifier for the constant.
		 * \param value		The resolved Result value.
		 **/
		void							registerConstant(const std::string& name, const Result& value) {
			registeredConstants[name] = value;
		}

		/**
		 * Checks if a constant is registered and retrieves its value.
		 * 
		 * \param name		The string identifier to check.
		 * \param outVal	Output parameter to store the Result if found.
		 * \return			True if the constant exists, false otherwise.
		 **/
		bool							getConstant(const std::string& name, Result& outVal) const {
			auto it = registeredConstants.find(name);
			if (it != registeredConstants.end()) {
				outVal = it->second;
				return true;
			}
			return false;
		}

		/**
		 * Checks if an identifier is a registers constant without getting the value of it.
		 * 
		 * \param name		The string identifier to check.
		 * \return			True if the constant exists, false otherwise.
		 **/
		bool							isConstant(const std::string& name) const {
			auto it = registeredConstants.find(name);
			if (it != registeredConstants.end()) {
				return true;
			}
			return false;
		}

		/**
		 * Registers a new built-in function to the execution context.
		 * 
		 * \param name				The string identifier used in the script.
		 * \param params			A vector defining the expected type, name, and description of each argument.
		 * \param callback			The C++ function pointer to execute at runtime.
		 * \param vectorElements	If true, the function can be called on each element of a vector instead of on a single non-vector parameter.
		 **/
		void							registerFunction(const char* name, const std::vector<ParameterDef>& params, IntrinsicCallback callback, bool vectorElements) {
			try {
				FunctionDef def;
				def.name = name;
				def.description = StringId::None;
				def.parameters = params;
				def.callback = callback;
				def.variadic = params.size() && params[params.size()-1].type == DataType::Variadic;
				def.operateOnVectorElements = vectorElements;

				FunctionSignature sig = { name, params.size(), def.variadic };
				registeredFunctions[sig] = def;
			}
			catch (...) { throw ErrorCode::Out_Of_Memory; }
		}

		/**
		 * Checks if a specific function overload is registered and retrieves its definition.
		 * 
		 * \param name		The string identifier to check.
		 * \param arity		The number of arguments the function was called with.
		 * \param outDef	Output parameter to store the FunctionDef if found.
		 * \return			True if the exact overload exists, false otherwise.
		 **/
		bool							getFunction(const std::string& name, size_t arity, FunctionDef& outDef) const {
			auto exactIt = registeredFunctions.find({ name, arity, false });
			
			if (exactIt != registeredFunctions.end()) {
				outDef = exactIt->second;
				return true;
			}

			auto startIt = std::make_reverse_iterator(registeredFunctions.upper_bound({ name, arity, false }));
			auto endIt = std::make_reverse_iterator(registeredFunctions.lower_bound({ name, 0, false }));

			auto match = std::find_if(startIt, endIt, [](const auto& pair) {
				return pair.first.variadic;
			});

			if (match != endIt) {
				outDef = match->second;
				return true;
			}

			return false;
		}

		/**
		 * Checks if a function is registered.
		 * 
		 * \param name		The string identifier to check.
		 * \return			True if the function exists, false otherwise.
		 **/
		bool							isFunction(const std::string& name) const {
			// Find the first signature that is not less than {name, 0}
			auto it = registeredFunctions.lower_bound({ name, 0 });
			
			// If it exists and the name matches, the function exists.
			if (it != registeredFunctions.end() && it->first.name == name) {
				return true;
			}
			return false;
		}

		/**
		 * Allocates an object of the specified type and tracks it for memory management via a smart pointer.
		 *
		 * \param flags			Optional flags for allocation.
		 * \return				Returns a non-owning pointer to the allocated object, or nullptr on failure.
		 **/
		template <typename T>
		T*								allocateObject(uint32_t flags = 0) {
			static_cast<void>(flags);
			try {
				std::unique_ptr<T> obj = std::make_unique<T>(this);
				T* ptr = obj.get();
				objects.push_back(std::move(obj));
				return ptr;
			}
			catch (const std::bad_alloc&) {
				return nullptr;
			}
		}

		/**
		 * Deallocates a specifically tracked object by removing its smart pointer.
		 *
		 * \param obj			The non-owning pointer to the object to deallocate.
		 * \return				Returns true if the object was found and deleted, false otherwise.
		 **/
		bool							deallocateObject(Object* obj) {
			if (!obj) { return true; }
			// Reverse search because it is most likely the immediate deletion of a temporary object.
			for (size_t i = objects.size(); i--; ) {
				if (objects[i].get() == obj) {
					objects.erase(objects.begin() + i);
					return true;
				}
				return true;
			}
			
			return false;
		}


	protected :
		// == Types.
		/**
		 * Represents a unique function signature for arity-based overloading.
		 **/
		struct FunctionSignature {
			std::string					name;
			size_t						arity;
			bool						variadic;

			bool						operator<(const FunctionSignature& rhs) const {
				if (name != rhs.name) {
					return name < rhs.name;
				}
				return arity < rhs.arity;
			}
		};


		// == Members.
		/** The central storage arena containing all allocated AST nodes. **/
		AstArena						arena;
		/** The array of registered variables. */
		std::vector<Result>				variables;
		/** A map of built-in and user-registered constants (e.g., M_PI). **/
		std::map<std::string, Result>	registeredConstants;
		/** A map of user-registered and built-in function definitions. **/
		std::map<FunctionSignature, FunctionDef>
										registeredFunctions;
		/** Tracked objects managed by the execution context. **/
		std::vector<std::unique_ptr<Object>>
										objects;
		/** The state of execution (continue, break, return, or normal). */
		FlowState						flowState = FlowState::Normal;
		/** The return value if return is used. */
		Result							returnValue;
		/** The arena index of the root AST node to execute. **/
		size_t							rootIndex = 0;
		/** The initiale size of the objects array. */
		size_t							initialObjectsTotal = 0;
		/** Treat standard integers as hex? */
		bool							treatAllAsHex = false;
		


	private :
		// == Types.
		/** A list of built-in constants. */
		struct BuiltInConstant {
			const char*					name;						/**< The name of the constant. */
			Result						result;						/**< The constant value. */
		};


		// == Members.
		/** A list of built-in constants. */
		static BuiltInConstant			builtInConsts[];
		/** The static list of built-in functions. */
		static const FunctionDef		builtInFunctions[];
	};

}	// namespace ve
