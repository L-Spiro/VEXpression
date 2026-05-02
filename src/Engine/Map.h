#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "Object.h"

#include <map>

namespace ve {

	class String;

	/**
	 * Comparator for Result objects to establish strict weak ordering.
	 * This allows Result structures to be natively used as keys in std::map.
	 **/
	struct ResultCompare {
		/**
		 * Evaluates whether the left-hand Result is strictly less than the right-hand Result.
		 *
		 * \param a			The left-hand Result.
		 * \param b			The right-hand Result.
		 * \return			Returns true if a is strictly less than b.
		 **/
		bool								operator()(const Result& a, const Result& b) const;
	};

	/**
	 * A flexible key-value dictionary implementation.
	 **/
	class Map : public Object {
	public :
		Map(ExecutionContext* ctx) : Object(ctx) {}
		virtual ~Map();

		/**
		 * Returns the type identifier for built-in maps.
		 *
		 * \return			Returns BuiltInType_Map.
		 **/
		virtual uint32_t					type() const override {
			return Object::type() | BuiltInType_Map;
		}

		/**
		 * Retrieves a value from the map using the given Result as a key.
		 *
		 * \param key		The Result to search for.
		 * \return			Returns the associated Result, or Invalid if the key is not found.
		 **/
		inline Result						get(const Result& key) const { return valueFromKey(key); }

		/**
		 * Inserts or updates a key-value pair in the map.
		 *
		 * \param key		The Result to use as the key.
		 * \param value		The Result to store.
		 **/
		void								insert(const Result& key, const Result& value);

		/**
		 * Serializes the object into a string representation.
		 *
		 * \param returnString	The output parameter where the string representation will be appended.
		 * \param depth			The current recursion depth (used for indenting or catching circular references).
		 * \param flags			Formatting flags dictating how the string should be generated.
		 * \return				Returns true if the object was successfully converted to a string.
		 **/
		virtual bool						toString(std::string& returnString, uint32_t depth, uint32_t flags) const override;

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
		 * Accesses an element within the object using a single index.
		 *
		 * \param idx			The zero-based index of the element to access.
		 * \return				Returns a Result containing the accessed element.
		 **/
		virtual Result						arrayAccess(int64_t idx) override;

		/**
		 * Accesses an element or sub-range within the object using complex indexing or slicing.
		 *
		 * \param idx0			The primary index or slice start.
		 * \param idx1			The secondary index or slice end.
		 * \param mask			A bitmask defining the specific access behavior.
		 * \return				Returns a Result containing the accessed element or range.
		 **/
		virtual Result						arrayAccessEx(int64_t idx0, int64_t idx1, uint32_t mask) override;

		/**
		 * Retrieves the total number of elements contained in the object.
		 *
		 * \return				Returns the element count as a size_t.
		 **/
		virtual size_t						arrayLength() const override;

		/**
		 * Evaluates equality between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if equal, 0 if not.
		 **/
		virtual Result						operator==(const Result& rhs) const override;

		/**
		 * Evaluates inequality between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if not equal, 0 if equal.
		 **/
		virtual Result						operator!=(const Result& rhs) const override;

		/**
		 * Evaluates strictly-less-than comparison between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if less, 0 otherwise.
		 **/
		virtual Result						operator<(const Result& rhs) const override;

		/**
		 * Evaluates strictly-greater-than comparison between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if greater, 0 otherwise.
		 **/
		virtual Result						operator>(const Result& rhs) const override;

		/**
		 * Evaluates less-than-or-equal comparison between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if less or equal, 0 otherwise.
		 **/
		virtual Result						operator<=(const Result& rhs) const override;

		/**
		 * Evaluates greater-than-or-equal comparison between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if greater or equal, 0 otherwise.
		 **/
		virtual Result						operator>=(const Result& rhs) const override;

		/**
		 * Evaluates the addition operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed sum.
		 **/
		virtual Result						operator+(const Result& rhs) const override;

