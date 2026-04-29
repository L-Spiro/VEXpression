#pragma once

#include <cstdint>

// ********************************************************* //
// Logic largely ripped from https://github.com/x448/float16 //
// ********************************************************* //

namespace ve {

	class Float16 {
	public:
		Float16() :
			valueBits(0) {
		}
		Float16(double val) {
			valueBits = doubleToUint16(val);
		}
		Float16(uint16_t bits) :
			valueBits(bits) {
		}
		Float16(const uint8_t* bitsPtr) :
			valueBits((*reinterpret_cast<const uint16_t*>(bitsPtr))) {
		}


		// == Operators.
		/**
		 * \brief Casts this value to a signed 8-bit integer.
		 *
		 * \return Returns the value converted from the 16-bit float representation to \c int8_t.
		 *
		 * \note Conversion is performed by first converting to a float via value() and then casting to \c int8_t.
		 */
		operator					int8_t() const {
			return int8_t(value());
		}

		/**
		 * \brief Casts this value to a signed 16-bit integer.
		 *
		 * \return Returns the value converted from the 16-bit float representation to \c int16_t.
		 *
		 * \note Conversion is performed by first converting to a float via value() and then casting to \c int16_t.
		 */
		operator					int16_t() const {
			return int16_t(value());
		}

		/**
		 * \brief Casts this value to a signed 32-bit integer.
		 *
		 * \return Returns the value converted from the 16-bit float representation to \c int32_t.
		 *
		 * \note Conversion is performed by first converting to a float via value() and then casting to \c int32_t.
		 */
		operator					int32_t() const {
			return int32_t(value());
		}

		/**
		 * \brief Casts this value to a signed 64-bit integer.
		 *
		 * \return Returns the value converted from the 16-bit float representation to \c int64_t.
		 *
		 * \note Conversion is performed by first converting to a float via value() and then casting to \c int64_t.
		 */
		operator					int64_t() const {
			return int64_t(value());
		}

		/**
		 * \brief Casts this value to an unsigned 8-bit integer.
		 *
		 * \return Returns the value converted from the 16-bit float representation to \c uint8_t.
		 *
		 * \note Conversion is performed by first converting to a float via value() and then casting to \c uint8_t.
		 */
		operator					uint8_t() const {
			return uint8_t(value());
		}
		
		/**
		 * \brief Casts this value to an unsigned 16-bit integer.
		 *
		 * \return Returns the value converted from the 16-bit float representation to \c uint16_t.
		 *
		 * \note Conversion is performed by first converting to a float via value() and then casting to \c uint16_t.
		 */
		operator					uint16_t() const {
			return uint16_t(value());
		}
		
		/**
		 * \brief Casts this value to an unsigned 32-bit integer.
		 *
		 * \return Returns the value converted from the 16-bit float representation to \c uint32_t.
		 *
		 * \note Conversion is performed by first converting to a float via value() and then casting to \c uint32_t.
		 */
		operator					uint32_t() const {
			return uint32_t(value());
		}
		
		/**
		 * \brief Casts this value to an unsigned 64-bit integer.
		 *
		 * \return Returns the value converted from the 16-bit float representation to \c uint64_t.
		 *
		 * \note Conversion is performed by first converting to a float via value() and then casting to \c uint64_t.
		 */
		operator					uint64_t() const {
			return uint64_t(value());
		}
		
		/**
		 * \brief Casts this value to a 32-bit floating-point number.
		 *
		 * \return Returns the value converted from the 16-bit float representation to \c float.
		 *
		 * \note Conversion uses value(), which returns a float value.
		 */
		operator					float() const {
			return float(value());
		}
		
