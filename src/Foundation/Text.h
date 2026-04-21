#pragma once

#include "../Engine/Result.h"
#include "Character.h"
#include "Html.h"
#include "TextPolicy.h"
#include "Unicode.h"

#include <cstdint>
#include <cwctype>
#include <format>
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

		/** Represents the explicit format of a string literal requested by the script. **/
		enum class StringFormat : uint8_t {
			Normal,
			Raw,
			Utf8,
			Utf16,
			Utf32,
			Wide,
			CString
		};


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
			static_assert(sizeof(CharT) == 1, "utf8CharSize: Character type must be 8 bits (char, char8_t, uint8_t, etc.)");

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

		/**
		 * Gets the size of the given UTF-16 character.
		 *
		 * \param str		Pointer to the UTF-16 characters to decode. Accepts any 16-bit type (char16_t, uint16_t, Windows wchar_t).
		 * \param len		The number of characters to which str points.
		 * \return			Returns the size of the UTF-16 character to which str points (1 or 2).
		 **/
		template <typename CharT>
		static inline size_t			utf16CharSize(const CharT* str, size_t len) {
			if (len == 0) { return 0; }
			if (len == 1) { return 1; }
			return (static_cast<uint16_t>(str[0]) >= 0xD800 && static_cast<uint16_t>(str[0]) <= 0xDBFF) ? 2 : 1;
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

		/**
		 * Gets the number of UTF-8 elements required to encode a UTF-32 character.
		 *
		 * \param character	The UTF-32 code point.
		 * \return			Returns the number of bytes required (1 to 4).
		 **/
		static size_t					getUtf8EncodedSize(uint32_t character) {
			if (character <= 0x7F) {
				return 1;
			}
			else if (character <= 0x7FF) {
				return 2;
			}
			else if (character <= 0xFFFF) {
				return 3;
			}
			else if (character <= 0x10FFFF) {
				return 4;
			}
			
			// Fallback for UNICODE_REPLACEMENT_CHAR (0xFFFD), which takes 3 bytes in UTF-8.
			return 3;
		}

		/**
		 * Gets the number of UTF-16 elements required to encode a UTF-32 character.
		 *
		 * \param character	The UTF-32 code point.
		 * \return			Returns 1 or 2.
		 **/
		static size_t					getUtf16EncodedSize(uint32_t character) {
			if (character <= 0xFFFF) {
				return 1;
			}
			else if (character <= 0x10FFFF) {
				return 2;
			}
			
			// Fallback for UNICODE_REPLACEMENT_CHAR (0xFFFD), which takes 1 element in UTF-16.
			return 1;
		}

		/**
		 * Gets the number of UTF-32 elements required to encode a character.
		 *
		 * \param character	The UTF-32 code point.
		 * \return			Returns 1.
		 **/
		static constexpr size_t			getUtf32EncodedSize(uint32_t character) {
			static_cast<void>(character);
			return 1;
		}


		// ===============================
		// String Append Writers (Allocating)
		// ===============================
		/**
		 * Encodes a UTF-32 codepoint into UTF-8 and appends it to a string.
		 *
		 * \param outString		A reference to the destination string/vector.
		 * \param cp			The 32-bit codepoint to encode and append.
		 **/
		template <typename StringT>
		static inline void				appendUtf8(StringT& outString, uint32_t cp) {
			using CharT = typename StringT::value_type;
			
			if (cp <= 0x7F) {
				outString.push_back(static_cast<CharT>(cp));
			}
			else if (cp <= 0x7FF) {
				outString.push_back(static_cast<CharT>(0xC0 | (cp >> 6)));
				outString.push_back(static_cast<CharT>(0x80 | (cp & 0x3F)));
			}
			else if (cp <= 0xFFFF) {
				outString.push_back(static_cast<CharT>(0xE0 | (cp >> 12)));
				outString.push_back(static_cast<CharT>(0x80 | ((cp >> 6) & 0x3F)));
				outString.push_back(static_cast<CharT>(0x80 | (cp & 0x3F)));
			}
			else if (cp <= 0x10FFFF) {
				outString.push_back(static_cast<CharT>(0xF0 | (cp >> 18)));
				outString.push_back(static_cast<CharT>(0x80 | ((cp >> 12) & 0x3F)));
				outString.push_back(static_cast<CharT>(0x80 | ((cp >> 6) & 0x3F)));
				outString.push_back(static_cast<CharT>(0x80 | (cp & 0x3F)));
			}
			else {
				appendUtf8(outString, UNICODE_REPLACEMENT_CHAR);
			}
		}

		/**
		 * Encodes a UTF-32 codepoint into UTF-16 and appends it to a string.
		 *
		 * \param outString		A reference to the destination string/vector.
		 * \param cp			The 32-bit codepoint to encode and append.
		 **/
		template <typename StringT>
		static inline void				appendUtf16(StringT& outString, uint32_t cp) {
			using CharT = typename StringT::value_type;
			
			if (cp <= 0xFFFF) {
				outString.push_back(static_cast<CharT>(cp));
			}
			else if (cp <= 0x10FFFF) {
				uint32_t tmp = cp - 0x10000;
				outString.push_back(static_cast<CharT>(0xD800 | (tmp >> 10)));
				outString.push_back(static_cast<CharT>(0xDC00 | (tmp & 0x3FF)));
			}
			else {
				appendUtf16(outString, UNICODE_REPLACEMENT_CHAR);
			}
		}

		/**
		 * Appends a UTF-32 codepoint directly to a string.
		 *
		 * \param outString		A reference to the destination string/vector.
		 * \param cp			The 32-bit codepoint to append.
		 **/
		template <typename StringT>
		static inline void				appendUtf32(StringT& outString, uint32_t cp) {
			using CharT = typename StringT::value_type;
			
			if (cp <= 0x10FFFF) {
				outString.push_back(static_cast<CharT>(cp));
			}
			else {
				outString.push_back(static_cast<CharT>(UNICODE_REPLACEMENT_CHAR));
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
			static_assert(sizeof(typename OutStringT::value_type) == 2, "utf8ToUtf16: Output string must have 16-bit characters.");
			static_assert(sizeof(typename InStringT::value_type) == 1, "utf8ToUtf16: Input string must have 8-bit characters.");

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
			static_assert(sizeof(typename OutStringT::value_type) == 1, "utf16ToUtf8: Output string must have 8-bit characters.");
			static_assert(sizeof(typename InStringT::value_type) == 2, "utf16ToUtf8: Input string must have 16-bit characters.");

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
			static_assert(sizeof(typename OutStringT::value_type) == 4, "utf8ToUtf32: Output string must have 32-bit characters.");
			static_assert(sizeof(typename InStringT::value_type) == 1, "utf8ToUtf32: Input string must have 8-bit characters.");

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
			static_assert(sizeof(typename OutStringT::value_type) == 1, "utf32ToUtf8: Output string must have 8-bit characters.");
			static_assert(sizeof(typename InStringT::value_type) == 4, "utf32ToUtf8: Input string must have 32-bit characters.");

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
		 * Converts a 16-bit UTF-16 string to a 32-bit UTF-32 string.
		 * Must be called within a try/catch block.
		 *
		 * \param utf16		The UTF-16 string to convert.
		 * \return			Returns the converted 32-bit string.
		 **/
		template <typename OutStringT = std::u32string, typename InStringT>
		static inline OutStringT		utf16ToUtf32(const InStringT& utf16) {
			static_assert(sizeof(typename OutStringT::value_type) == 4, "utf16ToUtf32: Output string must have 32-bit characters.");
			static_assert(sizeof(typename InStringT::value_type) == 2, "utf16ToUtf32: Input string must have 16-bit characters.");

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
				exactLen += getUtf32EncodedSize(cp);
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
				writeUtf32(outPtr, cp);
				ptr += eaten;
				len -= eaten;
			}
			return result;
		}

		/**
		 * Converts a 32-bit UTF-32 string to a 16-bit UTF-16 string.
		 * Must be called within a try/catch block.
		 *
		 * \param utf32		The UTF-32 string to convert.
		 * \return			Returns the converted 16-bit string.
		 **/
		template <typename OutStringT = std::u16string, typename InStringT>
		static inline OutStringT		utf32ToUtf16(const InStringT& utf32) {
			static_assert(sizeof(typename OutStringT::value_type) == 2, "utf32ToUtf16: Output string must have 16-bit characters.");
			static_assert(sizeof(typename InStringT::value_type) == 4, "utf32ToUtf16: Input string must have 32-bit characters.");

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
				exactLen += getUtf16EncodedSize(cp);
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
				writeUtf16(outPtr, cp);
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
			static_assert(sizeof(typename InStringT::value_type) == 1, "utf8ToWString: Input string must have 8-bit characters.");
			if constexpr ( sizeof(typename InStringT::value_type) == 2) {
				return utf8ToUtf16<OutStringT>(utf8);
			}
			else {
				return utf8ToUtf32<OutStringT>(utf8);
			}
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
			static_assert(sizeof(typename OutStringT::value_type) == 1, "wStringToUtf8: Output string must have 8-bit characters.");
			if constexpr ( sizeof(typename InStringT::value_type) == 2) {
				return utf16ToUtf8<OutStringT>(wstr);
			}
			else {
				return utf32ToUtf8<OutStringT>(wstr);
			}
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

		/**
		 * Converts a single Unicode code point to uppercase.
		 *
		 * \param cp	The Unicode code point.
		 * \return		Returns the uppercase code point.
		 **/
		static inline uint32_t			toUpper(uint32_t cp) {
			if (cp <= 0x10FFFF) {
				return static_cast<uint32_t>(std::towupper(static_cast<wint_t>(cp)));
			}
			return cp;
		}

		/**
		 * Converts a single Unicode code point to lowercase.
		 *
		 * \param cp	The Unicode code point.
		 * \return		Returns the lowercase code point.
		 **/
		static inline uint32_t			toLower(uint32_t cp) {
			if (cp <= 0x10FFFF) {
				return static_cast<uint32_t>(std::towlower(static_cast<wint_t>(cp)));
			}
			return cp;
		}

		/**
		 * Capitalizes a UTF-8 string (first character uppercase, the rest lowercase).
		 * Must be called within a try/catch block.
		 *
		 * \param input		The input UTF-8 string view.
		 * \return			Returns the capitalized UTF-8 string.
		 **/
		static inline std::string		capitalizeUtf8(std::string_view input) {
			std::string result;
			result.reserve(input.length());
			
			bool first = true;
			size_t i = 0;
			
			while (i < input.length()) {
				unsigned char c = static_cast<unsigned char>(input[i]);
				size_t seqLen = 1;
				
				if ((c & 0xE0) == 0xC0) { seqLen = 2; }
				else if ((c & 0xF0) == 0xE0) { seqLen = 3; }
				else if ((c & 0xF8) == 0xF0) { seqLen = 4; }
				
				if (i + seqLen > input.length()) {
					// Malformed trailing sequence; append raw and break.
					result.append(input.data() + i, input.length() - i);
					break;
				}
				
				uint32_t cp = 0;
				if (seqLen == 1) {
					cp = c;
				}
				else if (seqLen == 2) {
					cp = ((c & 0x1F) << 6) | (input[i + 1] & 0x3F);
				}
				else if (seqLen == 3) {
					cp = ((c & 0x0F) << 12) | ((input[i + 1] & 0x3F) << 6) | (input[i + 2] & 0x3F);
				}
				else if (seqLen == 4) {
					cp = ((c & 0x07) << 18) | ((input[i + 1] & 0x3F) << 12) | ((input[i + 2] & 0x3F) << 6) | (input[i + 3] & 0x3F);
				}
				
				if (first) {
					cp = toUpper(cp);
					first = false;
				}
				else {
					cp = toLower(cp);
				}
				
				appendUtf8(result, cp);
				i += seqLen;
			}
			
			return result;
		}

		/**
		 * Casefolds a UTF-8 string for caseless comparison.
		 * Must be called within a try/catch block.
		 *
		 * \param input		The input UTF-8 string view.
		 * \return			Returns the casefolded UTF-8 string.
		 **/
		static inline std::string		casefoldUtf8(std::string_view input) {
			std::string result;
			result.reserve(input.length());
			
			size_t i = 0;
			while (i < input.length()) {
				unsigned char c = static_cast<unsigned char>(input[i]);
				size_t seqLen = 1;
				
				if ((c & 0xE0) == 0xC0) { seqLen = 2; }
				else if ((c & 0xF0) == 0xE0) { seqLen = 3; }
				else if ((c & 0xF8) == 0xF0) { seqLen = 4; }
				
				if (i + seqLen > input.length()) {
					result.append(input.data() + i, input.length() - i);
					break;
				}
				
				uint32_t cp = 0;
				if (seqLen == 1) { cp = c; }
				else if (seqLen == 2) { cp = ((c & 0x1F) << 6) | (input[i + 1] & 0x3F); }
				else if (seqLen == 3) { cp = ((c & 0x0F) << 12) | ((input[i + 1] & 0x3F) << 6) | (input[i + 2] & 0x3F); }
				else if (seqLen == 4) { cp = ((c & 0x07) << 18) | ((input[i + 1] & 0x3F) << 12) | ((input[i + 2] & 0x3F) << 6) | (input[i + 3] & 0x3F); }
				
				// Standard Unicode casefolding rule: German 'ß' becomes 'ss'.
				if (cp == 0x00DF) {
					result.push_back('s');
					result.push_back('s');
				}
				else {
					appendUtf8(result, toLower(cp));
				}
				
				i += seqLen;
			}
			
			return result;
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
			result.append((*it));
			++it;
			
			for (; it != list.end(); ++it) {
				result.append(separator);
				result.append((*it));
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

			size_t totalLen = (list.size() - 1);
			for (const auto& item : list) {
				totalLen += item.length();
			}

			StringT result;
			result.reserve(totalLen);

			auto it = list.begin();
			result.append((*it));
			++it;
			
			for (; it != list.end(); ++it) {
				result.push_back(separator);
				result.append((*it));
			}

			return result;
		}


		// ===============================
		// Formatting & Stringification
		// ===============================
		/**
		 * Converts an integer or pointer to a hexadecimal string.
		 * Must be called within a try/catch block.
		 *
		 * \param value		The numeric value or pointer to convert.
		 * \param padding	The minimum number of digits to output (pads with leading zeros).
		 * \param prefix	If true, prepends "0x" to the output.
		 * \return			Returns the formatted hexadecimal string.
		 **/
		template <typename StringT = std::string, typename IntT>
		static inline StringT			toHex(IntT value, size_t padding = 0, bool prefix = true) {
			using CharT = typename StringT::value_type;
			uint64_t val;
			
			if constexpr (std::is_pointer_v<IntT>) {
				val = reinterpret_cast<uintptr_t>(value);
			}
			else {
				val = static_cast<uint64_t>(value);
			}

			CharT buffer[16];
			int index = 15;
			
			if (val == 0) {
				buffer[index--] = static_cast<CharT>('0');
			}
			else {
				while (val > 0) {
					uint64_t nibble = val & 0xF;
					buffer[index--] = static_cast<CharT>(nibble < 10 ? '0' + nibble : 'A' + (nibble - 10));
					val >>= 4;
				}
			}

			int charsWritten = 15 - index;
			int padLen = (padding > static_cast<size_t>(charsWritten)) ? static_cast<int>(padding) - charsWritten : 0;
			int prefixLen = prefix ? 2 : 0;

			StringT result;
			result.resize(prefixLen + padLen + charsWritten);
			
			auto* outPtr = result.data();
			if (prefix) {
				(*outPtr++) = static_cast<CharT>('0');
				(*outPtr++) = static_cast<CharT>('x');
			}
			for (int i = 0; i < padLen; ++i) {
				(*outPtr++) = static_cast<CharT>('0');
			}
			for (int i = 0; i < charsWritten; ++i) {
				(*outPtr++) = buffer[index+1+i];
			}
			
			return result;
		}

		/**
		 * Converts an integer or pointer to a binary string.
		 * Must be called within a try/catch block.
		 *
		 * \param value		The numeric value or pointer to convert.
		 * \param padding	The minimum number of digits to output (pads with leading zeros).
		 * \param prefix	If true, prepends "0b" to the output.
		 * \return			Returns the formatted binary string.
		 **/
		template <typename StringT = std::string, typename IntT>
		static inline StringT			toBinary(IntT value, size_t padding = 0, bool prefix = true) {
			using CharT = typename StringT::value_type;
			uint64_t val;
			
			if constexpr (std::is_pointer_v<IntT>) {
				val = reinterpret_cast<uintptr_t>(value);
			}
			else {
				val = static_cast<uint64_t>(value);
			}

			CharT buffer[64];
			int index = 63;
			
			if (val == 0) {
				buffer[index--] = static_cast<CharT>('0');
			}
			else {
				while (val > 0) {
					buffer[index--] = static_cast<CharT>('0' + (val & 1));
					val >>= 1;
				}
			}

			int charsWritten = 63 - index;
			int padLen = (padding > static_cast<size_t>(charsWritten)) ? static_cast<int>(padding) - charsWritten : 0;
			int prefixLen = prefix ? 2 : 0;

			StringT result;
			result.resize(prefixLen + padLen + charsWritten);
			
			auto* outPtr = result.data();
			if (prefix) {
				(*outPtr++) = static_cast<CharT>('0');
				(*outPtr++) = static_cast<CharT>('b');
			}
			for (int i = 0; i < padLen; ++i) {
				(*outPtr++) = static_cast<CharT>('0');
			}
			for (int i = 0; i < charsWritten; ++i) {
				(*outPtr++) = buffer[index+1+i];
			}
			
			return result;
		}

		/**
		 * Converts an integer or pointer to an octal string.
		 * Must be called within a try/catch block.
		 *
		 * \param value		The numeric value or pointer to convert.
		 * \param padding	The minimum number of digits to output (pads with leading zeros).
		 * \param prefix	If true, prepends "0" to the output.
		 * \return			Returns the formatted octal string.
		 **/
		template <typename StringT = std::string, typename IntT>
		static inline StringT			toOctal(IntT value, size_t padding = 0, bool prefix = true) {
			using CharT = typename StringT::value_type;
			uint64_t val;
			
			if constexpr (std::is_pointer_v<IntT>) {
				val = reinterpret_cast<uintptr_t>(value);
			}
			else {
				val = static_cast<uint64_t>(value);
			}

			CharT buffer[22];
			int index = 21;
			
			if (val == 0) {
				buffer[index--] = static_cast<CharT>('0');
			}
			else {
				while (val > 0) {
					buffer[index--] = static_cast<CharT>('0' + (val & 7));
					val >>= 3;
				}
			}

			int charsWritten = 21 - index;
			int padLen = (padding > static_cast<size_t>(charsWritten)) ? static_cast<int>(padding) - charsWritten : 0;
			int prefixLen = prefix ? 1 : 0;

			StringT result;
			result.resize(prefixLen + padLen + charsWritten);
			
			auto* outPtr = result.data();
			if (prefix) {
				(*outPtr++) = static_cast<CharT>('0');
			}
			for (int i = 0; i < padLen; ++i) {
				(*outPtr++) = static_cast<CharT>('0');
			}
			for (int i = 0; i < charsWritten; ++i) {
				(*outPtr++) = buffer[index+1+i];
			}
			
			return result;
		}

		/**
		 * Converts a NumericConstant::Signed value to a string.
		 * Must be called within a try/catch block.
		 * 
		 * \param value		The numeric value to convert.
		 * \param padding	The minimum number of digits to output (pads with leading zeros).
		 * \return			Returns the formatted string.
		 **/
		template <typename StringT = std::string>
		static inline StringT			toSigned(int64_t value, uint32_t padding = 0) {
			uint32_t digits = std::max(padding, 1u);
			int width = static_cast<int>(digits);
			
			if (value < 0) {
				width++;
			}
			
			std::string fmt = std::format("{:0{}}", value, width);
			return StringT(fmt.begin(), fmt.end());
		}

		/**
		 * Converts a NumericConstant::Unsigned value to a string.
		 * Must be called within a try/catch block.
		 *
		 * \param value		The numeric value to convert.
		 * \param padding	The minimum number of digits to output (pads with leading zeros).
		 * \return			Returns the formatted string.
		 **/
		template <typename StringT = std::string>
		static inline StringT			toUnsigned(uint64_t value, uint32_t padding = 0) {
			uint32_t digits = std::max(padding, 1u);
			std::string fmt = std::format("{:0{}}", value, digits);
			return StringT(fmt.begin(), fmt.end());
		}

		/**
		 * Converts a NumericConstant::Floating value to a string.
		 * Must be called within a try/catch block.
		 *
		 * \param value		The numeric value to convert.
		 * \param sigDigits	If < 0, prints all digits with trailing zeros removed. If 0, uses default shortest representation. If > 0, uses scientific notation with specified precision.
		 * \return			Returns the formatted string.
		 **/
		template <typename StringT = std::string>
		static inline StringT			toDouble(double value, int32_t sigDigits = -1) {
			std::string fmt;
			
			if (sigDigits < 0) {
				fmt = std::format("{:.2000f}", value);
				
				while (!fmt.empty() && fmt.back() == '0') {
					fmt.pop_back();
				}
				
				if (!fmt.empty() && fmt.back() == '.') {
					if (std::abs(value) > static_cast<double>(static_cast<uint64_t>(-1))) {
						fmt.push_back('0');
					}
					else {
						fmt.pop_back();
					}
				}
			}
			else if (sigDigits == 0) {
				fmt = std::format("{}", value);
			}
			else {
				fmt = std::format("{:.{}e}", value, sigDigits);
			}
			
			return StringT(fmt.begin(), fmt.end());
		}

		/**
		 * Converts a string to a C-style escaped string.
		 * Must be called within a try/catch block.
		 * 
		 * \param str			The input string to escape. Accepts any character width.
		 * \param len			The length of the input string in characters.
		 * \return				Returns the escaped string, formatted to the specified OutStringT.
		 **/
		template <typename OutStringT = std::string, typename CharT>
		static OutStringT				toEscaped(const CharT* str, size_t len) {
			OutStringT result;
			result.reserve(len + 2);

			using OutCharT = typename OutStringT::value_type;

			auto appendHex = [&result](uint32_t val, int width, char prefix) {
				result.push_back(static_cast<OutCharT>('\\'));
				result.push_back(static_cast<OutCharT>(prefix));
				const char* hexChars = "0123456789ABCDEF";
				for (int i = width - 1; i >= 0; --i) {
					result.push_back(static_cast<OutCharT>(hexChars[(val>>(i*4))&0xF]));
				}
			};

			for (size_t i = 0; i < len; ++i) {
				uint32_t cp = 0;
				size_t eaten = 0;

				if constexpr (sizeof(CharT) == 1) {
					cp = nextUtf8Char(reinterpret_cast<const uint8_t*>(&str[i]), len - i, &eaten);
					if (eaten > 1) { i += (eaten - 1); }
				}
				else if constexpr (sizeof(CharT) == 2) {
					cp = nextUtf16Char(reinterpret_cast<const uint16_t*>(&str[i]), len - i, &eaten);
					if (eaten > 1) { i += (eaten - 1); }
				}
				else {
					cp = static_cast<uint32_t>(str[i]);
				}

				if (cp == UTF_INVALID) {
					// Escape raw byte.
					appendHex(static_cast<uint8_t>(str[i]), 2, 'x');
					continue;
				}

				// Standard C Escapes.
				struct Escape { uint32_t val; char esc; };
				static constexpr Escape escapes[] = {
					{ '\0', '0' },
					{ '\a', 'a' }, { '\b', 'b' }, { '\f', 'f' },
					{ '\n', 'n' }, { '\r', 'r' }, { '\t', 't' },
					{ '\v', 'v' }, { '\"', '\"' }, { '\\', '\\' }
				};

				bool found = false;
				for (const auto& e : escapes) {
					if (cp == e.val) {
						result.push_back(static_cast<OutCharT>('\\'));
						result.push_back(static_cast<OutCharT>(e.esc));
						found = true;
						break;
					}
				}

				if (found) { continue; }

				// Printable ASCII and extended values.
				if (cp < 256) {
					// Safely check if the character is printable in standard ASCII/Latin-1 bounds.
					if (cp < 128 && std::isprint(static_cast<unsigned char>(cp))) {
						result.push_back(static_cast<OutCharT>(cp));
					}
					else {
						appendHex(cp, 2, 'x');
					}
				}
				else if (cp <= 0xFFFF) {
					// \uXXXX for Basic Multilingual Plane.
					appendHex(cp, 4, 'u');
				}
				else {
					// \UXXXXXXXX for extended planes.
					appendHex(cp, 8, 'U');
				}
			}
			return result;
		}

		/**
		 * Converts a string to an ASCII string.
		 * Unrepresentable characters are replaced with '?' to match standard encoding fallback behavior.
		 * Must be called within a try/catch block.
		 * 
		 * \param str			The input string to process. Accepts any character width.
		 * \param len			The length of the input string in characters.
		 * \return				Returns the ASCII string, formatted to the specified OutStringT.
		 **/
		template <typename OutStringT = std::string, typename CharT>
		static OutStringT				toAscii(const CharT* str, size_t len) {
			OutStringT result;
			result.reserve(len);

			using OutCharT = typename OutStringT::value_type;

			for (size_t i = 0; i < len; ++i) {
				uint32_t cp = 0;
				size_t eaten = 0;

				if constexpr (sizeof(CharT) == 1) {
					cp = nextUtf8Char(reinterpret_cast<const uint8_t*>(&str[i]), len - i, &eaten);
					if (eaten > 1) { i += (eaten - 1); }
				}
				else if constexpr (sizeof(CharT) == 2) {
					cp = nextUtf16Char(reinterpret_cast<const uint16_t*>(&str[i]), len - i, &eaten);
					if (eaten > 1) { i += (eaten - 1); }
				}
				else {
					cp = static_cast<uint32_t>(str[i]);
				}

				if (cp == UTF_INVALID || cp > 127) {
					result.push_back(static_cast<OutCharT>('?'));
					continue;
				}

				// Standard printable ASCII values.
				result.push_back(static_cast<OutCharT>(cp));
			}
			return result;
		}


		// ===============================
		// Numeric Parsing
		// ===============================
		/**
		 * Classifies a string as one of the NumericConstant types. Determines whether the string represents a valid floating-point,
		 * signed integer, unsigned integer, or is invalid.
		 *
		 * \param sIn			The input string to classify.
		 * \param specialBase	Optional pointer to receive the detected numeric base (8, 10, 16, etc.)
		 * \return				Returns the classification as a NumericConstant enum value.
		 **/
		static NumericConstant			classifyString(const std::string& sIn, uint8_t* specialBase = nullptr);

		/**
		 * String to integer, from any base. Since std::stoull() raises exceptions etc. Also provides information on whether the parsed
		 * number is too large to fit within a given range.
		 *
		 * \param text		The text to parse.
		 * \param base		The base of the number to parse out of the text.
		 * \param eaten		Optional pointer to a size_t that will be set to the number of character eaten during parsing.
		 * \param maxVal	The maximum value after which overflow is considered to have happened.
		 * \param overflow	An optional pointer to a boolean used to indicate whether overflow has occurred or not.
		 * \return			Returns the value parsed from the string.
		 **/
		static uint64_t					stoull(const char* text, int base, size_t* eaten = nullptr, uint64_t maxVal = std::numeric_limits<uint64_t>::max(), bool* overflow = nullptr);

		/**
		 * String to double. Unlike std::atof(), this returns the number of characters eaten, and casts to float when the f postfix is seen.
		 *
		 * \param text		The text to parse.
		 * \param eaten		The number of characters consumed while parsing the double value.
		 * \param error		Optional pointer to a boolean which will be set to true if there are parsing errors.
		 * \return			Returns the parsed double.
		 **/
		static double					atof(const char* text, size_t* eaten = nullptr, bool* error = nullptr);


		// ===============================
		// Escape Sequence Parsing
		// ===============================
		/**
		 * Converts a hexadecimal character to its numeric value.
		 *
		 * \param c				The character to convert.
		 * \return				Returns the integer value (0-15), or 0 if invalid.
		 **/
		static inline uint32_t			hexToUint32(char c) {
			if (c >= '0' && c <= '9') {
				return static_cast<uint32_t>(c - '0');
			}
			else if (c >= 'a' && c <= 'f') {
				return static_cast<uint32_t>(c - 'a' + 10);
			}
			else if (c >= 'A' && c <= 'F') {
				return static_cast<uint32_t>(c - 'A' + 10);
			}
			
			return 0;
		}

		/**
		 * Converts an octal character to its numeric value.
		 *
		 * \param c				The character to convert.
		 * \return				Returns the integer value (0-7), or 0 if invalid.
		 **/
		static inline uint32_t			octalToUint32(char c) {
			if (c >= '0' && c <= '7') {
				return static_cast<uint32_t>(c - '0');
			}
			
			return 0;
		}

		/**
		 * Counts the number of alphanumeric or underscore characters from a starting position.
		 *
		 * \param val			Pointer to the input buffer.
		 * \param len			Total length of the buffer.
		 * \param cntFromPos	Index from which to start counting.
		 * \return				Number of consecutive alphanumeric or underscore characters.
		 **/
		template <typename CharT>
		static inline size_t			countAlphanumeric(const CharT* val, size_t len, size_t cntFromPos) {
			size_t ret = 0;
			
			for (; cntFromPos < len; ++cntFromPos) {
				char c = static_cast<char>(val[cntFromPos]);
				
				if ((c >= 'a' && c <= 'z') ||
					(c >= 'A' && c <= 'Z') ||
					(c >= '0' && c <= '9') ||
					c == '_') {
					++ret;
				}
				else {
					break;
				}
			}
			
			return ret;
		}

		/**
		 * Parses a hexadecimal escape sequence (\xNN).
		 *
		 * \param val					Pointer to the characters following the backslash.
		 * \param len					The remaining length of the string.
		 * \param charsConsumed			Reference to a size_t that will contain the number of characters consumed.
		 * \param maxAllowedHexChars	The maximum number of hexadecimal characters to consume.
		 * \return						Returns the parsed codepoint.
		 **/
		template <typename CharT>
		static inline uint32_t			escapeX(const CharT* val, size_t len, size_t& charsConsumed, size_t maxAllowedHexChars = 4) {
			charsConsumed = 0;
			
			if (len >= 2 && val[0] == static_cast<CharT>('x')) {
				size_t hexChars = 0;
				for (size_t i = 1; i < len; ++i) {
					if (std::isxdigit(static_cast<unsigned char>(val[i]))) {
						++hexChars;
					}
					else {
						break;
					}
				}
				
				if (hexChars >= 1) {
					hexChars = (hexChars < maxAllowedHexChars) ? hexChars : maxAllowedHexChars;
					size_t pos = 1;
					uint32_t ret = 0;
					
					for (size_t i = 0; i < hexChars; ++i) {
						char cTemp = static_cast<char>(val[pos++]);
						ret <<= 4;
						ret |= hexToUint32(cTemp);
					}
					
					charsConsumed = hexChars + 1;
					return ret;
				}
			}
			
			return 0;
		}

		/**
		 * Parses a 4-character wide Unicode escape sequence (\uNNNN).
		 *
		 * \param val					Pointer to the characters following the backslash.
		 * \param len					The remaining length of the string.
		 * \param charsConsumed			Reference to a size_t that will contain the number of characters consumed.
		 * \return						Returns the parsed codepoint.
		 **/
		template <typename CharT>
		static inline uint32_t			escapeUnicodeWide4(const CharT* val, size_t len, size_t& charsConsumed) {
			charsConsumed = 0;
			
			if (len >= 5 && val[0] == static_cast<CharT>('u')) {
				size_t hexChars = 0;
				for (size_t i = 1; i < len && i <= 4; ++i) {
					if (std::isxdigit(static_cast<unsigned char>(val[i]))) {
						++hexChars;
					}
					else {
						break;
					}
				}
				
				if (hexChars == 4) {
					size_t pos = 1;
					uint32_t ret = 0;
					
					for (size_t i = 0; i < hexChars; ++i) {
						char cTemp = static_cast<char>(val[pos++]);
						ret <<= 4;
						ret |= hexToUint32(cTemp);
					}
					
					charsConsumed = 5;
					return ret;
				}
			}
			
			return 0;
		}

		/**
		 * Parses a 4-character wide Unicode escape sequence, resolving surrogate pairs if present.
		 *
		 * \param val					Pointer to the characters following the backslash.
		 * \param len					The remaining length of the string.
		 * \param charsConsumed			Reference to a size_t that will contain the number of characters consumed.
		 * \return						Returns the parsed codepoint.
		 **/
		template <typename CharT>
		static inline uint32_t			escapeUnicodeWide4WithSurrogatePairs(const CharT* val, size_t len, size_t& charsConsumed) {
			uint32_t left = escapeUnicodeWide4(val, len, charsConsumed);
			
			if (!charsConsumed) {
				return left;
			}

			// In order to be a surrogate pair.
			if ((left & 0xFC00) == 0xD800) {
				const CharT* nextVal = val + charsConsumed;
				size_t nextLen = len - charsConsumed;
				
				// '\' + 'u' + NNNN.
				if (nextLen >= 6) {
					if (nextVal[0] == static_cast<CharT>('\\')) {
						++nextVal;
						--nextLen;
						size_t consumedRight = 0;
						uint32_t right = escapeUnicodeWide4(nextVal, nextLen, consumedRight);

						// 2nd half of surrogate pair must be valid.
						if ((right & 0xFC00) == 0xDC00) {
							uint32_t h = left & 0x03FF;
							uint32_t l = right & 0x03FF;
							left = 0x10000 + (h << 10) + l;
							charsConsumed = charsConsumed + 1 + consumedRight;
						}
					}
				}
			}
			
			return left;
		}

		/**
		 * Parses an 8-character Unicode escape sequence (\UNNNNNNNN).
		 *
		 * \param val					Pointer to the characters following the backslash.
		 * \param len					The remaining length of the string.
		 * \param charsConsumed			Reference to a size_t that will contain the number of characters consumed.
		 * \return						Returns the parsed codepoint.
		 **/
		template <typename CharT>
		static inline uint32_t			escapeUnicode8(const CharT* val, size_t len, size_t& charsConsumed) {
			charsConsumed = 0;
			
			if (len >= 9 && val[0] == static_cast<CharT>('U')) {
				size_t hexChars = 0;
				for (size_t i = 1; i < len && i <= 8; ++i) {
					if (std::isxdigit(static_cast<unsigned char>(val[i]))) {
						++hexChars;
					}
					else {
						break;
					}
				}
				
				if (hexChars == 8) {
					size_t pos = 1;
					uint32_t ret = 0;
					
					for (size_t i = 0; i < hexChars; ++i) {
						char cTemp = static_cast<char>(val[pos++]);
						ret <<= 4;
						ret |= hexToUint32(cTemp);
					}
					
					charsConsumed = 9;
					return ret;
				}
			}
			
			return 0;
		}

		/**
		 * Parses an octal escape sequence.
		 *
		 * \param val					Pointer to the characters following the backslash.
		 * \param len					The remaining length of the string.
		 * \param charsConsumed			Reference to a size_t that will contain the number of characters consumed.
		 * \param maxAllowedOctalChars	The maximum number of octal characters to consume.
		 * \return						Returns the parsed codepoint.
		 **/
		template <typename CharT>
		static inline uint32_t			escapeOctal(const CharT* val, size_t len, size_t& charsConsumed, size_t maxAllowedOctalChars = 4) {
			charsConsumed = 0;
			
			if (len >= 1) {
				size_t octalChars = 0;
				for (size_t i = 0; i < len; ++i) {
					char c = static_cast<char>(val[i]);
					if (c >= '0' && c <= '7') {
						++octalChars;
					}
					else {
						break;
					}
				}
				
				if (octalChars >= 1) {
					octalChars = (octalChars < maxAllowedOctalChars) ? octalChars : maxAllowedOctalChars;
					size_t pos = 0;
					uint32_t ret = 0;
					
					for (size_t i = 0; i < octalChars; ++i) {
						char cTemp = static_cast<char>(val[pos++]);
						ret <<= 3;
						ret |= octalToUint32(cTemp);
					}
					
					charsConsumed = octalChars;
					return ret;
				}
			}

			return 0;
		}

		/**
		 * Converts an HTML entity name or numeric escape sequence to a Unicode code point.
		 * Must be called within a try/catch block.
		 *
		 * \param val			Pointer to the input buffer (assumed to be pointing immediately after the '&').
		 * \param len			Remaining length of the buffer.
		 * \param charsConsumed	Reference to a size_t that will contain the number of characters consumed.
		 * \return				Returns the Unicode code point (or two packed code points), or 0 if invalid.
		 **/
		template <typename CharT>
		static inline uint64_t			escapeHtml(const CharT* val, size_t len, size_t& charsConsumed) {
			const CharT* orig = val;
			charsConsumed = 0;
			
			if (len) {
				if ((*val) == static_cast<CharT>('#')) {
					++val;
					--len;
					
					if (len && (*val) == static_cast<CharT>('x')) {
						++val;
						--len;
						
						uint32_t ret = 0;
						bool foundOne = false;
						
						for (size_t i = 0; i < len; ++i) {
							char cTemp = static_cast<char>(val[i]);
							
							if (!Character::validHex(cTemp)) {
								if (!foundOne) {
									return 0;
								}
								
								charsConsumed = static_cast<size_t>(val - orig) + i;
								
								if (cTemp == ';') {
									++charsConsumed;
								}
								
								return static_cast<uint64_t>(ret);
							}
							
							ret <<= 4;
							ret |= hexToUint32(cTemp);
							foundOne = true;
						}
					}
					else {
						uint32_t ret = 0;
						bool foundOne = false;
						
						for (size_t i = 0; i < len; ++i) {
							char cTemp = static_cast<char>(val[i]);
							
							if (!Character::isDigit(cTemp)) {
								if (!foundOne) {
									return 0;
								}
								
								charsConsumed = static_cast<size_t>(val - orig) + i;
								
								if (cTemp == ';') {
									++charsConsumed;
								}
								
								return static_cast<uint64_t>(ret);
							}
							
							ret *= 10;
							ret |= static_cast<uint32_t>(cTemp - '0');
							foundOne = true;
						}
					}
				}

				size_t count = countAlphanumeric(val, len, 0);
				
				if (count > 0) {
					std::string nameStr;
					nameStr.reserve(count);
					
					for (size_t i = 0; i < count; ++i) {
						nameStr.push_back(static_cast<char>(val[i]));
					}
					
					uint64_t code = Html::getCode(nameStr.c_str(), count);
					
					if (code != static_cast<uint64_t>(Html::InvalidCode::Invalid)) {
						charsConsumed = static_cast<size_t>(val - orig) + count;
						
						if (len > count && val[count] == static_cast<CharT>(';')) {
							++charsConsumed;
						}
						
						return code;
					}
				}
			}
			
			return 0;
		}

		/**
		 * Parses a named Unicode escape sequence (\N{NAME}).
		 * Must be called within a try/catch block.
		 *
		 * \param val					Pointer to the characters following the backslash (starting at 'N').
		 * \param len					The remaining length of the string.
		 * \param charsConsumed			Reference to a size_t that will contain the number of characters consumed.
		 * \return						Returns the parsed codepoint, or 0 if invalid.
		 **/
		template <typename CharT>
		static inline uint32_t			escapeNamedUnicode(const CharT* val, size_t len, size_t& charsConsumed) {
			const CharT* orig = val;
			charsConsumed = 0;
			const CharT* start = nullptr;
			size_t nameLen = 0;
			
			for (size_t i = 0; i < len; ++i) {
				if (val[i] == static_cast<CharT>('{')) {
					start = &val[i + 1];
				}
				else if (val[i] == static_cast<CharT>('}')) {
					if (start) {
						nameLen = static_cast<size_t>(&val[i] - start);
					}
					break;
				}
			}
			
			if (start && nameLen > 0) {
				std::string nameStr;
				nameStr.reserve(nameLen);
				
				for (size_t i = 0; i < nameLen; ++i) {
					nameStr.push_back(static_cast<char>(start[i]));
				}
				
				uint32_t code = Unicode::getCodeByName(nameStr.c_str(), nameLen);
				
				if (code != UTF_INVALID) {
					// We ate however many characters from the start plus the characters in the actual name plus the final }.
					charsConsumed = nameLen + static_cast<size_t>(start - orig) + 1;
					return code;
				}
			}
			
			return 0;
		}
		/**
		 * Resolves an escape sequence starting with a backslash (or an ampersand for HTML if supported).
		 * Must be called within a try/catch block.
		 *
		 * \param input					Pointer to the escape sequence (pointing to the backslash).
		 * \param len					The remaining length of the string.
		 * \param charsConsumed			Reference to a size_t that will contain the number of characters consumed.
		 * \param includeHtml			Whether to process HTML entities.
		 * \param escapeFound			Optional pointer to a boolean indicating if an escape was successfully resolved.
		 * \return						Returns the resolved Unicode codepoint.
		 **/
		template <typename CharT>
		static inline uint64_t			resolveEscape(const CharT* input, size_t len, size_t& charsConsumed, bool includeHtml = false, bool* escapeFound = nullptr) {
			if (escapeFound) {
				(*escapeFound) = false;
			}
#if !defined(VE_HTML_ESCAPES)
			includeHtml = false;
#endif	// #if !defined(VE_HTML_ESCAPES)
			
			if (!len) {
				charsConsumed = 0;
				return 0;
			}
			
			if (len == 1) {
				charsConsumed = 1;
				return static_cast<uint32_t>(*input);
			}

			// There are at least 2 characters so an escape is possible.
			if (len >= 2 && (*input) == static_cast<CharT>('&') && includeHtml) {
				size_t sLen = 0;
				uint64_t temp = escapeHtml(input + 1, len - 1, sLen);
				
				if (sLen) {
					charsConsumed = sLen + 1;
					
					if (escapeFound) {
						(*escapeFound) = true;
					}
					
					return temp;
				}
			}

			if ((*input) != static_cast<CharT>('\\')) {
				charsConsumed = 1;
				return static_cast<uint32_t>(*input);	// Not an escape.
			}

			struct StandardEscape {
				char cEscape;
				char cValue;
			};
			
			static constexpr StandardEscape escapes[] = {
				{ 'a', '\a' },
				{ 'b', '\b' },
				{ 'f', '\f' },
				{ 'n', '\n' },
				{ 'r', '\r' },
				{ 't', '\t' },
				{ 'v', '\v' },
				{ '\\', '\\' },
				{ '\'', '\'' },
				{ '"', '\"' },
				{ '?', '\?' },
				{ ' ', ' ' },
				{ '\0', '\0' }
			};

			char cNext = static_cast<char>(input[1]);
			charsConsumed = 1;

			switch (cNext) {
				case 'x' : {
					uint32_t temp = escapeX(&input[1], len - 1, charsConsumed);
					
					if (!charsConsumed) {
						charsConsumed = 1;
						return static_cast<uint32_t>(*input);
					}
					else {
						++charsConsumed;
						if (escapeFound) {
							(*escapeFound) = true;
						}
					}
					
					return temp;
				}
				case 'u' : {
					// Takes \uNNNN and \uNNNN\uNNNN.
					uint32_t temp = escapeUnicodeWide4WithSurrogatePairs(&input[1], len - 1, charsConsumed);
					
					if (!charsConsumed) {
						charsConsumed = 1;
						return static_cast<uint32_t>(*input);
					}
					else {
						++charsConsumed;
						if (escapeFound) {
							(*escapeFound) = true;
						}
					}
					
					return temp;
				}
				case 'U' : {
					uint32_t temp = escapeUnicode8(&input[1], len - 1, charsConsumed);
					
					if (!charsConsumed) {
						charsConsumed = 1;
						return static_cast<uint32_t>(*input);
					}
					else {
						++charsConsumed;
						if (escapeFound) {
							(*escapeFound) = true;
						}
					}
					
					return temp;
				}
				case 'N' : {
					uint32_t temp = escapeNamedUnicode(&input[1], len - 1, charsConsumed);
					
					if (!charsConsumed) {
						charsConsumed = 1;
						return static_cast<uint64_t>(*input);
					}
					else {
						++charsConsumed;
						if (escapeFound) {
							(*escapeFound) = true;
						}
					}
					
					return static_cast<uint64_t>(temp);
				}
				default : {
					if (input[1] >= static_cast<CharT>('0') && input[1] <= static_cast<CharT>('7')) {
						uint32_t temp = escapeOctal(&input[1], len - 1, charsConsumed);
						++charsConsumed;	// Eat the \.
						
						if (escapeFound) {
							(*escapeFound) = true;
						}
						
						return temp;
					}
					else {
						for (size_t i = 0; escapes[i].cEscape != '\0'; ++i) {
							if (cNext == escapes[i].cEscape) {
								++charsConsumed;
								
								if (escapeFound) {
									(*escapeFound) = true;
								}
								
								return static_cast<uint32_t>(static_cast<unsigned char>(escapes[i].cValue));
							}
						}
						
						// Invalid escape.
						return static_cast<uint32_t>(*input);
					}
				}
			}
		}

		/**
		 * Simulates converting a UTF-8 string to the current code page and back.
		 * 
		 * \param utf8Str				The input UTF-8 string.
		 * \return						Returns the processed UTF-8 string.
		 **/
		static std::string				simulateCodePageConversion(const std::string& utf8Str) {
			// TODO: Implement actual OS-level code page conversion.
			// 1. Convert utf8Str to wide string (UTF-16).
			// 2. Convert wide string to multi-byte string using current active code page.
			// 3. Convert multi-byte string back to wide string.
			// 4. Convert wide string back to UTF-8.
			return utf8Str; 
		}

		/**
		 * Parses a raw string literal, resolving quotes, escapes, and applying format-specific rules.
		 *
		 * \param rawToken				The raw string token matched by ANTLR.
		 * \param format				The specific format detected by the lexer.
		 * \return						Returns the fully processed UTF-8 string payload.
		 **/
		static std::string				parseStringLiteral(std::string_view rawToken, StringFormat format) {
			size_t quoteIdx = rawToken.find_first_of("\"'");
			
			if (quoteIdx == std::string_view::npos) {
				return "";
			}

			char quoteChar = rawToken[quoteIdx];
			size_t quoteLen = 1;
			
			if (quoteIdx + 2 < rawToken.size() && rawToken[quoteIdx + 1] == quoteChar && rawToken[quoteIdx + 2] == quoteChar) {
				quoteLen = 3;
			}

			std::string_view payload = rawToken.substr(quoteIdx + quoteLen, rawToken.size() - quoteIdx - (quoteLen * 2));

			// If a raw string, no need to do escape sequences.
			if (format == StringFormat::Raw) {
				return std::string(payload);
			}

			// Resolve Escapes.
			std::string result;
			result.reserve(payload.size());

			for (size_t i = 0; i < payload.size(); ) {
				// To fully enable HTML escapes in standard strings, set the 4th argument to true.
				if (payload[i] == '\\' || payload[i] == '&') {
					size_t charsConsumed = 0;
					bool escapeFound = false;
					uint64_t cp = resolveEscape(&payload[i], payload.size() - i, charsConsumed, true, &escapeFound);
					
					if (charsConsumed > 0 && escapeFound) {
						uint32_t lower = static_cast<uint32_t>(cp & 0xFFFFFFFF);
						uint32_t upper = static_cast<uint32_t>(cp >> 32);
						
						appendUtf8(result, lower);
						
						if (upper != 0) {
							appendUtf8(result, upper);
						}
						
						i += charsConsumed;
					}
					else {
						result.push_back(payload[i]);
						++i;
					}
				}
				else {
					result.push_back(payload[i]);
					++i;
				}
			}

			// Apply C-string code page conversion rule if explicitly requested.
			if (format == StringFormat::CString) {
				return simulateCodePageConversion(result);
			}

			return result;
		}


	protected :

	private :
	};

}	// namespace ve
