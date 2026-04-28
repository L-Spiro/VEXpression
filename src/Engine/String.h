#pragma once

#include "../Foundation/Text.h"
#include "ExecutionContext.h"
#include "Object.h"

#include <algorithm>
#include <cmath>
#include <string>
#include <string_view>
#include <vector>

namespace ve {

	/**
	 * A flexible string implementation based on Python 3's internal string representation.
	 * Storage width is automatically selected based on the highest code point.
	 **/
	class String : public Object {
	public :
		/** The internal character width used by the string. **/
		enum Width : uint8_t {
			Width_8,
			Width_16,
			Width_32
		};

		String(ExecutionContext* ctx) : Object(ctx), bufferWidth(Width_8), charCount(0) {}


		// == Functions.
		/**
		 * Returns the type identifier for built-in strings.
		 *
		 * \return				Returns BuiltInType_String.
		 **/
		virtual uint32_t					type() const override {
			return Object::type() | BuiltInType_String;
		}

		/**
		 * Retrieves the number of Unicode code points.
		 *
		 * \return				Returns the character count.
		 **/
		virtual size_t						arrayLength() const override {
			return charCount;
		}


		// == Operators.
		/**
		 * Evaluates equality between this string and a right-hand operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if the objects are identical strings, 0 otherwise.
		 **/
		virtual Result						operator==(const Result& rhs) const override {
			if (rhs.type == NumericConstant::Object && rhs.value.objectVal != nullptr) {
				if (rhs.value.objectVal->type() & BuiltInType_String) {
					const String* rhsString = static_cast<const String*>(rhs.value.objectVal);

					// Must be the same length.
					if (charCount != rhsString->charCount) {
						return Result::make(false);
					}

					// Must have the same character widths.
					if (bufferWidth != rhsString->bufferWidth) {
						return Result::make(false);
					}

					// Same width and length. Do a raw memory compare.
					if (buffer == rhsString->buffer) {
						return Result::make(true);
					}
				}
			}

			return Result::make(false);
		}

		/**
		 * Evaluates inequality between this string and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if the objects are not identical strings, 0 otherwise.
		 **/
		virtual Result						operator!=(const Result& rhs) const override {
			Result eq = operator==(rhs);
			
			if (eq.type == NumericConstant::Signed) {
				//return Result{ .type = NumericConstant::Signed, .value = { .intVal = (eq.value.intVal == 0) ? 1 : 0 } };
				return Result::make(eq.value.uintVal == 0);
			}
			
			return Result{};
		}

		/**
		 * Evaluates strictly-less-than comparison between this string and a right-hand operand.
		 * Invalid if RHS is not a String.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if less, 0 otherwise. 
		 **/
		virtual Result						operator<(const Result& rhs) const override {
			if (rhs.type == NumericConstant::Object && rhs.value.objectVal != nullptr) {
				if (rhs.value.objectVal->type() & BuiltInType_String) {
					int cmp = compareString(static_cast<const String*>(rhs.value.objectVal));
					return Result::make(cmp < 0);
				}
			}
			
			return Result{};
		}

		/**
		 * Evaluates strictly-greater-than comparison between this string and a right-hand operand.
		 * Invalid if RHS is not a String.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if greater, 0 otherwise.
		 **/
		virtual Result						operator>(const Result& rhs) const override {
			if (rhs.type == NumericConstant::Object && rhs.value.objectVal != nullptr) {
				if (rhs.value.objectVal->type() & BuiltInType_String) {
					int cmp = compareString(static_cast<const String*>(rhs.value.objectVal));
					return Result::make(cmp > 0);
				}
			}
			
			return Result{};
		}

		/**
		 * Evaluates less-than-or-equal comparison between this string and a right-hand operand.
		 * Invalid if RHS is not a String.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if less or equal, 0 otherwise.
		 **/
		virtual Result						operator<=(const Result& rhs) const override {
			if (rhs.type == NumericConstant::Object && rhs.value.objectVal != nullptr) {
				if (rhs.value.objectVal->type() & BuiltInType_String) {
					int cmp = compareString(static_cast<const String*>(rhs.value.objectVal));
					return Result::make(cmp <= 0);
				}
			}
			
			return Result{};
		}

