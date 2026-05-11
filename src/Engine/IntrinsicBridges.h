#pragma once

#include "../Foundation/Html.h"
#include "../Foundation/Math.h"
#include "../Foundation/Text.h"
#include "Result.h"
#include "String.h"
#include "Vector.h"

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
				return Result{};
			}
			
			size_t idx = 0;
			const Result& arg = args[0];
			
			if (arg.type == NumericConstant::Signed) {
				if (arg.value.intVal < 0) {
					return Result{};
				}
				idx = static_cast<size_t>(arg.value.intVal);
			}
			else if (arg.type == NumericConstant::Unsigned) {
				idx = static_cast<size_t>(arg.value.uintVal);
			}
			else {
				return Result{};
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
			
			return Result{};
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
				return Result{};
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
						return Result{};
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
					std::string name;
					
					// Assuming ToStringFlag_None is 0
					if (arg.value.objectVal->toString(name, 0, 0)) {						
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
			
			return Result{};
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
				return Result{};
			}
			
			// Ensure you perform whatever internal RTTI check you use for BuiltInType_String here if needed.
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			String* capStr = strObj->capitalize(ctx);
			
			if (capStr) {
				return capStr->createResult();
			}
			
			return Result{};
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
				return Result{};
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			try {
				String* foldedStr = strObj->casefold(ctx);
				if (foldedStr) {
					return foldedStr->createResult();
				}
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
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
				return Result{};
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			// Resolve target width.
			size_t width = 0;
			if (args[1].type == NumericConstant::Signed) {
				if (args[1].value.intVal < 0) {
					return Result{};
				}
				width = static_cast<size_t>(args[1].value.intVal);
			}
			else if (args[1].type == NumericConstant::Unsigned) {
				width = static_cast<size_t>(args[1].value.uintVal);
			}
			else {
				return Result{};
			}

			// Optional fillChar.
			uint32_t fillChar = ' ';
			if (args.size() >= 3) {
				if (args[2].type == NumericConstant::Signed) {
					if (args[2].value.intVal < 0 || args[2].value.intVal > 0x10FFFF) {
						return Result{};
					}
					fillChar = static_cast<uint32_t>(args[2].value.intVal);
				}
				else if (args[2].type == NumericConstant::Unsigned) {
					if (args[2].value.uintVal > 0x10FFFF) {
						return Result{};
					}
					fillChar = static_cast<uint32_t>(args[2].value.uintVal);
				}
				else if (args[2].type == NumericConstant::Object && 
					args[2].value.objectVal != nullptr && 
					(args[2].value.objectVal->type() & BuiltInType_String)) {
					
					String* fillStr = static_cast<String*>(args[2].value.objectVal);
					
					// Python requires fillchar to be exactly one character.
					if (fillStr->arrayLength() != 1) {
						return Result{};
					}
					
					fillChar = fillStr->getCodePoint(0);
				}
				else {
					return Result{};
				}
			}
			
			String* centeredStr = strObj->center(ctx, width, fillChar);
			if (centeredStr) {
				return centeredStr->createResult();
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.count(). Handles varying arity for optional start and end parameters.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Integer Result containing the count.
		 **/
		static Result		countBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 2 || args.size() > 4) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			if (args[1].type != NumericConstant::Object || 
				args[1].value.objectVal == nullptr || 
				!(args[1].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
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
					return Result{};
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
					return Result{};
				}
			}
				
			Result res = Result::make(strObj->count(subObj, start, end));
			return res;
			
			return Result{};
		}

		/**
		 * Bridge for String.encode(). Handles decoding the parameters into native CodePage and ErrorPolicy enums.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a String Result containing the encoded text.
		 **/
		static Result		encodeBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 2 || args.size() > 3) {
				return Result{};
			}
			
			if (args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			CodePage codePage = CodePage::UTF8;
			
			if (args[1].type == NumericConstant::Object && 
				args[1].value.objectVal != nullptr && 
				(args[1].value.objectVal->type() & BuiltInType_String)) {
				String* encStr = static_cast<String*>(args[1].value.objectVal);
				
				if (!Encode::getCodePageId(encStr->getUtf8(), codePage)) {
					return Result{};
				}
			}
			else if (args[1].type == NumericConstant::Unsigned) {
				codePage = static_cast<CodePage>(args[1].value.uintVal);
			}
			else if (args[1].type == NumericConstant::Signed) {
				codePage = static_cast<CodePage>(args[1].value.intVal);
			}
			else {
				return Result{};
			}
			
			EncodingErrorPolicy errorPolicy = EncodingErrorPolicy::Strict;
			
			if (args.size() == 3) {
				if (args[2].type == NumericConstant::Object && 
					args[2].value.objectVal != nullptr && 
					(args[2].value.objectVal->type() & BuiltInType_String)) {
					String* errStr = static_cast<String*>(args[2].value.objectVal);
					std::string errUtf8 = errStr->getUtf8();
					
					std::string errUpper;
					errUpper.reserve(errUtf8.length());
					
					for (size_t i = 0; i < errUtf8.length(); ++i) {
						errUpper += static_cast<char>(Text::toUpper(static_cast<unsigned char>(errUtf8[i])));
					}
					
					if (errUpper == "STRICT") {
						errorPolicy = EncodingErrorPolicy::Strict;
					}
					else if (errUpper == "REPLACE") {
						errorPolicy = EncodingErrorPolicy::Replace;
					}
					else {
						return Result{};
					}
				}
				else {
					return Result{};
				}
			}
			
			try {
				String* encodedStr = strObj->encode(ctx, codePage, errorPolicy);
				if (encodedStr) {
					return encodedStr->createResult();
				}
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.endswith(). Handles varying arity for optional start and end parameters.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Signed Integer Result containing 1 for true, 0 for false.
		 **/
		static Result		endsWithBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 2 || args.size() > 4) {
				return Result{};
			}
			
			if (args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			if (args[1].type != NumericConstant::Object || 
				args[1].value.objectVal == nullptr || 
				!(args[1].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			String* suffixObj = static_cast<String*>(args[1].value.objectVal);
			
			int64_t start = 0;
			if (args.size() >= 3) {
				if (args[2].type == NumericConstant::Signed) {
					start = args[2].value.intVal;
				}
				else if (args[2].type == NumericConstant::Unsigned) {
					start = static_cast<int64_t>(args[2].value.uintVal);
				}
				else {
					return Result{};
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
					return Result{};
				}
			}
			
			try {
				Result res = Result::make(strObj->endsWith(suffixObj, start, end));
				return res;
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.expandtabs().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a String Result containing the expanded text.
		 **/
		static Result		expandTabsBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || args.size() > 2) {
				return Result{};
			}
			
			if (args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			int64_t tabSize = 8;
			
			if (args.size() == 2) {
				if (args[1].type == NumericConstant::Signed) {
					tabSize = args[1].value.intVal;
				}
				else if (args[1].type == NumericConstant::Unsigned) {
					tabSize = static_cast<int64_t>(args[1].value.uintVal);
				}
				else {
					return Result{};
				}
			}
			
			try {
				String* expandedStr = strObj->expandtabs(ctx, tabSize);
				if (expandedStr) {
					return expandedStr->createResult();
				}
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.find(). Handles varying arity for optional start and end parameters.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Signed Integer Result containing the found index, or -1.
		 **/
		static Result		findBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 2 || args.size() > 4) {
				return Result{};
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			if (args[1].type != NumericConstant::Object || 
				args[1].value.objectVal == nullptr || 
				!(args[1].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			String* subObj = static_cast<String*>(args[1].value.objectVal);
			
			int64_t start = 0;
			if (args.size() >= 3) {
				if (args[2].type == NumericConstant::Signed) { start = args[2].value.intVal; }
				else if (args[2].type == NumericConstant::Unsigned) { start = static_cast<int64_t>(args[2].value.uintVal); }
				else { return Result{}; }
			}
			
			int64_t end = -1;
			if (args.size() == 4) {
				if (args[3].type == NumericConstant::Signed) { end = args[3].value.intVal; }
				else if (args[3].type == NumericConstant::Unsigned) { end = static_cast<int64_t>(args[3].value.uintVal); }
				else { return Result{}; }
			}
			
			try {
				Result res = Result::make(strObj->find(subObj, start, end));
				return res;
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.format(). Handles dynamic replacement of {} placeholders.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a String Result containing the formatted text.
		 **/
		static Result		formatBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty()) {
				return Result{};
			}
			
			if (args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			std::vector<Result> formatArgs(args.begin() + 1, args.end());
			
			try {
				String* formattedStr = strObj->format(ctx, formatArgs);
				
				if (formattedStr) {
					return formattedStr->createResult();
				}
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.isalnum().
		 * Must be called within a try/catch block.
		 * 
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Signed Integer Result containing 1 for true, 0 for false.
		 **/
		static Result		isAlnumBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			
			if (args.size() != 1) { return Result{}; }
			if (args[0].type == NumericConstant::Unsigned) {
				return Result::make(Character::isAlphaUtf(args[0].value.uintVal) || Character::isNumericUtf(args[0].value.uintVal));
			}
			else if (args[0].type == NumericConstant::Signed) {
				return Result::make(Character::isAlphaUtf(args[0].value.intVal) || Character::isNumericUtf(args[0].value.intVal));
			}
			else if (args[0].type == NumericConstant::Object && args[0].value.objectVal && (args[0].value.objectVal->type() & BuiltInType_String)) {
			
				String* strObj = static_cast<String*>(args[0].value.objectVal);
			
				try {
					Result res = Result::make(strObj->isalnum());
					return res;
				}
				catch (...) {
					throw ErrorCode::Out_Of_Memory;
				}
			}
			return Result{};
		}

		/**
		 * Bridge for String.isalpha().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Signed Integer Result containing 1 for true, 0 for false.
		 **/
		static Result		isAlphaBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			
			if (args.size() != 1) { return Result{}; }
			if (args[0].type == NumericConstant::Unsigned) {
				return Result::make(Character::isAlphaUtf(args[0].value.uintVal));
			}
			else if (args[0].type == NumericConstant::Signed) {
				return Result::make(Character::isAlphaUtf(args[0].value.intVal));
			}
			else if (args[0].type == NumericConstant::Object && args[0].value.objectVal && (args[0].value.objectVal->type() & BuiltInType_String)) {
			
				String* strObj = static_cast<String*>(args[0].value.objectVal);
			
				try {
					Result res = Result::make(strObj->isalpha());
					return res;
				}
				catch (...) {
					throw ErrorCode::Out_Of_Memory;
				}
			}
			return Result{};
		}

		/**
		 * Bridge for String.isascii().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Signed Integer Result containing 1 for true, 0 for false.
		 **/
		static Result		isAsciiBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			
			if (args.size() != 1) { return Result{}; }
			if (args[0].type == NumericConstant::Unsigned) {
				return Result::make(args[0].value.uintVal <= 127 && Character::isAscii(args[0].value.uintVal));
			}
			else if (args[0].type == NumericConstant::Signed) {
				return Result::make(args[0].value.intVal <= 127 && args[0].value.intVal >= 0 && Character::isAscii(args[0].value.intVal));
			}
			else if (args[0].type == NumericConstant::Object && args[0].value.objectVal && (args[0].value.objectVal->type() & BuiltInType_String)) {
			
				String* strObj = static_cast<String*>(args[0].value.objectVal);
			
				try {
					Result res = Result::make(strObj->isAscii());
					return res;
				}
				catch (...) {
					throw ErrorCode::Out_Of_Memory;
				}
			}
			return Result{};
		}

		/**
		 * Bridge for String.isdecimal().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Signed Integer Result containing 1 for true, 0 for false.
		 **/
		static Result		isDecimalBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			
			if (args.size() != 1) { return Result{}; }
			if (args[0].type == NumericConstant::Unsigned) {
				return Result::make(Character::isDecimalUtf(args[0].value.uintVal));
			}
			else if (args[0].type == NumericConstant::Signed) {
				return Result::make(Character::isDecimalUtf(args[0].value.intVal));
			}
			else if (args[0].type == NumericConstant::Object && args[0].value.objectVal && (args[0].value.objectVal->type() & BuiltInType_String)) {
			
				String* strObj = static_cast<String*>(args[0].value.objectVal);
			
				try {
					Result res = Result::make(strObj->isdecimal());
					return res;
				}
				catch (...) {
					throw ErrorCode::Out_Of_Memory;
				}
			}
			return Result{};
		}

		/**
		 * Bridge for String.isdigit().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Signed Integer Result containing 1 for true, 0 for false.
		 **/
		static Result		isDigitBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			
			if (args.size() != 1) { return Result{}; }
			if (args[0].type == NumericConstant::Unsigned) {
				return Result::make(Character::isDigitUtf(args[0].value.uintVal));
			}
			else if (args[0].type == NumericConstant::Signed) {
				return Result::make(Character::isDigitUtf(args[0].value.intVal));
			}
			else if (args[0].type == NumericConstant::Object && args[0].value.objectVal && (args[0].value.objectVal->type() & BuiltInType_String)) {
			
				String* strObj = static_cast<String*>(args[0].value.objectVal);
			
				try {
					bool result = strObj->isdigit();
				
					Result res;
					res.type = NumericConstant::Signed;
					res.value.intVal = result ? 1 : 0;
					return res;
				}
				catch (...) {
					throw ErrorCode::Out_Of_Memory;
				}
			}
			return Result{};
		}

		/**
		 * Bridge for String.isidentifier().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Signed Integer Result containing 1 for true, 0 for false.
		 **/
		static Result		isIdentifierBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			
			if (args.size() != 1) {
				return Result{};
			}
			
			if (args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			try {
				Result res = Result::make(strObj->isidentifier());
				return res;
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.islower().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Signed Integer Result containing 1 for true, 0 for false.
		 **/
		static Result		isLowerBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			
			if (args.size() != 1) { return Result{}; }
			if (args[0].type == NumericConstant::Unsigned) {
				return Result::make(Character::isLowerUtf(args[0].value.uintVal));
			}
			else if (args[0].type == NumericConstant::Signed) {
				return Result::make(Character::isLowerUtf(args[0].value.intVal));
			}
			else if (args[0].type == NumericConstant::Object && args[0].value.objectVal && (args[0].value.objectVal->type() & BuiltInType_String)) {
			
				String* strObj = static_cast<String*>(args[0].value.objectVal);
			
				try {
					Result res = Result::make(strObj->islower());
					return res;
				}
				catch (...) {
					throw ErrorCode::Out_Of_Memory;
				}
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.isnumeric().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Signed Integer Result containing 1 for true, 0 for false.
		 **/
		static Result		isNumericBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			
			if (args.size() != 1) { return Result{}; }
			if (args[0].type == NumericConstant::Unsigned) {
				return Result::make(Character::isNumericUtf(args[0].value.uintVal));
			}
			else if (args[0].type == NumericConstant::Signed) {
				return Result::make(Character::isNumericUtf(args[0].value.intVal));
			}
			else if (args[0].type == NumericConstant::Object && args[0].value.objectVal && (args[0].value.objectVal->type() & BuiltInType_String)) {
			
				String* strObj = static_cast<String*>(args[0].value.objectVal);
			
				try {
					Result res = Result::make(strObj->isnumeric());
					return res;
				}
				catch (...) {
					throw ErrorCode::Out_Of_Memory;
				}
			}
			return Result{};
		}

		/**
		 * Bridge for String.isprintable().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Signed Integer Result containing 1 for true, 0 for false.
		 **/
		static Result		isPrintableBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			
			if (args.size() != 1) { return Result{}; }
			if (args[0].type == NumericConstant::Unsigned) {
				return Result::make(Character::isPrintableUtf(args[0].value.uintVal));
			}
			else if (args[0].type == NumericConstant::Signed) {
				return Result::make(Character::isPrintableUtf(args[0].value.intVal));
			}
			else if (args[0].type == NumericConstant::Object && args[0].value.objectVal && (args[0].value.objectVal->type() & BuiltInType_String)) {
			
				String* strObj = static_cast<String*>(args[0].value.objectVal);
			
				try {
					bool result = strObj->isprintable();
				
					Result res;
					res.type = NumericConstant::Signed;
					res.value.intVal = result ? 1 : 0;
					return res;
				}
				catch (...) {
					throw ErrorCode::Out_Of_Memory;
				}
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.isspace().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Signed Integer Result containing 1 for true, 0 for false.
		 **/
		static Result		isSpaceBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			
			if (args.size() != 1) { return Result{}; }
			if (args[0].type == NumericConstant::Unsigned) {
				return Result::make(Character::isSpaceUtf(args[0].value.uintVal));
			}
			else if (args[0].type == NumericConstant::Signed) {
				return Result::make(Character::isSpaceUtf(args[0].value.intVal));
			}
			else if (args[0].type == NumericConstant::Object && args[0].value.objectVal && (args[0].value.objectVal->type() & BuiltInType_String)) {
			
				String* strObj = static_cast<String*>(args[0].value.objectVal);
			
				try {
					bool result = strObj->isspace();
				
					Result res;
					res.type = NumericConstant::Signed;
					res.value.intVal = result ? 1 : 0;
					return res;
				}
				catch (...) {
					throw ErrorCode::Out_Of_Memory;
				}
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.istitle().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Signed Integer Result containing 1 for true, 0 for false.
		 **/
		static Result		isTitleBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			
			if (args.size() != 1) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			try {
				bool result = strObj->istitle();
				
				Result res;
				res.type = NumericConstant::Signed;
				res.value.intVal = result ? 1 : 0;
				return res;
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.isupper().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Signed Integer Result containing 1 for true, 0 for false.
		 **/
		static Result		isUpperBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			
			if (args.size() != 1) { return Result{}; }
			if (args[0].type == NumericConstant::Unsigned) {
				return Result::make(Character::isSpaceUtf(args[0].value.uintVal));
			}
			else if (args[0].type == NumericConstant::Signed) {
				return Result::make(Character::isSpaceUtf(args[0].value.intVal));
			}
			else if (args[0].type == NumericConstant::Object && args[0].value.objectVal && (args[0].value.objectVal->type() & BuiltInType_String)) {
			
				String* strObj = static_cast<String*>(args[0].value.objectVal);
			
				try {
					bool result = strObj->isupper();
				
					Result res;
					res.type = NumericConstant::Signed;
					res.value.intVal = result ? 1 : 0;
					return res;
				}
				catch (...) {
					throw ErrorCode::Out_Of_Memory;
				}
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.join().
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a String Result containing the joined string.
		 **/
		static Result		joinBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 2 || 
				args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			
			if (args[1].type != NumericConstant::Object || args[1].value.objectVal == nullptr) {
				return Result{};
			}
			
			Object* iterable = args[1].value.objectVal;
			uint32_t objType = iterable->type();
			
			String* resultStr = ctx->allocateObject<String>();
			if (!resultStr) {
				return Result{};
			}
			
			Result outRes = resultStr->createResult();
			
			if (objType & BuiltInType_Vector) {
				Vector* vec = static_cast<Vector*>(iterable);
				size_t length = vec->arrayLength();
				
				for (size_t i = 0; i < length; ++i) {
					if (i > 0) {
						resultStr->operator+=(args[0]);
					}
					
					Result elemRes = vec->arrayAccess(static_cast<int64_t>(i));
					if (elemRes.type == NumericConstant::Object && 
						elemRes.value.objectVal != nullptr && 
						(elemRes.value.objectVal->type() & BuiltInType_String)) {
						
						resultStr->operator+=(elemRes);
					}
					else {
						return Result{};
					}
				}
			}
			else if (objType & BuiltInType_Map) {
				Map* mapObj = static_cast<Map*>(iterable);
				std::vector<Result> keys = mapObj->getKeys();
				
				for (size_t i = 0; i < keys.size(); ++i) {
					if (i > 0) {
						resultStr->operator+=(args[0]);
					}
					
					if (keys[i].type == NumericConstant::Object && 
						keys[i].value.objectVal != nullptr && 
						(keys[i].value.objectVal->type() & BuiltInType_String)) {
						
						resultStr->operator+=(keys[i]);
					}
					else {
						return Result{};
					}
				}
			}
			else if (objType & BuiltInType_String) {
				String* strObj = static_cast<String*>(iterable);
				size_t length = strObj->arrayLength();
				
				for (size_t i = 0; i < length; ++i) {
					if (i > 0) {
						resultStr->operator+=(args[0]);
					}
					
					Result elemRes = strObj->arrayAccess(static_cast<int64_t>(i));
					resultStr->operator+=(elemRes);
				}
			}
			else {
				return Result{};
			}
			
			return outRes;
		}

		/**
		 * Bridge for String.ljust().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Object Result containing the newly justified String.
		 **/
		static Result		ljustBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			
			if (args.size() < 2 || args.size() > 3) {
				return Result{};
			}
			
			if (args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}

			int64_t width = 0;

			if (args[1].type == NumericConstant::Signed) {
				width = args[1].value.intVal;
			}
			else if (args[1].type == NumericConstant::Unsigned) {
				width = static_cast<int64_t>(args[1].value.uintVal);
			}
			else {
				return Result{};
			}
			
			uint32_t fillCharCp = ' ';

			if (args.size() == 3) {
				if (args[2].type == NumericConstant::Unsigned) {
					fillCharCp = uint32_t(args[2].value.uintVal);
				}
				else if (args[2].type == NumericConstant::Signed) {
					fillCharCp = uint32_t(args[2].value.intVal);
				}
				else {
					if (args[2].type != NumericConstant::Object || 
						args[2].value.objectVal == nullptr || 
						!(args[2].value.objectVal->type() & BuiltInType_String)) {
						return Result{};
					}
				
					String* fillStr = static_cast<String*>(args[2].value.objectVal);
				
					if (fillStr->arrayLength() != 1) {
						return Result{};
					}
				
					fillCharCp = fillStr->getCodePoint(0);
				}
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			try {
				size_t validWidth = width > 0 ? static_cast<size_t>(width) : 0;
				String* resultStr = strObj->ljust(validWidth, fillCharCp);
				if (resultStr) {
					return resultStr->createResult();
				}
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.lower().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Object Result containing the newly lowercased String.
		 **/
		static Result		lowerBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type == NumericConstant::Unsigned) {
				char32_t outSeq[3];
				auto lowerCount = Case::getLowerSequence(char32_t(args[0].value.uintVal), outSeq);
				if (lowerCount == 1) {
					return Result::make(uint64_t(outSeq[0]));
				}
				else if (lowerCount) {
					std::string result;
					try {
						for (uint32_t j = 0; j < lowerCount; ++j) {
							Text::appendUtf8(result, static_cast<uint32_t>(outSeq[j]));
						}

						String* newStr = ctx->allocateObject<String>();
						if (newStr) {
							if (!newStr->assignUtf8(result.data(), result.length())) {
								ctx->deallocateObject(newStr);
								throw ErrorCode::Object_Initialization_Failed;
							}
							return newStr->createResult();
						}
					}
					catch (...) { throw ErrorCode::Out_Of_Memory; }
					return Result{};	// Creates an invalid return.
				}
				return args[0];
			}
			else if (args[0].type == NumericConstant::Signed) {
				char32_t outSeq[3];
				auto lowerCount = Case::getLowerSequence(char32_t(args[0].value.uintVal), outSeq);
				if (lowerCount == 1) {
					return Result::make(int64_t(outSeq[0]));
				}
				else if (lowerCount) {
					std::string result;
					try {
						for (uint32_t j = 0; j < lowerCount; ++j) {
							Text::appendUtf8(result, static_cast<uint32_t>(outSeq[j]));
						}

						String* newStr = ctx->allocateObject<String>();
						if (newStr) {
							if (!newStr->assignUtf8(result.data(), result.length())) {
								ctx->deallocateObject(newStr);
								throw ErrorCode::Object_Initialization_Failed;
							}
							return newStr->createResult();
						}
					}
					catch (...) { throw ErrorCode::Out_Of_Memory; }
					return Result{};	// Creates an invalid return.
				}
				return args[0];
			}
			else if (args[0].type == NumericConstant::Object && args[0].value.objectVal && (args[0].value.objectVal->type() & BuiltInType_String)) {
			
				String* strObj = static_cast<String*>(args[0].value.objectVal);
			
				try {
					String* resultStr = strObj->lower(ctx);
				
					if (resultStr) {
						return resultStr->createResult();
					}
				}
				catch (...) {
					throw ErrorCode::Out_Of_Memory;
				}
			}
			return Result{};
		}

		/**
		 * Bridge for String.lstrip().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Object Result containing the newly stripped String.
		 **/
		static Result		lstripBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 1 || args.size() > 2) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			
			std::u32string stripChars;
			
			if (args.size() == 2) {
				if (args[1].type != NumericConstant::Object || 
					args[1].value.objectVal == nullptr || 
					!(args[1].value.objectVal->type() & BuiltInType_String)) {
					return Result{};
				}
				
				String* charStr = static_cast<String*>(args[1].value.objectVal);
				stripChars = charStr->getUtf32();
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			try {
				String* resultStr = strObj->lstrip(ctx, stripChars);
				
				if (resultStr) { return resultStr->createResult(); }
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.partition().
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (this string, separator).
		 * \return			Returns a Vector Result containing 3 String elements.
		 **/
		static Result		partitionBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 2 || 
				args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			
			Result sepRes = ctx->castArgument(args[1], DataType::String);
			if (sepRes.type != NumericConstant::Object || 
				sepRes.value.objectVal == nullptr || 
				!(sepRes.value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}

			String* strObj = static_cast<String*>(args[0].value.objectVal);
			String* sepObj = static_cast<String*>(sepRes.value.objectVal);

			size_t sourceLen = strObj->arrayLength();
			size_t sepLen = sepObj->arrayLength();

			if (sepLen == 0) { return Result{}; }

			size_t foundPos = static_cast<size_t>(-1);
			
			if (sourceLen >= sepLen) {
				for (size_t i = 0; i <= sourceLen - sepLen; ++i) {
					bool match = true;
					for (size_t j = 0; j < sepLen; ++j) {
						if (strObj->getCodePoint(i + j) != sepObj->getCodePoint(j)) {
							match = false;
							break;
						}
					}
					if (match) {
						foundPos = i;
						break;
					}
				}
			}

			String* s1 = ctx->allocateObject<String>();
			String* s2 = ctx->allocateObject<String>();
			String* s3 = ctx->allocateObject<String>();
			Vector* outVec = ctx->allocateObject<Vector>();

			if (!s1 || !s2 || !s3 || !outVec) { return Result{}; }

			if (foundPos != static_cast<size_t>(-1)) {
				for (size_t i = 0; i < foundPos; ++i) {
					s1->operator+=(strObj->arrayAccess(static_cast<int64_t>(i)));
				}
				for (size_t i = 0; i < sepLen; ++i) {
					s2->operator+=(sepObj->arrayAccess(static_cast<int64_t>(i)));
				}
				for (size_t i = foundPos + sepLen; i < sourceLen; ++i) {
					s3->operator+=(strObj->arrayAccess(static_cast<int64_t>(i)));
				}
			}
			else {
				for (size_t i = 0; i < sourceLen; ++i) {
					s1->operator+=(strObj->arrayAccess(static_cast<int64_t>(i)));
				}
			}

			outVec->resize(3);
			outVec->directAccess(0) = s1->createResult(); s1->incRef();
			outVec->directAccess(1) = s2->createResult(); s2->incRef();
			outVec->directAccess(2) = s3->createResult(); s3->incRef();

			return outVec->createResult();
		}

		/**
		 * Bridge for String.removeprefix().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Object Result containing the newly formatted String.
		 **/
		static Result		removePrefixBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr || !(args[0].value.objectVal->type() & BuiltInType_String)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || args[1].value.objectVal == nullptr || !(args[1].value.objectVal->type() & BuiltInType_String)) { return Result{}; }
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			String* prefixObj = static_cast<String*>(args[1].value.objectVal);
			
			try {
				String* resultStr = strObj->removeprefix(ctx, prefixObj->getUtf32());
				if (resultStr) { return resultStr->createResult(); }
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.removesuffix().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Object Result containing the newly formatted String.
		 **/
		static Result		removeSuffixBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr || !(args[0].value.objectVal->type() & BuiltInType_String)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || args[1].value.objectVal == nullptr || !(args[1].value.objectVal->type() & BuiltInType_String)) { return Result{}; }
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			String* suffixObj = static_cast<String*>(args[1].value.objectVal);
			
			try {
				String* resultStr = strObj->removesuffix(ctx, suffixObj->getUtf32());
				if (resultStr) { return resultStr->createResult(); }
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.replace().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Object Result containing the newly replaced String.
		 **/
		static Result		replaceBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 3 || args.size() > 4) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			
			if (args[1].type != NumericConstant::Object || 
				args[1].value.objectVal == nullptr || 
				!(args[1].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			
			if (args[2].type != NumericConstant::Object || 
				args[2].value.objectVal == nullptr || 
				!(args[2].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			
			int64_t count = -1;
			
			if (args.size() == 4) {
				if (args[3].type == NumericConstant::Signed) {
					count = args[3].value.intVal;
				}
				else if (args[3].type == NumericConstant::Unsigned) {
					count = static_cast<int64_t>(args[3].value.uintVal);
				}
				else {
					return Result{};
				}
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			String* oldStr = static_cast<String*>(args[1].value.objectVal);
			String* newStr = static_cast<String*>(args[2].value.objectVal);
			
			try {
				String* resultStr = strObj->replace(ctx, oldStr->getUtf32(), newStr->getUtf32(), count);
				if (resultStr) { return resultStr->createResult(); }
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.rfind().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Signed Integer Result containing the found index, or -1.
		 **/
		static Result		rfindBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			
			if (args.size() < 2 || args.size() > 4) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			
			if (args[1].type != NumericConstant::Object || 
				args[1].value.objectVal == nullptr || 
				!(args[1].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			
			int64_t start = 0;
			int64_t end = -1;
			
			if (args.size() >= 3) {
				if (args[2].type == NumericConstant::Signed) {
					start = args[2].value.intVal;
				}
				else if (args[2].type == NumericConstant::Unsigned) {
					start = static_cast<int64_t>(args[2].value.uintVal);
				}
				else {
					return Result{};
				}
			}
			
			if (args.size() == 4) {
				if (args[3].type == NumericConstant::Signed) {
					end = args[3].value.intVal;
				}
				else if (args[3].type == NumericConstant::Unsigned) {
					end = static_cast<int64_t>(args[3].value.uintVal);
				}
				else {
					return Result{};
				}
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			String* subObj = static_cast<String*>(args[1].value.objectVal);
			
			try {
				int64_t resultIdx = strObj->rfind(subObj->getUtf32(), start, end);
				
				Result res;
				res.type = NumericConstant::Signed;
				res.value.intVal = resultIdx;
				return res;
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.rjust().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Object Result containing the newly justified String.
		 **/
		static Result		rjustBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 2 || args.size() > 3) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}

			int64_t width = 0;

			if (args[1].type == NumericConstant::Signed) {
				width = args[1].value.intVal;
			}
			else if (args[1].type == NumericConstant::Unsigned) {
				width = static_cast<int64_t>(args[1].value.uintVal);
			}
			else {
				return Result{};
			}
			
			uint32_t fillCharCp = ' ';

			if (args.size() == 3) {
				if (args[2].type != NumericConstant::Object || 
					args[2].value.objectVal == nullptr || 
					!(args[2].value.objectVal->type() & BuiltInType_String)) {
					return Result{};
				}
				
				String* fillStr = static_cast<String*>(args[2].value.objectVal);
				
				if (fillStr->arrayLength() != 1) {
					return Result{};
				}
				
				fillCharCp = fillStr->getCodePoint(0);
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			try {
				size_t validWidth = width > 0 ? static_cast<size_t>(width) : 0;
				String* resultStr = strObj->rjust(ctx, validWidth, fillCharCp);
				
				if (resultStr) { return resultStr->createResult(); }
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.rpartition().
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (this string, separator).
		 * \return			Returns a Vector Result containing 3 String elements.
		 **/
		static Result		rpartitionBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 2 || 
				args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			
			Result sepRes = ctx->castArgument(args[1], DataType::String);
			if (sepRes.type != NumericConstant::Object || 
				sepRes.value.objectVal == nullptr || 
				!(sepRes.value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}

			String* strObj = static_cast<String*>(args[0].value.objectVal);
			String* sepObj = static_cast<String*>(sepRes.value.objectVal);

			size_t sourceLen = strObj->arrayLength();
			size_t sepLen = sepObj->arrayLength();

			if (sepLen == 0) { return Result{}; }

			size_t foundPos = static_cast<size_t>(-1);
			
			if (sourceLen >= sepLen) {
				for (size_t i = sourceLen - sepLen; i != static_cast<size_t>(-1); --i) {
					bool match = true;
					for (size_t j = 0; j < sepLen; ++j) {
						if (strObj->getCodePoint(i + j) != sepObj->getCodePoint(j)) {
							match = false;
							break;
						}
					}
					if (match) {
						foundPos = i;
						break;
					}
				}
			}

			String* s1 = ctx->allocateObject<String>();
			String* s2 = ctx->allocateObject<String>();
			String* s3 = ctx->allocateObject<String>();
			Vector* outVec = ctx->allocateObject<Vector>();

			if (!s1 || !s2 || !s3 || !outVec) { return Result{}; }

			if (foundPos != static_cast<size_t>(-1)) {
				for (size_t i = 0; i < foundPos; ++i) {
					s1->operator+=(strObj->arrayAccess(static_cast<int64_t>(i)));
				}
				for (size_t i = 0; i < sepLen; ++i) {
					s2->operator+=(sepObj->arrayAccess(static_cast<int64_t>(i)));
				}
				for (size_t i = foundPos + sepLen; i < sourceLen; ++i) {
					s3->operator+=(strObj->arrayAccess(static_cast<int64_t>(i)));
				}
			}
			else {
				for (size_t i = 0; i < sourceLen; ++i) {
					s3->operator+=(strObj->arrayAccess(static_cast<int64_t>(i)));
				}
			}

			outVec->resize(3);
			outVec->directAccess(0) = s1->createResult(); s1->incRef();
			outVec->directAccess(1) = s2->createResult(); s2->incRef();
			outVec->directAccess(2) = s3->createResult(); s3->incRef();

			return outVec->createResult();
		}

		/**
		 * Bridge for String.rstrip().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Object Result containing the newly stripped String.
		 **/
		static Result		rstripBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 1 || args.size() > 2) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || 
				args[0].value.objectVal == nullptr || 
				!(args[0].value.objectVal->type() & BuiltInType_String)) {
				return Result{};
			}
			
			std::u32string stripChars;
			
			if (args.size() == 2) {
				if (args[1].type != NumericConstant::Object || 
					args[1].value.objectVal == nullptr || 
					!(args[1].value.objectVal->type() & BuiltInType_String)) {
					return Result{};
				}
				
				String* charStr = static_cast<String*>(args[1].value.objectVal);
				stripChars = charStr->getUtf32();
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			try {
				String* resultStr = strObj->rstrip(ctx, stripChars);
				if (resultStr) { return resultStr->createResult(); }
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.split().
		 * Splits the string into a vector of words using the specified separator.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (this string, optional separator, optional maxsplit).
		 * \return			Returns a Vector Result containing the split String elements.
		 **/
		static Result		splitBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr || !(args[0].value.objectVal->type() & BuiltInType_String)) { return Result{}; }

			String* strObj = static_cast<String*>(args[0].value.objectVal);
			size_t sourceLen = strObj->arrayLength();

			String* sepObj = nullptr;
			int64_t maxsplit = -1;

			if (args.size() > 1 && args[1].type == NumericConstant::Object && args[1].value.objectVal != nullptr && (args[1].value.objectVal->type() & BuiltInType_String)) {
				sepObj = static_cast<String*>(args[1].value.objectVal);
			}

			if (args.size() > 2 && args[2].type == NumericConstant::Signed) {
				maxsplit = args[2].value.intVal;
			}

			Vector* outVec = ctx->allocateObject<Vector>();
			if (!outVec) { return Result{}; }

			std::vector<String*> parts;

			if (sepObj) {
				size_t sepLen = sepObj->arrayLength();
				if (sepLen == 0) { return Result{}; }

				size_t startPos = 0;
				int64_t splits = 0;

				while (startPos <= sourceLen) {
					if (maxsplit != -1 && splits >= maxsplit) {
						String* rem = ctx->allocateObject<String>();
						for (size_t i = startPos; i < sourceLen; ++i) {
							rem->operator+=(strObj->arrayAccess(static_cast<int64_t>(i)));
						}
						parts.push_back(rem);
						break;
					}

					size_t foundPos = static_cast<size_t>(-1);
					if (sourceLen >= sepLen && startPos <= sourceLen - sepLen) {
						for (size_t i = startPos; i <= sourceLen - sepLen; ++i) {
							bool match = true;
							for (size_t j = 0; j < sepLen; ++j) {
								if (strObj->getCodePoint(i + j) != sepObj->getCodePoint(j)) {
									match = false;
									break;
								}
							}
							if (match) {
								foundPos = i;
								break;
							}
						}
					}

					String* part = ctx->allocateObject<String>();
					if (foundPos != static_cast<size_t>(-1)) {
						for (size_t i = startPos; i < foundPos; ++i) {
							part->operator+=(strObj->arrayAccess(static_cast<int64_t>(i)));
						}
						parts.push_back(part);
						startPos = foundPos + sepLen;
						splits++;
					}
					else {
						for (size_t i = startPos; i < sourceLen; ++i) {
							part->operator+=(strObj->arrayAccess(static_cast<int64_t>(i)));
						}
						parts.push_back(part);
						break;
					}
				}
			}
			else {
				size_t i = 0;
				int64_t splits = 0;

				while (i < sourceLen) {
					while (i < sourceLen) {
						uint32_t cp = strObj->getCodePoint(i);
						if (!Character::isWhiteSpace(cp)) { break; }
						i++;
					}

					if (i == sourceLen) { break; }

					if (maxsplit != -1 && splits >= maxsplit) {
						String* rem = ctx->allocateObject<String>();
						for (size_t j = i; j < sourceLen; ++j) {
							rem->operator+=(strObj->arrayAccess(static_cast<int64_t>(j)));
						}
						parts.push_back(rem);
						break;
					}

					size_t startPos = i;
					while (i < sourceLen) {
						uint32_t cp = strObj->getCodePoint(i);
						if (Character::isWhiteSpace(cp)) { break; }
						i++;
					}

					String* part = ctx->allocateObject<String>();
					for (size_t j = startPos; j < i; ++j) {
						part->operator+=(strObj->arrayAccess(static_cast<int64_t>(j)));
					}
					parts.push_back(part);
					splits++;
				}
			}

			outVec->resize(parts.size());
			for (size_t i = 0; i < parts.size(); ++i) {
				outVec->directAccess(i) = parts[i]->createResult();
				parts[i]->incRef();
			}

			return outVec->createResult();
		}

		/**
		 * Bridge for String.splitlines().
		 * Splits the string at line boundaries and returns a vector of the lines.
		 * Supports an optional keepends parameter to retain the line break characters.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (this string, optional keepends).
		 * \return			Returns a Vector Result containing the extracted lines.
		 **/
		static Result		splitlinesBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr || !(args[0].value.objectVal->type() & BuiltInType_String)) { return Result{}; }

			String* strObj = static_cast<String*>(args[0].value.objectVal);
			size_t sourceLen = strObj->arrayLength();

			bool keepends = false;

			if (args.size() > 1) {
				const Result& keepRes = args[1];
				
				if (keepRes.type == NumericConstant::Signed) {
					keepends = (keepRes.value.intVal != 0);
				}
				else if (keepRes.type == NumericConstant::Unsigned) {
					keepends = (keepRes.value.uintVal != 0);
				}
				else if (keepRes.type == NumericConstant::Floating) {
					keepends = (keepRes.value.doubleVal != 0.0);
				}
				else if (keepRes.type == NumericConstant::Object && keepRes.value.objectVal != nullptr && !(keepRes.value.objectVal->type() & BuiltInType_Map)) {
					keepends = (keepRes.value.objectVal->arrayLength() > 0);
				}
			}

			Vector* outVec = ctx->allocateObject<Vector>();
			if (!outVec) { return Result{}; }

			std::vector<String*> parts;
			size_t i = 0;
			size_t startPos = 0;

			while (i < sourceLen) {
				uint32_t cp = strObj->getCodePoint(i);
				
				// Standard Python line boundary checks.
				bool isBreak = false;
				size_t breakLen = 1;
				
				if (cp == '\n' || cp == '\r' || cp == '\v' || cp == '\f' || 
					cp == 0x1C || cp == 0x1D || cp == 0x1E || 
					cp == 0x85 || cp == 0x2028 || cp == 0x2029) {
					
					isBreak = true;
					if (cp == '\r' && i + 1 < sourceLen && strObj->getCodePoint(i + 1) == '\n') {
						breakLen = 2;
					}
				}

				if (isBreak) {
					String* part = ctx->allocateObject<String>();
					
					for (size_t j = startPos; j < i; ++j) {
						part->operator+=(strObj->arrayAccess(static_cast<int64_t>(j)));
					}
					
					if (keepends) {
						for (size_t j = i; j < i + breakLen; ++j) {
							part->operator+=(strObj->arrayAccess(static_cast<int64_t>(j)));
						}
					}
					
					parts.push_back(part);
					i += breakLen;
					startPos = i;
				}
				else {
					i++;
				}
			}

			if (startPos < sourceLen) {
				String* part = ctx->allocateObject<String>();
				for (size_t j = startPos; j < sourceLen; ++j) {
					part->operator+=(strObj->arrayAccess(static_cast<int64_t>(j)));
				}
				parts.push_back(part);
			}

			outVec->resize(parts.size());
			for (size_t j = 0; j < parts.size(); ++j) {
				outVec->directAccess(j) = parts[j]->createResult();
				parts[j]->incRef();
			}

			return outVec->createResult();
		}

		/**
		 * Bridge for String.startswith().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Signed Integer Result containing 1 for true, 0 for false.
		 **/
		static Result		startsWithBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			static_cast<void>(ctx);
			
			if (args.size() < 2 || args.size() > 4) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr || !(args[0].value.objectVal->type() & BuiltInType_String)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || args[1].value.objectVal == nullptr || !(args[1].value.objectVal->type() & BuiltInType_String)) { return Result{}; }
			
			int64_t start = 0;
			int64_t end = -1;
			
			if (args.size() >= 3) {
				if (args[2].type == NumericConstant::Signed) {
					start = args[2].value.intVal;
				}
				else if (args[2].type == NumericConstant::Unsigned) {
					start = static_cast<int64_t>(args[2].value.uintVal);
				}
				else {
					return Result{};
				}
			}
			
			if (args.size() == 4) {
				if (args[3].type == NumericConstant::Signed) {
					end = args[3].value.intVal;
				}
				else if (args[3].type == NumericConstant::Unsigned) {
					end = static_cast<int64_t>(args[3].value.uintVal);
				}
				else {
					return Result{};
				}
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			String* prefixObj = static_cast<String*>(args[1].value.objectVal);
			
			try {
				return Result::make(strObj->startswith(prefixObj->getUtf32(), start, end));
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.strip().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Object Result containing the newly stripped String.
		 **/
		static Result		stripBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 1 || args.size() > 2) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr || !(args[0].value.objectVal->type() & BuiltInType_String)) { return Result{}; }
			
			std::u32string stripChars;
			
			if (args.size() == 2) {
				if (args[1].type != NumericConstant::Object || args[1].value.objectVal == nullptr || !(args[1].value.objectVal->type() & BuiltInType_String)) { return Result{}; }
				
				String* charStr = static_cast<String*>(args[1].value.objectVal);
				stripChars = charStr->getUtf32();
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			try {
				String* resultStr = strObj->strip(ctx, stripChars);
				if (resultStr) { return resultStr->createResult(); }
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.swapcase().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Object Result containing the case-swapped String.
		 **/
		static Result		swapcaseBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr || !(args[0].value.objectVal->type() & BuiltInType_String)) { return Result{}; }
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			try {
				String* resultStr = strObj->swapcase(ctx);
				if (resultStr) { return resultStr->createResult(); }
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.title().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Object Result containing the titlecased String.
		 **/
		static Result		titleBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr || !(args[0].value.objectVal->type() & BuiltInType_String)) { return Result{}; }
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			try {
				String* resultStr = strObj->title(ctx);
				if (resultStr) { return resultStr->createResult(); }
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for String.upper().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Object Result containing the uppercase String.
		 **/
		static Result		upperBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type == NumericConstant::Unsigned) {
				char32_t outSeq[3];
				auto lowerCount = Case::getUpperSequence(char32_t(args[0].value.uintVal), outSeq);
				if (lowerCount == 1) {
					return Result::make(uint64_t(outSeq[0]));
				}
				else if (lowerCount) {
					std::string result;
					try {
						for (uint32_t j = 0; j < lowerCount; ++j) {
							Text::appendUtf8(result, static_cast<uint32_t>(outSeq[j]));
						}

						String* newStr = ctx->allocateObject<String>();
						if (newStr) {
							if (!newStr->assignUtf8(result.data(), result.length())) {
								ctx->deallocateObject(newStr);
								throw ErrorCode::Object_Initialization_Failed;
							}
							return newStr->createResult();
						}
					}
					catch (...) { throw ErrorCode::Out_Of_Memory; }
					return Result{};	// Creates an invalid return.
				}
				return args[0];
			}
			else if (args[0].type == NumericConstant::Signed) {
				char32_t outSeq[3];
				auto lowerCount = Case::getUpperSequence(char32_t(args[0].value.uintVal), outSeq);
				if (lowerCount == 1) {
					return Result::make(int64_t(outSeq[0]));
				}
				else if (lowerCount) {
					std::string result;
					try {
						for (uint32_t j = 0; j < lowerCount; ++j) {
							Text::appendUtf8(result, static_cast<uint32_t>(outSeq[j]));
						}

						String* newStr = ctx->allocateObject<String>();
						if (newStr) {
							if (!newStr->assignUtf8(result.data(), result.length())) {
								ctx->deallocateObject(newStr);
								throw ErrorCode::Object_Initialization_Failed;
							}
							return newStr->createResult();
						}
					}
					catch (...) { throw ErrorCode::Out_Of_Memory; }
					return Result{};	// Creates an invalid return.
				}
				return args[0];
			}
			else if (args[0].type == NumericConstant::Object && args[0].value.objectVal && (args[0].value.objectVal->type() & BuiltInType_String)) {
			
				String* strObj = static_cast<String*>(args[0].value.objectVal);
			
				try {
					String* resultStr = strObj->upper(ctx);
					if (resultStr) { return resultStr->createResult(); }
				}
				catch (...) {
					throw ErrorCode::Out_Of_Memory;
				}
			}
			return Result{};
		}

		/**
		 * Bridge for String.zfill().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Object Result containing the newly zero-padded String.
		 **/
		static Result		zfillBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr || !(args[0].value.objectVal->type() & BuiltInType_String)) { return Result{}; }

			int64_t width = 0;

			if (args[1].type == NumericConstant::Signed) {
				width = args[1].value.intVal;
			}
			else if (args[1].type == NumericConstant::Unsigned) {
				width = static_cast<int64_t>(args[1].value.uintVal);
			}
			else {
				return Result{};
			}
			
			String* strObj = static_cast<String*>(args[0].value.objectVal);
			
			try {
				size_t validWidth = width > 0 ? static_cast<size_t>(width) : 0;
				String* resultStr = strObj->zfill(ctx, validWidth);
				if (resultStr) { return resultStr->createResult(); }
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for append().
		 * Appends an item to the end of a Vector or String object.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (this object, item to append).
		 * \return			Returns an empty Result.
		 **/
		static Result		appendBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 2 || args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr) { return Result{}; }

			uint32_t objType = args[0].value.objectVal->type();

			if (objType & BuiltInType_String) {
				String* strObj = static_cast<String*>(args[0].value.objectVal);
				if (strObj->pushBack(args[1])) { return strObj->createResult(); }
				ctx->deallocateObject(strObj);
			}
			else if (objType & BuiltInType_Vector) {
				Vector* vecObj = static_cast<Vector*>(args[0].value.objectVal);
				if (vecObj->pushBack(args[1])) { return vecObj->createResult(); }
				ctx->deallocateObject(vecObj);
			}

			return Result{};
		}

		/**
		 * Bridge for Object.at().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Object Result containing the element.
		 **/
		static Result		atBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr) { return Result{}; }
			
			int64_t index = 0;
			if (args[1].type == NumericConstant::Signed) {
				index = args[1].value.intVal;
			}
			else if (args[1].type == NumericConstant::Unsigned) {
				index = static_cast<int64_t>(args[1].value.uintVal);
			}
			else {
				return Result{};
			}
			
			Object* obj = args[0].value.objectVal;
			
			try {
				if (obj->type() & BuiltInType_Vector) {
					return static_cast<Vector*>(obj)->at(index);
				}
				else if (obj->type() & BuiltInType_String) {
					return static_cast<String*>(obj)->at(index);
				}
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for clear().
		 * Removes all items from the object.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (this object).
		 * \return			Returns a Result containing the cleared object.
		 **/
		static Result		clearBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr) { return Result{}; }

			args[0].value.objectVal->clear();

			return args[0].value.objectVal->createResult();
		}

		/**
		 * Bridge for copy().
		 * Returns a shallow copy of the target object.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (this object).
		 * \return			Returns a Result containing the copied object.
		 **/
		static Result		copyBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr) { return Result{}; }

			return args[0].value.objectVal->copy();
		}

		/**
		 * Bridge for Object.size() and len(Object).
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Unsigned Result containing the length of the object.
		 **/
		static Result		lengthBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr) { return Result{}; }
			
			Object* obj = args[0].value.objectVal;
			
			try {
				Result res;
				res.type = NumericConstant::Unsigned;
				res.value.uintVal = static_cast<uint64_t>(obj->arrayLength());
				return res;
			}
			catch (...) {
				throw ErrorCode::Out_Of_Memory;
			}
			
			return Result{};
		}

		/**
		 * Bridge for pop().
		 * Removes the item at the given index (default is -1, the last item) and returns the object itself.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (this object, optional index).
		 * \return			Returns a Result containing the modified object.
		 **/
		static Result		popBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr) { return Result{}; }

			uint32_t objType = args[0].value.objectVal->type();
			int64_t idx = -1;

			if (args.size() > 1) {
				const Result& idxRes = args[1];
				if (idxRes.type == NumericConstant::Signed) {
					idx = static_cast<int64_t>(idxRes.value.intVal);
				}
				else if (idxRes.type == NumericConstant::Unsigned) {
					idx = static_cast<int64_t>(idxRes.value.uintVal);
				}
				else if (idxRes.type == NumericConstant::Floating) {
					idx = static_cast<int64_t>(idxRes.value.doubleVal);
				}
				else { return Result{}; }
			}

			if (objType & BuiltInType_String) {
				String* strObj = static_cast<String*>(args[0].value.objectVal);
				return strObj->pop(idx);
			}
			else if (objType & BuiltInType_Vector) {
				Vector* vecObj = static_cast<Vector*>(args[0].value.objectVal);
				return vecObj->pop(idx);
			}

			return Result{};
		}

		/**
		 * Bridge for Object.push_back().
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns an Invalid Result (void return).
		 **/
		static Result		pushBackBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			
			if (args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr) { return Result{}; }
			
			Object* obj = args[0].value.objectVal;
			
			try {
				if (obj->type() & BuiltInType_Vector) {
					if (!static_cast<Vector*>(obj)->pushBack(args[1])) { return Result{}; }
				}
				else if (obj->type() & BuiltInType_String) {
					if (!static_cast<String*>(obj)->pushBack(args[1])) { return Result{}; }
				}
			}
			catch (...) { throw ErrorCode::Out_Of_Memory; }
			
			return obj->createResult();
		}

		/**
		 * Bridge for remove().
		 * Removes the first occurrence of the specified value from the object.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (this object, value to remove).
		 * \return			Returns the result of the object's remove method.
		 **/
		static Result		removeBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 2 || args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr) { return Result{}; }

			return args[0].value.objectVal->remove(args[1]);
		}

		/**
		 * Bridge for reverse().
		 * Reverses the elements of the String or Vector in place.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (this object).
		 * \return			Returns a Result containing the modified object.
		 **/
		static Result		reverseBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || args[0].type != NumericConstant::Object || args[0].value.objectVal == nullptr) { return Result{}; }

			uint32_t objType = args[0].value.objectVal->type();

			if (objType & BuiltInType_String) {
				String* strObj = static_cast<String*>(args[0].value.objectVal);
				return strObj->reverse();
			}
			else if (objType & BuiltInType_Vector) {
				Vector* vecObj = static_cast<Vector*>(args[0].value.objectVal);
				return vecObj->reverse();
			}

			return Result{};
		}


		// =======================================================================================================
		// MATH BRIDGES
		// =======================================================================================================

		/**
		 * Bridge for Math::min.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the minimum value.
		 **/
		static Result		minBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || !args[0].isPrimitive() || !args[1].isPrimitive()) { return Result{}; }
			
			NumericConstant common = ExecutionContext::getCastType(args[0].type, args[1].type);
			Result l = ctx->convertResult(args[0], common);
			Result r = ctx->convertResult(args[1], common);
			
			if (common == NumericConstant::Floating) { return Result::make(Math::min(l.value.doubleVal, r.value.doubleVal)); }
			if (common == NumericConstant::Signed) { return Result::make(Math::min(l.value.intVal, r.value.intVal)); }
			if (common == NumericConstant::Unsigned) { return Result::make(Math::min(l.value.uintVal, r.value.uintVal)); }
			
			return Result{};
		}

		/**
		 * Bridge for Math::max.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the maximum value.
		 **/
		static Result		maxBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || !args[0].isPrimitive() || !args[1].isPrimitive()) { return Result{}; }
			
			NumericConstant common = ExecutionContext::getCastType(args[0].type, args[1].type);
			Result l = ctx->convertResult(args[0], common);
			Result r = ctx->convertResult(args[1], common);
			
			if (common == NumericConstant::Floating) { return Result::make(Math::max(l.value.doubleVal, r.value.doubleVal)); }
			if (common == NumericConstant::Signed) { return Result::make(Math::max(l.value.intVal, r.value.intVal)); }
			if (common == NumericConstant::Unsigned) { return Result::make(Math::max(l.value.uintVal, r.value.uintVal)); }
			
			return Result{};
		}

		/**
		 * Bridge for Math::clamp.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the clamped value.
		 **/
		static Result		clampBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 3 || !args[0].isPrimitive() || !args[1].isPrimitive() || !args[2].isPrimitive()) { return Result{}; }
			
			NumericConstant common = ExecutionContext::getCastType(ExecutionContext::getCastType(args[0].type, args[1].type), args[2].type);
			Result v = ctx->convertResult(args[0], common);
			Result minVal = ctx->convertResult(args[1], common);
			Result maxVal = ctx->convertResult(args[2], common);
			
			if (common == NumericConstant::Floating) { return Result::make(Math::clamp(v.value.doubleVal, minVal.value.doubleVal, maxVal.value.doubleVal)); }
			if (common == NumericConstant::Signed) { return Result::make(Math::clamp(v.value.intVal, minVal.value.intVal, maxVal.value.intVal)); }
			if (common == NumericConstant::Unsigned) { return Result::make(Math::clamp(v.value.uintVal, minVal.value.uintVal, maxVal.value.uintVal)); }
			
			return Result{};
		}

		/**
		 * Bridge for Math::frac.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the fractional part.
		 **/
		static Result		fracBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 1 || !args[0].isPrimitive()) { return Result{}; }
			Result val = ctx->convertResult(args[0], NumericConstant::Floating);
			return Result::make(Math::frac(val.value.doubleVal));
		}

		/**
		 * Bridge for Math::step.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the calculated step.
		 **/
		static Result		stepBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || !args[0].isPrimitive() || !args[1].isPrimitive()) { return Result{}; }
			Result edge = ctx->convertResult(args[0], NumericConstant::Floating);
			Result x = ctx->convertResult(args[1], NumericConstant::Floating);
			return Result::make(Math::step(edge.value.doubleVal, x.value.doubleVal));
		}

		/**
		 * Bridge for Math::sinc.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the sinc evaluation.
		 **/
		static Result		sincBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 1 || !args[0].isPrimitive()) { return Result{}; }
			Result val = ctx->convertResult(args[0], NumericConstant::Floating);
			return Result::make(Math::sinc(val.value.doubleVal));
		}

		/**
		 * Bridge for Math::relativeEpsilon.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing 1 if the values are within epsilon distance, otherwise 0.
		 **/
		static Result		relativeEpsilonBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 3 || !args[0].isPrimitive() || !args[1].isPrimitive() || !args[2].isPrimitive()) { 
				return Result{}; 
			}
			
			double left = ctx->convertResult(args[0], NumericConstant::Floating).value.doubleVal;
			double right = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
			double epsilon = ctx->convertResult(args[2], NumericConstant::Floating).value.doubleVal;
			
			bool isEqual = Math::relativeEpsilon(left, right, epsilon);
			
			return Result::make(static_cast<int64_t>(isEqual ? 1 : 0));
		}

		/**
		 * Bridge for Math::sinExact.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the exact sine.
		 **/
		static Result		sinExactBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 1 || !args[0].isPrimitive()) { return Result{}; }
			Result val = ctx->convertResult(args[0], NumericConstant::Floating);
			return Result::make(Math::sinExact(val.value.doubleVal));
		}

		/**
		 * Bridge for Math::cosExact.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the exact cosine.
		 **/
		static Result		cosExactBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 1 || !args[0].isPrimitive()) { return Result{}; }
			Result val = ctx->convertResult(args[0], NumericConstant::Floating);
			return Result::make(Math::cosExact(val.value.doubleVal));
		}

		/**
		 * Bridge for Math::lcm.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the least common multiple.
		 **/
		static Result		lcmBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || !args[0].isPrimitive() || !args[1].isPrimitive()) { return Result{}; }
			
			NumericConstant common = ExecutionContext::getCastType(args[0].type, args[1].type);
			if (common == NumericConstant::Floating) { common = NumericConstant::Signed; }
			
			Result l = ctx->convertResult(args[0], common);
			Result r = ctx->convertResult(args[1], common);
			
			if (common == NumericConstant::Signed) { return Result::make(Math::lcm(l.value.intVal, r.value.intVal)); }
			if (common == NumericConstant::Unsigned) { return Result::make(Math::lcm(l.value.uintVal, r.value.uintVal)); }
			
			return Result{};
		}

		/**
		 * Bridge for Math::lcmChecked.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the checked least common multiple.
		 **/
		/*static Result		lcmCheckedBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || !args[0].isPrimitive() || !args[1].isPrimitive()) { return Result{}; }
			
			NumericConstant common = ExecutionContext::getCastType(args[0].type, args[1].type);
			if (common == NumericConstant::Floating) { common = NumericConstant::Signed; }
			
			Result l = ctx->convertResult(args[0], common);
			Result r = ctx->convertResult(args[1], common);
			
			if (common == NumericConstant::Signed) { return Result::make(Math::lcmChecked(l.value.intVal, r.value.intVal)); }
			if (common == NumericConstant::Unsigned) { return Result::make(Math::lcmChecked(l.value.uintVal, r.value.uintVal)); }
			
			return Result{};
		}*/


		// =======================================================================================================
		// COLOR / GAMMA TRANSFER BRIDGES
		// =======================================================================================================
		/**
		 * Macro helper to automatically generate uniform execution context bridges for single-argument Math functions.
		 * Provides the requisite type conversion and Result generation.
		 * 
		 * \param funcName		The name of the Math function to bridge.
		 **/
