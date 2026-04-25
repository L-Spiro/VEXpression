#include "Vector.h"


namespace ve {

	// == Functions.
	/**
	 * Converts the vector into a string representation.
	 * Must be called within a try/catch block.
	 *
	 * \param outStr		The string to populate with the result.
	 * \param depth			The recursion depth for stringifying nested objects (defaults to 1).
	 * \param flags			Bitmask defining formatting rules (defaults to 0).
	 * \return				Returns true on success, false on error.
	 **/
	bool Vector::toString(std::string& outStr, uint32_t depth, uint32_t flags) const {
		if (depth >= 32) {
			outStr = "<...>";
			return true;
		}
		
		try {
			outStr = "{";
			uint32_t elementFlags = flags | ToStringFlags::ToStringFlag_CString;

			for (size_t i = 0; i < elements.size(); ++i) {
				outStr += context->toString(elements[i], depth + 1, elementFlags);
				
				if (i != elements.size() - 1) {
					outStr += ", ";
				}
			}

			outStr += "}";
			return true;
		}
		catch (...) {
			return false;
		}
	}

	/**
	 * Creates a formatted string representation of the vector.
	 * Must be called within a try/catch block.
	 *
	 * \param formatStr		The format string to apply to each element.
	 * \param flags			Bitmask defining formatting rules (defaults to 0).
	 * \return				Returns a string containing the formatted elements.
	 **/
	std::string Vector::formattedString(const std::string& formatStr, uint32_t flags) const {
		std::string ret;
		
		try {
			ret = "{";

			for (size_t i = 0; i < elements.size(); ++i) {
				ret += context->formattedString(elements[i], formatStr, flags);
				
				if (i != elements.size() - 1) {
					ret += ", ";
				}
			}

			ret += "}";
		}
		catch (...) {
		}
		
		return ret;
	}

	/**
	 * Converts the object to a fundamental numeric constant type if possible.
	 *
	 * \param targetType	The target numeric type to convert to.
	 * \return				Returns a Result containing the converted value, or an error state if invalid.
	 **/
	Result Vector::convertTo(NumericConstant targetType) const {
		if (elements.size() == 1) {
			return context->convertResult(elements[0], targetType);
		}
		return Result{};
	}

	/**
	 * Initializes the internal state of the object using a raw Result value.
	 *
	 * \param val			The Result value to initialize from.
	 * \return				Returns true if initialization was successful, false otherwise.
	 **/
	bool Vector::initializeFrom(const Result& val) {
		if (val.type == NumericConstant::Object && val.value.objectVal) {
			if (val.value.objectVal->type() & BuiltInType_Vector) {
				elements = reinterpret_cast<Vector*>(val.value.objectVal)->elements;
				return true;
			}
		}
		return false;
	}

	// == Operators.

	/**
	 * Evaluates the equality comparison operation against a right-hand operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the boolean evaluation.
	 **/
	Result Vector::operator==(const Result& rhs) const {
		return Result{ .type = NumericConstant::Invalid };
	}

	/**
	 * Evaluates the inequality comparison operation against a right-hand operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the boolean evaluation.
	 **/
	Result Vector::operator!=(const Result& rhs) const {
		return Result{ .type = NumericConstant::Invalid };
	}

	/**
	 * Evaluates the less-than comparison operation against a right-hand operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the boolean evaluation.
	 **/
	Result Vector::operator<(const Result& rhs) const {
		return Result{ .type = NumericConstant::Invalid };
	}

	/**
	 * Evaluates the greater-than comparison operation against a right-hand operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the boolean evaluation.
	 **/
	Result Vector::operator>(const Result& rhs) const {
		return Result{ .type = NumericConstant::Invalid };
	}

	/**
	 * Evaluates the less-than-or-equal comparison operation against a right-hand operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the boolean evaluation.
	 **/
	Result Vector::operator<=(const Result& rhs) const {
		return Result{ .type = NumericConstant::Invalid };
	}

	/**
	 * Evaluates the greater-than-or-equal comparison operation against a right-hand operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the boolean evaluation.
	 **/
	Result Vector::operator>=(const Result& rhs) const {
		return Result{ .type = NumericConstant::Invalid };
	}

	/**
	 * Evaluates the addition (concatenation) operation against a right-hand operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the concatenated Vector.
	 **/
	Result Vector::operator+(const Result& rhs) const {
		return Result{ .type = NumericConstant::Invalid };
	}

	/**
	 * Evaluates the subtraction operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the computed difference.
	 **/
	Result Vector::operator-(const Result& rhs) const {
		return Result{ .type = NumericConstant::Invalid };
	}

	/**
	 * Evaluates the multiplication (repetition) operation against a right-hand operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the repeated Vector.
	 **/
	Result Vector::operator*(const Result& rhs) const {
		return Result{ .type = NumericConstant::Invalid };
	}

	/**
	 * Evaluates the division operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the computed quotient.
	 **/
	Result Vector::operator/(const Result& rhs) const {
		return Result{ .type = NumericConstant::Invalid };
	}

	/**
	 * Evaluates the modulo operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the computed remainder.
	 **/
	Result Vector::operator%(const Result& rhs) const {
		return Result{ .type = NumericConstant::Invalid };
	}

