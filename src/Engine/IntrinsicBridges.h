#pragma once

#include "Result.h"

#include <bit>
#include <cmath>
#include <numbers>
#include <vector>

namespace ve {

	/**
	 * A collection of static bridge callbacks mapping the engine's Result array directly to C++ intrinsics.
	 **/
	class IntrinsicBridges {
	public :
		// =========================================================================
		// Core Math
		// =========================================================================

		/**
		 * Bridge for std::pow (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		powBridge(const std::vector<Result>& args) {
			return Result::make(std::pow(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::powf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		powfBridge(const std::vector<Result>& args) {
			return Result::make(std::powf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::sin (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		sinBridge(const std::vector<Result>& args) {
			return Result::make(std::sin(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::sinf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		sinfBridge(const std::vector<Result>& args) {
			return Result::make(std::sinf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::cos (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		cosBridge(const std::vector<Result>& args) {
			return Result::make(std::cos(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::cosf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		cosfBridge(const std::vector<Result>& args) {
			return Result::make(std::cosf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::tan (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		tanBridge(const std::vector<Result>& args) {
			return Result::make(std::tan(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::tanf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		tanfBridge(const std::vector<Result>& args) {
			return Result::make(std::tanf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::asin (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		asinBridge(const std::vector<Result>& args) {
			return Result::make(std::asin(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::asinf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		asinfBridge(const std::vector<Result>& args) {
			return Result::make(std::asinf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::acos (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		acosBridge(const std::vector<Result>& args) {
			return Result::make(std::acos(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::acosf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		acosfBridge(const std::vector<Result>& args) {
			return Result::make(std::acosf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::atan (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		atanBridge(const std::vector<Result>& args) {
			return Result::make(std::atan(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::atanf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		atanfBridge(const std::vector<Result>& args) {
			return Result::make(std::atanf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::atan2 (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		atan2Bridge(const std::vector<Result>& args) {
			return Result::make(std::atan2(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::atan2f (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		atan2fBridge(const std::vector<Result>& args) {
			return Result::make(std::atan2f(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::exp (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		expBridge(const std::vector<Result>& args) {
			return Result::make(std::exp(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::expf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		expfBridge(const std::vector<Result>& args) {
			return Result::make(std::expf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::log (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		logBridge(const std::vector<Result>& args) {
			return Result::make(std::log(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::logf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		logfBridge(const std::vector<Result>& args) {
			return Result::make(std::logf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::log10 (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		log10Bridge(const std::vector<Result>& args) {
			return Result::make(std::log10(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::log10f (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		log10fBridge(const std::vector<Result>& args) {
			return Result::make(std::log10f(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::sqrt (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		sqrtBridge(const std::vector<Result>& args) {
			return Result::make(std::sqrt(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::sqrtf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		sqrtfBridge(const std::vector<Result>& args) {
			return Result::make(std::sqrtf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::cbrt (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		cbrtBridge(const std::vector<Result>& args) {
			return Result::make(std::cbrt(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::cbrtf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		cbrtfBridge(const std::vector<Result>& args) {
			return Result::make(std::cbrtf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::ceil (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		ceilBridge(const std::vector<Result>& args) {
			return Result::make(std::ceil(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::ceilf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		ceilfBridge(const std::vector<Result>& args) {
			return Result::make(std::ceilf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::floor (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		floorBridge(const std::vector<Result>& args) {
			return Result::make(std::floor(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::floorf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		floorfBridge(const std::vector<Result>& args) {
			return Result::make(std::floorf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::abs (integer overload resolved through std::abs on double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		absBridge(const std::vector<Result>& args) {
			return Result::make(std::abs(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::fabs (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fabsBridge(const std::vector<Result>& args) {
			return Result::make(std::fabs(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::fabsf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fabsfBridge(const std::vector<Result>& args) {
			return Result::make(std::fabsf(static_cast<float>(args[0].value.doubleVal)));
		}


		// =========================================================================
		// Hyperbolic Functions
		// =========================================================================

		/**
		 * Bridge for std::cosh.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		coshBridge(const std::vector<Result>& args) {
			return Result::make(std::cosh(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::coshf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		coshfBridge(const std::vector<Result>& args) {
			return Result::make(std::coshf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::sinh.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		sinhBridge(const std::vector<Result>& args) {
			return Result::make(std::sinh(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::sinhf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		sinhfBridge(const std::vector<Result>& args) {
			return Result::make(std::sinhf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::tanh.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		tanhBridge(const std::vector<Result>& args) {
			return Result::make(std::tanh(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::tanhf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		tanhfBridge(const std::vector<Result>& args) {
			return Result::make(std::tanhf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::acosh.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		acoshBridge(const std::vector<Result>& args) {
			return Result::make(std::acosh(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::acoshf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		acoshfBridge(const std::vector<Result>& args) {
			return Result::make(std::acoshf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::asinh.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		asinhBridge(const std::vector<Result>& args) {
			return Result::make(std::asinh(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::asinhf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		asinhfBridge(const std::vector<Result>& args) {
			return Result::make(std::asinhf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::atanh.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		atanhBridge(const std::vector<Result>& args) {
			return Result::make(std::atanh(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::atanhf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		atanhfBridge(const std::vector<Result>& args) {
			return Result::make(std::atanhf(static_cast<float>(args[0].value.doubleVal)));
		}


		// =========================================================================
		// Exponents & Logs
		// =========================================================================

		/**
		 * Bridge for std::log2.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		log2Bridge(const std::vector<Result>& args) {
			return Result::make(std::log2(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::log2f.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		log2fBridge(const std::vector<Result>& args) {
			return Result::make(std::log2f(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::exp2.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		exp2Bridge(const std::vector<Result>& args) {
			return Result::make(std::exp2(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::exp2f.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		exp2fBridge(const std::vector<Result>& args) {
			return Result::make(std::exp2f(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::expm1.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		expm1Bridge(const std::vector<Result>& args) {
			return Result::make(std::expm1(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::expm1f.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		expm1fBridge(const std::vector<Result>& args) {
			return Result::make(std::expm1f(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::ilogb.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		ilogbBridge(const std::vector<Result>& args) {
			return Result::make(static_cast<int64_t>(std::ilogb(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::ilogbf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		ilogbfBridge(const std::vector<Result>& args) {
			return Result::make(static_cast<int64_t>(std::ilogbf(static_cast<float>(args[0].value.doubleVal))));
		}

		/**
		 * Bridge for std::log1p.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		log1pBridge(const std::vector<Result>& args) {
			return Result::make(std::log1p(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::log1pf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		log1pfBridge(const std::vector<Result>& args) {
			return Result::make(std::log1pf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::logb.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		logbBridge(const std::vector<Result>& args) {
			return Result::make(std::logb(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::logbf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		logbfBridge(const std::vector<Result>& args) {
			return Result::make(std::logbf(static_cast<float>(args[0].value.doubleVal)));
		}


		// =========================================================================
		// Miscellaneous Math
		// =========================================================================

		/**
		 * Bridge for std::hypot.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		hypotBridge(const std::vector<Result>& args) {
			return Result::make(std::hypot(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::hypotf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		hypotfBridge(const std::vector<Result>& args) {
			return Result::make(std::hypotf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::tgamma.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		tgammaBridge(const std::vector<Result>& args) {
			return Result::make(std::tgamma(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::tgammaf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		tgammafBridge(const std::vector<Result>& args) {
			return Result::make(std::tgammaf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::lgamma.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		lgammaBridge(const std::vector<Result>& args) {
			return Result::make(std::lgamma(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::lgammaf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		lgammafBridge(const std::vector<Result>& args) {
			return Result::make(std::lgammaf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::fmod (also mapped to 'mod').
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fmodBridge(const std::vector<Result>& args) {
			return Result::make(std::fmod(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::fmodf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fmodfBridge(const std::vector<Result>& args) {
			return Result::make(std::fmodf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::trunc.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		truncBridge(const std::vector<Result>& args) {
			return Result::make(std::trunc(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::truncf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		truncfBridge(const std::vector<Result>& args) {
			return Result::make(std::truncf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::round.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		roundBridge(const std::vector<Result>& args) {
			return Result::make(std::round(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::roundf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		roundfBridge(const std::vector<Result>& args) {
			return Result::make(std::roundf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::nearbyint.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		nearbyintBridge(const std::vector<Result>& args) {
			return Result::make(std::nearbyint(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::nearbyintf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		nearbyintfBridge(const std::vector<Result>& args) {
			return Result::make(std::nearbyintf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::remainder.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		remainderBridge(const std::vector<Result>& args) {
			return Result::make(std::remainder(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::remainderf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		remainderfBridge(const std::vector<Result>& args) {
			return Result::make(std::remainderf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::remquo.
		 * TODO: Will be updated to return a tuple instead of using pointer arguments.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function (quotient is currently discarded).
		 **/
		static Result		remquoBridge(const std::vector<Result>& args) {
			int dummyQuo;
			return Result::make(std::remquo(args[0].value.doubleVal, args[1].value.doubleVal, &dummyQuo));
		}

