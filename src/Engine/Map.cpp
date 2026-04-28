#include "Map.h"
#include "String.h"

namespace ve {
	
	// == Types.
	/**
	 * Evaluates whether the left-hand Result is strictly less than the right-hand Result.
	 *
	 * \param a			The left-hand Result.
	 * \param b			The right-hand Result.
	 * \return			Returns true if a is strictly less than b.
	 **/
	bool ResultCompare::operator()(const Result& a, const Result& b) const {
		if (a.type != b.type) {
			return a.type < b.type;
		}

		switch (a.type) {
			case NumericConstant::Signed : { return a.value.intVal < b.value.intVal; }
			case NumericConstant::Unsigned : { return a.value.uintVal < b.value.uintVal; }
			case NumericConstant::Floating : { return a.value.doubleVal < b.value.doubleVal; }
			case NumericConstant::Object : {
				if (a.value.objectVal == b.value.objectVal) { return false; }

				if (!a.value.objectVal || !b.value.objectVal) { return a.value.objectVal < b.value.objectVal; }

				if ((a.value.objectVal->type() & BuiltInType_String) && (b.value.objectVal->type() & BuiltInType_String)) {
					const String* strA = static_cast<const String*>(a.value.objectVal);
					const String* strB = static_cast<const String*>(b.value.objectVal);
					return strA->compareString(strB) < 0;
				}

				return a.value.objectVal < b.value.objectVal;
			}
			default : {
				return false;
			}
		}
	}

	Map::~Map() {
		for (auto& pair : internalMap) {
			if (pair.first.type == NumericConstant::Object && pair.first.value.objectVal) {
				pair.first.value.objectVal->decRef();
				if (!pair.first.value.objectVal->getRef()) {
					context->deallocateObject(pair.first.value.objectVal);
				}
			}
			if (pair.second.type == NumericConstant::Object && pair.second.value.objectVal) {
				pair.second.value.objectVal->decRef();
				if (!pair.second.value.objectVal->getRef()) {
					context->deallocateObject(pair.second.value.objectVal);
				}
			}
		}
		internalMap.clear();
	}

	// == Functions.
	/**
	 * Inserts or updates a key-value pair in the map.
	 *
	 * \param key		The Result to use as the key.
	 * \param value		The Result to store.
	 **/
	void Map::insert(const Result& key, const Result& value) {
		auto it = internalMap.find(key);
		if (it != internalMap.end()) {
			if (value.type == NumericConstant::Object && value.value.objectVal) {
				value.value.objectVal->incRef();
			}
			if (it->second.type == NumericConstant::Object && it->second.value.objectVal) {
				it->second.value.objectVal->decRef();
				if (!it->second.value.objectVal->getRef()) {
					context->deallocateObject(it->second.value.objectVal);
				}
			}

			
			
			it->second = value;
			return;
		}

		if (value.type == NumericConstant::Object && value.value.objectVal) {
			value.value.objectVal->incRef();
		}
		if (key.type == NumericConstant::Object && key.value.objectVal) {
			key.value.objectVal->incRef();
		}
		

		internalMap.insert({ key, value });
	}

	/**
	 * Serializes the object into a string representation.
	 *
	 * \param returnString	The output parameter where the string representation will be appended.
	 * \param depth			The current recursion depth (used for indenting or catching circular references).
	 * \param flags			Formatting flags dictating how the string should be generated.
	 * \return				Returns true if the object was successfully converted to a string.
	 **/
	bool Map::toString(std::string& returnString, uint32_t depth, uint32_t flags) const {
		if (depth >= 32) {
			returnString = "<...>";
			return true;
		}
		
		try {
			returnString = "{";
			uint32_t elementFlags = flags | ToStringFlags::ToStringFlag_CString;

			bool addedAnything = false;
			for (const auto & i : internalMap ) {
				if (addedAnything) {
					returnString += ", ";
				}
				returnString += context->toString(i.first, depth + 1, elementFlags);
				returnString += ":";
				returnString += context->toString(i.second, depth + 1, elementFlags);
				addedAnything = true;
			}

			returnString += "}";
			return true;
		}
		catch (...) { return false; }
	}

	/**
	 * Converts the object to a fundamental numeric constant type if possible.
	 *
	 * \param targetType	The target numeric type to convert to.
	 * \return				Returns a Result containing the converted value, or an error state if invalid.
	 **/
	Result Map::convertTo(NumericConstant targetType) const {
		return Result{};
	}

	/**
	 * Initializes the internal state of the object using a raw Result value.
	 *
	 * \param val			The Result value to initialize from.
	 * \return				Returns true if initialization was successful, false otherwise.
	 **/
	bool Map::initializeFrom(const Result& val) {
		if (val.type == NumericConstant::Object && val.value.objectVal) {
			if (val.value.objectVal->type() & BuiltInType_Map) {
				for (const auto & i : static_cast<Map*>(val.value.objectVal)->internalMap) {
					setValue(i.first, i.second);
				}
				return true;
			}
		}
		return false;
	}

	/**
	 * Accesses an element within the object using a single index.
	 *
	 * \param idx			The zero-based index of the element to access.
	 * \return				Returns a Result containing the accessed element.
	 **/
	Result Map::arrayAccess(int64_t idx) {
		return get(Result::make(idx));
	}

