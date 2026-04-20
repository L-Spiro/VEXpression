#pragma once

#include "../Engine/Result.h"

#include <cstdint>
#include <string>

namespace ve {

	class ExecutionContext;


	// == Enumerations
	/**
	 * Bit flags describing object types that are implemented directly by the expression-evaluation runtime.
	 *
	 * These flags identify concrete built-in object implementations (for example, a dynamic UTF-8 string type
	 * or a vector container) that can be created and manipulated by the evaluator.
	 *
	 * \note This is a bitmask enumeration. Multiple flags may be combined.
	 **/
	enum BuiltInTypes : uint32_t {
		BuiltInType_None					= 0,
		BuiltInType_String					= (1 << 1),
		BuiltInType_Vector					= (1 << 2),
		BuiltInType_Map						= (1 << 3),
		BuiltInType_Set						= (1 << 4)
	};

	/**
	 * Bit flags controlling extended array-access behavior.
	 *
	 * Extended array access allows implementations to interpret one or two indices depending on which
	 * flags are set in the mask passed to arrayAccessEx().
	 *
	 * \note This is a bitmask enumeration. Multiple flags may be combined.
	 **/
	enum ArrayExFlags : uint32_t {
		ArrayExFlag_Start					= (1 << 0),
		ArrayExFlag_End						= (1 << 1)
	};

	/**
	 * Flags controlling string conversion and formatting behaviors.
	 *
	 * These flags influence how toString() and formattedString() escape or present data.
	 *
	 * \note This is a bitmask enumeration. Multiple flags may be combined.
	 **/
	enum ToStringFlags : uint32_t {
		/** No special formatting is applied. */
		ToStringFlag_None					= 0,

		/**
		 * Treats the output as a C-style string literal, escaping quotes and other characters as needed.
		 * Example: Hey "Bob" -> "Hey \"Bob\""
		 **/
		ToStringFlag_CString				= (1 << 0)
	};


	// == Types.
	/**
	 * The abstract base class for all dynamically allocated script objects (Strings, Vectors, Maps, Sets).
	 **/
	class Object {
	public :
		/**
		 * Constructs the object, binding it to the current execution context.
		 *
		 * \param ctx		A pointer to the execution context managing this object.
		 **/
		Object(ExecutionContext* ctx) : context(ctx) {}

		/**
		 * Default virtual destructor.
		 **/
		virtual ~Object() = default;


		// == Enumerations.
		/** A constant representing an invalid or out-of-bounds array index. */
		static constexpr size_t				InvalidIndex = static_cast<size_t>(-1);


		// == Core API
		/**
		 * Gets the runtime type identifier of this object.
		 *
		 * Derived classes should return a stable type value used by the evaluator to identify the object
		 * implementation.
		 *
		 * \return				Returns the object type identifier.
		 **/
		virtual uint32_t					type() const { return BuiltInType_None; }

		/**
		 * Serializes the object into a string representation.
		 *
		 * \param returnString	The output parameter where the string representation will be appended.
		 * \param depth			The current recursion depth (used for indenting or catching circular references).
		 * \param flags			Formatting flags dictating how the string should be generated.
		 * \return				Returns true if the object was successfully converted to a string.
		 **/
		virtual bool						toString(std::wstring& returnString, uint32_t depth, uint32_t flags) const = 0;

		/**
		 * Generates a formatted string representation of the object.
		 *
		 * \param format		The format string specifying how the object should be presented.
		 * \param flags			Formatting flags.
		 * \return				Returns the formatted wide string.
		 **/
		virtual std::wstring				formattedString(const std::wstring& format, uint32_t flags) const = 0;

		/**
		 * Converts the object to a fundamental numeric constant type if possible.
		 *
		 * \param targetType	The target numeric type to convert to.
		 * \return				Returns a Result containing the converted value, or an error state if invalid.
		 **/
		virtual Result						convertTo(NumericConstant targetType) const = 0;

		/**
		 * Initializes the internal state of the object using a raw Result value.
		 *
		 * \param val			The Result value to initialize from.
		 * \return				Returns true if initialization was successful, false otherwise.
		 **/
		virtual bool						initializeFrom(const Result& val) = 0;


		// == Array Operations
		/**
		 * Accesses an element within the object using a single index.
		 *
		 * \param idx			The zero-based index of the element to access.
		 * \return				Returns a Result containing the accessed element.
		 **/
		virtual Result						arrayAccess(int64_t idx) = 0;

		/**
		 * Accesses an element or sub-range within the object using complex indexing or slicing.
		 *
		 * \param idx0			The primary index or slice start.
		 * \param idx1			The secondary index or slice end.
		 * \param mask			A bitmask defining the specific access behavior.
		 * \return				Returns a Result containing the accessed element or range.
		 **/
		virtual Result						arrayAccessEx(int64_t idx0, int64_t idx1, uint32_t mask) = 0;

