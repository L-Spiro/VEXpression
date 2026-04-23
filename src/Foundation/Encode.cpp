#include "Encode.h"
#include "Text.h"


namespace ve {

	// == Members.
	/** The string-to-ID database. */
	const Encode::Enum_Mapping Encode::enumMapping[] = {
#define VE_ENC(id, name, enumName)		{ CodePage::enumName, name, },
#include "EncodeEnum.inl"
#undef VE_ENC
	};

	// == Functions.
	/**
	 * Dummy function to map a CodePage enum to an iconv-compatible string descriptor.
	 *
	 * \param codePage		The numeric code page identifier.
	 * \return				Returns a string descriptor (e.g., "SHIFT_JIS").
	 **/
	const char* Encode::getCodePageString(CodePage codePage) {
		if constexpr (sizeof(enumMapping) == 0) {
			return "UTF-8";
		}

		size_t left = 0;
		size_t right = std::size(enumMapping) - 1;

		while (left <= right) {
			size_t mid = left + (right - left) / 2;

			if (enumMapping[mid].codePage == codePage) { return enumMapping[mid].name; }

			if (enumMapping[mid].codePage < codePage) {
				left = mid + 1;
			}
			else {
				if (mid == 0) { break; }
				right = mid - 1;
			}
		}

		return "UTF-8";
	}

	/**
	 * Retrieves the CodePage identifier associated with a string descriptor.
	 * Performs a case-insensitive, locale-independent search.
	 *
	 * \param name			The string descriptor to search for (e.g., "SHIFT_JIS").
	 * \param outCodePage	Output parameter to store the resolved CodePage.
	 * \return				Returns true if a matching code page was found, false otherwise.
	 **/
	bool Encode::getCodePageId(std::string_view name, CodePage& outCodePage) {
		std::string upperName;
		upperName.reserve(name.length());

		for (size_t i = 0; i < name.length(); ++i) {
			upperName += static_cast<char>(Text::toUpper(static_cast<unsigned char>(name[i])));
		}

		for (size_t i = 0; i < std::size(enumMapping); ++i) {
			std::string_view entryName = enumMapping[i].name;

			if (entryName == upperName) {
				outCodePage = enumMapping[i].codePage;
				return true;
			}
		}

		return false;
	}

}	// namespace ve
