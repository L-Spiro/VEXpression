#pragma once

#include <cmath>
#include <numbers>
#include <numeric>
#include <optional>
#include <stdexcept>
#include <vector>

namespace ve {

	/**
	 * Provides standard mathematical utilities, filters, and comparisons.
	 **/
	class Math {
	public :
		// == Enumerations.
		/** Window types. */
		enum class WindowType {
			bartlett,
			blackman,
			blackmanHarris,
			blackmanNuttal,
			bohman,
			boxcar,
			chebwin,
			cosine,
			dpss,
			exponential,
			flatTop,
			gaussian,
			generalCosine,
			generalGaussian,
			generalHamming,
			hann,
			hamming,
			kaiser,
			kaiserBesselDerived,
			lanczos,
			nuttall,
			parzen,
			taylor,
			triang,
			tukey,
		};


		// == Types.
		/**
		 * Function pointer definition for generating window filters.
		 **/
		template <typename Type = double>
		using PfWindowFunc =		bool (*)(size_t n, std::vector<Type>& ret);


		// ===============================
		// General Math & Utilities
		// ===============================
		// == Functions.
		/**
		 * Returns the smaller of two values.
		 * 
		 * \param a		The first value to compare.
		 * \param b		The second value to compare.
		 * \return		Returns a if a < b; otherwise returns b.
		 **/
		template <typename Type>
		static inline Type			min(const Type& a, const Type& b) { 
			return a < b ? a : b; 
		}

		/**
		 * Returns the larger of two values.
		 * 
		 * \param a		The first value to compare.
		 * \param b		The second value to compare.
		 * \return		Returns a if a > b; otherwise returns b.
		 **/
		template <typename Type>
		static inline Type			max(const Type& a, const Type& b) { 
			return a > b ? a : b; 
		}

		/**
		 * Clamps the given value between the given range.
		 *
		 * \param value	The value to clamp.
		 * \param low	Lower limit for the clamped value.
		 * \param high	Upper limit for the clamped value.
		 * \return		Returns the given value clamped within the given range.
		 **/
		template <typename Type>
		static Type					clamp(Type value, Type low, Type high) {
			if (value < low) { return low; }
			if (value > high) { return high; }
			return value;
		}

		/**
		 * Gets the largest absolute value in the given vector.
		 * 
		 * \param a		The vector to evaluate.
		 * \return		Returns the maximum absolute value in the given vector.
		 **/
		template <typename Type = std::vector<double>>
		static inline typename Type::value_type
									maxVec(const Type& a) {
			typename Type::value_type ret = typename Type::value_type(0);
			for (size_t i = a.size(); i--; ) {
				typename Type::value_type tmp = a[i];
				tmp = tmp < typename Type::value_type(0) ? -tmp : tmp;
				ret = max(ret, tmp);
			}
			return ret;
		}

		/**
		 * Gets the fractional part of a given double value. Differs from std::fmod( x, 1.0 ) because std::fmod( -9.7, 1.0 ) returns -0.699999999999999289457264239899814128875732421875
		 *	while frac( -9.7 ) returns 0.300000000000000710542735760100185871124267578125.
		 * 
		 * \param x			The values whose fractional part is to be returned.
		 * \return			Returns the fractional part of x.
		 **/
		static inline double		frac(double x) {
			return x - std::floor(x);
		}

		/**
		 * Shader-style step function.
		 * 
		 * \param edge		The edge location.
		 * \param x			The input value.
		 * \return			Returns 0.0 if x < edge, else 1.0.
		 **/
		static inline double		step(double edge, double x) {
			return (x < edge) ? 0.0 : 1.0;
		}

		/**
		 * Standard sinc() function.
		 * 
		 * \param x		The operand.
		 * \return		Returns sin(x*PI) / (x*PI).
		 **/
		static inline double		sinc(double x) {
			x = std::fabs(x * std::numbers::pi);
			if (x < 0.01) {
				double xSq = x * x;
				return 1.0 + xSq * ((-1.0 / 6.0) + xSq * (1.0 / 120.0));
			}

			return sinExact(x) / x;
		}

		/**
		 * Performs a relative epsilon comparison between two floating-point values.
		 * Uses a scaled absolute comparison to safely handle values near zero.
		 * 
		 * \param left		The first value.
		 * \param right		The second value.
		 * \param epsilon	The relative epsilon tolerance.
		 * \return			Returns true if the values are within the scaled epsilon distance.
		 **/
		static inline bool			relativeEpsilon(double left, double right, double epsilon) {
			if (left == right) {
				return true;
			}
			else {
				double diff = std::abs(left - right);
				double absLeft = std::abs(left);
				double absRight = std::abs(right);
				double largest = (absRight > absLeft) ? absRight : absLeft;
				
				if (diff <= largest * epsilon) {
					return true;
				}
				else {
					return false;
				}
			}
		}

		/**
		 * Computes the least common multiple (LCM) of two integers.
		 *
		 * \param a			First integer value.
		 * \param b			Second integer value.
		 * \return			Returns the LCM (always non-negative). If either input is 0, returns 0.
		 **/
		template <typename Int>
		static inline Int			lcm(Int a, Int b) {
			static_assert(std::is_integral_v<Int>, "");

			if (a == 0 || b == 0) {
				return 0;
			}

			Int gcdVal = std::gcd(a, b);

			// Divide before multiply to reduce overflow risk.
			// Note: This can still overflow for large values; see lcmChecked() below if you need detection.
			Int div = a / gcdVal;
			Int lcmVal = div * b;

			// LCM is defined as non-negative.
			if (lcmVal < 0) {
				lcmVal = -lcmVal;
			}

			return lcmVal;
		}

		/**
		 * Computes the LCM of two integers, returning std::nullopt on overflow.
		 *
		 * \param a			First integer value.
		 * \param b			Second integer value.
		 * \return			Returns the LCM if it fits in the type; otherwise std::nullopt. If either input is 0, returns 0.
		 **/
		template <typename Int>
		static inline std::optional<Int>
									lcmChecked(Int a, Int b) {
			static_assert(std::is_integral_v<Int>, "");

			if (a == 0 || b == 0) {
				return Int(0);
			}

			Int gcdVal = std::gcd(a, b);
			Int div = a / gcdVal;

			// Overflow check for: div * b
			// Use unsigned magnitude checks to handle negatives safely.
			using Unsigned = std::make_unsigned_t<Int>;
			auto absU = [](Int x) -> Unsigned {
				// Convert to unsigned magnitude without UB on INT_MIN.
				Unsigned u = static_cast<Unsigned>(x);
				if (x < 0) {
					u = Unsigned(0) - u;
				}
				return u;
			};

			Unsigned uA = absU(div);
			Unsigned uB = absU(b);

			if (uA != 0 && uB > Unsigned(std::numeric_limits<Int>::max()) / uA) {
				return std::nullopt;
			}

			Int lcmVal = div * b;
			if (lcmVal < 0) {
				lcmVal = -lcmVal;
			}

			return lcmVal;
		}

		/**
		 * Computes the sine of an angle, explicitly handling floating-point inaccuracies near multiples of PI and PI/2.
		 * 
		 * \param x			The angle in radians.
		 * \return			Returns the sine of the angle, snapping to exactly 0.0 or +/-1.0 at cardinal points.
		 **/
		static inline double		sinExact(double x) {
			if (x == 0.0) {
				return 0.0;
			}

			double halfRatio = x / (std::numbers::pi * 0.5);
			double nearestHalf = std::round(halfRatio);

			if (std::fabs(halfRatio - nearestHalf) <= 2.22044604925031308e-16) {	// Tuned on Windows.  TODO: Verify on other platforms.
				int64_t n = static_cast<int64_t>(nearestHalf);
				if (n % 2 == 0) {
					return 0.0;
				}
				else {
					// Covers both positive and negative odd multiples.
					return ((n % 4) == 1 || (n % 4) == -3) ? 1.0 : -1.0;
				}
			}

			return std::sin(x);
		}

		/**
		 * Computes the cosine of an angle, explicitly handling floating-point inaccuracies near multiples of PI and PI/2.
		 * 
		 * \param x			The angle in radians.
		 * \return			Returns the cosine of the angle, snapping to exactly 0.0 or +/-1.0 at cardinal points.
		 **/
		static inline double		cosExact(double x) {
			if (x == 0.0) {
				return 1.0;
			}

			double halfRatio = x / (std::numbers::pi * 0.5);
			double nearestHalf = std::round(halfRatio);

			if (std::fabs(halfRatio - nearestHalf) <= 1.11022302462515654e-16) {	// Tuned on Windows.  TODO: Verify on other platforms.
				int64_t n = static_cast<int64_t>(nearestHalf);
				if ((n & 1) != 0) {
					return 0.0;
				}
				else {
					// Covers both positive and negative even multiples.
					return ((n % 4) == 0) ? 1.0 : -1.0;
				}
			}

			return std::cos(x);
		}


		// ===============================
		// Bit Manipulation & Utilities
		// ===============================
		/**
		 * Counts the number of set (non-zero) bytes in a 64-bit unsigned value.
		 * 
		 * \param value		The value to analyze.
		 * \return			The number of non-zero bytes.
		 **/
		static inline uint32_t		countSetBytes(uint64_t value) {
			uint32_t ret = 0;
			while (value) {
				++ret;
				value >>= 8;
			}
			return ret;
		}

		/**
		 * Counts the number of bits set to 1 in a 64-bit unsigned value.
		 * 
		 * \param value		The value to analyze.
		 * \return			The total count of bits set to 1.
		 **/
		static inline uint32_t		countSetBits(uint64_t value) {
			uint32_t cnt = 0;
			while (value) {
				value &= (value - 1);
				cnt++;
			}
			return cnt;
		}

		/**
		 * Finds the index of the highest set bit in a 64-bit unsigned value.
		 * 
		 * \param value		The value to examine.
		 * \return			The zero-based index of the most significant bit set to 1. Returns 0 if no bits are set.
		 **/
		static inline uint32_t		highestSetBit(uint64_t value) {
			if (!value) {
				return 0;
			}

#if defined( _MSC_VER )
			unsigned long pos = 0;
	#if defined( _M_X64 ) || defined( _M_AMD64 )
			_BitScanReverse64(&pos, value);
	#else
			// 32-bit MSVC fallback.
			if (_BitScanReverse(&pos, static_cast<unsigned long>(value >> 32ULL))) {
				return static_cast<uint32_t>(pos + 32UL);
			}
			_BitScanReverse(&pos, static_cast<unsigned long>(value));
	#endif
			return static_cast<uint32_t>(pos);
#else
			// Clang/GCC (including Xcode): msb index = 63 - clz(value).
			return static_cast<uint32_t>(63U - static_cast<uint32_t>(__builtin_clzll(value)));
#endif
		}

		/**
		 * Takes a bit mask and returns a shift and divisor.
		 * 
		 * \param mask		The bit mask.
		 * \param maxVal	Holds the returned maximum value for the given mask.
		 * \return			Returns the mask shift.
		 **/
		static inline size_t		bitMaskToShift(uint64_t mask, double& maxVal) {
			if (!mask) {
				maxVal = 0.0;
				return 0;
			}
			size_t shift = 0;
			while (!(mask & 1)) {
				mask >>= 1;
				++shift;
			}
			maxVal = static_cast<double>(mask);
			return shift;
		}

		/**
		 * Is the given value a power of 2?
		 *
		 * \param val		The value.
		 * \return			Returns true if the given value is a power of 2.
		 **/
		static inline bool			isPo2(uint32_t val) {
			if (!val) { return false; }
			return (val & (val - 1U)) == 0;
		}

		/**
		 * Reverses the bits in an 8-bit value.
		 * 
		 * \param val		The value to bit-reverse.
		 * \return			Returns the bit-reversed result.
		 **/
		static inline uint8_t		reverseBits8(uint8_t val) {
			val = (val & 0xF0) >> 4 | (val & 0x0F) << 4;
			val = (val & 0xCC) >> 2 | (val & 0x33) << 2;
			val = (val & 0xAA) >> 1 | (val & 0x55) << 1;
			return val;
		}

		/**
		 * Reverses the bits in an 16-bit value.
		 * 
		 * \param val		The value to bit-reverse.
		 * \return			Returns the bit-reversed result.
		 **/
		static inline uint16_t		reverseBits16(uint16_t val) {
			val = ((val >> 1) & 0x5555) | ((val & 0x5555) << 1);
			val = ((val >> 2) & 0x3333) | ((val & 0x3333) << 2);
			val = ((val >> 4) & 0x0F0F) | ((val & 0x0F0F) << 4);
			val = ((val >> 8) & 0x00FF) | ((val & 0x00FF) << 8);
			return val;
		}

		/**
		 * Reverses the bits in an 32-bit value.
		 * 
		 * \param val		The value to bit-reverse.
		 * \return			Returns the bit-reversed result.
		 **/
		static inline uint32_t		reverseBits32(uint32_t val) {
			val = ((val >> 1) & 0x55555555U) | ((val & 0x55555555U) << 1);
			val = ((val >> 2) & 0x33333333U) | ((val & 0x33333333U) << 2);
			val = ((val >> 4) & 0x0F0F0F0FU) | ((val & 0x0F0F0F0FU) << 4);
			val = ((val >> 8) & 0x00FF00FFU) | ((val & 0x00FF00FFU) << 8);
			val = ((val >> 16) & 0xFFFFU) | ((val & 0xFFFFU) << 16);
			return val;
		}

		/**
		 * Reverses the bits in an 64-bit value.
		 * 
		 * \param val		The value to bit-reverse.
		 * \return			Returns the bit-reversed result.
		 **/
		static inline uint64_t		reverseBits64(uint64_t val) {
			val = ((val >> 1) & 0x5555555555555555ULL) | ((val & 0x5555555555555555ULL) << 1);
			val = ((val >> 2) & 0x3333333333333333ULL) | ((val & 0x3333333333333333ULL) << 2);
			val = ((val >> 4) & 0x0F0F0F0F0F0F0F0FULL) | ((val & 0x0F0F0F0F0F0F0F0FULL) << 4);
			val = ((val >> 8) & 0x00FF00FF00FF00FFULL) | ((val & 0x00FF00FF00FF00FFULL) << 8);
			val = ((val >> 16) & 0x0000FFFF0000FFFFULL) | ((val & 0x0000FFFF0000FFFFULL) << 16);
			val = ((val >> 32) & 0x00000000FFFFFFFFULL) | ((val & 0x00000000FFFFFFFFULL) << 32);
			return val;
		}


		// ===============================
		// Byte Swapping Utilities
		// ===============================
		/**
		 * Swaps the byte order of the given unsigned integral value.
		 * Provides a cross-platform fallback for std::byteswap (C++23) in C++20.
		 * 
		 * \param value		The unsigned integral value whose bytes are to be swapped.
		 * \return			Returns the byte-swapped result.
		 **/
		template <typename Type>
		requires std::is_integral_v<Type> && std::is_unsigned_v<Type>
		static constexpr inline Type
									byteswap(Type value) noexcept {
			if constexpr (sizeof(Type) == 1) {
				return value;
			} 
			else if constexpr (sizeof(Type) == 2) {
#if defined(_MSC_VER) && !defined(__clang__)
				return _byteswap_ushort(value);
#elif defined(__GNUC__) || defined(__clang__)
				return __builtin_bswap16(value);
#else
				return static_cast<Type>((value >> 8) | (value << 8));
#endif
			} 
			else if constexpr (sizeof(Type) == 4) {
#if defined(_MSC_VER) && !defined(__clang__)
				return _byteswap_ulong(value);
#elif defined(__GNUC__) || defined(__clang__)
				return __builtin_bswap32(value);
#else
				return static_cast<Type>(
					((value & 0xFF000000u) >> 24) |
					((value & 0x00FF0000u) >>  8) |
					((value & 0x0000FF00u) <<  8) |
					((value & 0x000000FFu) << 24)
				);
#endif
			} 
			else if constexpr (sizeof(Type) == 8) {
#if defined(_MSC_VER) && !defined(__clang__)
				return _byteswap_uint64(value);
#elif defined(__GNUC__) || defined(__clang__)
				return __builtin_bswap64(value);
#else
				return static_cast<Type>(
					((value & 0xFF00000000000000ull) >> 56) |
					((value & 0x00FF000000000000ull) >> 40) |
					((value & 0x0000FF0000000000ull) >> 24) |
					((value & 0x000000FF00000000ull) >>  8) |
					((value & 0x00000000FF000000ull) <<  8) |
					((value & 0x0000000000FF0000ull) << 24) |
					((value & 0x000000000000FF00ull) << 40) |
					((value & 0x00000000000000FFull) << 56)
				);
#endif
			} 
			else {
				return value;
			}
		}


		// ===============================
		// Color Space Conversions
		// ===============================
		/**
		 * Converts a single double value from sRGB space to linear space. Performs a conversion according to the standard.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the converted value.
		 **/
		static inline double		sRgbToLinear(double val) {
			if (val < -0.04045) {
				return -std::pow((-val + 0.055) / 1.055, 2.4);
			}
			return val <= 0.04045 ?
				val / 12.92 :
				std::pow((val + 0.055) / 1.055, 2.4);
		}

		/**
		 * Converts a single double value from linear space to sRGB space. Performs a conversion according to the standard.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the converted value.
		 **/
		static inline double		linearToSRgb(double val) {
			if (val < -0.0031308) {
				return -1.055 * std::pow(-val, 1.0 / 2.4) + 0.055;
			}
			return val <= 0.0031308 ?
				val * 12.92 :
				1.055 * std::pow(val, 1.0 / 2.4) - 0.055;
		}

		/**
		 * Converts a single double value from sRGB space to linear space. Performs a precise conversion without a gap.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the converted value.
		 **/
		static inline double		sRgbToLinearPrecise(double val) {
			constexpr double alpha = 0.055000000000000000277555756156289135105907917022705078125;
			constexpr double beta  = 1.0549999999999999378275106209912337362766265869140625;
			constexpr double theta = 12.92321018078785499483274179510772228240966796875;
			constexpr double cut   = 0.039285714285714291860163172032116563059389591217041015625;
			
			if (val < -cut) {
				return -std::pow((-val + alpha) / beta, 2.4);
			}
			return val <= cut ?
				val / theta :
				std::pow((val + alpha) / beta, 2.4);
		}

		/**
		 * Converts a single double value from linear space to sRGB space. Performs a precise conversion without a gap.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the converted value.
		 **/
		static inline double		linearToSRgbPrecise(double val) {
			constexpr double alpha = 0.055000000000000000277555756156289135105907917022705078125;
			constexpr double beta  = 1.0549999999999999378275106209912337362766265869140625;
			constexpr double theta = 12.92321018078785499483274179510772228240966796875;
			constexpr double cut   = 0.003039934639778431833823102437008856213651597499847412109375;
			
			if (val < -cut) {
				return -beta * std::pow(-val, 1.0 / 2.4) + alpha;
			}
			return val <= cut ?
				val * theta :
				beta * std::pow(val, 1.0 / 2.4) - alpha;
		}

		/**
		 * Converts from macOS “Color LCD” (Display P3-class) to linear.
		 * Uses the sRGB transfer function (sRGB TRC).
		 *
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		colorLcdToLinear(double val) {
			if (val < -0.04045) {
				return -std::pow((-val + 0.055) / 1.055, 2.4);
			}
			return val <= 0.04045 ?
				val / 12.92 :
				std::pow((val + 0.055) / 1.055, 2.4);
		}

		/**
		 * Converts from linear to macOS “Color LCD” (Display P3-class).
		 * Uses the sRGB transfer function (sRGB TRC).
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to “Color LCD” space.
		 **/
		static inline double		linearToColorLcd(double val) {
			if (val < -(0.04045 / 12.92)) {
				return -1.055 * std::pow(-val, 1.0 / 2.4) + 0.055;
			}
			return val <= (0.04045 / 12.92) ?
				val * 12.92 :
				1.055 * std::pow(val, 1.0 / 2.4) - 0.055;
		}

		/**
		 * Converts from SMPTE 170M-2004 to linear. Performs a conversion according to the standard.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		smpte170MToLinear(double val) {
			if (val < -0.081) {
				return -std::pow((-val + 0.099) / 1.099, 1.0 / 0.45);
			}
			return val <= 0.081 ?
				val / 4.5 :
				std::pow((val + 0.099) / 1.099, 1.0 / 0.45);
		}

		/**
		 * Converts from linear to SMPTE 170M-2004. Performs a conversion according to the standard.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to SMPTE 170M-2004 space.
		 **/
		static inline double		linearToSmpte170M(double val) {
			if (val < -0.018) {
				return -1.099 * std::pow(-val, 0.45) + 0.099;
			}
			return val <= 0.018 ?
				val * 4.5 :
				1.099 * std::pow(val, 0.45) - 0.099;
		}

