#pragma once

#include "TextPolicy.h"

#include <cstdint>
#include <cwctype>
#include <string>
#include <vector>

namespace ve {

	/**
	 * Provides string manipulation, Unicode folding, and text comparison utilities.
	 **/
	class Text {
	public :
		// == Enumerations.
		// Value returned when a sequence is malformed or invalid.
		static constexpr uint32_t		UTF_INVALID = 0xFFFFFFFF;

		// Standard Unicode replacement character for malformed sequences.
		static constexpr uint32_t		UNICODE_REPLACEMENT_CHAR = 0xFFFD;


		// == Functions.
		// ===============================
		// UTF & Encoding Conversions
		// ===============================
		/**
		 * Gets the next UTF-32 character from a stream or error (UTF_INVALID).
		 *
		 * \param str		The string to parse. Accepts any 32-bit type (char32_t, uint32_t, POSIX wchar_t).
		 * \param len		The length of the string to which str points.
		 * \param outSize	Optional pointer to a size_t that will contain the number of characters eaten from str during the parsing.
		 * \return			Returns the next character as a UTF-32 code.
		 **/
		template <typename CharT = char32_t>
		static inline uint32_t			nextUtf32Char(const CharT* str, size_t len, size_t* outSize = nullptr) {
			static_assert(sizeof(CharT) == 4, "nextUtf32Char: Character type must be 32 bits (char32_t, uint32_t, POSIX wchar_t, etc.)");

			if (len == 0) {
				if (outSize) { (*outSize) = 0; }
				return 0;
			}
			if (outSize) { (*outSize) = 1; }

			uint32_t ret = static_cast<uint32_t>(*str);
			if (ret & 0xFFE00000) { return UTF_INVALID; }
			return ret;
		}

		/**
		 * Gets the next UTF-16 character from a stream or error (UTF_INVALID).
		 *
		 * \param str		The string to parse. Accepts any 16-bit type (char16_t, uint16_t, Windows wchar_t).
		 * \param len		The length of the string to which str points.
		 * \param outSize	Optional pointer to a size_t that will contain the number of characters eaten from str during the parsing.
		 * \return			Returns the next character as a UTF-32 code.
		 **/
		template <typename CharT = char16_t>
		static inline uint32_t			nextUtf16Char(const CharT* str, size_t len, size_t* outSize = nullptr) {
			static_assert(sizeof(CharT) == 2, "nextUtf16Char: Character type must be 16 bits (char16_t, uint16_t, Windows wchar_t, etc.)");

			if (len == 0) {
				if (outSize) { (*outSize) = 0; }
				return 0;
			}

			// Get the low bits by casting the value, avoiding strict-aliasing violations.
			uint32_t ret = static_cast<uint16_t>(*str);
			uint32_t top = ret & 0xFC00U;
			
			// Check to see if this is a surrogate pair.
			if (top == 0xD800U) {
				if (len < 2) {
					// Not enough space to decode correctly.
					if (outSize) { (*outSize) = 1; }
					return UTF_INVALID;
				}

				// Need to add the next character to it.
				// Remove the 0xD800.
				ret &= ~0xD800U;
				ret <<= 10;

				// Get the second set of bits by casting the value.
				uint32_t next = static_cast<uint16_t>(*(++str));
				if ((next & 0xFC00U) != 0xDC00U) {
					// Invalid second character. Standard defines this as an error.
					if (outSize) { (*outSize) = 1; }
					return UTF_INVALID;
				}
				if (outSize) { (*outSize) = 2; }

				next &= ~0xDC00U;

				// Add the second set of bits.
				ret |= next;

				return ret + 0x10000U;
			}

			if (outSize) { (*outSize) = 1; }
			return ret;
		}