		/**
		 * Evaluates greater-than-or-equal comparison between this string and a right-hand operand.
		 * Invalid if RHS is not a String.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if greater or equal, 0 otherwise.
		 **/
		virtual Result						operator>=(const Result& rhs) const override {
			if (rhs.type == NumericConstant::Object && rhs.value.objectVal != nullptr) {
				if (rhs.value.objectVal->type() & BuiltInType_String) {
					int cmp = compareString(static_cast<const String*>(rhs.value.objectVal));
					return Result::make(cmp >= 0);
				}
			}
			
			return Result{};
		}

		/**
		 * Evaluates the addition (concatenation) operation against a right-hand operand.
		 * 
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the new concatenated String, or invalid if RHS is not a String.
		 **/
		virtual Result						operator+(const Result& rhs) const override;

		/**
		 * Evaluates the subtraction operation.
		 * Invalid for string objects.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						operator-(const Result& rhs) const override {
			return Result{};
		}

		/**
		 * Evaluates the multiplication operation.
		 * If the right-hand operand is a non-negative integer, repeats the string that many times.
		 *
		 * \param rhs			The right-hand side operand indicating the repeat count.
		 * \return				Returns a Result containing the new repeated String, or invalid if RHS is invalid.
		 **/
		virtual Result						operator*(const Result& rhs) const override {
			uint64_t count = 0;
			
			if (rhs.type == NumericConstant::Unsigned) {
				count = rhs.value.uintVal;
			}
			else if (rhs.type == NumericConstant::Signed && rhs.value.intVal >= 0) {
				count = static_cast<uint64_t>(rhs.value.intVal);
			}
			else {
				return Result{};
			}

			size_t newCharCount = charCount * count;
			std::vector<uint8_t> newBuffer;
			
			if (count > 0) {
				size_t originalSize = buffer.size();
				newBuffer.resize(originalSize * count);
				
				// Fast raw copy since the buffer width remains identical.
				for (uint64_t i = 0; i < count; ++i) {
					std::copy(buffer.begin(), buffer.begin() + originalSize, newBuffer.begin() + (originalSize * i));
				}
			}

			String* newStr = context->allocateObject<String>();
			
			if (newStr) {
				newStr->buffer = std::move(newBuffer);
				newStr->bufferWidth = bufferWidth;
				newStr->charCount = newCharCount;
				return newStr->createResult();
			}
			
			return Result{};
		}