		/**
		 * Converts from SMPTE 170M-2004 to linear. Performs a precise conversion without a gap.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		smpte170MToLinearPrecise(double val) {
			if (val < -0.08124285829863515939752716121802222914993762969970703125) {
				return -std::pow((-val + 0.09929682680944297568093048766968422569334506988525390625) / 1.09929682680944296180314267985522747039794921875, 1.0 / 0.45);
			}
			return val <= 0.08124285829863515939752716121802222914993762969970703125 ?
				val / 4.5 :
				std::pow((val + 0.09929682680944297568093048766968422569334506988525390625) / 1.09929682680944296180314267985522747039794921875, 1.0 / 0.45);
		}

		/**
		 * Converts from linear to SMPTE 170M-2004. Performs a precise conversion without a gap.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to SMPTE 170M-2004 space.
		 **/
		static inline double		linearToSmpte170MPrecise(double val) {
			if (val < -0.0180539685108078128139563744980478077195584774017333984375) {
				return -1.09929682680944296180314267985522747039794921875 * std::pow(-val, 0.45) + 0.09929682680944297568093048766968422569334506988525390625;
			}
			return val <= 0.0180539685108078128139563744980478077195584774017333984375 ?
				val * 4.5 :
				1.09929682680944296180314267985522747039794921875 * std::pow(val, 0.45) - 0.09929682680944297568093048766968422569334506988525390625;
		}

		/**
		 * Converts from DCI-P3 to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		dciP3ToLinear(double val) {
			if (val < 0.0) {
				return -std::pow(-val, 2.6);
			}
			return std::pow(val, 2.6);
		}

		/**
		 * Converts from linear to DCI-P3.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to DCI-P3 space.
		 **/
		static inline double		linearToDciP3(double val) {
			if (val < 0.0) {
				return -std::pow(-val, 1.0 / 2.6);
			}
			return std::pow(val, 1.0 / 2.6);
		}

		/**
		 * Converts from macOS “Generic RGB Profile” to linear.
		 * The Generic RGB profile that ships with macOS uses a simple power-law TRC with gamma 1.8 (no toe).
		 *
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		genericRgbToLinear(double val) {
			if (val < 0.0) {
				return -std::pow(-val, 1.8);
			}
			return std::pow(val, 1.8);
		}

		/**
		 * Converts from linear to macOS “Generic RGB Profile”.
		 * The Generic RGB profile that ships with macOS uses a simple power-law TRC with gamma 1.8 (no toe).
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to Generic RGB space.
		 **/
		static inline double		linearToGenericRgb(double val) {
			constexpr double invGamma = 1.0 / 1.8;

			if (val < 0.0) {
				return -std::pow(-val, invGamma);
			}
			return std::pow(val, invGamma);
		}

		/**
		 * Converts from linear to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		passThrough(double val) {
			return val;
		}

		/**
		 * Converts from 2.2 to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		pow2_2ToLinear(double val) {
			if (val < 0.0) {
				return -std::pow(-val, 2.2);
			}
			return std::pow(val, 2.2);
		}

		/**
		 * Converts from linear to 2.2.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to 2.2 space.
		 **/
		static inline double		linearToPow2_2(double val) {
			if (val < 0.0) {
				return -std::pow(-val, 1.0 / 2.2);
			}
			return std::pow(val, 1.0 / 2.2);
		}

		/**
		 * Converts from 2.8 to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		pow2_8ToLinear(double val) {
			if (val < 0.0) {
				return -std::pow(-val, 2.8);
			}
			return std::pow(val, 2.8);
		}

		/**
		 * Converts from linear to 2.8.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to 2.8 space.
		 **/
		static inline double		linearToPow2_8(double val) {
			if (val < 0.0) {
				return -std::pow(-val, 1.0 / 2.8);
			}
			return std::pow(val, 1.0 / 2.8);
		}

		/**
		 * Converts from Adobe RGB (1998) to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		adobeRgbToLinear(double val) {
			if (val < 0.0) {
				return -std::pow(-val, 2.19921875);
			}
			return std::pow(val, 2.19921875);
		}

		/**
		 * Converts from linear to Adobe RGB (1998).
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to Adobe RGB space.
		 **/
		static inline double		linearToAdobeRgb(double val) {
			if (val < 0.0) {
				return -std::pow(-val, 1.0 / 2.19921875);
			}
			return std::pow(val, 1.0 / 2.19921875);
		}

		/**
		 * Converts from SMPTE 240M to linear. Performs a conversion according to the standard.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		smpte240MToLinear(double val) {
			if (val <= -0.0913) {
				return -std::pow((-val + 0.1115) / 1.1115, 1.0 / 0.45);
			}
			return val < 0.0913 ?
				val / 4.0 :
				std::pow((val + 0.1115) / 1.1115, 1.0 / 0.45);
		}

		/**
		 * Converts from linear to SMPTE 240M. Performs a conversion according to the standard.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to SMPTE 240M space.
		 **/
		static inline double		linearToSmpte240M(double val) {
			if (val <= -0.0228) {
				return -1.1115 * std::pow(-val, 0.45) + 0.1115;
			}
			return val < 0.0228 ?
				val * 4.0 :
				1.1115 * std::pow(val, 0.45) - 0.1115;
		}

		/**
		 * Converts from SMPTE 240M to linear. Performs a precise conversion without a gap.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		smpte240MToLinearPrecise(double val) {
			if (val < -0.0912863421177801115380390228892792947590351104736328125) {
				return -std::pow((-val + 0.1115721959217312597711924126997473649680614471435546875) / 1.1115721959217312875267680283286608755588531494140625, 1.0 / 0.45);
			}
			return val <= 0.0912863421177801115380390228892792947590351104736328125 ?
				val / 4.0 :
				std::pow((val + 0.1115721959217312597711924126997473649680614471435546875) / 1.1115721959217312875267680283286608755588531494140625, 1.0 / 0.45);
		}

		/**
		 * Converts from linear to SMPTE 240M. Performs a precise conversion without a gap.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to SMPTE 240M space.
		 **/
		static inline double		linearToSmpte240MPrecise(double val) {
			if (val < -0.022821585529445027884509755722319823689758777618408203125) {
				return -1.1115721959217312875267680283286608755588531494140625 * std::pow(-val, 0.45) + 0.1115721959217312597711924126997473649680614471435546875;
			}
			return val <= 0.022821585529445027884509755722319823689758777618408203125 ?
				val * 4.0 :
				1.1115721959217312875267680283286608755588531494140625 * std::pow(val, 0.45) - 0.1115721959217312597711924126997473649680614471435546875;
		}

		/**
		 * Converts from ACEScc to linear. Performs a conversion according to the standard.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		acesCcToLinear(double val) {
			constexpr double b = 9.72;
			constexpr double c = 17.52;
			constexpr double thresh = (b - 15.0) / c;
			constexpr double upperLimit = (15.9992953870234106972247900557704269886016845703125 + b) / c;

			if (val <= thresh) {
				return (std::pow(2.0, val * c - b) - 0.0000152587890625) * 2.0;
			}
			else if (val < upperLimit) {
				return std::pow(2.0, val * c - b);
			}
			else {
				return 65504.0;
			}
		}

		/**
		 * Converts from linear to ACEScc. Performs a conversion according to the standard.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to ACEScc space.
		 **/
		static inline double		linearToAcesCc(double val) {
			constexpr double b = 9.72;
			constexpr double c = 17.52;

			if (val <= 0.0) {
				return (-16.0 + b) / c;
			}
			else if (val < 0.000030517578125) {
				return (std::log2(0.0000152587890625 + val * 0.5) + b) / c;
			}
			else {
				return (std::log2(val) + b) / c;
			}
		}

		/**
		 * Converts from ACEScg (AP1) to linear.
		 * ACEScg is photometrically linear, so this is an identity transform.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		acesCgToLinear(double val) {
			return val;
		}

		/**
		 * Converts from linear to ACEScg (AP1).
		 * ACEScg is photometrically linear, so this is an identity transform.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to ACEScg space.
		 **/
		static inline double		linearToAcesCg(double val) {
			return val;
		}

		/**
		 * Converts from ROMM RGB to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		rommRgbToLinear(double val) {
			if (val <= 0.0) {
				return 0.0;
			}
			if (val <= 0.03125) {
				return val / 16.0;
			}
			if (val < 1.0) {
				return std::pow(val, 1.8);
			}
			return 1.0;
		}

		/**
		 * Converts from linear to ROMM RGB.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to ROMM RGB space.
		 **/
		static inline double		linearToRommRgb(double val) {
			if (val <= 0.0) {
				return 0.0;
			}
			if (val <= 0.001953125) {
				return val * 16.0;
			}
			if (val < 1.0) {
				return std::pow(val, 1.0 / 1.8);
			}
			return 1.0;
		}

		/**
		 * Converts from RIMM RGB to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		rimmRgbToLinear(double val) {
			constexpr double vClip = 1.4023868927346205826012237594113685190677642822265625;
			val *= vClip;
			if (val < -0.08124285829863515939752716121802222914993762969970703125) {
				return -std::pow((-val + 0.09929682680944297568093048766968422569334506988525390625) / 1.09929682680944296180314267985522747039794921875, 1.0 / 0.45);
			}
			return val <= 0.08124285829863515939752716121802222914993762969970703125 ?
				val / 4.5 :
				std::pow((val + 0.09929682680944297568093048766968422569334506988525390625) / 1.09929682680944296180314267985522747039794921875, 1.0 / 0.45);
		}

		/**
		 * Converts from linear to RIMM RGB.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to RIMM RGB space.
		 **/
		static inline double		linearToRimmRgb(double val) {
			constexpr double vClip = 1.4023868927346205826012237594113685190677642822265625;
			if (val < -0.0180539685108078128139563744980478077195584774017333984375) {
				return (-1.09929682680944296180314267985522747039794921875 * std::pow(-val, 0.45) + 0.09929682680944297568093048766968422569334506988525390625) * vClip;
			}
			return (val <= 0.0180539685108078128139563744980478077195584774017333984375 ?
				val * 4.5 :
				1.09929682680944296180314267985522747039794921875 * std::pow(val, 0.45) - 0.09929682680944297568093048766968422569334506988525390625) / vClip;
		}

		/**
		 * Converts from ERIMM RGB to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		erimmRgbToLinear(double val) {
			constexpr double logEclip = 2.5;
			constexpr double logEmin = -3.0;
			constexpr double logEt = -2.56570551809674807230976512073539197444915771484375;
			constexpr double et = 0.0027182818284590451983484538089896886958740651607513427734375;

			constexpr double logEclipMinusLogEmin = logEclip - logEmin;
			constexpr double logEtMinusLogEmin = logEt - logEmin;

			if (val <= 0.0) {
				return 0.0;
			}
			if (val <= (logEtMinusLogEmin / logEclipMinusLogEmin)) {
				return (logEclipMinusLogEmin / logEtMinusLogEmin) * (val * et);
			}
			if (val < 1.0) {
				return std::pow(10.0, val * logEclipMinusLogEmin + logEmin);
			}
			return 1.0;
		}

		/**
		 * Converts from linear to ERIMM RGB.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to ERIMM RGB space.
		 **/
		static inline double		linearToErimmRgb(double val) {
			constexpr double logEclip = 2.5;
			constexpr double eclip = 316.22776601683796116049052216112613677978515625;
			constexpr double logEmin = -3.0;
			constexpr double et = 0.0027182818284590451983484538089896886958740651607513427734375;
			constexpr double logEt = -2.56570551809674807230976512073539197444915771484375;

			constexpr double logEclipMinusLogEmin = logEclip - logEmin;

			if (val <= 0.0) {
				return 0.0;
			}
			if (val <= et) {
				return ((logEt - logEmin) / logEclipMinusLogEmin) * (val / et);
			}
			if (val <= eclip && val < 1.0) {
				return (std::log10(val) - logEmin) / logEclipMinusLogEmin;
			}
			return 1.0;
		}

		/**
		 * Converts from S-Log to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		sLogToLinear(double val) {
			return std::pow(10.0, ((val - 0.616596 - 0.03) / 0.432699)) - 0.037584;
		}

		/**
		 * Converts from linear to S-Log.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to S-Log space.
		 **/
		static inline double		linearToSLog(double val) {
			return (0.432699 * std::log10(val + 0.037584) + 0.616596) + 0.03;
		}

		/**
		 * Converts from S-Log2 to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		sLog2ToLinear(double val) {
			return (std::pow(10.0, (((val * 1023.0 / 4.0 - 16.0) / 219.0) - 0.616596 - 0.03) / 0.432699) - 0.037584) * 0.9;
		}

		/**
		 * Converts from linear to S-Log2.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to S-Log2 space.
		 **/
		static inline double		linearToSLog2(double val) {
			return (4.0 * (16.0 + 219.0 * (0.616596 + 0.03 + 0.432699 *
				std::log10(0.037584 + val / 0.9)))) / 1023.0;
		}

		/**
		 * Converts from S-Log3 to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		sLog3ToLinear(double val) {
			if (val >= 171.2102946929 / 1023.0) {
				return std::pow(10.0, ((val * 1023.0 - 420.0) / 261.5)) * (0.18 + 0.01) - 0.01;
			}
			return (val * 1023.0 - 95.0) * 0.01125000 / (171.2102946929 - 95.0);
		}

		/**
		 * Converts from linear to S-Log3.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to S-Log3 space.
		 **/
		static inline double		linearToSLog3(double val) {
			if (val >= 0.01125000) {
				return (420.0 + std::log10((val + 0.01) / (0.18 + 0.01)) * 261.5) / 1023.0;
			}
			return (val * (171.2102946929 - 95.0) / 0.01125000 + 95.0) / 1023.0;
		}

		/**
		 * Converts from Protune to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		protuneToLinear(double val) {
			return (std::pow(113.0, val) - 1.0) / 112.0;
		}

		/**
		 * Converts from linear to Protune.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to Protune space.
		 **/
		static inline double		linearToProtune(double val) {
			constexpr double d = 4.727387818712340816773576079867780208587646484375;
			return std::log(val * 112.0 + 1.0) / d;
		}

		/**
		 * Converts from Canon Log to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		canonLogToLinear(double val) {
			return (val < 0.0730597) ?
				-(std::pow(10.0, (0.0730597 - val) / 0.529136) - 1.0) / 10.1596 :
				(std::pow(10.0, (val - 0.0730597) / 0.529136) - 1.0) / 10.1596;
		}

		/**
		 * Converts from linear to Canon Log.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to Canon Log space.
		 **/
		static inline double		linearToCanonLog(double val) {
			constexpr double threshold = 0.0;

			return (val < threshold) ?
				-(0.529136 * (std::log10(-val * 10.1596 + 1.0)) - 0.0730597) :
				0.529136 * std::log10(10.1596 * val + 1.0) + 0.0730597;
		}

		/**
		 * Converts from Canon Log 2 to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		canonLog2ToLinear(double val) {
			return (val < 0.035388128) ?
				-(std::pow(10.0, (0.035388128 - val) / 0.281863093) - 1.0) / 87.09937546 :
				(std::pow(10.0, (val - 0.035388128) / 0.281863093) - 1.0) / 87.09937546;
		}

		/**
		 * Converts from linear to Canon Log 2.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to Canon Log 2 space.
		 **/
		static inline double		linearToCanonLog2(double val) {
			constexpr double threshold = 0.0;

			return (val < threshold) ?
				-(0.281863093 * (std::log10(-val * 87.09937546 + 1.0)) - 0.035388128) :
				0.281863093 * std::log10(val * 87.09937546 + 1.0) + 0.035388128;
		}

		/**
		 * Converts from Canon Log 3 to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		canonLog3ToLinear(double val) {
			if (val < 0.04076162) {
				return -(std::pow(10.0, (0.069886632 - val) / 0.42889912) - 1.0) / 14.98325;
			}
			else if (val <= 0.105357102) {
				return (val - 0.073059361) / 2.3069815;
			}
			return (std::pow(10.0, (val - 0.069886632) / 0.42889912) - 1.0) / 14.98325;
		}

		/**
		 * Converts from linear to Canon Log 3.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to Canon Log 3 space.
		 **/
		static inline double		linearToCanonLog3(double val) {
			constexpr double thresh1 = -0.014;
			constexpr double thresh2 = 0.014;

			if (val < thresh1) {
				return -(0.42889912 * (std::log10(-val * 14.98325 + 1.0)) - 0.069886632);
			}
			else if (val <= thresh2) {
				return 2.3069815 * val + 0.073059361;
			}
			return 0.42889912 * std::log10(val * 14.98325 + 1.0) + 0.069886632;
		}

		/**
		 * Converts from Viper to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		viperToLinear(double val) {
			return std::pow(10.0, (1023.0 * val - 1023.0) / 500.0);
		}

		/**
		 * Converts from linear to Viper.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to Viper space.
		 **/
		static inline double		linearToViper(double val) {
			return (1023.0 + 500.0 * std::log10(val)) / 1023.0;
		}

		/**
		 * Converts from ARIB STD-B67 to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		aribStdB67ToLinear(double val) {
			constexpr double a = 0.17883277;
			constexpr double b = 0.28466892;
			constexpr double c = 0.55991073;
			constexpr double r = 0.5;

			return (val <= (1.0 * r)) ?
				std::pow(val / r, 2.0) :
				std::exp((val - c) / a) + b;
		}

		/**
		 * Converts from linear to ARIB STD-B67.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to ARIB STD-B67 space.
		 **/
		static inline double		linearToAribStdB67(double val) {
			constexpr double a = 0.17883277;
			constexpr double b = 0.28466892;
			constexpr double c = 0.55991073;
			constexpr double r = 0.5;

			return (val <= 1.0) ?
				r * std::sqrt(val) :
				a * std::log(val - b) + c;
		}

		/**
		 * Converts from Panalog to linear.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		panalogToLinear(double val) {
			constexpr double blackOffset = 0.04077184461038073359784306148867472074925899505615234375;
			return (std::pow(10.0, (1023.0 * val - 681.0) / 444.0) - blackOffset) / (1.0 - blackOffset);
		}

		/**
		 * Converts from linear to Panalog.
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to Panalog space.
		 **/
		static inline double		linearToPanalog(double val) {
			constexpr double blackOffset = 0.04077184461038073359784306148867472074925899505615234375;
			return (681.0 + 444.0 * std::log10(val * (1.0 - blackOffset) + blackOffset)) / 1023.0;
		}

		/**
		 * A proper CRT curve based on measurements with WHITE and BRIGHTNESS controls.
		 * 
		 * \param val		The value to convert.
		 * \param lw		Screen luminance for white, reference setting is LW = 100 cd/m2.
		 * \param b			Variable for black level lift (legacy "brightness" control).
		 *	The value of b is set so that the calculated luminance can be the same as the
		 *	measurement data at input signal level 0.0183 (= (80-64)/876).
		 *	The value of b changes depending on "brightness" control.
		 * \return			Returns the corresponding value from a decent CRT curve back to linear.
		 **/
		static inline double		crtProperToLinear(double val, double lw = 1.0, double b = 0.0181) {
			constexpr double alpha1 = 2.6;
			constexpr double alpha2 = 3.0;
			constexpr double vc = 0.35;
			double k = lw / std::pow(1.0 + b, alpha1);

			if (val < vc) {
				return k * std::pow(vc + b, (alpha1 - alpha2)) * std::pow(val + b, alpha2);
			}
			return k * std::pow(val + b, alpha1);
		}

		/**
		 * The inverse of crtProperToLinear().
		 * 
		 * \param val		The value to convert.
		 * \param lw		Screen luminance for white, reference setting is LW = 100 cd/m2.
		 * \param b			Variable for black level lift (legacy "brightness" control).
		 *	The value of b is set so that the calculated luminance can be the same as the
		 *	measurement data at input signal level 0.0183 (= (80-64)/876).
		 *	The value of b changes depending on "brightness" control.
		 * \return			Returns the corresponding value along a decent CRT curve.
		 **/
		static inline double		linearToCrtProper(double val, double lw = 1.0, double b = 0.0181) {
			constexpr double alpha1 = 2.6;
			constexpr double alpha2 = 3.0;
			constexpr double vc = 0.35;
			double k = lw / std::pow(1.0 + b, alpha1);

			val /= k;
			if (val < std::pow(vc + b, alpha1)) {
				return std::pow(val / std::pow(vc + b, (alpha1 - alpha2)), 1.0 / alpha2) - b;
			}
			return std::pow(val, 1.0 / alpha1) - b;
		}

