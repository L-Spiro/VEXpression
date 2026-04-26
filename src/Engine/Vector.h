#pragma once

#include "ExecutionContext.h"
#include "Object.h"
#include "../Engine/Result.h"

#include <vector>

namespace ve {

	/**
	 * A flexible array container based on Python's list and C++'s std::vector.
	 **/
	class Vector : public Object {
	public :
		Vector(ExecutionContext* ctx) : Object(ctx) {}


		// == Functions.
		/**
		 * Returns the type identifier for built-in vectors.
		 *
		 * \return				Returns BuiltInType_Vector.
		 **/
		virtual uint32_t					type() const override {
			return Object::type() | BuiltInType_Vector;
		}

		/**
		 * Converts the vector into a string representation.
		 * Must be called within a try/catch block.
		 *
		 * \param outStr		The string to populate with the result.
		 * \param depth			The recursion depth for stringifying nested objects (defaults to 1).
		 * \param flags			Bitmask defining formatting rules (defaults to 0).
		 * \return				Returns true on success, false on error.
		 **/
		virtual bool						toString(std::string& outStr, uint32_t depth = 1, uint32_t flags = 0) const override;

		/**
		 * Creates a formatted string representation of the vector.
		 * Must be called within a try/catch block.
		 *
		 * \param formatStr		The format string to apply to each element.
		 * \param flags			Bitmask defining formatting rules (defaults to 0).
		 * \return				Returns a string containing the formatted elements.
		 **/
		virtual std::string					formattedString(const std::string& formatStr, uint32_t flags = 0) const override;

		/**
		 * Converts the object to a fundamental numeric constant type if possible.
		 *
		 * \param targetType	The target numeric type to convert to.
		 * \return				Returns a Result containing the converted value, or an error state if invalid.
		 **/
		virtual Result						convertTo(NumericConstant targetType) const override;

		/**
		 * Initializes the internal state of the object using a raw Result value.
		 *
		 * \param val			The Result value to initialize from.
		 * \return				Returns true if initialization was successful, false otherwise.
		 **/
		virtual bool						initializeFrom(const Result& val) override;

		/**
		 * Converts the object from its internal encoding to ASCII.
		 * Characters outside the 0-127 range are replaced with '?'.
		 *
		 * \return				Returns a Result containing the new ASCII string object.
		 **/
		virtual Result						ascii() const override { return Result{ .type = NumericConstant::Invalid }; }

		/**
		 * Gets the binary form of the object as a string.
		 * Invalid for string objects; requires an integer.
		 *
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						bin() const override { return Result{ .type = NumericConstant::Invalid }; }

		/**
		 * Gets the boolean representation of the object as a string ("True" or "False").
		 * Invalid for strings in this context.
		 *
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						toBool() const override { return Result{ .type = NumericConstant::Invalid }; }

		/**
		 * Returns the character represented by the object as a Unicode code point.
		 * Invalid for string objects; requires an integer.
		 *
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						chr() const override { return Result{ .type = NumericConstant::Invalid }; }

		/**
		 * Interprets the object as its best-fit numeric representation and converts it to a float.
		 * Matches typical user expectations by parsing the string as a floating-point number.
		 *
		 * \return				Returns a Result containing the converted double-precision floating-point value, or invalid if parsing fails.
		 **/
		virtual Result						toFloat() const override { return Result{ .type = NumericConstant::Invalid }; }

		/**
		 * Gets the hexadecimal form of the object as a string.
		 * Invalid for string objects; requires an integer.
		 *
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						hex() const override { return Result{ .type = NumericConstant::Invalid }; }

		/**
		 * Gets the octal form of the object as a string.
		 * Invalid for string objects; requires an integer.
		 *
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						oct() const override { return Result{ .type = NumericConstant::Invalid }; }

		/**
		 * Interprets the object as its best-fit numeric representation and converts it to an integer.
		 *
		 * \return				Returns a Result containing the converted 64-bit integer value, or invalid if parsing fails.
		 **/
		virtual Result						toInt() const override { return Result{ .type = NumericConstant::Invalid };
		}