		/**
		 * Gets the next UTF-8 character from a stream or error (UTF_INVALID).
		 *
		 * \param str		The string to parse. Accepts any 8-bit type (char, char8_t, uint8_t).
		 * \param len		The length of the string to which str points.
		 * \param outSize	Optional pointer to a size_t that will contain the number of characters eaten from str during the parsing.
		 * \return			Returns the next character as a UTF-32 code.
		 **/
		template <typename CharT = char8_t>
		static inline uint32_t			nextUtf8Char(const CharT* str, size_t len, size_t* outSize = nullptr) {
			static_assert(sizeof(CharT) == 1, "nextUtf8Char: Character type must be 8 bits (char, char8_t, uint8_t, etc.)");

			if (len == 0) {
				if (outSize) { (*outSize) = 0; }
				return 0;
			}

			// Get the low bits by casting the value, avoiding strict-aliasing violations.
			uint32_t ret = static_cast<uint8_t>(*str);

			// The first byte is a special case.
			if ((ret & 0x80U) == 0) {
				// We are done.
				if (outSize) { (*outSize) = 1; }
				return ret;
			}

			// We are in a multi-byte sequence. Get bits from the top, starting from the second bit.
			uint32_t i = 0x20;
			uint32_t seqLen = 2;
			uint32_t mask = 0xC0U;
			
			while (ret & i) {
				// Add this bit to the mask to be removed later.
				mask |= i;
				i >>= 1;
				++seqLen;
				if (i == 0) {
					// Invalid sequence.
					if (outSize) { (*outSize) = 1; }
					return UTF_INVALID;
				}
			}

			// Bounds checking.
			if (seqLen > len) {
				if (outSize) { (*outSize) = len; }
				return UTF_INVALID;
			}

			// We know the size now, so set it.
			// Even if we return an invalid character we want to return the correct number of bytes to skip.
			if (outSize) { (*outSize) = seqLen; }

			// If the length is greater than 4, it is invalid.
			if (seqLen > 4) { return UTF_INVALID; }

			// Mask out the leading bits.
			ret &= ~mask;

			// For every trailing bit, add it to the final value.
			for (uint32_t bitIdx = seqLen - 1; bitIdx--; ) {
				uint32_t thisChar = static_cast<uint8_t>(*(++str));
				// Validate the byte.
				if ((thisChar & 0xC0U) != 0x80U) { return UTF_INVALID; }

				ret <<= 6;
				ret |= (thisChar & 0x3F);
			}

			// Finally done.
			return ret;
		}

		/**
		 * Gets the size of the given UTF-8 character.
		 *
		 * \param str		Pointer to the UTF-8 characters to decode. Accepts any 8-bit type (char, char8_t, uint8_t).
		 * \param len		The number of characters to which str points.
		 * \return			Returns the size of the UTF-8 character to which str points.
		 **/
		template <typename CharT>
		static inline size_t			utf8CharSize(const CharT* str, size_t len) {
			static_assert(sizeof(CharT) == 1, "utf8CharSize requires an exactly 8-bit character type (e.g., char, char8_t, uint8_t).");

			if (len == 0) { return 0; }

			// Get the low bits by casting the value, avoiding strict-aliasing violations.
			uint32_t ret = static_cast<uint8_t>(*str);

			// The first byte is a special case.
			if ((ret & 0x80U) == 0) { return 1; }

			// We are in a multi-byte sequence. Get bits from the top, starting from the second bit.
			uint32_t i = 0x20;
			size_t seqLen = 2;
			
			while (ret & i) {
				// Add this bit to the mask to be removed later.
				i >>= 1;
				++seqLen;
				if (i == 0) { return 1; }
			}

			// Bounds checking.
			if (seqLen > len) { return len; }
			return seqLen;
		}


