#include "String.h"


namespace ve {
	
	// == Operators.
	/**
	 * Evaluates the addition (concatenation) operation against a right-hand operand.
	 * 
	 * \param rhs			The right-hand side operand.
	 * \return				Returns a Result containing the new concatenated String, or invalid if RHS is not a String.
	 **/
	Result String::operator+(const Result& rhs) const {
		if (rhs.type == NumericConstant::Object && rhs.value.objectVal != nullptr) {
			if (rhs.value.objectVal->type() == BuiltInType_String) {
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

				String* newStr = context->allocateObject<String>();
					
				if (newStr) {
					newStr->buffer = std::move(newBuffer);
					newStr->bufferWidth = newWidth;
					newStr->charCount = newCharCount;
					return newStr->createResult();
				}
					
				return Result{ .type = NumericConstant::Invalid };
			}
		}

		return Result{ .type = NumericConstant::Invalid };
	}

	// == Functions.
	/**
	 * Assigns a UTF-8 string to this object, automatically selecting the optimal width.
	 *
	 * \param str			The UTF-8 string to copy.
	 * \param len			The length of the string in bytes.
	 * \return				Returns true if the assignment was successful.
	 **/
	bool String::assignUtf8(const char* str, size_t len) {
		std::vector<uint32_t> codePoints;
		uint32_t maxCp = 0;
		size_t i = 0;

		while (i < len) {
			size_t eaten = 0;
			uint32_t cp = Text::nextUtf8Char(reinterpret_cast<const uint8_t*>(&str[i]), len - i, &eaten);
			if (cp == Text::UTF_INVALID) {
				break;
			}
			codePoints.push_back(cp);
			if (cp > maxCp) {
				maxCp = cp;
			}
			i += eaten;
		}

		charCount = codePoints.size();
		if (maxCp <= 0xFF) {
			bufferWidth = Width_8;
			buffer.resize(charCount * sizeof(char8_t));
			char8_t* p = reinterpret_cast<char8_t*>(buffer.data());
			for (size_t j = 0; j < charCount; ++j) {
				p[j] = static_cast<char8_t>(codePoints[j]);
			}
		} else if (maxCp <= 0xFFFF) {
			bufferWidth = Width_16;
			buffer.resize(charCount * sizeof(char16_t));
			char16_t* p = reinterpret_cast<char16_t*>(buffer.data());
			for (size_t j = 0; j < charCount; ++j) {
				p[j] = static_cast<char16_t>(codePoints[j]);
			}
		} else {
			bufferWidth = Width_32;
			buffer.resize(charCount * sizeof(char32_t));
			char32_t* p = reinterpret_cast<char32_t*>(buffer.data());
			for (size_t j = 0; j < charCount; ++j) {
				p[j] = static_cast<char32_t>(codePoints[j]);
			}
		}
		return true;
	}