		/**
		 * Evaluates the division operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						operator/(const Result& rhs) const override {
			return Result{};
		}

		/**
		 * Evaluates the modulo operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						operator%(const Result& rhs) const override {
			return Result{};
		}

		/**
		 * Evaluates the bitwise left-shift operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						operator<<(const Result& rhs) const override {
			return Result{};
		}

		/**
		 * Evaluates the bitwise right-shift operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						operator>>(const Result& rhs) const override {
			return Result{};
		}

		/**
		 * Evaluates the bitwise AND operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						operator&(const Result& rhs) const override {
			return Result{};
		}

		/**
		 * Evaluates the bitwise OR operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						operator|(const Result& rhs) const override {
			return Result{};
		}

		/**
		 * Evaluates the bitwise XOR operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						operator^(const Result& rhs) const override {
			return Result{};
		}


		// == Assignment Operators
		/**
		 * Evaluates the addition-assignment (concatenation) operation.
		 *
		 * \param rhs			The right-hand side operand to append.
		 * \return				Returns true if successful, false otherwise.
		 **/
		virtual Result						operator+=(const Result& rhs) override {
			if (rhs.type == NumericConstant::Object && rhs.value.objectVal != nullptr) {
				if (rhs.value.objectVal->type() & BuiltInType_String) {
					const String* rhsString = static_cast<const String*>(rhs.value.objectVal);

					Width newWidth = std::max(bufferWidth, rhsString->bufferWidth);
					size_t newCharCount = charCount + rhsString->charCount;
					std::vector<uint8_t> newBuffer;

					switch (newWidth) {
						case Width_8 : {
							newBuffer.resize(newCharCount * sizeof(char8_t));
							char8_t* outPtr = reinterpret_cast<char8_t*>(newBuffer.data());
							
							for (size_t i = 0; i < charCount; ++i) {
								outPtr[i] = static_cast<char8_t>(getCodePoint(i));
							}
							for (size_t i = 0; i < rhsString->charCount; ++i) {
								outPtr[charCount + i] = static_cast<char8_t>(rhsString->getCodePoint(i));
							}
							break;
						}
						case Width_16 : {
							newBuffer.resize(newCharCount * sizeof(char16_t));
							char16_t* outPtr = reinterpret_cast<char16_t*>(newBuffer.data());
							
							for (size_t i = 0; i < charCount; ++i) {
								outPtr[i] = static_cast<char16_t>(getCodePoint(i));
							}
							for (size_t i = 0; i < rhsString->charCount; ++i) {
								outPtr[charCount + i] = static_cast<char16_t>(rhsString->getCodePoint(i));
							}
							break;
						}
						case Width_32 : {
							newBuffer.resize(newCharCount * sizeof(char32_t));
							char32_t* outPtr = reinterpret_cast<char32_t*>(newBuffer.data());
							
							for (size_t i = 0; i < charCount; ++i) {
								outPtr[i] = static_cast<char32_t>(getCodePoint(i));
							}
							for (size_t i = 0; i < rhsString->charCount; ++i) {
								outPtr[charCount + i] = static_cast<char32_t>(rhsString->getCodePoint(i));
							}
							break;
						}
					}

					buffer = std::move(newBuffer);
					bufferWidth = newWidth;
					charCount = newCharCount;
					return createResult();
				}
			}
			else if (rhs.type == NumericConstant::Signed) {
				if (bufferWidth == Width_32) {
					buffer.resize(buffer.size() + sizeof(char32_t));
					(*reinterpret_cast<char32_t*>(&buffer[buffer.size()-sizeof(char32_t)])) = char32_t(rhs.value.intVal);
				}
				else {
					auto str = getUtf32();
					Text::appendUtf32(str, uint32_t(rhs.value.intVal));
					auto utf8 = Text::utf32ToUtf8(str);
					assignUtf8(utf8.c_str(), utf8.size());
				}
				return createResult();
			}
			else if (rhs.type == NumericConstant::Unsigned) {
				if (bufferWidth == Width_32) {
					buffer.resize(buffer.size() + sizeof(char32_t));
					(*reinterpret_cast<char32_t*>(&buffer[buffer.size()-sizeof(char32_t)])) = char32_t(rhs.value.uintVal);
				}
				else {
					auto str = getUtf32();
					Text::appendUtf32(str, uint32_t(rhs.value.uintVal));
					auto utf8 = Text::utf32ToUtf8(str);
					assignUtf8(utf8.c_str(), utf8.size());
				}
				return createResult();
			}

			return Result{};
		}

		/**
		 * Evaluates the subtraction-assignment operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns false.
		 **/
		virtual Result						operator-=(const Result& rhs) override {
			return Result{};
		}

		/**
		 * Evaluates the multiplication-assignment operation.
		 * Repeats the internal string buffer in-place.
		 *
		 * \param rhs			The right-hand side operand indicating the repeat count.
		 * \return				Returns true if successful, false otherwise.
		 **/
		virtual Result						operator*=(const Result& rhs) override {
			uint64_t count = 0;
			
			if (rhs.type == NumericConstant::Unsigned) {
				count = rhs.value.uintVal;
			}
			else if (rhs.type == NumericConstant::Signed && rhs.value.intVal >= 0) {
				count = static_cast<uint64_t>(rhs.value.intVal);
			}
			else {
				return Result{};
			}

			if (count == 0) {
				buffer.clear();
				charCount = 0;
				return createResult();
			}
			else if (count == 1) {
				return createResult();
			}

			size_t originalSize = buffer.size();
			buffer.resize(originalSize * count);
			
			for (uint64_t i = 1; i < count; ++i) {
				std::copy(buffer.begin(), buffer.begin() + originalSize, buffer.begin() + (originalSize * i));
			}
			charCount *= count;

			return createResult();
		}