		// ===============================
		// Raw Pointer Writers (Pass 2 Helpers)
		// ===============================
		/**
		 * Encodes a UTF-32 codepoint into UTF-8 and writes it directly to a memory buffer.
		 * Advances the pointer automatically to the next write position.
		 *
		 * \param outPtr	A reference to the destination pointer. Will be advanced by the number of characters written.
		 * \param cp		The 32-bit codepoint to encode and write.
		 **/
		template <typename CharT>
		static inline void				writeUtf8(CharT*& outPtr, uint32_t cp) {
			if (cp <= 0x7F) {
				(*outPtr++) = static_cast<CharT>(cp);
			}
			else if (cp <= 0x7FF) {
				(*outPtr++) = static_cast<CharT>(0xC0 | (cp >> 6));
				(*outPtr++) = static_cast<CharT>(0x80 | (cp & 0x3F));
			}
			else if (cp <= 0xFFFF) {
				(*outPtr++) = static_cast<CharT>(0xE0 | (cp >> 12));
				(*outPtr++) = static_cast<CharT>(0x80 | ((cp >> 6) & 0x3F));
				(*outPtr++) = static_cast<CharT>(0x80 | (cp & 0x3F));
			}
			else if (cp <= 0x10FFFF) {
				(*outPtr++) = static_cast<CharT>(0xF0 | (cp >> 18));
				(*outPtr++) = static_cast<CharT>(0x80 | ((cp >> 12) & 0x3F));
				(*outPtr++) = static_cast<CharT>(0x80 | ((cp >> 6) & 0x3F));
				(*outPtr++) = static_cast<CharT>(0x80 | (cp & 0x3F));
			}
			else {
				writeUtf8(outPtr, UNICODE_REPLACEMENT_CHAR);
			}
		}

		/**
		 * Encodes a UTF-32 codepoint into UTF-16 and writes it directly to a memory buffer.
		 * Advances the pointer automatically to the next write position.
		 *
		 * \param outPtr	A reference to the destination pointer. Will be advanced by the number of characters written.
		 * \param cp		The 32-bit codepoint to encode and write.
		 **/
		template <typename CharT>
		static inline void				writeUtf16(CharT*& outPtr, uint32_t cp) {
			if (cp <= 0xFFFF) {
				(*outPtr++) = static_cast<CharT>(cp);
			}
			else if (cp <= 0x10FFFF) {
				cp -= 0x10000;
				(*outPtr++) = static_cast<CharT>(0xD800 | (cp >> 10));
				(*outPtr++) = static_cast<CharT>(0xDC00 | (cp & 0x3FF));
			}
			else {
				(*outPtr++) = static_cast<CharT>(UNICODE_REPLACEMENT_CHAR);
			}
		}

		/**
		 * Writes a UTF-32 codepoint directly to a memory buffer.
		 * Advances the pointer automatically to the next write position.
		 *
		 * \param outPtr	A reference to the destination pointer. Will be advanced by 1.
		 * \param cp		The 32-bit codepoint to write.
		 **/
		template <typename CharT>
		static inline void				writeUtf32(CharT*& outPtr, uint32_t cp) {
			if (cp <= 0x10FFFF) {
				(*outPtr++) = static_cast<CharT>(cp);
			}
			else {
				(*outPtr++) = static_cast<CharT>(UNICODE_REPLACEMENT_CHAR);
			}
		}

		
		// ===============================
		// Two-Pass String Conversions
		// ===============================
		/**
		 * Converts an 8-bit UTF-8 string to a 16-bit UTF-16 string.
		 * Must be called within a try/catch block.
		 *
		 * \param utf8		The UTF-8 string to convert.
		 * \return			Returns the converted 16-bit string.
		 **/
		template <typename OutStringT = std::u16string, typename InStringT>
		static inline OutStringT		utf8ToUtf16(const InStringT& utf8) {
			static_assert(sizeof(typename OutStringT::value_type) == 2, "Output string must have 16-bit characters.");
			static_assert(sizeof(typename InStringT::value_type) == 1, "Input string must have 8-bit characters.");

			size_t exactLen = 0;
			const auto* ptr = utf8.data();
			size_t len = utf8.length();
			
			while (len > 0) {
				size_t eaten = 0;
				uint32_t cp = nextUtf8Char(ptr, len, &eaten);
				if (cp == UTF_INVALID || eaten == 0) {
					if (eaten == 0) { eaten = 1; }
					cp = UNICODE_REPLACEMENT_CHAR;
				}
				exactLen += getUtf16EncodedSize(cp);
				ptr += eaten;
				len -= eaten;
			}

			OutStringT result;
			result.resize(exactLen);
			
			auto* outPtr = result.data();
			ptr = utf8.data();
			len = utf8.length();
			
			while (len > 0) {
				size_t eaten = 0;
				uint32_t cp = nextUtf8Char(ptr, len, &eaten);
				if (cp == UTF_INVALID || eaten == 0) {
					if (eaten == 0) { eaten = 1; }
					cp = UNICODE_REPLACEMENT_CHAR;
				}
				writeUtf16(outPtr, cp);
				ptr += eaten;
				len -= eaten;
			}
			return result;
		}