#define VE_MATH_GAMMA_BRIDGE(funcName)																						\
	static Result funcName##Bridge(ExecutionContext* ctx, const std::vector<Result>& args) {								\
		if (args.size() != 1 || !args[0].isPrimitive()) { return Result{}; }												\
		Result val = ctx->convertResult(args[0], NumericConstant::Floating);												\
		return Result::make(Math::funcName(val.value.doubleVal));															\
	}

		VE_MATH_GAMMA_BRIDGE(linearToSRgb)
		VE_MATH_GAMMA_BRIDGE(sRgbToLinear)
		VE_MATH_GAMMA_BRIDGE(pow2_2ToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToPow2_2)
		VE_MATH_GAMMA_BRIDGE(smpte240MToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToSmpte240M)
		VE_MATH_GAMMA_BRIDGE(sLog2ToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToSLog2)
		VE_MATH_GAMMA_BRIDGE(canonLogToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToCanonLog)
		VE_MATH_GAMMA_BRIDGE(viperToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToViper)
		VE_MATH_GAMMA_BRIDGE(acesCgToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToAcesCg)
		VE_MATH_GAMMA_BRIDGE(sRgbToLinearPrecise)
		VE_MATH_GAMMA_BRIDGE(linearToSRgbPrecise)
		VE_MATH_GAMMA_BRIDGE(colorLcdToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToColorLcd)
		VE_MATH_GAMMA_BRIDGE(smpte170MToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToSmpte170M)
		VE_MATH_GAMMA_BRIDGE(smpte170MToLinearPrecise)
		VE_MATH_GAMMA_BRIDGE(linearToSmpte170MPrecise)
		VE_MATH_GAMMA_BRIDGE(dciP3ToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToDciP3)
		VE_MATH_GAMMA_BRIDGE(genericRgbToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToGenericRgb)
		VE_MATH_GAMMA_BRIDGE(pow2_8ToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToPow2_8)
		VE_MATH_GAMMA_BRIDGE(adobeRgbToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToAdobeRgb)
		VE_MATH_GAMMA_BRIDGE(smpte240MToLinearPrecise)
		VE_MATH_GAMMA_BRIDGE(linearToSmpte240MPrecise)
		VE_MATH_GAMMA_BRIDGE(acesCcToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToAcesCc)
		VE_MATH_GAMMA_BRIDGE(rommRgbToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToRommRgb)
		VE_MATH_GAMMA_BRIDGE(rimmRgbToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToRimmRgb)
		VE_MATH_GAMMA_BRIDGE(erimmRgbToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToErimmRgb)
		VE_MATH_GAMMA_BRIDGE(sLogToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToSLog)
		VE_MATH_GAMMA_BRIDGE(sLog3ToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToSLog3)
		VE_MATH_GAMMA_BRIDGE(protuneToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToProtune)
		VE_MATH_GAMMA_BRIDGE(canonLog2ToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToCanonLog2)
		VE_MATH_GAMMA_BRIDGE(canonLog3ToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToCanonLog3)
		VE_MATH_GAMMA_BRIDGE(aribStdB67ToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToAribStdB67)
		VE_MATH_GAMMA_BRIDGE(panalogToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToPanalog)
		VE_MATH_GAMMA_BRIDGE(crtProper2ToLinear)
		VE_MATH_GAMMA_BRIDGE(linearToCrtProper2)

