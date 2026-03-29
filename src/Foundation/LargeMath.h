#pragma once

#include <cassert>
#include <cstdint>
#include <stdexcept>

#if defined(_MSC_VER)
	#include <intrin.h>
#endif

namespace ve {

	/**
	 * Provides 128-bit precision mathematical operations.
	 * Utilizes hardware intrinsics where available, and pure C++ manual implementations 
	 * as robust cross-platform fallbacks.
	 **/
	class LargeMath {
	public :
		// == Functions.
		/**
		 * Counts the number of leading zeros in a 32-bit integer.
		 * 
		 * \param val			The 32-bit unsigned integer to evaluate.
		 * \return				Returns the number of leading zeros (0-32).
		 **/
		static inline uint32_t			countLeadingZeros(uint32_t val) {
#if defined(_MSC_VER)
			unsigned long index;
			if (_BitScanReverse(&index, val)) {
				return 31 - index;
			}
			else {
				return 32;
			}
#else
			if (val == 0) {
				return 32;
			}
			else {
				return static_cast<uint32_t>(__builtin_clz(val));
			}
#endif
		}

		/**
		 * Adds two 128-bit unsigned integers.
		 * 
		 * \param aHigh			The high 64 bits of the first operand.
		 * \param aLow			The low 64 bits of the first operand.
		 * \param bHigh			The high 64 bits of the second operand.
		 * \param bLow			The low 64 bits of the second operand.
		 * \param highSum		Pointer to receive the high 64 bits of the result.
		 * \return				Returns the low 64 bits of the sum.
		 **/
		static inline uint64_t			uadd128(uint64_t aHigh, uint64_t aLow, uint64_t bHigh, uint64_t bLow, uint64_t* highSum) {
			assert(highSum != nullptr);
			uint64_t lowSum = aLow + bLow;
			(*highSum) = aHigh + bHigh + (lowSum < aLow ? 1 : 0);
			return lowSum;
		}

		/**
		 * Adds two 128-bit signed integers.
		 * 
		 * \param aHigh			The high 64 bits of the first operand.
		 * \param aLow			The low 64 bits of the first operand.
		 * \param bHigh			The high 64 bits of the second operand.
		 * \param bLow			The low 64 bits of the second operand.
		 * \param highSum		Pointer to receive the high 64 bits of the result.
		 * \return				Returns the low 64 bits of the sum.
		 **/
		static inline uint64_t			add128(int64_t aHigh, uint64_t aLow, int64_t bHigh, uint64_t bLow, int64_t* highSum) {
			assert(highSum != nullptr);
			uint64_t lowSum = aLow + bLow;
			(*highSum) = static_cast<int64_t>(static_cast<uint64_t>(aHigh) + static_cast<uint64_t>(bHigh) + (lowSum < aLow ? 1 : 0));
			return lowSum;
		}

		/**
		 * Multiplies two 64-bit unsigned integers to produce a 128-bit result.
		 * 
		 * \param a				The first 64-bit operand.
		 * \param b				The second 64-bit operand.
		 * \param highProduct	Pointer to receive the high 64 bits of the product.
		 * \return				Returns the low 64 bits of the product.
		 **/
		static inline uint64_t			umul128(uint64_t a, uint64_t b, uint64_t* highProduct) {
			assert(highProduct != nullptr);
#if defined(_MSC_VER) && defined(_M_X64)
			return _umul128(a, b, highProduct);
#elif defined(__SIZEOF_INT128__)
			unsigned __int128 result = static_cast<unsigned __int128>(a) * b;
			(*highProduct) = static_cast<uint64_t>(result >> 64);
			return static_cast<uint64_t>(result);
#else
			// The explicit manual fallback for architectures without native 128-bit multiplication.
			uint64_t aLo = a & 0xFFFFFFFF;
			uint64_t aHi = a >> 32;
			uint64_t bLo = b & 0xFFFFFFFF;
			uint64_t bHi = b >> 32;

			uint64_t p00 = aLo * bLo;
			uint64_t p10 = aHi * bLo;
			uint64_t p01 = aLo * bHi;
			uint64_t p11 = aHi * bHi;

			uint64_t mid = p10 + (p00 >> 32);
			mid += p01;
			uint64_t highCarry = (mid < p01) ? 1ULL : 0;

			(*highProduct) = p11 + (mid >> 32) + (highCarry << 32);
			return (mid << 32) | (p00 & 0xFFFFFFFF);
#endif
		}

		/**
		 * Multiplies two 64-bit signed integers to produce a 128-bit result.
		 * 
		 * \param a				The first 64-bit operand.
		 * \param b				The second 64-bit operand.
		 * \param highProduct	Pointer to receive the high 64 bits of the product.
		 * \return				Returns the low 64 bits of the product.
		 **/
		static inline uint64_t			mul128(int64_t a, int64_t b, int64_t* highProduct) {
			assert(highProduct != nullptr);
#if defined(_MSC_VER) && defined(_M_X64)
			return _mul128(a, b, highProduct);
#elif defined(__SIZEOF_INT128__)
			__int128 result = static_cast<__int128>(a) * b;
			(*highProduct) = static_cast<int64_t>(result >> 64);
			return static_cast<uint64_t>(result);
#else
			// The explicit manual fallback logic for signed 128-bit math
			uint64_t uHigh;
			uint64_t uLow = umul128(static_cast<uint64_t>(a), static_cast<uint64_t>(b), &uHigh);
			
			if (a < 0) {
				uHigh -= static_cast<uint64_t>(b);
			}
			if (b < 0) {
				uHigh -= static_cast<uint64_t>(a);
			}
			
			(*highProduct) = static_cast<int64_t>(uHigh);
			return uLow;
#endif
		}

