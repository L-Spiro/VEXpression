#pragma once

#include <cmath>

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(_MSC_VER) && defined(_M_AMD64)

	/**
	 * Computes the sine and cosine of an angle in radians.
	 *
	 * MSVC x64 builds use a MASM implementation.
	 *
	 * \param radians	Angle in radians.
	 * \param outSin	Receives sin(radians). Must be non-null.
	 * \param outCos	Receives cos(radians). Must be non-null.
	 **/
	extern void 		sinCos(double radians, double* outSin, double* outCos);

	/**
	 * Computes the sine and cosine of an angle in radians (single-precision).
	 *
	 * MSVC x64 builds use a MASM implementation.
	 *
	 * \param angle		Angle in radians.
	 * \param outSin	Receives sin(angle). Must be non-null.
	 * \param outCos	Receives cos(angle). Must be non-null.
	 **/
	extern void 		sinCosF(float angle, float* outSin, float* outCos);

#elif defined(_MSC_VER) && defined(_M_IX86)

	/**
	 * Computes the sine and cosine of an angle in radians.
	 *
	 * MSVC x86 builds use inline x87 assembly (FSINCOS).
	 *
	 * \param radians	Angle in radians.
	 * \param outSin	Receives sin(radians). Must be non-null.
	 * \param outCos	Receives cos(radians). Must be non-null.
	 **/
	inline void 		sinCos(double radians, double* outSin, double* outCos) {
		double dSin, dCos;
		__asm {
			fld QWORD PTR[radians]
			fsincos
			fstp QWORD PTR[dCos]
			fstp QWORD PTR[dSin]
			fwait
		}
		(*outSin) = dSin;
		(*outCos) = dCos;
	}

	/**
	 * Computes the sine and cosine of an angle in radians (single-precision).
	 *
	 * MSVC x86 builds use inline x87 assembly (FSINCOS).
	 *
	 * \param angle		Angle in radians.
	 * \param outSin	Receives sin(angle). Must be non-null.
	 * \param outCos	Receives cos(angle). Must be non-null.
	 **/
	inline void 		sinCosF(float angle, float* outSin, float* outCos) {
		float fSinT, fCosT;
		__asm {
			fld DWORD PTR[angle]
			fsincos
			fstp DWORD PTR[fCosT]
			fstp DWORD PTR[fSinT]
			fwait
		}
		(*outSin) = fSinT;
		(*outCos) = fCosT;
	}

#elif defined(__linux__)

	/**
	 * Computes the sine and cosine of an angle in radians.
	 *
	 * Linux builds use the GNU extension ::sincos() from <math.h>.
	 *
	 * \param radians	Angle in radians.
	 * \param outSin	Receives sin(radians). Must be non-null.
	 * \param outCos	Receives cos(radians). Must be non-null.
	 **/
	inline void 		sinCos(double radians, double* outSin, double* outCos) {
		::sincos(radians, outSin, outCos);
	}

	/**
	 * Computes the sine and cosine of an angle in radians (single-precision).
	 *
	 * Linux builds use the GNU extension ::sincosf() from <math.h>.
	 *
	 * \param angle		Angle in radians.
	 * \param outSin	Receives sin(angle). Must be non-null.
	 * \param outCos	Receives cos(angle). Must be non-null.
	 **/
	inline void 		sinCosF(float angle, float* outSin, float* outCos) {
		::sincosf(angle, outSin, outCos);
	}

#else

	/**
	 * Computes the sine and cosine of an angle in radians.
	 *
	 * On Apple/Clang/GCC, attempts to call the platform/libm combined
	 * implementation when available; otherwise falls back to std::sin/std::cos.
	 *
	 * \param radians	Angle in radians.
	 * \param outSin	Receives sin(radians). Must be non-null.
	 * \param outCos	Receives cos(radians). Must be non-null.
	 **/
	inline void 		sinCos(double radians, double* outSin, double* outCos) {
#if defined(__APPLE__) || defined(__GNUC__) || defined(__clang__)
		::__sincos(radians, outSin, outCos);
#else
		(*outSin) = std::sin(radians);
		(*outCos) = std::cos(radians);
#endif
	}

	/**
	 * Computes the sine and cosine of an angle in radians (single-precision).
	 *
	 * On Apple/Clang/GCC, attempts to call the platform/libm combined
	 * implementation when available; otherwise falls back to std::sinf/std::cosf.
	 *
	 * \param angle		Angle in radians.
	 * \param outSin	Receives sin(angle). Must be non-null.
	 * \param outCos	Receives cos(angle). Must be non-null.
	 **/
	inline void 		sinCosF(float angle, float* outSin, float* outCos) {
#if defined(__APPLE__) || defined(__GNUC__) || defined(__clang__)
		::__sincosf(angle, outSin, outCos);
#else
		(*outSin) = std::sinf(angle);
		(*outCos) = std::cosf(angle);
#endif
	}

#endif

#if defined(__cplusplus)
} // extern "C"
#endif