#undef VE_MATH_GAMMA_BRIDGE

		/**
		 * Bridge for Math::crtProperToLinear.
		 * Allows up to 3 arguments, resolving defaults for omitted parameters.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the linear converted value.
		 **/
		static Result		crtProperToLinearBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || args.size() > 3) { return Result{}; }
			
			for (const auto& arg : args) {
				if (!arg.isPrimitive()) { return Result{}; }
			}
			
			double val = ctx->convertResult(args[0], NumericConstant::Floating).value.doubleVal;
			double lw = 1.0;
			double b = 0.0181;
			
			if (args.size() > 1) { lw = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal; }
			if (args.size() > 2) { b = ctx->convertResult(args[2], NumericConstant::Floating).value.doubleVal; }
			
			return Result::make(Math::crtProperToLinear(val, lw, b));
		}

		/**
		 * Bridge for Math::linearToCrtProper.
		 * Allows up to 3 arguments, resolving defaults for omitted parameters.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the proper CRT converted value.
		 **/
		static Result		linearToCrtProperBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || args.size() > 3) { return Result{}; }
			
			for (const auto& arg : args) {
				if (!arg.isPrimitive()) { return Result{}; }
			}
			
			double val = ctx->convertResult(args[0], NumericConstant::Floating).value.doubleVal;
			double lw = 1.0;
			double b = 0.0181;
			
			if (args.size() > 1) { lw = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal; }
			if (args.size() > 2) { b = ctx->convertResult(args[2], NumericConstant::Floating).value.doubleVal; }
			
			return Result::make(Math::linearToCrtProper(val, lw, b));
		}

		/**
		 * Bridge for Math::xyzToChromaticity.
		 * 
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (x, y, z).
		 * \return			Returns a Vector Result containing [chromaX, chromaY].
		 **/
		static Result		xyzToChromaticityBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 3) {
				return Result{};
			}

			double x = args[0].value.doubleVal;
			double y = args[1].value.doubleVal;
			double z = args[2].value.doubleVal;
			
			double chromaX = 0.0;
			double chromaY = 0.0;
			
			Math::xyzToChromaticity(x, y, z, chromaX, chromaY);

			Vector* outVec = ctx->allocateObject<Vector>();
			if (!outVec) {
				return Result{};
			}

			outVec->resize(2);
			outVec->directAccess(0) = Result::make(chromaX);
			outVec->directAccess(1) = Result::make(chromaY);

			return outVec->createResult();
		}

		/**
		 * Bridge for Math::chromaticityToXyz.
		 * 
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (chromaX, chromaY, y0).
		 * \return			Returns a Vector Result containing [X, Z].
		 **/
		static Result		chromaticityToXyzBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 3) { return Result{}; }

			double chromaX = args[0].value.doubleVal;
			double chromaY = args[1].value.doubleVal;
			double y0 = args[2].value.doubleVal;
			
			double x0 = 0.0;
			double z0 = 0.0;
			
			Math::chromaticityToXyz(chromaX, chromaY, y0, x0, z0);

			Vector* outVec = ctx->allocateObject<Vector>();
			if (!outVec) { return Result{}; }

			outVec->resize(2);
			outVec->directAccess(0) = Result::make(x0);
			outVec->directAccess(1) = Result::make(z0);

			return outVec->createResult();
		}

		/**
		 * Bridge for Math::rgbToHsl.
		 * 
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (r, g, b).
		 * \return			Returns a Vector Result containing [h, s, l].
		 **/
		static Result		rgbToHslBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 3) { return Result{}; }

			double r = args[0].value.doubleVal;
			double g = args[1].value.doubleVal;
			double b = args[2].value.doubleVal;
			
			double h = 0.0;
			double s = 0.0;
			double l = 0.0;
			
			Math::rgbToHsl(r, g, b, h, s, l);

			Vector* outVec = ctx->allocateObject<Vector>();
			if (!outVec) { return Result{}; }

			outVec->resize(3);
			outVec->directAccess(0) = Result::make(h);
			outVec->directAccess(1) = Result::make(s);
			outVec->directAccess(2) = Result::make(l);

			return outVec->createResult();
		}

		/**
		 * Bridge for Math::hslToRgb.
		 * 
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (h, s, l).
		 * \return			Returns a Vector Result containing [r, g, b].
		 **/
		static Result		hslToRgbBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 3) { return Result{}; }

			double h = args[0].value.doubleVal;
			double s = args[1].value.doubleVal;
			double l = args[2].value.doubleVal;
			
			double r = 0.0;
			double g = 0.0;
			double b = 0.0;
			
			Math::hslToRgb(h, s, l, r, g, b);

			Vector* outVec = ctx->allocateObject<Vector>();
			if (!outVec) { return Result{}; }

			outVec->resize(3);
			outVec->directAccess(0) = Result::make(r);
			outVec->directAccess(1) = Result::make(g);
			outVec->directAccess(2) = Result::make(b);

			return outVec->createResult();
		}

		/**
		 * Bridge for Math::rgbToHsv.
		 * 
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (r, g, b).
		 * \return			Returns a Vector Result containing [h, s, v].
		 **/
		static Result		rgbToHsvBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 3) { return Result{}; }

			double r = args[0].value.doubleVal;
			double g = args[1].value.doubleVal;
			double b = args[2].value.doubleVal;
			
			double h = 0.0;
			double s = 0.0;
			double v = 0.0;
			
			Math::rgbToHsv(r, g, b, h, s, v);

			Vector* outVec = ctx->allocateObject<Vector>();
			if (!outVec) { return Result{}; }

			outVec->resize(3);
			outVec->directAccess(0) = Result::make(h);
			outVec->directAccess(1) = Result::make(s);
			outVec->directAccess(2) = Result::make(v);

			return outVec->createResult();
		}

		/**
		 * Bridge for Math::hsvToRgb.
		 * 
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (h, s, v).
		 * \return			Returns a Vector Result containing [r, g, b].
		 **/
		static Result		hsvToRgbBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 3) { return Result{}; }

			double h = args[0].value.doubleVal;
			double s = args[1].value.doubleVal;
			double v = args[2].value.doubleVal;
			
			double r = 0.0;
			double g = 0.0;
			double b = 0.0;
			
			Math::hsvToRgb(h, s, v, r, g, b);

			Vector* outVec = ctx->allocateObject<Vector>();
			if (!outVec) { return Result{}; }

			outVec->resize(3);
			outVec->directAccess(0) = Result::make(r);
			outVec->directAccess(1) = Result::make(g);
			outVec->directAccess(2) = Result::make(b);

			return outVec->createResult();
		}

		/**
		 * Bridge for Math::rgbToYcbcr.
		 * 
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (r, g, b, [kr, [kb, [lumaRange, [lumaOffset, [chromaRange, [chromaOffset]]]]]]).
		 * \return			Returns a Vector Result containing [y, u, v].
		 **/
		static Result		rgbToYcbcrBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 3) { return Result{}; }

			double r = args[0].value.doubleVal;
			double g = args[1].value.doubleVal;
			double b = args[2].value.doubleVal;
			
			double kr = args.size() > 3 ? args[3].value.doubleVal : 0.212639005871510;
			double kb = args.size() > 4 ? args[4].value.doubleVal : 0.072192315360734;
			double lumaRange = args.size() > 5 ? args[5].value.doubleVal : 219.0;
			double lumaOffset = args.size() > 6 ? args[6].value.doubleVal : 16.0;
			double chromaRange = args.size() > 7 ? args[7].value.doubleVal : 224.0;
			double chromaOffset = args.size() > 8 ? args[8].value.doubleVal : 128.0;
			
			double y = 0.0;
			double u = 0.0;
			double v = 0.0;
			
			Math::rgbToYcbcr(r, g, b, y, u, v, kr, kb, lumaRange, lumaOffset, chromaRange, chromaOffset);

			Vector* outVec = ctx->allocateObject<Vector>();
			if (!outVec) { return Result{}; }

			outVec->resize(3);
			outVec->directAccess(0) = Result::make(y);
			outVec->directAccess(1) = Result::make(u);
			outVec->directAccess(2) = Result::make(v);

			return outVec->createResult();
		}

		/**
		 * Bridge for Math::ycbcrToRgb.
		 * 
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (y, u, v, [kr, [kb, [lumaRange, [lumaOffset, [chromaRange, [chromaOffset]]]]]]).
		 * \return			Returns a Vector Result containing [r, g, b].
		 **/
		static Result		ycbcrToRgbBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 3) { return Result{}; }

			double y = args[0].value.doubleVal;
			double u = args[1].value.doubleVal;
			double v = args[2].value.doubleVal;
			
			double kr = args.size() > 3 ? args[3].value.doubleVal : 0.212639005871510;
			double kb = args.size() > 4 ? args[4].value.doubleVal : 0.072192315360734;
			double lumaRange = args.size() > 5 ? args[5].value.doubleVal : 219.0;
			double lumaOffset = args.size() > 6 ? args[6].value.doubleVal : 16.0;
			double chromaRange = args.size() > 7 ? args[7].value.doubleVal : 224.0;
			double chromaOffset = args.size() > 8 ? args[8].value.doubleVal : 128.0;
			
			double r = 0.0;
			double g = 0.0;
			double b = 0.0;
			
			Math::ycbcrToRgb(y, u, v, r, g, b, kr, kb, lumaRange, lumaOffset, chromaRange, chromaOffset);

			Vector* outVec = ctx->allocateObject<Vector>();
			if (!outVec) { return Result{}; }

			outVec->resize(3);
			outVec->directAccess(0) = Result::make(r);
			outVec->directAccess(1) = Result::make(g);
			outVec->directAccess(2) = Result::make(b);

			return outVec->createResult();
		}

		/**
		 * Bridge for Math::rgbToYuv.
		 * 
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (r, g, b, [kr, [kb, [wu, [wv]]]]).
		 * \return			Returns a Vector Result containing [y, u, v].
		 **/
		static Result		rgbToYuvBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 3) { return Result{}; }

			double r = args[0].value.doubleVal;
			double g = args[1].value.doubleVal;
			double b = args[2].value.doubleVal;
			
			double kr = args.size() > 3 ? args[3].value.doubleVal : 0.299;
			double kb = args.size() > 4 ? args[4].value.doubleVal : 0.114;
			double wu = args.size() > 5 ? args[5].value.doubleVal : 0.492111;
			double wv = args.size() > 6 ? args[6].value.doubleVal : 0.877283;
			
			double y = 0.0;
			double u = 0.0;
			double v = 0.0;
			
			Math::rgbToYuv(r, g, b, y, u, v, kr, kb, wu, wv);

			Vector* outVec = ctx->allocateObject<Vector>();
			if (!outVec) { return Result{}; }

			outVec->resize(3);
			outVec->directAccess(0) = Result::make(y);
			outVec->directAccess(1) = Result::make(u);
			outVec->directAccess(2) = Result::make(v);

			return outVec->createResult();
		}

		/**
		 * Bridge for Math::yuvToRgb.
		 * 
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (y, u, v, [kr, [kb, [wu, [wv]]]]).
		 * \return			Returns a Vector Result containing [r, g, b].
		 **/
		static Result		yuvToRgbBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 3) { return Result{}; }

			double y = args[0].value.doubleVal;
			double u = args[1].value.doubleVal;
			double v = args[2].value.doubleVal;
			
			double kr = args.size() > 3 ? args[3].value.doubleVal : 0.299;
			double kb = args.size() > 4 ? args[4].value.doubleVal : 0.114;
			double wu = args.size() > 5 ? args[5].value.doubleVal : 0.492111;
			double wv = args.size() > 6 ? args[6].value.doubleVal : 0.877283;
			
			double r = 0.0;
			double g = 0.0;
			double b = 0.0;
			
			Math::yuvToRgb(y, u, v, r, g, b, kr, kb, wu, wv);

			Vector* outVec = ctx->allocateObject<Vector>();
			if (!outVec) { return Result{}; }

			outVec->resize(3);
			outVec->directAccess(0) = Result::make(r);
			outVec->directAccess(1) = Result::make(g);
			outVec->directAccess(2) = Result::make(b);

			return outVec->createResult();
		}


		// =======================================================================================================
		// SCIPY BRIDGES
		// =======================================================================================================
		/**
		 * Bridge for Math::simpson1D and Math::simpsonStrided.
		 * Dynamically identifies and routes to the correct Simpson integration overload.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the integrated value.
		 **/
		static Result		simpsonBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || (args.size() != 1 && args.size() != 2 && args.size() != 4 && args.size() != 5)) { 
				return Result{}; 
			}

			// The first argument must always be the Y array.
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector)) {
				return Result{};
			}

			Vector* yVec = static_cast<Vector*>(args[0].value.objectVal);
			std::vector<double> yVals;
			if (!yVec->toPrimitiveArray<double, NumericConstant::Floating>(yVals)) {
				return Result{};
			}

			// Overload 1: simpson(y) -> defaults to dx = 1.0
			if (args.size() == 1) {
				return Result::make(Math::simpson1D(yVals));
			}

			// Overload 2: simpson(y, dx) OR simpson(y, xArray)
			if (args.size() == 2) {
				if (args[1].type == NumericConstant::Object && args[1].value.objectVal && (args[1].value.objectVal->type() & BuiltInType_Vector)) {
					Vector* xVec = static_cast<Vector*>(args[1].value.objectVal);
					std::vector<double> xVals;
					if (!xVec->toPrimitiveArray<double, NumericConstant::Floating>(xVals)) {
						return Result{};
					}
					return Result::make(Math::simpson1D(yVals, xVals));
				}
				else if (args[1].isPrimitive()) {
					double dx = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
					return Result::make(Math::simpson1D(yVals, dx));
				}
				return Result{};
			}

			// Overload 3: simpson(y, start, count, stride) OR simpson(y, start, stride, xArray)
			if (args.size() == 4) {
				size_t start = static_cast<size_t>(ctx->convertResult(args[1], NumericConstant::Signed).value.intVal);
				
				if (args[3].type == NumericConstant::Object && args[3].value.objectVal && (args[3].value.objectVal->type() & BuiltInType_Vector)) {
					size_t stride = static_cast<size_t>(ctx->convertResult(args[2], NumericConstant::Signed).value.intVal);
					Vector* xVec = static_cast<Vector*>(args[3].value.objectVal);
					std::vector<double> xVals;
					if (!xVec->toPrimitiveArray<double, NumericConstant::Floating>(xVals)) {
						return Result{};
					}
					return Result::make(Math::simpsonStrided(yVals, start, stride, xVals));
				}
				else if (args[2].isPrimitive() && args[3].isPrimitive()) {
					size_t count = static_cast<size_t>(ctx->convertResult(args[2], NumericConstant::Signed).value.intVal);
					size_t stride = static_cast<size_t>(ctx->convertResult(args[3], NumericConstant::Signed).value.intVal);
					return Result::make(Math::simpsonStrided(yVals, start, count, stride));
				}
				return Result{};
			}

			// Overload 4: simpson(y, start, count, stride, dx)
			if (args.size() == 5) {
				if (!args[1].isPrimitive() || !args[2].isPrimitive() || !args[3].isPrimitive() || !args[4].isPrimitive()) {
					return Result{};
				}
				
				size_t start = static_cast<size_t>(ctx->convertResult(args[1], NumericConstant::Signed).value.intVal);
				size_t count = static_cast<size_t>(ctx->convertResult(args[2], NumericConstant::Signed).value.intVal);
				size_t stride = static_cast<size_t>(ctx->convertResult(args[3], NumericConstant::Signed).value.intVal);
				double dx = ctx->convertResult(args[4], NumericConstant::Floating).value.doubleVal;
				
				return Result::make(Math::simpsonStrided(yVals, start, count, stride, dx));
			}

			return Result{};
		}

		/**
		 * Bridge for Math::cumulativeSimpson1D.
		 * Dynamically identifies and routes to the correct cumulative Simpson integration overload.
		 * Returns a new Vector containing the cumulative integrals.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the new integrated Vector.
		 **/
		static Result		cumulativeSimpsonBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || args.size() > 3) { 
				return Result{}; 
			}

			// The first argument must always be the Y array.
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector)) {
				return Result{};
			}

			Vector* yVec = static_cast<Vector*>(args[0].value.objectVal);
			std::vector<double> yVals;
			if (!yVec->toPrimitiveArray<double, NumericConstant::Floating>(yVals)) {
				return Result{};
			}

			std::vector<double> outVals;

			if (args.size() == 1) {
				outVals = Math::cumulativeSimpson1D(yVals);
			}
			else if (args.size() == 2) {
				if (args[1].type == NumericConstant::Object && args[1].value.objectVal && (args[1].value.objectVal->type() & BuiltInType_Vector)) {
					Vector* xVec = static_cast<Vector*>(args[1].value.objectVal);
					std::vector<double> xVals;
					if (!xVec->toPrimitiveArray<double, NumericConstant::Floating>(xVals)) {
						return Result{};
					}
					outVals = Math::cumulativeSimpson1D(yVals, xVals);
				}
				else if (args[1].isPrimitive()) {
					double dx = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
					outVals = Math::cumulativeSimpson1D(yVals, dx);
				} 
				else {
					return Result{};
				}
			}
			else if (args.size() == 3) {
				if (!args[2].isPrimitive()) {
					return Result{};
				}
				
				double initial = ctx->convertResult(args[2], NumericConstant::Floating).value.doubleVal;

				if (args[1].type == NumericConstant::Object && args[1].value.objectVal && (args[1].value.objectVal->type() & BuiltInType_Vector)) {
					Vector* xVec = static_cast<Vector*>(args[1].value.objectVal);
					std::vector<double> xVals;
					if (!xVec->toPrimitiveArray<double, NumericConstant::Floating>(xVals)) {
						return Result{};
					}
					outVals = Math::cumulativeSimpson1D(yVals, xVals, initial);
				}
				else if (args[1].isPrimitive()) {
					double dx = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
					outVals = Math::cumulativeSimpson1D(yVals, dx, initial);
				} 
				else {
					return Result{};
				}
			}

			// Allocate the resulting script Vector and convert the std::vector back into it.
			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec || !resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for Math::trapezoid1D and Math::trapezoidStrided.
		 * Dynamically identifies and routes to the correct trapezoid integration overload.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the integrated scalar value.
		 **/
		static Result		trapezoidBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || (args.size() != 1 && args.size() != 2 && args.size() != 4 && args.size() != 5)) { 
				return Result{}; 
			}

			// The first argument must always be the Y array.
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector)) {
				return Result{};
			}

			Vector* yVec = static_cast<Vector*>(args[0].value.objectVal);
			std::vector<double> yVals;
			if (!yVec->toPrimitiveArray<double, NumericConstant::Floating>(yVals)) {
				return Result{};
			}

			// Overload 1: trapezoid(y) -> defaults to dx = 1.0
			if (args.size() == 1) {
				return Result::make(Math::trapezoid1D(yVals));
			}

			// Overload 2: trapezoid(y, dx) OR trapezoid(y, xArray)
			if (args.size() == 2) {
				if (args[1].type == NumericConstant::Object && args[1].value.objectVal && (args[1].value.objectVal->type() & BuiltInType_Vector)) {
					Vector* xVec = static_cast<Vector*>(args[1].value.objectVal);
					std::vector<double> xVals;
					if (!xVec->toPrimitiveArray<double, NumericConstant::Floating>(xVals)) {
						return Result{};
					}
					return Result::make(Math::trapezoid1D(yVals, xVals));
				}
				else if (args[1].isPrimitive()) {
					double dx = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
					return Result::make(Math::trapezoid1D(yVals, dx));
				}
				return Result{};
			}

			// Overload 3: trapezoid(y, start, count, stride) OR trapezoid(y, start, stride, xArray)
			if (args.size() == 4) {
				size_t start = static_cast<size_t>(ctx->convertResult(args[1], NumericConstant::Signed).value.intVal);
				
				if (args[3].type == NumericConstant::Object && args[3].value.objectVal && (args[3].value.objectVal->type() & BuiltInType_Vector)) {
					size_t stride = static_cast<size_t>(ctx->convertResult(args[2], NumericConstant::Signed).value.intVal);
					Vector* xVec = static_cast<Vector*>(args[3].value.objectVal);
					std::vector<double> xVals;
					if (!xVec->toPrimitiveArray<double, NumericConstant::Floating>(xVals)) {
						return Result{};
					}
					return Result::make(Math::trapezoidStrided(yVals, start, stride, xVals));
				}
				else if (args[2].isPrimitive() && args[3].isPrimitive()) {
					size_t count = static_cast<size_t>(ctx->convertResult(args[2], NumericConstant::Signed).value.intVal);
					size_t stride = static_cast<size_t>(ctx->convertResult(args[3], NumericConstant::Signed).value.intVal);
					return Result::make(Math::trapezoidStrided(yVals, start, count, stride));
				}
				return Result{};
			}

			// Overload 4: trapezoid(y, start, count, stride, dx)
			if (args.size() == 5) {
				if (!args[1].isPrimitive() || !args[2].isPrimitive() || !args[3].isPrimitive() || !args[4].isPrimitive()) {
					return Result{};
				}
				
				size_t start = static_cast<size_t>(ctx->convertResult(args[1], NumericConstant::Signed).value.intVal);
				size_t count = static_cast<size_t>(ctx->convertResult(args[2], NumericConstant::Signed).value.intVal);
				size_t stride = static_cast<size_t>(ctx->convertResult(args[3], NumericConstant::Signed).value.intVal);
				double dx = ctx->convertResult(args[4], NumericConstant::Floating).value.doubleVal;
				
				return Result::make(Math::trapezoidStrided(yVals, start, count, stride, dx));
			}

			return Result{};
		}

		/**
		 * Bridge for Math::cumulativeTrapezoid1D.
		 * Dynamically identifies and routes to the correct cumulative trapezoid integration overload.
		 * Returns a new Vector containing the cumulative integrals.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the new integrated Vector.
		 **/
		static Result		cumulativeTrapezoidBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || args.size() > 3) { 
				return Result{}; 
			}

			// The first argument must always be the Y array.
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector)) {
				return Result{};
			}

			Vector* yVec = static_cast<Vector*>(args[0].value.objectVal);
			std::vector<double> yVals;
			if (!yVec->toPrimitiveArray<double, NumericConstant::Floating>(yVals)) {
				return Result{};
			}

			std::vector<double> outVals;

			// Overload 1: cumulative_trapezoid(y) -> defaults to dx = 1.0
			if (args.size() == 1) {
				outVals = Math::cumulativeTrapezoid1D(yVals);
			}
			// Overload 2 & 3: cumulative_trapezoid(y, dx) OR cumulative_trapezoid(y, xArray)
			else if (args.size() == 2) {
				if (args[1].type == NumericConstant::Object && args[1].value.objectVal && (args[1].value.objectVal->type() & BuiltInType_Vector)) {
					Vector* xVec = static_cast<Vector*>(args[1].value.objectVal);
					std::vector<double> xVals;
					if (!xVec->toPrimitiveArray<double, NumericConstant::Floating>(xVals)) {
						return Result{};
					}
					outVals = Math::cumulativeTrapezoid1D(yVals, xVals);
				}
				else if (args[1].isPrimitive()) {
					double dx = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
					outVals = Math::cumulativeTrapezoid1D(yVals, dx);
				} 
				else {
					return Result{};
				}
			}
			// Overload 4 & 5: cumulative_trapezoid(y, dx, initial) OR cumulative_trapezoid(y, xArray, initial)
			else if (args.size() == 3) {
				if (!args[2].isPrimitive()) {
					return Result{};
				}
				
				double initial = ctx->convertResult(args[2], NumericConstant::Floating).value.doubleVal;

				if (args[1].type == NumericConstant::Object && args[1].value.objectVal && (args[1].value.objectVal->type() & BuiltInType_Vector)) {
					Vector* xVec = static_cast<Vector*>(args[1].value.objectVal);
					std::vector<double> xVals;
					if (!xVec->toPrimitiveArray<double, NumericConstant::Floating>(xVals)) {
						return Result{};
					}
					outVals = Math::cumulativeTrapezoid1D(yVals, xVals, initial);
				}
				else if (args[1].isPrimitive()) {
					double dx = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
					outVals = Math::cumulativeTrapezoid1D(yVals, dx, initial);
				} 
				else {
					return Result{};
				}
			}

			// Allocate the resulting script Vector and convert the std::vector back into it.
			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) {
				return Result{};
			}
			
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for Math::romb1D and Math::rombStrided.
		 * Dynamically identifies and routes to the correct Romberg integration overload.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the integrated scalar value.
		 **/
		static Result		rombBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || (args.size() != 1 && args.size() != 2 && args.size() != 4 && args.size() != 5)) { 
				return Result{}; 
			}

			// The first argument must always be the Y array.
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector)) {
				return Result{};
			}

			Vector* yVec = static_cast<Vector*>(args[0].value.objectVal);
			std::vector<double> yVals;
			if (!yVec->toPrimitiveArray<double, NumericConstant::Floating>(yVals)) {
				return Result{};
			}

			// Overload 1: romb(y) -> defaults to dx = 1.0
			if (args.size() == 1) {
				return Result::make(Math::romb1D(yVals));
			}

			// Overload 2: romb(y, dx)
			if (args.size() == 2) {
				if (!args[1].isPrimitive()) {
					return Result{};
				}
				double dx = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
				return Result::make(Math::romb1D(yVals, dx));
			}

			// Overload 3: romb(y, start, count, stride)
			if (args.size() == 4) {
				if (!args[1].isPrimitive() || !args[2].isPrimitive() || !args[3].isPrimitive()) {
					return Result{};
				}
				size_t start = static_cast<size_t>(ctx->convertResult(args[1], NumericConstant::Signed).value.intVal);
				size_t count = static_cast<size_t>(ctx->convertResult(args[2], NumericConstant::Signed).value.intVal);
				size_t stride = static_cast<size_t>(ctx->convertResult(args[3], NumericConstant::Signed).value.intVal);
				
				return Result::make(Math::rombStrided(yVals, start, count, stride));
			}

			// Overload 4: romb(y, start, count, stride, dx)
			if (args.size() == 5) {
				if (!args[1].isPrimitive() || !args[2].isPrimitive() || !args[3].isPrimitive() || !args[4].isPrimitive()) {
					return Result{};
				}
				size_t start = static_cast<size_t>(ctx->convertResult(args[1], NumericConstant::Signed).value.intVal);
				size_t count = static_cast<size_t>(ctx->convertResult(args[2], NumericConstant::Signed).value.intVal);
				size_t stride = static_cast<size_t>(ctx->convertResult(args[3], NumericConstant::Signed).value.intVal);
				double dx = ctx->convertResult(args[4], NumericConstant::Floating).value.doubleVal;
				
				return Result::make(Math::rombStrided(yVals, start, count, stride, dx));
			}

			return Result{};
		}


		// =======================================================================================================
		// NUMPY BRIDGES
		// =======================================================================================================
		/**
		 * Bridge for Math::linspace.
		 * Dynamically identifies and routes to the correct linspace overload, handling default arguments.
		 * Returns a new Vector containing the generated sequence.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the new generated Vector.
		 **/
		static Result		linspaceBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 2 || args.size() > 4) { 
				return Result{}; 
			}

			for (const auto& arg : args) {
				if (!arg.isPrimitive()) { return Result{}; }
			}

			double start = ctx->convertResult(args[0], NumericConstant::Floating).value.doubleVal;
			double stop = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
			
			size_t num = 50;
			if (args.size() >= 3) {
				num = static_cast<size_t>(ctx->convertResult(args[2], NumericConstant::Signed).value.intVal);
			}

			bool endpoint = true;
			if (args.size() == 4) {
				endpoint = ctx->convertResult(args[3], NumericConstant::Signed).value.intVal != 0;
			}

			// Generate the sequence (we leave the step pointer out as it is unnecessary for the script return).
			std::vector<double> outVals = Math::linspace<double>(start, stop, num, endpoint, nullptr);

			// Allocate the resulting script Vector and convert the std::vector back into it.
			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec || !resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for Math::arange.
		 * Dynamically identifies and routes to the correct arange overload based on argument count.
		 * Returns a new Vector containing the generated sequence.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the new generated Vector.
		 **/
		static Result		arangeBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || args.size() > 3) { 
				return Result{}; 
			}

			for (const auto& arg : args) {
				if (!arg.isPrimitive()) { return Result{}; }
			}

			std::vector<double> outVals;

			// Overload 1: arange(stop)
			if (args.size() == 1) {
				double stop = ctx->convertResult(args[0], NumericConstant::Floating).value.doubleVal;
				outVals = Math::arange<double>(stop);
			}
			// Overload 2: arange(start, stop)
			else if (args.size() == 2) {
				double start = ctx->convertResult(args[0], NumericConstant::Floating).value.doubleVal;
				double stop = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
				outVals = Math::arange<double, double, double, double>(start, stop, 1.0);
			}
			// Overload 3: arange(start, stop, step)
			else if (args.size() == 3) {
				double start = ctx->convertResult(args[0], NumericConstant::Floating).value.doubleVal;
				double stop = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
				double step = ctx->convertResult(args[2], NumericConstant::Floating).value.doubleVal;
				
				// Prevent C++ std::invalid_argument throw and handle it gracefully for the script context.
				if (step == 0.0) {
					return Result{};
				}
				outVals = Math::arange<double, double, double, double>(start, stop, step);
			}

			// Allocate the resulting script Vector and convert the std::vector back into it.
			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec || !resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for Math::logspace.
		 * Dynamically identifies and routes to the correct logspace overload, handling default arguments.
		 * Returns a new Vector containing the generated log-scaled sequence.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the new generated Vector.
		 **/
		static Result		logspaceBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 2 || args.size() > 5) { 
				return Result{}; 
			}

			for (const auto& arg : args) {
				if (!arg.isPrimitive()) { return Result{}; }
			}

			double start = ctx->convertResult(args[0], NumericConstant::Floating).value.doubleVal;
			double stop = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
			
			size_t num = 50;
			if (args.size() >= 3) {
				num = static_cast<size_t>(ctx->convertResult(args[2], NumericConstant::Signed).value.intVal);
			}

			bool endpoint = true;
			if (args.size() >= 4) {
				endpoint = ctx->convertResult(args[3], NumericConstant::Signed).value.intVal != 0;
			}

			double base = 10.0;
			if (args.size() == 5) {
				base = ctx->convertResult(args[4], NumericConstant::Floating).value.doubleVal;
			}

			// Generate the log-scaled sequence.
			std::vector<double> outVals = Math::logspace<double, double, double>(start, stop, num, endpoint, base);

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec || !resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for Math::geomspace.
		 * Dynamically identifies and routes to the correct geomspace overload, handling default arguments.
		 * Returns a new Vector containing the generated geometric progression.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the new generated Vector.
		 **/
		static Result		geomspaceBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() < 2 || args.size() > 4) { 
				return Result{}; 
			}

			for (const auto& arg : args) {
				if (!arg.isPrimitive()) { return Result{}; }
			}

			double start = ctx->convertResult(args[0], NumericConstant::Floating).value.doubleVal;
			double stop = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
			
			size_t num = 50;
			if (args.size() >= 3) {
				num = static_cast<size_t>(ctx->convertResult(args[2], NumericConstant::Signed).value.intVal);
			}

			bool endpoint = true;
			if (args.size() == 4) {
				endpoint = ctx->convertResult(args[3], NumericConstant::Signed).value.intVal != 0;
			}

			// Generate the geometric progression sequence.
			std::vector<double> outVals = Math::geomspace<double>(start, stop, num, endpoint);

			// Allocate the resulting script Vector and convert the std::vector back into it.
			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) {
				return Result{};
			}
			
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