		/**
		 * A proper CRT curve based on measurements.
		 * 
		 * \param val		The value to convert.
		 * \return			Returns the color value converted to linear space.
		 **/
		static inline double		crtProper2ToLinear(double val) {
			constexpr double alpha = 0.1115721959217312597711924126997473649680614471435546875;
			constexpr double beta = 1.1115721959217312875267680283286608755588531494140625;
			constexpr double cut = 0.0912863421177801115380390228892792947590351104736328125;
			if (val >= 0.36) {
				return std::pow(val, 2.31);
			}
			double frac = val / 0.36;
			return ((val <= cut ?
				val / 4.0 :
				std::pow((val + alpha) / beta, 1.0 / 0.45))
				* (1.0 - frac))
				+ (frac * std::pow(val, 2.31));
		}

		/**
		 * The inverse of crtProper2ToLinear().
		 *
		 * \param val		The value to convert.
		 * \return			Returns the value converted to SMPTE 240M space.
		 **/
		static inline double		linearToCrtProper2(double val) {
			if (val <= 0.0) {
				return 0.0;
			}
			if (val >= 1.0) {
				return 1.0;
			}

			constexpr double gamma = 2.31;
			constexpr double splitX = 0.36;
			constexpr double splitY = 0.09441886527340710710820559370404225774109363555908203125;	// std::pow( 0.36, 2.31 ).

			if (val >= splitY) {
				return std::pow(val, 1.0 / gamma);						// Easily reversible.
			}

			// The X-to-linear can't be reversed because val is a parameter for both the curves and the blend. Need an iterative approach.
			// This is expensive, but luckily this function isn't actually useful, since you won't be playing on a monitor/screen that has this curve. Only
			// crtProper2ToLinear() is actually useful, as it exactly matches the curve some CRT's applied to their images, which is the part necessary for emulation.
			// If this function is ever used, it must be for building LUT's only.
			double lo = 0.0;
			double hi = splitX;
			
			for (int i = 0; i < 48; ++i) {
				double mid = (lo + hi) * 0.5;
				double y = crtProper2ToLinear(mid);
				if (y < val) {
					lo = mid;
				}
				else {
					hi = mid;
				}
			}

			return (lo + hi) * 0.5;
		}

		/**
		 * Converts XYZ values to chromaticities.
		 * 
		 * \param x			The input X.
		 * \param y			The input Y.
		 * \param z			The input Z.
		 * \param chromaX	The output chromaticity X.
		 * \param chromaY	The output chromaticity Y.
		 **/
		static inline void			xyzToChromaticity(double x, double y, double z, double& chromaX, double& chromaY) {
			double xRatio = x / y;
			constexpr double yRatio = 1.0;
			double zRatio = z / y;

			chromaX = xRatio / (xRatio + yRatio + zRatio);
			chromaY = yRatio / (xRatio + yRatio + zRatio);
		}

		/**
		 * Converts chromaticities to XYZ values.
		 * 
		 * \param chromaX		The input chromaticity X.
		 * \param chromaY		The input chromaticity Y.
		 * \param y0			The input XYZ Y value.
		 * \param x0			The output XYZ X value.
		 * \param z0			The output XYZ Z value.
		 **/
		static inline void			chromaticityToXyz(double chromaX, double chromaY, double y0, double& x0, double& z0) {
			x0 = chromaX * (y0 / chromaY);
			z0 = (1.0 - chromaX - chromaY) * (y0 / chromaY);
		}


		// ===============================
		// Numerical Integration
		// ===============================
		/**
		 * Computes the composite Simpson integral over a subrange of uniformly spaced samples.
		 * 
		 * Applies Simpson's 1/3 rule on the range [start, end) of y, assuming uniform spacing dx.
		 * The number of samples in the subrange must be odd and at least 3 for Simpson's rule to apply.
		 * Ranges with fewer than 3 samples contribute 0 to the integral.
		 * 
		 * \tparam Type		The value type stored in the vector (defaults to double).
		 * \param y			The sample values y[i].
		 * \param start		The starting index (inclusive).
		 * \param end		The ending index (exclusive).
		 * \param dx		The uniform spacing between samples.
		 * \return			Returns the Simpson integral over the given subrange.
		 **/
		template <typename Type = double>
		static inline Type			simpsonUniformRange(const std::vector<Type>& y, size_t start, size_t end, Type dx) {
			const size_t count = end - start;
			if (count < static_cast<size_t>(3)) {
				return Type(0);
			}

			Type sum = y[start] + y[end - 1];

			// Odd-indexed terms (4 * y_i).
			for (size_t i = start + 1; i + 1 < end; i += 2) {
				sum += Type(4) * y[i];
			}

			// Even-indexed interior terms (2 * y_i).
			for (size_t i = start + 2; i + 1 < end; i += 2) {
				sum += Type(2) * y[i];
			}

			return dx * sum / Type(3);
		}

		/**
		 * Computes the composite Simpson integral over a strided subrange of uniformly spaced samples.
		 * 
		 * Applies Simpson's 1/3 rule on a strided sequence of samples in y. The logical indices
		 * along the integration line are [0..count-1], mapped to y[start + i * stride].
		 * The number of samples must be odd and at least 3 for Simpson's rule to apply.
		 * 
		 * \tparam Type		The value type stored in the vector (defaults to double).
		 * \param y			The sample values buffer.
		 * \param start		The starting index into y for the first sample in the line.
		 * \param stride	The stride (in elements) between successive samples.
		 * \param count		The number of samples along the line.
		 * \param dx		The uniform spacing between samples.
		 * \return			Returns the Simpson integral over the given strided line.
		 **/
		template <typename Type = double>
		static inline Type			simpsonUniformRangeStrided(const std::vector<Type>& y, size_t start, size_t stride, size_t count, Type dx) {
			if (count < static_cast<size_t>(3)) {
				return Type(0);
			}

			const size_t lastIndex = start + (count - 1) * stride;
			if (lastIndex >= y.size()) {
				throw std::out_of_range("");
			}

			Type sum = y[start] + y[lastIndex];

			// Odd-indexed terms (4 * y_i).
			for (size_t i = 1; i + 1 < count; i += 2) {
				const size_t idx = start + i * stride;
				sum += Type(4) * y[idx];
			}

			// Even-indexed interior terms (2 * y_i).
			for (size_t i = 2; i + 1 < count; i += 2) {
				const size_t idx = start + i * stride;
				sum += Type(2) * y[idx];
			}

			return dx * sum / Type(3);
		}

		/**
		 * Computes the Simpson integral over 1D data with uniform spacing.
		 * 
		 * This matches scipy.integrate.simpson( y, dx=dx ) for 1D input, using the default
		 * even='avg' behavior when there are an even number of samples.
		 * 
		 * \tparam Type		The value type stored in the vector (defaults to double).
		 * \param y			The sample values y[i].
		 * \param dx		The uniform spacing between samples.
		 * \return			Returns the approximate integral.
		 **/
		template <typename Type = double>
		static inline Type			simpson1D(const std::vector<Type>& y, Type dx = Type(1)) {
			const size_t count = y.size();
			if (count < 2) {
				return Type(0);
			}

			// For exactly two samples, Simpson's rule degenerates to the trapezoidal rule.
			if (count == 2) {
				return dx * Type(0.5) * (y[0] + y[1]);
			}

			// Odd number of samples -> even number of intervals: standard composite Simpson.
			if ((count % 2) == 1) {
				return simpsonUniformRange(y, 0, count, dx);
			}

			// Even number of samples: emulate SciPy's even='avg':
			// 1) Simpson on first N-1 points + trapezoid on last interval.
			// 2) Simpson on last N-1 points  + trapezoid on first interval.
			// Then average the two results.
			const size_t last = count - 1;

			const Type s1 = simpsonUniformRange(y, 0, last, dx);
			const Type trapLast = dx * Type(0.5) * (y[last - 1] + y[last]);
			const Type r1 = s1 + trapLast;

			const Type s2 = simpsonUniformRange(y, 1, count, dx);
			const Type trapFirst = dx * Type(0.5) * (y[0] + y[1]);
			const Type r2 = s2 + trapFirst;

			return Type(0.5) * (r1 + r2);
		}

		/**
		 * Computes the Simpson integral over 1D data with non-uniform spacing. Call within a try/catch block.
		 * 
		 * This matches scipy.integrate.simpson( y, x=x ) for 1D input, using the
		 * standard non-uniform composite Simpson's rule formulation (including the
		 * special handling for the final interval when the number of intervals is odd).
		 * 
		 * \tparam Type		The value type stored in the vectors (defaults to double).
		 * \param y			The sample values y[i].
		 * \param x			The sample locations x[i], same size as y.
		 * \return			Returns the approximate integral.
		 **/
		template <typename Type = double>
		static inline Type			simpson1D(const std::vector<Type>& y, const std::vector<Type>& x) {
			if (x.size() != y.size()) {
				throw std::invalid_argument("");
			}
			if (y.size() < 2) {
				return Type(0);
			}

			const size_t count = x.size();
			const size_t n = count - 1;      // Number of intervals.

			std::vector<Type> hVals;
			hVals.resize(n);

			for (size_t i = 0; i < n; ++i) {
				hVals[i] = x[i+1] - x[i];
			}

			Type result = Type(0);

			// Main Simpson contributions over pairs of adjacent intervals.
			for (size_t i = 1; i < n; i += 2) {
				const Type h0 = hVals[i-1];
				const Type h1 = hVals[i];
				const Type hph = h1 + h0;
				const Type hdh = h1 / h0;
				const Type hmh = h1 * h0;

				result += (hph / Type(6)) *
					((Type(2) - hdh) * y[i-1]
						+ ((hph * hph) / hmh) * y[i]
						+ (Type(2) - Type(1) / hdh) * y[i+1]);
			}

			// If there is an odd number of intervals, adjust the last one as in the standard formula.
			if ((n & 1) != 0) {
				const Type h0 = hVals[n-2];
				const Type h1 = hVals[n-1];

				result += y[n] * (Type(2) * h1 * h1 + Type(3) * h0 * h1) /
					(Type(6) * (h0 + h1));
				result += y[n-1] * (h1 * h1 + Type(3) * h1 * h0) /
					(Type(6) * h0);
				result -= y[n-2] * (h1 * h1 * h1) /
					(Type(6) * h0 * (h0 + h1));
			}

			return result;
		}

		/**
		 * Computes the Simpson integral over a strided 1D line with uniform spacing. Call within a try/catch block.
		 * 
		 * This is analogous to scipy.integrate.simpson( y, dx=dx, axis=axis ) on a
		 * view of the array along 'axis', flattened to a 1D strided line.
		 * 
		 * \tparam Type		The value type stored in the vector (defaults to double).
		 * \param y			The full data buffer.
		 * \param start		The starting index into y for this integration line.
		 * \param count		The number of samples along this line.
		 * \param stride	The stride (in elements) between successive samples.
		 * \param dx		The uniform spacing between samples.
		 * \return			Returns the approximate integral along that line.
		 **/
		template <typename Type = double>
		static inline Type			simpsonStrided(const std::vector<Type>& y, size_t start, size_t count, size_t stride, Type dx = Type(1)) {
			if (count < 2) {
				return Type(0);
			}

			const size_t lastIndex = start + (count - 1) * stride;
			if (lastIndex >= y.size()) {
				throw std::out_of_range("");
			}

			// For exactly two samples, Simpson's rule degenerates to the trapezoidal rule.
			if (count == 2) {
				const Type y0 = y[start];
				const Type y1 = y[start+stride];
				return dx * Type(0.5) * (y0 + y1);
			}

			// Odd number of samples -> even number of intervals: standard composite Simpson.
			if ((count % 2) == 1) {
				return simpsonUniformRangeStrided(y, start, stride, count, dx);
			}

			// Even number of samples: emulate SciPy's even='avg':
			// 1) Simpson on first N-1 points + trapezoid on last interval.
			// 2) Simpson on last N-1 points  + trapezoid on first interval.
			// Then average the two results.
			const size_t last = count - 1;

			const Type s1 = simpsonUniformRangeStrided(y, start, stride, last, dx);
			{
				const size_t idxA = start + (last - 1) * stride;
				const size_t idxB = start + last * stride;
				const Type trapLast = dx * Type(0.5) * (y[idxA] + y[idxB]);
				const Type r1 = s1 + trapLast;

				const Type s2 = simpsonUniformRangeStrided(y, start + stride, stride, last, dx);
				const Type trapFirst = dx * Type(0.5) * (y[start] + y[start+stride]);
				const Type r2 = s2 + trapFirst;

				return Type(0.5) * (r1 + r2);
			}
		}

		/**
		 * Computes the Simpson integral over a strided 1D line with non-uniform spacing. Call within a try/catch block.
		 * 
		 * This is analogous to scipy.integrate.simpson( y, x=x, axis=axis ) where x is
		 * 1D and y is multi-dimensional. The integration is performed along a single
		 * strided line of y, with x giving the coordinates along that axis.
		 * 
		 * \tparam Type		The value type stored in the vectors (defaults to double).
		 * \param y			The full data buffer.
		 * \param start		The starting index into y for this integration line.
		 * \param stride	The stride (in elements) between successive samples.
		 * \param x			The 1D coordinates x[0..N-1] along this axis.
		 * \return			Returns the approximate integral along that line.
		 **/
		template <typename Type = double>
		static inline Type			simpsonStrided(const std::vector<Type>& y, size_t start, size_t stride, const std::vector<Type>& x) {
			const size_t count = x.size();
			if (count < 2) {
				return Type(0);
			}

			const size_t lastIndex = start + (count - 1) * stride;
			if (lastIndex >= y.size()) {
				throw std::out_of_range("");
			}

			const size_t n = count - 1;      // Number of intervals.

			std::vector<Type> hVals;
			hVals.resize(n);

			for (size_t i = 0; i < n; ++i) {
				hVals[i] = x[i+1] - x[i];
			}

			Type result = Type(0);

			// Main Simpson contributions over pairs of adjacent intervals.
			for (size_t i = 1; i < n; i += 2) {
				const Type h0 = hVals[i-1];
				const Type h1 = hVals[i];
				const Type hph = h1 + h0;
				const Type hdh = h1 / h0;
				const Type hmh = h1 * h0;

				const size_t idx0 = start + (i - 1) * stride;
				const size_t idx1 = start + i * stride;
				const size_t idx2 = start + (i + 1) * stride;

				result += (hph / Type(6)) *
					((Type(2) - hdh) * y[idx0] +
					((hph * hph) / hmh) * y[idx1] +
					(Type(2) - Type(1) / hdh) * y[idx2]);
			}

			// If there is an odd number of intervals, adjust the last one as in the standard formula.
			if ((n % 2) == 1) {
				const Type h0 = hVals[n-2];
				const Type h1 = hVals[n-1];

				const size_t idxN   = start + n * stride;
				const size_t idxNm1 = start + (n - 1) * stride;
				const size_t idxNm2 = start + (n - 2) * stride;

				result += y[idxN] * (Type(2) * h1 * h1 + Type(3) * h0 * h1) /
					(Type(6) * (h0 + h1));
				result += y[idxNm1] * (h1 * h1 + Type(3) * h1 * h0) /
					(Type(6) * h0);
				result -= y[idxNm2] * (h1 * h1 * h1) /
					(Type(6) * h0 * (h0 + h1));
			}

			return result;
		}