		/**
		 * Evaluates the division-assignment operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns false.
		 **/
		virtual Result						operator/=(const Result& rhs) override {
			return Result{};
		}

		/**
		 * Evaluates the modulo-assignment operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns false.
		 **/
		virtual Result						operator%=(const Result& rhs) override {
			return Result{};
		}

		/**
		 * Evaluates the bitwise left-shift-assignment operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns false.
		 **/
		virtual Result						operator<<=(const Result& rhs) override {
			return Result{};
		}

		/**
		 * Evaluates the bitwise right-shift-assignment operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns false.
		 **/
		virtual Result						operator>>=(const Result& rhs) override {
			return Result{};
		}

		/**
		 * Evaluates the bitwise AND-assignment operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns false.
		 **/
		virtual Result						operator&=(const Result& rhs) override {
			return Result{};
		}

		/**
		 * Evaluates the bitwise OR-assignment operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns false.
		 **/
		virtual Result						operator|=(const Result& rhs) override {
			return Result{};
		}

		/**
		 * Evaluates the bitwise XOR-assignment operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns false.
		 **/
		virtual Result						operator^=(const Result& rhs) override {
			return Result{};
		}


		// == Functions.
		/**
		 * Assigns a UTF-8 string to this object, automatically selecting the optimal width.
		 * Must be called within a try/catch block.
		 *
		 * \param str			The UTF-8 string to copy.
		 * \param len			The length of the string in bytes.
		 * \return				Returns true if the assignment was successful.
		 **/
		bool								assignUtf8(const char* str, size_t len);

		/**
		 * Accesses a code point at a specific index (supports negative indexing).
		 *
		 * \param idx			The signed index.
		 * \return				Returns a Result containing the code point.
		 **/
		virtual Result						arrayAccess(int64_t idx) override {
			size_t linearIdx = arrayIndexToLinearIndex(idx, charCount);
			if (linearIdx == InvalidIndex) {
				return Result::make(0ULL); 
			}
			return Result::make(static_cast<uint64_t>(getCodePoint(linearIdx)));
		}

		/**
		 * Extracts a slice of the string using Python-style array access rules.
		 *
		 * \param idx0			The start index.
		 * \param idx1			The end index.
		 * \param mask			Mask specifying if start (ArrayAccessFlag_Start) or end (ArrayAccessFlag_End) are active.
		 * \return				Returns a Result containing the new extracted String slice.
		 **/
		virtual Result						arrayAccessEx(int64_t idx0, int64_t idx1, uint32_t mask) override;

		/**
		 * Assigns a value directly to a specified index, modifying the string in-place.
		 *
		 * \param index			The zero-based or negative offset index.
		 * \param rhs			The result containing the code point or string to insert.
		 * \return				Returns the assigned value on success, or Invalid on failure.
		 **/
		virtual Result						arrayAssign(int64_t index, const Result& rhs) override;

		/**
		 * Assigns a value or merges a string into a sliced range, modifying the string in-place.
		 *
		 * \param startIdx		The starting index of the slice.
		 * \param endIdx		The ending index of the slice.
		 * \param flags			Bitmask defining slice boundary rules.
		 * \param rhs			The result containing the string or code point to merge.
		 * \return				Returns the assigned value on success, or Invalid on failure.
		 **/
		virtual Result						arrayAssignEx(int64_t startIdx, int64_t endIdx, uint32_t flags, const Result& rhs) override;