#define VE_MATH_REDUCTION_BRIDGE(FuncName, MathFunc)																														\
	static Result		FuncName##Bridge(ExecutionContext* ctx, const std::vector<Result>& args) {																			\
		if (args.size() != 1 || args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector)) {			\
			return Result{};																												\
		}																																									\
		Vector* v = static_cast<Vector*>(args[0].value.objectVal);																											\
		std::vector<double> vals;																																			\
		if (!v->toPrimitiveArray<double, NumericConstant::Floating>(vals)) {																								\
			return Result{};																												\
		}																																									\
		return Result::make(MathFunc<double>(vals));																														\
	}

#define VE_MATH_INDEX_REDUCTION_BRIDGE(FuncName, MathFunc)																													\
	static Result		FuncName##Bridge(ExecutionContext* ctx, const std::vector<Result>& args) {																			\
		if (args.size() != 1 || args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector)) {			\
			return Result{};																												\
		}																																									\
		Vector* v = static_cast<Vector*>(args[0].value.objectVal);																											\
		std::vector<double> vals;																																			\
		if (!v->toPrimitiveArray<double, NumericConstant::Floating>(vals)) {																								\
			return Result{};																												\
		}																																									\
		return Result::make(static_cast<uint64_t>(MathFunc<double>(vals)));																									\
	}

		VE_MATH_REDUCTION_BRIDGE(sum, Math::sum)
		VE_MATH_REDUCTION_BRIDGE(prod, Math::prod)
		VE_MATH_REDUCTION_BRIDGE(mean, Math::mean)
		VE_MATH_REDUCTION_BRIDGE(median, Math::median)
		VE_MATH_REDUCTION_BRIDGE(std, Math::std)
		VE_MATH_REDUCTION_BRIDGE(var, Math::var)
		VE_MATH_REDUCTION_BRIDGE(ptp, Math::ptp)

		VE_MATH_INDEX_REDUCTION_BRIDGE(argMin, Math::argMin)
		VE_MATH_INDEX_REDUCTION_BRIDGE(argMax, Math::argMax)