	/**
	 * Accesses an element or sub-range within the object using complex indexing or slicing.
	 *
	 * \param idx0			The primary index or slice start.
	 * \param idx1			The secondary index or slice end.
	 * \param mask			A bitmask defining the specific access behavior.
	 * \return				Returns a Result containing the accessed element or range.
	 **/
	Result Map::arrayAccessEx(int64_t idx0, int64_t idx1, uint32_t mask) {
		return Result{};
	}

	/**
	 * Retrieves the total number of elements contained in the object.
	 *
	 * \return				Returns the element count as a size_t.
	 **/
	size_t Map::arrayLength() const {
		return internalMap.size();
	}

	/**
	 * Evaluates equality between this object and a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing 1 if equal, 0 if not.
	 **/
	Result Map::operator==(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates inequality between this object and a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing 1 if not equal, 0 if equal.
	 **/
	Result Map::operator!=(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates strictly-less-than comparison between this object and a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing 1 if less, 0 otherwise.
	 **/
	Result Map::operator<(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates strictly-greater-than comparison between this object and a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing 1 if greater, 0 otherwise.
	 **/
	Result Map::operator>(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates less-than-or-equal comparison between this object and a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing 1 if less or equal, 0 otherwise.
	 **/
	Result Map::operator<=(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates greater-than-or-equal comparison between this object and a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing 1 if greater or equal, 0 otherwise.
	 **/
	Result Map::operator>=(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates the addition operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the computed sum.
	 **/
	Result Map::operator+(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates the subtraction operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the computed difference.
	 **/
	Result Map::operator-(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates the multiplication operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the computed product.
	 **/
	Result Map::operator*(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates the division operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the computed quotient.
	 **/
	Result Map::operator/(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates the modulo operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the computed remainder.
	 **/
	Result Map::operator%(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates the bitwise left-shift operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand indicating the shift amount.
	 * \return				Returns a Result containing the shifted value.
	 **/
	Result Map::operator<<(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates the bitwise right-shift operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand indicating the shift amount.
	 * \return				Returns a Result containing the shifted value.
	 **/
	Result Map::operator>>(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates the bitwise AND operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the computed bitwise AND.
	 **/
	Result Map::operator&(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates the bitwise OR operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the computed bitwise OR.
	 **/
	Result Map::operator|(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates the bitwise XOR operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the computed bitwise XOR.
	 **/
	Result Map::operator^(const Result& rhs) const {
		return Result{};
	}

	/**
	 * Evaluates the compound addition assignment operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the modified Object.
	 **/
	Result Map::operator+=(const Result& rhs) {
		return Result{};
	}

	/**
	 * Evaluates the compound subtraction assignment operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the modified Object.
	 **/
	Result Map::operator-=(const Result& rhs) {
		return Result{};
	}

	/**
	 * Evaluates the compound multiplication assignment operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the modified Object.
	 **/
	Result Map::operator*=(const Result& rhs) {
		return Result{};
	}

	/**
	 * Evaluates the compound division assignment operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the modified Object.
	 **/
	Result Map::operator/=(const Result& rhs) {
		return Result{};
	}

	/**
	 * Evaluates the compound modulo assignment operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the modified Object.
	 **/
	Result Map::operator%=(const Result& rhs) {
		return Result{};
	}

	/**
	 * Evaluates the compound bitwise AND assignment operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the modified Object.
	 **/
	Result Map::operator&=(const Result& rhs) {
		return Result{};
	}

	/**
	 * Evaluates the compound bitwise OR assignment operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the modified Object.
	 **/
	Result Map::operator|=(const Result& rhs) {
		return Result{};
	}

	/**
	 * Evaluates the compound bitwise XOR assignment operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the modified Object.
	 **/
	Result Map::operator^=(const Result& rhs) {
		return Result{};
	}

	/**
	 * Evaluates the compound bitwise shift left assignment operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the modified Object.
	 **/
	Result Map::operator<<=(const Result& rhs) {
		return Result{};
	}

	/**
	 * Evaluates the compound bitwise shift right assignment operation against a right-hand operand.
	 *
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the modified Object.
	 **/
	Result Map::operator>>=(const Result& rhs) {
		return Result{};
	}

	// == Functions.
	/**
	 * Inserts or updates a key-value pair in the map.
	 * Manages reference counting and object deallocation for replaced values.
	 *
	 * \param key		The Result to use as the key.
	 * \param value		The Result to store.
	 **/
	void Map::setValue(const Result& key, const Result& value) {
		auto it = internalMap.find(key);
		if (it != internalMap.end()) {
			if (it->second.type == NumericConstant::Object && it->second.value.objectVal) {
				it->second.value.objectVal->decRef();
				if (!it->second.value.objectVal->getRef()) {
					context->deallocateObject(it->second.value.objectVal);
				}
			}
				
			if (value.type == NumericConstant::Object && value.value.objectVal) {
				value.value.objectVal->incRef();
			}
				
			it->second = value;
			return;
		}

		if (key.type == NumericConstant::Object && key.value.objectVal) {
			key.value.objectVal->incRef();
		}
		if (value.type == NumericConstant::Object && value.value.objectVal) {
			value.value.objectVal->incRef();
		}

		internalMap.insert({ key, value });
	}

}	// namespace ve