		/**
		 * \brief Casts this value to a 64-bit floating-point number.
		 *
		 * \return Returns the value converted from the 16-bit float representation to \c double.
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
		 * \return Returns the numeric value represented by the internal 16-bit float bit pattern as a \c double.
		 *
		 * \note This performs an IEEE-754 half-precision (1 sign bit, 5 exponent bits, 10 fraction bits) to single-precision conversion,
		 * then returns the resulting \c float as a \c double.
		 * \note NaN and infinity are preserved. Subnormals are normalized into the single-precision representation.
		 * \note The sign is propagated for all cases, including signed zero.
		 */
		double						value() const {
			union {
				float floatVal;
				uint32_t uintVal;
			} tmp;

			uint32_t sign = (valueBits & 0x8000) << 16;
			uint32_t exp = (valueBits & 0x7C00) >> 10;
			uint32_t coef = (valueBits & 0x03FF) << 13;
			do {
				if (exp == 0x1F) {
					tmp.uintVal = coef == 0 ?
						(sign | 0x7F800000 | coef) :
						(sign | 0x7FC00000 | coef);
					break;
				}
				if (exp == 0) {
					if (!coef) {
						tmp.uintVal = sign;
						break;
					}
					++exp;
					while ((coef & 0x7F800000) == 0) {
						coef <<= 1;
						--exp;
					}
					coef &= 0x007FFFFF;
				}

				tmp.uintVal = sign | ((exp + (0x7F - 0xF)) << 23) | coef;
			} while (false);
			return tmp.floatVal;
		}

		/**
		 * \brief Gets the raw 16-bit bit pattern.
		 *
		 * \return Returns the stored 16-bit value containing the IEEE-754 half-precision bit fields.
		 */
		uint16_t					rawValue() const { return valueBits; }

		/**
		 * \brief Gets the maximum finite value representable by this 16-bit float format.
		 *
		 * \return Returns the maximum finite half-precision value, as a \c double.
		 *
		 * \note This returns a constant (65504.0), which is the IEEE-754 binary16 maximum finite value.
		 */
		static double				max() {
			/*static double dMax = ve::FloatX::GetMaxForBits( 5, 11, true );
			return dMax;*/
			return 65504.0;
		}

		/**
		 * \brief Converts from a double to a 16-bit integer containing the bits for the 16-bit float.
		 *
		 * \param val The input value to convert.
		 * \return Returns a 16-bit value containing the IEEE-754 half-precision encoding of \p val.
		 *
		 * \note The input is first converted to \c float, and the conversion is performed from that single-precision representation.
		 * \note NaN and infinity are preserved. Values that overflow the half-precision range are converted to infinity.
		 * \note Subnormal results are generated when the magnitude is too small to be represented as a normal half.
		 * \note Rounding is performed using a tie-breaking rule based on the discarded bits (see the round-bit checks).
		 */
		static uint16_t				doubleToUint16(double val) {
			union {
				float floatVal;
				uint32_t uintVal;
			} tmp;
			tmp.floatVal = static_cast<float>(val);
			uint32_t sign = tmp.uintVal & 0x80000000;
			uint32_t exp = tmp.uintVal & 0x7F800000;
			uint32_t coef = tmp.uintVal & 0x007FFFFF;
			if (exp == 0x7F800000) {
				// NaN or Inf.
				uint32_t nanBit = 0;
				if (!coef) { nanBit = 0x0200; }
				return static_cast<uint16_t>((sign >> 16) | 0x7C00 | nanBit | (coef >> 13));
			}
			uint32_t halfSign = sign >> 16;
			int32_t unbiasedExp = (exp >> 23) - 127;
			int32_t halfExp = unbiasedExp + 15;

			if (halfExp >= 0x1F) { return static_cast<uint16_t>(halfSign | 0x7C00); }
			if (halfExp <= 0) {
				if (14 - halfExp > 24) { return static_cast<uint16_t>(halfSign); }
				uint32_t c = coef | 0x00800000;
				uint32_t halfCoef = c >> static_cast<uint32_t>(14 - halfExp);
				uint32_t roundBit = 1 << static_cast<uint32_t>(13 - halfExp);
				if ((c & roundBit) != 0 && (c & (3 * roundBit - 1)) != 0) {
					halfCoef++;
				}
				return static_cast<uint16_t>(halfSign | halfCoef);
			}
			uint32_t halfEp = halfExp << 10;
			uint32_t halfCoef = coef >> 13;
			uint32_t roundBit = 0x00001000;
			if ((coef & roundBit) != 0 && (coef & (3 * roundBit - 1)) != 0) {
				return static_cast<uint16_t>((halfSign | halfEp | halfCoef) + 1);
			}
			return static_cast<uint16_t>(halfSign | halfEp | halfCoef);
		}


	protected:
		// == Members.
		uint16_t					valueBits;
	};

}	// namespace ve