#undef VE_MATH_REDUCTION_BRIDGE
#undef VE_MATH_INDEX_REDUCTION_BRIDGE

		/**
		 * Bridge for Math::percentile.
		 * Dynamically extracts the input vector and the requested percentile scalar, routing them to the C++ backend.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (Vector v, Double q).
		 * \return			Returns a Result containing the interpolated q-th percentile value as a primitive. Returns an Invalid result if argument extraction fails.
		 **/
		static Result		percentileBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector) || !args[1].isPrimitive()) { 
				return Result{}; 
			}
			
			Vector* v = static_cast<Vector*>(args[0].value.objectVal);
			std::vector<double> vals;
			if (!v->toPrimitiveArray<double, NumericConstant::Floating>(vals)) { 
				return Result{}; 
			}
			
			double q = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
			return Result::make(Math::percentile<double>(vals, q));
		}

		
		// =======================================================================================================
		// ARRAY CREATION BRIDGES
		// =======================================================================================================
		/**
		 * Bridge for Math::ones.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the new Vector filled with ones.
		 **/
		static Result		onesBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 1 || !args[0].isPrimitive()) { 
				return Result{}; 
			}

			size_t count = static_cast<size_t>(ctx->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			std::vector<double> outVals = Math::ones<double>(count);

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) {
				return Result{};
			}
			
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for Math::onesLike.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the new Vector filled with ones matching the reference.
		 **/
		static Result		onesLikeBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 1 || args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector)) {
				return Result{};
			}

			Vector* refVec = static_cast<Vector*>(args[0].value.objectVal);

			std::vector<double> outVals = Math::ones<double>(refVec->arrayLength());

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) {
				return Result{};
			}
			
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for Math::zeros.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the new Vector filled with zeros.
		 **/
		static Result		zerosBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 1 || !args[0].isPrimitive()) { 
				return Result{}; 
			}

			size_t count = static_cast<size_t>(ctx->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			std::vector<double> outVals = Math::zeros<double>(count);

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) {
				return Result{};
			}
			
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for Math::zerosLike.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the new Vector filled with zeros matching the reference.
		 **/
		static Result		zerosLikeBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 1 || args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector)) {
				return Result{};
			}

			Vector* refVec = static_cast<Vector*>(args[0].value.objectVal);

			std::vector<double> outVals = Math::zeros<double>(refVec->arrayLength());

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) {
				return Result{};
			}
			
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for Math::full.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the new Vector filled with the constant value.
		 **/
		static Result		fullBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || !args[0].isPrimitive() || !args[1].isPrimitive()) { 
				return Result{}; 
			}

			size_t count = static_cast<size_t>(ctx->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			double fillValue = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
			
			std::vector<double> outVals = Math::full<double>(count, fillValue);

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) {
				return Result{};
			}
			
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for Math::fullLike.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments.
		 * \return			Returns a Result containing the new Vector filled with the constant value matching the reference array.
		 **/
		static Result		fullLikeBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector) || !args[1].isPrimitive()) {
				return Result{};
			}

			Vector* refVec = static_cast<Vector*>(args[0].value.objectVal);
			double fillValue = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
			
			std::vector<double> outVals = Math::full<double>(refVec->arrayLength(), fillValue);

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) {
				return Result{};
			}
			
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}


		// =======================================================================================================
		// CUMULATIVE & DIFFERENCES BRIDGES
		// =======================================================================================================
#define VE_MATH_VECTOR_RET_BRIDGE(FuncName, MathFunc)																														\
	static Result		FuncName##Bridge(ExecutionContext* ctx, const std::vector<Result>& args) {																			\
		if (args.size() != 1 || args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector)) {			\
			return Result{};																												\
		}																																									\
		Vector* v = static_cast<Vector*>(args[0].value.objectVal);																											\
		std::vector<double> vals;																																			\
		if (!v->toPrimitiveArray<double, NumericConstant::Floating>(vals)) {																								\
			return Result{};																												\
		}																																									\
		std::vector<double> outVals = MathFunc<double>(vals);																												\
		Vector* resVec = ctx->allocateObject<Vector>();																														\
		if (!resVec) { return Result{}; }																									\
		if (!resVec->fromPrimitiveArray(outVals)) {																															\
			ctx->deallocateObject(resVec);																																	\
			return Result{};																												\
		}																																									\
		return resVec->createResult();																																		\
	}

		VE_MATH_VECTOR_RET_BRIDGE(cumSum, Math::cumSum)
		VE_MATH_VECTOR_RET_BRIDGE(cumProd, Math::cumProd)

#undef VE_MATH_VECTOR_RET_BRIDGE

		/**
		 * Bridge for Math::diff1D.
		 * Dynamically identifies and routes to the correct discrete difference overload based on argument count, 
		 * defaulting to an order of 1 if the 'n' parameter is omitted.
		 * Returns a new Vector containing the discrete differences.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (Vector x, [Integer n]).
		 * \return			Returns a Result containing the new generated Vector. Returns an Invalid result if extraction or allocation fails.
		 **/
		static Result		diffBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || args.size() > 2) { return Result{}; }

			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector)) {
				return Result{};
			}

			Vector* xVec = static_cast<Vector*>(args[0].value.objectVal);
			std::vector<double> xVals;
			if (!xVec->toPrimitiveArray<double, NumericConstant::Floating>(xVals)) { return Result{}; }

			size_t n = 1;
			if (args.size() == 2) {
				if (!args[1].isPrimitive()) { return Result{}; }
				n = static_cast<size_t>(ctx->convertResult(args[1], NumericConstant::Signed).value.intVal);
			}

			std::vector<double> outVals = Math::diff1D<double>(xVals, n);

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }
			
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for Math::ediff1d.
		 * Dynamically parses 1 to 3 arguments to extract the primary array and the optional prepend (to_begin) and append (to_end) arrays.
		 * Returns a new Vector containing the prepended values, differences, and appended values.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (Vector ary, [Vector to_begin], [Vector to_end]).
		 * \return			Returns a Result containing the new generated Vector. Returns an Invalid result if extraction or allocation fails.
		 **/
		static Result		ediff1dBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.empty() || args.size() > 3) { return Result{}; }

			// Helper lambda to safely extract std::vector<double> from a Result
			auto extractVector = [](const Result& res, std::vector<double>& out) -> bool {
				if (res.type != NumericConstant::Object || !res.value.objectVal || !(res.value.objectVal->type() & BuiltInType_Vector)) {
					return false;
				}
				Vector* vec = static_cast<Vector*>(res.value.objectVal);
				return vec->toPrimitiveArray<double, NumericConstant::Floating>(out);
			};

			std::vector<double> ary, toBegin, toEnd;
			
			if (!extractVector(args[0], ary)) { return Result{}; }
			
			if (args.size() >= 2) {
				if (!extractVector(args[1], toBegin)) { return Result{}; }
			}

			if (args.size() == 3) {
				if (!extractVector(args[2], toEnd)) { return Result{}; }
			}

			std::vector<double> outVals = Math::ediff1d<double>(ary, toBegin, toEnd);

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }
			
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}


		// =======================================================================================================
		// ARRAY MANIPULATION BRIDGES
		// =======================================================================================================
		/**
		 * Bridge for Math::clip.
		 * Dynamically extracts the input vector and the bounding primitives, routing them to the C++ backend.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (Vector v, Double minVal, Double maxVal).
		 * \return			Returns a Result containing the new generated Vector.
		 **/
		static Result		clipBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 3 || args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector) || !args[1].isPrimitive() || !args[2].isPrimitive()) {
				return Result{};
			}

			Vector* v = static_cast<Vector*>(args[0].value.objectVal);
			std::vector<double> vals;
			if (!v->toPrimitiveArray<double, NumericConstant::Floating>(vals)) { 
				return Result{}; 
			}

			double minVal = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
			double maxVal = ctx->convertResult(args[2], NumericConstant::Floating).value.doubleVal;

			std::vector<double> outVals = Math::clip<double>(vals, minVal, maxVal);

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}
			return resVec->createResult();
		}

		/**
		 * Bridge for Math::roll.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (Vector v, Integer shift).
		 * \return			Returns a Result containing the new generated Vector.
		 **/
		static Result		rollBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector) || !args[1].isPrimitive()) {
				return Result{};
			}

			Vector* v = static_cast<Vector*>(args[0].value.objectVal);
			std::vector<double> vals;
			if (!v->toPrimitiveArray<double, NumericConstant::Floating>(vals)) { 
				return Result{}; 
			}

			int64_t shift = ctx->convertResult(args[1], NumericConstant::Signed).value.intVal;

			std::vector<double> outVals = Math::roll<double>(vals, shift);

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}
			return resVec->createResult();
		}

		/**
		 * Bridge for Math::concatenate.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (Vector v1, Vector v2).
		 * \return			Returns a Result containing the new generated Vector.
		 **/
		static Result		concatenateBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }

			auto extractVector = [](const Result& res, std::vector<double>& out) -> bool {
				if (res.type != NumericConstant::Object || !res.value.objectVal || !(res.value.objectVal->type() & BuiltInType_Vector)) {
					return false;
				}
				Vector* vec = static_cast<Vector*>(res.value.objectVal);
				return vec->toPrimitiveArray<double, NumericConstant::Floating>(out);
			};

			std::vector<double> v1, v2;
			if (!extractVector(args[0], v1) || !extractVector(args[1], v2)) {
				return Result{};
			}

			std::vector<double> outVals = Math::concatenate<double>(v1, v2);

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}
			return resVec->createResult();
		}

		/**
		 * Bridge for Math::repeat.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (Vector v, Integer repeats).
		 * \return			Returns a Result containing the new generated Vector.
		 **/
		static Result		repeatBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector) || !args[1].isPrimitive()) {
				return Result{};
			}

			Vector* v = static_cast<Vector*>(args[0].value.objectVal);
			std::vector<double> vals;
			if (!v->toPrimitiveArray<double, NumericConstant::Floating>(vals)) { 
				return Result{}; 
			}

			size_t repeats = static_cast<size_t>(ctx->convertResult(args[1], NumericConstant::Signed).value.intVal);

			std::vector<double> outVals = Math::repeat<double>(vals, repeats);

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}
			return resVec->createResult();
		}

		/**
		 * Bridge for Math::tile.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (Vector v, Integer reps).
		 * \return			Returns a Result containing the new generated Vector.
		 **/
		static Result		tileBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector) || !args[1].isPrimitive()) {
				return Result{};
			}

			Vector* v = static_cast<Vector*>(args[0].value.objectVal);
			std::vector<double> vals;
			if (!v->toPrimitiveArray<double, NumericConstant::Floating>(vals)) { 
				return Result{}; 
			}

			size_t reps = static_cast<size_t>(ctx->convertResult(args[1], NumericConstant::Signed).value.intVal);

			std::vector<double> outVals = Math::tile<double>(vals, reps);

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}
			return resVec->createResult();
		}

		/**
		 * Bridge for Math::pad.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (Vector v, Integer padLeft, Integer padRight, Double constantValue).
		 * \return			Returns a Result containing the new generated Vector.
		 **/
		static Result		padBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 4 || args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Vector) || !args[1].isPrimitive() || !args[2].isPrimitive() || !args[3].isPrimitive()) {
				return Result{};
			}

			Vector* v = static_cast<Vector*>(args[0].value.objectVal);
			std::vector<double> vals;
			if (!v->toPrimitiveArray<double, NumericConstant::Floating>(vals)) { 
				return Result{}; 
			}

			size_t padLeft = static_cast<size_t>(ctx->convertResult(args[1], NumericConstant::Signed).value.intVal);
			size_t padRight = static_cast<size_t>(ctx->convertResult(args[2], NumericConstant::Signed).value.intVal);
			double constantValue = ctx->convertResult(args[3], NumericConstant::Floating).value.doubleVal;

			std::vector<double> outVals = Math::pad<double>(vals, padLeft, padRight, constantValue);

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}
			return resVec->createResult();
		}


		// =======================================================================================================
		// SIGNAL PROCESSING & MATH BRIDGES
		// =======================================================================================================
		/**
		 * Bridge for Math::convolve.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (Vector v1, Vector v2).
		 * \return			Returns a Result containing the new generated Vector.
		 **/
		static Result		convolveBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }

			auto extractVector = [](const Result& res, std::vector<double>& out) -> bool {
				if (res.type != NumericConstant::Object || !res.value.objectVal || !(res.value.objectVal->type() & BuiltInType_Vector)) {
					return false;
				}
				Vector* vec = static_cast<Vector*>(res.value.objectVal);
				return vec->toPrimitiveArray<double, NumericConstant::Floating>(out);
			};

			std::vector<double> v1, v2;
			if (!extractVector(args[0], v1) || !extractVector(args[1], v2)) {
				return Result{};
			}

			std::vector<double> outVals = Math::convolve<double>(v1, v2);

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}
			return resVec->createResult();
		}

		/**
		 * Bridge for Math::correlate.
		 * Evaluates the cross-correlation of two 1D sequences. Safely catches invalid dimension exceptions.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (Vector a, Vector v).
		 * \return			Returns a Result containing the new generated Vector, or Invalid if a.size() < v.size().
		 **/
		static Result		correlateBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }

			auto extractVector = [](const Result& res, std::vector<double>& out) -> bool {
				if (res.type != NumericConstant::Object || !res.value.objectVal || !(res.value.objectVal->type() & BuiltInType_Vector)) {
					return false;
				}
				Vector* vec = static_cast<Vector*>(res.value.objectVal);
				return vec->toPrimitiveArray<double, NumericConstant::Floating>(out);
			};

			std::vector<double> a, v;
			if (!extractVector(args[0], a) || !extractVector(args[1], v)) {
				return Result{};
			}

			std::vector<double> outVals;
			try {
				outVals = Math::correlate<double>(a, v);
			}
			catch (const std::exception&) {
				// Prevent script crash if the signal 'a' is shorter than template 'v'.
				return Result{};
			}

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}
			return resVec->createResult();
		}

		/**
		 * Bridge for Math::interp.
		 * Evaluates the 1D linear interpolation. Safely catches invalid dimension/data exceptions.
		 * Must be called within a try/catch block.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (Vector x, Vector xp, Vector fp).
		 * \return			Returns a Result containing the new generated Vector, or Invalid if xp and fp size mismatch.
		 **/
		static Result		interpBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }

			auto extractVector = [](const Result& res, std::vector<double>& out) -> bool {
				if (res.type != NumericConstant::Object || !res.value.objectVal || !(res.value.objectVal->type() & BuiltInType_Vector)) {
					return false;
				}
				Vector* vec = static_cast<Vector*>(res.value.objectVal);
				return vec->toPrimitiveArray<double, NumericConstant::Floating>(out);
			};

			std::vector<double> x, xp, fp;
			if (!extractVector(args[0], x) || !extractVector(args[1], xp) || !extractVector(args[2], fp)) {
				return Result{};
			}

			std::vector<double> outVals;
			try {
				outVals = Math::interp<double>(x, xp, fp);
			}
			catch (const std::exception&) {
				// Prevent script crash if xp.size() != fp.size()
				return Result{};
			}

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }
			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}
			return resVec->createResult();
		}


		// =======================================================================================================
		// WINDOW CREATION
		// =======================================================================================================
		/**
		 * Macro to generate a bridge function for a standard Math windowing function.
		 * Automatically extracts the sample count, calls the corresponding Math::[name]Window function,
		 * and packages the std::vector<double> output into a Vector object Result.
		 *
		 * \param name		The base name of the window function (e.g., bartlett).
		 **/
#define VE_MAKE_WINDOW_BRIDGE(name)																							\
	static Result		name##Bridge(ExecutionContext* ctx, const std::vector<Result>& args) {								\
		if (args.size() != 1 || !args[0].isPrimitive()) { return Result{}; }												\
		size_t count = static_cast<size_t>(ctx->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);			\
		std::vector<double> outVals;																						\
		if (!Math::name##Window<double>(count, outVals)) { return Result{}; }												\
		Vector* resVec = ctx->allocateObject<Vector>();																		\
		if (!resVec) { return Result{}; }																					\
		if (!resVec->fromPrimitiveArray(outVals)) {																			\
			ctx->deallocateObject(resVec);																					\
			return Result{};																								\
		}																													\
		return resVec->createResult();																						\
	}
		VE_MAKE_WINDOW_BRIDGE(barthann)
		VE_MAKE_WINDOW_BRIDGE(bartlett)
		VE_MAKE_WINDOW_BRIDGE(blackman)
		VE_MAKE_WINDOW_BRIDGE(blackmanHarris)
		VE_MAKE_WINDOW_BRIDGE(blackmanNuttal)
		VE_MAKE_WINDOW_BRIDGE(bohman)
		VE_MAKE_WINDOW_BRIDGE(boxcar)
		VE_MAKE_WINDOW_BRIDGE(cosine)
		VE_MAKE_WINDOW_BRIDGE(flatTop)
		VE_MAKE_WINDOW_BRIDGE(hann)
		VE_MAKE_WINDOW_BRIDGE(hamming)
		VE_MAKE_WINDOW_BRIDGE(lanczos)
		VE_MAKE_WINDOW_BRIDGE(nuttall)
		VE_MAKE_WINDOW_BRIDGE(parzen)
		VE_MAKE_WINDOW_BRIDGE(triang)

