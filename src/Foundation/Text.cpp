#include "Text.h"

namespace ve {

	// == Functions.
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
	NumericConstant Text::classifyString(const std::string& sIn, uint8_t* specialBase) {
		// TODO:	The commented-out "return hasNegSign ? NumericConstant::Signed : NumericConstant::Unsigned;" might be added back
		//			but changed to "return (!DefaultToUnsigned && hasNegSign) ? NumericConstant::Signed : NumericConstant::Unsigned;"
		if (specialBase) { (*specialBase) = 0; }
		size_t idx = 0;
		while (idx < sIn.size() && isAsciiWhitespace(sIn[idx])) { ++idx; }
			
		if (idx >= sIn.size()) { return NumericConstant::Invalid; }

		bool hasNegSign = sIn[idx] == '-';
		bool hasPosSign = sIn[idx] == '+';
		if (hasNegSign || hasPosSign) {
			++idx;
		}

		if ((sIn.size() - idx) >= 3) {
			if (sIn[idx] == '0') {
				if ((sIn[idx+1] == 'x' || sIn[idx+1] == 'X')) {
					size_t i = idx + 2;
					for (; i < sIn.size() && Character::validHex(sIn[i]); ++i) {}

					if (i < sIn.size()) {
						if ((sIn[i] == 'l' || sIn[i] == 'L')) { return NumericConstant::Signed; }
						else if ((sIn[i] == 'u' || sIn[i] == 'U')) { return NumericConstant::Unsigned; }
					}

					if (i == sIn.size()) {
						if (specialBase) { (*specialBase) = 16; }
						//return hasNegSign ? NumericConstant::Signed : NumericConstant::Unsigned;
						return NumericConstant::Signed;
					}
					if (sIn[i] == '.') { return NumericConstant::Floating; }
					if ((sIn[i] == 'p' || sIn[i] == 'P') && sIn.size() > i + 1) {
						++i;
						if ((sIn[i] == '+' || sIn[i] == '-') && sIn.size() > i + 1) { ++i; }
						bool found = false;
						while (i < sIn.size() && Character::isDigit(sIn[i])) { 
							found = true; 
							++i; 
						}
						if (found) { return NumericConstant::Floating; }
					}
					if (specialBase) { (*specialBase) = 16; }
					//return hasNegSign ? NumericConstant::Signed : NumericConstant::Unsigned;
					return NumericConstant::Signed;
				}
				if ((sIn[idx+1] == 'b' || sIn[idx+1] == 'B') && Character::validBin(sIn[idx+2])) {
					idx += 2;
					while (idx < sIn.size() && Character::validBin(sIn[idx])) { ++idx; }
					if (specialBase) { (*specialBase) = 2; }
					if (idx < sIn.size()) {
						if ((sIn[idx] == 'l' || sIn[idx] == 'L')) { return NumericConstant::Signed; }
						else if ((sIn[idx] == 'u' || sIn[idx] == 'U')) { return NumericConstant::Unsigned; }
					}
					//return hasNegSign ? NumericConstant::Signed : NumericConstant::Unsigned;
					return NumericConstant::Signed;
				}
			}
		}

		bool found = false;
		size_t i = idx;
		if (specialBase) {
			for (; i < sIn.size(); ++i) {
				if (!Character::validHex(sIn[i])) { break; }
				found = true;
			}
			if (found && i < sIn.size()) {
				if (sIn[i] == 'h' || sIn[i] == 'H') {
					(*specialBase) = 16;
					//return hasNegSign ? NumericConstant::Signed : NumericConstant::Unsigned;
					return NumericConstant::Signed;
				}
			}

			found = false;
			i = idx;
		}
		for (; i < sIn.size(); ++i) {
			if (!Character::isDigit(sIn[i])) { break; }
			found = true;
		}
		if (found) {
			if (i < sIn.size()) {
				if (sIn[i] == '.') { return NumericConstant::Floating; }
				if ((sIn[i] == 'e' || sIn[i] == 'E') && sIn.size() > i + 1) {
					++i;
					if ((sIn[i] == '+' || sIn[i] == '-') && sIn.size() > i + 1) { ++i; }
					if (Character::isDigit(sIn[i])) { return NumericConstant::Floating; }
				}
				else if ((sIn[i] == 'l' || sIn[i] == 'L')) { return NumericConstant::Signed; }
				else if ((sIn[i] == 'u' || sIn[i] == 'U')) { return NumericConstant::Unsigned; }
			}
			//return hasNegSign ? NumericConstant::Signed : NumericConstant::Unsigned;
			return NumericConstant::Signed;
		}

		return NumericConstant::Invalid;
	}

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
	uint64_t Text::stoull(const char* text, int base, size_t* eaten, uint64_t maxVal, bool* overflow) {
		if (overflow) { (*overflow) = false; }
		const char* orig = text;
		bool negate = false;
		// Negate?
		if (text[0] == '-') {
			negate = true;
			++text;
		}
		else if (text[0] == '+') {
			++text;
		}

		// Skip whitespace.
		while (isAsciiWhitespace((*text))) {
			++text;
		}

		// Skip any opening "0", "0x", etc.
		if ((*text) == '0') {
			++text;
				
			if ((*text) == 'b' || (*text) == 'B') {
				++text;
				base = 2;
			}
			else if ((*text) == 'x' || (*text) == 'X') {
				++text;
				base = 16;
			}
			else if ((*text) == 'o' || (*text) == 'O') {
				++text;
				base = 8;
			}
			else if (base <= 0) {
				base = 8;
			}
		}
			
		if (base <= 0) {
			base = 10;
		}
			
		uint64_t res = 0;
		for (; (*text); ++text) {
			uint8_t next = static_cast<uint8_t>((*text));
			if (next >= '0' && next <= '9') {
				next -= '0';
			}
			else {
				if (next >= 'A' && next <= 'Z') {
					next -= 'A';
				}
				else {
					next -= 'a';
				}
				next += 10;
			}
				
			if (next >= base) {
				break;
			}
				
			uint64_t temp = res;
			uint64_t preview = res * static_cast<uint64_t>(base) + next;
			// Bounds checking.
			if (preview > maxVal) { break; }

			if ((preview - next) / base != temp) {
				if (eaten) { (*eaten) = text - orig + 1; }
				if (overflow) { (*overflow) = true; }
				return std::numeric_limits<uint64_t>::max();
			}
			res = preview;
		}
			
		if (eaten) { (*eaten) = text - orig; }
		return negate ? static_cast<uint64_t>(-static_cast<int64_t>(res)) : res;
	}