		/**
		 * Computes Simpson sub-interval integrals for equally spaced samples. Call within a try/catch block.
		 * 
		 * Helper for cumulative Simpson integration with equal interval widths.
		 * Given N samples in y and N-1 spacings in dx, returns N-2 sub-interval
		 * integrals corresponding to the "h1" intervals (Cartwright equal-interval
		 * formula).
		 * 
		 * \tparam Type		The value type stored in the vectors (defaults to double).
		 * \param y			The sample values y[i].
		 * \param dx		The spacing between consecutive x-values, size y.size() - 1.
		 * \return			Returns a vector of size y.size() - 2 with sub-interval integrals.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									cumulativeSimpsonEqualIntervalsSub(const std::vector<Type>& y, const std::vector<Type>& dx) {
			if (y.size() < size_t(3)) {
				return std::vector<Type>();
			}

			if (dx.size() + 1 != y.size()) {
				throw std::invalid_argument("");
			}

			std::vector<Type> sub;
			sub.resize(y.size() - 2);

			for (size_t i = 0; i + 2 < y.size(); ++i) {
				const Type d  = dx[i];
				const Type f1 = y[i];
				const Type f2 = y[i+1];
				const Type f3 = y[i+2];

				const Type inner = (Type(5) * f1 / Type(4)) +
					(Type(2) * f2) -
					(f3 / Type(4));

				sub[i] = d * inner / Type(3);
			}

			return sub;
		}

		/**
		 * Computes Simpson sub-interval integrals for unequally spaced samples. Call within a try/catch block.
		 * 
		 * Helper for cumulative Simpson integration with unequal interval widths.
		 * Given N samples in y and N-1 spacings in dx, returns N-2 sub-interval
		 * integrals corresponding to the "h1" intervals (Cartwright unequal-interval
		 * formula).
		 * 
		 * \tparam Type		The value type stored in the vectors (defaults to double).
		 * \param y			The sample values y[i].
		 * \param dx		The spacing between consecutive x-values, size y.size() - 1.
		 * \return			Returns a vector of size y.size() - 2 with sub-interval integrals.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									cumulativeSimpsonUnequalIntervalsSub(const std::vector<Type>& y, const std::vector<Type>& dx) {
			if (y.size() < size_t(3)) {
				return std::vector<Type>();
			}

			if (dx.size() + 1 != y.size()) {
				throw std::invalid_argument("");
			}

			std::vector<Type> sub;
			sub.resize(y.size() - 2);

			for (size_t i = 0; i + 2 < y.size(); ++i) {
				const Type x21 = dx[i];
				const Type x32 = dx[i+1];

				const Type f1 = y[i];
				const Type f2 = y[i+1];
				const Type f3 = y[i+2];

				const Type x31            = x21 + x32;
				const Type x21_x31        = x21 / x31;
				const Type x21_x32        = x21 / x32;
				const Type x21x21_x31x32  = x21_x31 * x21_x32;
				const Type coeff1         = Type(3) - x21_x31;
				const Type coeff2         = Type(3) + x21x21_x31x32 + x21_x31;
				const Type coeff3         = -x21x21_x31x32;

				sub[i] = (x21 / Type(6)) * (coeff1 * f1 + coeff2 * f2 + coeff3 * f3);
			}

			return sub;
		}

		/**
		 * Combines "h1" and "h2" Simpson sub-interval integrals and returns per-interval contributions. Call within a try/catch block.
		 * 
		 * This mirrors SciPy's _cumulatively_sum_simpson_integrals behavior in 1D:
		 * sub-interval integrals from the left-biased (h1) and right-biased (h2)
		 * formulas are interleaved, and the last interval uses the final h2 value.
		 * 
		 * \tparam Type		The value type stored in the vectors (defaults to double).
		 * \param subH1		The sub-interval integrals for h1 intervals (size N-2).
		 * \param subH2		The sub-interval integrals for h2 intervals (size N-2).
		 * \return			Returns a vector of size N-1 with per-interval contributions.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									cumulativeSimpsonCombineSubIntervals(const std::vector<Type>& subH1, const std::vector<Type>& subH2) {
			if (subH1.size() != subH2.size()) {
				throw std::invalid_argument("");
			}
			if (subH1.empty()) {
				return std::vector<Type>();
			}

			const size_t subCount   = subH1.size();       // N-2
			const size_t intervalCt = subCount + 1;       // N-1

			std::vector<Type> sub;
			sub.resize(intervalCt);

			// sub_integrals[..., :-1:2] = sub_integrals_h1[..., ::2]
			for (size_t j = 0; j + 1 < intervalCt; j += 2) {
				sub[j] = subH1[j];
			}

			// sub_integrals[..., 1::2] = sub_integrals_h2[..., ::2]
			for (size_t j = 1, r = 0; j < intervalCt && r < subCount; j += 2, r += 2) {
				sub[j] = subH2[r];
			}

			// sub_integrals[..., -1] = sub_integrals_h2[..., -1]
			sub[intervalCt - 1] = subH2[subCount - 1];

			return sub;
		}

		/**
		 * Cumulatively integrates 1D data using the composite Simpson's 1/3 rule with uniform spacing.
		 * 
		 * For fewer than 3 points, falls back to the cumulative trapezoidal rule.
		 * This matches scipy.integrate.cumulative_simpson( y, dx=dx, x=None, initial=None ) for 1D input.
		 * 
		 * \tparam Type		The value type stored in the vector (defaults to double).
		 * \param y			The sample values y[i].
		 * \param dx		The uniform spacing between samples.
		 * \return			Returns a vector of size y.size() - 1 containing the cumulative integral.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									cumulativeSimpson1D(const std::vector<Type>& y, Type dx = Type(1)) {
			if (y.size() < 2) {
				return std::vector<Type>();
			}

			// For 2 points, no Simpson; use cumulative trapezoid.
			if (y.size() < size_t(3)) {
				std::vector<Type> out;
				out.resize(y.size() - 1);

				Type integrate = Type(0);
				for (size_t i = 1; i < y.size(); ++i) {
					const Type area = dx * Type(0.5) * (y[i-1] + y[i]);
					integrate += area;
					out[i-1] = integrate;
				}
				return out;
			}

			// Build dx array (equal intervals).
			std::vector<Type> dxVals;
			dxVals.resize(y.size() - 1);
			for (size_t i = 0; i < dxVals.size(); ++i) {
				dxVals[i] = dx;
			}

			// h1 contributions.
			std::vector<Type> subH1 = cumulativeSimpsonEqualIntervalsSub(y, dxVals);

			// h2 contributions: reverse inputs, compute, then reverse results.
			std::vector<Type> yRev(y.rbegin(), y.rend());
			std::vector<Type> dxValsRev(dxVals.rbegin(), dxVals.rend());
			std::vector<Type> subH2Rev = cumulativeSimpsonEqualIntervalsSub(yRev, dxValsRev);
			std::vector<Type> subH2(subH2Rev.rbegin(), subH2Rev.rend());

			// Combine h1 and h2 into per-interval contributions.
			std::vector<Type> sub = cumulativeSimpsonCombineSubIntervals(subH1, subH2);

			// Cumulative sum of interval contributions.
			std::vector<Type> out;
			out.resize(sub.size());

			Type integrate = Type(0);
			for (size_t i = 0; i < sub.size(); ++i) {
				integrate += sub[i];
				out[i] = integrate;
			}

			return out;
		}

		/**
		 * Cumulatively integrates 1D data using the composite Simpson's 1/3 rule with uniform spacing and an initial value.
		 * 
		 * For fewer than 3 points, falls back to the cumulative trapezoidal rule.
		 * The result matches scipy.integrate.cumulative_simpson( y, dx=dx, x=None, initial=initial )
		 * for 1D input.
		 * 
		 * \tparam Type		The value type stored in the vector (defaults to double).
		 * \param y			The sample values y[i].
		 * \param dx		The uniform spacing between samples.
		 * \param initial	The initial integral value (inserted at the beginning and added to the cumulative result).
		 * \return			Returns a vector of size y.size() containing the cumulative integral.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									cumulativeSimpson1D(const std::vector<Type>& y, Type dx, Type initial) {
			if (y.empty()) {
				return std::vector<Type>();
			}

			// Base cumulative Simpson (no initial).
			std::vector<Type> base = cumulativeSimpson1D(y, dx);

			std::vector<Type> out;
			out.resize(y.size());

			out[0] = initial;
			for (size_t i = 0; i < base.size(); ++i) {
				out[i+1] = initial + base[i];
			}

			return out;
		}

		/**
		 * Cumulatively integrates 1D data using the composite Simpson's 1/3 rule with non-uniform spacing. Call within a try/catch block.
		 * 
		 * For fewer than 3 points, falls back to the cumulative trapezoidal rule with non-uniform spacing.
		 * This matches scipy.integrate.cumulative_simpson( y, x=x, dx=1.0, initial=None ) for 1D input.
		 * 
		 * \tparam Type		The value type stored in the vectors (defaults to double).
		 * \param y			The sample values y[i].
		 * \param x			The sample locations x[i], same size as y and strictly increasing.
		 * \return			Returns a vector of size y.size() - 1 containing the cumulative integral.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									cumulativeSimpson1D(const std::vector<Type>& y, const std::vector<Type>& x) {
			if (x.size() != y.size()) {
				throw std::invalid_argument("");
			}

			if (y.size() < 2) {
				return std::vector<Type>();
			}

			// Build dx and check strictly increasing x.
			std::vector<Type> dxVals;
			dxVals.resize(x.size() - 1);
			for (size_t i = 1; i < x.size(); ++i) {
				const Type dx = x[i] - x[i-1];
				if (dx <= Type(0)) {
					throw std::invalid_argument("");
				}
				dxVals[i-1] = dx;
			}

			// For 2 points, no Simpson; use cumulative trapezoid.
			if (y.size() < size_t(3)) {
				std::vector<Type> out;
				out.resize(y.size() - 1);

				Type integrate = Type(0);
				for (size_t i = 1; i < y.size(); ++i) {
					const Type area = dxVals[i-1] * Type(0.5) * (y[i-1] + y[i]);
					integrate += area;
					out[i-1] = integrate;
				}
				return out;
			}

			// h1 contributions (unequal intervals).
			std::vector<Type> subH1 = cumulativeSimpsonUnequalIntervalsSub(y, dxVals);

			// h2 contributions: reverse inputs, compute, then reverse results.
			std::vector<Type> yRev(y.rbegin(), y.rend());
			std::vector<Type> dxValsRev(dxVals.rbegin(), dxVals.rend());
			std::vector<Type> subH2Rev = cumulativeSimpsonUnequalIntervalsSub(yRev, dxValsRev);
			std::vector<Type> subH2(subH2Rev.rbegin(), subH2Rev.rend());

			// Combine h1 and h2 into per-interval contributions.
			std::vector<Type> sub = cumulativeSimpsonCombineSubIntervals(subH1, subH2);

			// Cumulative sum of interval contributions.
			std::vector<Type> out;
			out.resize(sub.size());

			Type integrate = Type(0);
			for (size_t i = 0; i < sub.size(); ++i) {
				integrate += sub[i];
				out[i] = integrate;
			}

			return out;
		}

		/**
		 * Cumulatively integrates 1D data using the composite Simpson's 1/3 rule with non-uniform spacing and an initial value. Call within a try/catch block.
		 * 
		 * For fewer than 3 points, falls back to the cumulative trapezoidal rule with non-uniform spacing.
		 * This matches scipy.integrate.cumulative_simpson( y, x=x, initial=initial ) for 1D input.
		 * 
		 * \tparam Type		The value type stored in the vectors (defaults to double).
		 * \param y			The sample values y[i].
		 * \param x			The sample locations x[i], same size as y and strictly increasing.
		 * \param initial	The initial integral value (inserted at the beginning and added to the cumulative result).
		 * \return			Returns a vector of size y.size() containing the cumulative integral.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									cumulativeSimpson1D(const std::vector<Type>& y, const std::vector<Type>& x, Type initial) {
			if (y.empty()) {
				return std::vector<Type>();
			}

			std::vector<Type> base = cumulativeSimpson1D(y, x);

			std::vector<Type> out;
			out.resize(y.size());

			out[0] = initial;
			for (size_t i = 0; i < base.size(); ++i) {
				out[i+1] = initial + base[i];
			}

			return out;
		}

		/**
		 * Computes the trapezoidal integral over 1D data with uniform spacing.
		 * 
		 * \tparam Type		The value type stored in the vectors (defaults to double).
		 * \param y			The sample values y[i].
		 * \param dx		The uniform spacing between samples.
		 * \return			Returns the approximate integral.
		 **/
		template <typename Type = double>
		static inline Type			trapezoid1D(const std::vector<Type>& y, Type dx = Type(1)) {
			if (y.size() < 2) {
				return Type(0);
			}

			Type integrate = Type(0);

			// Interior points.
			for (size_t i = 1; i + 1 < y.size(); ++i) {
				integrate += y[i];
			}

			// Endpoints with half weight.
			integrate += Type(0.5) * (y.front() + y.back());

			return integrate * dx;
		}

		/**
		 * Computes the trapezoidal integral over 1D data with non-uniform spacing. Call within a try/catch block.
		 * 
		 * This matches scipy.integrate.trapezoid( y, x=x ) for 1D input.
		 * 
		 * \tparam Type		The value type stored in the vectors (defaults to double).
		 * \param y			The sample values y[i].
		 * \param x			The sample locations x[i], same size as y.
		 * \return			Returns the approximate integral.
		 **/
		template <typename Type = double>
		static inline Type			trapezoid1D(const std::vector<Type>& y, const std::vector<Type>& x) {
			if (x.size() != y.size()) {
				throw std::invalid_argument("");
			}
			if (y.size() < 2) {
				return Type(0);
			}

			Type integrate = Type(0);

			for (size_t i = 0; i + 1 < y.size(); ++i) {
				const Type dx = x[i+1] - x[i];
				const Type avg = Type(0.5) * (y[i] + y[i+1]);
				integrate += dx * avg;
			}

			return integrate;
		}

		/**
		 * Trapezoidal integration along a strided axis with uniform spacing. Call within a try/catch block.
		 * 
		 * This is analogous to scipy.integrate.trapezoid( y, dx=dx, axis=axis ) on a
		 * view of the array along 'axis', flattened to a 1D strided line.
		 * 
		 * \tparam Type		The value type stored in the vectors (defaults to double).
		 * \param y			The full data buffer.
		 * \param start		The starting index into y for this integration line.
		 * \param count		The number of samples along this line.
		 * \param stride	The stride (in elements) between successive samples.
		 * \param dx		The uniform spacing between samples.
		 * \return			Returns the approximate integral along that line.
		 **/
		template <typename Type = double>
		static inline Type			trapezoidStrided(const std::vector<Type>& y, size_t start, size_t count, size_t stride, Type dx = Type(1)) {
			if (count < 2) {
				return Type(0);
			}

			const size_t lastIndex = start + (count - 1) * stride;
			if (lastIndex >= y.size()) {
				throw std::out_of_range("");
			}

			Type integrate = Type(0);

			// First and last samples (half weight).
			const Type first = y[start];
			const Type last  = y[lastIndex];

			// Interior samples.
			for (size_t i = 1; i + 1 < count; ++i) {
				const size_t idx = start + i * stride;
				integrate += y[idx];
			}

			integrate += Type(0.5) * (first + last);

			return integrate * dx;
		}

		/**
		 * Trapezoidal integration along a strided axis with non-uniform spacing. Call within a try/catch block.
		 * 
		 * This is analogous to scipy.integrate.trapezoid( y, x=x, axis=axis ) where x is
		 * 1D and y is multi-dimensional. The integration is performed along a single
		 * strided line of y, with x giving the coordinates along that axis.
		 * 
		 * \tparam Type		The value type stored in the vectors (defaults to double).
		 * \param y			The full data buffer.
		 * \param start		The starting index into y for this integration line.
		 * \param stride	The stride (in elements) between successive samples.
		 * \param x			The 1D coordinates x[0..N-1] along this axis.
		 * \return			Returns the approximate integral along that line.
		 **/
		template <typename Type = double>
		static inline Type			trapezoidStrided(const std::vector<Type>& y, size_t start, size_t stride, const std::vector<Type>& x) {
			const size_t count = x.size();

			if (count < 2) {
				return Type(0);
			}

			const size_t lastIndex = start + (count - 1) * stride;
			if (lastIndex >= y.size()) {
				throw std::out_of_range("");
			}

			Type integrate = Type(0);

			for (size_t i = 0; i + 1 < count; ++i) {
				const size_t idx0 = start + i * stride;
				const size_t idx1 = start + (i + 1) * stride;

				const Type y0  = y[idx0];
				const Type y1  = y[idx1];
				const Type dx  = x[i+1] - x[i];
				const Type avg = Type(0.5) * (y0 + y1);

				integrate += dx * avg;
			}

			return integrate;
		}

		/**
		 * Computes the cumulative trapezoidal integral over 1D data with uniform spacing.
		 * 
		 * This matches scipy.integrate.cumulative_trapezoid( y, dx=dx, initial=None )
		 * in behavior for 1D input (no initial term).
		 * 
		 * \tparam Type		The value type stored in the vectors (defaults to double).
		 * \param y			The sample values y[i].
		 * \param dx		The uniform spacing between samples.
		 * \return			Returns a vector of size y.size() - 1 containing the cumulative integral.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									cumulativeTrapezoid1D(const std::vector<Type>& y, Type dx = Type(1)) {
			if (y.size() < 2) {
				return std::vector<Type>();
			}

			std::vector<Type> out;
			out.resize(y.size() - 1);

			Type integrate = Type(0);

			for (size_t i = 1; i < y.size(); ++i) {
				const Type area = dx * Type(0.5) * (y[i-1] + y[i]);
				integrate += area;
				out[i-1] = integrate;
			}

			return out;
		}

		/**
		 * Computes the cumulative trapezoidal integral over 1D data with uniform spacing and an initial value.
		 * 
		 * This matches scipy.integrate.cumulative_trapezoid( y, dx=dx, initial=initial )
		 * in behavior for 1D input (output has the same length as y).
		 * 
		 * \tparam Type		The value type stored in the vectors (defaults to double).
		 * \param y			The sample values y[i].
		 * \param dx		The uniform spacing between samples.
		 * \param initial	The initial integral value (prepended to the cumulative result).
		 * \return			Returns a vector of size y.size() containing the cumulative integral.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									cumulativeTrapezoid1D(const std::vector<Type>& y, Type dx, Type initial) {
			if (y.empty()) {
				return std::vector<Type>();
			}

			std::vector<Type> out;
			out.resize(y.size());

			out[0] = initial;
			Type integrate = initial;

			for (size_t i = 1; i < y.size(); ++i) {
				const Type area = dx * Type(0.5) * (y[i-1] + y[i]);
				integrate += area;
				out[i] = integrate;
			}

			return out;
		}

		/**
		 * Computes the cumulative trapezoidal integral over 1D data with non-uniform spacing. Call within a try/catch block.
		 * 
		 * This matches scipy.integrate.cumulative_trapezoid( y, x=x, initial=None )
		 * in behavior for 1D input (no initial term).
		 * 
		 * \tparam Type		The value type stored in the vectors (defaults to double).
		 * \param y			The sample values y[i].
		 * \param x			The sample locations x[i], same size as y.
		 * \return			Returns a vector of size y.size() - 1 containing the cumulative integral.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									cumulativeTrapezoid1D(const std::vector<Type>& y, const std::vector<Type>& x) {
			if (x.size() != y.size()) {
				throw std::invalid_argument("");
			}
			if (y.size() < 2) {
				return std::vector<Type>();
			}

			std::vector<Type> out;
			out.resize(y.size() - 1);

			Type integrate = Type(0);

			for (size_t i = 1; i < y.size(); ++i) {
				const Type dx = x[i] - x[i-1];
				const Type area = dx * Type(0.5) * (y[i-1] + y[i]);
				integrate += area;
				out[i-1] = integrate;
			}

			return out;
		}

		/**
		 * Computes the cumulative trapezoidal integral over 1D data with non-uniform spacing and an initial value. Call within a try/catch block.
		 * 
		 * This matches scipy.integrate.cumulative_trapezoid( y, x=x, initial=initial )
		 * in behavior for 1D input (output has the same length as y).
		 * 
		 * \tparam Type		The value type stored in the vectors (defaults to double).
		 * \param y			The sample values y[i].
		 * \param x			The sample locations x[i], same size as y.
		 * \param initial	The initial integral value (prepended to the cumulative result).
		 * \return			Returns a vector of size y.size() containing the cumulative integral.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									cumulativeTrapezoid1D(const std::vector<Type>& y, const std::vector<Type>& x, Type initial) {
			if (x.size() != y.size()) {
				throw std::invalid_argument("");
			}
			if (y.empty()) {
				return std::vector<Type>();
			}

			std::vector<Type> out;
			out.resize(y.size());

			out[0] = initial;
			Type integrate = initial;

			for (size_t i = 1; i < y.size(); ++i) {
				const Type dx = x[i] - x[i-1];
				const Type area = dx * Type(0.5) * (y[i-1] + y[i]);
				integrate += area;
				out[i] = integrate;
			}

			return out;
		}

		/**
		 * Romberg integration over a 1D array of equally spaced samples. Must be called within a try/catch block.
		 * 
		 * The number of samples must be 2^k + 1 for some integer k >= 1. The spacing between samples is dx.
		 * This mirrors scipy.integrate.romb( y, dx=dx ) for 1D input.
		 * 
		 * \tparam Type		The floating-point type used for accumulation and return (defaults to double).
		 * \param y			The vector of function samples y[0..N-1].
		 * \param dx		The spacing between consecutive samples.
		 * \return			Returns the Romberg approximation to the integral over the sampled interval.
		 * \throw std::invalid_argument Thrown if the input size is invalid.
		 **/
		template <typename Type = double>
		static inline Type			romb1D(const std::vector<Type>& y, Type dx = Type(1)) {
			const size_t nSamples = y.size();
			if (nSamples < 2) {
				throw std::invalid_argument("");
			}

			const size_t nIntervals = nSamples - 1;
			if ((nIntervals & (nIntervals - 1)) != 0) {
				throw std::invalid_argument("");
			}

			// Number of Romberg levels k such that nIntervals == 2^k.
			size_t k = 0;
			{
				size_t tmp = nIntervals;
				while (tmp > 1) {
					tmp >>= 1;
					++k;
				}
			}

			// Romberg table rows (we only keep previous and current).
			std::vector<Type> rowPrev;
			std::vector<Type> rowCurr;
			rowPrev.reserve(k + 1);
			rowCurr.reserve(k + 1);

			const size_t lastIndex = nSamples - 1;

			// Build T_l (trapezoid approximations) for l = 0..k from the pre-sampled data.
			// For each level l:
			//  * Number of intervals  = 2^l
			//  * Index step in samples = 2^(k-l)
			//  * Step width h_l = step * dx
			for (size_t l = 0; l <= k; ++l) {
				const size_t step      = 1 << (k - l);   // Index step between samples.
				const size_t intervals = 1 << l;         // Number of intervals.
				const Type h           = dx * static_cast<Type>(step);

				// Trapezoid T_l over this coarser grid.
				Type sum = y[0] + y[lastIndex];
				for (size_t j = 1; j < intervals; ++j) {
					const size_t idx = j * step;
					sum += y[idx];
				}
				const Type t = h * sum * Type(0.5);

				rowCurr.resize(l + 1);
				rowCurr[0] = t;

				// Richardson extrapolation for this row.
				for (size_t m = 1; m <= l; ++m) {
					const Type fourPow = static_cast<Type>(1 << (2 * m));
					const Type denom   = fourPow - Type(1);
					const Type prev    = rowCurr[m-1];

					rowCurr[m] = prev + (prev - rowPrev[m-1]) / denom; 
				}

				rowPrev = rowCurr;
			}

			return rowPrev[k];
		}