#undef VE_MAKE_WINDOW_BRIDGE

		/**
		 * Bridge for chebwin().
		 * Returns a Dolph-Chebyshev window.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (n, at).
		 * \return			Returns a Vector Result containing the window values.
		 **/
		static Result		chebwinBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || !args[0].isPrimitive() || !args[1].isPrimitive()) { return Result{}; }

			size_t m = static_cast<size_t>(ctx->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			double at = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;

			std::vector<double> outVals;
			if (!Math::chebwinWindow<double>(m, at, outVals)) { return Result{}; }

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }

			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for dpss().
		 * Returns a Discrete Prolate Spheroidal Sequences (DPSS) window.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (n, nw, kMax).
		 * \return			Returns a Vector Result of Vector Results containing the window values.
		 **/
		static Result		dpssBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 3 || !args[0].isPrimitive() || !args[1].isPrimitive() || !args[2].isPrimitive()) { return Result{}; }

			size_t m = static_cast<size_t>(ctx->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			double nw = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
			size_t kMax = static_cast<size_t>(ctx->convertResult(args[2], NumericConstant::Unsigned).value.uintVal);

			std::vector<std::vector<double>> vvRet;
			if (!Math::dpssWindows<double>(m, nw, kMax, vvRet)) { return Result{}; }

			Vector* outerVec = ctx->allocateObject<Vector>();
			if (!outerVec) { return Result{}; }

			outerVec->resize(vvRet.size());
			for (size_t i = 0; i < vvRet.size(); ++i) {
				Vector* innerVec = ctx->allocateObject<Vector>();
				if (innerVec && innerVec->fromPrimitiveArray(vvRet[i])) {
					outerVec->directAccess(i) = innerVec->createResult();
					innerVec->incRef();
				}
				else {
					if (innerVec) {
						ctx->deallocateObject(innerVec);
					}
				}
			}

			return outerVec->createResult();
		}

		/**
		 * Bridge for exponential().
		 * Returns an Exponential window.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (n, tau, center).
		 * \return			Returns a Vector Result containing the window values.
		 **/
		static Result		exponentialBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 3 || !args[0].isPrimitive() || !args[1].isPrimitive() || !args[2].isPrimitive()) { return Result{}; }

			size_t n = static_cast<size_t>(ctx->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			double tau = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
			double center = ctx->convertResult(args[2], NumericConstant::Floating).value.doubleVal;

			std::vector<double> outVals;
			if (!Math::exponentialWindow<double>(n, tau, center, outVals)) { return Result{}; }

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }

			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for gaussian().
		 * Returns a Gaussian window.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (n, sigma).
		 * \return			Returns a Vector Result containing the window values.
		 **/
		static Result		gaussianBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || !args[0].isPrimitive() || !args[1].isPrimitive()) {
				return Result{};
			}

			size_t n = static_cast<size_t>(ctx->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			double sigma = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;

			std::vector<double> outVals;
			if (!Math::gaussianWindow<double>(n, sigma, outVals)) {
				return Result{};
			}

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) {
				return Result{};
			}

			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for general_cosine().
		 * Returns a Generalized Cosine window.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (n, aVals).
		 * \return			Returns a Vector Result containing the window values.
		 **/
		static Result		generalCosineBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || !args[0].isPrimitive() || args[1].type != NumericConstant::Object || args[1].value.objectVal == nullptr || !(args[1].value.objectVal->type() & BuiltInType_Vector)) { return Result{}; }

			size_t n = static_cast<size_t>(ctx->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			Vector* vecObj = static_cast<Vector*>(args[1].value.objectVal);
			size_t len = vecObj->arrayLength();
			std::vector<double> aVals;
			aVals.reserve(len);

			for (size_t i = 0; i < len; ++i) {
				aVals.push_back(ctx->convertResult(vecObj->arrayAccess(static_cast<int64_t>(i)), NumericConstant::Floating).value.doubleVal);
			}

			std::vector<double> outVals;
			if (!Math::generalCosineWindow<double>(n, aVals, outVals)) { return Result{}; }

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }

			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for general_gaussian().
		 * Returns a Generalized Gaussian window.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (n, p, sigma).
		 * \return			Returns a Vector Result containing the window values.
		 **/
		static Result		generalGaussianBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 3 || !args[0].isPrimitive() || !args[1].isPrimitive() || !args[2].isPrimitive()) { return Result{}; }

			size_t n = static_cast<size_t>(ctx->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			double p = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
			double sigma = ctx->convertResult(args[2], NumericConstant::Floating).value.doubleVal;

			std::vector<double> outVals;
			if (!Math::generalGaussianWindow<double>(n, p, sigma, outVals)) { return Result{}; }

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }

			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for general_hamming().
		 * Returns a Generalized Hamming window.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (n, alpha).
		 * \return			Returns a Vector Result containing the window values.
		 **/
		static Result		generalHammingBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || !args[0].isPrimitive() || !args[1].isPrimitive()) { return Result{}; }

			size_t n = static_cast<size_t>(ctx->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			double alpha = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;

			std::vector<double> outVals;
			if (!Math::generalHammingWindow<double>(n, alpha, outVals)) { return Result{}; }

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }

			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for kaiser().
		 * Returns a Kaiser window.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (n, beta).
		 * \return			Returns a Vector Result containing the window values.
		 **/
		static Result		kaiserBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || !args[0].isPrimitive() || !args[1].isPrimitive()) { return Result{}; }

			size_t n = static_cast<size_t>(ctx->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			double beta = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;

			std::vector<double> outVals;
			if (!Math::kaiserWindow<double>(n, beta, outVals)) { return Result{}; }

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }

			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for kaiser_bessel_derived().
		 * Returns a Kaiser-Bessel Derived (KBD) window.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (n, beta).
		 * \return			Returns a Vector Result containing the window values.
		 **/
		static Result		kaiserBesselDerivedBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || !args[0].isPrimitive() || !args[1].isPrimitive()) { return Result{}; }

			size_t n = static_cast<size_t>(ctx->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			double beta = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;

			std::vector<double> outVals;
			if (!Math::kaiserBesselDerivedWindow<double>(n, beta, outVals)) { return Result{}; }

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }

			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for taylor().
		 * Returns a Taylor window.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (n, nBar, sll, norm).
		 * \return			Returns a Vector Result containing the window values.
		 **/
		static Result		taylorBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 4 || !args[0].isPrimitive() || !args[1].isPrimitive() || !args[2].isPrimitive()) { return Result{}; }

			size_t n = static_cast<size_t>(ctx->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			int32_t nBar = static_cast<int32_t>(ctx->convertResult(args[1], NumericConstant::Signed).value.intVal);
			double sll = ctx->convertResult(args[2], NumericConstant::Floating).value.doubleVal;

			bool norm = false;
			if (args[3].type == NumericConstant::Signed) {
				norm = (args[3].value.intVal != 0);
			}
			else if (args[3].type == NumericConstant::Unsigned) {
				norm = (args[3].value.uintVal != 0);
			}
			else if (args[3].type == NumericConstant::Floating) {
				norm = (args[3].value.doubleVal != 0.0);
			}
			else if (args[3].type == NumericConstant::Object && args[3].value.objectVal != nullptr) {
				return Result{};
			}

			std::vector<double> outVals;
			if (!Math::taylorWindow<double>(n, nBar, sll, norm, outVals)) { return Result{}; }

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }

			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for tukey().
		 * Returns a Tukey window.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (n, alpha).
		 * \return			Returns a Vector Result containing the window values.
		 **/
		static Result		tukeyBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 2 || !args[0].isPrimitive() || !args[1].isPrimitive()) { return Result{}; }

			size_t n = static_cast<size_t>(ctx->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			double alpha = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;

			std::vector<double> outVals;
			if (!Math::tukeyWindow<double>(n, alpha, outVals)) {
				return Result{};
			}

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) {
				return Result{};
			}

			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for sinc_filter_lpf().
		 * Returns the coefficients for a windowed sinc low-pass filter.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (hz, fc, m).
		 * \return			Returns a Vector Result containing the filter coefficients.
		 **/
		static Result		sincFilterLpfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 3 || !args[0].isPrimitive() || !args[1].isPrimitive() || !args[2].isPrimitive()) { return Result{}; }

			double hz = ctx->convertResult(args[0], NumericConstant::Floating).value.doubleVal;
			double fc = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
			size_t m = static_cast<size_t>(ctx->convertResult(args[2], NumericConstant::Unsigned).value.uintVal);

			std::vector<double> outVals;
			try {
				outVals = Math::sincFilterLpf<std::vector<double>>(hz, fc, m, nullptr);
			} catch (...) {
				return Result{};
			}

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }

			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for sinc_filter_hpf().
		 * Returns the coefficients for a windowed sinc high-pass filter.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (hz, fc, m).
		 * \return			Returns a Vector Result containing the filter coefficients.
		 **/
		static Result		sincFilterHpfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 3 || !args[0].isPrimitive() || !args[1].isPrimitive() || !args[2].isPrimitive()) { return Result{}; }

			double hz = ctx->convertResult(args[0], NumericConstant::Floating).value.doubleVal;
			double fc = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
			size_t m = static_cast<size_t>(ctx->convertResult(args[2], NumericConstant::Unsigned).value.uintVal);

			std::vector<double> outVals;
			try {
				outVals = Math::sincFilterHpf<std::vector<double>>(hz, fc, m, nullptr);
			} catch (...) { return Result{}; }

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }

			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}

		/**
		 * Bridge for sinc_filter_bpf().
		 * Returns the coefficients for a windowed sinc band-pass filter.
		 *
		 * \param ctx		The runtime execution context.
		 * \param args		A vector containing the evaluated arguments (hz, f1, f2, m).
		 * \return			Returns a Vector Result containing the filter coefficients.
		 **/
		static Result		sincFilterBpfBridge(ExecutionContext* ctx, const std::vector<Result>& args) {
			if (args.size() != 4 || !args[0].isPrimitive() || !args[1].isPrimitive() || !args[2].isPrimitive() || !args[3].isPrimitive()) { return Result{}; }

			double hz = ctx->convertResult(args[0], NumericConstant::Floating).value.doubleVal;
			double f1 = ctx->convertResult(args[1], NumericConstant::Floating).value.doubleVal;
			double f2 = ctx->convertResult(args[2], NumericConstant::Floating).value.doubleVal;
			size_t m = static_cast<size_t>(ctx->convertResult(args[3], NumericConstant::Unsigned).value.uintVal);

			std::vector<double> outVals;
			try {
				outVals = Math::sincFilterBpf<std::vector<double>>(hz, f1, f2, m, nullptr);
			} catch (...) { return Result{}; }

			Vector* resVec = ctx->allocateObject<Vector>();
			if (!resVec) { return Result{}; }

			if (!resVec->fromPrimitiveArray(outVals)) {
				ctx->deallocateObject(resVec);
				return Result{};
			}

			return resVec->createResult();
		}


		// SIMD Bridges
/**
 * Maps runtime integers to compile-time constants for strict native immediate requirements.
 **/
#define VE_MSA_IMM5_SWITCH(FUNC, RES, A, IMM)												\
	switch (IMM) {																			\
		case 0 : { RES = FUNC(A, 0); break; }												\
		case 1 : { RES = FUNC(A, 1); break; }												\
		case 2 : { RES = FUNC(A, 2); break; }												\
		case 3 : { RES = FUNC(A, 3); break; }												\
		case 4 : { RES = FUNC(A, 4); break; }												\
		case 5 : { RES = FUNC(A, 5); break; }												\
		case 6 : { RES = FUNC(A, 6); break; }												\
		case 7 : { RES = FUNC(A, 7); break; }												\
		case 8 : { RES = FUNC(A, 8); break; }												\
		case 9 : { RES = FUNC(A, 9); break; }												\
		case 10 : { RES = FUNC(A, 10); break; }												\
		case 11 : { RES = FUNC(A, 11); break; }												\
		case 12 : { RES = FUNC(A, 12); break; }												\
		case 13 : { RES = FUNC(A, 13); break; }												\
		case 14 : { RES = FUNC(A, 14); break; }												\
		case 15 : { RES = FUNC(A, 15); break; }												\
		case 16 : { RES = FUNC(A, 16); break; }												\
		case 17 : { RES = FUNC(A, 17); break; }												\
		case 18 : { RES = FUNC(A, 18); break; }												\
		case 19 : { RES = FUNC(A, 19); break; }												\
		case 20 : { RES = FUNC(A, 20); break; }												\
		case 21 : { RES = FUNC(A, 21); break; }												\
		case 22 : { RES = FUNC(A, 22); break; }												\
		case 23 : { RES = FUNC(A, 23); break; }												\
		case 24 : { RES = FUNC(A, 24); break; }												\
		case 25 : { RES = FUNC(A, 25); break; }												\
		case 26 : { RES = FUNC(A, 26); break; }												\
		case 27 : { RES = FUNC(A, 27); break; }												\
		case 28 : { RES = FUNC(A, 28); break; }												\
		case 29 : { RES = FUNC(A, 29); break; }												\
		case 30 : { RES = FUNC(A, 30); break; }												\
		case 31 : { RES = FUNC(A, 31); break; }												\
		default : { return Result{}; }														\
	}


		/**
		 * Bridge for simde_msa_add_a_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddAB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_add_a_b(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_add_a_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddAH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_add_a_h(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_add_a_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddAW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_add_a_w(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_add_a_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddAD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg1->regType != Simd_v2i64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_add_a_d(simdArg0->reg.v2i64, simdArg1->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_adds_s_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddsSB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_adds_s_b(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_adds_s_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddsSH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_adds_s_h(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_adds_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddsSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_adds_s_w(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_adds_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddsSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg1->regType != Simd_v2i64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_adds_s_d(simdArg0->reg.v2i64, simdArg1->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_adds_u_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddsUB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16u8 || simdArg1->regType != Simd_v16u8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16u8;
			outObj->reg.v16u8 = simde_msa_adds_u_b(simdArg0->reg.v16u8, simdArg1->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_adds_u_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddsUH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8u16 || simdArg1->regType != Simd_v8u16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8u16;
			outObj->reg.v8u16 = simde_msa_adds_u_h(simdArg0->reg.v8u16, simdArg1->reg.v8u16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_adds_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddsUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4u32 || simdArg1->regType != Simd_v4u32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4u32;
			outObj->reg.v4u32 = simde_msa_adds_u_w(simdArg0->reg.v4u32, simdArg1->reg.v4u32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_adds_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddsUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2u64 || simdArg1->regType != Simd_v2u64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2u64;
			outObj->reg.v2u64 = simde_msa_adds_u_d(simdArg0->reg.v2u64, simdArg1->reg.v2u64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_adds_a_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddsAB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_adds_a_b(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_adds_a_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddsAH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_adds_a_h(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_adds_a_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddsAW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_adds_a_w(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_adds_a_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddsAD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg1->regType != Simd_v2i64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_adds_a_d(simdArg0->reg.v2i64, simdArg1->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_addv_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddvB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_addv_b(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_addv_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddvH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_addv_h(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_addv_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddvW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_addv_w(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_addv_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddvD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg1->regType != Simd_v2i64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_addv_d(simdArg0->reg.v2i64, simdArg1->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_addvi_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddviB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v16i8) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;
			if (imm < 0 || imm > 31) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }
			outObj->regType = Simd_v16i8;

			VE_MSA_IMM5_SWITCH(simde_msa_addvi_b, outObj->reg.v16i8, simdArg0->reg.v16i8, imm)

			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_addvi_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddviH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v8i16) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;
			if (imm < 0 || imm > 31) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }
			outObj->regType = Simd_v8i16;

			VE_MSA_IMM5_SWITCH(simde_msa_addvi_h, outObj->reg.v8i16, simdArg0->reg.v8i16, imm)

			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_addvi_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddviW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4i32) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;
			if (imm < 0 || imm > 31) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }
			outObj->regType = Simd_v4i32;

			VE_MSA_IMM5_SWITCH(simde_msa_addvi_w, outObj->reg.v4i32, simdArg0->reg.v4i32, imm)

			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_addvi_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAddviD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2i64) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;
			if (imm < 0 || imm > 31) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }
			outObj->regType = Simd_v2i64;

			VE_MSA_IMM5_SWITCH(simde_msa_addvi_d, outObj->reg.v2i64, simdArg0->reg.v2i64, imm)

			return outObj->createResult();
		}

#undef VE_MSA_IMM5_SWITCH

		/**
		 * Bridge for simde_msa_and_v.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAndV(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16u8 || simdArg1->regType != Simd_v16u8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16u8;
			outObj->reg.v16u8 = simde_msa_and_v(simdArg0->reg.v16u8, simdArg1->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_andi_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAndiB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v16u8) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16u8;
			outObj->reg.v16u8 = simde_msa_andi_b(simdArg0->reg.v16u8, static_cast<int>(imm));
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_asub_s_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAsubSB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_asub_s_b(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_asub_s_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAsubSH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_asub_s_h(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_asub_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAsubSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_asub_s_w(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_asub_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAsubSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg1->regType != Simd_v2i64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_asub_s_d(simdArg0->reg.v2i64, simdArg1->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_asub_u_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAsubUB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16u8 || simdArg1->regType != Simd_v16u8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16u8;
			outObj->reg.v16u8 = simde_msa_asub_u_b(simdArg0->reg.v16u8, simdArg1->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_asub_u_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAsubUH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8u16 || simdArg1->regType != Simd_v8u16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8u16;
			outObj->reg.v8u16 = simde_msa_asub_u_h(simdArg0->reg.v8u16, simdArg1->reg.v8u16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_asub_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAsubUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4u32 || simdArg1->regType != Simd_v4u32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4u32;
			outObj->reg.v4u32 = simde_msa_asub_u_w(simdArg0->reg.v4u32, simdArg1->reg.v4u32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_asub_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAsubUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2u64 || simdArg1->regType != Simd_v2u64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2u64;
			outObj->reg.v2u64 = simde_msa_asub_u_d(simdArg0->reg.v2u64, simdArg1->reg.v2u64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ave_s_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAveSB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_ave_s_b(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ave_s_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAveSH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_ave_s_h(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ave_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAveSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_ave_s_w(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ave_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAveSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg1->regType != Simd_v2i64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_ave_s_d(simdArg0->reg.v2i64, simdArg1->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ave_u_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAveUB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16u8 || simdArg1->regType != Simd_v16u8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16u8;
			outObj->reg.v16u8 = simde_msa_ave_u_b(simdArg0->reg.v16u8, simdArg1->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ave_u_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAveUH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8u16 || simdArg1->regType != Simd_v8u16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8u16;
			outObj->reg.v8u16 = simde_msa_ave_u_h(simdArg0->reg.v8u16, simdArg1->reg.v8u16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ave_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAveUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4u32 || simdArg1->regType != Simd_v4u32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4u32;
			outObj->reg.v4u32 = simde_msa_ave_u_w(simdArg0->reg.v4u32, simdArg1->reg.v4u32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ave_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAveUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2u64 || simdArg1->regType != Simd_v2u64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2u64;
			outObj->reg.v2u64 = simde_msa_ave_u_d(simdArg0->reg.v2u64, simdArg1->reg.v2u64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_aver_s_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAverSB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_aver_s_b(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_aver_s_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAverSH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_aver_s_h(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_aver_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAverSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_aver_s_w(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_aver_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAverSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg1->regType != Simd_v2i64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_aver_s_d(simdArg0->reg.v2i64, simdArg1->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_aver_u_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAverUB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16u8 || simdArg1->regType != Simd_v16u8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16u8;
			outObj->reg.v16u8 = simde_msa_aver_u_b(simdArg0->reg.v16u8, simdArg1->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_aver_u_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAverUH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8u16 || simdArg1->regType != Simd_v8u16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8u16;
			outObj->reg.v8u16 = simde_msa_aver_u_h(simdArg0->reg.v8u16, simdArg1->reg.v8u16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_aver_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAverUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4u32 || simdArg1->regType != Simd_v4u32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4u32;
			outObj->reg.v4u32 = simde_msa_aver_u_w(simdArg0->reg.v4u32, simdArg1->reg.v4u32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_aver_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaAverUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2u64 || simdArg1->regType != Simd_v2u64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2u64;
			outObj->reg.v2u64 = simde_msa_aver_u_d(simdArg0->reg.v2u64, simdArg1->reg.v2u64);
			return outObj->createResult();
		}

	/**
	 * Resolves dynamic arguments into compile-time macros to satisfy strict intrinsic constraints.
	 **/
#define VE_MSA_CASE_1(FUNC, RES, A, IMM) case IMM: { RES = FUNC(A, IMM); break; }
#define VE_MSA_CASE_4(FUNC, RES, A, IMM) VE_MSA_CASE_1(FUNC, RES, A, IMM) VE_MSA_CASE_1(FUNC, RES, A, IMM+1) VE_MSA_CASE_1(FUNC, RES, A, IMM+2) VE_MSA_CASE_1(FUNC, RES, A, IMM+3)
#define VE_MSA_CASE_16(FUNC, RES, A, IMM) VE_MSA_CASE_4(FUNC, RES, A, IMM) VE_MSA_CASE_4(FUNC, RES, A, IMM+4) VE_MSA_CASE_4(FUNC, RES, A, IMM+8) VE_MSA_CASE_4(FUNC, RES, A, IMM+12)
#define VE_MSA_CASE_64(FUNC, RES, A, IMM) VE_MSA_CASE_16(FUNC, RES, A, IMM) VE_MSA_CASE_16(FUNC, RES, A, IMM+16) VE_MSA_CASE_16(FUNC, RES, A, IMM+32) VE_MSA_CASE_16(FUNC, RES, A, IMM+48)

#define VE_MSA_CASE_1_3(FUNC, RES, A, B, IMM) case IMM: { RES = FUNC(A, B, IMM); break; }
#define VE_MSA_CASE_4_3(FUNC, RES, A, B, IMM) VE_MSA_CASE_1_3(FUNC, RES, A, B, IMM) VE_MSA_CASE_1_3(FUNC, RES, A, B, IMM+1) VE_MSA_CASE_1_3(FUNC, RES, A, B, IMM+2) VE_MSA_CASE_1_3(FUNC, RES, A, B, IMM+3)
#define VE_MSA_CASE_16_3(FUNC, RES, A, B, IMM) VE_MSA_CASE_4_3(FUNC, RES, A, B, IMM) VE_MSA_CASE_4_3(FUNC, RES, A, B, IMM+4) VE_MSA_CASE_4_3(FUNC, RES, A, B, IMM+8) VE_MSA_CASE_4_3(FUNC, RES, A, B, IMM+12)
#define VE_MSA_CASE_64_3(FUNC, RES, A, B, IMM) VE_MSA_CASE_16_3(FUNC, RES, A, B, IMM) VE_MSA_CASE_16_3(FUNC, RES, A, B, IMM+16) VE_MSA_CASE_16_3(FUNC, RES, A, B, IMM+32) VE_MSA_CASE_16_3(FUNC, RES, A, B, IMM+48)
#define VE_MSA_CASE_256_3(FUNC, RES, A, B, IMM) VE_MSA_CASE_64_3(FUNC, RES, A, B, IMM) VE_MSA_CASE_64_3(FUNC, RES, A, B, IMM+64) VE_MSA_CASE_64_3(FUNC, RES, A, B, IMM+128) VE_MSA_CASE_64_3(FUNC, RES, A, B, IMM+192)

#define VE_MSA_IMM6_SWITCH_2(FUNC, RES, A, IMM_VAL) \
	switch (IMM_VAL) { \
		VE_MSA_CASE_64(FUNC, RES, A, 0) \
		default: { return Result{}; } \
	}

#define VE_MSA_IMM6_SWITCH_3(FUNC, RES, A, B, IMM_VAL) \
	switch (IMM_VAL) { \
		VE_MSA_CASE_64_3(FUNC, RES, A, B, 0) \
		default: { return Result{}; } \
	}