		/**
		 * Gets the number of elements or characters in the object.
		 *
		 * \return				Returns a Result containing the UTF code point count.
		 **/
		virtual Result						len() const override {
			return Result{ .type = NumericConstant::Unsigned, .value = { .uintVal = static_cast<uint64_t>(elements.size()) } };
		}

		/**
		 * Returns the ordinal (numeric) value of the object as a Unicode code point.
		 * Matches Python's ord(str): requires a string of exactly length 1.
		 *
		 * \return				Returns a Result containing the ordinal value as an unsigned integer, or invalid if length != 1.
		 **/
		virtual Result						ord() const override { return Result{ .type = NumericConstant::Invalid }; }

		/**
		 * Retrieves the number of elements in the vector.
		 *
		 * \return				Returns the element count.
		 **/
		virtual size_t						arrayLength() const override { return elements.size(); }


		// == Operators.

		/**
		 * Evaluates the equality comparison operation against a right-hand operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the boolean evaluation.
		 **/
		virtual Result						operator==(const Result& rhs) const override;

		/**
		 * Evaluates the inequality comparison operation against a right-hand operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the boolean evaluation.
		 **/
		virtual Result						operator!=(const Result& rhs) const override;

		/**
		 * Evaluates the less-than comparison operation against a right-hand operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the boolean evaluation.
		 **/
		virtual Result						operator<(const Result& rhs) const override;

		/**
		 * Evaluates the greater-than comparison operation against a right-hand operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the boolean evaluation.
		 **/
		virtual Result						operator>(const Result& rhs) const override;

		/**
		 * Evaluates the less-than-or-equal comparison operation against a right-hand operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the boolean evaluation.
		 **/
		virtual Result						operator<=(const Result& rhs) const override;

		/**
		 * Evaluates the greater-than-or-equal comparison operation against a right-hand operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the boolean evaluation.
		 **/
		virtual Result						operator>=(const Result& rhs) const override;
		
		/**
		 * Evaluates the addition operation against a right-hand operand.
		 * 
		 * If the right-hand operand is a Vector, the two vectors are concatenated.
		 * Otherwise, the addition operation is applied element-wise against the operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the new resulting Vector.
		 **/
		virtual Result						operator+(const Result& rhs) const override;

		/**
		 * Evaluates the subtraction operation against a right-hand operand.
		 * 
		 * The subtraction operation is applied element-wise against the operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the new resulting Vector.
		 **/
		virtual Result						operator-(const Result& rhs) const override;

		/**
		 * Evaluates the multiplication operation against a right-hand operand.
		 * 
		 * The multiplication operation is applied element-wise against the operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the new resulting Vector.
		 **/
		virtual Result						operator*(const Result& rhs) const override;

		/**
		 * Evaluates the division operation against a right-hand operand.
		 * 
		 * The division operation is applied element-wise against the operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the new resulting Vector.
		 **/
		virtual Result						operator/(const Result& rhs) const override;

		/**
		 * Evaluates the modulo operation against a right-hand operand.
		 * 
		 * The modulo operation is applied element-wise against the operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the new resulting Vector.
		 **/
		virtual Result						operator%(const Result& rhs) const override;

		/**
		 * Evaluates the bitwise AND operation against a right-hand operand.
		 * 
		 * The bitwise AND operation is applied element-wise against the operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the new resulting Vector.
		 **/
		virtual Result						operator&(const Result& rhs) const override;

		/**
		 * Evaluates the bitwise OR operation against a right-hand operand.
		 * 
		 * The bitwise OR operation is applied element-wise against the operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the new resulting Vector.
		 **/
		virtual Result						operator|(const Result& rhs) const override;