	/**
	 * String to double. Unlike std::atof(), this returns the number of characters eaten, and casts to float when the f postfix is seen.
	 *
	 * \param text		The text to parse.
	 * \param eaten		The number of characters consumed while parsing the double value.
	 * \param error		Optional pointer to a boolean which will be set to true if there are parsing errors.
	 * \return			Returns the parsed double.
	 **/
	double Text::atof(const char* text, size_t* eaten, bool* error) {
		const char* orig = text;
		if (error) { (*error) = true; }
		// The number is in the following format:
		// [whitespace] [sign] [digits] [.digits] [ {e | E }[sign]digits]
		// Skip whitespace.
		while (isAsciiWhitespace((*text))) { ++text; }
			
		const char* numberBegins = text;
		// Optional sign.
		if ((*text) == '-' || (*text) == '+') {
			++text;
		}
			
		if (text[0] == '0' && (text[1] == 'X' || text[1] == 'x') && (Character::validHex(text[2]) || text[2] == '.')) {
			text += 2;
			// Digits are optional.
			bool hasDigits = false;
			while (Character::validHex((*text))) {
				++text;
				hasDigits = true;
			}

			// A decimal point is optional.
			if ((*text) == '.') {
				++text;
				while (Character::validHex((*text))) {
					++text;
					hasDigits = true;
				}
			}

			if (!hasDigits) {
				if (eaten) { (*eaten) = text - orig; }
				return 0.0;
			}

			// Exponent.
			if ((*text) != 'P' && (*text) != 'p') {
				if (eaten) { (*eaten) = text - orig; }
				return 0.0;
			}
			++text;

			// Optional sign.
			if ((*text) == '-' || (*text) == '+') {
				++text;
			}
				
			// Digits must be next.
			if (!Character::isDigit((*text))) {
				if (eaten) { (*eaten) = text - orig; }
				return 0.0;
			}
			while (Character::isDigit((*text))) { ++text; }
		}
		else {
			// Digits must be next.
			if (!Character::isDigit((*text))) {
				if (eaten) { (*eaten) = text - orig; }
				return 0.0;
			}
			while (Character::isDigit((*text))) { ++text; }

			// A decimal point and trailing digits are optional.
			if ((*text) == '.') {
				++text;
				while (Character::isDigit((*text))) { ++text; }
			}
			// Exponent.
			if ((*text) == 'E' || (*text) == 'e') {
				++text;
				// Optional sign.
				if ((*text) == '-' || (*text) == '+') {
					++text;
				}
				// Digits must be next.
				if (!Character::isDigit((*text))) {
					if (eaten) { (*eaten) = text - orig; }
					return 0.0;
				}
				while (Character::isDigit((*text))) { ++text; }
			}
		}

		// Optional suffix.
		bool isFloat = false;
		if ((*text) == 'f' || (*text) == 'F') {
			++text;
			isFloat = true;
		}
		else if ((*text) == 'l' || (*text) == 'L') {
			++text;
		}

		if (eaten) { (*eaten) = text - orig; }
		if (error) { (*error) = false; }
			
		return isFloat ? static_cast<double>(static_cast<float>(std::atof(numberBegins))) : std::atof(numberBegins);
	}

}	// namespace ve