#define VE_MSA_IMM8_SWITCH_3(FUNC, RES, A, B, IMM_VAL) \
	switch (IMM_VAL) { \
		VE_MSA_CASE_256_3(FUNC, RES, A, B, 0) \
		default: { return Result{}; } \
	}


		/**
		 * Bridge for simde_msa_bclr_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBclrB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if ((simdArg0->regType != Simd_v16i8 && simdArg0->regType != Simd_v16u8) ||
				(simdArg1->regType != Simd_v16i8 && simdArg1->regType != Simd_v16u8)) {
				return Result{};
			}

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			simde_v16u8 a_u, b_u;
			std::memcpy(&a_u, &simdArg0->reg, sizeof(a_u));
			std::memcpy(&b_u, &simdArg1->reg, sizeof(b_u));

			simde_v16u8 res = simde_msa_bclr_b(a_u, b_u);

			outObj->regType = simdArg0->regType;
			std::memcpy(&outObj->reg, &res, sizeof(res));

			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bclr_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBclrH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if ((simdArg0->regType != Simd_v8i16 && simdArg0->regType != Simd_v8u16) ||
				(simdArg1->regType != Simd_v8i16 && simdArg1->regType != Simd_v8u16)) {
				return Result{};
			}

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			simde_v8u16 a_u, b_u;
			std::memcpy(&a_u, &simdArg0->reg, sizeof(a_u));
			std::memcpy(&b_u, &simdArg1->reg, sizeof(b_u));

			simde_v8u16 res = simde_msa_bclr_h(a_u, b_u);

			outObj->regType = simdArg0->regType;
			std::memcpy(&outObj->reg, &res, sizeof(res));

			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bclr_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBclrW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if ((simdArg0->regType != Simd_v4i32 && simdArg0->regType != Simd_v4u32) ||
				(simdArg1->regType != Simd_v4i32 && simdArg1->regType != Simd_v4u32)) {
				return Result{};
			}

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			simde_v4u32 a_u, b_u;
			std::memcpy(&a_u, &simdArg0->reg, sizeof(a_u));
			std::memcpy(&b_u, &simdArg1->reg, sizeof(b_u));

			simde_v4u32 res = simde_msa_bclr_w(a_u, b_u);

			outObj->regType = simdArg0->regType;
			std::memcpy(&outObj->reg, &res, sizeof(res));

			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bclr_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBclrD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if ((simdArg0->regType != Simd_v2i64 && simdArg0->regType != Simd_v2u64) ||
				(simdArg1->regType != Simd_v2i64 && simdArg1->regType != Simd_v2u64)) {
				return Result{};
			}

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			simde_v2u64 a_u, b_u;
			std::memcpy(&a_u, &simdArg0->reg, sizeof(a_u));
			std::memcpy(&b_u, &simdArg1->reg, sizeof(b_u));

			simde_v2u64 res = simde_msa_bclr_d(a_u, b_u);

			outObj->regType = simdArg0->regType;
			std::memcpy(&outObj->reg, &res, sizeof(res));

			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bclri_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBclriB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v16i8 && simdArg0->regType != Simd_v16u8) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;
			if (imm < 0 || imm > 63) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			simde_v16u8 a_u;
			std::memcpy(&a_u, &simdArg0->reg, sizeof(a_u));
			simde_v16u8 res;

			VE_MSA_IMM6_SWITCH_2(simde_msa_bclri_b, res, a_u, imm)

			outObj->regType = simdArg0->regType;
			std::memcpy(&outObj->reg, &res, sizeof(res));

			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bclri_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBclriH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v8i16 && simdArg0->regType != Simd_v8u16) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;
			if (imm < 0 || imm > 63) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			simde_v8u16 a_u;
			std::memcpy(&a_u, &simdArg0->reg, sizeof(a_u));
			simde_v8u16 res;

			VE_MSA_IMM6_SWITCH_2(simde_msa_bclri_h, res, a_u, imm)

			outObj->regType = simdArg0->regType;
			std::memcpy(&outObj->reg, &res, sizeof(res));

			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bclri_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBclriW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4i32 && simdArg0->regType != Simd_v4u32) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;
			if (imm < 0 || imm > 63) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			simde_v4u32 a_u;
			std::memcpy(&a_u, &simdArg0->reg, sizeof(a_u));
			simde_v4u32 res;

			VE_MSA_IMM6_SWITCH_2(simde_msa_bclri_w, res, a_u, imm)

			outObj->regType = simdArg0->regType;
			std::memcpy(&outObj->reg, &res, sizeof(res));

			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bclri_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBclriD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2i64 && simdArg0->regType != Simd_v2u64) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;
			if (imm < 0 || imm > 63) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			simde_v2u64 a_u;
			std::memcpy(&a_u, &simdArg0->reg, sizeof(a_u));
			simde_v2u64 res;

			VE_MSA_IMM6_SWITCH_2(simde_msa_bclri_d, res, a_u, imm)

			outObj->regType = simdArg0->regType;
			std::memcpy(&outObj->reg, &res, sizeof(res));

			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_binsl_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBinslB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if ((simdArg0->regType != Simd_v16i8 && simdArg0->regType != Simd_v16u8) ||
				(simdArg1->regType != Simd_v16i8 && simdArg1->regType != Simd_v16u8) ||
				(simdArg2->regType != Simd_v16i8 && simdArg2->regType != Simd_v16u8)) {
				return Result{};
			}

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			simde_v16u8 a_u, b_u, c_u;
			std::memcpy(&a_u, &simdArg0->reg, sizeof(a_u));
			std::memcpy(&b_u, &simdArg1->reg, sizeof(b_u));
			std::memcpy(&c_u, &simdArg2->reg, sizeof(c_u));

			simde_v16u8 res = simde_msa_binsl_b(a_u, b_u, c_u);

			outObj->regType = simdArg0->regType;
			std::memcpy(&outObj->reg, &res, sizeof(res));

			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_binsl_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBinslH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if ((simdArg0->regType != Simd_v8i16 && simdArg0->regType != Simd_v8u16) ||
				(simdArg1->regType != Simd_v8i16 && simdArg1->regType != Simd_v8u16) ||
				(simdArg2->regType != Simd_v8i16 && simdArg2->regType != Simd_v8u16)) {
				return Result{};
			}

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			simde_v8u16 a_u, b_u, c_u;
			std::memcpy(&a_u, &simdArg0->reg, sizeof(a_u));
			std::memcpy(&b_u, &simdArg1->reg, sizeof(b_u));
			std::memcpy(&c_u, &simdArg2->reg, sizeof(c_u));

			simde_v8u16 res = simde_msa_binsl_h(a_u, b_u, c_u);

			outObj->regType = simdArg0->regType;
			std::memcpy(&outObj->reg, &res, sizeof(res));

			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_binsl_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBinslW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if ((simdArg0->regType != Simd_v4i32 && simdArg0->regType != Simd_v4u32) ||
				(simdArg1->regType != Simd_v4i32 && simdArg1->regType != Simd_v4u32) ||
				(simdArg2->regType != Simd_v4i32 && simdArg2->regType != Simd_v4u32)) {
				return Result{};
			}

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			simde_v4u32 a_u, b_u, c_u;
			std::memcpy(&a_u, &simdArg0->reg, sizeof(a_u));
			std::memcpy(&b_u, &simdArg1->reg, sizeof(b_u));
			std::memcpy(&c_u, &simdArg2->reg, sizeof(c_u));

			simde_v4u32 res = simde_msa_binsl_w(a_u, b_u, c_u);

			outObj->regType = simdArg0->regType;
			std::memcpy(&outObj->reg, &res, sizeof(res));

			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_binsl_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBinslD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if ((simdArg0->regType != Simd_v2i64 && simdArg0->regType != Simd_v2u64) ||
				(simdArg1->regType != Simd_v2i64 && simdArg1->regType != Simd_v2u64) ||
				(simdArg2->regType != Simd_v2i64 && simdArg2->regType != Simd_v2u64)) {
				return Result{};
			}

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			simde_v2u64 a_u, b_u, c_u;
			std::memcpy(&a_u, &simdArg0->reg, sizeof(a_u));
			std::memcpy(&b_u, &simdArg1->reg, sizeof(b_u));
			std::memcpy(&c_u, &simdArg2->reg, sizeof(c_u));

			simde_v2u64 res = simde_msa_binsl_d(a_u, b_u, c_u);

			outObj->regType = simdArg0->regType;
			std::memcpy(&outObj->reg, &res, sizeof(res));

			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_binsli_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBinsliB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[2].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v16i8 && simdArg1->regType == Simd_v16i8) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v16u8 && simdArg1->regType == Simd_v16u8) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[2], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v16u8 : Simd_v16i8;
			outObj->reg.v16u8 = simde_msa_binsli_b(simdArg0->reg.v16u8, simdArg1->reg.v16u8, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_binsli_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBinsliH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[2].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v8i16 && simdArg1->regType == Simd_v8i16) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v8u16 && simdArg1->regType == Simd_v8u16) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[2], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v8u16 : Simd_v8i16;
			outObj->reg.v8u16 = simde_msa_binsli_h(simdArg0->reg.v8u16, simdArg1->reg.v8u16, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_binsli_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBinsliW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[2].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v4i32 && simdArg1->regType == Simd_v4i32) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v4u32 && simdArg1->regType == Simd_v4u32) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[2], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v4u32 : Simd_v4i32;
			outObj->reg.v4u32 = simde_msa_binsli_w(simdArg0->reg.v4u32, simdArg1->reg.v4u32, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_binsli_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBinsliD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[2].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v2i64 && simdArg1->regType == Simd_v2i64) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v2u64 && simdArg1->regType == Simd_v2u64) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[2], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v2u64 : Simd_v2i64;
			outObj->reg.v2u64 = simde_msa_binsli_d(simdArg0->reg.v2u64, simdArg1->reg.v2u64, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_binsr_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBinsrB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v16i8 && simdArg1->regType == Simd_v16i8 && simdArg2->regType == Simd_v16i8) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v16u8 && simdArg1->regType == Simd_v16u8 && simdArg2->regType == Simd_v16u8) {
				isUnsigned = true;
			}
			else { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v16u8 : Simd_v16i8;
			outObj->reg.v16u8 = simde_msa_binsr_b(simdArg0->reg.v16u8, simdArg1->reg.v16u8, simdArg2->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_binsr_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBinsrH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v8i16 && simdArg1->regType == Simd_v8i16 && simdArg2->regType == Simd_v8i16) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v8u16 && simdArg1->regType == Simd_v8u16 && simdArg2->regType == Simd_v8u16) {
				isUnsigned = true;
			}
			else { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v8u16 : Simd_v8i16;
			outObj->reg.v8u16 = simde_msa_binsr_h(simdArg0->reg.v8u16, simdArg1->reg.v8u16, simdArg2->reg.v8u16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_binsr_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBinsrW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v4i32 && simdArg1->regType == Simd_v4i32 && simdArg2->regType == Simd_v4i32) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v4u32 && simdArg1->regType == Simd_v4u32 && simdArg2->regType == Simd_v4u32) {
				isUnsigned = true;
			}
			else { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v4u32 : Simd_v4i32;
			outObj->reg.v4u32 = simde_msa_binsr_w(simdArg0->reg.v4u32, simdArg1->reg.v4u32, simdArg2->reg.v4u32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_binsr_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBinsrD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v2i64 && simdArg1->regType == Simd_v2i64 && simdArg2->regType == Simd_v2i64) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v2u64 && simdArg1->regType == Simd_v2u64 && simdArg2->regType == Simd_v2u64) {
				isUnsigned = true;
			}
			else { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v2u64 : Simd_v2i64;
			outObj->reg.v2u64 = simde_msa_binsr_d(simdArg0->reg.v2u64, simdArg1->reg.v2u64, simdArg2->reg.v2u64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_binsri_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBinsriB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[2].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v16i8 && simdArg1->regType == Simd_v16i8) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v16u8 && simdArg1->regType == Simd_v16u8) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[2], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v16u8 : Simd_v16i8;
			outObj->reg.v16u8 = simde_msa_binsri_b(simdArg0->reg.v16u8, simdArg1->reg.v16u8, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_binsri_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBinsriH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[2].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v8i16 && simdArg1->regType == Simd_v8i16) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v8u16 && simdArg1->regType == Simd_v8u16) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[2], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v8u16 : Simd_v8i16;
			outObj->reg.v8u16 = simde_msa_binsri_h(simdArg0->reg.v8u16, simdArg1->reg.v8u16, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_binsri_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBinsriW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[2].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v4i32 && simdArg1->regType == Simd_v4i32) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v4u32 && simdArg1->regType == Simd_v4u32) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[2], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v4u32 : Simd_v4i32;
			outObj->reg.v4u32 = simde_msa_binsri_w(simdArg0->reg.v4u32, simdArg1->reg.v4u32, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_binsri_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBinsriD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[2].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v2i64 && simdArg1->regType == Simd_v2i64) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v2u64 && simdArg1->regType == Simd_v2u64) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[2], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v2u64 : Simd_v2i64;
			outObj->reg.v2u64 = simde_msa_binsri_d(simdArg0->reg.v2u64, simdArg1->reg.v2u64, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bmnz_v.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBmnzV(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v16i8 && simdArg1->regType == Simd_v16i8 && simdArg2->regType == Simd_v16i8) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v16u8 && simdArg1->regType == Simd_v16u8 && simdArg2->regType == Simd_v16u8) {
				isUnsigned = true;
			}
			else { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v16u8 : Simd_v16i8;
			outObj->reg.v16u8 = simde_msa_bmnz_v(simdArg0->reg.v16u8, simdArg1->reg.v16u8, simdArg2->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bmnzi_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBmnziB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[2].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v16i8 && simdArg1->regType == Simd_v16i8) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v16u8 && simdArg1->regType == Simd_v16u8) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[2], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v16u8 : Simd_v16i8;
			outObj->reg.v16u8 = simde_msa_bmnzi_b(simdArg0->reg.v16u8, simdArg1->reg.v16u8, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bmz_v.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBmzV(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v16i8 && simdArg1->regType == Simd_v16i8 && simdArg2->regType == Simd_v16i8) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v16u8 && simdArg1->regType == Simd_v16u8 && simdArg2->regType == Simd_v16u8) {
				isUnsigned = true;
			}
			else { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v16u8 : Simd_v16i8;
			outObj->reg.v16u8 = simde_msa_bmz_v(simdArg0->reg.v16u8, simdArg1->reg.v16u8, simdArg2->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bmzi_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBmziB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[2].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v16i8 && simdArg1->regType == Simd_v16i8) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v16u8 && simdArg1->regType == Simd_v16u8) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[2], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v16u8 : Simd_v16i8;
			outObj->reg.v16u8 = simde_msa_bmzi_b(simdArg0->reg.v16u8, simdArg1->reg.v16u8, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bneg_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBnegB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v16i8 && simdArg1->regType == Simd_v16i8) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v16u8 && simdArg1->regType == Simd_v16u8) {
				isUnsigned = true;
			}
			else { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v16u8 : Simd_v16i8;
			outObj->reg.v16u8 = simde_msa_bneg_b(simdArg0->reg.v16u8, simdArg1->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bneg_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBnegH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v8i16 && simdArg1->regType == Simd_v8i16) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v8u16 && simdArg1->regType == Simd_v8u16) {
				isUnsigned = true;
			}
			else { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v8u16 : Simd_v8i16;
			outObj->reg.v8u16 = simde_msa_bneg_h(simdArg0->reg.v8u16, simdArg1->reg.v8u16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bneg_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBnegW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v4i32 && simdArg1->regType == Simd_v4i32) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v4u32 && simdArg1->regType == Simd_v4u32) {
				isUnsigned = true;
			}
			else { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v4u32 : Simd_v4i32;
			outObj->reg.v4u32 = simde_msa_bneg_w(simdArg0->reg.v4u32, simdArg1->reg.v4u32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bneg_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBnegD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v2i64 && simdArg1->regType == Simd_v2i64) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v2u64 && simdArg1->regType == Simd_v2u64) {
				isUnsigned = true;
			}
			else { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v2u64 : Simd_v2i64;
			outObj->reg.v2u64 = simde_msa_bneg_d(simdArg0->reg.v2u64, simdArg1->reg.v2u64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bnegi_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBnegiB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v16i8) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v16u8) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v16u8 : Simd_v16i8;
			outObj->reg.v16u8 = simde_msa_bnegi_b(simdArg0->reg.v16u8, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bnegi_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBnegiH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v8i16) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v8u16) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v8u16 : Simd_v8i16;
			outObj->reg.v8u16 = simde_msa_bnegi_h(simdArg0->reg.v8u16, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bnegi_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBnegiW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v4i32) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v4u32) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v4u32 : Simd_v4i32;
			outObj->reg.v4u32 = simde_msa_bnegi_w(simdArg0->reg.v4u32, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bnegi_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBnegiD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v2i64) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v2u64) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v2u64 : Simd_v2i64;
			outObj->reg.v2u64 = simde_msa_bnegi_d(simdArg0->reg.v2u64, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bsel_v.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBselV(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v16i8 && simdArg1->regType == Simd_v16i8 && simdArg2->regType == Simd_v16i8) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v16u8 && simdArg1->regType == Simd_v16u8 && simdArg2->regType == Simd_v16u8) {
				isUnsigned = true;
			}
			else { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v16u8 : Simd_v16i8;
			outObj->reg.v16u8 = simde_msa_bsel_v(simdArg0->reg.v16u8, simdArg1->reg.v16u8, simdArg2->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bseli_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBseliB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[2].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v16i8 && simdArg1->regType == Simd_v16i8) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v16u8 && simdArg1->regType == Simd_v16u8) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[2], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v16u8 : Simd_v16i8;
			outObj->reg.v16u8 = simde_msa_bseli_b(simdArg0->reg.v16u8, simdArg1->reg.v16u8, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bset_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBsetB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v16i8 && simdArg1->regType == Simd_v16i8) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v16u8 && simdArg1->regType == Simd_v16u8) {
				isUnsigned = true;
			}
			else { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v16u8 : Simd_v16i8;
			outObj->reg.v16u8 = simde_msa_bset_b(simdArg0->reg.v16u8, simdArg1->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bset_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBsetH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v8i16 && simdArg1->regType == Simd_v8i16) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v8u16 && simdArg1->regType == Simd_v8u16) {
				isUnsigned = true;
			}
			else { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v8u16 : Simd_v8i16;
			outObj->reg.v8u16 = simde_msa_bset_h(simdArg0->reg.v8u16, simdArg1->reg.v8u16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bset_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBsetW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v4i32 && simdArg1->regType == Simd_v4i32) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v4u32 && simdArg1->regType == Simd_v4u32) {
				isUnsigned = true;
			}
			else { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v4u32 : Simd_v4i32;
			outObj->reg.v4u32 = simde_msa_bset_w(simdArg0->reg.v4u32, simdArg1->reg.v4u32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bset_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBsetD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v2i64 && simdArg1->regType == Simd_v2i64) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v2u64 && simdArg1->regType == Simd_v2u64) {
				isUnsigned = true;
			}
			else { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v2u64 : Simd_v2i64;
			outObj->reg.v2u64 = simde_msa_bset_d(simdArg0->reg.v2u64, simdArg1->reg.v2u64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bseti_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBsetiB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v16i8) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v16u8) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v16u8 : Simd_v16i8;
			outObj->reg.v16u8 = simde_msa_bseti_b(simdArg0->reg.v16u8, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bseti_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBsetiH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v8i16) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v8u16) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v8u16 : Simd_v8i16;
			outObj->reg.v8u16 = simde_msa_bseti_h(simdArg0->reg.v8u16, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bseti_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBsetiW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v4i32) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v4u32) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v4u32 : Simd_v4i32;
			outObj->reg.v4u32 = simde_msa_bseti_w(simdArg0->reg.v4u32, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_bseti_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaBsetiD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			bool isUnsigned = false;
			if (simdArg0->regType == Simd_v2i64) {
				isUnsigned = false;
			}
			else if (simdArg0->regType == Simd_v2u64) {
				isUnsigned = true;
			}
			else { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = isUnsigned ? Simd_v2u64 : Simd_v2i64;
			outObj->reg.v2u64 = simde_msa_bseti_d(simdArg0->reg.v2u64, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_cast_to_scalar_double.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCastToScalarDouble(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2f64) { return Result{}; }

			double res = simde_msa_cast_to_scalar_double(simdArg0->reg.v2f64);
			return Result::make(res);
		}

		/**
		 * Bridge for simde_msa_cast_to_scalar_float.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCastToScalarFloat(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4f32) { return Result{}; }

			float res = simde_msa_cast_to_scalar_float(simdArg0->reg.v4f32);
			return Result::make(static_cast<double>(res));
		}

		/**
		 * Bridge for simde_msa_cast_to_vector_double.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCastToVectorDouble(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (!args[0].isPrimitive()) { return Result{}; }

			double val = context->convertResult(args[0], NumericConstant::Floating).value.doubleVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_cast_to_vector_double(val);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_cast_to_vector_float.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCastToVectorFloat(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (!args[0].isPrimitive()) { return Result{}; }

			float val = static_cast<float>(context->convertResult(args[0], NumericConstant::Floating).value.doubleVal);

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_cast_to_vector_float(val);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ceq_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCeqB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			SimdRegisterType type0 = simdArg0->regType;
			SimdRegisterType type1 = simdArg1->regType;

			if (type0 != Simd_v16i8 && type0 != Simd_v16u8) { return Result{}; }
			if (type0 != type1) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = type0;
			outObj->reg.v16i8 = simde_msa_ceq_b(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ceq_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCeqH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			SimdRegisterType type0 = simdArg0->regType;
			SimdRegisterType type1 = simdArg1->regType;

			if (type0 != Simd_v8i16 && type0 != Simd_v8u16) { return Result{}; }
			if (type0 != type1) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = type0;
			outObj->reg.v8i16 = simde_msa_ceq_h(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ceq_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCeqW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			SimdRegisterType type0 = simdArg0->regType;
			SimdRegisterType type1 = simdArg1->regType;

			if (type0 != Simd_v4i32 && type0 != Simd_v4u32) { return Result{}; }
			if (type0 != type1) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = type0;
			outObj->reg.v4i32 = simde_msa_ceq_w(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ceq_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCeqD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			SimdRegisterType type0 = simdArg0->regType;
			SimdRegisterType type1 = simdArg1->regType;

			if (type0 != Simd_v2i64 && type0 != Simd_v2u64) { return Result{}; }
			if (type0 != type1) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = type0;
			outObj->reg.v2i64 = simde_msa_ceq_d(simdArg0->reg.v2i64, simdArg1->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ceqi_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCeqiB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdRegisterType type0 = simdArg0->regType;

			if (type0 != Simd_v16i8 && type0 != Simd_v16u8) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = type0;
			outObj->reg.v16i8 = simde_msa_ceqi_b(simdArg0->reg.v16i8, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ceqi_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCeqiH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdRegisterType type0 = simdArg0->regType;

			if (type0 != Simd_v8i16 && type0 != Simd_v8u16) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = type0;
			outObj->reg.v8i16 = simde_msa_ceqi_h(simdArg0->reg.v8i16, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ceqi_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCeqiW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdRegisterType type0 = simdArg0->regType;

			if (type0 != Simd_v4i32 && type0 != Simd_v4u32) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = type0;
			outObj->reg.v4i32 = simde_msa_ceqi_w(simdArg0->reg.v4i32, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ceqi_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCeqiD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdRegisterType type0 = simdArg0->regType;

			if (type0 != Simd_v2i64 && type0 != Simd_v2u64) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = type0;
			outObj->reg.v2i64 = simde_msa_ceqi_d(simdArg0->reg.v2i64, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_cfcmsa.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCfcmsa(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (!args[0].isPrimitive()) { return Result{}; }

			int64_t cs = context->convertResult(args[0], NumericConstant::Signed).value.intVal;

			return Result::make(static_cast<int64_t>(simde_msa_cfcmsa(cs)));
		}

		/**
		 * Bridge for simde_msa_cle_s_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCleSB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_cle_s_b(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_cle_s_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCleSH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_cle_s_h(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_cle_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCleSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_cle_s_w(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_cle_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCleSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg1->regType != Simd_v2i64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_cle_s_d(simdArg0->reg.v2i64, simdArg1->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_cle_u_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCleUB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16u8 || simdArg1->regType != Simd_v16u8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16u8;
			outObj->reg.v16u8 = simde_msa_cle_u_b(simdArg0->reg.v16u8, simdArg1->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_cle_u_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCleUH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8u16 || simdArg1->regType != Simd_v8u16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8u16;
			outObj->reg.v8u16 = simde_msa_cle_u_h(simdArg0->reg.v8u16, simdArg1->reg.v8u16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_cle_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCleUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4u32 || simdArg1->regType != Simd_v4u32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4u32;
			outObj->reg.v4u32 = simde_msa_cle_u_w(simdArg0->reg.v4u32, simdArg1->reg.v4u32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_cle_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCleUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2u64 || simdArg1->regType != Simd_v2u64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2u64;
			outObj->reg.v2u64 = simde_msa_cle_u_d(simdArg0->reg.v2u64, simdArg1->reg.v2u64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clei_s_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCleiSB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v16i8) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_clei_s_b(simdArg0->reg.v16i8, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clei_s_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCleiSH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v8i16) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_clei_s_h(simdArg0->reg.v8i16, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clei_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCleiSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4i32) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_clei_s_w(simdArg0->reg.v4i32, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clei_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCleiSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2i64) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_clei_s_d(simdArg0->reg.v2i64, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clei_u_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCleiUB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v16u8) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16u8;
			outObj->reg.v16u8 = simde_msa_clei_u_b(simdArg0->reg.v16u8, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clei_u_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCleiUH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v8u16) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8u16;
			outObj->reg.v8u16 = simde_msa_clei_u_h(simdArg0->reg.v8u16, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clei_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCleiUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4u32) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4u32;
			outObj->reg.v4u32 = simde_msa_clei_u_w(simdArg0->reg.v4u32, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clei_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCleiUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2u64) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2u64;
			outObj->reg.v2u64 = simde_msa_clei_u_d(simdArg0->reg.v2u64, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clt_s_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCltSB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_clt_s_b(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clt_s_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCltSH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_clt_s_h(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clt_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCltSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_clt_s_w(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clt_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCltSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg1->regType != Simd_v2i64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_clt_s_d(simdArg0->reg.v2i64, simdArg1->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clt_u_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCltUB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16u8 || simdArg1->regType != Simd_v16u8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16u8;
			outObj->reg.v16u8 = simde_msa_clt_u_b(simdArg0->reg.v16u8, simdArg1->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clt_u_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCltUH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8u16 || simdArg1->regType != Simd_v8u16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8u16;
			outObj->reg.v8u16 = simde_msa_clt_u_h(simdArg0->reg.v8u16, simdArg1->reg.v8u16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clt_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCltUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4u32 || simdArg1->regType != Simd_v4u32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4u32;
			outObj->reg.v4u32 = simde_msa_clt_u_w(simdArg0->reg.v4u32, simdArg1->reg.v4u32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clt_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCltUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2u64 || simdArg1->regType != Simd_v2u64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2u64;
			outObj->reg.v2u64 = simde_msa_clt_u_d(simdArg0->reg.v2u64, simdArg1->reg.v2u64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clti_s_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCltiSB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v16i8) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_clti_s_b(simdArg0->reg.v16i8, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clti_s_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCltiSH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v8i16) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_clti_s_h(simdArg0->reg.v8i16, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clti_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCltiSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4i32) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_clti_s_w(simdArg0->reg.v4i32, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clti_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCltiSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2i64) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_clti_s_d(simdArg0->reg.v2i64, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clti_u_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCltiUB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v16u8) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16u8;
			outObj->reg.v16u8 = simde_msa_clti_u_b(simdArg0->reg.v16u8, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clti_u_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCltiUH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v8u16) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8u16;
			outObj->reg.v8u16 = simde_msa_clti_u_h(simdArg0->reg.v8u16, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clti_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCltiUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4u32) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4u32;
			outObj->reg.v4u32 = simde_msa_clti_u_w(simdArg0->reg.v4u32, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_clti_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCltiUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2u64) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2u64;
			outObj->reg.v2u64 = simde_msa_clti_u_d(simdArg0->reg.v2u64, imm);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_copy_s_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCopySB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v16i8) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			int64_t res = static_cast<int64_t>(simde_msa_copy_s_b(simdArg0->reg.v16i8, imm));
			return Result::make(res);
		}

		/**
		 * Bridge for simde_msa_copy_s_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCopySH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v8i16) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			int64_t res = static_cast<int64_t>(simde_msa_copy_s_h(simdArg0->reg.v8i16, imm));
			return Result::make(res);
		}

		/**
		 * Bridge for simde_msa_copy_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCopySW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4i32) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			int64_t res = static_cast<int64_t>(simde_msa_copy_s_w(simdArg0->reg.v4i32, imm));
			return Result::make(res);
		}

		/**
		 * Bridge for simde_msa_copy_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCopySD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2i64) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			int64_t res = static_cast<int64_t>(simde_msa_copy_s_d(simdArg0->reg.v2i64, imm));
			return Result::make(res);
		}

		/**
		 * Bridge for simde_msa_copy_u_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCopyUB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v16u8) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			uint64_t res = static_cast<uint64_t>(simde_msa_copy_u_b(simdArg0->reg.v16u8, imm));
			return Result::make(res);
		}

		/**
		 * Bridge for simde_msa_copy_u_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCopyUH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v8u16) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			uint64_t res = static_cast<uint64_t>(simde_msa_copy_u_h(simdArg0->reg.v8u16, imm));
			return Result::make(res);
		}

		/**
		 * Bridge for simde_msa_copy_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCopyUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4u32) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			uint64_t res = static_cast<uint64_t>(simde_msa_copy_u_w(simdArg0->reg.v4u32, imm));
			return Result::make(res);
		}

		/**
		 * Bridge for simde_msa_copy_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaCopyUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2u64) { return Result{}; }

			int64_t imm = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			uint64_t res = static_cast<uint64_t>(simde_msa_copy_u_d(simdArg0->reg.v2u64, imm));
			return Result::make(res);
		}

		/**
		 * Bridge for simde_msa_div_s_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDivSB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_div_s_b(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_div_s_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDivSH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_div_s_h(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_div_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDivSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_div_s_w(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_div_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDivSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg1->regType != Simd_v2i64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_div_s_d(simdArg0->reg.v2i64, simdArg1->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_div_u_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDivUB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16u8 || simdArg1->regType != Simd_v16u8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16u8;
			outObj->reg.v16u8 = simde_msa_div_u_b(simdArg0->reg.v16u8, simdArg1->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_div_u_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDivUH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8u16 || simdArg1->regType != Simd_v8u16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8u16;
			outObj->reg.v8u16 = simde_msa_div_u_h(simdArg0->reg.v8u16, simdArg1->reg.v8u16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_div_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDivUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4u32 || simdArg1->regType != Simd_v4u32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4u32;
			outObj->reg.v4u32 = simde_msa_div_u_w(simdArg0->reg.v4u32, simdArg1->reg.v4u32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_div_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDivUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2u64 || simdArg1->regType != Simd_v2u64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2u64;
			outObj->reg.v2u64 = simde_msa_div_u_d(simdArg0->reg.v2u64, simdArg1->reg.v2u64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dotp_s_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDotpSH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_dotp_s_h(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dotp_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDotpSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_dotp_s_w(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dotp_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDotpSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_dotp_s_d(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dotp_u_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDotpUH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16u8 || simdArg1->regType != Simd_v16u8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8u16;
			outObj->reg.v8u16 = simde_msa_dotp_u_h(simdArg0->reg.v16u8, simdArg1->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dotp_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDotpUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8u16 || simdArg1->regType != Simd_v8u16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4u32;
			outObj->reg.v4u32 = simde_msa_dotp_u_w(simdArg0->reg.v8u16, simdArg1->reg.v8u16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dotp_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDotpUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4u32 || simdArg1->regType != Simd_v4u32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2u64;
			outObj->reg.v2u64 = simde_msa_dotp_u_d(simdArg0->reg.v4u32, simdArg1->reg.v4u32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dpadd_s_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDpaddSH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v16i8 || simdArg2->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_dpadd_s_h(simdArg0->reg.v8i16, simdArg1->reg.v16i8, simdArg2->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dpadd_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDpaddSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v8i16 || simdArg2->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_dpadd_s_w(simdArg0->reg.v4i32, simdArg1->reg.v8i16, simdArg2->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dpadd_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDpaddSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg1->regType != Simd_v4i32 || simdArg2->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_dpadd_s_d(simdArg0->reg.v2i64, simdArg1->reg.v4i32, simdArg2->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dpadd_u_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDpaddUH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v8u16 || simdArg1->regType != Simd_v16u8 || simdArg2->regType != Simd_v16u8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8u16;
			outObj->reg.v8u16 = simde_msa_dpadd_u_h(simdArg0->reg.v8u16, simdArg1->reg.v16u8, simdArg2->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dpadd_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDpaddUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v4u32 || simdArg1->regType != Simd_v8u16 || simdArg2->regType != Simd_v8u16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4u32;
			outObj->reg.v4u32 = simde_msa_dpadd_u_w(simdArg0->reg.v4u32, simdArg1->reg.v8u16, simdArg2->reg.v8u16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dpadd_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDpaddUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v2u64 || simdArg1->regType != Simd_v4u32 || simdArg2->regType != Simd_v4u32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2u64;
			outObj->reg.v2u64 = simde_msa_dpadd_u_d(simdArg0->reg.v2u64, simdArg1->reg.v4u32, simdArg2->reg.v4u32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dpsub_s_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDpsubSH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v16i8 || simdArg2->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_dpsub_s_h(simdArg0->reg.v8i16, simdArg1->reg.v16i8, simdArg2->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dpsub_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDpsubSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v8i16 || simdArg2->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_dpsub_s_w(simdArg0->reg.v4i32, simdArg1->reg.v8i16, simdArg2->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dpsub_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDpsubSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg1->regType != Simd_v4i32 || simdArg2->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_dpsub_s_d(simdArg0->reg.v2i64, simdArg1->reg.v4i32, simdArg2->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dpsub_u_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDpsubUH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v8u16 || simdArg1->regType != Simd_v16u8 || simdArg2->regType != Simd_v16u8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8u16;
			outObj->reg.v8u16 = simde_msa_dpsub_u_h(simdArg0->reg.v8u16, simdArg1->reg.v16u8, simdArg2->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dpsub_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDpsubUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v4u32 || simdArg1->regType != Simd_v8u16 || simdArg2->regType != Simd_v8u16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4u32;
			outObj->reg.v4u32 = simde_msa_dpsub_u_w(simdArg0->reg.v4u32, simdArg1->reg.v8u16, simdArg2->reg.v8u16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_dpsub_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaDpsubUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v2u64 || simdArg1->regType != Simd_v4u32 || simdArg2->regType != Simd_v4u32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2u64;
			outObj->reg.v2u64 = simde_msa_dpsub_u_d(simdArg0->reg.v2u64, simdArg1->reg.v4u32, simdArg2->reg.v4u32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fadd_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFaddW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_fadd_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fadd_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFaddD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_fadd_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcaf_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcafW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fcaf_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcaf_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcafD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fcaf_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fceq_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFceqW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fceq_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fceq_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFceqD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fceq_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fclass_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFclassW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			if (simdArg0->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fclass_w(simdArg0->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fclass_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFclassD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			if (simdArg0->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fclass_d(simdArg0->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcle_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcleW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fcle_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcle_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcleD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fcle_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fclt_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcltW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fclt_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fclt_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcltD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fclt_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcne_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcneW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fcne_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcne_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcneD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fcne_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcor_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcorW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fcor_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcor_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcorD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fcor_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcueq_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcueqW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fcueq_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcueq_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcueqD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fcueq_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcule_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFculeW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fcule_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcule_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFculeD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fcule_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcult_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcultW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fcult_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcult_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcultD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fcult_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcun_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcunW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fcun_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcun_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcunD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fcun_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcune_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcuneW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fcune_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fcune_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFcuneD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fcune_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fdiv_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFdivW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_fdiv_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fdiv_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFdivD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_fdiv_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fexdo_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFexdoH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_fexdo_h(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fexdo_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFexdoW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_fexdo_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fexp2_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFexp2W(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
            
			if (simdArg0->regType != Simd_v4f32) { return Result{}; }
			if (simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_fexp2_w(simdArg0->reg.v4f32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fexp2_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFexp2D(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64) { return Result{}; }
			if (simdArg1->regType != Simd_v2i64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_fexp2_d(simdArg0->reg.v2f64, simdArg1->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fexupl_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFexuplW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_fexupl_w(simdArg0->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fexupl_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFexuplD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_fexupl_d(simdArg0->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fexupr_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFexuprW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_fexupr_w(simdArg0->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fexupr_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFexuprD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_fexupr_d(simdArg0->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ffint_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFfintSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_ffint_s_w(simdArg0->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ffint_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFfintSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2i64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_ffint_s_d(simdArg0->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ffint_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFfintUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4u32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_ffint_u_w(simdArg0->reg.v4u32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ffint_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFfintUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2u64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_ffint_u_d(simdArg0->reg.v2u64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ffql_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFfqlW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_ffql_w(simdArg0->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ffql_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFfqlD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_ffql_d(simdArg0->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ffqr_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFfqrW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_ffqr_w(simdArg0->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ffqr_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFfqrD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_ffqr_d(simdArg0->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fill_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFillB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (!args[0].isPrimitive()) { return Result{}; }

			int64_t val = context->convertResult(args[0], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_fill_b(static_cast<int8_t>(val));
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fill_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFillH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (!args[0].isPrimitive()) { return Result{}; }

			int64_t val = context->convertResult(args[0], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_fill_h(static_cast<int16_t>(val));
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fill_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFillW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (!args[0].isPrimitive()) { return Result{}; }

			int64_t val = context->convertResult(args[0], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fill_w(static_cast<int32_t>(val));
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fill_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFillD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (!args[0].isPrimitive()) { return Result{}; }

			int64_t val = context->convertResult(args[0], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fill_d(val);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_flog2_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFlog2W(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_flog2_w(simdArg0->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_flog2_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFlog2D(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_flog2_d(simdArg0->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fmadd_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFmaddW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32 || simdArg2->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_fmadd_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32, simdArg2->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fmadd_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFmaddD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64 || simdArg2->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_fmadd_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64, simdArg2->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fmax_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFmaxW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_fmax_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fmax_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFmaxD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_fmax_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fmax_a_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFmaxAW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_fmax_a_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fmax_a_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFmaxAD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_fmax_a_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fmin_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFminW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_fmin_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fmin_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFminD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_fmin_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fmin_a_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFminAW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_fmin_a_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fmin_a_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFminAD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_fmin_a_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fmsub_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFmsubW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32 || simdArg2->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_fmsub_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32, simdArg2->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fmsub_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFmsubD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64 || simdArg2->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_fmsub_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64, simdArg2->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fmul_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFmulW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_fmul_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fmul_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFmulD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_fmul_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_frcp_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFrcpW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			if (simdArg0->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_frcp_w(simdArg0->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_frcp_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFrcpD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			if (simdArg0->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_frcp_d(simdArg0->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_frint_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFrintW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			if (simdArg0->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_frint_w(simdArg0->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_frint_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFrintD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			if (simdArg0->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_frint_d(simdArg0->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_frsqrt_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFrsqrtW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			if (simdArg0->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_frsqrt_w(simdArg0->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_frsqrt_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFrsqrtD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			if (simdArg0->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_frsqrt_d(simdArg0->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsaf_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsafW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fsaf_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsaf_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsafD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fsaf_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fseq_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFseqW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fseq_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fseq_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFseqD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fseq_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsle_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsleW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fsle_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsle_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsleD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fsle_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fslt_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsltW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fslt_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fslt_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsltD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fslt_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsne_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsneW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fsne_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsne_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsneD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fsne_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsor_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsorW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fsor_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsor_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsorD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fsor_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsqrt_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsqrtW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			if (simdArg0->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_fsqrt_w(simdArg0->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsqrt_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsqrtD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);

			if (simdArg0->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_fsqrt_d(simdArg0->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsub_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsubW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4f32;
			outObj->reg.v4f32 = simde_msa_fsub_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsub_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsubD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2f64;
			outObj->reg.v2f64 = simde_msa_fsub_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsueq_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsueqW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fsueq_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsueq_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsueqD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fsueq_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsule_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsuleW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fsule_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsule_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsuleD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fsule_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsult_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsultW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fsult_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsult_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsultD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fsult_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsun_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsunW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fsun_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsun_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsunD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fsun_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsune_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsuneW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_fsune_w(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_fsune_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFsuneD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_fsune_d(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ftint_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFtintSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_ftint_s_w(simdArg0->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ftint_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFtintSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_ftint_s_d(simdArg0->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ftint_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFtintUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4u32;
			outObj->reg.v4u32 = simde_msa_ftint_u_w(simdArg0->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ftint_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFtintUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2u64;
			outObj->reg.v2u64 = simde_msa_ftint_u_d(simdArg0->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ftq_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFtqH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4f32 || simdArg1->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_ftq_h(simdArg0->reg.v4f32, simdArg1->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ftq_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFtqW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2f64 || simdArg1->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_ftq_w(simdArg0->reg.v2f64, simdArg1->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ftrunc_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFtruncSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_ftrunc_s_w(simdArg0->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ftrunc_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFtruncSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_ftrunc_s_d(simdArg0->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ftrunc_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFtruncUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4f32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4u32;
			outObj->reg.v4u32 = simde_msa_ftrunc_u_w(simdArg0->reg.v4f32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ftrunc_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaFtruncUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 1) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2f64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2u64;
			outObj->reg.v2u64 = simde_msa_ftrunc_u_d(simdArg0->reg.v2f64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_hadd_s_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaHaddSH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_hadd_s_h(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_hadd_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaHaddSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_hadd_s_w(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_hadd_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaHaddSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_hadd_s_d(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_hadd_u_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaHaddUH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16u8 || simdArg1->regType != Simd_v16u8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8u16;
			outObj->reg.v8u16 = simde_msa_hadd_u_h(simdArg0->reg.v16u8, simdArg1->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_hadd_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaHaddUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8u16 || simdArg1->regType != Simd_v8u16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4u32;
			outObj->reg.v4u32 = simde_msa_hadd_u_w(simdArg0->reg.v8u16, simdArg1->reg.v8u16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_hadd_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaHaddUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4u32 || simdArg1->regType != Simd_v4u32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2u64;
			outObj->reg.v2u64 = simde_msa_hadd_u_d(simdArg0->reg.v4u32, simdArg1->reg.v4u32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_hsub_s_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaHsubSH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_hsub_s_h(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_hsub_s_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaHsubSW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_hsub_s_w(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_hsub_s_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaHsubSD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_hsub_s_d(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_hsub_u_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaHsubUH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16u8 || simdArg1->regType != Simd_v16u8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8u16;
			outObj->reg.v8u16 = simde_msa_hsub_u_h(simdArg0->reg.v16u8, simdArg1->reg.v16u8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_hsub_u_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaHsubUW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8u16 || simdArg1->regType != Simd_v8u16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4u32;
			outObj->reg.v4u32 = simde_msa_hsub_u_w(simdArg0->reg.v8u16, simdArg1->reg.v8u16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_hsub_u_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaHsubUD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4u32 || simdArg1->regType != Simd_v4u32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2u64;
			outObj->reg.v2u64 = simde_msa_hsub_u_d(simdArg0->reg.v4u32, simdArg1->reg.v4u32);
			return outObj->createResult();
		}

		// == Functions.
		/**
		 * Bridge for simde_msa_ilvev_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaIlvevB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_ilvev_b(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ilvev_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaIlvevH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_ilvev_h(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ilvev_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaIlvevW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_ilvev_w(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ilvev_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaIlvevD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg1->regType != Simd_v2i64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_ilvev_d(simdArg0->reg.v2i64, simdArg1->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ilvl_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaIlvlB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_ilvl_b(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ilvl_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaIlvlH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_ilvl_h(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ilvl_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaIlvlW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_ilvl_w(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ilvl_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaIlvlD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg1->regType != Simd_v2i64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_ilvl_d(simdArg0->reg.v2i64, simdArg1->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ilvod_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaIlvodB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_ilvod_b(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ilvod_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaIlvodH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_ilvod_h(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ilvod_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaIlvodW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_ilvod_w(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ilvod_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaIlvodD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg1->regType != Simd_v2i64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_ilvod_d(simdArg0->reg.v2i64, simdArg1->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ilvr_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaIlvrB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg1->regType != Simd_v16i8) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_ilvr_b(simdArg0->reg.v16i8, simdArg1->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ilvr_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaIlvrH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg1->regType != Simd_v8i16) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_ilvr_h(simdArg0->reg.v8i16, simdArg1->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ilvr_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaIlvrW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg1->regType != Simd_v4i32) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_ilvr_w(simdArg0->reg.v4i32, simdArg1->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ilvr_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaIlvrD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (args[1].type != NumericConstant::Object || !args[1].value.objectVal || !(args[1].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg1 = static_cast<SimdObject*>(args[1].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg1->regType != Simd_v2i64) { return Result{}; }

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_ilvr_d(simdArg0->reg.v2i64, simdArg1->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_insert_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaInsertB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }
			if (!args[2].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v16i8) { return Result{}; }

			int64_t lane = context->convertResult(args[1], NumericConstant::Signed).value.intVal;
			int64_t val = context->convertResult(args[2], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_insert_b(simdArg0->reg.v16i8, static_cast<int>(lane), static_cast<int8_t>(val));
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_insert_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaInsertH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }
			if (!args[2].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v8i16) { return Result{}; }

			int64_t lane = context->convertResult(args[1], NumericConstant::Signed).value.intVal;
			int64_t val = context->convertResult(args[2], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_insert_h(simdArg0->reg.v8i16, static_cast<int>(lane), static_cast<int16_t>(val));
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_insert_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaInsertW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }
			if (!args[2].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v4i32) { return Result{}; }

			int64_t lane = context->convertResult(args[1], NumericConstant::Signed).value.intVal;
			int64_t val = context->convertResult(args[2], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_insert_w(simdArg0->reg.v4i32, static_cast<int>(lane), static_cast<int32_t>(val));
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_insert_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaInsertD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }
			if (!args[2].isPrimitive()) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			if (simdArg0->regType != Simd_v2i64) { return Result{}; }

			int64_t lane = context->convertResult(args[1], NumericConstant::Signed).value.intVal;
			int64_t val = context->convertResult(args[2], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_insert_d(simdArg0->reg.v2i64, static_cast<int>(lane), static_cast<int64_t>(val));
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_insve_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaInsveB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v16i8 || simdArg2->regType != Simd_v16i8) { return Result{}; }

			int64_t lane = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_insve_b(simdArg0->reg.v16i8, static_cast<int>(lane), simdArg2->reg.v16i8);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_insve_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaInsveH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v8i16 || simdArg2->regType != Simd_v8i16) { return Result{}; }

			int64_t lane = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_insve_h(simdArg0->reg.v8i16, static_cast<int>(lane), simdArg2->reg.v8i16);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_insve_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaInsveW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v4i32 || simdArg2->regType != Simd_v4i32) { return Result{}; }

			int64_t lane = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_insve_w(simdArg0->reg.v4i32, static_cast<int>(lane), simdArg2->reg.v4i32);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_insve_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaInsveD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 3) { return Result{}; }
			if (args[0].type != NumericConstant::Object || !args[0].value.objectVal || !(args[0].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }
			if (args[2].type != NumericConstant::Object || !args[2].value.objectVal || !(args[2].value.objectVal->type() & BuiltInType_Simd)) { return Result{}; }

			SimdObject* simdArg0 = static_cast<SimdObject*>(args[0].value.objectVal);
			SimdObject* simdArg2 = static_cast<SimdObject*>(args[2].value.objectVal);

			if (simdArg0->regType != Simd_v2i64 || simdArg2->regType != Simd_v2i64) { return Result{}; }

			int64_t lane = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_insve_d(simdArg0->reg.v2i64, static_cast<int>(lane), simdArg2->reg.v2i64);
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ld_b.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaLdB(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (!args[0].isPrimitive()) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			const void* ptr = reinterpret_cast<const void*>(context->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			int64_t offset = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v16i8;
			outObj->reg.v16i8 = simde_msa_ld_b(ptr, static_cast<int>(offset));
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ld_h.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaLdH(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (!args[0].isPrimitive()) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			const void* ptr = reinterpret_cast<const void*>(context->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			int64_t offset = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v8i16;
			outObj->reg.v8i16 = simde_msa_ld_h(ptr, static_cast<int>(offset));
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ld_w.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaLdW(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (!args[0].isPrimitive()) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			const void* ptr = reinterpret_cast<const void*>(context->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			int64_t offset = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v4i32;
			outObj->reg.v4i32 = simde_msa_ld_w(ptr, static_cast<int>(offset));
			return outObj->createResult();
		}

		/**
		 * Bridge for simde_msa_ld_d.
		 *
		 * \param context		The execution context containing variables and runtime states.
		 * \param args			The list of arguments passed to the intrinsic.
		 * \return				Returns the result of the intrinsic, or an invalid Result on failure.
		 **/
		static Result		bridgeMsaLdD(ExecutionContext* context, const std::vector<Result>& args) {
			if (args.size() != 2) { return Result{}; }
			if (!args[0].isPrimitive()) { return Result{}; }
			if (!args[1].isPrimitive()) { return Result{}; }

			const void* ptr = reinterpret_cast<const void*>(context->convertResult(args[0], NumericConstant::Unsigned).value.uintVal);
			int64_t offset = context->convertResult(args[1], NumericConstant::Signed).value.intVal;

			SimdObject* outObj = context->allocateObject<SimdObject>();
			if (!outObj) { return Result{}; }

			outObj->regType = Simd_v2i64;
			outObj->reg.v2i64 = simde_msa_ld_d(ptr, static_cast<int>(offset));
			return outObj->createResult();
		}
	};

}	// namespace ve