		/**
		 * Evaluates the subtraction operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed difference.
		 **/
		virtual Result						operator-(const Result& rhs) const override;

		/**
		 * Evaluates the multiplication operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed product.
		 **/
		virtual Result						operator*(const Result& rhs) const override;

		/**
		 * Evaluates the division operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed quotient.
		 **/
		virtual Result						operator/(const Result& rhs) const override;

		/**
		 * Evaluates the modulo operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed remainder.
		 **/
		virtual Result						operator%(const Result& rhs) const override;

		/**
		 * Evaluates the bitwise left-shift operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand indicating the shift amount.
		 * \return				Returns a Result containing the shifted value.
		 **/
		virtual Result						operator<<(const Result& rhs) const override;

		/**
		 * Evaluates the bitwise right-shift operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand indicating the shift amount.
		 * \return				Returns a Result containing the shifted value.
		 **/
		virtual Result						operator>>(const Result& rhs) const override;

		/**
		 * Evaluates the bitwise AND operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed bitwise AND.
		 **/
		virtual Result						operator&(const Result& rhs) const override;

		/**
		 * Evaluates the bitwise OR operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed bitwise OR.
		 **/
		virtual Result						operator|(const Result& rhs) const override;

		/**
		 * Evaluates the bitwise XOR operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed bitwise XOR.
		 **/
		virtual Result						operator^(const Result& rhs) const override;

		/**
		 * Evaluates the compound addition assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator+=(const Result& rhs) override;

		/**
		 * Evaluates the compound subtraction assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator-=(const Result& rhs) override;

		/**
		 * Evaluates the compound multiplication assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator*=(const Result& rhs) override;

		/**
		 * Evaluates the compound division assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator/=(const Result& rhs) override;

		/**
		 * Evaluates the compound modulo assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator%=(const Result& rhs) override;

		/**
		 * Evaluates the compound bitwise AND assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator&=(const Result& rhs) override;

		/**
		 * Evaluates the compound bitwise OR assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator|=(const Result& rhs) override;

		/**
		 * Evaluates the compound bitwise XOR assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator^=(const Result& rhs) override;

		/**
		 * Evaluates the compound bitwise shift left assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator<<=(const Result& rhs) override;

		/**
		 * Evaluates the compound bitwise shift right assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator>>=(const Result& rhs) override;


		// == Functions.
		/**
		 * Retrieves a value from the map using the given Result as a key.
		 *
		 * \param key		The Result to search for.
		 * \return			Returns the associated Result, or Invalid if the key is not found.
		 **/
		inline Result						valueFromKey(const Result& key) const {
			auto it = internalMap.find(key);
			if (it != internalMap.end()) {
				return it->second;
			}
			return Result{};
		}

		/**
		 * Inserts or updates a key-value pair in the map.
		 * Manages reference counting and object deallocation for replaced values.
		 *
		 * \param key		The Result to use as the key.
		 * \param value		The Result to store.
		 **/
		void								setValue(const Result& key, const Result& value);

		/**
		 * Retrieves all keys currently stored in the map.
		 * Must be called within a try/catch block.
		 *
		 * \return			Returns a standard vector containing all key Results.
		 **/
		inline std::vector<Result>			getKeys() const {
			std::vector<Result> keys;
			keys.reserve(internalMap.size());
			for (const auto& pair : internalMap) {
				keys.push_back(pair.first);
			}
			return keys;
		}

		/**
		 * Creates a copy of the object.
		 * 
		 * \return				Returns a copy of this object.
		 **/
		virtual Result						copy() const override;

		/**
		 * Clears the vector.
		 **/
		virtual void						clear() override {
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

		/**
		 * Removes the first element with the given value.
		 * 
		 * \param value			The value to find and erase.
		 * \return				Returns this object.
		 **/
		virtual Result						remove(const Result& value) override;

	protected :
		std::map<Result, Result, ResultCompare>
											internalMap;
	};

}	// namespace ve