		/**
		 * Serializes the string into a wide string representation.
		 *
		 * \param returnString	The output parameter to overwrite with the string content.
		 * \param depth			The current recursion depth.
		 * \param flags			Formatting flags (e.g., ToStringFlag_CString).
		 * \return				Returns true on success.
		 **/
		virtual bool						toString(std::string& returnString, uint32_t depth, uint32_t flags) const override;

		/**
		 * Converts the string to a specified numeric constant type.
		 *
		 * \param type			The requested target numeric type.
		 * \return				Returns a Result containing the parsed value, or invalid if parsing fails.
		 **/
		virtual Result						convertTo(NumericConstant type) const override;

		/**
		 * Initializes the contents of this string object from an evaluation result.
		 * Must be called within a try/catch block.
		 *
		 * \param obj			The evaluation result to read from.
		 * \return				Returns true if successful, false otherwise.
		 **/
		virtual bool						initializeFrom(const Result& obj) override;

		/**
		 * Converts the internal string representation into a UTF-8 encoded standard string.
		 * Must be called within a try/catch block.
		 *
		 * \return				Returns a std::string containing the UTF-8 encoded characters.
		 **/
		std::string							getUtf8() const {
			std::string result;
			result.reserve(charCount);
			
			for (size_t i = 0; i < charCount; ++i) {
				Text::appendUtf8(result, getCodePoint(i));
			}
			
			return result;
		}

		/**
		 * Converts the internal string representation into a UTF-8 encoded standard string.
		 * Must be called within a try/catch block.
		 *
		 * \return				Returns a std::string containing the UTF-8 encoded characters.
		 **/
		std::u32string						getUtf32() const {
			std::u32string result;
			result.reserve(charCount);
			
			for (size_t i = 0; i < charCount; ++i) {
				Text::appendUtf32(result, getCodePoint(i));
			}
			
			return result;
		}


		// == API Functions.
		/**
		 * Creates a new string with the first character capitalized and the rest lowercased.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The execution context for allocation.
		 * \return				Returns a new String object with the capitalized content, or nullptr on allocation failure.
		 **/
		String*								capitalize(ExecutionContext* ctx) const {
			std::string capStr = Text::capitalizeUtf8<std::string>(this->getUtf8());
		
			String* newStr = ctx->allocateObject<String>();
			if (newStr) {
				newStr->assignUtf8(capStr.data(), capStr.length());
			}
		
			return newStr;
		}

		/**
		 * Creates a casefolded copy of the string.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The execution context for allocation.
		 * \return				Returns a new String object.
		 **/
		String*								casefold(ExecutionContext* ctx) const;

		/**
		 * Creates a copy of the string centered in a string of length width.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The execution context for allocation.
		 * \param width			The total width of the new string.
		 * \param fillChar		The padding character code point (defaults to space).
		 * \return				Returns a new String object, or nullptr on allocation failure.
		 **/
		String*								center(ExecutionContext* ctx, size_t width, uint32_t fillChar = ' ') const;

		/**
		 * Returns the number of non-overlapping occurrences of substring sub in the range [start, end].
		 * Optional arguments start and end are interpreted as in slice notation.
		 * Must be called within a try/catch block.
		 *
		 * \param sub			The substring to count.
		 * \param start			The starting index (character-based, handles negative).
		 * \param end			The ending index (character-based, handles negative).
		 * \return				Returns the number of occurrences.
		 **/
		int64_t								count(const String* sub, int64_t start = 0, int64_t end = -1) const;

		/**
		 * Returns an encoded version of the string as a new String object.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The runtime execution context.
		 * \param codePage		The target code page to encode to.
		 * \param errorPolicy	The policy for handling invalid characters.
		 * \return				Returns the newly encoded String.
		 **/
		String*								encode(ExecutionContext* ctx, CodePage codePage, EncodingErrorPolicy errorPolicy = EncodingErrorPolicy::Strict) const;

