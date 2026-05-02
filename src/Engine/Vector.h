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
		virtual ~Vector();


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
		 * Clears the vector.
		 **/
		virtual void						clear() override {
			for (size_t i = 0; i < elements.size(); ++i) {
				prepareErase_Unsafe(i);
			}
			elements.clear();
		}

		/**
		 * Creates a copy of the object.
		 * 
		 * \return				Returns a copy of this object.
		 **/
		virtual Result						copy() const override;

		/**
		 * Pushes an expression to the back of the vector.
		 * 
		 * \param result		The result to push.
		 * \return				Returns true if the item was added.  False always indicates a memory failure.
		 **/
		inline bool							pushBack(const Result& result) {
			try {
				elements.push_back(result);
				if (result.type == NumericConstant::Object && result.value.objectVal) {
					result.value.objectVal->incRef();
				}
				return true;
			}
			catch (...) { return false; }
		}

		/**
		 * Removes an element at the specified position.
		 * 
		 * \param idx			The index at which to remove an item.
		 * \return				Returns this object.
		 **/
		Result								pop(int64_t idx = -1) {
			size_t i = arrayIndexToLinearIndex(idx, arrayLength());
			if (i == InvalidIndex) { return createResult(); }

			Result & result = elements[i];
			if (result.type == NumericConstant::Object && result.value.objectVal) {
				result.value.objectVal->decRef();
				if (!result.value.objectVal->getRef()) {
					context->deallocateObject(result.value.objectVal);
				}
			}
			elements.erase(elements.begin() + i);
			return createResult();
		}

		/**
		 * Removes the first element with the given value.
		 * 
		 * \param value			The value to find and erase.
		 * \return				Returns this object.
		 **/
		virtual Result						remove(const Result& value) override;

		/**
		 * Reverses the string.
		 * 
		 * \return				Returns this object.
		 **/
		Result								reverse() {
			std::reverse(elements.begin(), elements.end());
			return createResult();
		}

		/**
		 * Sets a given element to a given value.
		 * 
		 * \param idx			The index of the value to set.
		 * \param result		The value to set.
		 **/
		inline void							setAt(size_t idx, const Result& result) {
			if (idx < elements.size()) {
				setAt_Unsafe(idx, result);
			}
		}

		/**
		 * Sets a given element to a given value without checking for the index being valid.
		 * 
		 * \param idx			The index of the value to set.
		 * \param result		The value to set.
		 **/
		inline void							setAt_Unsafe(size_t idx, const Result& result) {
			Result & item = elements[idx];
			Object* prevObj = item.type == NumericConstant::Object && item.value.objectVal ? item.value.objectVal : nullptr;
			item = result;
			Object* newObj = item.type == NumericConstant::Object && item.value.objectVal ? item.value.objectVal : nullptr;
			if (newObj) { newObj->incRef(); }
			if (prevObj) { prevObj->decRef();
				if (!prevObj->getRef()) { context->deallocateObject(prevObj); }
			}
		}

		/**
		 * Dereferences an item by index and potentially deallocates it without actually removing it from the vector.
		 * 
		 * \param idx			The index of the item to prepare for erasing from the vector.
		 **/
		template <bool deleteObj = true>
		inline void							prepareErase_Unsafe(size_t idx) {
			Result & item = elements[idx];
			Object* isObj = item.type == NumericConstant::Object && item.value.objectVal ? item.value.objectVal : nullptr;
			if (isObj) {
				isObj->decRef();
				if constexpr (deleteObj) {
					if (!isObj->getRef()) { context->deallocateObject(isObj); }
				}
			}
			item.type = NumericConstant::Invalid;
		}

		/**
		 * Checks the given item for being an Object, and increases its reference count if it is.
		 * 
		 * \param idx			The index of the item to check.
		 **/
		inline void							incObjectRef_Unsafe(size_t idx) {
			Result & item = elements[idx];
			Object* isObj = item.type == NumericConstant::Object && item.value.objectVal ? item.value.objectVal : nullptr;
			if (isObj) { isObj->incRef(); }
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

		/**
		 * Gives direct access to an array element. Misuse can cause bugs. Index is not verified.
		 * 
		 * \param idx			The index of the element being accessed.
		 * \return				Returns a reference to the requested item.
		 **/
		Result &							directAccess(size_t idx) { return elements[idx]; }

		/**
		 * Resizes the vector to the given length.  Each new element is invalid initially.
		 * 
		 * \param size			The new length of the vector.
		 * \return				Returns false if the resize fails.
		 **/
		bool								resize(size_t size) {
			try {
				elements.resize(size);
				return true;
			}
			catch (...) { return false; }
		}

	protected :
		// == Members.
		std::vector<Result>					elements;
	};

}	// namespace ve