		/**
		 * Bridge for std::remquof.
		 * TODO: Will be updated to return a tuple instead of using pointer arguments.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function (quotient is currently discarded).
		 **/
		static Result		remquofBridge(const std::vector<Result>& args) {
			int dummyQuo;
			return Result::make(std::remquo(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal), &dummyQuo));
		}

		/**
		 * Bridge for std::nextafter.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		nextafterBridge(const std::vector<Result>& args) {
			return Result::make(std::nextafter(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::nextafterf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		nextafterfBridge(const std::vector<Result>& args) {
			return Result::make(std::nextafterf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::nexttoward.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		nexttowardBridge(const std::vector<Result>& args) {
			return Result::make(std::nexttoward(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::nexttowardf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		nexttowardfBridge(const std::vector<Result>& args) {
			return Result::make(std::nexttowardf(static_cast<float>(args[0].value.doubleVal), args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::fdim (also mapped to 'dim').
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fdimBridge(const std::vector<Result>& args) {
			return Result::make(std::fdim(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::fdimf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fdimfBridge(const std::vector<Result>& args) {
			return Result::make(std::fdimf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::fmax (also mapped to 'max').
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fmaxBridge(const std::vector<Result>& args) {
			return Result::make(std::fmax(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::fmaxf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fmaxfBridge(const std::vector<Result>& args) {
			return Result::make(std::fmaxf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::fmin (also mapped to 'min').
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fminBridge(const std::vector<Result>& args) {
			return Result::make(std::fmin(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::fminf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fminfBridge(const std::vector<Result>& args) {
			return Result::make(std::fminf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::fma (also mapped to 'madd').
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fmaBridge(const std::vector<Result>& args) {
			return Result::make(std::fma(args[0].value.doubleVal, args[1].value.doubleVal, args[2].value.doubleVal));
		}

		/**
		 * Bridge for std::fmaf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fmafBridge(const std::vector<Result>& args) {
			return Result::make(std::fmaf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal), static_cast<float>(args[2].value.doubleVal)));
		}

		/**
		 * Bridge for degrees conversion (custom).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		degBridge(const std::vector<Result>& args) {
			return Result::make(args[0].value.doubleVal * (180.0 / std::numbers::pi));
		}

		/**
		 * Bridge for radians conversion (custom).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		radBridge(const std::vector<Result>& args) {
			return Result::make(args[0].value.doubleVal * (std::numbers::pi / 180.0));
		}

		/**
		 * Bridge for std::rand (0 arguments).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		randBridge(const std::vector<Result>& args) {
			return Result::make(static_cast<int64_t>(std::rand()));
		}

		/**
		 * Bridge for std::isnan. Returns 1 if true, 0 if false.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		isnanBridge(const std::vector<Result>& args) {
			return Result::make(static_cast<int64_t>(std::isnan(args[0].value.doubleVal) ? 1 : 0));
		}

		/**
		 * Bridge for std::isinf. Returns 1 if true, 0 if false.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		isinfBridge(const std::vector<Result>& args) {
			return Result::make(static_cast<int64_t>(std::isinf(args[0].value.doubleVal) ? 1 : 0));
		}


		// =========================================================================
		// Bit Manipulation (<bit>)
		// =========================================================================

		/**
		 * Bridge for std::byteswap. Reverses the bytes of a 64-bit unsigned integer.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the byte-swapped result.
		 **/
		static Result		byteswapBridge(const std::vector<Result>& args) {
			return Result::make(std::byteswap(args[0].value.uintVal));
		}