		/**
		 * Returns true if the string ends with the specified suffix, otherwise false.
		 * Optional arguments start and end are interpreted as in slice notation.
		 * Must be called within a try/catch block.
		 *
		 * \param suffix		The suffix string to check for.
		 * \param start			The starting index (character-based, handles negative).
		 * \param end			The ending index (character-based, handles negative).
		 * \return				Returns true if the string ends with the suffix.
		 **/
		bool								endsWith(const String* suffix, int64_t start = 0, int64_t end = -1) const;

		/**
		 * Returns a copy of the string where all tab characters are replaced by one or more spaces.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The runtime execution context.
		 * \param tabSize		The size of each tab stop (defaults to 8).
		 * \return				Returns the newly expanded String.
		 **/
		String*								expandtabs(ExecutionContext* ctx, int64_t tabSize = 8) const;

		/**
		 * Returns the lowest index in the string where substring sub is found within the slice [start, end].
		 * Must be called within a try/catch block.
		 *
		 * \param sub			The substring to search for.
		 * \param start			The starting index (character-based, handles negative).
		 * \param end			The ending index (character-based, handles negative).
		 * \return				Returns the character index of the match, or -1 if not found.
		 **/
		int64_t								find(const String* sub, int64_t start = 0, int64_t end = -1) const;

		/**
		 * Returns a formatted version of the string, replacing {} and {N} placeholders with arguments.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The runtime execution context.
		 * \param args			A vector of UTF-8 string representations of the arguments.
		 * \return				Returns the newly formatted String.
		 **/
		String*								format(ExecutionContext* ctx, const std::vector<Result>& args) const;

		/**
		 * Returns true if all characters in the string are alphanumeric and there is at least one character.
		 * Must be called within a try/catch block.
		 * 
		 * \return				Returns true if the string is alphanumeric, false otherwise.
		 **/
		bool								isalnum() const;

		/**
		 * Returns true if all characters in the string are alphabetic and there is at least one character.
		 * Must be called within a try/catch block.
		 *
		 * \return				Returns true if the string is alphabetic, false otherwise.
		 **/
		bool								isalpha() const;

		/**
		 * Returns true if the string is empty or all characters in the string are ASCII, false otherwise.
		 * Must be called within a try/catch block.
		 *
		 * \return				Returns true if the string is ASCII, false otherwise.
		 **/
		bool								isAscii() const;

		/**
		 * Returns true if all characters in the string are decimal characters and there is at least one character, false otherwise.
		 * Must be called within a try/catch block.
		 *
		 * \return				Returns true if the string is decimal, false otherwise.
		 **/
		bool								isdecimal() const;

		/**
		 * Returns true if all characters in the string are digits and there is at least one character, false otherwise.
		 * Must be called within a try/catch block.
		 *
		 * \return				Returns true if the string is composed entirely of digits, false otherwise.
		 **/
		bool								isdigit() const;

		/**
		 * Returns true if the string is a valid identifier and is not empty, false otherwise.
		 * Must be called within a try/catch block.
		 *
		 * \return				Returns true if the string is a valid identifier, false otherwise.
		 **/
		bool								isidentifier() const;

		/**
		 * Returns true if all cased characters in the string are lowercase and there is at least one cased character, false otherwise.
		 * Must be called within a try/catch block.
		 *
		 * \return				Returns true if the string is lowercase, false otherwise.
		 **/
		bool								islower() const;

		/**
		 * Returns true if all characters in the string are numeric characters and there is at least one character, false otherwise.
		 * Must be called within a try/catch block.
		 *
		 * \return				Returns true if the string is numeric, false otherwise.
		 **/
		bool								isnumeric() const;

		/**
		 * Returns true if all characters in the string are printable or the string is empty, false otherwise.
		 * Must be called within a try/catch block.
		 *
		 * \return				Returns true if the string is printable, false otherwise.
		 **/
		bool								isprintable() const;

		/**
		 * Returns true if all characters in the string are whitespace characters and there is at least one character, false otherwise.
		 * Must be called within a try/catch block.
		 *
		 * \return				Returns true if the string is whitespace, false otherwise.
		 **/
		bool								isspace() const;

