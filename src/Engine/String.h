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

		/**
		 * Converts the object from its internal encoding to ASCII.
		 * Characters outside the 0-127 range are replaced with '?'.
		 *
		 * \return				Returns a Result containing the new ASCII string object.
		 **/
		virtual Result						ascii() const override {
			std::string asciiStr;

			switch (bufferWidth) {
				case Width_8 : {
					asciiStr = Text::toAscii<std::string>(reinterpret_cast<const char8_t*>(buffer.data()), charCount);
					break;
				}
				case Width_16 : {
					asciiStr = Text::toAscii<std::string>(reinterpret_cast<const char16_t*>(buffer.data()), charCount);
					break;
				}
				case Width_32 : {
					asciiStr = Text::toAscii<std::string>(reinterpret_cast<const char32_t*>(buffer.data()), charCount);
					break;
				}
			}

			String* newStr = context->allocateObject<String>();
			
			if (newStr) {
				newStr->assignUtf8(asciiStr.data(), asciiStr.length());
				return newStr->createResult();
			}
			
			return Result{ .type = NumericConstant::Invalid };
		}

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
		virtual Result						toFloat() const override {
			Result res = bestFitNumeric();
			
			if (res.type == NumericConstant::Floating) {
				if (std::isnan(res.value.doubleVal)) {
					return Result{ .type = NumericConstant::Invalid };
				}
				return res;
			}
			else if (res.type == NumericConstant::Signed) {
				return Result{ .type = NumericConstant::Floating, .value = { .doubleVal = static_cast<double>(res.value.intVal) } };
			}
			else if (res.type == NumericConstant::Unsigned) {
				return Result{ .type = NumericConstant::Floating, .value = { .doubleVal = static_cast<double>(res.value.uintVal) } };
			}
			
			return Result{ .type = NumericConstant::Invalid };
		}

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
		virtual Result						toInt() const override {
			Result res = bestFitNumeric();
			
			if (res.type == NumericConstant::Signed || res.type == NumericConstant::Unsigned) {
				return res;
			}
			else if (res.type == NumericConstant::Floating) {
				if (std::isnan(res.value.doubleVal)) {
					return Result{ .type = NumericConstant::Invalid };
				}
				// Truncate floating-point values to integer, matching standard casting behavior.
				return Result{ .type = NumericConstant::Signed, .value = { .intVal = static_cast<int64_t>(res.value.doubleVal) } };
			}
			
			return Result{ .type = NumericConstant::Invalid };
		}

		/**
		 * Gets the number of elements or characters in the object.
		 *
		 * \return				Returns a Result containing the UTF code point count.
		 **/
		virtual Result						len() const override {
			return Result{ .type = NumericConstant::Unsigned, .value = { .uintVal = static_cast<uint64_t>(charCount) } };
		}

		/**
		 * Returns the ordinal (numeric) value of the object as a Unicode code point.
		 * Matches Python's ord(str): requires a string of exactly length 1.
		 *
		 * \return				Returns a Result containing the ordinal value as an unsigned integer, or invalid if length != 1.
		 **/
		virtual Result						ord() const override {
			if (charCount == 1) {
				return Result{ .type = NumericConstant::Unsigned, .value = { .uintVal = static_cast<uint64_t>(getCodePoint(0)) } };
			}
			else {
				return Result{ .type = NumericConstant::Invalid };
			}
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
						return Result{ .type = NumericConstant::Signed, .value = { .intVal = 0 } };
					}

					// Must have the same character widths.
					if (bufferWidth != rhsString->bufferWidth) {
						return Result{ .type = NumericConstant::Signed, .value = { .intVal = 0 } };
					}

					// Same width and length. Do a raw memory compare.
					if (buffer == rhsString->buffer) {
						return Result{ .type = NumericConstant::Signed, .value = { .intVal = 1 } };
					}
				}
			}

			return Result{ .type = NumericConstant::Signed, .value = { .intVal = 0 } };
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
				return Result{ .type = NumericConstant::Signed, .value = { .intVal = (eq.value.intVal == 0) ? 1 : 0 } };
			}
			
			return Result{ .type = NumericConstant::Invalid };
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
					return Result{ .type = NumericConstant::Signed, .value = { .intVal = (cmp < 0) ? 1 : 0 } };
				}
			}
			
			return Result{ .type = NumericConstant::Invalid };
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
					return Result{ .type = NumericConstant::Signed, .value = { .intVal = (cmp > 0) ? 1 : 0 } };
				}
			}
			
			return Result{ .type = NumericConstant::Invalid };
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
					return Result{ .type = NumericConstant::Signed, .value = { .intVal = (cmp <= 0) ? 1 : 0 } };
				}
			}
			
			return Result{ .type = NumericConstant::Invalid };
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
					return Result{ .type = NumericConstant::Signed, .value = { .intVal = (cmp >= 0) ? 1 : 0 } };
				}
			}
			
			return Result{ .type = NumericConstant::Invalid };
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
			return Result{ .type = NumericConstant::Invalid };
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
				return Result{ .type = NumericConstant::Invalid };
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
			
			return Result{ .type = NumericConstant::Invalid };
		}

		/**
		 * Evaluates the division operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						operator/(const Result& rhs) const override {
			return Result{ .type = NumericConstant::Invalid };
		}

		/**
		 * Evaluates the modulo operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						operator%(const Result& rhs) const override {
			return Result{ .type = NumericConstant::Invalid };
		}

		/**
		 * Evaluates the bitwise left-shift operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						operator<<(const Result& rhs) const override {
			return Result{ .type = NumericConstant::Invalid };
		}

		/**
		 * Evaluates the bitwise right-shift operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						operator>>(const Result& rhs) const override {
			return Result{ .type = NumericConstant::Invalid };
		}

		/**
		 * Evaluates the bitwise AND operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						operator&(const Result& rhs) const override {
			return Result{ .type = NumericConstant::Invalid };
		}

		/**
		 * Evaluates the bitwise OR operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						operator|(const Result& rhs) const override {
			return Result{ .type = NumericConstant::Invalid };
		}

		/**
		 * Evaluates the bitwise XOR operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns an invalid Result.
		 **/
		virtual Result						operator^(const Result& rhs) const override {
			return Result{ .type = NumericConstant::Invalid };
		}


		// == Assignment Operators
		/**
		 * Evaluates the addition-assignment (concatenation) operation.
		 *
		 * \param rhs			The right-hand side operand to append.
		 * \return				Returns true if successful, false otherwise.
		 **/
		virtual bool						operator+=(const Result& rhs) override {
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
					return true;
				}
			}

			return false;
		}

		/**
		 * Evaluates the subtraction-assignment operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns false.
		 **/
		virtual bool						operator-=(const Result& rhs) override {
			return false;
		}

		/**
		 * Evaluates the multiplication-assignment operation.
		 * Repeats the internal string buffer in-place.
		 *
		 * \param rhs			The right-hand side operand indicating the repeat count.
		 * \return				Returns true if successful, false otherwise.
		 **/
		virtual bool						operator*=(const Result& rhs) override {
			uint64_t count = 0;
			
			if (rhs.type == NumericConstant::Unsigned) {
				count = rhs.value.uintVal;
			}
			else if (rhs.type == NumericConstant::Signed && rhs.value.intVal >= 0) {
				count = static_cast<uint64_t>(rhs.value.intVal);
			}
			else {
				return false;
			}

			if (count == 0) {
				buffer.clear();
				charCount = 0;
				return true;
			}
			else if (count == 1) {
				return true;
			}

			size_t originalSize = buffer.size();
			buffer.resize(originalSize * count);
			
			for (uint64_t i = 1; i < count; ++i) {
				std::copy(buffer.begin(), buffer.begin() + originalSize, buffer.begin() + (originalSize * i));
			}
			charCount *= count;

			return true;
		}

		/**
		 * Evaluates the division-assignment operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns false.
		 **/
		virtual bool						operator/=(const Result& rhs) override {
			return false;
		}

		/**
		 * Evaluates the modulo-assignment operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns false.
		 **/
		virtual bool						operator%=(const Result& rhs) override {
			return false;
		}

		/**
		 * Evaluates the bitwise left-shift-assignment operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns false.
		 **/
		virtual bool						operator<<=(const Result& rhs) override {
			return false;
		}

		/**
		 * Evaluates the bitwise right-shift-assignment operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns false.
		 **/
		virtual bool						operator>>=(const Result& rhs) override {
			return false;
		}

		/**
		 * Evaluates the bitwise AND-assignment operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns false.
		 **/
		virtual bool						operator&=(const Result& rhs) override {
			return false;
		}

		/**
		 * Evaluates the bitwise OR-assignment operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns false.
		 **/
		virtual bool						operator|=(const Result& rhs) override {
			return false;
		}

		/**
		 * Evaluates the bitwise XOR-assignment operation. Invalid for strings.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns false.
		 **/
		virtual bool						operator^=(const Result& rhs) override {
			return false;
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
		 * Serializes the string into a wide string representation.
		 *
		 * \param returnString	The output parameter to overwrite with the string content.
		 * \param depth			The current recursion depth.
		 * \param flags			Formatting flags (e.g., ToStringFlag_CString).
		 * \return				Returns true on success.
		 **/
		virtual bool						toString(std::wstring& returnString, uint32_t depth, uint32_t flags) const override;

		/**
		 * Generates a formatted string representation of the object.
		 *
		 * \param format		The format string specifying how the object should be presented.
		 * \param flags			Formatting flags.
		 * \return				Returns the formatted wide string.
		 **/
		virtual std::wstring				formattedString(const std::wstring& format, uint32_t flags) const override {
			std::wstring wStr;

			if (flags & ToStringFlag_CString) {
				switch (bufferWidth) {
					case Width_8 : {
						wStr = Text::toEscaped<std::wstring>(reinterpret_cast<const char8_t*>(buffer.data()), charCount);
						break;
					}
					case Width_16 : {
						wStr = Text::toEscaped<std::wstring>(reinterpret_cast<const char16_t*>(buffer.data()), charCount);
						break;
					}
					case Width_32 : {
						wStr = Text::toEscaped<std::wstring>(reinterpret_cast<const char32_t*>(buffer.data()), charCount);
						break;
					}
				}
			}
			else {
				toString(wStr, 0, ToStringFlag_None);
			}

			return std::vformat(format, std::make_wformat_args(wStr));
		}

		/**
		 * Converts the string to a specified numeric constant type.
		 *
		 * \param type			The requested target numeric type.
		 * \return				Returns a Result containing the parsed value, or invalid if parsing fails.
		 **/
		virtual Result						convertTo(NumericConstant type) const override;

		/**
		 * Initializes the contents of this string object from an evaluation result.
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
		int64_t								count(const String* sub, int64_t start = 0, int64_t end = INT64_MAX) const;
		
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
	};

}	// namespace ve