		/**
		 * Bridge for std::byteswap (16-bit). Reverses the bytes of a 16-bit unsigned integer.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the byte-swapped result.
		 **/
		static Result		byteswap16Bridge(const std::vector<Result>& args) {
			return Result::make(static_cast<uint64_t>(std::byteswap(static_cast<uint16_t>(args[0].value.uintVal))));
		}

		/**
		 * Bridge for std::byteswap (32-bit). Reverses the bytes of a 32-bit unsigned integer.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the byte-swapped result.
		 **/
		static Result		byteswap32Bridge(const std::vector<Result>& args) {
			return Result::make(static_cast<uint64_t>(std::byteswap(static_cast<uint32_t>(args[0].value.uintVal))));
		}

		/**
		 * Bridge for std::byteswap (64-bit). Reverses the bytes of a 64-bit unsigned integer.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the byte-swapped result.
		 **/
		static Result		byteswap64Bridge(const std::vector<Result>& args) {
			return Result::make(std::byteswap(static_cast<uint64_t>(args[0].value.uintVal)));
		}

		/**
		 * Bridge for std::has_single_bit. Checks if a 64-bit integer is a power of two.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns 1 if it has a single bit set, 0 otherwise.
		 **/
		static Result		has_single_bitBridge(const std::vector<Result>& args) {
			return Result::make(static_cast<uint64_t>(std::has_single_bit(args[0].value.uintVal) ? 1 : 0));
		}