		/**
		 * Returns true if the string is a title-cased string and there is at least one character, false otherwise.
		 * Must be called within a try/catch block.
		 *
		 * \return				Returns true if the string is title-cased, false otherwise.
		 **/
		bool								istitle() const;

		/**
		 * Returns true if all cased characters in the string are uppercase and there is at least one cased character, false otherwise.
		 * Must be called within a try/catch block.
		 *
		 * \return				Returns true if the string is uppercase, false otherwise.
		 **/
		bool								isupper() const;

		/**
		 * Returns a left-justified string of length width. 
		 * Padding is done using the specified fill character (default is an ASCII space).
		 * Must be called within a try/catch block.
		 *
		 * \param width			The total length of the newly justified string.
		 * \param fillchar		The UTF-32 code point of the padding character.
		 * \return				Returns the justified string as a new String.
		 **/
		String*								ljust(size_t width, uint32_t fillchar = ' ') const;

		/**
		 * Creates a lowercased copy of the string.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The execution context for allocation.
		 * \return				Returns a new String object.
		 **/
		String*								lower(ExecutionContext* ctx) const;

		/**
		 * Returns a copy of the string with leading characters removed.
		 * If chars is omitted or empty, whitespace characters are removed.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The execution context for allocation.
		 * \param chars			The characters to remove.
		 * \return				Returns a new String object.
		 **/
		String*								lstrip(ExecutionContext* ctx, const std::u32string& chars = {}) const;

		/**
		 * Returns a copy of the string with the given prefix removed if it is present.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The execution context for allocation.
		 * \param prefix		The prefix string to remove.
		 * \return				Returns a new String object.
		 **/
		String*								removeprefix(ExecutionContext* ctx, const std::u32string& prefix) const;

		/**
		 * Returns a copy of the string with the given suffix removed if it is present.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The execution context for allocation.
		 * \param suffix		The suffix string to remove.
		 * \return				Returns a new String object.
		 **/
		String*								removesuffix(ExecutionContext* ctx, const std::u32string& suffix) const;

		/**
		 * Returns a copy of the string with all occurrences of substring old replaced by new.
		 * If the optional argument count is given, only the first count occurrences are replaced.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The execution context for allocation.
		 * \param oldStr		The substring to find.
		 * \param newStr		The substring to replace with.
		 * \param count			The maximum number of replacements to perform (-1 for unlimited).
		 * \return				Returns a new String object.
		 **/
		String*								replace(ExecutionContext* ctx, const std::u32string& oldStr, const std::u32string& newStr, int64_t count = -1) const;

		/**
		 * Returns the highest index in the string where a substring is found within the given boundaries.
		 * Must be called within a try/catch block.
		 *
		 * \param sub			The substring to search for.
		 * \param start			The starting character index.
		 * \param end			The ending character index.
		 * \return				Returns the index of the substring, or -1 if not found.
		 **/
		int64_t								rfind(const std::u32string& sub, int64_t start = 0, int64_t end = -1) const;

		/**
		 * Returns a right-justified string of length width.
		 * Padding is done using the specified fill character (default is an ASCII space).
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The execution context for allocation.
		 * \param width			The total length of the newly justified string.
		 * \param fillchar		The UTF-32 code point of the padding character.
		 * \return				Returns a new String object.
		 **/
		String*								rjust(ExecutionContext* ctx, size_t width, uint32_t fillchar = ' ') const;

		/**
		 * Returns a copy of the string with trailing characters removed.
		 * If chars is omitted or empty, whitespace characters are removed.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The execution context for allocation.
		 * \param chars			The characters to remove.
		 * \return				Returns a new String object.
		 **/
		String*								rstrip(ExecutionContext* ctx, const std::u32string& chars = {}) const;