		/**
		 * Evaluates the bitwise XOR operation against a right-hand operand.
		 * 
		 * The bitwise XOR operation is applied element-wise against the operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the new resulting Vector.
		 **/
		virtual Result						operator^(const Result& rhs) const override;

		/**
		 * Evaluates the bitwise shift-left operation against a right-hand operand.
		 * 
		 * The shift-left operation is applied element-wise against the operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the new resulting Vector.
		 **/
		virtual Result						operator<<(const Result& rhs) const override;

		/**
		 * Evaluates the bitwise shift-right operation against a right-hand operand.
		 * 
		 * The shift-right operation is applied element-wise against the operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the new resulting Vector.
		 **/
		virtual Result						operator>>(const Result& rhs) const override;


		// == Assignment Operators
		/**
		 * Evaluates the addition-assignment operation and updates the object's state.
		 *
		 * \param rhs			The right-hand side operand to add.
		 * \return				Returns true if the assignment was successful, false otherwise.
		 **/
		virtual Result						operator+=(const Result& rhs) override;

		/**
		 * Evaluates the compound subtraction assignment operation against a right-hand operand.
		 * 
		 * The subtraction operation is applied element-wise against the operand, modifying this vector in-place.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing this vector after modification.
		 **/
		virtual Result						operator-=(const Result& rhs) override;

		/**
		 * Evaluates the compound multiplication assignment operation against a right-hand operand.
		 * 
		 * The multiplication operation is applied element-wise against the operand, modifying this vector in-place.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing this vector after modification.
		 **/
		virtual Result						operator*=(const Result& rhs) override;

		/**
		 * Evaluates the compound division assignment operation against a right-hand operand.
		 * 
		 * The division operation is applied element-wise against the operand, modifying this vector in-place.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing this vector after modification.
		 **/
		virtual Result						operator/=(const Result& rhs) override;

		/**
		 * Evaluates the compound modulo assignment operation against a right-hand operand.
		 * 
		 * The modulo operation is applied element-wise against the operand, modifying this vector in-place.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing this vector after modification.
		 **/
		virtual Result						operator%=(const Result& rhs) override;

		/**
		 * Evaluates the compound bitwise AND assignment operation against a right-hand operand.
		 * 
		 * The bitwise AND operation is applied element-wise against the operand, modifying this vector in-place.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing this vector after modification.
		 **/
		virtual Result						operator&=(const Result& rhs) override;

		/**
		 * Evaluates the compound bitwise OR assignment operation against a right-hand operand.
		 * 
		 * The bitwise OR operation is applied element-wise against the operand, modifying this vector in-place.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing this vector after modification.
		 **/
		virtual Result						operator|=(const Result& rhs) override;

		/**
		 * Evaluates the compound bitwise XOR assignment operation against a right-hand operand.
		 * 
		 * The bitwise XOR operation is applied element-wise against the operand, modifying this vector in-place.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing this vector after modification.
		 **/
		virtual Result						operator^=(const Result& rhs) override;

		/**
		 * Evaluates the compound bitwise shift-left assignment operation against a right-hand operand.
		 * 
		 * The shift-left operation is applied element-wise against the operand, modifying this vector in-place.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing this vector after modification.
		 **/
		virtual Result						operator<<=(const Result& rhs) override;

		/**
		 * Evaluates the compound bitwise shift-right assignment operation against a right-hand operand.
		 * 
		 * The shift-right operation is applied element-wise against the operand, modifying this vector in-place.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing this vector after modification.
		 **/
		virtual Result						operator>>=(const Result& rhs) override;


		// == Functions.
		/**
		 * Retrieves an element at the specified index.
		 * 
		 * \param index			The zero-based or negative offset index.
		 * \return				Returns the Result at the given index.
		 **/
		virtual Result						arrayAccess(int64_t index) override;