		/**
		 * Converts a 16-bit UTF-16 string to an 8-bit UTF-8 string.
		 * Must be called within a try/catch block.
		 *
		 * \param utf16		The UTF-16 string to convert.
		 * \return			Returns the converted 8-bit string.
		 **/
		template <typename OutStringT = std::string, typename InStringT>
		static inline OutStringT		utf16ToUtf8(const InStringT& utf16) {
			static_assert(sizeof(typename OutStringT::value_type) == 1, "Output string must have 8-bit characters.");
			static_assert(sizeof(typename InStringT::value_type) == 2, "Input string must have 16-bit characters.");

			size_t exactLen = 0;
			const auto* ptr = utf16.data();
			size_t len = utf16.length();
			
			while (len > 0) {
				size_t eaten = 0;
				uint32_t cp = nextUtf16Char(ptr, len, &eaten);
				if (cp == UTF_INVALID || eaten == 0) {
					if (eaten == 0) { eaten = 1; }
					cp = UNICODE_REPLACEMENT_CHAR;
				}
				exactLen += getUtf8EncodedSize(cp);
				ptr += eaten;
				len -= eaten;
			}

			OutStringT result;
			result.resize(exactLen);
			
			auto* outPtr = result.data();
			ptr = utf16.data();
			len = utf16.length();
			
			while (len > 0) {
				size_t eaten = 0;
				uint32_t cp = nextUtf16Char(ptr, len, &eaten);
				if (cp == UTF_INVALID || eaten == 0) {
					if (eaten == 0) { eaten = 1; }
					cp = UNICODE_REPLACEMENT_CHAR;
				}
				writeUtf8(outPtr, cp);
				ptr += eaten;
				len -= eaten;
			}
			return result;
		}

		/**
		 * Converts an 8-bit UTF-8 string to a 32-bit UTF-32 string.
		 * Must be called within a try/catch block.
		 *
		 * \param utf8		The UTF-8 string to convert.
		 * \return			Returns the converted 32-bit string.
		 **/
		template <typename OutStringT = std::u32string, typename InStringT>
		static inline OutStringT		utf8ToUtf32(const InStringT& utf8) {
			static_assert(sizeof(typename OutStringT::value_type) == 4, "Output string must have 32-bit characters.");
			static_assert(sizeof(typename InStringT::value_type) == 1, "Input string must have 8-bit characters.");

			size_t exactLen = 0;
			const auto* ptr = utf8.data();
			size_t len = utf8.length();
			
			while (len > 0) {
				size_t eaten = 0;
				uint32_t cp = nextUtf8Char(ptr, len, &eaten);
				if (cp == UTF_INVALID || eaten == 0) {
					if (eaten == 0) { eaten = 1; }
					cp = UNICODE_REPLACEMENT_CHAR;
				}
				exactLen += getUtf32EncodedSize(cp);
				ptr += eaten;
				len -= eaten;
			}

			OutStringT result;
			result.resize(exactLen);
			
			auto* outPtr = result.data();
			ptr = utf8.data();
			len = utf8.length();
			
			while (len > 0) {
				size_t eaten = 0;
				uint32_t cp = nextUtf8Char(ptr, len, &eaten);
				if (cp == UTF_INVALID || eaten == 0) {
					if (eaten == 0) { eaten = 1; }
					cp = UNICODE_REPLACEMENT_CHAR;
				}
				writeUtf32(outPtr, cp);
				ptr += eaten;
				len -= eaten;
			}
			return result;
		}