		/**
		 * Bridge for std::bit_ceil. Finds the smallest power of two not less than the value.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the calculated power of two.
		 **/
		static Result		bit_ceilBridge(const std::vector<Result>& args) {
			return Result::make(std::bit_ceil(args[0].value.uintVal));
		}

		/**
		 * Bridge for std::bit_floor. Finds the largest power of two not greater than the value.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the calculated power of two.
		 **/
		static Result		bit_floorBridge(const std::vector<Result>& args) {
			return Result::make(std::bit_floor(args[0].value.uintVal));
		}

		/**
		 * Bridge for std::bit_width. Finds the smallest number of bits needed to represent the value.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the bit width.
		 **/
		static Result		bit_widthBridge(const std::vector<Result>& args) {
			return Result::make(static_cast<int64_t>(std::bit_width(args[0].value.uintVal)));
		}

		/**
		 * Bridge for std::rotl. Computes the result of a bitwise left-rotation.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the rotated 64-bit value.
		 **/
		static Result		rotlBridge(const std::vector<Result>& args) {
			return Result::make(std::rotl(args[0].value.uintVal, static_cast<int>(args[1].value.intVal)));
		}

		/**
		 * Bridge for std::rotr. Computes the result of a bitwise right-rotation.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the rotated 64-bit value.
		 **/
		static Result		rotrBridge(const std::vector<Result>& args) {
			return Result::make(std::rotr(args[0].value.uintVal, static_cast<int>(args[1].value.intVal)));
		}

		/**
		 * Bridge for std::countl_zero. Counts consecutive 0 bits starting from the MSB.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the number of leading zeros.
		 **/
		static Result		countl_zeroBridge(const std::vector<Result>& args) {
			return Result::make(static_cast<int64_t>(std::countl_zero(args[0].value.uintVal)));
		}

		/**
		 * Bridge for std::countl_one. Counts consecutive 1 bits starting from the MSB.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the number of leading ones.
		 **/
		static Result		countl_oneBridge(const std::vector<Result>& args) {
			return Result::make(static_cast<int64_t>(std::countl_one(args[0].value.uintVal)));
		}

		/**
		 * Bridge for std::countr_zero. Counts consecutive 0 bits starting from the LSB.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the number of trailing zeros.
		 **/
		static Result		countr_zeroBridge(const std::vector<Result>& args) {
			return Result::make(static_cast<int64_t>(std::countr_zero(args[0].value.uintVal)));
		}

		/**
		 * Bridge for std::countr_one. Counts consecutive 1 bits starting from the LSB.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the number of trailing ones.
		 **/
		static Result		countr_oneBridge(const std::vector<Result>& args) {
			return Result::make(static_cast<int64_t>(std::countr_one(args[0].value.uintVal)));
		}

		/**
		 * Bridge for std::popcount. Counts the total number of 1 bits.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the number of set bits.
		 **/
		static Result		popcountBridge(const std::vector<Result>& args) {
			return Result::make(static_cast<int64_t>(std::popcount(args[0].value.uintVal)));
		}
	};

}	// namespace ve