		/**
		 * Romberg integration over a strided 1D line of equally spaced samples. Must be called within a try/catch block.
		 * 
		 * This is the "axis" analogue of Romb1D. It integrates along the logical sequence
		 * 
		 * y[k] = y[start + k * stride],  k = 0..(count-1),
		 * 
		 * where the length count must be 2^k + 1 for some integer k >= 1. The spacing
		 * between samples along this line is dx. This mirrors scipy.integrate.romb( y, dx=dx, axis=axis )
		 * for one axis slice at a time.
		 * 
		 * \tparam Type		The floating-point type used for accumulation and return (defaults to double).
		 * \param y			The full data buffer.
		 * \param start		The starting index in y for this integration line.
		 * \param count		The number of samples along this line (must be 2^k + 1).
		 * \param stride	The stride (in elements) between successive samples along the line.
		 * \param dx		The spacing between consecutive samples along the line.
		 * \return			Returns the Romberg approximation to the integral over the sampled line.
		 * \throw std::invalid_argument Thrown if count is invalid.
		 * \throw std::out_of_range Thrown if the line exceeds y.size().
		 **/
		template <typename Type = double>
		static inline Type			rombStrided(const std::vector<Type>& y, size_t start, size_t count, size_t stride, Type dx = Type(1)) {
			if (count < 2) {
				throw std::invalid_argument("");
			}

			const size_t lastIndex = start + (count - 1) * stride;
			if (lastIndex >= y.size()) {
				throw std::out_of_range("");
			}

			const size_t nIntervals = count - 1;
			if ((nIntervals & (nIntervals - 1)) != 0) {
				throw std::invalid_argument("");
			}

			// Number of Romberg levels k such that nIntervals == 2^k.
			size_t k = 0;
			{
				size_t tmp = nIntervals;
				while (tmp > 1) {
					tmp >>= 1;
					++k;
				}
			}

			std::vector<Type> rowPrev;
			std::vector<Type> rowCurr;
			rowPrev.reserve(k + 1);
			rowCurr.reserve(k + 1);

			// Build T_l (trapezoid approximations) for l = 0..k along the strided line.
			for (size_t l = 0; l <= k; ++l) {
				const size_t step      = 1 << (k - l);   // Step in "logical sample index" units.
				const size_t intervals = 1 << l;         // Number of intervals.
				const Type h           = dx * static_cast<Type>(step);

				const size_t idx0      = start;
				const size_t idxLast   = start + (count - 1) * stride;

				Type sum = y[idx0] + y[idxLast];

				for (size_t j = 1; j < intervals; ++j) {
					const size_t logicalIdx = j * step;
					const size_t idx        = start + logicalIdx * stride;
					sum += y[idx];
				}

				const Type t = h * sum * Type(0.5);

				rowCurr.resize(l + 1);
				rowCurr[0] = t;

				for (size_t m = 1; m <= l; ++m) {
					const Type fourPow = static_cast<Type>(1 << (2 * m));
					const Type denom   = fourPow - Type(1);
					const Type prev    = rowCurr[m-1];

					rowCurr[m] = prev + (prev - rowPrev[m-1]) / denom;
				}

				rowPrev = rowCurr;
			}

			return rowPrev[k];
		}


		// ===============================
		// Vector Generation & Initialization
		// ===============================
		/**
		 * Creates a 1D vector of linearly spaced values. Must be called within a try/catch block.
		 * 
		 * This function emulates numpy.linspace for 1D data:
		 * 
		 * - If num == 0, returns an empty vector.
		 * - If num == 1, returns {start} regardless of endpoint.
		 * - If endpoint is true, the last element equals stop.
		 * - If endpoint is false, the sequence goes up to but does not include stop.
		 * 
		 * If step is not nullptr, the step size used to generate the sequence is
		 * written to *step (similar to retstep=True in NumPy).
		 * 
		 * \tparam Type		The value type used for the sequence (defaults to double).
		 * \param start		The starting value of the sequence.
		 * \param stop		The final value of the sequence (inclusive if endpoint is true).
		 * \param num		The number of samples to generate.
		 * \param endpoint	If true, stop is included as the last sample. If false, stop is excluded.
		 * \param step		Optional pointer that, if non-null, receives the step size used.
		 * \return			Returns a vector containing the generated samples.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									linspace(Type start, Type stop, size_t num = 50, bool endpoint = true, Type* step = nullptr) {
			std::vector<Type> out;

			if (num == 0) {
				if (step) {
					(*step) = Type(0);
				}
				return out;
			}

			out.resize(num);

			if (num == 1) {
				out[0] = start;
				if (step) {
					(*step) = Type(0);
				}
				return out;
			}

			const double div = endpoint ?
				static_cast<double>(num - 1.0) :
				static_cast<double>(num);

			const double stepSize = static_cast<double>(stop - start) / div;

			if (step) {
				(*step) = Type(stepSize);
			}

			for (size_t i = 0; i < num; ++i) {
				out[i] = static_cast<Type>(start + stepSize * i);
			}

			// For endpoint == true, the formula already gives out.back() == stop
			// algebraically, but a direct assignment avoids any accumulated rounding.
			if (endpoint) {
				out[num-1] = static_cast<Type>(stop);
			}

			return out;
		}

		/**
		 * Creates a 1D vector with values in the half-open interval [0, stop). Must be called within a try/catch block.
		 * 
		 * This emulates numpy.arange( stop ) for 1D data.
		 * 
		 * \tparam Type		The value type used for the sequence (defaults to double).
		 * \param stop		The end of the half-open interval [0, stop).
		 * \return			Returns a vector containing the generated samples.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									arange(Type stop) {
			return arange<Type>(Type(0), stop, Type(1));
		}

		/**
		 * Creates a 1D vector with values in the half-open interval [start, stop) with a given step. Must be called within a try/catch block.
		 * 
		 * This emulates numpy.arange( start, stop, step, dtype=Out ) for 1D data.
		 * 
		 * For floating-point arguments, the length is computed as:
		 * ceil((stop - start) / step)
		 * 
		 * The actual step used to populate the array matches NumPy's documented behavior:
		 * step_actual = dtype(start + step) - dtype(start)
		 * 
		 * \tparam Out		The output element type (NumPy's dtype). Defaults to double.
		 * \tparam Start	The type of the start parameter.
		 * \tparam Stop		The type of the stop parameter.
		 * \tparam Step		The type of the step parameter.
		 * \param startVal	The start of the half-open interval.
		 * \param stopVal	The end of the half-open interval.
		 * \param stepVal	The step between consecutive samples (must be non-zero).
		 * \return			Returns a vector containing the generated samples.
		 * \throw std::invalid_argument Thrown if stepVal is zero.
		 **/
		template <typename Out = double, typename Start, typename Stop, typename Step>
		static inline std::vector<Out>
									arange(Start startVal, Stop stopVal, Step stepVal) {
			const long double startLd = static_cast<long double>(startVal);
			const long double stopLd  = static_cast<long double>(stopVal);
			const long double stepLd  = static_cast<long double>(stepVal);

			if (stepLd == static_cast<long double>(0)) {
				throw std::invalid_argument("");
			}

			size_t count = 0;

			// Only produce values if we can move from start toward stop using the sign of step.
			if ((stepLd > static_cast<long double>(0) && startLd < stopLd) ||
				(stepLd < static_cast<long double>(0) && startLd > stopLd)) {
				const long double spanLd = stopLd - startLd;
				const long double rawCountLd = spanLd / stepLd;

				long double ceilCountLd = std::ceill(rawCountLd);
				if (ceilCountLd < static_cast<long double>(0)) {
					ceilCountLd = static_cast<long double>(0);
				}

				count = static_cast<size_t>(ceilCountLd);
			}
			else {
				count = 0;
			}

			std::vector<Out> out;
			out.resize(count);

			if (count == 0) {
				return out;
			}

			// NumPy uses dtype(start + step) - dtype(start) as the internal step,
			// which reproduces the documented "instabilities" for integer dtypes.
			const Out startCast = static_cast<Out>(startLd);
			out[0] = startCast;

			if (count > 1) {
				const Out nextCast = static_cast<Out>(startLd + stepLd);
				const Out stepActual = static_cast<Out>(nextCast - startCast);

				for (size_t i = 1; i < count; ++i) {
					out[i] = static_cast<Out>(out[i-1] + stepActual);
				}
			}

			return out;
		}

		/**
		 * Creates a 1D vector filled with zeros. Must be called within a try/catch block.
		 * 
		 * This emulates numpy.zeros( shape ) for 1D data.
		 * 
		 * \tparam Type		The value type stored in the vector (defaults to double).
		 * \param count		The number of elements.
		 * \return			Returns a vector of length count, filled with zero.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									zeros(size_t count) {
			return std::vector<Type>(count, Type(0));
		}

		/**
		 * Creates a 1D vector filled with zeros, matching the length of another vector. Must be called within a try/catch block.
		 * 
		 * This emulates numpy.zeros_like( a ) for 1D data.
		 * 
		 * \tparam Type		The value type stored in the vectors.
		 * \param ref		The reference vector whose length is used.
		 * \return			Returns a vector of length ref.size(), filled with zero.
		 **/
		template <typename Type>
		static inline std::vector<Type>
									zerosLike(const std::vector<Type>& ref) {
			return std::vector<Type>(ref.size(), Type(0));
		}

		/**
		 * Creates a 1D vector filled with ones. Must be called within a try/catch block.
		 * 
		 * This emulates numpy.ones( shape ) for 1D data.
		 * 
		 * \tparam Type		The value type stored in the vector (defaults to double).
		 * \param count		The number of elements.
		 * \return			Returns a vector of length count, filled with one.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									ones(size_t count) {
			return std::vector<Type>(count, Type(1));
		}

		/**
		 * Creates a 1D vector filled with ones, matching the length of another vector. Must be called within a try/catch block.
		 * 
		 * This emulates numpy.ones_like( a ) for 1D data.
		 * 
		 * \tparam Type		The value type stored in the vectors.
		 * \param ref		The reference vector whose length is used.
		 * \return			Returns a vector of length ref.size(), filled with one.
		 **/
		template <typename Type>
		static inline std::vector<Type>
									onesLike(const std::vector<Type>& ref) {
			return std::vector<Type>(ref.size(), Type(1));
		}

		/**
		 * Creates a 1D vector filled with a constant value. Must be called within a try/catch block.
		 * 
		 * This emulates numpy.full( shape, fill_value ) for 1D data.
		 * 
		 * \tparam Type		The value type stored in the vector (defaults to double).
		 * \param count		The number of elements.
		 * \param value		The value with which to fill the vector.
		 * \return			Returns a vector of length count, filled with value.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									full(size_t count, Type value) {
			return std::vector<Type>(count, value);
		}

		/**
		 * Creates a 1D vector filled with a constant value, matching the length of another vector. Must be called within a try/catch block.
		 * 
		 * This emulates numpy.full_like( a, fill_value ) for 1D data.
		 * 
		 * \tparam Type		The value type stored in the vectors.
		 * \param ref		The reference vector whose length is used.
		 * \param value		The value with which to fill the vector.
		 * \return			Returns a vector of length ref.size(), filled with value.
		 **/
		template <typename Type>
		static inline std::vector<Type>
									fullLike(const std::vector<Type>& ref, Type value) {
			return std::vector<Type>(ref.size(), value);
		}

		/**
		 * Creates a 1D vector of numbers spaced evenly on a log scale. Must be called within a try/catch block.
		 * 
		 * This emulates numpy.logspace( start, stop, num=50, endpoint=True, base=10.0, dtype=Type, axis=0 )
		 * for real dtypes in 1D.
		 * 
		 * Floating-point Type:
		 * Behaves like NumPy's logspace for real inputs.
		 * Integer Type:
		 * Behaves like np.around(np.logspace(...)).astype(int), which avoids
		 * truncation artifacts when values are very close to integers.
		 * 
		 * \tparam Type		The result dtype (NumPy's dtype analogue). Defaults to double.
		 * \tparam Start	Type of the starting exponent.
		 * \tparam Stop		Type of the final exponent.
		 * \param startExp	The starting exponent.
		 * \param stopExp	The final exponent.
		 * \param num		The number of samples to generate (default 50).
		 * \param endpoint	If true, the last sample is approximately base**stopExp; otherwise it is excluded.
		 * \param base		The base of the log scale (default 10.0).
		 * \return			Returns a vector of log-spaced samples.
		 * \throw std::overflow_error Thrown for integer Type if a rounded value is out of range for Type.
		 **/
		template <typename Type = double, typename Start, typename Stop>
		static inline std::vector<Type>
									logspace(Start startExp, Stop stopExp, size_t num = 50, bool endpoint = true, double base = 10.0) {
			std::vector<Type> out;

			if (num == 0) {
				return out;
			}

			out.resize(num);

			if (num == 1) {
				// NumPy returns base**start when num == 1.
				const double startExpDouble = static_cast<double>(startExp);
				const double val = std::pow(base, startExpDouble);

				if constexpr (std::is_integral_v<Type>) {
					long long llVal = std::llround(static_cast<long double>(val));

					if (llVal < static_cast<long long>(std::numeric_limits<Type>::min()) ||
						llVal > static_cast<long long>(std::numeric_limits<Type>::max())) {
						throw std::overflow_error("");
					}

					out[0] = static_cast<Type>(llVal);
				}
				else {
					out[0] = static_cast<Type>(val);
				}

				return out;
			}

			const double startExpDouble = static_cast<double>(startExp);
			const double stopExpDouble  = static_cast<double>(stopExp);

			const double countDouble = static_cast<double>(num);
			const double divisor = endpoint
				? (countDouble - 1.0)
				: countDouble;

			const double stepExp = (stopExpDouble - startExpDouble) / divisor;

			for (size_t i = 0; i < num; ++i) {
				const double exp = startExpDouble + stepExp * static_cast<double>(i);
				const double val = std::pow(base, exp);

				if constexpr (std::is_integral_v<Type>) {
					long long llVal = std::llround(static_cast<long double>(val));

					if (llVal < static_cast<long long>(std::numeric_limits<Type>::min()) ||
						llVal > static_cast<long long>(std::numeric_limits<Type>::max())) {
						throw std::overflow_error("");
					}

					out[i] = static_cast<Type>(llVal);
				}
				else {
					out[i] = static_cast<Type>(val);
				}
			}

			if (endpoint) {
				const double endVal = std::pow(base, stopExpDouble);

				if constexpr (std::is_integral_v<Type>) {
					long long llVal = std::llround(static_cast<long double>(endVal));

					if (llVal < static_cast<long long>(std::numeric_limits<Type>::min()) ||
						llVal > static_cast<long long>(std::numeric_limits<Type>::max())) {
						throw std::overflow_error("");
					}

					out[num-1] = static_cast<Type>(llVal);
				}
				else {
					out[num-1] = static_cast<Type>(endVal);
				}
			}

			return out;
		}

		/**
		 * Creates a 1D vector of numbers spaced evenly on a multiplicative (geometric) scale. Must be called within a try/catch block.
		 * 
		 * This emulates numpy.geomspace( start, stop, num=50, endpoint=True, dtype=Type, axis=0 )
		 * for real dtypes in 1D.
		 * 
		 * Floating-point Type:
		 * Behaves like NumPy's geomspace for real inputs.
		 * Integer Type:
		 * Behaves like np.around(np.geomspace(...)).astype(int), which avoids
		 * truncation artifacts when values are very close to integers.
		 * 
		 * If start and stop have opposite signs, the real-valued version cannot reproduce
		 * NumPy's complex-valued spiral and will throw.
		 * 
		 * \tparam Type		The result type (NumPy's dtype analogue). Defaults to double.
		 * \param start		The starting value.
		 * \param stop		The final value.
		 * \param num		The number of samples to generate (default 50).
		 * \param endpoint	If true, the last sample is (approximately) stop; otherwise it is excluded.
		 * \return			Returns a vector of geometrically spaced samples.
		 * \throw std::invalid_argument Thrown if start and stop have opposite signs.
		 * \throw std::overflow_error Thrown for integer Type if a rounded value is out of range for Type.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									geomspace(Type start, Type stop, size_t num = size_t(50), bool endpoint = true) {
			std::vector<Type> out;

			if (num == 0) {
				return out;
			}

			out.resize(num);

			if (num == 1) {
				out[0] = static_cast<Type>(start);
				return out;
			}

			const double startDouble = static_cast<double>(start);
			const double stopDouble  = static_cast<double>(stop);

			const bool negStart = (startDouble < 0.0);
			const bool negStop  = (stopDouble < 0.0);

			int sign = 1;
			double magStart = startDouble;
			double magStop  = stopDouble;

			if (negStart && negStop) {
				magStart = -startDouble;
				magStop  = -stopDouble;
				sign = -1;
			}
			else if (negStart != negStop) {
				throw std::invalid_argument("");
			}

			const double ratio = magStop / magStart;

			// Exponent goes from 0 to 1 (endpoint) or 0 to 1 - 1/num (no endpoint).
			const double expStart = 0.0;
			const double expStop = endpoint ?
				1.0 :
				1.0 - 1.0 / static_cast<double>(num);
			const double stepExp = (expStop - expStart) /
				static_cast<double>(num - 1);

			for (size_t i = 0; i < num; ++i) {
				const double exp = expStart + stepExp * static_cast<double>(i);
				const double valMag = magStart * std::pow(ratio, exp);
				const double signedVal = static_cast<double>(sign) * valMag;

				if constexpr (std::is_integral_v<Type>) {
					long double ldVal = static_cast<long double>(signedVal);
					long long llVal = std::llround(ldVal);

					if (llVal < static_cast<long long>(std::numeric_limits<Type>::min()) ||
						llVal > static_cast<long long>(std::numeric_limits<Type>::max())) {
						throw std::overflow_error("");
					}

					out[i] = static_cast<Type>(llVal);
				}
				else {
					out[i] = static_cast<Type>(signedVal);
				}
			}

			if (endpoint) {
				out[num-1] = static_cast<Type>(stop);
			}

			return out;
		}

		/**
		 * Computes the n-th discrete difference along a 1D array. Must be called within a try/catch block.
		 * 
		 * This emulates numpy.diff( a, n=n ) for 1D input:
		 * 
		 * - If n == 0, a copy of x is returned.
		 * - Each application of the difference reduces the length by 1.
		 * - If n > 0 and x.size() <= n, an empty vector is returned.
		 * 
		 * \tparam Type		The value type stored in the vector (defaults to double).
		 * \param x			The input samples.
		 * \param n			The order of the difference (default 1).
		 * \return			Returns the n-th order difference of x.
		 **/
		template <typename Type = double>
		static inline std::vector<Type>
									diff1D(const std::vector<Type>& x, size_t n = 1) {
			if (n == 0) {
				return x;
			}

			if (x.size() <= n) {
				return std::vector<Type>();
			}

			std::vector<Type> cur = x;

			for (size_t iter = 0; iter < n; ++iter) {
				if (cur.size() < 2) {
					return std::vector<Type>();
				}

				std::vector<Type> next;
				next.resize(cur.size() - 1);

				for (size_t i = 0; i + 1 < cur.size(); ++i) {
					next[i] = cur[i+1] - cur[i];
				}

				cur.swap(next);
			}

			return cur;
		}


		// ===============================
		// Vector Operations & Transformations
		// ===============================
		/**
		 * Converts a single value to another type using NumPy-style astype semantics.
		 * 
		 * This emulates numpy.asarray(x).astype(Out)[...] for a single value:
		 * 
		 * - Floating-point to integer: Truncates toward zero (via static_cast).
		 * - Integer to floating-point: Converts exactly where representable.
		 * - Any numeric type to bool: Zero becomes false, non-zero becomes true.
		 * 
		 * No range checking is performed; overflow and underflow follow normal C++ conversion
		 * rules for static_cast.
		 * 
		 * \tparam Out		The output type (NumPy's dtype analogue).
		 * \tparam In		The input type.
		 * \param value		The value to convert.
		 * \return			Returns the converted value.
		 **/
		template <typename Out, typename In>
		static inline Out			astype(In value) {
			return static_cast<Out>(value);
		}

		/**
		 * Converts a vector to another type using NumPy-style astype semantics. Must be called within a try/catch block.
		 * 
		 * This emulates numpy.asarray(v).astype(Out) for 1D arrays:
		 * 
		 * - A new vector is always created (like copy=True in NumPy).
		 * - Floating-point to integer: Truncates toward zero (via static_cast).
		 * - Integer to floating-point: Converts exactly where representable.
		 * - Any numeric type to bool: Zero becomes false, non-zero becomes true.
		 * 
		 * No range checking is performed; overflow and underflow follow normal C++ conversion
		 * rules for static_cast (similar in spirit to NumPy's casting='unsafe').
		 * 
		 * \tparam Out		The output element type (NumPy's dtype analogue).
		 * \tparam In		The input element type.
		 * \param inVec		The input vector.
		 * \return			Returns a new vector whose elements are converted to Out.
		 **/
		template <typename Out, typename In>
		static inline std::vector<Out>
									astype(const std::vector<In>& inVec) {
			std::vector<Out> out;
			out.resize(inVec.size());

			for (size_t i = 0; i < inVec.size(); ++i) {
				out[i] = static_cast<Out>(inVec[i]);
			}

			return out;
		}

		// ===============================
		// DSP Window Functions
		// ===============================
		/**
		 * Internal helper to guard trivial window sizes.
		 * 
		 * \param n			Number of samples.
		 * \param ret		Returned vector.
		 * \return			Returns true if handled or memory was available; false on allocation failure.
		 **/
		template <typename Type>
		static bool					handleTrivialWindow(size_t n, std::vector<Type>& ret) {
			try {
				if (n == 0) {
					ret.clear();
					return true;
				}
				ret.resize(n);
				if (n == 1) {
					ret[0] = Type(1);
				}
				return true;
			}
			catch (...) {
				return false;
			}
		}