		/**
		 * Returns true if the string slice begins with the specified prefix, false otherwise.
		 * Must be called within a try/catch block.
		 *
		 * \param prefix		The prefix substring to check for.
		 * \param start			The starting character index.
		 * \param end			The ending character index.
		 * \return				Returns true if the string starts with the prefix.
		 **/
		bool								startswith(const std::u32string& prefix, int64_t start = 0, int64_t end = -1) const;

		/**
		 * Returns a copy of the string with leading and trailing characters removed.
		 * If chars is omitted or empty, whitespace characters are removed.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The execution context for allocation.
		 * \param chars			The characters to remove.
		 * \return				Returns a new String object.
		 **/
		String*								strip(ExecutionContext* ctx, const std::u32string& chars = {}) const;

		/**
		 * Creates a copy of the string with uppercase characters converted to lowercase and vice versa.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The execution context for allocation.
		 * \return				Returns a new String object.
		 **/
		String*								swapcase(ExecutionContext* ctx) const;

		/**
		 * Creates a titlecased copy of the string.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The execution context for allocation.
		 * \return				Returns a new String object.
		 **/
		String*								title(ExecutionContext* ctx) const;

		/**
		 * Creates an uppercase copy of the string.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The execution context for allocation.
		 * \return				Returns a new String object.
		 **/
		String*								upper(ExecutionContext* ctx) const;

		/**
		 * Returns a copy of the string left-filled with zeros to a length of width.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx			The execution context for allocation.
		 * \param width			The target total length of the newly padded string.
		 * \return				Returns a new String object.
		 **/
		String*								zfill(ExecutionContext* ctx, size_t width) const;

		/**
		 * Retrieves the character code point at the specified index.
		 *
		 * \param index			The zero-based or negative offset index.
		 * \return				Returns a Result containing the code point, or Invalid if out of bounds.
		 **/
		Result								at(int64_t index) const;

		/**
		 * Pushes a string expression to the back of the string.
		 * 
		 * \param result		The result to push.
		 * \return				Returns true if the item was added. False indicates a memory failure or incompatible type.
		 **/
		bool								pushBack(const Result& result);
		
		/**
		 * Internal helper to fetch a UTF-32 code point at a linear index.
		 *
		 * \param idx			The linear (0-based) index.
		 * \return				Returns the UTF-32 code point.
		 **/
		uint32_t							getCodePoint(size_t idx) const {
			switch (bufferWidth) {
				case Width_8 :  { return reinterpret_cast<const char8_t*>(buffer.data())[idx]; }
				case Width_16 : { return reinterpret_cast<const char16_t*>(buffer.data())[idx]; }
				case Width_32 : { return reinterpret_cast<const char32_t*>(buffer.data())[idx]; }
			}
			return 0;
		}

		/**
		 * Lexicographically compares this string with another string based on Unicode code points.
		 *
		 * \param rhsString		The other string object to compare against.
		 * \return				Returns a negative value if this is less, 0 if equal, and a positive value if greater.
		 **/
		int									compareString(const String* rhsString) const {
			size_t minLen = std::min(charCount, rhsString->charCount);
			
			for (size_t i = 0; i < minLen; ++i) {
				uint32_t cp1 = getCodePoint(i);
				uint32_t cp2 = rhsString->getCodePoint(i);
				
				if (cp1 != cp2) {
					return (cp1 < cp2) ? -1 : 1;
				}
			}
			
			if (charCount < rhsString->charCount) {
				return -1;
			}
			else if (charCount > rhsString->charCount) {
				return 1;
			}
			
			return 0;
		}

	protected :
		// == Members.
		std::vector<uint8_t>				buffer;
		Width								bufferWidth;
		size_t								charCount;


		// == Functions.
		/**
		 * Creates a Result using a best-fit interpretation of the string as a number.
		 *
		 * The input string is analyzed to determine the most appropriate numeric interpretation (for example,
		 * integer vs. floating-point, and/or base detection). If no reasonable numeric interpretation can be
		 * made, the returned result is NaN (floating-point).
		 *
		 * \return				Returns a Result containing the interpreted numeric value.
		 **/
		Result								bestFitNumeric() const;

		
	};

}	// namespace ve
