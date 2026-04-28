#include "String.h"

#include <cassert>


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
							outPtr[charCount+i] = static_cast<char8_t>(rhsString->getCodePoint(i));
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
							outPtr[charCount+i] = static_cast<char16_t>(rhsString->getCodePoint(i));
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
							outPtr[charCount+i] = static_cast<char32_t>(rhsString->getCodePoint(i));
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
					
				return Result{};
			}
		}
		else if (rhs.type == NumericConstant::Signed) {
			std::u32string str = getUtf32();
			Text::appendUtf32(str, uint32_t(rhs.value.intVal));
			String* newStr = context->allocateObject<String>();
					
			if (newStr) {
				std::string utf8 = Text::utf32ToUtf8(str);
				if (newStr->assignUtf8(utf8.c_str(), utf8.size())) {
					return newStr->createResult();
				}
				context->deallocateObject(newStr);
			}
		}
		else if (rhs.type == NumericConstant::Unsigned) {
			std::u32string str = getUtf32();
			Text::appendUtf32(str, uint32_t(rhs.value.uintVal));
			String* newStr = context->allocateObject<String>();
					
			if (newStr) {
				std::string utf8 = Text::utf32ToUtf8(str);
				if (newStr->assignUtf8(utf8.c_str(), utf8.size())) {
					return newStr->createResult();
				}
				context->deallocateObject(newStr);
			}
		}

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
			startIdx = arrayIndexToLinearIndex(idx0, this->charCount);
		}

		if (mask & ArrayExFlag_End) {
			endIdx = arrayIndexToLinearIndex(idx1, this->charCount) + 1;
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
			
		return Result{};
	}

	/**
	 * Assigns a value directly to a specified index, modifying the string in-place.
	 *
	 * \param index			The zero-based or negative offset index.
	 * \param rhs			The result containing the code point or string to insert.
	 * \return				Returns the assigned value on success, or Invalid on failure.
	 **/
	Result String::arrayAssign(int64_t index, const Result& rhs) {
		size_t lin = Object::arrayIndexToLinearIndex(index, charCount);
		if (lin == Object::InvalidIndex) { return Result{}; }

		std::u32string u32; 
		u32.reserve(charCount);
		for (size_t i = 0; i < charCount; ++i) { u32.push_back(getCodePoint(i)); }

		u32.erase(lin, 1);

		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_String)) {
			String* rStr = static_cast<String*>(rhs.value.objectVal);
			std::u32string ru32; 
			ru32.reserve(rStr->charCount);
			for (size_t i = 0; i < rStr->charCount; ++i) { ru32.push_back(rStr->getCodePoint(i)); }
			u32.insert(lin, ru32);
		} 
		else {
			uint32_t cp = 0;
			if (rhs.type == NumericConstant::Unsigned) { cp = static_cast<uint32_t>(rhs.value.uintVal); }
			else if (rhs.type == NumericConstant::Signed) { cp = static_cast<uint32_t>(rhs.value.intVal); }
			else { return Result{}; }
			u32.insert(u32.begin() + lin, cp);
		}

		std::string u8 = Text::utf32ToUtf8(u32);
		assignUtf8(u8.data(), u8.length());
		return rhs;
	}

	/**
	 * Assigns a value or merges a string into a sliced range, modifying the string in-place.
	 *
	 * \param startIdx		The starting index of the slice.
	 * \param endIdx		The ending index of the slice.
	 * \param flags			Bitmask defining slice boundary rules.
	 * \param rhs			The result containing the string or code point to merge.
	 * \return				Returns the assigned value on success, or Invalid on failure.
	 **/
	Result String::arrayAssignEx(int64_t startIdx, int64_t endIdx, uint32_t flags, const Result& rhs) {
		size_t idx0, idx1;
		if (!Object::resolveSliceBounds(startIdx, endIdx, flags, charCount, idx0, idx1)) {
			return Result{};
		}

		std::u32string u32 = getUtf32();

		u32.erase(u32.begin() + idx0, u32.begin() + idx1);

		if (rhs.type == NumericConstant::Object && rhs.value.objectVal && (rhs.value.objectVal->type() & BuiltInType_String)) {
			String* rStr = static_cast<String*>(rhs.value.objectVal);
			std::u32string ru32; 
			ru32.reserve(rStr->charCount);
			for (size_t i = 0; i < rStr->charCount; ++i) { ru32.push_back(rStr->getCodePoint(i)); }
			u32.insert(idx0, ru32);
		} 
		else {
			uint32_t cp = 0;
			if (rhs.type == NumericConstant::Unsigned) { cp = static_cast<uint32_t>(rhs.value.uintVal); }
			else if (rhs.type == NumericConstant::Signed) { cp = static_cast<uint32_t>(rhs.value.intVal); }
			else { return Result{}; }
			u32.insert(u32.begin() + idx0, cp);
		}

		std::string u8 = Text::utf32ToUtf8(u32);
		assignUtf8(u8.data(), u8.length());
		return rhs;
	}

	/**
	 * Serializes the string into a wide string representation.
	 *
	 * \param returnString	The output parameter to overwrite with the string content.
	 * \param depth			The current recursion depth.
	 * \param flags			Formatting flags (e.g., ToStringFlag_CString).
	 * \return				Returns true on success.
	 **/
	bool String::toString(std::string& returnString, uint32_t depth, uint32_t flags) const {
		static_cast<void>(depth);

		if (flags & ToStringFlag_CString) {
			returnString = "\"";
			switch (bufferWidth) {
				case Width_8 : {
					returnString += Text::toEscaped<std::string>(reinterpret_cast<const char8_t*>(buffer.data()), charCount);
					break;
				}
				case Width_16 : {
					returnString += Text::toEscaped<std::string>(reinterpret_cast<const char16_t*>(buffer.data()), charCount);
					break;
				}
				case Width_32 : {
					returnString += Text::toEscaped<std::string>(reinterpret_cast<const char32_t*>(buffer.data()), charCount);
					break;
				}
			}
			returnString += "\"";
		}
		else {
			switch (bufferWidth) {
				case Width_8 : {
					returnString.assign(reinterpret_cast<const std::string::value_type*>(buffer.data()), charCount);
					break;
				}
				case Width_16 : {
					if constexpr (sizeof(wchar_t) == sizeof(char16_t)) {
						std::basic_string_view<char16_t> view(reinterpret_cast<const char16_t*>(buffer.data()), charCount);
						returnString = Text::utf16ToUtf8<std::string>(view);
					}
					else if constexpr (sizeof(wchar_t) == sizeof(char32_t)) {
						std::basic_string_view<char32_t> view(reinterpret_cast<const char32_t*>(buffer.data()), charCount);
						returnString = Text::utf32ToUtf8<std::string>(view);
					}
					else {
						assert(false);
					}
					break;
				}
				case Width_32 : {
					std::basic_string_view<char32_t> view(reinterpret_cast<const char32_t*>(buffer.data()), charCount);
						returnString = Text::utf32ToUtf8<std::string>(view);
					break;
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
			
		return Result{};
	}

	/**
	 * Initializes the contents of this string object from an evaluation result.
	 * Must be called within a try/catch block.
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
					std::string str;
						
					if (obj.value.objectVal->toString(str, 0, ToStringFlag_None)) {
						assignUtf8(str.data(), str.length());
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
	 * Creates a casefolded copy of the string.
	 * Must be called within a try/catch block.
	 *
	 * \param ctx			The execution context for allocation.
	 * \return				Returns a new String object.
	 **/
	String* String::casefold(ExecutionContext* ctx) const {
		std::string foldedStr = Text::utf32ToUtf8(Text::casefoldUtf32<std::u32string>(this->getUtf32()));
		
		String* newStr = ctx->allocateObject<String>();
		if (newStr) {
			if (!newStr->assignUtf8(foldedStr.data(), foldedStr.length())) {
				ctx->deallocateObject(newStr);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}
		
		return newStr;
	}

	/**
	 * Creates a copy of the string centered in a string of length width.
	 * Must be called within a try/catch block.
	 *
	 * \param ctx			The execution context for allocation.
	 * \param width			The total width of the new string.
	 * \param fillChar		The padding character code point (defaults to space).
	 * \return				Returns a new String object, or nullptr on allocation failure.
	 **/
	String* String::center(ExecutionContext* ctx, size_t width, uint32_t fillChar) const {
		std::string centeredStr = Text::centerUtf8<std::string>(this->getUtf8(), this->charCount, width, fillChar);
		
		String* newStr = ctx->allocateObject<String>();
		if (newStr) {
			newStr->assignUtf8(centeredStr.data(), centeredStr.length());
		}
		
		return newStr;
	}

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
	int64_t String::count(const String* sub, int64_t start, int64_t end) const {
		int64_t len = static_cast<int64_t>(this->charCount);
		
		start = arrayIndexToLinearIndex(start, this->charCount);
		end = arrayIndexToLinearIndex(end, this->charCount) + 1;
		
		if (start > end || start >= len) {
			if (sub->charCount == 0) { return 1; }
			return 0;
		}
		
		std::string haystackStr;
		haystackStr.reserve(static_cast<size_t>(end - start));
		
		for (int64_t i = start; i < end; ++i) {
			Text::appendUtf8(haystackStr, this->getCodePoint(static_cast<size_t>(i)));
		}
		
		std::string needleStr = sub->getUtf8();
		
		return static_cast<int64_t>(Text::countUtf8<std::string>(haystackStr, needleStr));
	}

	/**
	 * Returns an encoded version of the string as a new String object.
	 * Must be called within a try/catch block.
	 *
	 * \param ctx			The runtime execution context.
	 * \param codePage		The target code page to encode to.
	 * \param errorPolicy	The policy for handling invalid characters.
	 * \return				Returns the newly encoded String.
	 **/
	String* String::encode(ExecutionContext* ctx, CodePage codePage, EncodingErrorPolicy errorPolicy) const {
		std::string currentUtf8 = this->getUtf8();
		std::string reencoded = Text::encodeUtf8<std::string>(currentUtf8, codePage, errorPolicy);
		
		String* newStr = ctx->allocateObject<String>();
		if (newStr) {
			if (!newStr->assignUtf8(reencoded.data(), reencoded.length())) {
				ctx->deallocateObject(newStr);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}
		
		return newStr;
	}

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
	bool String::endsWith(const String* suffix, int64_t start, int64_t end) const {
		int64_t len = static_cast<int64_t>(this->charCount);
		
		start = arrayIndexToLinearIndex(start, this->charCount);
		end = arrayIndexToLinearIndex(end, this->charCount) + 1;
		
		if (start > end || start >= len) {
			if (suffix->charCount == 0) { return true; }
			return false;
		}
		
		int64_t sliceCharLen = end - start;
		int64_t suffixCharLen = static_cast<int64_t>(suffix->charCount);
		
		if (suffixCharLen > sliceCharLen) { return false; }
		
		if (suffixCharLen == 0) { return true; }
		
		int64_t matchStart = end - suffixCharLen;
		
		for (int64_t i = 0; i < suffixCharLen; ++i) {
			if (this->getCodePoint(static_cast<size_t>(matchStart + i)) != suffix->getCodePoint(static_cast<size_t>(i))) {
				return false;
			}
		}
		
		return true;
	}

	/**
	 * Returns a copy of the string where all tab characters are replaced by one or more spaces.
	 * Must be called within a try/catch block.
	 *
	 * \param ctx			The runtime execution context.
	 * \param tabSize		The size of each tab stop (defaults to 8).
	 * \return				Returns the newly expanded String.
	 **/
	String* String::expandtabs(ExecutionContext* ctx, int64_t tabSize) const {
		std::string currentUtf8 = this->getUtf8();
		std::string expanded = Text::expandTabsUtf8<std::string>(currentUtf8, tabSize);
		
		String* newStr = ctx->allocateObject<String>();
		if (newStr) {
			if (!newStr->assignUtf8(expanded.data(), expanded.length())) {
				ctx->deallocateObject(newStr);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}
		
		return newStr;
	}

	/**
	 * Returns the lowest index in the string where substring sub is found within the slice [start, end].
	 * Must be called within a try/catch block.
	 *
	 * \param sub			The substring to search for.
	 * \param start			The starting index (character-based, handles negative).
	 * \param end			The ending index (character-based, handles negative).
	 * \return				Returns the character index of the match, or -1 if not found.
	 **/
	int64_t String::find(const String* sub, int64_t start, int64_t end) const {
		int64_t len = static_cast<int64_t>(this->charCount);
		
		start = arrayIndexToLinearIndex(start, this->charCount);
		end = arrayIndexToLinearIndex(end, this->charCount) + 1;
		
		if (start > end || start >= len) {
			if (sub->charCount == 0 && start <= len) {
				return start;
			}
			return -1;
		}
		
		int64_t subLen = static_cast<int64_t>(sub->charCount);
		
		if (subLen == 0) {
			return start;
		}
		
		int64_t searchLimit = end - subLen;
		
		for (int64_t i = start; i <= searchLimit; ++i) {
			bool match = true;
			
			for (int64_t j = 0; j < subLen; ++j) {
				if (this->getCodePoint(static_cast<size_t>(i + j)) != sub->getCodePoint(static_cast<size_t>(j))) {
					match = false;
					break;
				}
			}
			
			if (match) {
				return i;
			}
		}
		
		return -1;
	}
	
	/**
	 * Returns a formatted version of the string, replacing {} and {N} placeholders with arguments.
	 * Must be called within a try/catch block.
	 *
	 * \param ctx			The runtime execution context.
	 * \param args			A vector of UTF-8 string representations of the arguments.
	 * \return				Returns the newly formatted String.
	 **/
	String* String::format(ExecutionContext* ctx, const std::vector<Result>& args) const {
		std::string currentUtf8 = this->getUtf8();
		std::string formatted;

		try {
			formatted = Text::formatUtf8<std::string>(currentUtf8, [&](size_t argIndex, const std::string& formatter) -> std::string {
				if (argIndex < args.size()) {
					try {
						switch (args[argIndex].type) {
							case NumericConstant::Unsigned : {
								return std::vformat(formatter, std::make_format_args(args[argIndex].value.uintVal));
							}
							case NumericConstant::Signed : {
								return std::vformat(formatter, std::make_format_args(args[argIndex].value.intVal));
							}
							case NumericConstant::Floating : {
								return std::vformat(formatter, std::make_format_args(args[argIndex].value.doubleVal));
							}
							case NumericConstant::Object : {
								if (args[argIndex].value.objectVal != nullptr) {
									std::string tmp;
									if (!args[argIndex].value.objectVal->toString(tmp, 0, ToStringFlag_None/*ToStringFlag_CString | ToStringFlag_LowQualityFloat*/)) {
										return std::vformat(formatter, std::make_format_args("<error>"));
									}
									return std::vformat(formatter, std::make_format_args(tmp));
								}
								return std::vformat(formatter, std::make_format_args("<null>"));
							}
							default : {
								return std::vformat(formatter, std::make_format_args("<null>"));
							}
						}
					}
					catch (...) {
						return formatter;
					}
				}
				return formatter;
			});
		}
		catch (...) {
			formatted.clear();
		}

		String* newStr = ctx->allocateObject<String>();
		if (newStr) {
			if (!newStr->assignUtf8(formatted.data(), formatted.length())) {
				ctx->deallocateObject(newStr);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}

		return newStr;
	}

	/**
	 * Returns true if all characters in the string are alphanumeric and there is at least one character.
	 * Must be called within a try/catch block.
	 * 
	 * \return				Returns true if the string is alphanumeric, false otherwise.
	 **/
	bool String::isalnum() const {
		auto currentUtf32 = this->getUtf32();
		
		return Text::isAlnumUtf32<decltype(currentUtf32)>(currentUtf32);
	}

	/**
	 * Returns true if all characters in the string are alphabetic and there is at least one character.
	 * Must be called within a try/catch block.
	 *
	 * \return				Returns true if the string is alphabetic, false otherwise.
	 **/
	bool String::isalpha() const {
		auto currentUtf32 = this->getUtf32();
		
		return Text::isAlphaUtf32<decltype(currentUtf32)>(currentUtf32);
	}

	/**
	 * Returns true if the string is empty or all characters in the string are ASCII, false otherwise.
	 * Must be called within a try/catch block.
	 *
	 * \return				Returns true if the string is ASCII, false otherwise.
	 **/
	bool String::isAscii() const {
		auto currentUtf32 = this->getUtf32();
		
		return Text::isAsciiUtf32<decltype(currentUtf32)>(currentUtf32);
	}

	/**
	 * Returns true if all characters in the string are decimal characters and there is at least one character, false otherwise.
	 * Must be called within a try/catch block.
	 *
	 * \return				Returns true if the string is decimal, false otherwise.
	 **/
	bool String::isdecimal() const {
		auto currentUtf32 = this->getUtf32();
		
		return Text::isDecimalUtf32<decltype(currentUtf32)>(currentUtf32);
	}

	/**
	 * Returns true if all characters in the string are digits and there is at least one character, false otherwise.
	 * Must be called within a try/catch block.
	 *
	 * \return				Returns true if the string is composed entirely of digits, false otherwise.
	 **/
	bool String::isdigit() const {
		auto currentUtf32 = this->getUtf32();
		
		return Text::isDigitUtf32<decltype(currentUtf32)>(currentUtf32);
	}

	/**
	 * Returns true if the string is a valid identifier and is not empty, false otherwise.
	 * Must be called within a try/catch block.
	 *
	 * \return				Returns true if the string is a valid identifier, false otherwise.
	 **/
	bool String::isidentifier() const {
		auto currentUtf32 = this->getUtf32();
		
		return Text::isIdentifierUtf32<decltype(currentUtf32)>(currentUtf32);
	}

	/**
	 * Returns true if all cased characters in the string are lowercase and there is at least one cased character, false otherwise.
	 * Must be called within a try/catch block.
	 *
	 * \return				Returns true if the string is lowercase, false otherwise.
	 **/
	bool String::islower() const {
		auto currentUtf32 = this->getUtf32();
		
		return Text::isLowerUtf32<decltype(currentUtf32)>(currentUtf32);
	}

	/**
	 * Returns true if all characters in the string are numeric characters and there is at least one character, false otherwise.
	 * Must be called within a try/catch block.
	 *
	 * \return				Returns true if the string is numeric, false otherwise.
	 **/
	bool String::isnumeric() const {
		auto currentUtf32 = this->getUtf32();
		
		return Text::isNumericUtf32<decltype(currentUtf32)>(currentUtf32);
	}

	/**
	 * Returns true if all characters in the string are printable or the string is empty, false otherwise.
	 * Must be called within a try/catch block.
	 *
	 * \return				Returns true if the string is printable, false otherwise.
	 **/
	bool String::isprintable() const {
		auto currentUtf32 = this->getUtf32();
		
		return Text::isPrintableUtf32<decltype(currentUtf32)>(currentUtf32);
	}

	/**
	 * Returns true if all characters in the string are whitespace characters and there is at least one character, false otherwise.
	 * Must be called within a try/catch block.
	 *
	 * \return				Returns true if the string is whitespace, false otherwise.
	 **/
	bool String::isspace() const {
		auto currentUtf32 = this->getUtf32();
		
		return Text::isSpaceUtf32<decltype(currentUtf32)>(currentUtf32);
	}

	/**
	 * Returns true if the string is a title-cased string and there is at least one character, false otherwise.
	 * Must be called within a try/catch block.
	 *
	 * \return				Returns true if the string is title-cased, false otherwise.
	 **/
	bool String::istitle() const {
		auto currentUtf32 = this->getUtf32();
		
		return Text::isTitleUtf32<decltype(currentUtf32)>(currentUtf32);
	}

	/**
	 * Returns true if all cased characters in the string are uppercase and there is at least one cased character, false otherwise.
	 * Must be called within a try/catch block.
	 *
	 * \return				Returns true if the string is uppercase, false otherwise.
	 **/
	bool String::isupper() const {
		auto currentUtf32 = this->getUtf32();
		
		return Text::isUpperUtf32<decltype(currentUtf32)>(currentUtf32);
	}

	/**
	 * Returns a left-justified string of length width. 
	 * Padding is done using the specified fill character (default is an ASCII space).
	 * Must be called within a try/catch block.
	 *
	 * \param width			The total length of the newly justified string.
	 * \param fillchar		The UTF-32 code point of the padding character.
	 * \return				Returns the justified string as a new String.
	 **/
	String* String::ljust(size_t width, uint32_t fillchar) const {
		auto currentUtf32 = this->getUtf32();
		
		auto newStr8 = Text::utf32ToUtf8(Text::ljustUtf32<std::u32string>(currentUtf32, width, fillchar));
		String* newStr = context->allocateObject<String>();
		if (newStr) {
			if (!newStr->assignUtf8(newStr8.data(), newStr8.length())) {
				context->deallocateObject(newStr);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}

		return newStr;
	}

	/**
	 * Creates a lowercased copy of the string.
	 * Must be called within a try/catch block.
	 *
	 * \param ctx			The execution context for allocation.
	 * \return				Returns a new String object.
	 **/
	String* String::lower(ExecutionContext* ctx) const {
		std::string lowerStr = Text::utf32ToUtf8(Text::lowerUtf32<std::u32string>(this->getUtf32()));
		
		String* newStr = ctx->allocateObject<String>();
		if (newStr) {
			if (!newStr->assignUtf8(lowerStr.data(), lowerStr.length())) {
				ctx->deallocateObject(newStr);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}
		
		return newStr;
	}

	/**
	 * Returns a copy of the string with leading characters removed.
	 * If chars is omitted or empty, whitespace characters are removed.
	 * Must be called within a try/catch block.
	 *
	 * \param ctx			The execution context for allocation.
	 * \param chars			The characters to remove.
	 * \return				Returns a new String object.
	 **/
	String* String::lstrip(ExecutionContext* ctx, const std::u32string& chars) const {
		std::string strippedStr = Text::utf32ToUtf8(Text::lstripUtf32<std::u32string>(this->getUtf32(), chars));
		
		String* newStr = ctx->allocateObject<String>();
		if (newStr) {
			if (!newStr->assignUtf8(strippedStr.data(), strippedStr.length())) {
				ctx->deallocateObject(newStr);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}
		
		return newStr;
	}

	/**
	 * Returns a copy of the string with the given prefix removed if it is present.
	 * Must be called within a try/catch block.
	 *
	 * \param ctx			The execution context for allocation.
	 * \param prefix		The prefix string to remove.
	 * \return				Returns a new String object.
	 **/
	String* String::removeprefix(ExecutionContext* ctx, const std::u32string& prefix) const {
		std::string removedStr = Text::utf32ToUtf8(Text::removePrefixUtf32<std::u32string>(this->getUtf32(), prefix));
		
		String* newStr = ctx->allocateObject<String>();
		if (newStr) {
			if (!newStr->assignUtf8(removedStr.data(), removedStr.length())) {
				ctx->deallocateObject(newStr);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}
		
		return newStr;
	}

	/**
	 * Returns a copy of the string with the given suffix removed if it is present.
	 * Must be called within a try/catch block.
	 *
	 * \param ctx			The execution context for allocation.
	 * \param suffix		The suffix string to remove.
	 * \return				Returns a new String object.
	 **/
	String* String::removesuffix(ExecutionContext* ctx, const std::u32string& suffix) const {
		std::string removedStr = Text::utf32ToUtf8(Text::removeSuffixUtf32<std::u32string>(this->getUtf32(), suffix));
		
		String* newStr = ctx->allocateObject<String>();
		if (newStr) {
			if (!newStr->assignUtf8(removedStr.data(), removedStr.length())) {
				ctx->deallocateObject(newStr);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}
		
		return newStr;
	}

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
	String* String::replace(ExecutionContext* ctx, const std::u32string& oldStr, const std::u32string& newStr, int64_t count) const {
		std::string replacedStr = Text::utf32ToUtf8(Text::replaceUtf32<std::u32string>(this->getUtf32(), oldStr, newStr, count));
		
		String* newStrObj = ctx->allocateObject<String>();
		if (newStrObj) {
			if (!newStrObj->assignUtf8(replacedStr.data(), replacedStr.length())) {
				ctx->deallocateObject(newStrObj);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}
		
		return newStrObj;
	}

	/**
	 * Returns the highest index in the string where a substring is found within the given boundaries.
	 * Must be called within a try/catch block.
	 *
	 * \param sub			The substring to search for.
	 * \param start			The starting character index.
	 * \param end			The ending character index.
	 * \return				Returns the index of the substring, or -1 if not found.
	 **/
	int64_t String::rfind(const std::u32string& sub, int64_t start, int64_t end) const {
		auto currentUtf32 = this->getUtf32();

		start = arrayIndexToLinearIndex(start, this->charCount);
		end = arrayIndexToLinearIndex(end, this->charCount) + 1;
		
		return Text::rfindUtf32<decltype(currentUtf32)>(currentUtf32, sub, start, end);
	}

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
	String* String::rjust(ExecutionContext* ctx, size_t width, uint32_t fillchar) const {
		std::string justifiedStr = Text::utf32ToUtf8(Text::rjustUtf32<std::u32string>(this->getUtf32(), width, fillchar));
		
		String* newStr = ctx->allocateObject<String>();
		if (newStr) {
			if (!newStr->assignUtf8(justifiedStr.data(), justifiedStr.length())) {
				ctx->deallocateObject(newStr);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}
		
		return newStr;
	}

	/**
	 * Returns a copy of the string with trailing characters removed.
	 * If chars is omitted or empty, whitespace characters are removed.
	 * Must be called within a try/catch block.
	 *
	 * \param ctx			The execution context for allocation.
	 * \param chars			The characters to remove.
	 * \return				Returns a new String object.
	 **/
	String* String::rstrip(ExecutionContext* ctx, const std::u32string& chars) const {
		std::string strippedStr = Text::utf32ToUtf8(Text::rstripUtf32<std::u32string>(this->getUtf32(), chars));
		
		String* newStr = ctx->allocateObject<String>();
		if (newStr) {
			if (!newStr->assignUtf8(strippedStr.data(), strippedStr.length())) {
				ctx->deallocateObject(newStr);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}
		
		return newStr;
	}

	/**
	 * Returns true if the string slice begins with the specified prefix, false otherwise.
	 * Must be called within a try/catch block.
	 *
	 * \param prefix		The prefix substring to check for.
	 * \param start			The starting character index.
	 * \param end			The ending character index.
	 * \return				Returns true if the string starts with the prefix.
	 **/
	bool String::startswith(const std::u32string& prefix, int64_t start, int64_t end) const {
		auto currentUtf32 = this->getUtf32();

		start = arrayIndexToLinearIndex(start, this->charCount);
		end = arrayIndexToLinearIndex(end, this->charCount) + 1;
		
		return Text::startsWithUtf32<decltype(currentUtf32)>(currentUtf32, prefix, start, end);
	}

	/**
	 * Returns a copy of the string with leading and trailing characters removed.
	 * If chars is omitted or empty, whitespace characters are removed.
	 * Must be called within a try/catch block.
	 *
	 * \param ctx			The execution context for allocation.
	 * \param chars			The characters to remove.
	 * \return				Returns a new String object.
	 **/
	String* String::strip(ExecutionContext* ctx, const std::u32string& chars) const {
		std::string strippedStr = Text::utf32ToUtf8(Text::stripUtf32<std::u32string>(this->getUtf32(), chars));
		
		String* newStr = ctx->allocateObject<String>();
		if (newStr) {
			if (!newStr->assignUtf8(strippedStr.data(), strippedStr.length())) {
				ctx->deallocateObject(newStr);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}
		
		return newStr;
	}

	/**
	 * Creates a copy of the string with uppercase characters converted to lowercase and vice versa.
	 * Must be called within a try/catch block.
	 *
	 * \param ctx			The execution context for allocation.
	 * \return				Returns a new String object.
	 **/
	String* String::swapcase(ExecutionContext* ctx) const {
		std::string swappedStr = Text::utf32ToUtf8(Text::swapcaseUtf32<std::u32string>(this->getUtf32()));
		
		String* newStr = ctx->allocateObject<String>();
		if (newStr) {
			if (!newStr->assignUtf8(swappedStr.data(), swappedStr.length())) {
				ctx->deallocateObject(newStr);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}
		
		return newStr;
	}

	/**
	 * Creates a titlecased copy of the string.
	 * Must be called within a try/catch block.
	 *
	 * \param ctx			The execution context for allocation.
	 * \return				Returns a new String object.
	 **/
	String* String::title(ExecutionContext* ctx) const {
		std::string titledStr = Text::utf32ToUtf8(Text::titleUtf32<std::u32string>(this->getUtf32()));
		
		String* newStr = ctx->allocateObject<String>();
		if (newStr) {
			if (!newStr->assignUtf8(titledStr.data(), titledStr.length())) {
				ctx->deallocateObject(newStr);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}
		
		return newStr;
	}

	/**
	 * Creates an uppercase copy of the string.
	 * Must be called within a try/catch block.
	 *
	 * \param ctx			The execution context for allocation.
	 * \return				Returns a new String object.
	 **/
	String* String::upper(ExecutionContext* ctx) const {
		std::string upperStr = Text::utf32ToUtf8(Text::upperUtf32<std::u32string>(this->getUtf32()));
		
		String* newStr = ctx->allocateObject<String>();
		if (newStr) {
			if (!newStr->assignUtf8(upperStr.data(), upperStr.length())) {
				ctx->deallocateObject(newStr);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}
		
		return newStr;
	}

	/**
	 * Returns a copy of the string left-filled with zeros to a length of width.
	 * Must be called within a try/catch block.
	 *
	 * \param ctx			The execution context for allocation.
	 * \param width			The target total length of the newly padded string.
	 * \return				Returns a new String object.
	 **/
	String* String::zfill(ExecutionContext* ctx, size_t width) const {
		std::string paddedStr = Text::utf32ToUtf8(Text::zfillUtf32<std::u32string>(this->getUtf32(), width));
		
		String* newStr = ctx->allocateObject<String>();
		if (newStr) {
			if (!newStr->assignUtf8(paddedStr.data(), paddedStr.length())) {
				ctx->deallocateObject(newStr);
				throw ErrorCode::Object_Initialization_Failed;
			}
		}
		
		return newStr;
	}

	/**
	 * Retrieves the character code point at the specified index.
	 *
	 * \param index			The zero-based or negative offset index.
	 * \return				Returns a Result containing the code point, or Invalid if out of bounds.
	 **/
	Result String::at(int64_t index) const {
		size_t linearIndex = Object::arrayIndexToLinearIndex(index, charCount);
		
		if (linearIndex == Object::InvalidIndex) {
			return Result{};
		}
		
		Result res;
		res.type = NumericConstant::Unsigned;
		res.value.uintVal = static_cast<uint64_t>(getCodePoint(linearIndex));
		return res;
	}

	/**
	 * Pushes a string expression to the back of the string.
	 * 
	 * \param result		The result to push.
	 * \return				Returns true if the item was added. False indicates a memory failure or incompatible type.
	 **/
	bool String::pushBack(const Result& result) {
		try {
			auto res = (*this) += result;
			if (res.type == NumericConstant::Invalid) { return false; }
			
			return true;
		}
		catch (...) {
			return false;
		}
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
