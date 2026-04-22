#pragma once

#include "../Foundation/Html.h"
#include "../Foundation/Math.h"
#include "../Foundation/Text.h"
#include "Result.h"
#include "String.h"

#include <bit>
#include <cmath>
#include <numbers>
#include <vector>

namespace ve {

	class					ExecutionContext;

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
		static Result		powBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::pow(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::powf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		powfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::powf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::sin (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		sinBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::sin(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::sinf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		sinfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::sinf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::cos (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		cosBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::cos(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::cosf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		cosfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::cosf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::tan (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		tanBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::tan(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::tanf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		tanfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::tanf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::asin (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		asinBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::asin(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::asinf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		asinfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::asinf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::acos (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		acosBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::acos(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::acosf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		acosfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::acosf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::atan (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		atanBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::atan(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::atanf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		atanfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::atanf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::atan2 (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		atan2Bridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::atan2(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::atan2f (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		atan2fBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::atan2f(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::exp (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		expBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::exp(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::expf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		expfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::expf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::log (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		logBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::log(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::logf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		logfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::logf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::log10 (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		log10Bridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::log10(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::log10f (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		log10fBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::log10f(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::sqrt (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		sqrtBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::sqrt(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::sqrtf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		sqrtfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::sqrtf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::cbrt (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		cbrtBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::cbrt(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::cbrtf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		cbrtfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::cbrtf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::ceil (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		ceilBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::ceil(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::ceilf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		ceilfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::ceilf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::floor (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		floorBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::floor(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::floorf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		floorfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::floorf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::abs (integer overload resolved through std::abs on double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		absBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::abs(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::fabs (double precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fabsBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::fabs(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::fabsf (single precision).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fabsfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
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
		static Result		coshBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::cosh(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::coshf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		coshfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::coshf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::sinh.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		sinhBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::sinh(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::sinhf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		sinhfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::sinhf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::tanh.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		tanhBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::tanh(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::tanhf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		tanhfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::tanhf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::acosh.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		acoshBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::acosh(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::acoshf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		acoshfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::acoshf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::asinh.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		asinhBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::asinh(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::asinhf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		asinhfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::asinhf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::atanh.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		atanhBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::atanh(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::atanhf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		atanhfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
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
		static Result		log2Bridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::log2(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::log2f.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		log2fBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::log2f(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::exp2.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		exp2Bridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::exp2(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::exp2f.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		exp2fBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::exp2f(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::expm1.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		expm1Bridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::expm1(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::expm1f.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		expm1fBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::expm1f(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::ilogb.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		ilogbBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(static_cast<int64_t>(std::ilogb(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::ilogbf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		ilogbfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(static_cast<int64_t>(std::ilogbf(static_cast<float>(args[0].value.doubleVal))));
		}

		/**
		 * Bridge for std::log1p.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		log1pBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::log1p(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::log1pf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		log1pfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::log1pf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::logb.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		logbBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::logb(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::logbf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		logbfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
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
		static Result		hypotBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::hypot(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::hypotf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		hypotfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::hypotf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::tgamma.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		tgammaBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::tgamma(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::tgammaf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		tgammafBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::tgammaf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::lgamma.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		lgammaBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::lgamma(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::lgammaf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		lgammafBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::lgammaf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::fmod (also mapped to 'mod').
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fmodBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::fmod(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::fmodf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fmodfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::fmodf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::trunc.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		truncBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::trunc(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::truncf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		truncfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::truncf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::round.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		roundBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::round(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::roundf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		roundfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::roundf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::nearbyint.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		nearbyintBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::nearbyint(args[0].value.doubleVal));
		}

		/**
		 * Bridge for std::nearbyintf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		nearbyintfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::nearbyintf(static_cast<float>(args[0].value.doubleVal)));
		}

		/**
		 * Bridge for std::remainder.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		remainderBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::remainder(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::remainderf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		remainderfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::remainderf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::remquo.
		 * TODO: Will be updated to return a tuple instead of using pointer arguments.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function (quotient is currently discarded).
		 **/
		static Result		remquoBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
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
		static Result		remquofBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			int dummyQuo;
			return Result::make(std::remquo(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal), &dummyQuo));
		}

		/**
		 * Bridge for std::nextafter.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		nextafterBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::nextafter(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::nextafterf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		nextafterfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::nextafterf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::nexttoward.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		nexttowardBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::nexttoward(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::nexttowardf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		nexttowardfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::nexttowardf(static_cast<float>(args[0].value.doubleVal), args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::fdim (also mapped to 'dim').
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fdimBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::fdim(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::fdimf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fdimfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::fdimf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::fmax (also mapped to 'max').
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fmaxBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::fmax(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::fmaxf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fmaxfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::fmaxf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::fmin (also mapped to 'min').
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fminBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::fmin(args[0].value.doubleVal, args[1].value.doubleVal));
		}

		/**
		 * Bridge for std::fminf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fminfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::fminf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal)));
		}

		/**
		 * Bridge for std::fma (also mapped to 'madd').
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fmaBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::fma(args[0].value.doubleVal, args[1].value.doubleVal, args[2].value.doubleVal));
		}

		/**
		 * Bridge for std::fmaf.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		fmafBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::fmaf(static_cast<float>(args[0].value.doubleVal), static_cast<float>(args[1].value.doubleVal), static_cast<float>(args[2].value.doubleVal)));
		}

		/**
		 * Bridge for degrees conversion (custom).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		degBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(args[0].value.doubleVal * (180.0 / std::numbers::pi));
		}

		/**
		 * Bridge for radians conversion (custom).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		radBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(args[0].value.doubleVal * (std::numbers::pi / 180.0));
		}

		/**
		 * Bridge for std::rand (0 arguments).
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		randBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(static_cast<int64_t>(std::rand()));
		}

		/**
		 * Bridge for std::isnan. Returns 1 if true, 0 if false.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		isnanBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(static_cast<int64_t>(std::isnan(args[0].value.doubleVal) ? 1 : 0));
		}

		/**
		 * Bridge for std::isinf. Returns 1 if true, 0 if false.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the result of the intrinsic function.
		 **/
		static Result		isinfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(static_cast<int64_t>(std::isinf(args[0].value.doubleVal) ? 1 : 0));
		}


		// =========================================================================
		// Bit Manipulation (<bit>)
		// =========================================================================

		/**
		 * Bridge for std::byteswap (16-bit). Reverses the bytes of a 16-bit unsigned integer.
		 * 
		 * \param ctx		The execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the byte-swapped result.
		 **/
		static Result		byteswap16Bridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(static_cast<uint64_t>(Math::byteswap(static_cast<uint16_t>(args[0].value.uintVal))));
		}

		/**
		 * Bridge for std::byteswap (32-bit). Reverses the bytes of a 32-bit unsigned integer.
		 * 
		 * \param ctx		The execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the byte-swapped result.
		 **/
		static Result		byteswap32Bridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(static_cast<uint64_t>(Math::byteswap(static_cast<uint32_t>(args[0].value.uintVal))));
		}

		/**
		 * Bridge for std::byteswap (64-bit). Reverses the bytes of a 64-bit unsigned integer.
		 * 
		 * \param ctx		The execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the byte-swapped result.
		 **/
		static Result		byteswap64Bridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(Math::byteswap(static_cast<uint64_t>(args[0].value.uintVal)));
		}

		/**
		 * Bridge for std::has_single_bit. Checks if a 64-bit integer is a power of two.
		 * 
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns 1 if it has a single bit set, 0 otherwise.
		 **/
		static Result		has_single_bitBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(static_cast<uint64_t>(std::has_single_bit(args[0].value.uintVal) ? 1 : 0));
		}

		/**
		 * Bridge for std::bit_ceil. Finds the smallest power of two not less than the value.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the calculated power of two.
		 **/
		static Result		bit_ceilBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::bit_ceil(args[0].value.uintVal));
		}

		/**
		 * Bridge for std::bit_floor. Finds the largest power of two not greater than the value.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the calculated power of two.
		 **/
		static Result		bit_floorBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::bit_floor(args[0].value.uintVal));
		}

		/**
		 * Bridge for std::bit_width. Finds the smallest number of bits needed to represent the value.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the bit width.
		 **/
		static Result		bit_widthBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(static_cast<int64_t>(std::bit_width(args[0].value.uintVal)));
		}

		/**
		 * Bridge for std::rotl. Computes the result of a bitwise left-rotation.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the rotated 64-bit value.
		 **/
		static Result		rotlBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::rotl(args[0].value.uintVal, static_cast<int>(args[1].value.intVal)));
		}

		/**
		 * Bridge for std::rotr. Computes the result of a bitwise right-rotation.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the rotated 64-bit value.
		 **/
		static Result		rotrBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(std::rotr(args[0].value.uintVal, static_cast<int>(args[1].value.intVal)));
		}

		/**
		 * Bridge for std::countl_zero. Counts consecutive 0 bits starting from the MSB.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the number of leading zeros.
		 **/
		static Result		countl_zeroBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(static_cast<int64_t>(std::countl_zero(args[0].value.uintVal)));
		}

		/**
		 * Bridge for std::countl_one. Counts consecutive 1 bits starting from the MSB.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the number of leading ones.
		 **/
		static Result		countl_oneBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(static_cast<int64_t>(std::countl_one(args[0].value.uintVal)));
		}

		/**
		 * Bridge for std::countr_zero. Counts consecutive 0 bits starting from the LSB.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the number of trailing zeros.
		 **/
		static Result		countr_zeroBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(static_cast<int64_t>(std::countr_zero(args[0].value.uintVal)));
		}

		/**
		 * Bridge for std::countr_one. Counts consecutive 1 bits starting from the LSB.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the number of trailing ones.
		 **/
		static Result		countr_oneBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(static_cast<int64_t>(std::countr_one(args[0].value.uintVal)));
		}

		/**
		 * Bridge for std::popcount. Counts the total number of 1 bits.
		 *
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns the number of set bits.
		 **/
		static Result		popcountBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			return Result::make(static_cast<int64_t>(std::popcount(args[0].value.uintVal)));
		}


		// =========================================================================
		// HTML Entities
		// =========================================================================

		/**
		 * Bridge for htmlCount().
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Unsigned Result containing the total number of HTML entities.
		 **/
		static Result		htmlCountBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			static_cast<void>(args);
			return Result{ .type = NumericConstant::Unsigned, .value = { .uintVal = static_cast<uint64_t>(Html::totalNames()) } };
		}

		/**
		 * Bridge for htmlName(index).
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a String Result containing the entity name, or invalid if out of bounds.
		 **/
		static Result		htmlNameBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty()) {
				return Result{ .type = NumericConstant::Invalid };
			}
			
			size_t idx = 0;
			const Result& arg = args[0];
			
			if (arg.type == NumericConstant::Signed) {
				if (arg.value.intVal < 0) {
					return Result{ .type = NumericConstant::Invalid };
				}
				idx = static_cast<size_t>(arg.value.intVal);
			}
			else if (arg.type == NumericConstant::Unsigned) {
				idx = static_cast<size_t>(arg.value.uintVal);
			}
			else {
				return Result{ .type = NumericConstant::Invalid };
			}

			std::string name;
			Html::getName(name, idx);
			
			if (!name.empty()) {
				String* strObj = ctx->allocateObject<String>();
				
				if (strObj) {
					strObj->assignUtf8(name.data(), name.length());
					return strObj->createResult();
				}
			}
			
			return Result{ .type = NumericConstant::Invalid };
		}

		/**
		 * Bridge for htmlChar(index) OR htmlChar(name).
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a String Result containing the 1 or 2 UTF-8 characters, or invalid if not found.
		 **/
		static Result		htmlCharBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty()) {
				return Result{ .type = NumericConstant::Invalid };
			}
			
			const Result& arg = args[0];
			uint64_t code = static_cast<uint64_t>(Html::InvalidCode::Invalid);
			
			if (arg.type == NumericConstant::Signed || arg.type == NumericConstant::Unsigned) {
				size_t idx = 0;
				
				if (arg.type == NumericConstant::Signed) {
					if (arg.value.intVal >= 0) {
						idx = static_cast<size_t>(arg.value.intVal);
					}
					else {
						return Result{ .type = NumericConstant::Invalid };
					}
				}
				else {
					idx = static_cast<size_t>(arg.value.uintVal);
				}
				
				std::string name;
				Html::getName(name, idx);
				
				if (!name.empty()) {
					code = Html::getCode(name.c_str(), name.length());
				}
			}
			else if (arg.type == NumericConstant::Object && arg.value.objectVal != nullptr) {
				if (arg.value.objectVal->type() & BuiltInType_String) {
					std::wstring wStr;
					
					// Assuming ToStringFlag_None is 0
					if (arg.value.objectVal->toString(wStr, 0, 0)) {
						std::string name;
						name.reserve(wStr.length());
						
						for (size_t i = 0; i < wStr.length(); ++i) {
							name.push_back(static_cast<char>(wStr[i]));
						}
						
						code = Html::getCode(name.c_str(), name.length());
					}
				}
			}
			
			if (code != static_cast<uint64_t>(Html::InvalidCode::Invalid)) {
				std::string utf8Payload;
				uint32_t lower = static_cast<uint32_t>(code & 0xFFFFFFFF);
				uint32_t upper = static_cast<uint32_t>(code >> 32);
				
				Text::appendUtf8(utf8Payload, lower);
				
				if (upper != 0) {
					Text::appendUtf8(utf8Payload, upper);
				}
				
				String* strObj = ctx->allocateObject<String>();
				
				if (strObj) {
					strObj->assignUtf8(utf8Payload.data(), utf8Payload.length());
					return strObj->createResult();
				}
			}
			
			return Result{ .type = NumericConstant::Invalid };
		}


		// =========================================================================
		// String Methods
		// =========================================================================

		/**
		 * Bridge for String.capitalize().
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a String Result containing the capitalized string.
		 **/
		static Result		capitalizeBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr || !(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{ .type = NumericConstant::Invalid };
			}
			
			// Ensure you perform whatever internal RTTI check you use for BuiltInType_String here if needed.
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			String* capStr = strObj->capitalize(ctx);
			
			if (capStr) {
				return capStr->createResult();
			}
			
			return Result{ .type = NumericConstant::Invalid };
		}

		/**
		 * Bridge for String.casefold().
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a String Result containing the casefolded string.
		 **/
		static Result		casefoldBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr || !(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{ .type = NumericConstant::Invalid };
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			try {
				String* foldedStr = strObj->casefold(ctx);
				if (foldedStr) {
					return foldedStr->createResult();
				}
			}
			catch (...) {
			}
			
			return Result{ .type = NumericConstant::Invalid };
		}

		/**
		 * Bridge for String.center().
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a String Result containing the centered string.
		 **/
		static Result		centerBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 2 || 
				args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{ .type = NumericConstant::Invalid };
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			// Resolve target width.
			size_t width = 0;
			if (args[1].type == NumericConstant::Signed) {
				if (args[1].value.intVal < 0) {
					return Result{ .type = NumericConstant::Invalid };
				}
				width = static_cast<size_t>(args[1].value.intVal);
			}
			else if (args[1].type == NumericConstant::Unsigned) {
				width = static_cast<size_t>(args[1].value.uintVal);
			}
			else {
				return Result{ .type = NumericConstant::Invalid };
			}

			// Optional fillChar.
			uint32_t fillChar = ' ';
			if (args.size() >= 3) {
				if (args[2].type == NumericConstant::Signed) {
					if (args[2].value.intVal < 0 || args[2].value.intVal > 0x10FFFF) {
						return Result{ .type = NumericConstant::Invalid };
					}
					fillChar = static_cast<uint32_t>(args[2].value.intVal);
				}
				else if (args[2].type == NumericConstant::Unsigned) {
					if (args[2].value.uintVal > 0x10FFFF) {
						return Result{ .type = NumericConstant::Invalid };
					}
					fillChar = static_cast<uint32_t>(args[2].value.uintVal);
				}
				else if (args[2].type == NumericConstant::Object && 
					args[2].value.objectVal != nullptr && 
					(args[2].value.objectVal->type() & BuiltInType_String)) {
					
					String* fillStr = static_cast<String*>(args[2].value.objectVal);
					
					// Python requires fillchar to be exactly one character.
					if (fillStr->arrayLength() != 1) {
						return Result{ .type = NumericConstant::Invalid };
					}
					
					fillChar = fillStr->getCodePoint(0);
				}
				else {
					return Result{ .type = NumericConstant::Invalid };
				}
			}
			
			String* centeredStr = strObj->center(ctx, width, fillChar);
			if (centeredStr) {
				return centeredStr->createResult();
			}
			
			return Result{ .type = NumericConstant::Invalid };
		}

		/**
		 * Bridge for String.count(). Handles varying arity for optional start and end parameters.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Integer Result containing the count.
		 **/
		static Result		countBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 2 || args.size() > 4) { return Result{ .type = NumericConstant::Invalid }; }
			
			if (args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{ .type = NumericConstant::Invalid };
			}
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			if (args[1].type != NumericConstant::Object || 
				args[1].value.objectVal == nullptr || 
				!(args[1].value.objectVal->type() & BuiltInType_String)) {
				return Result{ .type = NumericConstant::Invalid };
			}
			String* subObj = static_cast<String*>(args[1].value.objectVal);
			
			int64_t start = 0;
			if (args.size() >= 3) {
				if (args[2].type == NumericConstant::Signed) {
					start = args[2].value.intVal;
				}
				else if (args[2].type == NumericConstant::Unsigned) {
					start = static_cast<int64_t>(args[2].value.uintVal);
				}
				else {
					return Result{ .type = NumericConstant::Invalid };
				}
			}
			
			int64_t end = -1;
			if (args.size() == 4) {
				if (args[3].type == NumericConstant::Signed) {
					end = args[3].value.intVal;
				}
				else if (args[3].type == NumericConstant::Unsigned) {
					end = static_cast<int64_t>(args[3].value.uintVal);
				}
				else {
					return Result{ .type = NumericConstant::Invalid };
				}
			}
			
			int64_t occurrences = strObj->count(subObj, start, end);
				
			Result res;
			res.type = NumericConstant::Signed;
			res.value.intVal = occurrences;
			return res;
			
			return Result{ .type = NumericConstant::Invalid };
		}
	};

}	// namespace ve