		/**
		 * Converts a 32-bit UTF-32 string to an 8-bit UTF-8 string.
		 * Must be called within a try/catch block.
		 *
		 * \param utf32		The UTF-32 string to convert.
		 * \return			Returns the converted 8-bit string.
		 **/
		template <typename OutStringT = std::string, typename InStringT>
		static inline OutStringT		utf32ToUtf8(const InStringT& utf32) {
			static_assert(sizeof(typename OutStringT::value_type) == 1, "Output string must have 8-bit characters.");
			static_assert(sizeof(typename InStringT::value_type) == 4, "Input string must have 32-bit characters.");

			size_t exactLen = 0;
			const auto* ptr = utf32.data();
			size_t len = utf32.length();
			
			while (len > 0) {
				size_t eaten = 0;
				uint32_t cp = nextUtf32Char(ptr, len, &eaten);
				if (cp == UTF_INVALID || eaten == 0) {
					if (eaten == 0) { eaten = 1; }
					cp = UNICODE_REPLACEMENT_CHAR;
				}
				exactLen += getUtf8EncodedSize(cp);
				ptr += eaten;
				len -= eaten;
			}

			OutStringT result;
			result.resize(exactLen);
			
			auto* outPtr = result.data();
			ptr = utf32.data();
			len = utf32.length();
			
			while (len > 0) {
				size_t eaten = 0;
				uint32_t cp = nextUtf32Char(ptr, len, &eaten);
				if (cp == UTF_INVALID || eaten == 0) {
					if (eaten == 0) { eaten = 1; }
					cp = UNICODE_REPLACEMENT_CHAR;
				}
				writeUtf8(outPtr, cp);
				ptr += eaten;
				len -= eaten;
			}
			return result;
		}

		/**
		 * Converts an 8-bit UTF-8 string to an OS-dependent wide string (std::wstring).
		 * Safely routes to 16-bit conversion on Windows and 32-bit conversion on POSIX.
		 * Must be called within a try/catch block.
		 *
		 * \param utf8		The 8-bit string to convert.
		 * \return			Returns the converted wide string.
		 **/
		template <typename OutStringT = std::wstring, typename InStringT>
		static inline OutStringT		utf8ToWString(const InStringT& utf8) {
			static_assert(sizeof(typename InStringT::value_type) == 1, "Input string must have 8-bit characters.");
#if defined( _WIN32 )
			return utf8ToUtf16<OutStringT>(utf8);
#else
			return utf8ToUtf32<OutStringT>(utf8);
#endif
		}

		/**
		 * Converts an OS-dependent wide string (std::wstring) to an 8-bit UTF-8 string.
		 * Safely routes from 16-bit conversion on Windows and 32-bit conversion on POSIX.
		 * Must be called within a try/catch block.
		 *
		 * \param wstr		The wide string to convert.
		 * \return			Returns the converted 8-bit string.
		 **/
		template <typename OutStringT = std::string, typename InStringT = std::wstring>
		static inline OutStringT		wStringToUtf8(const InStringT& wstr) {
			static_assert(sizeof(typename OutStringT::value_type) == 1, "Output string must have 8-bit characters.");
#if defined( _WIN32 )
			return utf16ToUtf8<OutStringT>(wstr);
#else
			return utf32ToUtf8<OutStringT>(wstr);
#endif
		}


		// ===============================
		// Trimming & Whitespace
		// ===============================
		/**
		 * Checks if a character is a standard ASCII whitespace character.
		 * Locale-independent and safe from signed char undefined behavior.
		 *
		 * \param c			The character to check.
		 * \return			Returns true if the character is whitespace (space, tab, newline, etc.).
		 **/
		template <typename CharT>
		static constexpr bool			isAsciiWhitespace(CharT c) noexcept {
			return c == static_cast<CharT>(' ') || 
				   c == static_cast<CharT>('\t') || 
				   c == static_cast<CharT>('\n') || 
				   c == static_cast<CharT>('\r') || 
				   c == static_cast<CharT>('\v') || 
				   c == static_cast<CharT>('\f');
		}

