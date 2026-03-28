#pragma once

#include <cstdint>

namespace ve {

	// == Enumerations.
	/**
	 * Numeric constant categories used to identify runtime representation 
	 * and define cast priority for C++-style type promotion.
	 **/
	enum class NumericConstant : uint8_t {
		Unsigned		= 0x00,
		Signed			= 0x01,
		Floating		= 0x02,
		Object			= 0x03,
		Invalid			= 0x80
	};

	// == Types.
	/**
	 * A tagged union representing the result of an expression evaluation.
	 **/
	struct Result {
		// == Members.
		/** The active type currently stored in the union. **/
		NumericConstant type;

		union {
			int64_t		intVal;
			uint64_t	uintVal;
			double		doubleVal;
			void *		objectVal;
		}				value;
	};

}	// namespace ve
