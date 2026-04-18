#pragma once

#include <cstdint>

namespace ve {

#define VE_STR1(id, txt)	VE_STR(id, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt, txt)

	// == Enumerations.
	/**
	 * Languages.
	 **/
	enum class Languages {
		English				= 0,
		Japanese			= 1,
		Chinese				= 2,
		Spanish				= 3,
		French				= 4,
		Italian				= 5,
		Portuguese			= 6,
		Arabic				= 7,
		Russia				= 8,
		German				= 9,
		Dutch				= 10,
		Korean				= 11,
		Thai				= 12,
		Hindi				= 13,
		Turkish				= 14,
	};

	/**
	 * Unique identifiers for localized strings.
	 **/
	enum class StringId {
#define VE_STR( id, ... ) id,
#include "StringEnum.inl"
#undef VE_STR
	};


	/**
	 * Gets a string by ID.
	 * 
	 * \param id			The ID of the string to return.
	 * \param language		The language for the string to select.
	 * \return				Returns the requested string as an L"" string.
	 **/
	inline const wchar_t*	StrL(StringId id, size_t language) {
		switch ( id ) {
#define VE_STR( id, en, ja, zh, es, fr, it, pt, ar, ru, de, nl, ko, th, hi, tr )						case StringId::id : { const wchar_t* strings[] = { L##en, L##ja, L##zh, L##es, L##fr, L##it, L##pt, L##ar, L##ru, L##de, L##nl, L##ko, L##th, L##hi, L##tr }; return strings[language]; }

#include "StringEnum.inl"
#undef VE_STR
			default : { return L""; }
		}
	}

	/**
	 * Gets a string by ID.
	 * 
	 * \param id			The ID of the string to return.
	 * \param language		The language for the string to select.
	 * \return				Returns the requested string as a u"" string.
	 **/
	inline const char16_t*	StrU(StringId id, size_t language) {
		switch ( id ) {
#define VE_STR( id, en, ja, zh, es, fr, it, pt, ar, ru, de, nl, ko, th, hi, tr )						case StringId::id : { const char16_t* strings[] = { u##en, u##ja, u##zh, u##es, u##fr, u##it, u##pt, u##ar, u##ru, u##de, u##nl, u##ko, u##th, u##hi, u##tr }; return strings[language]; }

#include "StringEnum.inl"
#undef VE_STR
			default : { return u""; }
		}
	}

	/**
	 * Gets a string by ID.
	 * 
	 * \param id			The ID of the string to return.
	 * \param language		The language for the string to select.
	 * \return				Returns the requested string as a u8"" string.
	 **/
	inline const char8_t*	StrU8(StringId id, size_t language) {
		switch ( id ) {
#define VE_STR( id, en, ja, zh, es, fr, it, pt, ar, ru, de, nl, ko, th, hi, tr )						case StringId::id : { const char8_t* strings[] = { u8##en, u8##ja, u8##zh, u8##es, u8##fr, u8##it, u8##pt, u8##ar, u8##ru, u8##de, u8##nl, u8##ko, u8##th, u8##hi, u8##tr }; return strings[language]; }

#include "StringEnum.inl"
#undef VE_STR
			default : { return u8""; }
		}
	}

}	// namespace ve
