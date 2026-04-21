#pragma once

#include <cstdint>
#include <string_view>

namespace ve {

	/**
	 * Provides storage and resolution utilities for named Unicode characters.
	 **/
	class Unicode {
	public :
		// == Functions.
		/**
		 * Gets the Unicode code point given its official name.
		 *
		 * \param name			Pointer to the character name (e.g., "LATIN SMALL LETTER A").
		 * \param len			Length of the name string in bytes.
		 * \return				Returns the Unicode code point, or 0xFFFFFFFF if not found.
		 **/
		static uint32_t						getCodeByName(const char* name, size_t len);

	private :
		struct UnicodeNameEntry {
			const char*						name;
			uint32_t						length;
			uint32_t						codePoint;
		};

		static const UnicodeNameEntry		unicodeNames[];
		static const size_t					numUnicodeNames;
	};

}	// namespace ve