		/**
		 * A 0th-order Bessel function needed for the Kaiser window.
		 * 
		 * \param x			The Bessel term.
		 * \return			Returns the Bessel function for the given term.
		 **/
		static inline double		bessel0(double x) {
			constexpr double espiRatio = 1.0e-16;
			double sum = 1.0;
			double powVal = 1.0;
			double ds = 1.0;
			double xh = x * 0.5;
			uint32_t k = 0;

			while (ds > sum * espiRatio) {
				++k;
				powVal *= (xh / k);
				ds = powVal * powVal;
				sum += ds;
			}

			return sum;
		}

		/**
		 * Barthann (modified Bartlett-Hann) window.
		 * 
		 * Returns a modified Bartlett-Hann window (Barthann).
		 * A common definition is:
		 * x = n / (N-1)
		 * w[n] = 0.62
		 * - 0.48 * |x - 0.5|
		 * - 0.38 * cos( 2*pi*x ).
		 * 
		 * \param n			Number of samples.
		 * \param ret		Returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					barthannWindow(size_t n, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n == 1) {
				return true;
			}

			double den = static_cast<double>(n - 1);
			for (size_t i = n; i--; ) {
				double x = static_cast<double>(i) / den;
				double v = 0.62
							- 0.48 * std::fabs(x - 0.5)
							- 0.38 * cosExact(2.0 * std::numbers::pi * x);
				ret[i] = Type(v);
			}
			return true;
		}

		/**
		 * Creates a Bartlett window.
		 * 
		 * \param n			Number of samples. Generally an odd number.
		 * \param ret		The returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					bartlettWindow(size_t n, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n <= 1) {
				return true;
			}

			size_t maxIdx = ret.size() - 1;
			double twoInvMax = 2.0 / maxIdx;
			double halfMax = maxIdx / 2.0;
			for (size_t i = n; i--; ) {
				ret[i] = Type(twoInvMax * (halfMax - std::abs(static_cast<double>(i) - halfMax)));
			}

			return true;
		}

		/**
		 * Creates a Blackman window.
		 * 
		 * \param n			Number of samples. Generally an odd number.
		 * \param ret		The returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					blackmanWindow(size_t n, std::vector<Type>& ret) {
			constexpr double a = 0.16;
			constexpr double a0 = (1.0 - a) / 2.0;
			constexpr double a1 = 1.0 / 2.0;
			constexpr double a2 = a / 2.0;
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n <= 1) {
				return true;
			}

			const double tau = 2.0 * std::numbers::pi;
			size_t maxIdx = ret.size() - 1;
			double invMax = 1.0 / maxIdx;
			double tauInvMax = tau * invMax;
			double tauInvMax2 = 2.0 * tauInvMax;
			for (size_t i = n; i--; ) {
				ret[i] = Type(a0 - a1 * cosExact(tauInvMax * i) + a2 * cosExact(tauInvMax2 * i));
			}

			return true;
		}

		/**
		 * Creates a Blackman-Harris window.
		 * 
		 * \param n			Number of samples. Generally an odd number.
		 * \param ret		The returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					blackmanHarrisWindow(size_t n, std::vector<Type>& ret) {
			constexpr double a0 = 0.35875;
			constexpr double a1 = 0.48829;
			constexpr double a2 = 0.14128;
			constexpr double a3 = 0.01168;

			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n <= 1) {
				return true;
			}

			const double tau = 2.0 * std::numbers::pi;
			size_t maxIdx = ret.size() - 1;
			double invMax = 1.0 / maxIdx;
			double tauInvMax = tau * invMax;
			double tauInvMax2 = 2.0 * tauInvMax;
			double tauInvMax3 = 3.0 * tauInvMax;
			for (size_t i = n; i--; ) {
				ret[i] = Type(a0 - a1 * cosExact(tauInvMax * i) + a2 * cosExact(tauInvMax2 * i) - a3 * cosExact(tauInvMax3 * i));
			}

			return true;
		}

		/**
		 * Creates a Blackman-Nuttal window.
		 * 
		 * \param n			Number of samples. Generally an odd number.
		 * \param ret		The returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					blackmanNuttalWindow(size_t n, std::vector<Type>& ret) {
			constexpr double a0 = 0.3635819;
			constexpr double a1 = 0.4891775;
			constexpr double a2 = 0.1365995;
			constexpr double a3 = 0.0106411;

			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n <= 1) {
				return true;
			}

			const double tau = 2.0 * std::numbers::pi;
			size_t maxIdx = ret.size() - 1;
			double invMax = 1.0 / maxIdx;
			double tauInvMax = tau * invMax;
			double tauInvMax2 = 2.0 * tauInvMax;
			double tauInvMax3 = 3.0 * tauInvMax;
			for (size_t i = n; i--; ) {
				ret[i] = Type(a0 - a1 * cosExact(tauInvMax * i) + a2 * cosExact(tauInvMax2 * i) - a3 * cosExact(tauInvMax3 * i));
			}

			return true;
		}

		/**
		 * Bohman window.
		 * 
		 * Returns a Bohman window:
		 * Let M = (N - 1) / 2.
		 * r = |k / M - 1|
		 * w[k] = (1 - r) cos( pi*r ) + (1/pi) sin( pi*r ).
		 * 
		 * \param n			Number of samples.
		 * \param ret		Returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					bohmanWindow(size_t n, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n == 1) {
				return true;
			}

			try {
				double m = (static_cast<double>(n) - 1.0) * 0.5;
				double invPi = 1.0 / std::numbers::pi;
				for (size_t i = n; i--; ) {
					double r = std::fabs(static_cast<double>(i) / m - 1.0);
					double cr, sr;
					::SinCos(std::numbers::pi * r, &sr, &cr);
					double v = (1.0 - r) * cr + invPi * sr;
					ret[i] = Type(v);
				}
				return true;
			}
			catch (...) {
				return false;
			}
		}

		/**
		 * Boxcar (rectangular) window.
		 * 
		 * Returns a simple boxcar window of ones.
		 * 
		 * \param n			Number of samples.
		 * \param ret		Returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					boxcarWindow(size_t n, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			for (size_t i = n; i--; ) {
				ret[i] = Type(1);
			}
			return true;
		}

		/**
		 * Creates a Dolph-Chebyshev (Chebwin) window.
		 * 
		 * Implements the same Chebyshev window as scipy.signal.windows.chebwin()
		 * / MATLAB's chebwin(), using the Lyons procedure:
		 * - M samples total.
		 * - Sidelobe attenuation of at dB.
		 * - Window is normalized so that max( w[n] ) == 1.
		 * 
		 * \param m			Number of samples in the window (M).
		 * \param at		Sidelobe attenuation in dB (e.g., 100.0).
		 * \param ret		The returned window values.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template<typename Type = double>
		static bool					chebwinWindow(size_t m, double at, std::vector<Type>& ret) {
			try {
				if (!handleTrivialWindow(m, ret)) {
					return false;
				}
				if (m == 1) {
					return true;
				}

				// Non-positive attenuation degenerates toward a boxcar.
				if (at <= 0.0) {
					for (size_t i = 0; i < m; ++i) {
						ret[i] = Type(1);
					}
					return true;
				}

				const size_t n = m - 1;		// Lyons: N = M - 1.

				// Step 2: γ controls sidelobe level, sidelobes at -20*γ dB.
				const double gamma = at / 20.0;
				const double tenGamma = std::pow(10.0, gamma);

				// Step 3: α = cosh( acosh(10^γ) / N ).
				const double alpha = std::cosh(std::acosh(tenGamma) / static_cast<double>(n));

				// Step 4 & 5: Build W(m) sequence in the frequency domain.
				std::vector<double> w;
				w.resize(n);

				for (size_t i = 0; i < n; ++i) {
					const double cosVal = cosExact(std::numbers::pi * static_cast<double>(i) / static_cast<double>(n));
					const double a = std::fabs(alpha * cosVal);

					double val;
					if (a > 1.0) {
						// W(M) = (-1)^M * cosh( N * acosh( |A(M)| ) ).
						val = std::cosh(static_cast<double>(n) * std::acosh(a));
					}
					else {
						// W(M) = (-1)^M * cos( N * acos( |A(M)| ) ).
						val = cosExact(static_cast<double>(n) * std::acos(a));
					}

					if (i & 1) {
						val = -val;
					}
					w[i] = val;
				}

				// Lyons 2011 update: If M is even and we used |A(m)|, flip the last M/2 - 1 W(m)'s.
				if ((m & 1) == 0) {
					const size_t half = m / 2;
					if (half > 1) {
						const size_t count = half - 1;
						const size_t start = n - count;
						for (size_t j = start; j < n; ++j) {
							w[j] = -w[j];
						}
					}
				}

				// Step 6: N-point inverse DFT of W(m), but we can ignore the 1/N scale factor
				// because we'll normalize later. Only the real part is needed, so we use cos().
				std::vector<double> tmp;
				tmp.resize(n);

				for (size_t i = 0; i < n; ++i) {
					double sum = 0.0;
					for (size_t k = 0; k < n; ++k) {
						const double angle = 2.0 * std::numbers::pi * static_cast<double>(i * k) / static_cast<double>(n);
						sum += w[k] * cosExact(angle);
					}
					tmp[i] = sum;
				}

				// Step 7: Replace w(0) with w(0)/2.
				tmp[0] *= 0.5;

				// Step 8: Append w(0) to create M-sample symmetric sequence.
				std::vector<double> cheb;
				cheb.resize(m);
				for (size_t i = 0; i < n; ++i) {
					cheb[i] = tmp[i];
				}
				cheb[m-1] = tmp[0];

				// Step 9: Normalize so that max( |w(k)| ) == 1.
				double maxVal = 0.0;
				for (size_t i = 0; i < m; ++i) {
					const double absVal = std::fabs(cheb[i]);
					if (absVal > maxVal) {
						maxVal = absVal;
					}
				}
				if (maxVal == 0.0) {
					maxVal = 1.0;
				}

				for (size_t i = 0; i < m; ++i) {
					ret[i] = Type(cheb[i] / maxVal);
				}

				return true;
			}
			catch (...) {
				return false;
			}
		}

		/**
		 * Cosine window (a.k.a. sine window).
		 * 
		 * Returns a window with a simple cosine shape:
		 * w[n] = sin( pi * n / (N-1) ),  0 <= n < N, N > 1.
		 * 
		 * \param n			Number of samples.
		 * \param ret		Returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					cosineWindow(size_t n, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n == 1) {
				return true;
			}

			double den = static_cast<double>(n - 1);
			for (size_t i = n; i--; ) {
				double v = sinExact(std::numbers::pi * static_cast<double>(i) / den);
				ret[i] = Type(v);
			}
			return true;
		}

		/**
		 * Computes Discrete Prolate Spheroidal Sequences (DPSS), similar to scipy.signal.windows.dpss().
		 * 
		 * Generates the first Kmax DPSS tapers (orders [0..(kMax-1)]) for a given sequence length and
		 * time-halfbandwidth product NW. The tapers are the eigenvectors of a symmetric tridiagonal matrix
		 * (Percival & Walden form), found here via power iteration with deflation.
		 * 
		 * \param m			Length of each window (M). 0 => No output. 1 => All windows are [1].
		 * \param nw		Time-halfbandwidth product NW (standardized half bandwidth).
		 * \param kMax		Number of windows to generate (orders 0..kMax-1). 0 => No output.
		 * \param vvRet		Returned windows. On success, resized to [kMax][m]. Each window has L2 norm 1.
		 * \param pvRatios	Optional output for associated eigenvalues (concentration-like ratios). Can be nullptr.
		 * \return			Returns true if all allocations succeeded.
		 **/
		template<typename Type = double>
		static bool					dpssWindows(size_t m, double nw, size_t kMax, std::vector<std::vector<Type>>& vvRet, std::vector<double>* pvRatios = nullptr) {
			try {
				vvRet.clear();
				if (pvRatios) {
					pvRatios->clear();
				}

				if (m == 0 || kMax == 0) {
					return true;
				}

				vvRet.resize(kMax);
				for (size_t k = 0; k < kMax; ++k) {
					vvRet[k].resize(m);
				}

				if (m == 1) {
					// Trivial 1-sample windows: all [1].
					for (size_t k = 0; k < kMax; ++k) {
						vvRet[k][0] = Type(1);
						if (pvRatios) {
							pvRatios->push_back(1.0);
						}
					}
					return true;
				}

				// ===============================
				// Build the symmetric tridiagonal matrix.
				// ===============================
				std::vector<double> diag(m);
				std::vector<double> off(m > 1 ? m - 1 : 0);

				// W = NW / M; the cosine term uses cos( 2*pi*W ) == cos( 2*pi*NW/M ).
				double cosVal = cosExact(2.0 * std::numbers::pi * nw / static_cast<double>(m));

				for (size_t i = 0; i < m; ++i) {
					double tmp = 0.5 * (static_cast<double>(m) - 2.0 * static_cast<double>(i) - 1.0);
					diag[i] = tmp * tmp * cosVal;
				}
				for (size_t i = 1; i < m; ++i) {
					// Off-diagonal entries: 0.5 * n * (M - n), n = 1..M-1.
					off[i-1] = 0.5 * static_cast<double>(i) * (static_cast<double>(m) - static_cast<double>(i));
				}

				// ===============================
				// Helper: y = A * x for symmetric tridiagonal A.
				// ===============================
				auto matVec = [&diag, &off](const std::vector<double>& inVec, std::vector<double>& outVec) {
					size_t n = diag.size();
					outVec.resize(n);
					if (n == 0) {
						return;
					}
					if (n == 1) {
						outVec[0] = diag[0] * inVec[0];
						return;
					}

					outVec[0] = diag[0] * inVec[0] + off[0] * inVec[1];
					for (size_t i = 1; i + 1 < n; ++i) {
						outVec[i] = off[i-1] * inVec[i-1] + diag[i] * inVec[i] + off[i] * inVec[i+1];
					}
					outVec[n-1] = off[n-2] * inVec[n-2] + diag[n-1] * inVec[n-1];
				};

				// ===============================
				// Power iteration with simple deflation to get kMax largest eigenpairs.
				// ===============================
				const uint32_t maxIter = 2000;
				const double tol = 1.0e-12;

				std::vector<double> cur(m);
				std::vector<double> next(m);
				std::vector<double> ax(m);
				std::vector<std::vector<double>> prevEig;
				prevEig.reserve(kMax);
				if (pvRatios) {
					pvRatios->reserve(kMax);
				}

				for (size_t k = 0; k < kMax; ++k) {
					// ---- Initial guess.
					// Start with a simple constant vector, then gently modulate for higher orders.
					for (size_t i = 0; i < m; ++i) {
						cur[i] = 1.0;
					}
					if (k > 0) {
						for (size_t i = 0; i < m; ++i) {
							double phase = std::numbers::pi * static_cast<double>(k * (2 * i + 1)) / (2.0 * static_cast<double>(m));
							cur[i] *= cosExact(phase);
						}
					}

					// Orthogonalize initial guess against previously found eigenvectors.
					for (size_t j = 0; j < prevEig.size(); ++j) {
						double dot = 0.0;
						for (size_t i = 0; i < m; ++i) {
							dot += cur[i] * prevEig[j][i];
						}
						for (size_t i = 0; i < m; ++i) {
							cur[i] -= dot * prevEig[j][i];
						}
					}

					// Normalize initial vector.
					double norm = 0.0;
					for (size_t i = 0; i < m; ++i) {
						norm += cur[i] * cur[i];
					}
					norm = std::sqrt(norm);
					if (norm == 0.0) {
						cur[0] = 1.0;
						norm = 1.0;
					}
					for (size_t i = 0; i < m; ++i) {
						cur[i] /= norm;
					}

					// ---- Power iteration loop.
					for (uint32_t iter = 0; iter < maxIter; ++iter) {
						// w = A * v.
						matVec(cur, next);

						// Deflate: remove components along earlier eigenvectors.
						for (size_t j = 0; j < prevEig.size(); ++j) {
							double dot = 0.0;
							for (size_t i = 0; i < m; ++i) {
								dot += next[i] * prevEig[j][i];
							}
							for (size_t i = 0; i < m; ++i) {
								next[i] -= dot * prevEig[j][i];
							}
						}

						// Normalize w.
						norm = 0.0;
						for (size_t i = 0; i < m; ++i) {
							norm += next[i] * next[i];
						}
						norm = std::sqrt(norm);
						if (norm == 0.0) {
							break;
						}
						for (size_t i = 0; i < m; ++i) {
							next[i] /= norm;
						}

						// Check convergence: ||w - v||_2.
						double diff = 0.0;
						for (size_t i = 0; i < m; ++i) {
							double delta = next[i] - cur[i];
							diff += delta * delta;
						}
						diff = std::sqrt(diff);
						cur.swap(next);
						if (diff < tol) {
							break;
						}
					}

					// Enforce deterministic sign: make the center sample non-negative.
					size_t centerIdx = m / 2;
					if (cur[centerIdx] < 0.0) {
						for (size_t i = 0; i < m; ++i) {
							cur[i] = -cur[i];
						}
					}

					// Compute associated eigenvalue (Rayleigh quotient).
					matVec(cur, ax);
					double lambda = 0.0;
					for (size_t i = 0; i < m; ++i) {
						lambda += cur[i] * ax[i];
					}
					if (pvRatios) {
						pvRatios->push_back(lambda);
					}

					// Store eigenvector for deflation.
					prevEig.emplace_back(m);
					for (size_t i = 0; i < m; ++i) {
						prevEig.back()[i] = cur[i];
					}

					// Copy to output (cast to requested type).
					for (size_t i = 0; i < m; ++i) {
						vvRet[k][i] = Type(cur[i]);
					}
				}

				return true;
			}
			catch (...) {
				return false;
			}
		}

