#pragma once

namespace ve {

	// == Enumerations.
	/**
	 * Kind of sort to apply to a text column.
	 **/
	enum class TextPolicy {
		OrdinalCi = 0,	/**< Case-insensitive ordinal (basic Unicode fold). */
		NaturalCi		/**< Natural order: numeric runs compare by value, case-insensitive. */
	};

}	// namespace ve