		/**
		 * Divides a 128-bit unsigned integer by a 64-bit unsigned integer.
		 * 
		 * \param high			The high 64 bits of the dividend.
		 * \param low			The low 64 bits of the dividend.
		 * \param divisor		The 64-bit divisor.
		 * \param remainder		Pointer to receive the division remainder.
		 * \return				Returns the quotient.
		 **/
		static inline uint64_t			udiv128(uint64_t high, uint64_t low, uint64_t divisor, uint64_t* remainder) {
			assert(remainder != nullptr);
			assert(divisor != 0);

			if (high >= divisor) {
				throw std::overflow_error("128-bit division overflow.");
			}

#if defined(_MSC_VER) && defined(_M_X64)
			return _udiv128(high, low, divisor, remainder);
#elif defined(__SIZEOF_INT128__)
			unsigned __int128 dividend = (static_cast<unsigned __int128>(high) << 64) | low;
			(*remainder) = static_cast<uint64_t>(dividend % divisor);
			return static_cast<uint64_t>(dividend / divisor);
#else
			// The explicit manual fallback for 128-bit division using shift-and-subtract
			uint64_t remVal = high;
			uint64_t quotient = 0;
			for (int i = 0; i < 64; ++i) {
				uint64_t topBit = remVal >> 63;
				remVal = (remVal << 1) | (low >> 63);
				low <<= 1;
				quotient <<= 1;
				
				if (topBit || remVal >= divisor) {
					remVal -= divisor;
					quotient |= 1;
				}
			}
			(*remainder) = remVal;
			return quotient;
#endif
		}

		/**
		 * Divides a 128-bit signed integer by a 64-bit signed integer.
		 * 
		 * \param high			The high 64 bits of the dividend.
		 * \param low			The low 64 bits of the dividend.
		 * \param divisor		The 64-bit divisor.
		 * \param remainder		Pointer to receive the division remainder.
		 * \return				Returns the quotient.
		 **/
		static inline int64_t			div128(int64_t high, uint64_t low, int64_t divisor, int64_t* remainder) {
			assert(remainder != nullptr);
			assert(divisor != 0);

			bool isDividendNegative = (high < 0);
			bool isDivisorNegative = (divisor < 0);

			uint64_t uHigh = static_cast<uint64_t>(high);
			uint64_t uLow = low;
			if (isDividendNegative) {
				uLow = ~uLow + 1;
				uHigh = ~uHigh + (uLow == 0 ? 1 : 0);
			}

			uint64_t uDivisor = static_cast<uint64_t>(isDivisorNegative ? -divisor : divisor);
			uint64_t uRemainder = 0;

			uint64_t uQuotient = udiv128(uHigh, uLow, uDivisor, &uRemainder);

			if (isDividendNegative != isDivisorNegative) {
				uQuotient = ~uQuotient + 1;
			}
			if (isDividendNegative) {
				uRemainder = ~uRemainder + 1;
			}

			(*remainder) = static_cast<int64_t>(uRemainder);
			return static_cast<int64_t>(uQuotient);
		}

		/**
		 * Computes (a * b) / divisor using a 128-bit intermediate product.
		 * 
		 * \param a				The first operand.
		 * \param b				The second operand.
		 * \param divisor		The divisor.
		 * \param remainder		Pointer to receive the division remainder.
		 * \return				Returns the quotient.
		 **/
		static inline uint64_t			umuldiv128(uint64_t a, uint64_t b, uint64_t divisor, uint64_t* remainder) {
			uint64_t high = 0;
			uint64_t low = umul128(a, b, &high);
			return udiv128(high, low, divisor, remainder);
		}

		/**
		 * Computes round((a * b) / divisor) using a 128-bit intermediate product.
		 * This calculates (a * b + divisor / 2) / divisor.
		 * 
		 * \param a				The first operand.
		 * \param b				The second operand.
		 * \param divisor		The divisor.
		 * \param remainder		Pointer to receive the remainder after rounding.
		 * \return				Returns the rounded quotient.
		 **/
		static inline uint64_t			umuldiv128Rounded(uint64_t a, uint64_t b, uint64_t divisor, uint64_t* remainder) {
			assert(remainder != nullptr);
			assert(divisor != 0);

			uint64_t high = 0;
			uint64_t low = umul128(a, b, &high);

			uint64_t halfDivisor = divisor / 2;
			uint64_t sumHigh = 0;
			
			low = uadd128(high, low, 0, halfDivisor, &sumHigh);

			return udiv128(sumHigh, low, divisor, remainder);
		}

	protected :

	private :
	};

}	// namespace ve
