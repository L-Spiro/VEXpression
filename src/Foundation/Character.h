#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <string>

namespace ve {

	/**
	 * Provides foundational character classification and conversion utilities.
	 **/
	class Character {
	public :
		// == Functions.
		/**
		 * Determines if a given character is a valid binary digit.
		 * 
		 * \param val		The character to check.
		 * \return			Returns true if the character is '0' or '1'.
		 **/
		static inline bool			validBin(char val) {
			return (val >= '0' && val <= '1');
		}

		/**
		 * Determines if a given character is a valid hexadecimal digit.
		 * 
		 * \param val		The character to check.
		 * \return			Returns true if the character is 0-9, a-f, or A-F.
		 **/
		static inline bool			validHex(char val) {
			return (val >= '0' && val <= '9') || (val >= 'a' && val <= 'f') || (val >= 'A' && val <= 'F');
		}

		/**
		 * Determines if a null-terminated string contains only valid hexadecimal digits.
		 * 
		 * \param str		The string to check.
		 * \return			Returns true if all characters in the string are valid hex digits.
		 **/
		static inline bool			validHex(const char* str) {
			if (!str) {
				return false;
			}
			while (*str) {
				if (!validHex(*str)) {
					return false;
				}
				++str;
			}
			return true;
		}

		/**
		 * Determines if a given character is a valid octal digit.
		 * 
		 * \param val		The character to check.
		 * \return			Returns true if the character is 0-7.
		 **/
		static inline bool			validOctal(char val) {
			return (val >= '0' && val <= '7');
		}

		/**
		 * Converts a hexadecimal character to its 32-bit unsigned integer value.
		 * 
		 * \param val		The character to convert.
		 * \return			Returns the 0-15 integer representation of the hex character.
		 **/
		static inline uint32_t		hexToUint32(char val) {
			if (val >= '0' && val <= '9') {
				return static_cast<uint32_t>(val - '0');
			}
			if (val >= 'a' && val <= 'f') {
				return static_cast<uint32_t>(val - 'a' + 10);
			}
			if (val >= 'A' && val <= 'F') {
				return static_cast<uint32_t>(val - 'A' + 10);
			}
			return 0;
		}

		/**
		 * Converts a wide character digit to its 32-bit signed integer value.
		 * 
		 * \param val		The wide character to convert.
		 * \return			Returns the 0-9 integer representation of the digit.
		 **/
		static inline int32_t		digitValWide(wchar_t val) {
			if (val >= L'0' && val <= L'9') {
				return static_cast<int32_t>(val - L'0');
			}
			return 0;
		}

		/**
		 * Converts an octal character to its 32-bit unsigned integer value.
		 * 
		 * \param val		The character to convert.
		 * \return			Returns the 0-7 integer representation of the octal character.
		 **/
		static inline uint32_t		octalToUint32(char val) {
			if (val >= '0' && val <= '7') {
				return static_cast<uint32_t>(val - '0');
			}
			return 0;
		}

		/**
		 * Determines if a given character is whitespace.
		 * 
		 * \param val		The character to check.
		 * \return			Returns true if the character is a space, tab, newline, carriage return, vertical tab, or form feed.
		 **/
		static inline bool			isWhiteSpace(char val) {
			return (val == ' ' || val == '\t' || val == '\n' || val == '\r' || val == '\v' || val == '\f');
		}

		/**
		 * Determines if a given character is a decimal digit.
		 * 
		 * \param val		The character to check.
		 * \return			Returns true if the character is 0-9.
		 **/
		static inline bool			isDigit(char val) {
			return (val >= '0' && val <= '9');
		}

		/**
		 * Determines if a given wide character is a decimal digit.
		 * 
		 * \param val		The wide character to check.
		 * \return			Returns true if the character is 0-9.
		 **/
		static inline bool			isDigit(wchar_t val) {
			return (val >= L'0' && val <= L'9') ||
				(val >= L'\uFF10' && val <= L'\uFF19');
		}