		/**
		 * Exponential window.
		 * 
		 * Returns an exponential window:
		 * w[n] = exp( -|n - center| / tau ).
		 * 
		 * \param n			Number of samples.
		 * \param tau		The decay parameter tau (> 0).
		 * \param center	The center position. If < 0, the center is (n-1)/2.
		 * \param ret		Returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					exponentialWindow(size_t n, double tau, double center, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n == 1) {
				return true;
			}

			if (tau <= 0.0) {
				tau = 1.0;
			}
			if (center < 0.0 || center > static_cast<double>(n - 1)) {
				center = (static_cast<double>(n) - 1.0) * 0.5;
			}

			try {
				for (size_t i = n; i--; ) {
					double nVal = static_cast<double>(i);
					double v = std::exp(-std::fabs(nVal - center) / tau);
					ret[i] = Type(v);
				}
				return true;
			}
			catch (...) {
				return false;
			}
		}

		/**
		 * Creates a Flat-Top window.
		 * 
		 * \param n			Number of samples. Generally an odd number.
		 * \param ret		The returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					flatTopWindow(size_t n, std::vector<Type>& ret) {
			constexpr double a0 = 0.21557895;
			constexpr double a1 = 0.41663158;
			constexpr double a2 = 0.277263158;
			constexpr double a3 = 0.083578947;
			constexpr double a4 = 0.006947368;

			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n <= 1) {
				return true;
			}

			try {
				const double tau = 2.0 * std::numbers::pi;
				size_t maxIdx = ret.size() - 1;
				double invMax = 1.0 / maxIdx;
				double tauInvMax = tau * invMax;
				double tauInvMax2 = 2.0 * tauInvMax;
				double tauInvMax3 = 3.0 * tauInvMax;
				double tauInvMax4 = 4.0 * tauInvMax;
				for (size_t i = n; i--; ) {
					ret[i] = Type(a0 - a1 * cosExact(tauInvMax * i) + a2 * cosExact(tauInvMax2 * i) - a3 * cosExact(tauInvMax3 * i) + a4 * cosExact(tauInvMax4 * i));
				}

				return true;
			}
			catch (...) {
				return false;
			}
		}

		/**
		 * Gaussian window.
		 * 
		 * Returns a Gaussian window:
		 * n = 0..N-1; m = (N-1)/2
		 * w[n] = exp( -0.5 * ((n - m) / sigma)^2 ).
		 * 
		 * \param n			Number of samples.
		 * \param sigma		Standard deviation of the Gaussian in samples.
		 * \param ret		Returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					gaussianWindow(size_t n, double sigma, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n == 1) {
				return true;
			}

			if (sigma <= 0.0) {
				sigma = 1.0;
			}

			double m = (static_cast<double>(n) - 1.0) * 0.5;
			for (size_t i = n; i--; ) {
				double nVal = static_cast<double>(i) - m;
				double v = std::exp(-0.5 * (nVal / sigma) * (nVal / sigma));
				ret[i] = Type(v);
			}
			return true;
		}

		/**
		 * Generalized cosine window.
		 * 
		 * Returns a window defined by a sum of cosine terms.
		 * 
		 * \param n			Number of samples.
		 * \param aVals		Coefficients a_k for the cosine terms (a[0] + a[1] cos(...) + ...).
		 * \param ret		The returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					generalCosineWindow(size_t n, const std::vector<Type>& aVals, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n <= 1) {
				return true;
			}

			if (aVals.empty()) {
				for (size_t i = n; i--; ) {
					ret[i] = Type(1);
				}
				return true;
			}

			double step = (2.0 * std::numbers::pi) / static_cast<double>(n - 1);
			for (size_t i = n; i--; ) {
				double x = -std::numbers::pi + step * static_cast<double>(i);
				double sum = 0.0;
				for (size_t k = 0; k < aVals.size(); ++k) {
					sum += static_cast<double>(aVals[k]) * cosExact(static_cast<double>(k) * x);
				}
				ret[i] = Type(sum);
			}
			return true;
		}

		/**
		 * Generalized Gaussian window.
		 * 
		 * Returns a window with a generalized Gaussian shape:
		 * w[n] = exp( -0.5 * ((n - m) / sigma)^(2p) ).
		 * 
		 * \param n			Number of samples.
		 * \param p			Shape parameter p.
		 * \param sigma		Sigma parameter.
		 * \param ret		Returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					generalGaussianWindow(size_t n, double p, double sigma, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n == 1) {
				return true;
			}

			if (p <= 0.0) {
				p = 1.0;
			}
			if (sigma <= 0.0) {
				sigma = 1.0;
			}

			double m = (static_cast<double>(n) - 1.0) * 0.5;
			double powVal = 2.0 * p;
			for (size_t i = n; i--; ) {
				double nVal = (static_cast<double>(i) - m) / sigma;
				double absVal = std::fabs(nVal);
				double term = std::pow(absVal, powVal);
				double v = std::exp(-0.5 * term);
				ret[i] = Type(v);
			}
			return true;
		}

		/**
		 * Generalized Hamming window.
		 * 
		 * Returns a generalized Hamming window:
		 * w[n] = alpha - (1 - alpha) cos( 2*pi*n / (N-1) ).
		 * 
		 * \param n			Number of samples.
		 * \param alpha		Alpha parameter.
		 * \param ret		Returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					generalHammingWindow(size_t n, double alpha, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n == 1) {
				return true;
			}

			double den = static_cast<double>(n - 1);
			for (size_t i = n; i--; ) {
				double cosVal = cosExact(2.0 * std::numbers::pi * static_cast<double>(i) / den);
				double v = alpha - (1.0 - alpha) * cosVal;
				ret[i] = Type(v);
			}
			return true;
		}

		/**
		 * Creates a Hann window.
		 * 
		 * \param n			Number of samples. Generally an odd number.
		 * \param ret		The returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					hannWindow(size_t n, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n <= 1) {
				return true;
			}

			const double tau = 2.0 * std::numbers::pi;
			size_t maxIdx = ret.size() - 1;
			double invMax = 1.0 / maxIdx;
			double tauInvMax = tau * invMax;
			for (size_t i = n; i--; ) {
				ret[i] = Type(0.5 - 0.5 * cosExact(tauInvMax * i));
			}

			return true;
		}

		/**
		 * Creates a Hamming window.
		 * 
		 * \param n			Number of samples. Generally an odd number.
		 * \param ret		The returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					hammingWindow(size_t n, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n <= 1) {
				return true;
			}

			const double tau = 2.0 * std::numbers::pi;
			size_t maxIdx = ret.size() - 1;
			double invMax = 1.0 / maxIdx;
			double tauInvMax = tau * invMax;
			for (size_t i = n; i--; ) {
				ret[i] = Type(0.53836 - 0.46164 * cosExact(tauInvMax * i));
			}

			return true;
		}

		/**
		 * Creates a Kaiser window.
		 * 
		 * \param n			Number of samples. Generally an odd number.
		 * \param beta		The beta parameter.
		 * \param ret		The returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					kaiserWindow(size_t n, Type beta, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n <= 1) {
				return true;
			}

			double denominator = bessel0(static_cast<double>(beta));

			for (size_t i = n; i--; ) {
				double ratio = 0.0;
				if (n > 1) {
					ratio = (2.0 * i) / (n - 1) - 1.0;
				}
				double arg = beta * std::sqrt(1.0 - ratio * ratio);
				ret[i] = Type(bessel0(arg) / denominator);
			}

			return true;
		}

		/**
		 * Kaiser-Bessel derived (KBD) window.
		 * 
		 * Returns a symmetric Kaiser-Bessel derived window of length N with shape 0 -> 1 -> 0,
		 * matching scipy.signal.windows.kaiser_bessel_derived (symmetry always symmetric here).
		 * 
		 * The algorithm:
		 * Let N = n and H = ceil(N/2).
		 * 1) Build a Kaiser window k of length H.
		 * 2) Compute cumulative sum c[n] = sum_{i=0..n} k[i].
		 * 3) Normalize: h[n] = sqrt( c[n] / c[H-1] ),  n = 0..H-1.  (0 -> 1).
		 * 4) Mirror h[] to get full length N:
		 * If N is odd (N = 2H-1):
		 * w[0..H-1]   = h[0..H-1]
		 * w[H..N-1]   = h[H-2..0]
		 * If N is even (N = 2H):
		 * w[0..H-1]   = h[0..H-1]
		 * w[H..N-1]   = h[H-1..0]
		 * 
		 * \param n			Number of samples.
		 * \param beta		Beta parameter for the underlying Kaiser window.
		 * \param ret		Returned vector (size n), symmetric 0 -> 1 -> 0.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					kaiserBesselDerivedWindow(size_t n, double beta, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n <= 1) {
				return true;
			}

			try {
				const bool odd  = ((n & 1) != 0);
				const size_t half = (n + 1) / 2;        // H = ceil(N/2).

				// ---- Build Kaiser window of length half.
				std::vector<double> kaiser(half);
				const double i0Beta = bessel0(std::numbers::pi * beta);
				const size_t lenMinus1 = (half > 1 ? (half - 1) : 1);

				for (size_t i = 0; i < half; ++i) {
					double x  = (2.0 * static_cast<double>(i) / static_cast<double>(lenMinus1)) - 1.0;
					double rad = std::sqrt(std::max(0.0, 1.0 - x * x));
					double val = bessel0(std::numbers::pi * beta * rad) / i0Beta;
					kaiser[i] = val;
				}

				// ---- Cumulative sum of Kaiser.
				std::vector<double> cum(half);
				double sum = 0.0;
				for (size_t i = 0; i < half; ++i) {
					sum += kaiser[i];
					cum[i] = sum;
				}
				double norm = cum[half - 1];
				if (norm == 0.0) {
					norm = 1.0;
				}

				// ---- Half KBD window: 0 -> 1.
				std::vector<double> halfVec(half);
				for (size_t i = 0; i < half; ++i) {
					halfVec[i] = std::sqrt(cum[i] / norm);
				}

				// ---- Mirror to full symmetric window: 0 -> 1 -> 0.
				if (odd) {
					// N = 2*H - 1
					// Left + center:
					for (size_t i = 0; i < half; ++i) {
						ret[i] = Type(halfVec[i]);
					}
					// Right (mirror excluding center).
					for (size_t i = 0; i < half - 1; ++i) {
						ret[n-1-i] = Type(halfVec[i]);
					}
				}
				else {
					// N = 2*H
					// Left:
					for (size_t i = 0; i < half; ++i) {
						ret[i] = Type(halfVec[i]);
					}
					// Right (mirror including last half sample).
					for (size_t i = 0; i < half; ++i) {
						ret[n-1-i] = Type(halfVec[i]);
					}
				}

				return true;
			}
			catch (...) {
				return false;
			}
		}

		/**
		 * Creates a Lanczos window.
		 * 
		 * \param n			Number of samples. Generally an odd number.
		 * \param ret		The returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					lanczosWindow(size_t n, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n <= 1) {
				return true;
			}

			const double nMinus1 = n ? (static_cast<double>(n) - 1.0) : 0.0;
			const double half = nMinus1 / 2.0;
			for (size_t i = n; i--; ) {
				ret[i] = Type(sinc(((std::fabs(static_cast<double>(i) - half) * 2.0) / nMinus1)));
			}

			return true;
		}

		/**
		 * Creates a Nuttall window.
		 * 
		 * \param n			Number of samples. Generally an odd number.
		 * \param ret		The returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					nuttallWindow(size_t n, std::vector<Type>& ret) {
			constexpr double a0 = 0.355768;
			constexpr double a1 = 0.487396;
			constexpr double a2 = 0.144232;
			constexpr double a3 = 0.012604;

			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n <= 1) {
				return true;
			}

			const double tau = 2.0 * std::numbers::pi;
			size_t maxIdx = ret.size() - 1;
			double invMax = 1.0 / maxIdx;
			double tauInvMax = tau * invMax;
			double tauInvMax2 = 2.0 * tauInvMax;
			double tauInvMax3 = 3.0 * tauInvMax;
			for (size_t i = n; i--; ) {
				ret[i] = Type(a0 - a1 * cosExact(tauInvMax * i) + a2 * cosExact(tauInvMax2 * i) - a3 * cosExact(tauInvMax3 * i));
			}

			return true;
		}

		/**
		 * Parzen window.
		 * 
		 * Returns a Parzen (de la Vallée Poussin) window:
		 * Let m = (N-1)/2 and r = |n - m| / m.
		 * if 0 <= r <= 0.5:
		 * w = 1 - 6 r^2 + 6 r^3
		 * else if 0.5 < r <= 1:
		 * t = 1 - r
		 * w = 2 t^3
		 * else:
		 * w = 0
		 * 
		 * \param n			Number of samples.
		 * \param ret		Returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					parzenWindow(size_t n, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n == 1) {
				return true;
			}

			double m = (static_cast<double>(n) - 1.0) * 0.5;
			for (size_t i = n; i--; ) {
				double r = std::fabs(static_cast<double>(i) - m) / m;
				double v = 0.0;
				if (r <= 0.5) {
					double r2 = r * r;
					double r3 = r2 * r;
					v = 1.0 - (6.0 * r2) + (6.0 * r3);
				}
				else if (r <= 1.0) {
					double t = 1.0 - r;
					double t2 = t * t;
					double t3 = t2 * t;
					v = 2.0 * t3;
				}
				ret[i] = Type(v);
			}
			return true;
		}

		/**
		 * Generates a Taylor window.
		 *
		 * \param n			Number of samples.
		 * \param nBar		Number of nearly constant level sidelobes adjacent to the mainlobe (nbar).
		 * \param sll		Desired sidelobe level (positive, in dB) relative to the mainlobe.
		 * \param norm		If true, normalize so the maximum sample is 1.0.
		 * \param ret		The returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					taylorWindow(size_t n, int nBar, double sll, bool norm, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n == 1) {
				return true;
			}
			try {
				if (sll < 0.0) {
					sll = -sll;
				}

				constexpr double twoPi = std::numbers::pi * 2.0;
				const double nBarDouble = static_cast<double>(nBar);

				// A = acosh(10^(SLL/20)) / pi  (SLL positive).
				const double a = std::acosh(std::pow(10.0, sll / 20.0)) / std::numbers::pi;

				// sigma^2 term (often written as S^2 or similar).
				const double sp2 = (nBarDouble * nBarDouble) / (a * a + (nBarDouble - 0.5) * (nBarDouble - 0.5));

				// Precompute F_m for m = 1..nbar-1.
				std::vector<double> fm;
				fm.resize(static_cast<size_t>(nBar > 1 ? (nBar - 1) : 0));

				for (int m = 1; m < nBar; ++m) {
					const double mDouble = static_cast<double>(m);

					double num = 1.0;
					double den = 1.0;

					for (int innerN = 1; innerN < nBar; ++innerN) {
						const double innerNDouble = static_cast<double>(innerN);

						// Numerator product term.
						const double numTerm =
							1.0 - (mDouble * mDouble) / (sp2 * (a * a + (innerNDouble - 0.5) * (innerNDouble - 0.5)));
						num *= numTerm;

						// Denominator product term (exclude N == M).
						if (innerN != m) {
							const double denTerm = 1.0 - (mDouble * mDouble) / (innerNDouble * innerNDouble);
							den *= denTerm;
						}
					}

					// (-1)^(M+1) without calling std::pow().
					const double sign = (m & 1) ? 1.0 : -1.0;

					fm[static_cast<size_t>(m-1)] = (sign * num) / (2.0 * den);
				}

				// Generate window samples.
				const double halfN = 0.5 * static_cast<double>(n);

				for (size_t i = 0; i < n; ++i) {
					const double k = static_cast<double>(i);
					// Xi in [-0.5, 0.5) as per common Taylor window implementations.
					const double xi = (k - halfN + 0.5) / static_cast<double>(n);

					double sum = 0.0;
					for (int m = 1; m < nBar; ++m) {
						sum += fm[static_cast<size_t>(m-1)] *
							cosExact(twoPi * static_cast<double>(m) * xi);
					}

					const double val = 1.0 + 2.0 * sum;
					ret[i] = static_cast<Type>(val);
				}

				// Optional normalization so that max == 1.0.
				if (norm) {
					double maxVal = 0.0;
					for (size_t i = 0; i < n; ++i) {
						const double absVal = std::abs(static_cast<double>(ret[i]));
						if (absVal > maxVal) {
							maxVal = absVal;
						}
					}
					if (maxVal > 0.0) {
						const double invMax = 1.0 / maxVal;
						for (size_t i = 0; i < n; ++i) {
							ret[i] = static_cast<Type>(static_cast<double>(ret[i]) * invMax);
						}
					}
				}

				return true;
			}
			catch (...) {
				return false;
			}
		}

		/**
		 * Triangular window (SciPy's triang).
		 * 
		 * Returns a symmetric triangular window with peak 1 and endpoints > 0:
		 * center = (N-1)/2
		 * denom  = N/2
		 * w[n] = 1 - |(n - center) / denom|.
		 * 
		 * \param n			Number of samples.
		 * \param ret		Returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					triangWindow(size_t n, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n == 1) {
				return true;
			}

			double center = (static_cast<double>(n) - 1.0) * 0.5;
			double den = static_cast<double>(n) * 0.5;
			for (size_t i = n; i--; ) {
				double v = 1.0 - std::fabs((static_cast<double>(i) - center) / den);
				ret[i] = Type(v);
			}
			return true;
		}

		/**
		 * Tukey window (tapered cosine).
		 * 
		 * Returns a Tukey window with parameter alpha:
		 * alpha <= 0  -> rectangular window
		 * alpha >= 1  -> Hann window
		 * else:
		 * taper length L = alpha * (N-1)
		 * first half of taper:  0 <= n < L/2
		 * w[n] = 0.5 * (1 - cos( 2*pi*n / L ))
		 * flat region: L/2 <= n <= (N-1) - L/2
		 * w[n] = 1
		 * trailing taper: symmetric.
		 * 
		 * \param n			Number of samples.
		 * \param alpha		Alpha parameter in [0,1].
		 * \param ret		Returned vector.
		 * \return			Returns true if there was enough memory to resize the vector.
		 **/
		template <typename Type = double>
		static bool					tukeyWindow(size_t n, double alpha, std::vector<Type>& ret) {
			if (!handleTrivialWindow(n, ret)) {
				return false;
			}
			if (n == 1) {
				return true;
			}

			if (alpha <= 0.0) {
				return boxcarWindow<Type>(n, ret);
			}
			if (alpha >= 1.0) {
				// Hann window.
				double den = static_cast<double>(n - 1);
				for (size_t i = 0; i < n; ++i) {
					double v = 0.5 * (1.0 - cosExact(2.0 * std::numbers::pi * static_cast<double>(i) / den));
					ret[i] = Type(v);
				}
				return true;
			}

			double n1 = static_cast<double>(n - 1);
			double l = alpha * n1;
			double halfL = l * 0.5;
			double flatStart = halfL;
			double flatEnd = n1 - halfL;

			for (size_t i = 0; i < n; ++i) {
				double nVal = static_cast<double>(i);
				double v = 0.0;
				if (nVal < flatStart) {
					// Rising cosine.
					v = 0.5 * (1.0 - cosExact(2.0 * std::numbers::pi * nVal / l));
				}
				else if (nVal <= flatEnd) {
					// Flat region.
					v = 1.0;
				}
				else {
					// Falling cosine (symmetric).
					double nr = n1 - nVal;
					v = 0.5 * (1.0 - cosExact(2.0 * std::numbers::pi * nr / l));
				}
				ret[i] = Type(v);
			}
			return true;
		}


		// ===============================
		// DSP Filter Generation
		// ===============================
		/**
		 * Creates a windowed sinc low-pass filter. Call within a try/catch block.
		 * 
		 * \tparam Type			The type of the filter coefficients.
		 * \param hz			The input Hz.
		 * \param fc			The cut-off frequency.
		 * \param m				The size of the coefficient table to create. On output, it contains the midpoint value for the created coefficient buffer.
		 * \param windowFunc	The window function.
		 * \return				Returns the created sinc-filter coefficients.
		 * \throws				std::runtime_error on allocation or window error.
		 **/
		template <typename Type = std::vector<double>>
		static inline Type			sincFilterLpf(double hz, double fc, size_t& m, PfWindowFunc<typename Type::value_type> windowFunc = &blackmanWindow<typename Type::value_type>) {
			using ValType = typename Type::value_type;
			Type filter;
			if (fc > hz / 2.0 || hz <= 0.0) {
				filter.push_back(ValType(1.0));
				m = 0;
				return filter;
			}
			if (!(m & 1)) {
				++m;
			}
			fc /= hz;
			
			filter.resize(m);				// Can throw.
			if (!windowFunc(m, filter)) {
				throw std::runtime_error("sincFilterLpf(): Failed to apply windowing function.");
			}

			size_t l = m / 2;
			double fc2 = 2.0 * fc;
			int64_t signedL = static_cast<int64_t>(l);
			for (size_t i = m; i--; ) {
				int64_t n = static_cast<int64_t>(i) - signedL;
				filter[i] = ValType(static_cast<double>(filter[i]) * fc2 * sinc(fc2 * static_cast<double>(n)));
			}

			// Normalize.
			double sum = 0.0;
			for (auto& val : filter) {
				sum += static_cast<double>(val);
			}
			for (auto& val : filter) {
				val = ValType(static_cast<double>(val) / sum);
			}
			m = l;
			return filter;
		}

		/**
		 * Creates a windowed sinc high-pass filter. Call within a try/catch block.
		 *
		 * \tparam Type			The type of the filter coefficients.
		 * \param hz			The sample rate in Hz.
		 * \param fc			The cutoff frequency in Hz.
		 * \param m				On input, the filter width (may be adjusted to odd); on output, set to half-width.
		 * \param windowFunc	The window function pointer (defaults to Hamming).
		 * \return				Returns the created filter coefficients.
		 * \throws				std::runtime_error on allocation or window error.
		 */
		template <typename Type = std::vector<double>>
		static inline Type			sincFilterHpf(double hz, double fc, size_t& m, PfWindowFunc<typename Type::value_type> windowFunc = &blackmanWindow<typename Type::value_type>) {
			using ValType = typename Type::value_type;
			Type filter;
			if (fc > hz / 2.0 || hz <= 0.0) {
				filter.push_back(ValType(1.0));
				m = 0;
				return filter;
			}
			if (!(m & 1)) {
				++m;
			}
			fc /= hz;

			filter.resize(m);
			if (!windowFunc(m, filter)) {
				throw std::runtime_error("sincFilterHpf(): Failed to apply windowing function.");
			}

			size_t l = m / 2;
			double fc2 = 2.0 * fc;
			int64_t signedL = static_cast<int64_t>(l);
			for (size_t i = m; i--; ) {
				int64_t n = static_cast<int64_t>(i) - signedL;
				if (n == 0) {
					// Center tap for HPF
					filter[i] = ValType(static_cast<double>(filter[i]) * (1.0 - fc2));
				}
				else {
					filter[i] = ValType(static_cast<double>(filter[i]) * (-fc2 * sinc(fc2 * static_cast<double>(n))));
				}
			}

			// Normalize.
			double sum = 0.0;
			for (auto& val : filter) {
				sum += static_cast<double>(val);
			}
			for (auto& val : filter) {
				val = ValType(static_cast<double>(val) / sum);
			}
			m = l;
			return filter;
		}