		/**
		 * Retrieves the total number of elements contained in the object.
		 *
		 * \return				Returns the element count as a size_t.
		 **/
		virtual size_t						arrayLength() const = 0;


		// == Extended API (Representations & Conversions)
		/**
		 * Converts the object from UTF-8 to ASCII.
		 *
		 * \return				Returns a Result containing the converted value. Behavior is implementation-defined for non-ASCII code points.
		 **/
		virtual Result						ascii() const = 0;

		/**
		 * Gets the binary form of the object as a string.
		 *
		 * \return				Returns a Result containing a string formatted as 0b****.
		 **/
		virtual Result						bin() const = 0;

		/**
		 * Gets the boolean representation of the object.
		 *
		 * \return				Returns a Result containing a truthy (1) or falsy (0) value.
		 **/
		virtual Result						toBool() const = 0;

		/**
		 * Returns the character represented by the object as a Unicode code point.
		 *
		 * \return				Returns a Result containing the resulting character.
		 **/
		virtual Result						chr() const = 0;

		/**
		 * Interprets the object as its best-fit numeric representation and converts it to a float.
		 *
		 * \return				Returns a Result containing the converted double-precision floating-point value.
		 **/
		virtual Result						toFloat() const = 0;

		/**
		 * Gets the hexadecimal form of the object as a string.
		 *
		 * \return				Returns a Result containing a string formatted as 0x****.
		 **/
		virtual Result						hex() const = 0;

		/**
		 * Interprets the object as its best-fit numeric representation and converts it to an integer.
		 *
		 * \return				Returns a Result containing the converted 64-bit integer value.
		 **/
		virtual Result						toInt() const = 0;

		/**
		 * Gets the number of elements or characters in the object.
		 *
		 * \return				Returns a Result containing the element or UTF code point count.
		 **/
		virtual Result						len() const = 0;

		/**
		 * Gets the octal form of the object as a string.
		 *
		 * \return				Returns a Result containing a string formatted as 0o****.
		 **/
		virtual Result						oct() const = 0;

		/**
		 * Returns the ordinal (numeric) value of the object as a Unicode code point.
		 *
		 * \return				Returns a Result containing the ordinal value as an unsigned integer.
		 **/
		virtual Result						ord() const = 0;


		// == Binary Operators
		/**
		 * Evaluates equality between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if equal, 0 if not.
		 **/
		virtual Result						operator==(const Result& rhs) const = 0;

		/**
		 * Evaluates inequality between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if not equal, 0 if equal.
		 **/
		virtual Result						operator!=(const Result& rhs) const = 0;

		/**
		 * Evaluates strictly-less-than comparison between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if less, 0 otherwise.
		 **/
		virtual Result						operator<(const Result& rhs) const = 0;

		/**
		 * Evaluates strictly-greater-than comparison between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if greater, 0 otherwise.
		 **/
		virtual Result						operator>(const Result& rhs) const = 0;

		/**
		 * Evaluates less-than-or-equal comparison between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if less or equal, 0 otherwise.
		 **/
		virtual Result						operator<=(const Result& rhs) const = 0;

		/**
		 * Evaluates greater-than-or-equal comparison between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if greater or equal, 0 otherwise.
		 **/
		virtual Result						operator>=(const Result& rhs) const = 0;

		/**
		 * Evaluates the addition operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed sum.
		 **/
		virtual Result						operator+(const Result& rhs) const = 0;

		/**
		 * Evaluates the subtraction operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed difference.
		 **/
		virtual Result						operator-(const Result& rhs) const = 0;

		/**
		 * Evaluates the multiplication operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed product.
		 **/
		virtual Result						operator*(const Result& rhs) const = 0;

		/**
		 * Evaluates the division operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed quotient.
		 **/
		virtual Result						operator/(const Result& rhs) const = 0;

		/**
		 * Evaluates the modulo operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed remainder.
		 **/
		virtual Result						operator%(const Result& rhs) const = 0;

		/**
		 * Evaluates the bitwise left-shift operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand indicating the shift amount.
		 * \return				Returns a Result containing the shifted value.
		 **/
		virtual Result						operator<<(const Result& rhs) const = 0;

		/**
		 * Evaluates the bitwise right-shift operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand indicating the shift amount.
		 * \return				Returns a Result containing the shifted value.
		 **/
		virtual Result						operator>>(const Result& rhs) const = 0;

		/**
		 * Evaluates the bitwise AND operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed bitwise AND.
		 **/
		virtual Result						operator&(const Result& rhs) const = 0;

		/**
		 * Evaluates the bitwise OR operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed bitwise OR.
		 **/
		virtual Result						operator|(const Result& rhs) const = 0;

		/**
		 * Evaluates the bitwise XOR operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed bitwise XOR.
		 **/
		virtual Result						operator^(const Result& rhs) const = 0;