		/**
		 * Retrieves a sliced sub-vector based on start and end boundaries.
		 * 
		 * \param startIdx		The starting index of the slice.
		 * \param endIdx		The ending index of the slice.
		 * \param flags			Bitmask defining slice boundary rules.
		 * \return				Returns a Result containing the sliced Vector.
		 **/
		virtual Result						arrayAccessEx(int64_t startIdx, int64_t endIdx, uint32_t flags) override;

		/**
		 * Assigns a value directly to a specified index, modifying the vector in-place.
		 *
		 * \param index			The zero-based or negative offset index.
		 * \param rhs			The result to insert or overwrite with.
		 * \return				Returns the assigned value on success, or Invalid on failure.
		 **/
		virtual Result						arrayAssign(int64_t index, const Result& rhs) override;

		/**
		 * Assigns a value or merges an array into a sliced range, modifying the vector in-place.
		 *
		 * \param startIdx		The starting index of the slice.
		 * \param endIdx		The ending index of the slice.
		 * \param flags			Bitmask defining slice boundary rules.
		 * \param rhs			The result to insert or overwrite with.
		 * \return				Returns the assigned value on success, or Invalid on failure.
		 **/
		virtual Result						arrayAssignEx(int64_t startIdx, int64_t endIdx, uint32_t flags, const Result& rhs) override;

		/**
		 * Retrieves the element at the specified index.
		 *
		 * \param index			The zero-based or negative offset index.
		 * \return				Returns the Result at the given index, or Invalid if out of bounds.
		 **/
		Result								at(int64_t index) const;

		/**
		 * Pushes an expression to the back of the vector.
		 * 
		 * \param result		The result to push.
		 * \return				Returns true if the item was added.  False always indicates a memory failure.
		 **/
		inline bool							pushBack(const Result &result ) {
			try {
				elements.push_back(result);
				return true;
			}
			catch (...) { return false; }
		}

		/**
		 * Converts the internal vector to a standard C++ vector of primitives.
		 * 
		 * \tparam T			The standard C++ primitive type to convert the elements into.
		 * \tparam targetType	The internal NumericConstant type to cast the elements to before conversion.
		 * \param outVec		The standard array to fill with the converted values.
		 * \return				Returns true if the array was allocated and all values were successfully cast to the target type.
		 **/
		template <typename T, NumericConstant targetType>
		bool								toPrimitiveArray(std::vector<T>& outVec) const {
			try {
				if (elements.empty()) {
					outVec.clear();
					return true;
				}
				
				outVec.resize(elements.size());
				
				for (size_t i = elements.size(); i--; ) {
					Result tempResult = context->convertResult(elements[i], targetType);
					
					if (tempResult.type != targetType) { return false; }
					
					if constexpr (targetType == NumericConstant::Signed) { outVec[i] = static_cast<T>(tempResult.value.intVal); }
					else if constexpr (targetType == NumericConstant::Unsigned) { outVec[i] = static_cast<T>(tempResult.value.uintVal); }
					else if constexpr (targetType == NumericConstant::Floating) { outVec[i] = static_cast<T>(tempResult.value.doubleVal); }
				}
			}
			catch (...) { return false;  }
			
			return true;
		}

		/**
		 * Populates the internal vector based on a standard C++ vector of primitives.
		 * 
		 * \tparam T			The standard C++ primitive type of the incoming vector elements.
		 * \param inVec			The array of primitives to be used to fill this vector.
		 * \return				Returns true if this vector was successfully sized and populated.
		 **/
		template <typename T>
		bool								fromPrimitiveArray(const std::vector<T>& array) {
			try {
				if (!array.size()) {
					elements.clear();
					return true;
				}
				elements.resize(array.size());
				for (size_t i = 0; i < array.size(); ++i) {
					elements[i] = Result::make<T>(array[i]);
				}
				return true;
			}
			catch (...) { return false; }
		}

	protected :
		// == Members.
		std::vector<Result>					elements;
	};

}	// namespace ve
