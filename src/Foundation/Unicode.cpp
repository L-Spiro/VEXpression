#include "Unicode.h"

#include <algorithm>
#include <cstring>
#include <string>

// Include the generated data table.
#include "UnicodeData.inl"

namespace ve {

	// Constant array of prefixes mapped to algorithmic hex code points.
	constexpr std::string_view algorithmicHexPrefixes[] = {
		"CJK UNIFIED IDEOGRAPH-",
		"CJK COMPATIBILITY IDEOGRAPH-",
		"KHITAN SMALL SCRIPT CHARACTER-",
		"NUSHU CHARACTER-"
	};

	constexpr std::string_view tangutComponentPrefix = "TANGUT COMPONENT-";

	uint32_t Unicode::getCodeByName(const char* name, size_t len) {
		// Convert incoming name to uppercase for case-insensitive matching.
		// Unicode character names are strictly ASCII.
		std::string upperNameStr;
		upperNameStr.reserve(len);
		
		for (size_t i = 0; i < len; ++i) {
			char c = name[i];
			
			if (c >= 'a' && c <= 'z') {
				upperNameStr.push_back(static_cast<char>(c - 'a' + 'A'));
			}
			else {
				upperNameStr.push_back(c);
			}
		}
		
		std::string_view searchName(upperNameStr.data(), upperNameStr.length());

		// Manually handle algorithmic hex names (Prefix + Hex).
		for (const std::string_view& prefix : algorithmicHexPrefixes) {
			if (searchName.length() > prefix.length() && searchName.substr(0, prefix.length()) == prefix) {
				std::string_view hexPart = searchName.substr(prefix.length());
				uint32_t codePoint = 0;
				bool validHex = true;
				
				for (char c : hexPart) {
					if (c >= '0' && c <= '9') {
						codePoint = (codePoint << 4) | static_cast<uint32_t>(c - '0');
					}
					else if (c >= 'A' && c <= 'F') {
						codePoint = (codePoint << 4) | static_cast<uint32_t>(c - 'A' + 10);
					}
					else if (c >= 'a' && c <= 'f') {
						// This branch will technically not be hit due to the upperNameStr conversion above, 
						// but is left here for algorithmic completeness if the input rules ever change.
						codePoint = (codePoint << 4) | static_cast<uint32_t>(c - 'a' + 10);
					}
					else {
						validHex = false;
						break;
					}
				}
				
				if (validHex && hexPart.length() > 0) {
					return codePoint;
				}
			}
		}

		// Manually handle Tangut Components (Prefix + Decimal).
		// Tangut components are named TANGUT COMPONENT-001 through TANGUT COMPONENT-768.
		if (searchName.length() > tangutComponentPrefix.length() && searchName.substr(0, tangutComponentPrefix.length()) == tangutComponentPrefix) {
			std::string_view decPart = searchName.substr(tangutComponentPrefix.length());
			uint32_t componentNum = 0;
			bool validDec = true;
			
			for (char c : decPart) {
				if (c >= '0' && c <= '9') {
					componentNum = (componentNum * 10) + static_cast<uint32_t>(c - '0');
				}
				else {
					validDec = false;
					break;
				}
			}
			
			if (validDec && decPart.length() > 0) {
				// Component 001 maps to U+18800.
				return 0x187FF + componentNum;
			}
		}

		// Binary search for standard named entities using string_view for zero-allocation comparisons.
		auto comp = [](const UnicodeNameEntry& entry, std::string_view target) {
			std::string_view entryName(entry.name, entry.length);
			return entryName < target;
		};

		auto it = std::lower_bound(unicodeNames, unicodeNames + numUnicodeNames, searchName, comp);

		if (it != unicodeNames + numUnicodeNames && std::string_view(it->name, it->length) == searchName) {
			return it->codePoint;
		}

		return 0xFFFFFFFF; // Text::UTF_INVALID
	}

}	// namespace ve