		// == Assignment Operators
		/**
		 * Evaluates the addition-assignment operation and updates the object's state.
		 *
		 * \param rhs			The right-hand side operand to add.
		 * \return				Returns true if the assignment was successful, false otherwise.
		 **/
		virtual bool						operator+=(const Result& rhs) = 0;

		/**
		 * Evaluates the subtraction-assignment operation and updates the object's state.
		 *
		 * \param rhs			The right-hand side operand to subtract.
		 * \return				Returns true if the assignment was successful, false otherwise.
		 **/
		virtual bool						operator-=(const Result& rhs) = 0;

		/**
		 * Evaluates the multiplication-assignment operation and updates the object's state.
		 *
		 * \param rhs			The right-hand side operand to multiply.
		 * \return				Returns true if the assignment was successful, false otherwise.
		 **/
		virtual bool						operator*=(const Result& rhs) = 0;

		/**
		 * Evaluates the division-assignment operation and updates the object's state.
		 *
		 * \param rhs			The right-hand side operand to divide by.
		 * \return				Returns true if the assignment was successful, false otherwise.
		 **/
		virtual bool						operator/=(const Result& rhs) = 0;

		/**
		 * Evaluates the modulo-assignment operation and updates the object's state.
		 *
		 * \param rhs			The right-hand side operand to divide by for the remainder.
		 * \return				Returns true if the assignment was successful, false otherwise.
		 **/
		virtual bool						operator%=(const Result& rhs) = 0;

		/**
		 * Evaluates the bitwise left-shift-assignment operation and updates the object's state.
		 *
		 * \param rhs			The right-hand side operand indicating the shift amount.
		 * \return				Returns true if the assignment was successful, false otherwise.
		 **/
		virtual bool						operator<<=(const Result& rhs) = 0;

		/**
		 * Evaluates the bitwise right-shift-assignment operation and updates the object's state.
		 *
		 * \param rhs			The right-hand side operand indicating the shift amount.
		 * \return				Returns true if the assignment was successful, false otherwise.
		 **/
		virtual bool						operator>>=(const Result& rhs) = 0;

		/**
		 * Evaluates the bitwise AND-assignment operation and updates the object's state.
		 *
		 * \param rhs			The right-hand side operand to bitwise AND with.
		 * \return				Returns true if the assignment was successful, false otherwise.
		 **/
		virtual bool						operator&=(const Result& rhs) = 0;

		/**
		 * Evaluates the bitwise OR-assignment operation and updates the object's state.
		 *
		 * \param rhs			The right-hand side operand to bitwise OR with.
		 * \return				Returns true if the assignment was successful, false otherwise.
		 **/
		virtual bool						operator|=(const Result& rhs) = 0;

		/**
		 * Evaluates the bitwise XOR-assignment operation and updates the object's state.
		 *
		 * \param rhs			The right-hand side operand to bitwise XOR with.
		 * \return				Returns true if the assignment was successful, false otherwise.
		 **/
		virtual bool						operator^=(const Result& rhs) = 0;


		// == Functions.
		/**
		 * Creates an evaluator result that references this object.
		 *
		 * \return				Returns a Result tagged as Object, referencing this instance.
		 **/
		Result								createResult() {
			return Result{ .type = NumericConstant::Object, .value = { .objectVal = this } };
		}

		/**
		 * Creates an evaluator result that references this object.
		 *
		 * \return				Returns a Result tagged as Object, referencing this instance.
		 **/
		Result								createResult() const {
			return Result{ .type = NumericConstant::Object, .value = { .objectVal = const_cast<Object*>(this) } };
		}

		/**
		 * Converts a signed array index into a zero-based linear index.
		 *
		 * \param signedIdx The signed index to translate. Non-negative values index from the beginning; negative values index from the end.
		 * \param actualLen The length of the array.
		 * \return Returns the translated zero-based index on success; InvalidIndex on failure.
		 *
		 * \note Negative indices behave like Python indexing:
		 * - -1 refers to the last element.
		 * - -2 refers to the second-to-last element, etc.
		 * \note If \p signedIdx is out of range for \p actualLen, InvalidIndex is returned.
		 * \note This function also rejects negative values that cannot be safely represented as size_t.
		 */
		static size_t						arrayIndexToLinearIndex(int64_t signedIdx, size_t actualLen) {
			if (signedIdx < 0) {
				signedIdx = -signedIdx - 1;
				if (signedIdx != static_cast<int64_t>(static_cast<size_t>(signedIdx)) || static_cast<size_t>(signedIdx) >= actualLen) {
					return InvalidIndex;
				}
				return static_cast<size_t>(actualLen - 1 - signedIdx);
			}
			
			if (signedIdx != static_cast<int64_t>(static_cast<size_t>(signedIdx)) || static_cast<size_t>(signedIdx) >= actualLen) {
				return InvalidIndex;
			}
			
			return static_cast<size_t>(signedIdx);
		}

	protected :
		// == Members.
		ExecutionContext*					context;

	private :
	};

}	// namespace ve
