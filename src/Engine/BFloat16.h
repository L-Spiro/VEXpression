#pragma once

#include <cstdint>

namespace ve {

	class BFloat16 {
	public:
		BFloat16() :
			valueBits(0) {
		}
		BFloat16(double val) {
			valueBits = doubleToUint16(val);
		}
		BFloat16(uint16_t bits) :
			valueBits(bits) {
		}
		BFloat16(const uint8_t* bitsPtr) :
			valueBits((*reinterpret_cast<const uint16_t*>(bitsPtr))) {
		}


		// == Operators.
		/**
		 * \brief Casts this value to a signed 8-bit integer.
		 *
		 * \return Returns the value converted from the bfloat16 representation to \c int8_t.
		 *
		 * \note Conversion is performed by first converting to a float via value() and then casting to \c int8_t.
		 */
		operator					int8_t() const {
			return int8_t(value());
		}

		/**
		 * \brief Casts this value to a signed 16-bit integer.
		 *
		 * \return Returns the value converted from the bfloat16 representation to \c int16_t.
		 *
		 * \note Conversion is performed by first converting to a float via value() and then casting to \c int16_t.
		 */
		operator					int16_t() const {
			return int16_t(value());
		}

		/**
		 * \brief Casts this value to a signed 32-bit integer.
		 *
		 * \return Returns the value converted from the bfloat16 representation to \c int32_t.
		 *
		 * \note Conversion is performed by first converting to a float via value() and then casting to \c int32_t.
		 */
		operator					int32_t() const {
			return int32_t(value());
		}

		/**
		 * \brief Casts this value to a signed 64-bit integer.
		 *
		 * \return Returns the value converted from the bfloat16 representation to \c int64_t.
		 *
		 * \note Conversion is performed by first converting to a float via value() and then casting to \c int64_t.
		 */
		operator					int64_t() const {
			return int64_t(value());
		}

		/**
		 * \brief Casts this value to an unsigned 8-bit integer.
		 *
		 * \return Returns the value converted from the bfloat16 representation to \c uint8_t.
		 *
		 * \note Conversion is performed by first converting to a float via value() and then casting to \c uint8_t.
		 */
		operator					uint8_t() const {
			return uint8_t(value());
		}
		
		/**
		 * \brief Casts this value to an unsigned 16-bit integer.
		 *
		 * \return Returns the value converted from the bfloat16 representation to \c uint16_t.
		 *
		 * \note Conversion is performed by first converting to a float via value() and then casting to \c uint16_t.
		 */
		operator					uint16_t() const {
			return uint16_t(value());
		}
		
		/**
		 * \brief Casts this value to an unsigned 32-bit integer.
		 *
		 * \return Returns the value converted from the bfloat16 representation to \c uint32_t.
		 *
		 * \note Conversion is performed by first converting to a float via value() and then casting to \c uint32_t.
		 */
		operator					uint32_t() const {
			return uint32_t(value());
		}
		
		/**
		 * \brief Casts this value to an unsigned 64-bit integer.
		 *
		 * \return Returns the value converted from the bfloat16 representation to \c uint64_t.
		 *
		 * \note Conversion is performed by first converting to a float via value() and then casting to \c uint64_t.
		 */
		operator					uint64_t() const {
			return uint64_t(value());
		}
		
		/**
		 * \brief Casts this value to a 32-bit floating-point number.
		 *
		 * \return Returns the value converted from the bfloat16 representation to \c float.
		 *
		 * \note Conversion uses value(), which returns a float value.
		 */
		operator					float() const {
			return float(value());
		}
		
		/**
		 * \brief Casts this value to a 64-bit floating-point number.
		 *
		 * \return Returns the value converted from the bfloat16 representation to \c double.
		 *
		 * \note Conversion uses value(), which returns a float value and then casts it to \c double.
		 */
		operator					double() const {
			return double(value());
		}


		// == Functions.
		/**
		 * \brief Gets the value as a double.
		 *
		 * \return Returns the numeric value represented by the internal bfloat16 bit pattern as a \c double.
		 *
		 * \note This performs a bfloat16 (1 sign bit, 8 exponent bits, 7 fraction bits) to single-precision conversion,
		 * then returns the resulting \c float as a \c double.
		 * \note NaN, infinity, and subnormals map cleanly to their single-precision counterparts simply by padding with zeros.
		 */
		double						value() const {
			union {
				float floatVal;
				uint32_t uintVal;
			} tmp;

			tmp.uintVal = static_cast<uint32_t>(valueBits) << 16;
			
			return tmp.floatVal;
		}

		/**
		 * \brief Gets the raw 16-bit bit pattern.
		 *
		 * \return Returns the stored 16-bit value containing the bfloat16 bit fields.
		 */
		uint16_t					rawValue() const { return valueBits; }

		/**
		 * \brief Gets the maximum finite value representable by the bfloat16 format.
		 *
		 * \return Returns the maximum finite bfloat16 value, as a \c double.
		 *
		 * \note This returns a constant (3.389531389e38), which is the maximum finite value.
		 */
		static double				max() {
			return 338953138925153547590470800371487866880.0;
		}

		/**
		 * \brief Converts from a double to a 16-bit integer containing the bits for the bfloat16.
		 *
		 * \param val The input value to convert.
		 * \return Returns a 16-bit value containing the bfloat16 encoding of \p val.
		 *
		 * \note The input is first converted to \c float, and the conversion is performed from that single-precision representation.
		 * \note NaN and infinity are preserved.
		 * \note Rounding is performed using a round-to-nearest-even tie-breaking rule.
		 */
		static uint16_t				doubleToUint16(double val) {
			union {
				float floatVal;
				uint32_t uintVal;
			} tmp;
			
			tmp.floatVal = static_cast<float>(val);
			
			if ((tmp.uintVal & 0x7FFFFFFF) > 0x7F800000) {
				return static_cast<uint16_t>((tmp.uintVal >> 16) | 0x0040);
			}
			
			uint32_t roundingBias = 0x7FFF + ((tmp.uintVal >> 16) & 1);
			tmp.uintVal += roundingBias;
			
			return static_cast<uint16_t>(tmp.uintVal >> 16);
		}


	protected:
		// == Members.
		uint16_t					valueBits;
	};

}	// namespace ve
