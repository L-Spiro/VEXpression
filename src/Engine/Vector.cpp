#include "../generated/ExprLexer.h"
#include "Vector.h"


namespace ve {

	Vector::~Vector() {
		for (size_t i = 0; i < elements.size(); ++i) {
			prepareErase_Unsafe(i);
		}
		elements.clear();
	}

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
		catch (...) {}
		
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
				for (size_t i = 0; i < elements.size(); ++i) {
					prepareErase_Unsafe(i);
				}
				elements = reinterpret_cast<Vector*>(val.value.objectVal)->elements;
				for (size_t i = 0; i < elements.size(); ++i) {
					incObjectRef_Unsafe(i);
				}
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
		return Result{};
	}

	/**
	 * Evaluates the inequality comparison operation against a right-hand operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the boolean evaluation.
	 **/
	Result Vector::operator!=(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates the less-than comparison operation against a right-hand operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the boolean evaluation.
	 **/
	Result Vector::operator<(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates the greater-than comparison operation against a right-hand operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the boolean evaluation.
	 **/
	Result Vector::operator>(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates the less-than-or-equal comparison operation against a right-hand operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the boolean evaluation.
	 **/
	Result Vector::operator<=(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates the greater-than-or-equal comparison operation against a right-hand operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the boolean evaluation.
	 **/
	Result Vector::operator>=(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates the addition operation against a right-hand operand.
	 * 
	 * If the right-hand operand is a Vector, the two vectors are concatenated.
	 * Otherwise, the addition operation is applied element-wise against the operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the new resulting Vector.
	 **/
	Result Vector::operator+(const Result& rhs) const {
		Vector* newVec = context->allocateObject<Vector>();
		if (!newVec) { return Result{}; }

		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			newVec->elements.reserve(elements.size() + rVec->elements.size());
			newVec->elements.insert(newVec->elements.end(), elements.begin(), elements.end());
			newVec->elements.insert(newVec->elements.end(), rVec->elements.begin(), rVec->elements.end());
		} 
		else {
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->elements.push_back(context->evaluateMath(elements[i], rhs, ExprLexer::ADD));
			}
		}

		for (size_t i = 0; i < newVec->elements.size(); ++i) {
			newVec->incObjectRef_Unsafe(i);
		}

		return newVec->createResult();
	}

	/**
	 * Evaluates the subtraction operation against a right-hand operand.
	 * 
	 * The subtraction operation is applied element-wise against the operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the new resulting Vector.
	 **/
	Result Vector::operator-(const Result& rhs) const {
		Vector* newVec = context->allocateObject<Vector>();
		if (!newVec) { return Result{}; }

		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::SUB));
			}
		} 
		else {
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rhs, ExprLexer::SUB));
			}
		}

		return newVec->createResult();
	}

	/**
	 * Evaluates the multiplication operation against a right-hand operand.
	 * 
	 * The multiplication operation is applied element-wise against the operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the new resulting Vector.
	 **/
	Result Vector::operator*(const Result& rhs) const {
		Vector* newVec = context->allocateObject<Vector>();
		if (!newVec) { return Result{}; }

		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::MUL));
			}
		} 
		else {
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rhs, ExprLexer::MUL));
			}
		}

		return newVec->createResult();
	}

	/**
	 * Evaluates the division operation against a right-hand operand.
	 * 
	 * The division operation is applied element-wise against the operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the new resulting Vector.
	 **/
	Result Vector::operator/(const Result& rhs) const {
		Vector* newVec = context->allocateObject<Vector>();
		if (!newVec) { return Result{}; }

		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::DIV));
			}
		} 
		else {
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rhs, ExprLexer::DIV));
			}
		}

		return newVec->createResult();
	}

	/**
	 * Evaluates the modulo operation against a right-hand operand.
	 * 
	 * The modulo operation is applied element-wise against the operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the new resulting Vector.
	 **/
	Result Vector::operator%(const Result& rhs) const {
		Vector* newVec = context->allocateObject<Vector>();
		if (!newVec) { return Result{}; }

		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::MOD));
			}
		} 
		else {
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rhs, ExprLexer::MOD));
			}
		}

		return newVec->createResult();
	}

	/**
	 * Evaluates the bitwise AND operation against a right-hand operand.
	 * 
	 * The bitwise AND operation is applied element-wise against the operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the new resulting Vector.
	 **/
	Result Vector::operator&(const Result& rhs) const {
		Vector* newVec = context->allocateObject<Vector>();
		if (!newVec) { return Result{}; }

		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::BIT_AND));
			}
		} 
		else {
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rhs, ExprLexer::BIT_AND));
			}
		}

		return newVec->createResult();
	}

	/**
	 * Evaluates the bitwise OR operation against a right-hand operand.
	 * 
	 * The bitwise OR operation is applied element-wise against the operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the new resulting Vector.
	 **/
	Result Vector::operator|(const Result& rhs) const {
		Vector* newVec = context->allocateObject<Vector>();
		if (!newVec) { return Result{}; }

		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::BIT_OR));
			}
		} 
		else {
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rhs, ExprLexer::BIT_OR));
			}
		}

		return newVec->createResult();
	}

	/**
	 * Evaluates the bitwise XOR operation against a right-hand operand.
	 * 
	 * The bitwise XOR operation is applied element-wise against the operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the new resulting Vector.
	 **/
	Result Vector::operator^(const Result& rhs) const {
		Vector* newVec = context->allocateObject<Vector>();
		if (!newVec) { return Result{}; }

		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::BIT_XOR));
			}
		} 
		else {
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rhs, ExprLexer::BIT_XOR));
			}
		}

		return newVec->createResult();
	}

	/**
	 * Evaluates the bitwise shift-left operation against a right-hand operand.
	 * 
	 * The shift-left operation is applied element-wise against the operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the new resulting Vector.
	 **/
	Result Vector::operator<<(const Result& rhs) const {
		Vector* newVec = context->allocateObject<Vector>();
		if (!newVec) { return Result{}; }

		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::SHL));
			}
		} 
		else {
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rhs, ExprLexer::SHL));
			}
		}

		return newVec->createResult();
	}

	/**
	 * Evaluates the bitwise shift-right operation against a right-hand operand.
	 * 
	 * The shift-right operation is applied element-wise against the operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the new resulting Vector.
	 **/
	Result Vector::operator>>(const Result& rhs) const {
		Vector* newVec = context->allocateObject<Vector>();
		if (!newVec) { return Result{}; }

		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::SHR));
			}
		} 
		else {
			newVec->elements.reserve(elements.size());
			for (size_t i = 0; i < elements.size(); ++i) {
				newVec->pushBack(context->evaluateMath(elements[i], rhs, ExprLexer::SHR));
			}
		}

		return newVec->createResult();
	}


	// == Assignment Operators
	/**
	 * Evaluates the addition-assignment operation and updates the object's state.
	 *
	 * \param rhs			The right-hand side operand to add.
	 * \return				Returns true if the assignment was successful, false otherwise.
	 **/
	Result Vector::operator+=(const Result& rhs) {
		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			elements.reserve(elements.size() + rVec->elements.size());
			for (size_t i = 0; i < rVec->elements.size(); ++i) {
				pushBack(rVec->elements[i]);
			}
			return createResult();
		}
		pushBack(rhs);
		return createResult();
	}

	/**
	 * Evaluates the compound subtraction assignment operation against a right-hand operand.
	 * 
	 * The subtraction operation is applied element-wise against the operand, modifying this vector in-place.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing this vector after modification.
	 **/
	Result Vector::operator-=(const Result& rhs) {
		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::SUB_ASSIGN));
			}
		}
		else {
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rhs, ExprLexer::SUB_ASSIGN));
			}
		}
		return createResult();
	}

	/**
	 * Evaluates the compound multiplication assignment operation against a right-hand operand.
	 * 
	 * The multiplication operation is applied element-wise against the operand, modifying this vector in-place.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing this vector after modification.
	 **/
	Result Vector::operator*=(const Result& rhs) {
		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::MUL_ASSIGN));
			}
		}
		else {
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rhs, ExprLexer::MUL_ASSIGN));
			}
		}
		return createResult();
	}

	/**
	 * Evaluates the compound division assignment operation against a right-hand operand.
	 * 
	 * The division operation is applied element-wise against the operand, modifying this vector in-place.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing this vector after modification.
	 **/
	Result Vector::operator/=(const Result& rhs) {
		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::DIV_ASSIGN));
			}
		}
		else {
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rhs, ExprLexer::DIV_ASSIGN));
			}
		}
		return createResult();
	}

	/**
	 * Evaluates the compound modulo assignment operation against a right-hand operand.
	 * 
	 * The modulo operation is applied element-wise against the operand, modifying this vector in-place.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing this vector after modification.
	 **/
	Result Vector::operator%=(const Result& rhs) {
		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::MOD_ASSIGN));
			}
		}
		else {
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rhs, ExprLexer::MOD_ASSIGN));
			}
		}
		return createResult();
	}

	/**
	 * Evaluates the compound bitwise AND assignment operation against a right-hand operand.
	 * 
	 * The bitwise AND operation is applied element-wise against the operand, modifying this vector in-place.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing this vector after modification.
	 **/
	Result Vector::operator&=(const Result& rhs) {
		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::AND_ASSIGN));
			}
		}
		else {
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rhs, ExprLexer::AND_ASSIGN));
			}
		}
		return createResult();
	}

	/**
	 * Evaluates the compound bitwise OR assignment operation against a right-hand operand.
	 * 
	 * The bitwise OR operation is applied element-wise against the operand, modifying this vector in-place.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing this vector after modification.
	 **/
	Result Vector::operator|=(const Result& rhs) {
		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::OR_ASSIGN));
			}
		}
		else {
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rhs, ExprLexer::OR_ASSIGN));
			}
		}
		return createResult();
	}

	/**
	 * Evaluates the compound bitwise XOR assignment operation against a right-hand operand.
	 * 
	 * The bitwise XOR operation is applied element-wise against the operand, modifying this vector in-place.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing this vector after modification.
	 **/
	Result Vector::operator^=(const Result& rhs) {
		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::XOR_ASSIGN));
			}
		}
		else {
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rhs, ExprLexer::XOR_ASSIGN));
			}
		}
		return createResult();
	}

	/**
	 * Evaluates the compound bitwise shift-left assignment operation against a right-hand operand.
	 * 
	 * The shift-left operation is applied element-wise against the operand, modifying this vector in-place.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing this vector after modification.
	 **/
	Result Vector::operator<<=(const Result& rhs) {
		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::SHL_ASSIGN));
			}
		}
		else {
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rhs, ExprLexer::SHL_ASSIGN));
			}
		}
		return createResult();
	}

	/**
	 * Evaluates the compound bitwise shift-right assignment operation against a right-hand operand.
	 * 
	 * The shift-right operation is applied element-wise against the operand, modifying this vector in-place.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing this vector after modification.
	 **/
	Result Vector::operator>>=(const Result& rhs) {
		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			if (rVec->arrayLength() != elements.size()) { return Result{}; }
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rVec->directAccess(i), ExprLexer::SHR_ASSIGN));
			}
		}
		else {
			for (size_t i = 0; i < elements.size(); ++i) {
				setAt_Unsafe(i, context->evaluateMath(elements[i], rhs, ExprLexer::SHR_ASSIGN));
			}
		}
		return createResult();
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
			return Result{};
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
		int64_t idx0 = 0;
		int64_t idx1 = static_cast<int64_t>(elements.size());

		if (flags & ArrayExFlags::ArrayExFlag_Start) {
			size_t lin = arrayIndexToLinearIndex(startIdx, elements.size());
			if (lin != InvalidIndex) {
				idx0 = static_cast<int64_t>(lin);
			}
			else {  return Result{}; }
		}

		if (flags & ArrayExFlags::ArrayExFlag_End) {
			size_t lin = arrayIndexToLinearIndex(endIdx, elements.size());
			if (lin != InvalidIndex) {
				idx1 = static_cast<int64_t>(lin) + 1;
			}
			else { return Result{}; }
		}

		if (idx0 > idx1) { idx0 = idx1; }

		size_t newElemCount = static_cast<size_t>(idx1 - idx0);
		Vector* newVec = context->allocateObject<Vector>();
			
		if (newVec) {
			if (newElemCount > 0) {
				newVec->elements.reserve(newElemCount);
				newVec->elements.insert(newVec->elements.end(), elements.begin() + idx0, elements.begin() + idx1);
			}
			return newVec->createResult();
		}
			
		return Result{};
	}

	/**
	 * Assigns a value directly to a specified index, modifying the vector in-place.
	 *
	 * \param index			The zero-based or negative offset index.
	 * \param rhs			The result to insert or overwrite with.
	 * \return				Returns the assigned value on success, or Invalid on failure.
	 **/
	Result Vector::arrayAssign(int64_t index, const Result& rhs) {
		size_t lin = Object::arrayIndexToLinearIndex(index, elements.size());
		if (lin == Object::InvalidIndex) { return Result{}; }
		
		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			prepareErase_Unsafe(lin);
			elements.erase(elements.begin() + lin);
			elements.insert(elements.begin() + lin, rVec->elements.begin(), rVec->elements.end());
			for (size_t i = 0; i < rVec->elements.size(); ++i ) {
				incObjectRef_Unsafe(i + lin);
			}
		} 
		else {
			setAt_Unsafe(lin, rhs);
		}
		
		return rhs;
	}

	/**
	 * Assigns a value or merges an array into a sliced range, modifying the vector in-place.
	 *
	 * \param startIdx		The starting index of the slice.
	 * \param endIdx		The ending index of the slice.
	 * \param flags			Bitmask defining slice boundary rules.
	 * \param rhs			The result to insert or overwrite with.
	 * \return				Returns the assigned value on success, or Invalid on failure.
	 **/
	Result Vector::arrayAssignEx(int64_t startIdx, int64_t endIdx, uint32_t flags, const Result& rhs) {
		size_t idx0, idx1;
		if (!Object::resolveSliceBounds(startIdx, endIdx, flags, elements.size(), idx0, idx1)) {
			return Result{};
		}

		for (size_t i = idx0; i < idx1; ++i) {
			prepareErase_Unsafe(i);
		}
		elements.erase(elements.begin() + idx0, elements.begin() + idx1);

		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_Vector)) {
			Vector* rVec = static_cast<Vector*>(rhs.value.objectVal);
			elements.insert(elements.begin() + idx0, rVec->elements.begin(), rVec->elements.end());
			for (size_t i = 0; i < rVec->elements.size(); ++i ) {
				incObjectRef_Unsafe(i + idx0);
			}
		} 
		else {
			// Matches Python's slice insertion rule.
			elements.insert(elements.begin() + idx0, rhs);
			incObjectRef_Unsafe(idx0);
		}
		
		return rhs;
	}

	/**
	 * Retrieves the element at the specified index.
	 *
	 * \param index			The zero-based or negative offset index.
	 * \return				Returns the Result at the given index, or Invalid if out of bounds.
	 **/
	Result Vector::at(int64_t index) const {
		size_t linearIndex = Object::arrayIndexToLinearIndex(index, elements.size());
		
		if (linearIndex == Object::InvalidIndex) { return Result{}; }
		
		return elements[linearIndex];
	}

}	// namespace ve