	/**
	 * Evaluates the bitwise left-shift operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand indicating the shift amount.
	 * \return				Returns a Result containing the shifted value.
	 **/
	Result Vector::operator<<(const Result& rhs) const {
		return Result{ .type = NumericConstant::Invalid };
	}

	/**
	 * Evaluates the bitwise right-shift operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand indicating the shift amount.
	 * \return				Returns a Result containing the shifted value.
	 **/
	Result Vector::operator>>(const Result& rhs) const {
		return Result{ .type = NumericConstant::Invalid };
	}

	/**
	 * Evaluates the bitwise AND operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the computed bitwise AND.
	 **/
	Result Vector::operator&(const Result& rhs) const {
		return Result{ .type = NumericConstant::Invalid };
	}

	/**
	 * Evaluates the bitwise OR operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the computed bitwise OR.
	 **/
	Result Vector::operator|(const Result& rhs) const {
		return Result{ .type = NumericConstant::Invalid };
	}

	/**
	 * Evaluates the bitwise XOR operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the computed bitwise XOR.
	 **/
	Result Vector::operator^(const Result& rhs) const {
		return Result{ .type = NumericConstant::Invalid };
	}


	// == Assignment Operators
	/**
	 * Evaluates the addition-assignment operation and updates the object's state.
	 *
	 * \param rhs			The right-hand side operand to add.
	 * \return				Returns true if the assignment was successful, false otherwise.
	 **/
	bool Vector::operator+=(const Result& rhs) {
		return false;
	}

	/**
	 * Evaluates the subtraction-assignment operation and updates the object's state.
	 *
	 * \param rhs			The right-hand side operand to subtract.
	 * \return				Returns true if the assignment was successful, false otherwise.
	 **/
	bool Vector::operator-=(const Result& rhs) {
		return false;
	}

	/**
	 * Evaluates the multiplication-assignment operation and updates the object's state.
	 *
	 * \param rhs			The right-hand side operand to multiply.
	 * \return				Returns true if the assignment was successful, false otherwise.
	 **/
	bool Vector::operator*=(const Result& rhs) {
		return false;
	}

	/**
	 * Evaluates the division-assignment operation and updates the object's state.
	 *
	 * \param rhs			The right-hand side operand to divide by.
	 * \return				Returns true if the assignment was successful, false otherwise.
	 **/
	bool Vector::operator/=(const Result& rhs) {
		return false;
	}

	/**
	 * Evaluates the modulo-assignment operation and updates the object's state.
	 *
	 * \param rhs			The right-hand side operand to divide by for the remainder.
	 * \return				Returns true if the assignment was successful, false otherwise.
	 **/
	bool Vector::operator%=(const Result& rhs) {
		return false;
	}

	/**
	 * Evaluates the bitwise left-shift-assignment operation and updates the object's state.
	 *
	 * \param rhs			The right-hand side operand indicating the shift amount.
	 * \return				Returns true if the assignment was successful, false otherwise.
	 **/
	bool Vector::operator<<=(const Result& rhs) {
		return false;
	}

	/**
	 * Evaluates the bitwise right-shift-assignment operation and updates the object's state.
	 *
	 * \param rhs			The right-hand side operand indicating the shift amount.
	 * \return				Returns true if the assignment was successful, false otherwise.
	 **/
	bool Vector::operator>>=(const Result& rhs) {
		return false;
	}

	/**
	 * Evaluates the bitwise AND-assignment operation and updates the object's state.
	 *
	 * \param rhs			The right-hand side operand to bitwise AND with.
	 * \return				Returns true if the assignment was successful, false otherwise.
	 **/
	bool Vector::operator&=(const Result& rhs) {
		return false;
	}

	/**
	 * Evaluates the bitwise OR-assignment operation and updates the object's state.
	 *
	 * \param rhs			The right-hand side operand to bitwise OR with.
	 * \return				Returns true if the assignment was successful, false otherwise.
	 **/
	bool Vector::operator|=(const Result& rhs) {
		return false;
	}

	/**
	 * Evaluates the bitwise XOR-assignment operation and updates the object's state.
	 *
	 * \param rhs			The right-hand side operand to bitwise XOR with.
	 * \return				Returns true if the assignment was successful, false otherwise.
	 **/
	bool Vector::operator^=(const Result& rhs) {
		return false;
	}

	/**
	 * Retrieves an element at the specified index.
	 * 
	 * \param index			The zero-based or negative offset index.
	 * \return				Returns the Result at the given index.
	 **/
	Result Vector::arrayAccess(int64_t index) {
		size_t linearIdx = arrayIndexToLinearIndex(index, elements.size());
		if (linearIdx == InvalidIndex) {
			return Result{ .type = NumericConstant::Invalid };
		}
		return elements[linearIdx];
	}

	/**
	 * Retrieves a sliced sub-vector based on start and end boundaries.
	 * 
	 * \param startIdx		The starting index of the slice.
	 * \param endIdx		The ending index of the slice.
	 * \param flags			Bitmask defining slice boundary rules.
	 * \return				Returns a Result containing the sliced Vector.
	 **/
	Result Vector::arrayAccessEx(int64_t startIdx, int64_t endIdx, uint32_t flags) {
		return Result{ .type = NumericConstant::Invalid };
	}

}	// namespace ve