		/**
		 * Removes leading whitespace from a string in-place.
		 *
		 * \param str		The string to modify.
		 **/
		template <typename StringT>
		static inline void				trimLeft(StringT& str) {
			str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](typename StringT::value_type c) {
				return !isAsciiWhitespace(c);
			}));
		}

		/**
		 * Removes trailing whitespace from a string in-place.
		 *
		 * \param str		The string to modify.
		 **/
		template <typename StringT>
		static inline void				trimRight(StringT& str) {
			str.erase(std::find_if(str.rbegin(), str.rend(), [](typename StringT::value_type c) {
				return !isAsciiWhitespace(c);
			}).base(), str.end());
		}

		/**
		 * Removes both leading and trailing whitespace from a string in-place.
		 *
		 * \param str		The string to modify.
		 **/
		template <typename StringT>
		static inline void				trim(StringT& str) {
			trimRight(str);
			trimLeft(str);
		}

		/**
		 * Creates a copy of the string with leading whitespace removed.
		 * Must be called within a try/catch block.
		 *
		 * \param str		The input string (passed by value to incur the copy).
		 * \return			Returns the trimmed copy.
		 **/
		template <typename StringT>
		static inline StringT			trimLeftCopy(StringT str) {
			trimLeft(str);
			return str;
		}

		/**
		 * Creates a copy of the string with trailing whitespace removed.
		 * Must be called within a try/catch block.
		 *
		 * \param str		The input string (passed by value to incur the copy).
		 * \return			Returns the trimmed copy.
		 **/
		template <typename StringT>
		static inline StringT			trimRightCopy(StringT str) {
			trimRight(str);
			return str;
		}

		/**
		 * Creates a copy of the string with both leading and trailing whitespace removed.
		 * Must be called within a try/catch block.
		 *
		 * \param str		The input string (passed by value to incur the copy).
		 * \return			Returns the trimmed copy.
		 **/
		template <typename StringT>
		static inline StringT			trimCopy(StringT str) {
			trim(str);
			return str;
		}


		// ===============================
		// Case Manipulation
		// ===============================
		/**
		 * Converts a character to lowercase using strict ASCII rules.
		 *
		 * \param c			The character to convert.
		 * \return			Returns the lowercase equivalent if it is an ASCII uppercase letter.
		 **/
		template <typename CharT>
		static constexpr CharT			toLowerAsciiChar(CharT c) noexcept {
			if (c >= static_cast<CharT>('A') && c <= static_cast<CharT>('Z')) {
				return c + static_cast<CharT>('a' - 'A');
			}
			return c;
		}

		/**
		 * Converts a character to uppercase using strict ASCII rules.
		 *
		 * \param c			The character to convert.
		 * \return			Returns the uppercase equivalent if it is an ASCII lowercase letter.
		 **/
		template <typename CharT>
		static constexpr CharT			toUpperAsciiChar(CharT c) noexcept {
			if (c >= static_cast<CharT>('a') && c <= static_cast<CharT>('z')) {
				return c - static_cast<CharT>('a' - 'A');
			}
			return c;
		}

		/**
		 * Converts a string to lowercase in-place using strict ASCII rules.
		 *
		 * \param str		The string to modify.
		 **/
		template <typename StringT>
		static inline void				toLowerAscii(StringT& str) noexcept {
			for (auto& c : str) {
				c = toLowerAsciiChar(c);
			}
		}

		/**
		 * Converts a string to uppercase in-place using strict ASCII rules.
		 *
		 * \param str		The string to modify.
		 **/
		template <typename StringT>
		static inline void				toUpperAscii(StringT& str) noexcept {
			for (auto& c : str) {
				c = toUpperAsciiChar(c);
			}
		}

		/**
		 * Creates a lowercase copy of the string using strict ASCII rules.
		 * Must be called within a try/catch block.
		 *
		 * \param str		The input string (passed by value to incur the copy).
		 * \return			Returns the lowercase copy.
		 **/
		template <typename StringT>
		static inline StringT			toLowerAsciiCopy(StringT str) {
			toLowerAscii(str);
			return str;
		}

		/**
		 * Creates an uppercase copy of the string using strict ASCII rules.
		 * Must be called within a try/catch block.
		 *
		 * \param str		The input string (passed by value to incur the copy).
		 * \return			Returns the uppercase copy.
		 **/
		template <typename StringT>
		static inline StringT			toUpperAsciiCopy(StringT str) {
			toUpperAscii(str);
			return str;
		}

		/**
		 * Converts a string to lowercase in-place using the standard library.
		 * Note: For true UTF-8 string case folding, a heavy Unicode library (such as ICU) is required.
		 *
		 * \param str		The string to modify.
		 **/
		template <typename StringT>
		static inline void				toLower(StringT& str) noexcept {
			using CharT = typename StringT::value_type;
			for (auto& c : str) {
				if constexpr (sizeof(CharT) == sizeof(unsigned char)) {
					// Cast to unsigned char to strictly prevent undefined behavior with negative signed chars.
					c = static_cast<CharT>(std::tolower(static_cast<unsigned char>(c)));
				}
				else {
					c = static_cast<CharT>(std::towlower(static_cast<wint_t>(c)));
				}
			}
		}

		/**
		 * Converts a string to uppercase in-place using the standard library.
		 * Note: For true UTF-8 string case folding, a heavy Unicode library (such as ICU) is required.
		 *
		 * \param str		The string to modify.
		 **/
		template <typename StringT>
		static inline void				toUpper(StringT& str) noexcept {
			using CharT = typename StringT::value_type;
			for (auto& c : str) {
				if constexpr (sizeof(CharT) == 1) {
					// Cast to unsigned char to strictly prevent undefined behavior with negative signed chars.
					c = static_cast<CharT>(std::toupper(static_cast<unsigned char>(c)));
				}
				else {
					c = static_cast<CharT>(std::towupper(static_cast<wint_t>(c)));
				}
			}
		}

		/**
		 * Creates a lowercase copy of the string using the standard library.
		 * Must be called within a try/catch block.
		 *
		 * \param str		The input string (passed by value to incur the copy).
		 * \return			Returns the lowercase copy.
		 **/
		template <typename StringT>
		static inline StringT			toLowerCopy(StringT str) {
			toLower(str);
			return str;
		}

		/**
		 * Creates an uppercase copy of the string using the standard library.
		 * Must be called within a try/catch block.
		 *
		 * \param str		The input string (passed by value to incur the copy).
		 * \return			Returns the uppercase copy.
		 **/
		template <typename StringT>
		static inline StringT			toUpperCopy(StringT str) {
			toUpper(str);
			return str;
		}


		// ===============================
		// Search, Replace & Validation
		// ===============================
		/**
		 * Replaces all occurrences of a substring within a string in-place.
		 * Must be called within a try/catch block (can throw std::bad_alloc during reallocation).
		 *
		 * \param str		The string to modify.
		 * \param from		The substring to find.
		 * \param to		The substring to replace it with.
		 **/
		template <typename StringT, typename FromT, typename ToT>
		static inline void				replace(StringT& str, const FromT& from, const ToT& to) {
			auto fromView = std::basic_string_view(from);
			auto toView = std::basic_string_view(to);
			
			if (fromView.empty()) {
				return;
			}
			
			size_t startPos = 0;
			while ((startPos = str.find(fromView, startPos)) != StringT::npos) {
				str.replace(startPos, fromView.length(), toView);
				startPos += toView.length(); 
			}
		}

		/**
		 * Creates a copy of a string with all occurrences of a substring replaced.
		 * Must be called within a try/catch block.
		 *
		 * \param str		The input string (passed by value to incur the copy).
		 * \param from		The substring to find.
		 * \param to		The substring to replace it with.
		 * \return			Returns the modified string copy.
		 **/
		template <typename StringT, typename FromT, typename ToT>
		static inline StringT			replaceCopy(StringT str, const FromT& from, const ToT& to) {
			replace(str, from, to);
			return str;
		}

		/**
		 * Checks if a string begins with the given prefix.
		 *
		 * \param str		The string to check.
		 * \param prefix	The prefix to look for.
		 * \return			Returns true if the string starts with the prefix.
		 **/
		template <typename StrT, typename SubT>
		static constexpr bool			startsWith(const StrT& str, const SubT& prefix) noexcept {
			return std::basic_string_view(str).starts_with(std::basic_string_view(prefix));
		}

		/**
		 * Checks if a string ends with the given suffix.
		 *
		 * \param str		The string to check.
		 * \param suffix	The suffix to look for.
		 * \return			Returns true if the string ends with the suffix.
		 **/
		template <typename StrT, typename SubT>
		static constexpr bool			endsWith(const StrT& str, const SubT& suffix) noexcept {
			return std::basic_string_view(str).ends_with(std::basic_string_view(suffix));
		}

		/**
		 * Checks if a string contains the given substring.
		 *
		 * \param str		The string to search within.
		 * \param sub		The substring to find.
		 * \return			Returns true if the substring exists within the string.
		 **/
		template <typename StrT, typename SubT>
		static constexpr bool			contains(const StrT& str, const SubT& sub) noexcept {
			return std::basic_string_view(str).contains(std::basic_string_view(sub));
		}


		// ===============================
		// Splitting & Joining
		// ===============================
		/**
		 * Splits a string into a vector of substrings based on a delimiter character.
		 * Must be called within a try/catch block (can throw std::bad_alloc).
		 *
		 * \param str		The string to split.
		 * \param delimiter	The character to split the string by.
		 * \param skipEmpty	If true, consecutive delimiters will not produce empty string elements in the output.
		 * \return			Returns a vector containing the parsed substrings.
		 **/
		template <typename StringT>
		static inline std::vector<StringT>
										split(const StringT& str, typename StringT::value_type delimiter, bool skipEmpty = false) {
			std::vector<StringT> tokens;
			size_t startPos = 0;
			size_t endPos = str.find(delimiter);

			while (endPos != StringT::npos) {
				size_t len = endPos - startPos;
				if (!skipEmpty || len > 0) {
					tokens.push_back(str.substr(startPos, len));
				}
				startPos = endPos + 1;
				endPos = str.find(delimiter, startPos);
			}
			
			size_t remainingLen = str.length() - startPos;
			if (!skipEmpty || remainingLen > 0) {
				tokens.push_back(str.substr(startPos, remainingLen));
			}
			
			return tokens;
		}

		/**
		 * Joins a container of strings into a single string, separated by a delimiter string.
		 * Uses a strict two-pass approach to guarantee zero reallocation overhead.
		 * Must be called within a try/catch block (can throw std::bad_alloc).
		 *
		 * \param list		The iterable container of strings (e.g., std::vector<std::string>).
		 * \param separator	The string to insert between each element.
		 * \return			Returns the joined string.
		 **/
		template <typename ContainerT, typename StringT>
		static inline StringT			join(const ContainerT& list, const StringT& separator) {
			if (list.empty()) {
				return StringT();
			}

			size_t totalLen = separator.length() * (list.size() - 1);
			for (const auto& item : list) {
				totalLen += item.length();
			}

			StringT result;
			result.reserve(totalLen);

			auto it = list.begin();
			result.append(*it);
			++it;
			
			for (; it != list.end(); ++it) {
				result.append(separator);
				result.append(*it);
			}

			return result;
		}

		/**
		 * Joins a container of strings into a single string, separated by a single character.
		 * Uses a strict two-pass approach to guarantee zero reallocation overhead.
		 * Must be called within a try/catch block (can throw std::bad_alloc).
		 *
		 * \param list		The iterable container of strings (e.g., std::vector<std::string>).
		 * \param separator	The character to insert between each element.
		 * \return			Returns the joined string.
		 **/
		template <typename ContainerT, typename StringT = typename ContainerT::value_type>
		static inline StringT			join(const ContainerT& list, typename StringT::value_type separator) {
			if (list.empty()) {
				return StringT();
			}

			size_t totalLen = (list.size() - 1); // 1 char per separator.
			for (const auto& item : list) {
				totalLen += item.length();
			}

			StringT result;
			result.reserve(totalLen);

			auto it = list.begin();
			result.append(*it);
			++it;
			
			for (; it != list.end(); ++it) {
				result.push_back(separator);
				result.append(*it);
			}

			return result;
		}
	protected :

	private :
	};

}	// namespace ve