		/**
		 * Determines if a given character is an alphabetical letter.
		 * 
		 * \param val		The character to check.
		 * \return			Returns true if the character is a-z or A-Z.
		 **/
		static inline bool			isAlpha(char val) {
			return ((val >= 'a' && val <= 'z') || (val >= 'A' && val <= 'Z'));
		}

		/**
		 * Determines if a given character is a valid ASCII character.
		 * 
		 * \param val		The character to check.
		 * \return			Returns true if the character is in the ASCII range (0-127).
		 **/
		static inline bool			isAscii(char val) {
			return static_cast<unsigned char>(val) <= 127;
		}

		/**
		 * Validates if a character is valid within an identifier, properly enforcing the first-character rule.
		 * 
		 * \param val		The character to check.
		 * \param isFirst	A reference to a boolean indicating if this is the first character. It will be automatically set to false.
		 * \return			Returns true if the character is valid at the current position.
		 **/
		static inline bool			isIdentifier(char val, bool& isFirst) {
			if (isFirst) {
				isFirst = false;
				return isAlpha(val) || val == '_';
			}
			else {
				return isAlpha(val) || isDigit(val) || val == '_';
			}
		}

		/**
		 * Determines if an entire string represents a valid identifier.
		 * 
		 * \param ident		The string to check.
		 * \return			Returns true if the string adheres to strict identifier naming rules.
		 **/
		template <typename StringType = std::string>
		static bool					isIdentifier(const StringType& ident) {
			if (ident.empty()) {
				return false;
			}
			
			bool isFirst = true;
			for (auto c : ident) {
				if (!isIdentifier(static_cast<char>(c), isFirst)) {
					return false;
				}
			}
			return true;
		}

		/**
		 * Determines if the given Unicode character is a lower-case character.
		 * 
		 * \param val		The character to check for being lower-case.
		 * \return			Returns true if the given character is a lower-case character.
		 **/
		template <typename CharT>
		static bool					isLowerUtf(CharT val) {
			uint32_t codePoint = static_cast<uint32_t>(val);
			const uint32_t* begin = unicodeLowercaseTable;
			const uint32_t* end = unicodeLowercaseTable + unicodeLowercaseTableSize;

			return std::binary_search(
				begin, 
				end,
				codePoint
			);
		}

		/**
		 * Determines if the given Unicode character is a upper-case character.
		 * 
		 * \param val		The character to check for being upper-case.
		 * \return			Returns true if the given character is a upper-case character.
		 **/
		template <typename CharT>
		static bool					isUpperUtf(CharT val) {
			uint32_t codePoint = static_cast<uint32_t>(val);
			const uint32_t* begin = unicodeUppercaseTable;
			const uint32_t* end = unicodeUppercaseTable + unicodeUppercaseTableSize;

			return std::binary_search(
				begin, 
				end, 
				codePoint
			);
		}

		/**
		 * Determines if the given Unicode character is a numeric character.
		 * 
		 * \param val		The character to check for being numeric.
		 * \return			Returns true if the given character is a numeric character.
		 **/
		template <typename CharT>
		static bool					isNumericUtf(CharT val) {
			uint32_t codePoint = static_cast<uint32_t>(val);
			const uint32_t* begin = unicodeNumericTable;
			const uint32_t* end = unicodeNumericTable + unicodeNumericTableSize;

			return std::binary_search(
				begin, 
				end, 
				codePoint
			);
		}

		/**
		 * Determines if the given Unicode character is a alpha character.
		 * 
		 * \param val		The character to check for being alpha.
		 * \return			Returns true if the given character is a alpha character.
		 **/
		template <typename CharT>
		static bool					isAlphaUtf(CharT val) {
#ifdef VE_FULL_STRINGS
			uint32_t codePoint = static_cast<uint32_t>(val);
			const uint32_t* begin = unicodeAlphaTable;
			const uint32_t* end = unicodeAlphaTable + unicodeAlphaTableSize;

			return std::binary_search(
				begin, 
				end, 
				codePoint
			);
#else	// #ifdef VE_FULL_STRINGS
			return std::islower(int(val));
#endif	// #ifdef VE_FULL_STRINGS
		}

