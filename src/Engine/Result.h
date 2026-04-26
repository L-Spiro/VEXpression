#pragma once

#include <cstdint>
#include <type_traits>

namespace ve {

	class				Object;

	// == Enumerations.
	/**
	 * Numeric constant categories used to identify runtime representation 
	 * and define cast priority for C++-style type promotion.
	 **/
	enum class NumericConstant : uint8_t {
		Signed			= 0x00,
		Unsigned		= 0x01,
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
		NumericConstant type = NumericConstant::Invalid;

		union {
			int64_t		intVal;
			uint64_t	uintVal;
			double		doubleVal;
			Object *	objectVal;
		}				value;


		// == Functions.
		/**
		 * Determines if the Result is a primitive type (Unsigned, Signed, or Floating).
		 * 
		 * \return		Returns true if the type is Unsigned, Signed, or Floating.
		 **/
		inline bool		isPrimitive() const {
			return type == NumericConstant::Signed || type == NumericConstant::Unsigned || type == NumericConstant::Floating;
		}

		/**
		 * Creates a Result object directly from a C++ arithmetic type.
		 * Resolves the underlying NumericConstant type and union assignment at compile time.
		 * 
		 * \param val	The numeric constant to wrap.
		 * \return		Returns a properly initialized Result.
		 **/
		template <typename T>
		static Result	make(T val) {
			static_assert(std::is_arithmetic_v<T>, "Result::make requires an arithmetic type.");

			Result out;

			if constexpr (std::is_floating_point_v<T>) {
				out.type = NumericConstant::Floating;
				out.value.doubleVal = static_cast<double>(val);
			}
			else if constexpr (std::is_integral_v<T> && std::is_signed_v<T>) {
				out.type = NumericConstant::Signed;
				out.value.intVal = static_cast<int64_t>(val);
			}
			else if constexpr (std::is_integral_v<T> && std::is_unsigned_v<T>) {
				out.type = NumericConstant::Unsigned;
				out.value.uintVal = static_cast<uint64_t>(val);
			}

			return out;
		}

		
		
	};

}	// namespace ve