		/**
		 * Creates a windowed sinc band-pass filter. Call within a try/catch block.
		 *
		 * \tparam Type			The type of the filter coefficients.
		 * \param hz			The sample rate in Hz.
		 * \param f1			The low cutoff frequency in Hz.
		 * \param f2			The high cutoff frequency in Hz.
		 * \param m				On input, the filter width (may be adjusted to odd); on output, set to half-width (midpoint index).
		 * \param windowFunc	The window function pointer (defaults to Hamming).
		 * \return				Returns the created band-pass sinc-filter coefficients.
		 * \throws				std::runtime_error on allocation or window error.
		 **/
		template <typename Type = std::vector<double>>
		static inline Type			sincFilterBpf(double hz, double f1, double f2, size_t& m, PfWindowFunc<typename Type::value_type> windowFunc = &blackmanWindow<typename Type::value_type>) {
			using ValType = typename Type::value_type;
			Type filter;
			if (hz <= 0.0 || f1 >= f2 || f2 > hz * 0.5 || f1 < 0.0) {
				filter.push_back(ValType(1.0));
				m = 0;
				return filter;
			}

			if (!(m & 1)) {
				++m;
			}

			double f1n = f1 / hz;
			double f2n = f2 / hz;

			filter.resize(m);
			if (!windowFunc(m, filter)) {
				throw std::runtime_error("sincFilterBpf(): Failed to apply windowing function.");
			}

			size_t l = m / 2;
			double f12 = 2.0 * f1n;
			double f22 = 2.0 * f2n;
			int64_t signedL = static_cast<int64_t>(l);

			// Build band-pass by subtracting two low-pass responses.
			for (size_t i = m; i--; ) {
				int64_t n = static_cast<int64_t>(i) - signedL;
				if (n == 0) {
					// Center tap: difference of DC gains.
					filter[i] = ValType(static_cast<double>(filter[i]) * (f22 - f12));
				}
				else {
					// Off-center taps: difference of sinc kernels.
					double nDouble = static_cast<double>(n);
					double lo = f12 * sinc(f12 * nDouble);
					double hi = f22 * sinc(f22 * nDouble);
					filter[i] = ValType(static_cast<double>(filter[i]) * (hi - lo));
				}
			}

			// Normalize.
			double sum = 0.0;
			for (auto& val : filter) {
				sum += static_cast<double>(val);
			}
			for (auto& val : filter) {
				val = ValType(static_cast<double>(val) / sum);
			}

			m = l;
			return filter;
		}


		// ===============================
		// Signal Analysis & Measurement
		// ===============================
		/**
		 * Calculates a "gated" AC-RMS: subtracts DC and only counts samples above a threshold.
		 *
		 * \param samples		The input samples.
		 * \param threshold		The absolute amplitude gate; samples with |x-mean| < threshold are ignored.
		 * \return				The computed gated RMS; zero if no samples exceed threshold.
		 * \throws				std::runtime_error if samples is empty.
		 */
		template <typename Type = std::vector<double>>
		static inline double		calcRmsGated(const Type& samples, double threshold) {
			if (samples.empty()) {
				return 0.0;
			}

			// Remove DC.
			double mean = 0.0;
			for (size_t i = samples.size(); i--; ) {
				mean += static_cast<double>(samples[i]);
			}
			mean /= static_cast<double>(samples.size());

			// Accumulate only above threshold.
			double sumSq = 0.0;
			size_t count = 0;
			for (size_t i = samples.size(); i--; ) {
				double centered = static_cast<double>(samples[i]) - mean;
				if (std::abs(centered) >= threshold) {
					sumSq += centered * centered;
					++count;
				}
			}
			if (count == 0) {
				return 0.0;
			}

			double meanSq = sumSq / static_cast<double>(count);
			return std::sqrt(meanSq);
		}

		/**
		 * Computes the normalized magnitude response |H(f)| at a given frequency.
		 * 
		 * Note: This mathematical formulation computes the Dirichlet kernel (the frequency response 
		 * of a moving average / rectangular window), not an ideal low-pass sinc filter.
		 * 
		 * \param sampleHz		Sampling rate Fs (Hz).
		 * \param freqHz		Frequency at which to evaluate (Hz).
		 * \param m				Number of taps (must be odd).
		 * \return				Returns |H(f)| normalized so H(0)=1.
		 **/
		static inline double		sincFilterResponse(double sampleHz, double freqHz, size_t m) {
			if (sampleHz == 0.0 || m == 0) {
				return 0.0;
			}

			// Floating-point inaccuracy in std::sin(PI) bypasses absolute epsilon checks.
			// We mathematically check if the frequency ratio is an integer multiple of the sample rate.
			double ratio = freqHz / sampleHz;
			double omega = 2.0 * std::numbers::pi * ratio;
			double halfOmega = omega * 0.5;
			
			double num = sinExact(static_cast<double>(m) * halfOmega);
			double den = static_cast<double>(m) * sinExact(halfOmega);

			return std::fabs(num / den);
		}


		// ===============================
		// Audio Utilities
		// ===============================
		/**
		 * Converts a sample from a floating-point format to a uint8_t. 8-bit PCM data is expressed as an unsigned value over the range 0 to 255, 128 being an
		 *	audio output level of zero.
		 *
		 * \param sample	The sample to convert.
		 * \return			Returns the converted sample.
		 **/
		template <typename Type>
		static inline uint8_t		sampleToUi8(Type sample) {
			double clampedSample;
			if (sample < Type(-1.0)) {
				clampedSample = -1.0;
			}
			else if (sample > Type(1.0)) {
				clampedSample = 1.0;
			}
			else {
				clampedSample = static_cast<double>(sample);
			}
			
			double scaledSample = (clampedSample + 1.0) * 0.5 * 255.0;
			return static_cast<uint8_t>(std::round(scaledSample));
		}

		/**
		 * Converts a sample from a floating-point format to an int16_t. 16-bit PCM data is expressed as a signed value over the
		 *	range -32768 to 32767, 0 being an audio output level of zero. Note that both -32768 and -32767 are -1.0; a proper
		 *	conversion never generates -32768.
		 *
		 * \param sample	The sample to convert.
		 * \return			Returns the converted sample.
		 **/
		template <typename Type>
		static inline int16_t		sampleToI16(Type sample) {
			double clampedSample;
			if (sample < Type(-1.0)) {
				clampedSample = -1.0;
			}
			else if (sample > Type(1.0)) {
				clampedSample = 1.0;
			}
			else {
				clampedSample = static_cast<double>(sample);
			}
			
			double scaledSample = clampedSample * 32767.0;
			return static_cast<int16_t>(std::round(scaledSample));
		}

		/**
		 * Converts a sample from a floating-point format to an int16_t while applying error-diffusion dithering. 16-bit PCM data is expressed as a signed value over the
		 *	range -32768 to 32767, 0 being an audio output level of zero. Note that both -32768 and -32767 are -1.0; a proper
		 *	conversion never generates -32768.
		 * 
		 * \param sample	The sample to convert.
		 * \param error		The running error state.
		 * \return			Returns the converted sample.
		 **/
		template <typename Type>
		static inline int16_t		sampleToI16Dither(Type sample, Type& error) {
			double thisVal = static_cast<double>(sample) + static_cast<double>(error);
			if (thisVal < -1.0) {
				thisVal = -1.0;
			}
			else if (thisVal > 1.0) {
				thisVal = 1.0;
			}
		
			int16_t finalVal = static_cast<int16_t>(std::round(thisVal * 32767.0));

			double scaled = static_cast<double>(finalVal);
			double quantized = scaled * (1.0 / 32767.0);
			error = static_cast<Type>(thisVal - quantized);

			return finalVal;
		}
		
		/**
		 * Converts a sample from a floating-point format to an int32_t. 24-bit PCM data is expressed as a signed value over the
		 *	range -8388608 to 8388607, 0 being an audio output level of zero. Note that both -8388608 and -8388607 are -1.0; a proper
		 *	conversion never generates -8388608.
		 *
		 * \param sample	The sample to convert.
		 * \return			Returns the converted sample.
		 **/
		template <typename Type>
		static inline int32_t		sampleToI24(Type sample) {
			double clampedSample;
			if (sample < Type(-1.0)) {
				clampedSample = -1.0;
			}
			else if (sample > Type(1.0)) {
				clampedSample = 1.0;
			}
			else {
				clampedSample = static_cast<double>(sample);
			}
			
			double scaledSample = clampedSample * 8388607.0;
			return static_cast<int32_t>(std::round(scaledSample));
		}

		/**
		 * Converts a sample from a floating-point format to an int32_t. 32-bit PCM data is expressed as a signed value over the
		 *	range -2147483648 to 2147483647, 0 being an audio output level of zero. Note that both -2147483648 and -2147483647 are -1.0; a proper
		 *	conversion never generates -2147483648.
		 *
		 * \param sample	The sample to convert.
		 * \return			Returns the converted sample.
		 **/
		template <typename Type>
		static inline int32_t		sampleToI32(Type sample) {
			double clampedSample;
			if (sample < Type(-1.0)) {
				clampedSample = -1.0;
			}
			else if (sample > Type(1.0)) {
				clampedSample = 1.0;
			}
			else {
				clampedSample = static_cast<double>(sample);
			}
			
			double scaledSample = clampedSample * 2147483647.0;
			return static_cast<int32_t>(std::round(scaledSample));
		}

		/**
		 * Gets the volume of a sample using Audacity's Studio Fade Out routine.
		 * 
		 * \param fraction	The amount of fade to apply from 0 to 1.
		 * \return			Returns the fade amount from 1 to 0 as fraction goes from 0 to 1.
		 **/
		template <typename Type = float>
		static inline Type			studioFadeOut(Type fraction) {
			if (fraction <= Type(0.0)) {
				return Type(1.0);
			}
			if (fraction >= Type(1.0) || std::isnan(fraction)) {
				return Type(0.0);
			}

			return Type(1.0) - (Type(3.0) * fraction * fraction - Type(2.0) * fraction * fraction * fraction);
		}


		// ===============================
		// Audio Interpolation
		// ===============================
		/**
		 * 4-point, 3rd-order Hermite X-form sampling.
		 * 
		 * \param samples		The array of 4 input samples, indices -1, 0, 1, and 2.
		 * \param frac			The interpolation amount.
		 * \return				Returns the interpolated point.
		 **/
		template <typename Type>
		static inline Type			sample4Point3rdOrderHermiteX(const Type* samples, Type frac) {
			Type c0 = samples[0+1];
			Type c1 = static_cast<Type>(1.0 / 2.0) * (samples[1+1] - samples[-1+1]);
			Type c2 = samples[-1+1] - static_cast<Type>(5.0 / 2.0) * samples[0+1] + static_cast<Type>(2.0) * samples[1+1] - static_cast<Type>(1.0 / 2.0) * samples[2+1];
			Type c3 = static_cast<Type>(1.0 / 2.0) * (samples[2+1] - samples[-1+1]) + static_cast<Type>(3.0 / 2.0) * (samples[0+1] - samples[1+1]);
			
			return ((c3 * frac + c2) * frac + c1) * frac + c0;
		}

		/**
		 * 6-point, 5th-order Hermite X-form sampling.
		 * 
		 * \param samples		The array of 6 input samples, indices -2, -1, 0, 1, 2, and 3.
		 * \param frac			The interpolation amount.
		 * \return				Returns the interpolated point.
		 **/
		template <typename Type>
		static inline Type			sample6Point5thOrderHermiteX(const Type* samples, Type frac) {
			Type eightThym2 = static_cast<Type>(1.0 / 8.0) * samples[-2+2];
			Type elevenTwentyFourThy2 = static_cast<Type>(11.0 / 24.0) * samples[2+2];
			Type twelvThy3 = static_cast<Type>(1.0 / 12.0) * samples[3+2];
			
			Type c0 = samples[0+2];
			Type c1 = static_cast<Type>(1.0 / 12.0) * (samples[-2+2] - samples[2+2]) + static_cast<Type>(2.0 / 3.0) * (samples[1+2] - samples[-1+2]);
			Type c2 = static_cast<Type>(13.0 / 12.0) * samples[-1+2] - static_cast<Type>(25.0 / 12.0) * samples[0+2] + static_cast<Type>(3.0 / 2.0) * samples[1+2] -
				elevenTwentyFourThy2 + twelvThy3 - eightThym2;
			Type c3 = static_cast<Type>(5.0 / 12.0) * samples[0+2] - static_cast<Type>(7.0 / 12.0) * samples[1+2] + static_cast<Type>(7.0 / 24.0) * samples[2+2] -
				static_cast<Type>(1.0 / 24.0) * (samples[-2+2] + samples[-1+2] + samples[3+2]);
			Type c4 = eightThym2 - static_cast<Type>(7.0 / 12.0) * samples[-1+2] + static_cast<Type>(13.0 / 12.0) * samples[0+2] - samples[1+2] +
				elevenTwentyFourThy2 - twelvThy3;
			Type c5 = static_cast<Type>(1.0 / 24.0) * (samples[3+2] - samples[-2+2]) + static_cast<Type>(5.0 / 24.0) * (samples[-1+2] - samples[2+2]) +
				static_cast<Type>(5.0 / 12.0) * (samples[1+2] - samples[0+2]);
				
			return ((((c5 * frac + c4) * frac + c3) * frac + c2) * frac + c1) * frac + c0;
		}

		/**
		 * 6-point, 4th-order optimal 2x z-form sampling.
		 * 
		 * \param samples		The array of 6 input samples, indices -2, -1, 0, 1, 2, and 3.
		 * \param frac			The interpolation amount.
		 * \return				Returns the interpolated point.
		 **/
		template <typename Type>
		static inline Type			sample6Point4thOrder2XZ(const Type* samples, Type frac) {
			Type z = frac - static_cast<Type>(0.5);
			Type even1 = samples[-2+2] + samples[3+2];
			Type odd1 = samples[-2+2] - samples[3+2];
			Type even2 = samples[-1+2] + samples[2+2];
			Type odd2 = samples[-1+2] - samples[2+2];
			Type even3 = samples[0+2] + samples[1+2];
			Type odd3 = samples[0+2] - samples[1+2];
			
			Type c0 = even1 * static_cast<Type>(0.37484203669443822) + even2 * static_cast<Type>(0.11970939637439368)
				+ even3 * static_cast<Type>(0.00544862268096358);
			Type c1 = odd1 * static_cast<Type>(0.19253897284651597) + odd2 * static_cast<Type>(0.22555179040018719)
				+ odd3 * static_cast<Type>(0.02621377625620669);
			Type c2 = even1 * static_cast<Type>(-0.154026006475653071) + even2 * static_cast<Type>(0.10546111301131367)
				+ even3 * static_cast<Type>(0.04856757454258609);
			Type c3 = odd1 * static_cast<Type>(-0.06523685579716083) + odd2 * static_cast<Type>(-0.04867197815057284)
				+ odd3 * static_cast<Type>(0.04200764942718964);
			Type c4 = even1 * static_cast<Type>(0.03134095684084392) + even2 * static_cast<Type>(-0.04385804833432710)
				+ even3 * static_cast<Type>(0.01249475765486819);
				
			return (((c4 * z + c3) * z + c2) * z + c1) * z + c0;
		}

		/**
		 * 6-point, 4th-order optimal 4x z-form sampling.
		 * 
		 * \param samples		The array of 6 input samples, indices -2, -1, 0, 1, 2, and 3.
		 * \param frac			The interpolation amount.
		 * \return				Returns the interpolated point.
		 **/
		template <typename Type>
		static inline Type			sample6Point4thOrder4XZ(const Type* samples, Type frac) {
			Type z = frac - static_cast<Type>(0.5);
			Type even1 = samples[-2+2] + samples[3+2];
			Type odd1 = samples[-2+2] - samples[3+2];
			Type even2 = samples[-1+2] + samples[2+2];
			Type odd2 = samples[-1+2] - samples[2+2];
			Type even3 = samples[0+2] + samples[1+2];
			Type odd3 = samples[0+2] - samples[1+2];
			
			Type c0 = even1 * static_cast<Type>(0.26148143200222657) + even2 * static_cast<Type>(0.22484494681472966)
				+ even3 * static_cast<Type>(0.01367360612950508);
			Type c1 = odd1 * static_cast<Type>(-0.20245593827436142) + odd2 * static_cast<Type>(0.29354348112881601)
				+ odd3 * static_cast<Type>(0.06436924057941607);
			Type c2 = even1 * static_cast<Type>(-0.022982104451679701) + even2 * static_cast<Type>(-0.09068617668887535)
				+ even3 * static_cast<Type>(0.11366875749521399);
			Type c3 = odd1 * static_cast<Type>(0.36296419678970931) + odd2 * static_cast<Type>(-0.26421064520663945)
				+ odd3 * static_cast<Type>(0.08591542869416055);
			Type c4 = even1 * static_cast<Type>(0.02881527997393852) + even2 * static_cast<Type>(-0.04250898918476453)
				+ even3 * static_cast<Type>(0.01369173779618459);
				
			return (((c4 * z + c3) * z + c2) * z + c1) * z + c0;
		}

		/**
		 * 6-point, 5th-order optimal 32x z-form sampling.
		 * 
		 * \param samples		The array of 6 input samples, indices -2, -1, 0, 1, 2, and 3.
		 * \param frac			The interpolation amount.
		 * \return				Returns the interpolated point.
		 **/
		template <typename Type>
		static inline Type			sample6Point5thOrder32XZ(const Type* samples, Type frac) {
			Type z = frac - static_cast<Type>(0.5);
			Type even1 = samples[1+2] + samples[0+2];
			Type odd1 = samples[1+2] - samples[0+2];
			Type even2 = samples[2+2] + samples[-1+2];
			Type odd2 = samples[2+2] - samples[-1+2];
			Type even3 = samples[3+2] + samples[-2+2];
			Type odd3 = samples[3+2] - samples[-2+2];
			
			Type c0 = even1 * static_cast<Type>(0.42685983409379380) + even2 * static_cast<Type>(0.07238123511170030)
				+ even3 * static_cast<Type>(0.00075893079450573);
			Type c1 = odd1 * static_cast<Type>(0.35831772348893259) + odd2 * static_cast<Type>(0.20451644554758297)
				+ odd3 * static_cast<Type>(0.00562658797241955);
			Type c2 = even1 * static_cast<Type>(-0.217009177221292431) + even2 * static_cast<Type>(0.20051376594086157)
				+ even3 * static_cast<Type>(0.01649541128040211);
			Type c3 = odd1 * static_cast<Type>(-0.25112715343740988) + odd2 * static_cast<Type>(0.04223025992200458)
				+ odd3 * static_cast<Type>(0.02488727472995134);
			Type c4 = even1 * static_cast<Type>(0.04166946673533273) + even2 * static_cast<Type>(-0.06250420114356986)
				+ even3 * static_cast<Type>(0.02083473440841799);
			Type c5 = odd1 * static_cast<Type>(0.08349799235675044) + odd2 * static_cast<Type>(-0.04174912841630993)
				+ odd3 * static_cast<Type>(0.00834987866042734);
				
			return ((((c5 * z + c4) * z + c3) * z + c2) * z + c1) * z + c0;
		}

		/**
		 * 4-point, 2nd-order parabolic 2x x-form sampling.
		 * 
		 * \param samples		The array of 6 input samples, indices -2, -1, 0, 1, 2, and 3.
		 * \param frac			The interpolation amount.
		 * \return				Returns the interpolated point.
		 **/
		template <typename Type>
		static inline Type			sample4Point2ndOrderParabolic2XX(const Type* samples, Type frac) {
			Type y1mM1 = samples[1+2] - samples[-1+2];
			Type c0 = static_cast<Type>(1.0 / 2.0) * samples[0+2] + static_cast<Type>(1.0 / 4.0) * (samples[-1+2] + samples[1+2]);
			Type c1 = static_cast<Type>(1.0 / 2.0) * y1mM1;
			Type c2 = static_cast<Type>(1.0 / 4.0) * (samples[2+2] - samples[0+2] - y1mM1);
			
			return (c2 * frac + c1) * frac + c0;
		}

	protected :

	private :
	};

}	// namespace ve