		/**
		 * Determines if the given Unicode character is a digit character.
		 * 
		 * \param val		The character to check for being digit.
		 * \return			Returns true if the given character is a digit character.
		 **/
		template <typename CharT>
		static bool					isDigitUtf(CharT val) {
			uint32_t codePoint = static_cast<uint32_t>(val);
			const uint32_t* begin = unicodeDigitTable;
			const uint32_t* end = unicodeDigitTable + unicodeDigitTableSize;

			return std::binary_search(
				begin, 
				end, 
				codePoint
			);
		}

		/**
		 * Determines if the given Unicode character is a decimal character.
		 * 
		 * \param val		The character to check for being decimal.
		 * \return			Returns true if the given character is a decimal character.
		 **/
		template <typename CharT>
		static bool					isDecimalUtf(CharT val) {
			const auto end = unicodeDecimalRanges + unicodeDecimalTableSize;
			auto it = std::lower_bound(unicodeDecimalRanges, end, uint32_t(val),
				[](const UnicodeRange& range, uint32_t val) {
					return range.end < val;
				});

			return (it != end && uint32_t(val) >= it->start);
		}

		/**
		 * Determines if the given Unicode character is a printable character.
		 * 
		 * \param val		The character to check for being printable.
		 * \return			Returns true if the given character is a printable character.
		 **/
		template <typename CharT>
		static bool					isPrintableUtf(CharT val) {
			const auto end = unicodePrintableRanges + unicodePrintableTableSize;
			auto it = std::lower_bound(unicodePrintableRanges, end, uint32_t(val),
				[](const UnicodeRange& range, uint32_t val) {
					return range.end < val;
				});

			return (it != end && uint32_t(val) >= it->start);
		}

		/**
		 * Determines if the given Unicode character is a whitespace character.
		 * 
		 * \param val		The character to check for being whitespace.
		 * \return			Returns true if the given character is a whitespace character.
		 **/
		template <typename CharT>
		static bool					isSpaceUtf(CharT val) {
			const auto end = unicodeSpaceRanges + unicodeSpaceTableSize;
			auto it = std::lower_bound(unicodeSpaceRanges, end, uint32_t(val),
				[](const UnicodeRange& range, uint32_t val) {
					return range.end < val;
				});

			return (it != end && uint32_t(val) >= it->start);
		}

	protected :
		// == Types.
		/** A range of characters. */
		struct UnicodeRange {
			uint32_t				start;
			uint32_t				end;
		};


		// == Members.
		/** The table of alpha characters. */
		static const uint32_t		unicodeAlphaTable[];
		/** Necessary size of the alpha table. */
		static const size_t			unicodeAlphaTableSize;
		/** The table of digit characters. */
		static const uint32_t		unicodeDigitTable[];
		/** Necessary size of the digit table. */
		static const size_t			unicodeDigitTableSize;
		/** The table of lower-cased characters. */
		static const uint32_t		unicodeLowercaseTable[];
		/** Necessary size of the lower-case table. */
		static const size_t			unicodeLowercaseTableSize;
		/** The table of upper-cased characters. */
		static const uint32_t		unicodeUppercaseTable[];
		/** Necessary size of the upper-case table. */
		static const size_t			unicodeUppercaseTableSize;
		/** The table of numeric characters. */
		static const uint32_t		unicodeNumericTable[];
		/** Necessary size of the numeric table. */
		static const size_t			unicodeNumericTableSize;
		/** A range of printable characters. */
		static const UnicodeRange	unicodePrintableRanges[];
		/** Necessary size of the printable table. */
		static const size_t			unicodePrintableTableSize;
		/** A range of decimal characters. */
		static const UnicodeRange	unicodeDecimalRanges[];
		/** Necessary size of the decimal table. */
		static const size_t			unicodeDecimalTableSize;
		/** A range of whitespace characters. */
		static const UnicodeRange	unicodeSpaceRanges[];
		/** Necessary size of the whitespace table. */
		static const size_t			unicodeSpaceTableSize;

	private :
	};

}	// namespace ve
