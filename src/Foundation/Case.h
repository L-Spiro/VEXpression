#pragma once

#include <cstdint>
#include <cstddef>

namespace ve {

	/**
	 * Provides lookup tables and resolution for full Unicode casefolding.
	 **/
	class Case {
	public :
		// == Types.
		/**
		 * Maps a single Unicode code point to its casefolded sequence.
		 **/
		struct CasefoldTable {
			/** The input Unicode code point. **/
			char32_t					uniChar;
			/** The casefolded output (can expand to up to 3 code points). **/
			char32_t					caseResult[3];
			/** The total number of characters in the output sequence. **/
			uint32_t					newSize;
		};


		// == Functions.
		/**
		 * Retrieves the casefolded sequence for a given Unicode code point.
		 *
		 * \param cp		The input Unicode code point to fold.
		 * \param outSeq	Pointer to a char32_t array (must hold at least 3 elements) to receive the output.
		 * \return			Returns the number of characters in the sequence, or 0 if it is not in the table.
		 **/
		static uint32_t					getFoldedSequence(char32_t cp, char32_t* outSeq);

		/**
		 * Retrieves the lower-case sequence for a given Unicode code point.
		 *
		 * \param cp		The input Unicode code point to fold.
		 * \param outSeq	Pointer to a char32_t array (must hold at least 2 elements) to receive the output.
		 * \return			Returns the number of characters in the sequence, or 0 if it is not in the table.
		 **/
		static uint32_t					getLowerSequence(char32_t cp, char32_t* outSeq);

		/**
		 * Retrieves the upper-case sequence for a given Unicode code point.
		 *
		 * \param cp		The input Unicode code point to upper-case.
		 * \param outSeq	Pointer to a char32_t array (must hold at least 2 elements) to receive the output.
		 * \return			Returns the number of characters in the sequence, or 0 if it is not in the table.
		 **/
		static uint32_t					getUpperSequence(char32_t cp, char32_t* outSeq);

	private :
		/** The explicit casefold expansions. **/
		static const CasefoldTable		casefoldData[];

		/** The explicit lower expansions. **/
		static const CasefoldTable		lowerData[];

		/** The explicit upper expansions. **/
		static const CasefoldTable		upperData[];
	};

}	// namespace ve