	/**
	 * Extracts a slice of the string using Python-style array access rules.
	 *
	 * \param idx0			The start index.
	 * \param idx1			The end index.
	 * \param mask			Mask specifying if start (ArrayAccessFlag_Start) or end (ArrayAccessFlag_End) are active.
	 * \return				Returns a Result containing the new extracted String slice.
	 **/
	Result String::arrayAccessEx(int64_t idx0, int64_t idx1, uint32_t mask) {
		int64_t startIdx = 0;
		int64_t endIdx = static_cast<int64_t>(charCount);

		if (mask & ArrayExFlag_Start) {
			startIdx = idx0;
				
			if (startIdx < 0) {
				startIdx += static_cast<int64_t>(charCount);
			}
				
			if (startIdx < 0) {
				startIdx = 0;
			}
			else if (startIdx > static_cast<int64_t>(charCount)) {
				startIdx = static_cast<int64_t>(charCount);
			}
		}

		if (mask & ArrayExFlag_End) {
			endIdx = idx1;
				
			if (endIdx < 0) {
				endIdx += static_cast<int64_t>(charCount);
			}
				
			if (endIdx < 0) {
				endIdx = 0;
			}
			else if (endIdx > static_cast<int64_t>(charCount)) {
				endIdx = static_cast<int64_t>(charCount);
			}
		}

		// Python slicing behavior: an invalid range simply results in an empty string.
		if (startIdx > endIdx) {
			startIdx = endIdx;
		}

		size_t newCharCount = static_cast<size_t>(endIdx - startIdx);
		std::vector<uint8_t> newBuffer;
			
		if (newCharCount > 0) {
			size_t elementSize = 1;
				
			switch (bufferWidth) {
				case Width_8 : {
					elementSize = sizeof(char8_t);
					break;
				}
				case Width_16 : {
					elementSize = sizeof(char16_t);
					break;
				}
				case Width_32 : {
					elementSize = sizeof(char32_t);
					break;
				}
			}
				
			size_t byteStart = static_cast<size_t>(startIdx) * elementSize;
			size_t byteLen = newCharCount * elementSize;
				
			newBuffer.resize(byteLen);
			std::copy(buffer.begin() + byteStart, buffer.begin() + byteStart + byteLen, newBuffer.begin());
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
	 * Serializes the string into a wide string representation.
	 *
	 * \param returnString	The output parameter to overwrite with the string content.
	 * \param depth			The current recursion depth.
	 * \param flags			Formatting flags (e.g., ToStringFlag_CString).
	 * \return				Returns true on success.
	 **/
	bool String::toString(std::wstring& returnString, uint32_t depth, uint32_t flags) const {
		static_cast<void>(depth);

		if (flags & ToStringFlag_CString) {
			returnString = L"\"";
			switch (bufferWidth) {
				case Width_8 : {
					returnString += Text::toEscaped<std::wstring>(reinterpret_cast<const char8_t*>(buffer.data()), charCount);
					break;
				}
				case Width_16 : {
					returnString += Text::toEscaped<std::wstring>(reinterpret_cast<const char16_t*>(buffer.data()), charCount);
					break;
				}
				case Width_32 : {
					returnString += Text::toEscaped<std::wstring>(reinterpret_cast<const char32_t*>(buffer.data()), charCount);
					break;
				}
			}
			returnString += L"\"";
		}
		else {
			if constexpr (sizeof(wchar_t) == 2) {
				switch (bufferWidth) {
					case Width_8 : {
						std::basic_string_view<char8_t> view(reinterpret_cast<const char8_t*>(buffer.data()), charCount);
						returnString = Text::utf8ToUtf16<std::wstring>(view);
						break;
					}
					case Width_16 : {
						// Direct copy if both are 16-bit.
						returnString.assign(reinterpret_cast<const wchar_t*>(buffer.data()), charCount);
						break;
					}
					case Width_32 : {
						std::basic_string_view<char32_t> view(reinterpret_cast<const char32_t*>(buffer.data()), charCount);
						returnString = Text::utf32ToUtf16<std::wstring>(view);
						break;
					}
				}
			} else if constexpr (sizeof(wchar_t) == 4) {
				switch (bufferWidth) {
					case Width_8 : {
						std::basic_string_view<char8_t> view(reinterpret_cast<const char8_t*>(buffer.data()), charCount);
						returnString = Text::utf8ToUtf32<std::wstring>(view);
						break;
					}
					case Width_16 : {
						std::basic_string_view<char16_t> view(reinterpret_cast<const char16_t*>(buffer.data()), charCount);
						returnString = Text::utf16ToUtf32<std::wstring>(view);
						break;
					}
					case Width_32 : {
						// Direct copy if both are 32-bit.
						returnString.assign(reinterpret_cast<const wchar_t*>(buffer.data()), charCount);
						break;
					}
				}
			}
		}
		return true;
	}

	/**
	 * Converts the string to a specified numeric constant type.
	 *
	 * \param type			The requested target numeric type.
	 * \return				Returns a Result containing the parsed value, or invalid if parsing fails.
	 **/
	Result String::convertTo(NumericConstant type) const {
		std::string utf8Str;
			
		switch (bufferWidth) {
			case Width_8 : {
				utf8Str.assign(reinterpret_cast<const char*>(buffer.data()), charCount);
				break;
			}
			case Width_16 : {
				std::basic_string_view<char16_t> view(reinterpret_cast<const char16_t*>(buffer.data()), charCount);
				utf8Str = Text::utf16ToUtf8<std::string>(view);
				break;
			}
			case Width_32 : {
				std::basic_string_view<char32_t> view(reinterpret_cast<const char32_t*>(buffer.data()), charCount);
				utf8Str = Text::utf32ToUtf8<std::string>(view);
				break;
			}
		}

		switch (type) {
			case NumericConstant::Unsigned : {
				bool overflowed = false;
				size_t eaten = 0;
				uint64_t val = Text::stoull(utf8Str.c_str(), 10, &eaten, UINT64_MAX, &overflowed);
					
				if (!overflowed && eaten) {
					return Result{ .type = NumericConstant::Unsigned, .value = { .uintVal = val } };
				}
					
				break;
			}
			case NumericConstant::Signed : {
				bool overflowed = false;
				size_t eaten = 0;
				uint64_t val = Text::stoull(utf8Str.c_str(), 10, &eaten, UINT64_MAX / 2ULL + 1ULL, &overflowed);
					
				if (!overflowed && eaten) {
					return Result{ .type = NumericConstant::Signed, .value = { .intVal = static_cast<int64_t>(val) } };
				}
					
				break;
			}
			case NumericConstant::Floating : {
				bool errored = false;
				size_t eaten = 0;
				double val = Text::atof(utf8Str.c_str(), &eaten, &errored);
					
				if (!errored && eaten) {
					return Result{ .type = NumericConstant::Floating, .value = { .doubleVal = val } };
				}
					
				break;
			}
			default : {
				break;
			}
		}
			
		return Result{ .type = NumericConstant::Invalid };
	}

	/**
	 * Initializes the contents of this string object from an evaluation result.
	 *
	 * \param obj			The evaluation result to read from.
	 * \return				Returns true if successful, false otherwise.
	 **/
	bool String::initializeFrom(const Result& obj) {
		std::string tempStr;
			
		switch (obj.type) {
			case NumericConstant::Unsigned : {
				try {
					tempStr = std::to_string(obj.value.uintVal);
				}
				catch (const std::bad_alloc&) {
					return false;
				}
					
				assignUtf8(tempStr.data(), tempStr.length());
				return true;
			}
			case NumericConstant::Signed : {
				try {
					tempStr = std::to_string(obj.value.intVal);
				}
				catch (const std::bad_alloc&) {
					return false;
				}
					
				assignUtf8(tempStr.data(), tempStr.length());
				return true;
			}
			case NumericConstant::Floating : {
				try {
					tempStr = std::to_string(obj.value.doubleVal);
				}
				catch (const std::bad_alloc&) {
					return false;
				}
					
				assignUtf8(tempStr.data(), tempStr.length());
				return true;
			}
			case NumericConstant::Object : {
				if (obj.value.objectVal) {
					std::wstring wStr;
						
					if (obj.value.objectVal->toString(wStr, 0, ToStringFlag_None)) {
						if constexpr (sizeof(wchar_t) == 2) {
							std::basic_string_view<char16_t> view(reinterpret_cast<const char16_t*>(wStr.data()), wStr.length());
							tempStr = Text::utf16ToUtf8<std::string>(view);
						}
						else if constexpr (sizeof(wchar_t) == 4) {
							std::basic_string_view<char32_t> view(reinterpret_cast<const char32_t*>(wStr.data()), wStr.length());
							tempStr = Text::utf32ToUtf8<std::string>(view);
						}
							
						assignUtf8(tempStr.data(), tempStr.length());
						return true;
					}
				}
					
				break;
			}
			default : {
				break;
			}
		}
			
		return false;
	}

	/**
	 * Creates a Result using a best-fit interpretation of the string as a number.
	 *
	 * The input string is analyzed to determine the most appropriate numeric interpretation (for example,
	 * integer vs. floating-point, and/or base detection). If no reasonable numeric interpretation can be
	 * made, the returned result is NaN (floating-point).
	 *
	 * \return				Returns a Result containing the interpreted numeric value.
	 **/
	Result String::bestFitNumeric() const {
		std::string utf8Str;

		switch (bufferWidth) {
			case Width_8 : {
				utf8Str.assign(reinterpret_cast<const char*>(buffer.data()), charCount);
				break;
			}
			case Width_16 : {
				std::basic_string_view<char16_t> view(reinterpret_cast<const char16_t*>(buffer.data()), charCount);
				utf8Str = Text::utf16ToUtf8<std::string>(view);
				break;
			}
			case Width_32 : {
				std::basic_string_view<char32_t> view(reinterpret_cast<const char32_t*>(buffer.data()), charCount);
				utf8Str = Text::utf32ToUtf8<std::string>(view);
				break;
			}
		}

		uint8_t base = 0;
		NumericConstant sncClass = Text::classifyString(utf8Str, &base);

		switch (sncClass) {
			case NumericConstant::Unsigned : {
				bool overflow = false;
				uint64_t uVal = Text::stoull(utf8Str.c_str(), base, nullptr, UINT64_MAX, &overflow);
					
				if (overflow && base == 0) {
					double dVal = Text::atof(utf8Str.c_str(), nullptr, &overflow);
					if (!overflow) {
						return Result::make(dVal);
					}
				}
					
				return Result::make(uVal);
			}
			case NumericConstant::Signed : {
				bool overflow = false;
				uint64_t uVal = Text::stoull(utf8Str.c_str(), base, nullptr, UINT64_MAX / 2 + 1, &overflow);
					
				if (overflow && base == 0) {
					double dVal = Text::atof(utf8Str.c_str(), nullptr, &overflow);
					if (!overflow) {
						return Result::make(dVal);
					}
				}
					
				return Result::make(static_cast<int64_t>(uVal));
			}
			case NumericConstant::Floating : {
				bool errored = false;
				size_t eaten = 0;
				double dVal = Text::atof(utf8Str.c_str(), &eaten, &errored);
					
				if (errored || !eaten) {
					return Result::make(std::nan(""));
				}
					
				return Result::make(dVal);
			}
			default : {
				return Result::make(std::nan(""));
			}
		}
	}

}	// namespace ve
