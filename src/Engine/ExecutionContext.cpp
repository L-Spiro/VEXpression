#include "../../generated/ExprLexer.h"
#include "../../generated/ExprParser.h"
#include "../Compiler/AstBuilderVisitor.h"
#include "../Strings/Strings.h"
#include "BFloat16.h"
#include "ExecutionContext.h"
#include "Float16.h"
#include "IntrinsicBridges.h"
#include "SimdBridges.h"

#include "antlr4-runtime.h"
#include "atn/ParserATNSimulator.h"
#include "BailErrorStrategy.h"

#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numbers>
//#include <stdio.h>

#ifndef LDBL_DECIMAL_DIG
#define LDBL_DECIMAL_DIG					DBL_DECIMAL_DIG
#endif	// #ifndef LDBL_DECIMAL_DIG

namespace ve {

	// == Members.
	/** A list of built-in constants. */
	ExecutionContext::BuiltInConstant ExecutionContext::builtInConsts[] = {
		// == Math Constants (<cmath>)
		{ StringId::Desc_Category_MathConstants,			"M_E",								Result::make(M_E), },
		{ StringId::Desc_Category_MathConstants,			"M_LOG2E",							Result::make(M_LOG2E), },
		{ StringId::Desc_Category_MathConstants,			"M_LOG10E",							Result::make(M_LOG10E), },
		{ StringId::Desc_Category_MathConstants,			"M_LN2",							Result::make(M_LN2), },
		{ StringId::Desc_Category_MathConstants,			"M_LN10",							Result::make(M_LN10), },
		{ StringId::Desc_Category_MathConstants,			"M_PI",								Result::make(M_PI), },
		{ StringId::Desc_Category_MathConstants,			"M_PI_2",							Result::make(M_PI_2), },
		{ StringId::Desc_Category_MathConstants,			"M_PI_4",							Result::make(M_PI_4), },
		{ StringId::Desc_Category_MathConstants,			"M_1_PI",							Result::make(M_1_PI), },
		{ StringId::Desc_Category_MathConstants,			"M_2_PI",							Result::make(M_2_PI), },
		{ StringId::Desc_Category_MathConstants,			"M_2_SQRTPI",						Result::make(M_2_SQRTPI), },
		{ StringId::Desc_Category_MathConstants,			"M_SQRT2",							Result::make(M_SQRT2), },
		{ StringId::Desc_Category_MathConstants,			"M_SQRT1_2",						Result::make(M_SQRT1_2), },

		// == Character Limits (<climits>)
		{ StringId::Desc_Category_CharacterLimits,			"CHAR_BIT",							Result::make(CHAR_BIT), },
		{ StringId::Desc_Category_CharacterLimits,			"MB_LEN_MAX",						Result::make(MB_LEN_MAX), },
		{ StringId::Desc_Category_CharacterLimits,			"CHAR_MIN",							Result::make(CHAR_MIN), },
		{ StringId::Desc_Category_CharacterLimits,			"CHAR_MAX",							Result::make(CHAR_MAX), },
		{ StringId::Desc_Category_CharacterLimits,			"SCHAR_MIN",						Result::make(SCHAR_MIN), },
		{ StringId::Desc_Category_CharacterLimits,			"SCHAR_MAX",						Result::make(SCHAR_MAX), },
		{ StringId::Desc_Category_CharacterLimits,			"UCHAR_MAX",						Result::make(UCHAR_MAX), },

		// == Standard Integer Limits (<climits>)
		{ StringId::Desc_Category_StdIntegerLimits,			"SHRT_MIN",							Result::make(SHRT_MIN), },
		{ StringId::Desc_Category_StdIntegerLimits,			"SHRT_MAX",							Result::make(SHRT_MAX), },
		{ StringId::Desc_Category_StdIntegerLimits,			"USHRT_MAX",						Result::make(USHRT_MAX), },
		{ StringId::Desc_Category_StdIntegerLimits,			"INT_MIN",							Result::make(INT_MIN), },
		{ StringId::Desc_Category_StdIntegerLimits,			"INT_MAX",							Result::make(INT_MAX), },
		{ StringId::Desc_Category_StdIntegerLimits,			"UINT_MAX",							Result::make(UINT_MAX), },
		{ StringId::Desc_Category_StdIntegerLimits,			"LONG_MIN",							Result::make(LONG_MIN), },
		{ StringId::Desc_Category_StdIntegerLimits,			"LONG_MAX",							Result::make(LONG_MAX), },
		{ StringId::Desc_Category_StdIntegerLimits,			"ULONG_MAX",						Result::make(ULONG_MAX), },
		{ StringId::Desc_Category_StdIntegerLimits,			"LLONG_MIN",						Result::make(LLONG_MIN), },
		{ StringId::Desc_Category_StdIntegerLimits,			"LLONG_MAX",						Result::make(LLONG_MAX), },
		{ StringId::Desc_Category_StdIntegerLimits,			"ULLONG_MAX",						Result::make(ULLONG_MAX), },

		// == Fixed-Width Integer Limits (<cstdint>)
		{ StringId::Desc_Category_FixedWidthLimits,			"INT8_MIN",							Result::make(INT8_MIN), },
		{ StringId::Desc_Category_FixedWidthLimits,			"INT8_MAX",							Result::make(INT8_MAX), },
		{ StringId::Desc_Category_FixedWidthLimits,			"UINT8_MAX",						Result::make(UINT8_MAX), },
		{ StringId::Desc_Category_FixedWidthLimits,			"INT16_MIN",						Result::make(INT16_MIN), },
		{ StringId::Desc_Category_FixedWidthLimits,			"INT16_MAX",						Result::make(INT16_MAX), },
		{ StringId::Desc_Category_FixedWidthLimits,			"UINT16_MAX",						Result::make(UINT16_MAX), },
		{ StringId::Desc_Category_FixedWidthLimits,			"INT32_MIN",						Result::make(INT32_MIN), },
		{ StringId::Desc_Category_FixedWidthLimits,			"INT32_MAX",						Result::make(INT32_MAX), },
		{ StringId::Desc_Category_FixedWidthLimits,			"UINT32_MAX",						Result::make(UINT32_MAX), },
		{ StringId::Desc_Category_FixedWidthLimits,			"INT64_MIN",						Result::make(INT64_MIN), },
		{ StringId::Desc_Category_FixedWidthLimits,			"INT64_MAX",						Result::make(INT64_MAX), },
		{ StringId::Desc_Category_FixedWidthLimits,			"UINT64_MAX",						Result::make(UINT64_MAX), },

		// == Floating-Point Characteristics & Limits (<cfloat>)
		{ StringId::Desc_Category_FloatLimits,				"FLT_RADIX",						Result::make(FLT_RADIX), },
		{ StringId::Desc_Category_FloatLimits,				"DECIMAL_DIG",						Result::make(DECIMAL_DIG), },
		{ StringId::Desc_Category_FloatLimits,				"FLT_DECIMAL_DIG",					Result::make(FLT_DECIMAL_DIG), },
		{ StringId::Desc_Category_FloatLimits,				"DBL_DECIMAL_DIG",					Result::make(DBL_DECIMAL_DIG), },
		{ StringId::Desc_Category_FloatLimits,				"LDBL_DECIMAL_DIG",					Result::make(LDBL_DECIMAL_DIG), },
		{ StringId::Desc_Category_FloatLimits,				"FLT_MIN",							Result::make(FLT_MIN), },
		{ StringId::Desc_Category_FloatLimits,				"DBL_MIN",							Result::make(DBL_MIN), },
		{ StringId::Desc_Category_FloatLimits,				"LDBL_MIN",							Result::make(LDBL_MIN), },
		{ StringId::Desc_Category_FloatLimits,				"FLT_TRUE_MIN",						Result::make(FLT_TRUE_MIN), },
		{ StringId::Desc_Category_FloatLimits,				"DBL_TRUE_MIN",						Result::make(DBL_TRUE_MIN), },
		{ StringId::Desc_Category_FloatLimits,				"LDBL_TRUE_MIN",					Result::make(LDBL_TRUE_MIN), },
		{ StringId::Desc_Category_FloatLimits,				"FLT_MAX",							Result::make(FLT_MAX), },
		{ StringId::Desc_Category_FloatLimits,				"DBL_MAX",							Result::make(DBL_MAX), },
		{ StringId::Desc_Category_FloatLimits,				"LDBL_MAX",							Result::make(LDBL_MAX), },
		{ StringId::Desc_Category_FloatLimits,				"FLT_EPSILON",						Result::make(FLT_EPSILON), },
		{ StringId::Desc_Category_FloatLimits,				"DBL_EPSILON",						Result::make(DBL_EPSILON), },
		{ StringId::Desc_Category_FloatLimits,				"LDBL_EPSILON",						Result::make(LDBL_EPSILON), },
		{ StringId::Desc_Category_FloatLimits,				"FLT_DIG",							Result::make(FLT_DIG), },
		{ StringId::Desc_Category_FloatLimits,				"DBL_DIG",							Result::make(DBL_DIG), },
		{ StringId::Desc_Category_FloatLimits,				"LDBL_DIG",							Result::make(LDBL_DIG), },
		{ StringId::Desc_Category_FloatLimits,				"FLT_MANT_DIG",						Result::make(FLT_MANT_DIG), },
		{ StringId::Desc_Category_FloatLimits,				"DBL_MANT_DIG",						Result::make(DBL_MANT_DIG), },
		{ StringId::Desc_Category_FloatLimits,				"LDBL_MANT_DIG",					Result::make(LDBL_MANT_DIG), },
		{ StringId::Desc_Category_FloatLimits,				"FLT_MIN_EXP",						Result::make(FLT_MIN_EXP), },
		{ StringId::Desc_Category_FloatLimits,				"DBL_MIN_EXP",						Result::make(DBL_MIN_EXP), },
		{ StringId::Desc_Category_FloatLimits,				"LDBL_MIN_EXP",						Result::make(LDBL_MIN_EXP), },
		{ StringId::Desc_Category_FloatLimits,				"FLT_MIN_10_EXP",					Result::make(FLT_MIN_10_EXP), },
		{ StringId::Desc_Category_FloatLimits,				"DBL_MIN_10_EXP",					Result::make(DBL_MIN_10_EXP), },
		{ StringId::Desc_Category_FloatLimits,				"LDBL_MIN_10_EXP",					Result::make(LDBL_MIN_10_EXP), },
		{ StringId::Desc_Category_FloatLimits,				"FLT_MAX_EXP",						Result::make(FLT_MAX_EXP), },
		{ StringId::Desc_Category_FloatLimits,				"DBL_MAX_EXP",						Result::make(DBL_MAX_EXP), },
		{ StringId::Desc_Category_FloatLimits,				"LDBL_MAX_EXP",						Result::make(LDBL_MAX_EXP), },
		{ StringId::Desc_Category_FloatLimits,				"FLT_MAX_10_EXP",					Result::make(FLT_MAX_10_EXP), },
		{ StringId::Desc_Category_FloatLimits,				"DBL_MAX_10_EXP",					Result::make(DBL_MAX_10_EXP), },
		{ StringId::Desc_Category_FloatLimits,				"LDBL_MAX_10_EXP",					Result::make(LDBL_MAX_10_EXP), },

		// == Time (<ctime>)
		{ StringId::Desc_Category_Time,						"CLOCKS_PER_SEC",					Result::make(CLOCKS_PER_SEC), },

		// == Floating-Point Specials (<cmath>)
		{ StringId::Desc_Category_FloatSpecials,			"INFINITY",							Result::make(INFINITY), },
		{ StringId::Desc_Category_FloatSpecials,			"NAN",								Result::make(NAN), },
		{ StringId::Desc_Category_FloatSpecials,			"HUGE_VAL",							Result::make(HUGE_VAL), },
		{ StringId::Desc_Category_FloatSpecials,			"HUGE_VALF",						Result::make(HUGE_VALF), },
		{ StringId::Desc_Category_FloatSpecials,			"HUGE_VALL",						Result::make(HUGE_VALL), },

		// == Maximum-Width Integer Limits (<cstdint>)
		{ StringId::Desc_Category_MaxWidthLimits,			"INTMAX_MIN",						Result::make(INTMAX_MIN), },
		{ StringId::Desc_Category_MaxWidthLimits,			"INTMAX_MAX",						Result::make(INTMAX_MAX), },
		{ StringId::Desc_Category_MaxWidthLimits,			"UINTMAX_MAX",						Result::make(UINTMAX_MAX), },

		// == Pointer & Size Limits (<cstdint>)
		{ StringId::Desc_Category_PointerSizeLimits,		"INTPTR_MIN",						Result::make(INTPTR_MIN), },
		{ StringId::Desc_Category_PointerSizeLimits,		"INTPTR_MAX",						Result::make(INTPTR_MAX), },
		{ StringId::Desc_Category_PointerSizeLimits,		"UINTPTR_MAX",						Result::make(UINTPTR_MAX), },
		{ StringId::Desc_Category_PointerSizeLimits,		"PTRDIFF_MIN",						Result::make(PTRDIFF_MIN), },
		{ StringId::Desc_Category_PointerSizeLimits,		"PTRDIFF_MAX",						Result::make(PTRDIFF_MAX), },
		{ StringId::Desc_Category_PointerSizeLimits,		"SIZE_MAX",							Result::make(SIZE_MAX), },

		// == Wide Character & Atomic Limits (<cstdint>)
		{ StringId::Desc_Category_WideCharAtomicLimits,		"SIG_ATOMIC_MIN",					Result::make(SIG_ATOMIC_MIN), },
		{ StringId::Desc_Category_WideCharAtomicLimits,		"SIG_ATOMIC_MAX",					Result::make(SIG_ATOMIC_MAX), },
		{ StringId::Desc_Category_WideCharAtomicLimits,		"WCHAR_MIN",						Result::make(WCHAR_MIN), },
		{ StringId::Desc_Category_WideCharAtomicLimits,		"WCHAR_MAX",						Result::make(WCHAR_MAX), },
		{ StringId::Desc_Category_WideCharAtomicLimits,		"WINT_MIN",							Result::make(WINT_MIN), },
		{ StringId::Desc_Category_WideCharAtomicLimits,		"WINT_MAX",							Result::make(WINT_MAX), },

		// == Common C-Library Constants (<cstdlib> / <cstdio>)
		{ StringId::Desc_Category_CommonCLibrary,			"RAND_MAX",							Result::make(RAND_MAX), },
		//{ "EOF",							Result::make(EOF), },

		// == Custom
		{ StringId::Desc_Category_SciMathConstants,			"_PI_",								Result::make(3.1415926535897932384626433832795), },
		{ StringId::Desc_Category_SciMathConstants,			"_HALFPI_",							Result::make(1.5707963267948966192313216916398), },
		{ StringId::Desc_Category_SciMathConstants,			"_E_",								Result::make(2.7182818284590452353602874713527), },
		{ StringId::Desc_Category_SciMathConstants,			"_ZETA_",							Result::make(1.202056903159594285399738161511449990764986292), },
		{ StringId::Desc_Category_SciMathConstants,			"_GR_",								Result::make(1.6180339887498948482045868343656381177203091798057628621), },
		{ StringId::Desc_Category_SciMathConstants,			"_GOLDENRATIO_",					Result::make(1.6180339887498948482045868343656381177203091798057628621), },
		{ StringId::Desc_Category_SciMathConstants,			"_GOLDENR_",						Result::make(1.6180339887498948482045868343656381177203091798057628621), },
		{ StringId::Desc_Category_SciMathConstants,			"_GOLDENRAT_",						Result::make(1.6180339887498948482045868343656381177203091798057628621), },
		{ StringId::Desc_Category_SciMathConstants,			"_GRATIO_",							Result::make(1.6180339887498948482045868343656381177203091798057628621), },
		{ StringId::Desc_Category_SciMathConstants,			"_EULER_",							Result::make(0.5772156649015328606065120900824024310421), },
		{ StringId::Desc_Category_SciMathConstants,			"_EULERMASCHERONI_",				Result::make(0.5772156649015328606065120900824024310421), },
		{ StringId::Desc_Category_SciMathConstants,			"_MASCHERONI_",						Result::make(0.5772156649015328606065120900824024310421), },
		{ StringId::Desc_Category_SciMathConstants,			"_EM_",								Result::make(0.5772156649015328606065120900824024310421), },
		{ StringId::Desc_Category_SciMathConstants,			"_K_",								Result::make(2.685452001065306445309714835481795693820382293994462953051152345557218), },
		{ StringId::Desc_Category_SciMathConstants,			"_KHINCHIN_",						Result::make(2.685452001065306445309714835481795693820382293994462953051152345557218), },
		{ StringId::Desc_Category_SciMathConstants,			"_A_",								Result::make(1.2824271291006226368753425688697917277676889273250011920637400217404), },
		{ StringId::Desc_Category_SciMathConstants,			"_GLAISHER_",						Result::make(1.2824271291006226368753425688697917277676889273250011920637400217404), },
		{ StringId::Desc_Category_SciMathConstants,			"_GLAISHERKINKELIN_",				Result::make(1.2824271291006226368753425688697917277676889273250011920637400217404), },
		{ StringId::Desc_Category_SciMathConstants,			"_KINKELIN_",						Result::make(1.2824271291006226368753425688697917277676889273250011920637400217404), },
		{ StringId::Desc_Category_SciMathConstants,			"_M1_",								Result::make(0.26149721284764278375542683860869585), },
		{ StringId::Desc_Category_SciMathConstants,			"_MEISSEL_",						Result::make(0.26149721284764278375542683860869585), },
		{ StringId::Desc_Category_SciMathConstants,			"_MEISSELMERTENS_",					Result::make(0.26149721284764278375542683860869585), },
		{ StringId::Desc_Category_SciMathConstants,			"_MERTENS_",						Result::make(0.26149721284764278375542683860869585), },
		{ StringId::Desc_Category_SciMathConstants,			"_B_",								Result::make(0.28016949902386913303), },
		{ StringId::Desc_Category_SciMathConstants,			"_BERNSTEIN_",						Result::make(0.28016949902386913303), },
		{ StringId::Desc_Category_SciMathConstants,			"_LAMDA_",							Result::make(0.30366300289873265859744812190155623), },
		{ StringId::Desc_Category_SciMathConstants,			"_LAMBDA_",							Result::make(0.30366300289873265859744812190155623), },
		{ StringId::Desc_Category_SciMathConstants,			"_GWK_",							Result::make(0.30366300289873265859744812190155623), },
		{ StringId::Desc_Category_SciMathConstants,			"_GAUSS_",							Result::make(0.30366300289873265859744812190155623), },
		{ StringId::Desc_Category_SciMathConstants,			"_KUZMIN_",							Result::make(0.30366300289873265859744812190155623), },
		{ StringId::Desc_Category_SciMathConstants,			"_WIRSING_",						Result::make(0.30366300289873265859744812190155623), },
		{ StringId::Desc_Category_SciMathConstants,			"_GAUSSKUZMINWIRSING_",				Result::make(0.30366300289873265859744812190155623), },
		{ StringId::Desc_Category_SciMathConstants,			"_SIGMA_",							Result::make(0.35323637185499598454351655043268201), },
		{ StringId::Desc_Category_SciMathConstants,			"_HSMC_",							Result::make(0.35323637185499598454351655043268201), },
		{ StringId::Desc_Category_SciMathConstants,			"_HSM_",							Result::make(0.35323637185499598454351655043268201), },
		{ StringId::Desc_Category_SciMathConstants,			"_HAFNER_",							Result::make(0.35323637185499598454351655043268201), },
		{ StringId::Desc_Category_SciMathConstants,			"_SARNAK_",							Result::make(0.35323637185499598454351655043268201), },
		{ StringId::Desc_Category_SciMathConstants,			"_MCCURLEY_",						Result::make(0.35323637185499598454351655043268201), },
		{ StringId::Desc_Category_SciMathConstants,			"_HAFNERSARNAKMCCURLEY_",			Result::make(0.35323637185499598454351655043268201), },
		{ StringId::Desc_Category_SciMathConstants,			"_OMEGA_",							Result::make(0.56714329040978387299996866221035554), },
		{ StringId::Desc_Category_SciMathConstants,			"_MU_",								Result::make(0.62432998854355087099293638310083724), },
		{ StringId::Desc_Category_SciMathConstants,			"_GOLOMB_",							Result::make(0.62432998854355087099293638310083724), },
		{ StringId::Desc_Category_SciMathConstants,			"_DICKMAN_",						Result::make(0.62432998854355087099293638310083724), },
		{ StringId::Desc_Category_SciMathConstants,			"_GOLOMBDICKMAN_",					Result::make(0.62432998854355087099293638310083724), },
		{ StringId::Desc_Category_SciMathConstants,			"_GD_",								Result::make(0.62432998854355087099293638310083724), },
		{ StringId::Desc_Category_SciMathConstants,			"_CAHEN_",							Result::make(0.6434105462), },
		{ StringId::Desc_Category_SciMathConstants,			"_C2_",								Result::make(0.66016181584686957392781211001455577), },
		{ StringId::Desc_Category_SciMathConstants,			"_TWINPRIME_",						Result::make(0.66016181584686957392781211001455577), },
		{ StringId::Desc_Category_SciMathConstants,			"_TP_",								Result::make(0.66016181584686957392781211001455577), },
		{ StringId::Desc_Category_SciMathConstants,			"_LAPLACE_",						Result::make(0.66274341934918158097474209710925290), },
		{ StringId::Desc_Category_SciMathConstants,			"_BETA_",							Result::make(0.70258), },
		{ StringId::Desc_Category_SciMathConstants,			"_EMBREE_",							Result::make(0.70258), },
		{ StringId::Desc_Category_SciMathConstants,			"_TREFETHEN_",						Result::make(0.70258), },
		{ StringId::Desc_Category_SciMathConstants,			"_EMBREETREFETHEN_",				Result::make(0.70258), },
		{ StringId::Desc_Category_SciMathConstants,			"_LANDAU_",							Result::make(0.76422365358922066299069873125009232), },
		{ StringId::Desc_Category_SciMathConstants,			"_LANDAURAMANUJAN_",				Result::make(0.76422365358922066299069873125009232), },
		{ StringId::Desc_Category_SciMathConstants,			"_ALLADI_",							Result::make(0.8093940205), },
		{ StringId::Desc_Category_SciMathConstants,			"_GRINSTEAD_",						Result::make(0.8093940205), },
		{ StringId::Desc_Category_SciMathConstants,			"_ALLADIGRINSTEAD_",				Result::make(0.8093940205), },
		{ StringId::Desc_Category_SciMathConstants,			"_B4_",								Result::make(0.87058838), },
		{ StringId::Desc_Category_SciMathConstants,			"_BRUN_",							Result::make(0.87058838), },
		{ StringId::Desc_Category_SciMathConstants,			"_BRUNPRIMEQUADRUPLETS_",			Result::make(0.87058838), },
		{ StringId::Desc_Category_SciMathConstants,			"_BRUNPQ_",							Result::make(0.87058838), },
		{ StringId::Desc_Category_SciMathConstants,			"_BRUNPRIMEQUAD_",					Result::make(0.87058838), },
		{ StringId::Desc_Category_SciMathConstants,			"_BRUNPRIMEQ_",						Result::make(0.87058838), },
		{ StringId::Desc_Category_SciMathConstants,			"_CATALAN_",						Result::make(0.91596559417721901505460351493238411), },
		{ StringId::Desc_Category_SciMathConstants,			"_LENGYEL_",						Result::make(1.0986858055), },
		{ StringId::Desc_Category_SciMathConstants,			"_LENG_",							Result::make(1.0986858055), },
		{ StringId::Desc_Category_SciMathConstants,			"_VISWANATH_",						Result::make(1.13198824), },
		{ StringId::Desc_Category_SciMathConstants,			"_VISWAN_",							Result::make(1.13198824), },
		{ StringId::Desc_Category_SciMathConstants,			"_VIS_",							Result::make(1.13198824), },
		{ StringId::Desc_Category_SciMathConstants,			"_ZETA3_",							Result::make(1.20205690315959428539973816151144999), },
		{ StringId::Desc_Category_SciMathConstants,			"_APERY_",							Result::make(1.20205690315959428539973816151144999), },
		{ StringId::Desc_Category_SciMathConstants,			"_CONWAY_",							Result::make(1.30357726903429639125709911215255189), },
		{ StringId::Desc_Category_SciMathConstants,			"_THETA_",							Result::make(1.30637788386308069046861449260260571), },
		{ StringId::Desc_Category_SciMathConstants,			"_MILL_",							Result::make(1.30637788386308069046861449260260571), },
		{ StringId::Desc_Category_SciMathConstants,			"_RHO_",							Result::make(1.32471795724474602596090885447809734), },
		{ StringId::Desc_Category_SciMathConstants,			"_PLASTIC_",						Result::make(1.32471795724474602596090885447809734), },
		{ StringId::Desc_Category_SciMathConstants,			"_RAMANUJAN_",						Result::make(1.45136923488338105028396848589202744), },
		{ StringId::Desc_Category_SciMathConstants,			"_RAMAN_",							Result::make(1.45136923488338105028396848589202744), },
		{ StringId::Desc_Category_SciMathConstants,			"_RAMAMU_",							Result::make(1.45136923488338105028396848589202744), },
		{ StringId::Desc_Category_SciMathConstants,			"_SOLDNER_",						Result::make(1.45136923488338105028396848589202744), },
		{ StringId::Desc_Category_SciMathConstants,			"_RAMANUJANSOLDNER_",				Result::make(1.45136923488338105028396848589202744), },
		{ StringId::Desc_Category_SciMathConstants,			"_RS_",								Result::make(1.45136923488338105028396848589202744), },
		{ StringId::Desc_Category_SciMathConstants,			"_RAMASOLDNER_",					Result::make(1.45136923488338105028396848589202744), },
		{ StringId::Desc_Category_SciMathConstants,			"_RAMASOL_",						Result::make(1.45136923488338105028396848589202744), },
		{ StringId::Desc_Category_SciMathConstants,			"_BLACKHOUSE_",						Result::make(1.45607494858268967139959535111654356), },
		{ StringId::Desc_Category_SciMathConstants,			"_BH_",								Result::make(1.45607494858268967139959535111654356), },
		{ StringId::Desc_Category_SciMathConstants,			"_PORTER_",							Result::make(1.4670780794), },
		{ StringId::Desc_Category_SciMathConstants,			"_LIEB_",							Result::make(1.5396007178), },
		{ StringId::Desc_Category_SciMathConstants,			"_SQUAREICE_",						Result::make(1.5396007178), },
		{ StringId::Desc_Category_SciMathConstants,			"_SQICE_",							Result::make(1.5396007178), },
		{ StringId::Desc_Category_SciMathConstants,			"_EB_",								Result::make(1.60669515241529176378330152319092458), },
		{ StringId::Desc_Category_SciMathConstants,			"_ERDOS_",							Result::make(1.60669515241529176378330152319092458), },
		{ StringId::Desc_Category_SciMathConstants,			"_BORWEIN_",						Result::make(1.60669515241529176378330152319092458), },
		{ StringId::Desc_Category_SciMathConstants,			"_ERDOSBORWEIN_",					Result::make(1.60669515241529176378330152319092458), },
		{ StringId::Desc_Category_SciMathConstants,			"_NIVEN_",							Result::make(1.70521114010536776428855145343450816), },
		{ StringId::Desc_Category_SciMathConstants,			"_NIV_",							Result::make(1.70521114010536776428855145343450816), },
		{ StringId::Desc_Category_SciMathConstants,			"_B2_",								Result::make(1.902160583104), },
		{ StringId::Desc_Category_SciMathConstants,			"_BRUN2_",							Result::make(1.902160583104), },
		{ StringId::Desc_Category_SciMathConstants,			"_BRUNTWINPRIME_",					Result::make(1.902160583104), },
		{ StringId::Desc_Category_SciMathConstants,			"_BRUNTP_",							Result::make(1.902160583104), },
		{ StringId::Desc_Category_SciMathConstants,			"_P2_",								Result::make(2.29558714939263807403429804918949039), },
		{ StringId::Desc_Category_SciMathConstants,			"_PARABOLIC_",						Result::make(2.29558714939263807403429804918949039), },
		{ StringId::Desc_Category_SciMathConstants,			"_ALPHA_",							Result::make(2.50290787509589282228390287321821578), },
		{ StringId::Desc_Category_SciMathConstants,			"_FEIGENBAUM_",						Result::make(2.50290787509589282228390287321821578), },
		{ StringId::Desc_Category_SciMathConstants,			"_FEIGENBAUMA_",					Result::make(2.50290787509589282228390287321821578), },
		{ StringId::Desc_Category_SciMathConstants,			"_SIERP_",							Result::make(2.58498175957925321706589358738317116), },
		{ StringId::Desc_Category_SciMathConstants,			"_SIERPINSKI_",						Result::make(2.58498175957925321706589358738317116), },
		{ StringId::Desc_Category_SciMathConstants,			"_F_",								Result::make(2.80777024202851936522150118655777293), },
		{ StringId::Desc_Category_SciMathConstants,			"_FRANSEN_",						Result::make(2.80777024202851936522150118655777293), },
		{ StringId::Desc_Category_SciMathConstants,			"_ROBINSON_",						Result::make(2.80777024202851936522150118655777293), },
		{ StringId::Desc_Category_SciMathConstants,			"_FRANSENROBINSON_",				Result::make(2.80777024202851936522150118655777293), },
		{ StringId::Desc_Category_SciMathConstants,			"_LEVY_",							Result::make(3.27582291872181115978768188245384386), },
		{ StringId::Desc_Category_SciMathConstants,			"_PSI_",							Result::make(3.35988566624317755317201130291892717), },
		{ StringId::Desc_Category_SciMathConstants,			"_RECIPROCALFIBONACCI_",			Result::make(3.35988566624317755317201130291892717), },
		{ StringId::Desc_Category_SciMathConstants,			"_RECIPFIBONACCI_",					Result::make(3.35988566624317755317201130291892717), },
		{ StringId::Desc_Category_SciMathConstants,			"_RFIBONACCI_",						Result::make(3.35988566624317755317201130291892717), },
		{ StringId::Desc_Category_SciMathConstants,			"_RF_",								Result::make(3.35988566624317755317201130291892717), },
		{ StringId::Desc_Category_SciMathConstants,			"_DELTA_",							Result::make(4.66920160910299067185320382046620161), },
		{ StringId::Desc_Category_SciMathConstants,			"_FEIGENBAUMD_",					Result::make(4.66920160910299067185320382046620161), },

		// == SIMD.
		{ StringId::Desc_Category_SIMD,						"_MM_HINT_NTA",						Result::make(SIMDE_MM_HINT_NTA), },
		{ StringId::Desc_Category_SIMD,						"_MM_HINT_T0",						Result::make(SIMDE_MM_HINT_T0), },
		{ StringId::Desc_Category_SIMD,						"_MM_HINT_T1",						Result::make(SIMDE_MM_HINT_T1), },
		{ StringId::Desc_Category_SIMD,						"_MM_HINT_T2",						Result::make(SIMDE_MM_HINT_T2), },
		{ StringId::Desc_Category_SIMD,						"_MM_HINT_ENTA",					Result::make(SIMDE_MM_HINT_ENTA), },

		{ StringId::Desc_Category_SIMD,						"_MM_HINT_IT0",						Result::make(7), },
		{ StringId::Desc_Category_SIMD,						"_MM_HINT_IT1",						Result::make(6), },
		{ StringId::Desc_Category_SIMD,						"_MM_EXCEPT_MASK",					Result::make(SIMDE_MM_EXCEPT_MASK), },
		{ StringId::Desc_Category_SIMD,						"_MM_EXCEPT_INVALID",				Result::make(SIMDE_MM_EXCEPT_INVALID), },
		{ StringId::Desc_Category_SIMD,						"_MM_EXCEPT_DENORM",				Result::make(SIMDE_MM_EXCEPT_DENORM), },
		{ StringId::Desc_Category_SIMD,						"_MM_EXCEPT_DIV_ZERO",				Result::make(SIMDE_MM_EXCEPT_DIV_ZERO), },
		{ StringId::Desc_Category_SIMD,						"_MM_EXCEPT_OVERFLOW",				Result::make(SIMDE_MM_EXCEPT_OVERFLOW), },
		{ StringId::Desc_Category_SIMD,						"_MM_EXCEPT_UNDERFLOW",				Result::make(SIMDE_MM_EXCEPT_UNDERFLOW), },
		{ StringId::Desc_Category_SIMD,						"_MM_EXCEPT_INEXACT",				Result::make(SIMDE_MM_EXCEPT_INEXACT), },

		{ StringId::Desc_Category_SIMD,						"_MM_MASK_MASK",					Result::make(SIMDE_MM_MASK_MASK), },
		{ StringId::Desc_Category_SIMD,						"_MM_MASK_INVALID",					Result::make(SIMDE_MM_MASK_INVALID), },
		{ StringId::Desc_Category_SIMD,						"_MM_MASK_DENORM",					Result::make(SIMDE_MM_MASK_DENORM), },
		{ StringId::Desc_Category_SIMD,						"_MM_MASK_DIV_ZERO",				Result::make(SIMDE_MM_MASK_DIV_ZERO), },
		{ StringId::Desc_Category_SIMD,						"_MM_MASK_OVERFLOW",				Result::make(SIMDE_MM_MASK_OVERFLOW), },
		{ StringId::Desc_Category_SIMD,						"_MM_MASK_UNDERFLOW",				Result::make(SIMDE_MM_MASK_UNDERFLOW), },
		{ StringId::Desc_Category_SIMD,						"_MM_MASK_INEXACT",					Result::make(SIMDE_MM_MASK_INEXACT), },

		{ StringId::Desc_Category_SIMD,						"_MM_ROUND_MASK",					Result::make(0x6000), },
		{ StringId::Desc_Category_SIMD,						"_MM_ROUND_NEAREST",				Result::make(SIMDE_MM_ROUND_NEAREST), },
		{ StringId::Desc_Category_SIMD,						"_MM_ROUND_DOWN",					Result::make(SIMDE_MM_ROUND_DOWN), },
		{ StringId::Desc_Category_SIMD,						"_MM_ROUND_UP",						Result::make(SIMDE_MM_ROUND_UP), },
		{ StringId::Desc_Category_SIMD,						"_MM_ROUND_TOWARD_ZERO",			Result::make(SIMDE_MM_ROUND_TOWARD_ZERO), },

		{ StringId::Desc_Category_SIMD,						"_MM_FLUSH_ZERO_MASK",				Result::make(SIMDE_MM_FLUSH_ZERO_MASK), },
		{ StringId::Desc_Category_SIMD,						"_MM_FLUSH_ZERO_ON",				Result::make(SIMDE_MM_FLUSH_ZERO_ON), },
		{ StringId::Desc_Category_SIMD,						"_MM_FLUSH_ZERO_OFF",				Result::make(SIMDE_MM_FLUSH_ZERO_OFF), },

		{ StringId::Desc_Category_SIMD,						"_MM_K0_REG8",						Result::make(0xff), },
		{ StringId::Desc_Category_SIMD,						"_MM_K0_REG16",						Result::make(0xffff), },
		{ StringId::Desc_Category_SIMD,						"_MM_K0_REG32",						Result::make(0xffffffff), },
		{ StringId::Desc_Category_SIMD,						"_MM_K0_REG64",						Result::make(0xffffffffffffffff), },

		{ StringId::Desc_Category_SIMD,						"_MM_BROADCAST32_NONE",				Result::make(0), },
		{ StringId::Desc_Category_SIMD,						"_MM_BROADCAST_16X16",				Result::make(0), },
		{ StringId::Desc_Category_SIMD,						"_MM_BROADCAST_1X16",				Result::make(1), },
		{ StringId::Desc_Category_SIMD,						"_MM_BROADCAST_4X16",				Result::make(2), },

		{ StringId::Desc_Category_SIMD,						"_MM_BROADCAST64_NONE",				Result::make(0), },
		{ StringId::Desc_Category_SIMD,						"_MM_BROADCAST_8X8",				Result::make(0), },
		{ StringId::Desc_Category_SIMD,						"_MM_BROADCAST_1X8",				Result::make(1), },
		{ StringId::Desc_Category_SIMD,						"_MM_BROADCAST_4X8",				Result::make(2), },

		{ StringId::Desc_Category_SIMD,						"_MM_ROUND_MODE_NEAREST",			Result::make(0), },
		{ StringId::Desc_Category_SIMD,						"_MM_ROUND_MODE_DOWN",				Result::make(1), },
		{ StringId::Desc_Category_SIMD,						"_MM_ROUND_MODE_UP",				Result::make(2), },
		{ StringId::Desc_Category_SIMD,						"_MM_ROUND_MODE_TOWARD_ZERO",		Result::make(3), },
		{ StringId::Desc_Category_SIMD,						"_MM_ROUND_MODE_DEFAULT",			Result::make(4), },
		{ StringId::Desc_Category_SIMD,						"_MM_ROUND_MODE_NO_EXC",			Result::make(8), },

		{ StringId::Desc_Category_SIMD,						"_MM_EXPADJ_NONE",					Result::make(0), },
		{ StringId::Desc_Category_SIMD,						"_MM_EXPADJ_4",						Result::make(1), },
		{ StringId::Desc_Category_SIMD,						"_MM_EXPADJ_5",						Result::make(2), },
		{ StringId::Desc_Category_SIMD,						"_MM_EXPADJ_8",						Result::make(3), },
		{ StringId::Desc_Category_SIMD,						"_MM_EXPADJ_16",					Result::make(4), },
		{ StringId::Desc_Category_SIMD,						"_MM_EXPADJ_24",					Result::make(5), },
		{ StringId::Desc_Category_SIMD,						"_MM_EXPADJ_31",					Result::make(6), },
		{ StringId::Desc_Category_SIMD,						"_MM_EXPADJ_32",					Result::make(7), },

		{ StringId::Desc_Category_SIMD,						"_MM_SCALE_1",						Result::make(1), },
		{ StringId::Desc_Category_SIMD,						"_MM_SCALE_2",						Result::make(2), },
		{ StringId::Desc_Category_SIMD,						"_MM_SCALE_4",						Result::make(4), },
		{ StringId::Desc_Category_SIMD,						"_MM_SCALE_8",						Result::make(8), },

		{ StringId::Desc_Category_SIMD,						"_MM_FIXUP_NO_CHANGE",				Result::make(0), },
		{ StringId::Desc_Category_SIMD,						"_MM_FIXUP_NEG_INF",				Result::make(1), },
		{ StringId::Desc_Category_SIMD,						"_MM_FIXUP_NEG_ZERO",				Result::make(2), },
		{ StringId::Desc_Category_SIMD,						"_MM_FIXUP_POS_ZERO",				Result::make(3), },
		{ StringId::Desc_Category_SIMD,						"_MM_FIXUP_POS_INF",				Result::make(4), },
		{ StringId::Desc_Category_SIMD,						"_MM_FIXUP_NAN",					Result::make(5), },
		{ StringId::Desc_Category_SIMD,						"_MM_FIXUP_MAX_FLOAT",				Result::make(6), },
		{ StringId::Desc_Category_SIMD,						"_MM_FIXUP_MIN_FLOAT",				Result::make(7), },

		{ StringId::Desc_Category_SIMD,						"_MM_MANT_NORM_1_2",				Result::make(0), },
		{ StringId::Desc_Category_SIMD,						"_MM_MANT_NORM_p5_2",				Result::make(1), },
		{ StringId::Desc_Category_SIMD,						"_MM_MANT_NORM_p5_1",				Result::make(2), },
		{ StringId::Desc_Category_SIMD,						"_MM_MANT_NORM_p75_1p5",			Result::make(3), },

		{ StringId::Desc_Category_SIMD,						"_MM_MANT_SIGN_src",				Result::make(0), },
		{ StringId::Desc_Category_SIMD,						"_MM_MANT_SIGN_zero",				Result::make(1), },
		{ StringId::Desc_Category_SIMD,						"_MM_MANT_SIGN_nan",				Result::make(2), },

		{ StringId::Desc_Category_SIMD,						"_MM_CMPINT_EQ",					Result::make(SIMDE_MM_CMPINT_EQ), },
		{ StringId::Desc_Category_SIMD,						"_MM_CMPINT_LT",					Result::make(SIMDE_MM_CMPINT_LT), },
		{ StringId::Desc_Category_SIMD,						"_MM_CMPINT_LE",					Result::make(SIMDE_MM_CMPINT_LE), },
		{ StringId::Desc_Category_SIMD,						"_MM_CMPINT_UNUSED",				Result::make(SIMDE_MM_CMPINT_FALSE), },
		{ StringId::Desc_Category_SIMD,						"_MM_CMPINT_NE",					Result::make(SIMDE_MM_CMPINT_NE), },
		{ StringId::Desc_Category_SIMD,						"_MM_CMPINT_NLT",					Result::make(SIMDE_MM_CMPINT_NLT), },
		{ StringId::Desc_Category_SIMD,						"_MM_CMPINT_GE",					Result::make(SIMDE_MM_CMPINT_NLT), },
		{ StringId::Desc_Category_SIMD,						"_MM_CMPINT_NLE",					Result::make(SIMDE_MM_CMPINT_NLE), },
		{ StringId::Desc_Category_SIMD,						"_MM_CMPINT_GT",					Result::make(SIMDE_MM_CMPINT_NLE), },

		{ StringId::Desc_Category_SIMD,						"_MM_FROUND_TO_NEAREST_INT",		Result::make(SIMDE_MM_FROUND_TO_NEAREST_INT), },
		{ StringId::Desc_Category_SIMD,						"_MM_FROUND_TO_NEG_INF",			Result::make(SIMDE_MM_FROUND_TO_NEG_INF), },
		{ StringId::Desc_Category_SIMD,						"_MM_FROUND_TO_POS_INF",			Result::make(SIMDE_MM_FROUND_TO_POS_INF), },
		{ StringId::Desc_Category_SIMD,						"_MM_FROUND_TO_ZERO",				Result::make(SIMDE_MM_FROUND_TO_ZERO), },
		{ StringId::Desc_Category_SIMD,						"_MM_FROUND_CUR_DIRECTION",			Result::make(SIMDE_MM_FROUND_CUR_DIRECTION), },

		{ StringId::Desc_Category_SIMD,						"_MM_FROUND_RAISE_EXC",				Result::make(SIMDE_MM_FROUND_RAISE_EXC), },
		{ StringId::Desc_Category_SIMD,						"_MM_FROUND_NO_EXC",				Result::make(SIMDE_MM_FROUND_NO_EXC), },

		{ StringId::Desc_Category_SIMD,						"_MM_FROUND_NINT",					Result::make(SIMDE_MM_FROUND_NINT), },
		{ StringId::Desc_Category_SIMD,						"_MM_FROUND_FLOOR",					Result::make(SIMDE_MM_FROUND_FLOOR), },
		{ StringId::Desc_Category_SIMD,						"_MM_FROUND_CEIL",					Result::make(SIMDE_MM_FROUND_CEIL), },
		{ StringId::Desc_Category_SIMD,						"_MM_FROUND_TRUNC",					Result::make(SIMDE_MM_FROUND_TRUNC), },
		{ StringId::Desc_Category_SIMD,						"_MM_FROUND_RINT",					Result::make(SIMDE_MM_FROUND_RINT), },
		{ StringId::Desc_Category_SIMD,						"_MM_FROUND_NEARBYINT",				Result::make(SIMDE_MM_FROUND_NEARBYINT), },
		
		{ StringId::Desc_Category_SIMD,						"_SIDD_UBYTE_OPS",					Result::make(SIMDE_SIDD_UBYTE_OPS), },
		{ StringId::Desc_Category_SIMD,						"_SIDD_UWORD_OPS",					Result::make(SIMDE_SIDD_UWORD_OPS), },
		{ StringId::Desc_Category_SIMD,						"_SIDD_SBYTE_OPS",					Result::make(SIMDE_SIDD_SBYTE_OPS), },
		{ StringId::Desc_Category_SIMD,						"_SIDD_SWORD_OPS",					Result::make(SIMDE_SIDD_SWORD_OPS), },
		
		{ StringId::Desc_Category_SIMD,						"_SIDD_CMP_EQUAL_ANY",				Result::make(SIMDE_SIDD_CMP_EQUAL_ANY), },
		{ StringId::Desc_Category_SIMD,						"_SIDD_CMP_RANGES",					Result::make(SIMDE_SIDD_CMP_RANGES), },
		{ StringId::Desc_Category_SIMD,						"_SIDD_CMP_EQUAL_EACH",				Result::make(SIMDE_SIDD_CMP_EQUAL_EACH), },
		{ StringId::Desc_Category_SIMD,						"_SIDD_CMP_EQUAL_ORDERED",			Result::make(SIMDE_SIDD_CMP_EQUAL_ORDERED), },
		
		{ StringId::Desc_Category_SIMD,						"_SIDD_POSITIVE_POLARITY",			Result::make(SIMDE_SIDD_POSITIVE_POLARITY), },
		{ StringId::Desc_Category_SIMD,						"_SIDD_NEGATIVE_POLARITY",			Result::make(SIMDE_SIDD_NEGATIVE_POLARITY), },
		{ StringId::Desc_Category_SIMD,						"_SIDD_MASKED_POSITIVE_POLARITY",	Result::make(SIMDE_SIDD_MASKED_POSITIVE_POLARITY), },
		{ StringId::Desc_Category_SIMD,						"_SIDD_MASKED_NEGATIVE_POLARITY",	Result::make(SIMDE_SIDD_MASKED_NEGATIVE_POLARITY), },
		
		{ StringId::Desc_Category_SIMD,						"_SIDD_LEAST_SIGNIFICANT",			Result::make(SIMDE_SIDD_LEAST_SIGNIFICANT), },
		{ StringId::Desc_Category_SIMD,						"_SIDD_MOST_SIGNIFICANT",			Result::make(SIMDE_SIDD_MOST_SIGNIFICANT), },
		
		{ StringId::Desc_Category_SIMD,						"_SIDD_BIT_MASK",					Result::make(SIMDE_SIDD_BIT_MASK), },
		{ StringId::Desc_Category_SIMD,						"_SIDD_UNIT_MASK",					Result::make(SIMDE_SIDD_UNIT_MASK), },
		
		{ StringId::Desc_Category_SIMD,						"_MM_DENORMALS_ZERO_MASK",			Result::make(0x0040), },
		{ StringId::Desc_Category_SIMD,						"_MM_DENORMALS_ZERO_ON",			Result::make(0x0040), },
		{ StringId::Desc_Category_SIMD,						"_MM_DENORMALS_ZERO_OFF",			Result::make(0x0000), },

		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_AAAA",					Result::make(0x00), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_AAAB",					Result::make(0x01), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_AAAC",					Result::make(0x02), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_AAAD",					Result::make(0x03), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_AABA",					Result::make(0x04), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_AABB",					Result::make(0x05), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_AABC",					Result::make(0x06), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_AABD",					Result::make(0x07), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_AACA",					Result::make(0x08), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_AACB",					Result::make(0x09), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_AACC",					Result::make(0x0A), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_AACD",					Result::make(0x0B), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_AADA",					Result::make(0x0C), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_AADB",					Result::make(0x0D), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_AADC",					Result::make(0x0E), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_AADD",					Result::make(0x0F), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ABAA",					Result::make(0x10), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ABAB",					Result::make(0x11), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ABAC",					Result::make(0x12), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ABAD",					Result::make(0x13), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ABBA",					Result::make(0x14), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ABBB",					Result::make(0x15), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ABBC",					Result::make(0x16), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ABBD",					Result::make(0x17), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ABCA",					Result::make(0x18), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ABCB",					Result::make(0x19), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ABCC",					Result::make(0x1A), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ABCD",					Result::make(0x1B), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ABDA",					Result::make(0x1C), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ABDB",					Result::make(0x1D), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ABDC",					Result::make(0x1E), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ABDD",					Result::make(0x1F), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ACAA",					Result::make(0x20), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ACAB",					Result::make(0x21), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ACAC",					Result::make(0x22), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ACAD",					Result::make(0x23), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ACBA",					Result::make(0x24), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ACBB",					Result::make(0x25), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ACBC",					Result::make(0x26), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ACBD",					Result::make(0x27), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ACCA",					Result::make(0x28), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ACCB",					Result::make(0x29), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ACCC",					Result::make(0x2A), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ACCD",					Result::make(0x2B), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ACDA",					Result::make(0x2C), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ACDB",					Result::make(0x2D), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ACDC",					Result::make(0x2E), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ACDD",					Result::make(0x2F), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ADAA",					Result::make(0x30), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ADAB",					Result::make(0x31), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ADAC",					Result::make(0x32), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ADAD",					Result::make(0x33), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ADBA",					Result::make(0x34), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ADBB",					Result::make(0x35), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ADBC",					Result::make(0x36), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ADBD",					Result::make(0x37), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ADCA",					Result::make(0x38), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ADCB",					Result::make(0x39), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ADCC",					Result::make(0x3A), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ADCD",					Result::make(0x3B), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ADDA",					Result::make(0x3C), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ADDB",					Result::make(0x3D), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ADDC",					Result::make(0x3E), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_ADDD",					Result::make(0x3F), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BAAA",					Result::make(0x40), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BAAB",					Result::make(0x41), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BAAC",					Result::make(0x42), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BAAD",					Result::make(0x43), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BABA",					Result::make(0x44), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BABB",					Result::make(0x45), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BABC",					Result::make(0x46), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BABD",					Result::make(0x47), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BACA",					Result::make(0x48), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BACB",					Result::make(0x49), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BACC",					Result::make(0x4A), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BACD",					Result::make(0x4B), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BADA",					Result::make(0x4C), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BADB",					Result::make(0x4D), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BADC",					Result::make(0x4E), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BADD",					Result::make(0x4F), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BBAA",					Result::make(0x50), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BBAB",					Result::make(0x51), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BBAC",					Result::make(0x52), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BBAD",					Result::make(0x53), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BBBA",					Result::make(0x54), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BBBB",					Result::make(0x55), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BBBC",					Result::make(0x56), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BBBD",					Result::make(0x57), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BBCA",					Result::make(0x58), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BBCB",					Result::make(0x59), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BBCC",					Result::make(0x5A), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BBCD",					Result::make(0x5B), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BBDA",					Result::make(0x5C), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BBDB",					Result::make(0x5D), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BBDC",					Result::make(0x5E), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BBDD",					Result::make(0x5F), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BCAA",					Result::make(0x60), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BCAB",					Result::make(0x61), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BCAC",					Result::make(0x62), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BCAD",					Result::make(0x63), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BCBA",					Result::make(0x64), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BCBB",					Result::make(0x65), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BCBC",					Result::make(0x66), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BCBD",					Result::make(0x67), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BCCA",					Result::make(0x68), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BCCB",					Result::make(0x69), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BCCC",					Result::make(0x6A), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BCCD",					Result::make(0x6B), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BCDA",					Result::make(0x6C), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BCDB",					Result::make(0x6D), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BCDC",					Result::make(0x6E), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BCDD",					Result::make(0x6F), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BDAA",					Result::make(0x70), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BDAB",					Result::make(0x71), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BDAC",					Result::make(0x72), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BDAD",					Result::make(0x73), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BDBA",					Result::make(0x74), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BDBB",					Result::make(0x75), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BDBC",					Result::make(0x76), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BDBD",					Result::make(0x77), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BDCA",					Result::make(0x78), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BDCB",					Result::make(0x79), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BDCC",					Result::make(0x7A), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BDCD",					Result::make(0x7B), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BDDA",					Result::make(0x7C), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BDDB",					Result::make(0x7D), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BDDC",					Result::make(0x7E), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_BDDD",					Result::make(0x7F), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CAAA",					Result::make(0x80), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CAAB",					Result::make(0x81), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CAAC",					Result::make(0x82), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CAAD",					Result::make(0x83), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CABA",					Result::make(0x84), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CABB",					Result::make(0x85), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CABC",					Result::make(0x86), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CABD",					Result::make(0x87), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CACA",					Result::make(0x88), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CACB",					Result::make(0x89), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CACC",					Result::make(0x8A), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CACD",					Result::make(0x8B), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CADA",					Result::make(0x8C), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CADB",					Result::make(0x8D), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CADC",					Result::make(0x8E), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CADD",					Result::make(0x8F), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CBAA",					Result::make(0x90), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CBAB",					Result::make(0x91), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CBAC",					Result::make(0x92), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CBAD",					Result::make(0x93), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CBBA",					Result::make(0x94), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CBBB",					Result::make(0x95), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CBBC",					Result::make(0x96), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CBBD",					Result::make(0x97), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CBCA",					Result::make(0x98), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CBCB",					Result::make(0x99), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CBCC",					Result::make(0x9A), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CBCD",					Result::make(0x9B), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CBDA",					Result::make(0x9C), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CBDB",					Result::make(0x9D), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CBDC",					Result::make(0x9E), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CBDD",					Result::make(0x9F), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CCAA",					Result::make(0xA0), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CCAB",					Result::make(0xA1), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CCAC",					Result::make(0xA2), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CCAD",					Result::make(0xA3), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CCBA",					Result::make(0xA4), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CCBB",					Result::make(0xA5), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CCBC",					Result::make(0xA6), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CCBD",					Result::make(0xA7), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CCCA",					Result::make(0xA8), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CCCB",					Result::make(0xA9), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CCCC",					Result::make(0xAA), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CCCD",					Result::make(0xAB), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CCDA",					Result::make(0xAC), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CCDB",					Result::make(0xAD), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CCDC",					Result::make(0xAE), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CCDD",					Result::make(0xAF), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CDAA",					Result::make(0xB0), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CDAB",					Result::make(0xB1), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CDAC",					Result::make(0xB2), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CDAD",					Result::make(0xB3), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CDBA",					Result::make(0xB4), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CDBB",					Result::make(0xB5), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CDBC",					Result::make(0xB6), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CDBD",					Result::make(0xB7), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CDCA",					Result::make(0xB8), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CDCB",					Result::make(0xB9), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CDCC",					Result::make(0xBA), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CDCD",					Result::make(0xBB), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CDDA",					Result::make(0xBC), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CDDB",					Result::make(0xBD), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CDDC",					Result::make(0xBE), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_CDDD",					Result::make(0xBF), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DAAA",					Result::make(0xC0), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DAAB",					Result::make(0xC1), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DAAC",					Result::make(0xC2), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DAAD",					Result::make(0xC3), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DABA",					Result::make(0xC4), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DABB",					Result::make(0xC5), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DABC",					Result::make(0xC6), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DABD",					Result::make(0xC7), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DACA",					Result::make(0xC8), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DACB",					Result::make(0xC9), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DACC",					Result::make(0xCA), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DACD",					Result::make(0xCB), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DADA",					Result::make(0xCC), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DADB",					Result::make(0xCD), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DADC",					Result::make(0xCE), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DADD",					Result::make(0xCF), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DBAA",					Result::make(0xD0), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DBAB",					Result::make(0xD1), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DBAC",					Result::make(0xD2), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DBAD",					Result::make(0xD3), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DBBA",					Result::make(0xD4), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DBBB",					Result::make(0xD5), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DBBC",					Result::make(0xD6), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DBBD",					Result::make(0xD7), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DBCA",					Result::make(0xD8), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DBCB",					Result::make(0xD9), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DBCC",					Result::make(0xDA), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DBCD",					Result::make(0xDB), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DBDA",					Result::make(0xDC), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DBDB",					Result::make(0xDD), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DBDC",					Result::make(0xDE), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DBDD",					Result::make(0xDF), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DCAA",					Result::make(0xE0), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DCAB",					Result::make(0xE1), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DCAC",					Result::make(0xE2), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DCAD",					Result::make(0xE3), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DCBA",					Result::make(0xE4), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DCBB",					Result::make(0xE5), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DCBC",					Result::make(0xE6), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DCBD",					Result::make(0xE7), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DCCA",					Result::make(0xE8), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DCCB",					Result::make(0xE9), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DCCC",					Result::make(0xEA), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DCCD",					Result::make(0xEB), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DCDA",					Result::make(0xEC), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DCDB",					Result::make(0xED), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DCDC",					Result::make(0xEE), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DCDD",					Result::make(0xEF), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DDAA",					Result::make(0xF0), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DDAB",					Result::make(0xF1), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DDAC",					Result::make(0xF2), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DDAD",					Result::make(0xF3), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DDBA",					Result::make(0xF4), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DDBB",					Result::make(0xF5), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DDBC",					Result::make(0xF6), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DDBD",					Result::make(0xF7), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DDCA",					Result::make(0xF8), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DDCB",					Result::make(0xF9), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DDCC",					Result::make(0xFA), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DDCD",					Result::make(0xFB), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DDDA",					Result::make(0xFC), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DDDB",					Result::make(0xFD), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DDDC",					Result::make(0xFE), },
		{ StringId::Desc_Category_SIMDPermutations,			"_MM_PERM_DDDD",					Result::make(0xFF), },
	};

	/** The static list of built-in functions. */
	const FunctionDef ExecutionContext::builtInFunctions[] = {
		// == Pow.
		{ StringId::Desc_Category_Cmath,					"pow", StringId::Desc_Pow, { { DataType::Double, "x", StringId::Desc_MathParam_PowX }, { DataType::Double, "y", StringId::VE_STR_POW_PARAM_Y } }, IntrinsicBridges::powBridge, false },
		{ StringId::Desc_Category_Cmath,					"powf", StringId::Desc_Pow, { { DataType::Float, "x", StringId::Desc_MathParam_PowX }, { DataType::Float, "y", StringId::VE_STR_POW_PARAM_Y } }, IntrinsicBridges::powfBridge, false },

		// == Trigonometry.
		{ StringId::Desc_Category_Cmath,					"sin", StringId::Desc_Sin, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::sinBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"sinf", StringId::Desc_Sin, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::sinfBridge, false, true },
		
		{ StringId::Desc_Category_Cmath,					"cos", StringId::Desc_Cos, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::cosBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"cosf", StringId::Desc_Cos, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::cosfBridge, false, true },
		
		{ StringId::Desc_Category_Cmath,					"tan", StringId::Desc_Tan, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::tanBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"tanf", StringId::Desc_Tan, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::tanfBridge, false, true },

		// == Inverse Trigonometry.
		{ StringId::Desc_Category_Cmath,					"asin", StringId::Desc_Asin, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::asinBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"asinf", StringId::Desc_Asin, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::asinfBridge, false, true },
		
		{ StringId::Desc_Category_Cmath,					"acos", StringId::Desc_Acos, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::acosBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"acosf", StringId::Desc_Acos, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::acosfBridge, false, true },
		
		{ StringId::Desc_Category_Cmath,					"atan", StringId::Desc_Atan, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::atanBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"atanf", StringId::Desc_Atan, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::atanfBridge, false, true },
		
		{ StringId::Desc_Category_Cmath,					"atan2", StringId::Desc_Atan2, { { DataType::Double, "y", StringId::Desc_MathParam_Y }, { DataType::Double, "x", StringId::Desc_MathParam_X } }, IntrinsicBridges::atan2Bridge },
		{ StringId::Desc_Category_Cmath,					"atan2f", StringId::Desc_Atan2, { { DataType::Float, "y", StringId::Desc_MathParam_Y }, { DataType::Float, "x", StringId::Desc_MathParam_X } }, IntrinsicBridges::atan2fBridge },

		// == Exponential & Logarithmic.
		{ StringId::Desc_Category_Cmath,					"exp", StringId::Desc_Exp, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::expBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"expf", StringId::Desc_Exp, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::expfBridge, false, true },
		
		{ StringId::Desc_Category_Cmath,					"log", StringId::Desc_Log, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::logBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"logf", StringId::Desc_Log, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::logfBridge, false, true },
		
		{ StringId::Desc_Category_Cmath,					"log10", StringId::Desc_Log10, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log10Bridge, false, true },
		{ StringId::Desc_Category_Cmath,					"log10f", StringId::Desc_Log10, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log10fBridge, false, true },

		// == Roots.
		{ StringId::Desc_Category_Cmath,					"sqrt", StringId::Desc_Sqrt, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::sqrtBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"sqrtf", StringId::Desc_Sqrt, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::sqrtfBridge, false, true },
		
		{ StringId::Desc_Category_Cmath,					"cbrt", StringId::Desc_Cbrt, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::cbrtBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"cbrtf", StringId::Desc_Cbrt, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::cbrtfBridge, false, true },

		// == Rounding & Absolute Value.
		{ StringId::Desc_Category_Cmath,					"ceil", StringId::Desc_Ceil, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::ceilBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"ceilf", StringId::Desc_Ceil, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::ceilfBridge, false, true },

		{ StringId::Desc_Category_Cmath,					"floor", StringId::Desc_Floor, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::floorBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"floorf", StringId::Desc_Floor, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::floorfBridge, false, true },
		
		{ StringId::Desc_Category_Cmath,					"abs", StringId::Desc_Abs, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::absBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"fabs", StringId::Desc_Abs, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::fabsBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"fabsf", StringId::Desc_Abs, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::fabsfBridge, false, true },

		// == Hyperbolics.
		{ StringId::Desc_Category_Cmath,					"cosh", StringId::Desc_CosH, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::coshBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"coshf", StringId::Desc_CosH, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::coshfBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"sinh", StringId::Desc_SinH, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::sinhBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"sinhf", StringId::Desc_SinH, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::sinhfBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"tanh", StringId::Desc_TanH, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::tanhBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"tanhf", StringId::Desc_TanH, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::tanhfBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"acosh", StringId::Desc_AcosH, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::acoshBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"acoshf", StringId::Desc_AcosH, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::acoshfBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"asinh", StringId::Desc_AsinH, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::asinhBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"asinhf", StringId::Desc_AsinH, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::asinhfBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"atanh", StringId::Desc_AtanH, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::atanhBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"atanhf", StringId::Desc_AtanH, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::atanhfBridge, false, true },

		// == Extended Exponents & Logs.
		{ StringId::Desc_Category_Cmath,					"log2", StringId::Desc_Log2, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log2Bridge, false, true },
		{ StringId::Desc_Category_Cmath,					"log2f", StringId::Desc_Log2, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log2fBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"exp2", StringId::Desc_Exp2, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::exp2Bridge, false, true },
		{ StringId::Desc_Category_Cmath,					"exp2f", StringId::Desc_Exp2, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::exp2fBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"expm1", StringId::Desc_ExpM1, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::expm1Bridge, false, true },
		{ StringId::Desc_Category_Cmath,					"expm1f", StringId::Desc_ExpM1, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::expm1fBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"ilogb", StringId::Desc_Log, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::ilogbBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"ilogbf", StringId::Desc_Log, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::ilogbfBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"log1p", StringId::Desc_Log, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log1pBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"log1pf", StringId::Desc_Log, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log1pfBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"logb", StringId::Desc_Log, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::logbBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"logbf", StringId::Desc_Log, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::logbfBridge, false, true },

		// == Misc Math.
		{ StringId::Desc_Category_Cmath,					"hypot", StringId::Desc_Hypot, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::hypotBridge },
		{ StringId::Desc_Category_Cmath,					"hypotf", StringId::Desc_Hypot, { { DataType::Float, "x", StringId::Desc_MathParam_X }, { DataType::Float, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::hypotfBridge },
		{ StringId::Desc_Category_Cmath,					"tgamma", StringId::Desc_TGamma, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::tgammaBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"tgammaf", StringId::Desc_TGamma, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::tgammafBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"lgamma", StringId::Desc_LGamma, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::lgammaBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"lgammaf", StringId::Desc_LGamma, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::lgammafBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"trunc", StringId::Desc_Trunc, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::truncBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"truncf", StringId::Desc_Trunc, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::truncfBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"round", StringId::Desc_Round, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::roundBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"roundf", StringId::Desc_Round, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::roundfBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"nearbyint", StringId::Desc_NearbyInt, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::nearbyintBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"nearbyintf", StringId::Desc_NearbyInt, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::nearbyintfBridge, false, true },

		// == Mod/Remainder.
		{ StringId::Desc_Category_Cmath,					"mod", StringId::Desc_Fmod, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::fmodBridge },
		{ StringId::Desc_Category_Cmath,					"fmod", StringId::Desc_Fmod, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::fmodBridge },
		{ StringId::Desc_Category_Cmath,					"fmodf", StringId::Desc_Fmod, { { DataType::Float, "x", StringId::Desc_MathParam_X }, { DataType::Float, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::fmodfBridge },
		{ StringId::Desc_Category_Cmath,					"remainder", StringId::Desc_Remainder, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::remainderBridge },
		{ StringId::Desc_Category_Cmath,					"remainderf", StringId::Desc_Remainder, { { DataType::Float, "x", StringId::Desc_MathParam_X }, { DataType::Float, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::remainderfBridge },
		// TODO: { StringId::Desc_Category_Cmath,				"remquo", StringId::Desc_Fmod, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y }, { DataType::Pointer, "quo", StringId::VE_STR_MATH_PARAM_PTR } }, IntrinsicBridges::remquoBridge },
		
		// == Bounds & MADD.
		{ StringId::Desc_Category_Cmath,					"nextafter", StringId::Desc_NextAfter, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::nextafterBridge },
		{ StringId::Desc_Category_Cmath,					"nextafterf", StringId::Desc_NextAfter, { { DataType::Float, "x", StringId::Desc_MathParam_X }, { DataType::Float, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::nextafterfBridge },
		{ StringId::Desc_Category_Cmath,					"nexttoward", StringId::Desc_NextToward, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::nexttowardBridge },
		{ StringId::Desc_Category_Cmath,					"nexttowardf", StringId::Desc_NextToward, { { DataType::Float, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::nexttowardfBridge },
		{ StringId::Desc_Category_Cmath,					"dim", StringId::Desc_Fdim, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::fdimBridge },
		{ StringId::Desc_Category_Cmath,					"fdim", StringId::Desc_Fdim, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::fdimBridge },
		{ StringId::Desc_Category_Cmath,					"fdimf", StringId::Desc_Fdim, { { DataType::Float, "x", StringId::Desc_MathParam_X }, { DataType::Float, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::fdimfBridge },
		{ StringId::Desc_Category_Cmath,					"max", StringId::Desc_Max, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::fmaxBridge },
		{ StringId::Desc_Category_Cmath,					"min", StringId::Desc_Min, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::fminBridge },
		{ StringId::Desc_Category_Cmath,					"madd", StringId::Desc_Fma, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y }, { DataType::Double, "z", StringId::Desc_MathParam_Z } }, IntrinsicBridges::fmaBridge },
		{ StringId::Desc_Category_Cmath,					"fma", StringId::Desc_Fma, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y }, { DataType::Double, "z", StringId::Desc_MathParam_Z } }, IntrinsicBridges::fmaBridge },
		
		// == Type Identification/Logic.
		{ StringId::Desc_Category_Cmath,					"isnan", StringId::Desc_IsNan, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::isnanBridge, false, true },
		{ StringId::Desc_Category_Cmath,					"isinf", StringId::Desc_IsInf, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::isinfBridge, false, true },

		// == Bit Manipulation (<bit>).
		{ StringId::Desc_Category_Bit,						"byteswap16", StringId::Desc_ByteSwap16, { { DataType::UInt16, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::byteswap16Bridge, false, true },
		{ StringId::Desc_Category_Bit,						"byteswap32", StringId::Desc_ByteSwap32, { { DataType::UInt32, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::byteswap32Bridge, false, true },
		{ StringId::Desc_Category_Bit,						"byteswap64", StringId::Desc_ByteSwap, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::byteswap64Bridge, false, true },
		{ StringId::Desc_Category_Bit,						"byteswap", StringId::Desc_ByteSwap, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::byteswap64Bridge, false, true },
		{ StringId::Desc_Category_Bit,						"has_single_bit", StringId::Desc_HasSingleBit, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::has_single_bitBridge, false, true },
		{ StringId::Desc_Category_Bit,						"bit_ceil", StringId::Desc_BitCeil, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::bit_ceilBridge, false, true },
		{ StringId::Desc_Category_Bit,						"bit_floor", StringId::Desc_BitFloor, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::bit_floorBridge, false, true },
		{ StringId::Desc_Category_Bit,						"bit_width", StringId::Desc_BitWidth, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::bit_widthBridge, false, true },
		{ StringId::Desc_Category_Bit,						"rotl", StringId::Desc_RotL, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val }, { DataType::Int32, "s", StringId::Desc_BitParamS } }, IntrinsicBridges::rotlBridge },
		{ StringId::Desc_Category_Bit,						"rotr", StringId::Desc_RotR, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val }, { DataType::Int32, "s", StringId::Desc_BitParamS } }, IntrinsicBridges::rotrBridge },
		{ StringId::Desc_Category_Bit,						"countl_zero", StringId::Desc_CountLZero, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::countl_zeroBridge, false, true },
		{ StringId::Desc_Category_Bit,						"countl_one", StringId::Desc_CountLOne, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::countl_oneBridge, false, true },
		{ StringId::Desc_Category_Bit,						"countr_zero", StringId::Desc_CountRZero, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::countr_zeroBridge, false, true },
		{ StringId::Desc_Category_Bit,						"countr_one", StringId::Desc_CountROne, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::countr_oneBridge, false, true },
		{ StringId::Desc_Category_Bit,						"popcount", StringId::Desc_PopCount, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::popcountBridge, false, true },

		// == Randomization.
		{ StringId::Desc_Category_Randomization,			"rand", StringId::Desc_Rand, { }, IntrinsicBridges::randBridge },

		// == HTML.
		{ StringId::Desc_Category_Html,						"htmlCount", StringId::Desc_HtmlCount, {}, IntrinsicBridges::htmlCountBridge },
		{ StringId::Desc_Category_Html,						"htmlName", StringId::Desc_HtmlName, { { DataType::Int64, "index", StringId::Desc_HtmlName_Index } }, IntrinsicBridges::htmlNameBridge, false, true },
		{ StringId::Desc_Category_Html,						"htmlChar", StringId::Desc_HtmlChar, { { DataType::Int64, "indexOrName", StringId::Desc_HtmlChar_Arg } }, IntrinsicBridges::htmlCharBridge, false, true },

		// == Strings.
		{ StringId::Desc_Category_Strings,					"capitalize", StringId::Desc_String_Capitalize, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::capitalizeBridge, false, true },
		{ StringId::Desc_Category_Strings,					"casefold", StringId::Desc_String_Casefold, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::casefoldBridge, false, true },
		{ StringId::Desc_Category_Strings,					"center", StringId::Desc_String_Center, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width } }, IntrinsicBridges::centerBridge },
		{ StringId::Desc_Category_Strings,					"center", StringId::Desc_String_Center, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width }, { DataType::Any, "fillchar", StringId::String_Param_FillChar } }, IntrinsicBridges::centerBridge },
		{ StringId::Desc_Category_Strings,					"count", StringId::Desc_String_Count, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub } }, IntrinsicBridges::countBridge },
		{ StringId::Desc_Category_Strings,					"count", StringId::Desc_String_Count, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub }, { DataType::Any, "start", StringId::String_Param_Start } }, IntrinsicBridges::countBridge },
		{ StringId::Desc_Category_Strings,					"count", StringId::Desc_String_Count, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub }, { DataType::Any, "start", StringId::String_Param_Start }, { DataType::Any, "end", StringId::String_Param_End } }, IntrinsicBridges::countBridge },
		{ StringId::Desc_Category_Strings,					"encode", StringId::Desc_String_Encode, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "encoding", StringId::String_Param_Encoding } }, IntrinsicBridges::encodeBridge },
		{ StringId::Desc_Category_Strings,					"encode", StringId::Desc_String_Encode, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "encoding", StringId::String_Param_Encoding }, { DataType::Any, "errors", StringId::String_Param_Errors } }, IntrinsicBridges::encodeBridge },
		{ StringId::Desc_Category_Strings,					"endswith", StringId::Desc_String_EndsWith, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "suffix", StringId::String_Param_Suffix } }, IntrinsicBridges::endsWithBridge },
		{ StringId::Desc_Category_Strings,					"endswith", StringId::Desc_String_EndsWith, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "suffix", StringId::String_Param_Suffix }, { DataType::Any, "start", StringId::String_Param_Start } }, IntrinsicBridges::endsWithBridge },
		{ StringId::Desc_Category_Strings,					"endswith", StringId::Desc_String_EndsWith, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "suffix", StringId::String_Param_Suffix }, { DataType::Any, "start", StringId::String_Param_Start }, { DataType::Any, "end", StringId::String_Param_End } }, IntrinsicBridges::endsWithBridge },
		{ StringId::Desc_Category_Strings,					"expandtabs", StringId::Desc_String_ExpandTabs, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::expandTabsBridge },
		{ StringId::Desc_Category_Strings,					"expandtabs", StringId::Desc_String_ExpandTabs, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "tabsize", StringId::String_Param_TabSize } }, IntrinsicBridges::expandTabsBridge },
		{ StringId::Desc_Category_Strings,					"find", StringId::Desc_String_Find, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub } }, IntrinsicBridges::findBridge },
		{ StringId::Desc_Category_Strings,					"find", StringId::Desc_String_Find, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub }, { DataType::Any, "start", StringId::String_Param_Start } }, IntrinsicBridges::findBridge },
		{ StringId::Desc_Category_Strings,					"find", StringId::Desc_String_Find, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub }, { DataType::Any, "start", StringId::String_Param_Start }, { DataType::Any, "end", StringId::String_Param_End } }, IntrinsicBridges::findBridge },
		{ StringId::Desc_Category_Strings,					"format", StringId::Desc_String_Format, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Variadic } }, IntrinsicBridges::formatBridge },
		{ StringId::Desc_Category_Strings,					"index", StringId::Desc_String_Find, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub } }, IntrinsicBridges::findBridge },
		{ StringId::Desc_Category_Strings,					"index", StringId::Desc_String_Find, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub }, { DataType::Any, "start", StringId::String_Param_Start } }, IntrinsicBridges::findBridge },
		{ StringId::Desc_Category_Strings,					"index", StringId::Desc_String_Find, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub }, { DataType::Any, "start", StringId::String_Param_Start }, { DataType::Any, "end", StringId::String_Param_End } }, IntrinsicBridges::findBridge },
		{ StringId::Desc_Category_Strings,					"isalnum", StringId::Desc_String_IsAlnum, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isAlnumBridge, false, true },
		{ StringId::Desc_Category_Strings,					"isalpha", StringId::Desc_String_IsAlpha, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isAlphaBridge, false, true },
		{ StringId::Desc_Category_Strings,					"isascii", StringId::Desc_String_IsAscii, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isAsciiBridge, false, true },
		{ StringId::Desc_Category_Strings,					"isdecimal", StringId::Desc_String_IsDecimal, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isDecimalBridge, false, true },
		{ StringId::Desc_Category_Strings,					"isdigit", StringId::Desc_String_IsDigit, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isDigitBridge, false, true },
		{ StringId::Desc_Category_Strings,					"isidentifier", StringId::Desc_String_IsIdentifier, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::isIdentifierBridge, false, true },
		{ StringId::Desc_Category_Strings,					"isnumeric", StringId::Desc_String_IsNumeric, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isNumericBridge, false, true },
		{ StringId::Desc_Category_Strings,					"isprintable", StringId::Desc_String_IsPrintable, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isPrintableBridge, false, true },
		{ StringId::Desc_Category_Strings,					"isspace", StringId::Desc_String_IsSpace, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isSpaceBridge, false, true },
		{ StringId::Desc_Category_Strings,					"istitle", StringId::Desc_String_IsTitle, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::isTitleBridge, false, true },
		{ StringId::Desc_Category_Strings,					"isupper", StringId::Desc_String_IsUpper, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isUpperBridge, false, true },
		{ StringId::Desc_Category_Strings,					"join", StringId::Desc_String_Join, { { DataType::String, "separator", StringId::Desc_Param_Separator }, { DataType::Any, "iterable", StringId::Desc_Param_Iterable } }, IntrinsicBridges::joinBridge },
		{ StringId::Desc_Category_Strings,					"ljust", StringId::Desc_String_LJust, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width } }, IntrinsicBridges::ljustBridge },
		{ StringId::Desc_Category_Strings,					"ljust", StringId::Desc_String_LJust, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width }, { DataType::Any, "fillchar", StringId::String_Param_Fillchar } }, IntrinsicBridges::ljustBridge },
		{ StringId::Desc_Category_Strings,					"lower", StringId::Desc_String_Lower, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::lowerBridge, false, true },
		{ StringId::Desc_Category_Strings,					"lstrip", StringId::Desc_String_LStrip, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::lstripBridge, false, true },
		{ StringId::Desc_Category_Strings,					"lstrip", StringId::Desc_String_LStrip, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "chars", StringId::String_Param_Chars } }, IntrinsicBridges::lstripBridge },
		{ StringId::Desc_Category_Strings,					"partition", StringId::Desc_String_Partition, { { DataType::String, "separator", StringId::Desc_Param_Separator } }, IntrinsicBridges::partitionBridge },
		{ StringId::Desc_Category_Strings,					"removeprefix", StringId::Desc_String_RemovePrefix, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "prefix", StringId::String_Param_Prefix } }, IntrinsicBridges::removePrefixBridge },
		{ StringId::Desc_Category_Strings,					"removesuffix", StringId::Desc_String_RemoveSuffix, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "suffix", StringId::String_Param_Suffix_RemoveSuffix } }, IntrinsicBridges::removeSuffixBridge },
		{ StringId::Desc_Category_Strings,					"replace", StringId::Desc_String_Replace, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "old", StringId::String_Param_Old }, { DataType::String, "new", StringId::String_Param_New } }, IntrinsicBridges::replaceBridge },
		{ StringId::Desc_Category_Strings,					"replace", StringId::Desc_String_Replace, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "old", StringId::String_Param_Old }, { DataType::String, "new", StringId::String_Param_New }, { DataType::Integer, "count", StringId::String_Param_Count } }, IntrinsicBridges::replaceBridge },
		{ StringId::Desc_Category_Strings,					"rfind", StringId::Desc_String_RFind, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "sub", StringId::String_Param_Sub_RFind } }, IntrinsicBridges::rfindBridge },
		{ StringId::Desc_Category_Strings,					"rfind", StringId::Desc_String_RFind, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "sub", StringId::String_Param_Sub_RFind }, { DataType::Integer, "start", StringId::String_Param_Start_RFind } }, IntrinsicBridges::rfindBridge },
		{ StringId::Desc_Category_Strings,					"rfind", StringId::Desc_String_RFind, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "sub", StringId::String_Param_Sub_RFind }, { DataType::Integer, "start", StringId::String_Param_Start_RFind }, { DataType::Integer, "end", StringId::String_Param_End_RFind } }, IntrinsicBridges::rfindBridge },
		{ StringId::Desc_Category_Strings,					"rindex", StringId::Desc_String_RFind, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "sub", StringId::String_Param_Sub_RFind } }, IntrinsicBridges::rfindBridge },
		{ StringId::Desc_Category_Strings,					"rindex", StringId::Desc_String_RFind, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "sub", StringId::String_Param_Sub_RFind }, { DataType::Integer, "start", StringId::String_Param_Start_RFind } }, IntrinsicBridges::rfindBridge },
		{ StringId::Desc_Category_Strings,					"rindex", StringId::Desc_String_RFind, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "sub", StringId::String_Param_Sub_RFind }, { DataType::Integer, "start", StringId::String_Param_Start_RFind }, { DataType::Integer, "end", StringId::String_Param_End_RFind } }, IntrinsicBridges::rfindBridge },
		{ StringId::Desc_Category_Strings,					"rjust", StringId::Desc_String_RJust, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width } }, IntrinsicBridges::rjustBridge },
		{ StringId::Desc_Category_Strings,					"rjust", StringId::Desc_String_RJust, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width }, { DataType::String, "fillchar", StringId::String_Param_Fillchar } }, IntrinsicBridges::rjustBridge },
		{ StringId::Desc_Category_Strings,					"rpartition", StringId::Desc_String_RPartition, { { DataType::String, "separator", StringId::Desc_Param_Separator } }, IntrinsicBridges::rpartitionBridge },
		{ StringId::Desc_Category_Strings,					"rstrip", StringId::Desc_String_RStrip, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::rstripBridge, false, true },
		{ StringId::Desc_Category_Strings,					"rstrip", StringId::Desc_String_RStrip, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "chars", StringId::String_Param_Chars } }, IntrinsicBridges::rstripBridge },
		{ StringId::Desc_Category_Strings,					"split", StringId::Desc_String_Split, { { DataType::String, "separator", StringId::Desc_Param_Separator } }, IntrinsicBridges::splitBridge },
		{ StringId::Desc_Category_Strings,					"split", StringId::Desc_String_Split, { { DataType::String, "separator", StringId::Desc_Param_Separator }, { DataType::Int64, "maxsplit", StringId::Desc_Param_MaxSplit } }, IntrinsicBridges::splitBridge },
		{ StringId::Desc_Category_Strings,					"splitlines", StringId::Desc_String_SplitLines, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::splitlinesBridge },
		{ StringId::Desc_Category_Strings,					"splitlines", StringId::Desc_String_SplitLines, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "keepends", StringId::Desc_Param_KeepEnds } }, IntrinsicBridges::splitlinesBridge },
		{ StringId::Desc_Category_Strings,					"startswith", StringId::Desc_String_StartsWith, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "prefix", StringId::String_Param_Prefix } }, IntrinsicBridges::startsWithBridge },
		{ StringId::Desc_Category_Strings,					"startswith", StringId::Desc_String_StartsWith, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "prefix", StringId::String_Param_Prefix }, { DataType::Integer, "start", StringId::String_Param_Start } }, IntrinsicBridges::startsWithBridge },
		{ StringId::Desc_Category_Strings,					"startswith", StringId::Desc_String_StartsWith, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "prefix", StringId::String_Param_Prefix }, { DataType::Integer, "start", StringId::String_Param_Start }, { DataType::Integer, "end", StringId::String_Param_End } }, IntrinsicBridges::startsWithBridge },
		{ StringId::Desc_Category_Strings,					"strip", StringId::Desc_String_Strip, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::stripBridge, false, true },
		{ StringId::Desc_Category_Strings,					"strip", StringId::Desc_String_Strip, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "chars", StringId::String_Param_Chars } }, IntrinsicBridges::stripBridge },
		{ StringId::Desc_Category_Strings,					"swapcase", StringId::Desc_String_SwapCase, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::swapcaseBridge, false, true },
		{ StringId::Desc_Category_Strings,					"title", StringId::Desc_String_Title, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::titleBridge, false, true },
		{ StringId::Desc_Category_Strings,					"upper", StringId::Desc_String_Upper, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::upperBridge, false, true },
		{ StringId::Desc_Category_Strings,					"zfill", StringId::Desc_String_ZFill, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width } }, IntrinsicBridges::zfillBridge },

		// == Strings/Vectors.
		{ StringId::Desc_Category_Vectors,					"append", StringId::Desc_Intrinsic_Append, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject }, { DataType::Any, "val", StringId::Desc_Param_Item } }, IntrinsicBridges::appendBridge },
		{ StringId::Desc_Category_Vectors,					"at", StringId::Desc_Object_At, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject }, { DataType::Integer, "index", StringId::String_Param_Index } }, IntrinsicBridges::atBridge },
		{ StringId::Desc_Category_Vectors,					"clear", StringId::Desc_Intrinsic_Clear, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject } }, IntrinsicBridges::clearBridge },
		{ StringId::Desc_Category_Vectors,					"copy", StringId::Desc_Intrinsic_Copy, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject } }, IntrinsicBridges::copyBridge },
		{ StringId::Desc_Category_Vectors,					"len", StringId::Desc_Object_Len, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject } }, IntrinsicBridges::lengthBridge },
		{ StringId::Desc_Category_Vectors,					"pop", StringId::Desc_Intrinsic_Pop, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject } }, IntrinsicBridges::popBridge },
		{ StringId::Desc_Category_Vectors,					"pop", StringId::Desc_Intrinsic_Pop, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject }, { DataType::Int32, "index", StringId::Desc_Param_PopIndex } }, IntrinsicBridges::popBridge },
		{ StringId::Desc_Category_Vectors,					"pop_back", StringId::Desc_Intrinsic_Pop, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject } }, IntrinsicBridges::popBridge },
		{ StringId::Desc_Category_Vectors,					"push_back", StringId::Desc_Object_PushBack, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject }, { DataType::Any, "val", StringId::String_Param_Item } }, IntrinsicBridges::pushBackBridge },
		{ StringId::Desc_Category_Vectors,					"remove", StringId::Desc_Intrinsic_Remove, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject }, { DataType::Any, "val", StringId::Desc_Param_RemoveValue } }, IntrinsicBridges::removeBridge },
		{ StringId::Desc_Category_Vectors,					"reverse", StringId::Desc_Intrinsic_Reverse, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject } }, IntrinsicBridges::reverseBridge },
		{ StringId::Desc_Category_Vectors,					"size", StringId::Desc_Object_Size, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject } }, IntrinsicBridges::lengthBridge },

		// == Trigonometry & Angles.
		{ StringId::Desc_Category_TrigonometryAngles,		"deg", StringId::Desc_Deg, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::degBridge, false, true },
		{ StringId::Desc_Category_TrigonometryAngles,		"rad", StringId::Desc_Rad, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::radBridge, false, true },
		{ StringId::Desc_Category_TrigonometryAngles,		"sinc", StringId::Desc_Math_Sinc, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sincBridge, false, true },
		{ StringId::Desc_Category_TrigonometryAngles,		"sinExact", StringId::Desc_Math_SinExact, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sinExactBridge, false, true },
		{ StringId::Desc_Category_TrigonometryAngles,		"cosExact", StringId::Desc_Math_CosExact, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::cosExactBridge, false, true },

		// == Clamping & Bounds.
		{ StringId::Desc_Category_ClampingBounds,			"min", StringId::Desc_Math_Min, { { DataType::Any, "x", StringId::Math_Param_X }, { DataType::Any, "y", StringId::Math_Param_Y } }, IntrinsicBridges::minBridge },
		{ StringId::Desc_Category_ClampingBounds,			"max", StringId::Desc_Math_Max, { { DataType::Any, "x", StringId::Math_Param_X }, { DataType::Any, "y", StringId::Math_Param_Y } }, IntrinsicBridges::maxBridge },
		{ StringId::Desc_Category_ClampingBounds,			"clamp", StringId::Desc_Math_Clamp, { { DataType::Any, "val", StringId::Math_Param_Val }, { DataType::Any, "minVal", StringId::Math_Param_Min }, { DataType::Any, "maxVal", StringId::Math_Param_Max } }, IntrinsicBridges::clampBridge },
		{ StringId::Desc_Category_ClampingBounds,			"step", StringId::Desc_Math_Step, { { DataType::Double, "edge", StringId::Math_Param_Edge }, { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::stepBridge },
		
		// == Floating-Point Analysis.
		{ StringId::Desc_Category_FloatingPointAnalysis,	"relativeEpsilon", StringId::Desc_Math_RelativeEpsilon, { { DataType::Double, "left", StringId::Math_Param_Left }, { DataType::Double, "right", StringId::Math_Param_Right }, { DataType::Double, "epsilon", StringId::Math_Param_Epsilon } }, IntrinsicBridges::relativeEpsilonBridge },
		
		// == Arithmetic & Number Theory.
		{ StringId::Desc_Category_ArithmeticNumberTheory,	"frac", StringId::Desc_Math_Frac, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::fracBridge, false, true },
		{ StringId::Desc_Category_ArithmeticNumberTheory,	"lcm", StringId::Desc_Math_Lcm, { { DataType::Integer, "x", StringId::Math_Param_X }, { DataType::Integer, "y", StringId::Math_Param_Y } }, IntrinsicBridges::lcmBridge },
		//{ StringId::Desc_Category_ArithmeticNumberTheory,	"lcmChecked", StringId::Desc_Math_LcmChecked, { { DataType::Integer, "x", StringId::Math_Param_X }, { DataType::Integer, "y", StringId::Math_Param_Y } }, IntrinsicBridges::lcmCheckedBridge },

		// == Gamma Functions.
		{ StringId::Desc_Category_Gamma,					"linearToSRgb", StringId::Desc_Math_LinearToSRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSRgbBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"sRgbToLinear", StringId::Desc_Math_SRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sRgbToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"pow2_2ToLinear", StringId::Desc_Math_Pow2_2ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::pow2_2ToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToPow2_2", StringId::Desc_Math_LinearToPow2_2, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToPow2_2Bridge, false, true },
		{ StringId::Desc_Category_Gamma,					"smpte240MToLinear", StringId::Desc_Math_Smpte240MToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::smpte240MToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToSmpte240M", StringId::Desc_Math_LinearToSmpte240M, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSmpte240MBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"sLog2ToLinear", StringId::Desc_Math_SLog2ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sLog2ToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToSLog2", StringId::Desc_Math_LinearToSLog2, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSLog2Bridge, false, true },
		{ StringId::Desc_Category_Gamma,					"canonLogToLinear", StringId::Desc_Math_CanonLogToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::canonLogToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToCanonLog", StringId::Desc_Math_LinearToCanonLog, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToCanonLogBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"viperToLinear", StringId::Desc_Math_ViperToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::viperToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToViper", StringId::Desc_Math_LinearToViper, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToViperBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"acesCgToLinear", StringId::Desc_Math_AcesCgToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::acesCgToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToAcesCg", StringId::Desc_Math_LinearToAcesCg, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToAcesCgBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"sRgbToLinearPrecise", StringId::Desc_Math_SRgbToLinearPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sRgbToLinearPreciseBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToSRgbPrecise", StringId::Desc_Math_LinearToSRgbPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSRgbPreciseBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"colorLcdToLinear", StringId::Desc_Math_ColorLcdToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::colorLcdToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToColorLcd", StringId::Desc_Math_LinearToColorLcd, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToColorLcdBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"smpte170MToLinear", StringId::Desc_Math_Smpte170MToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::smpte170MToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToSmpte170M", StringId::Desc_Math_LinearToSmpte170M, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSmpte170MBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"smpte170MToLinearPrecise", StringId::Desc_Math_Smpte170MToLinearPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::smpte170MToLinearPreciseBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToSmpte170MPrecise", StringId::Desc_Math_LinearToSmpte170MPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSmpte170MPreciseBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"dciP3ToLinear", StringId::Desc_Math_DciP3ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::dciP3ToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToDciP3", StringId::Desc_Math_LinearToDciP3, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToDciP3Bridge, false, true },
		{ StringId::Desc_Category_Gamma,					"genericRgbToLinear", StringId::Desc_Math_GenericRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::genericRgbToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToGenericRgb", StringId::Desc_Math_LinearToGenericRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToGenericRgbBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"pow2_8ToLinear", StringId::Desc_Math_Pow2_8ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::pow2_8ToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToPow2_8", StringId::Desc_Math_LinearToPow2_8, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToPow2_8Bridge, false, true },
		{ StringId::Desc_Category_Gamma,					"adobeRgbToLinear", StringId::Desc_Math_AdobeRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::adobeRgbToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToAdobeRgb", StringId::Desc_Math_LinearToAdobeRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToAdobeRgbBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"smpte240MToLinearPrecise", StringId::Desc_Math_Smpte240MToLinearPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::smpte240MToLinearPreciseBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToSmpte240MPrecise", StringId::Desc_Math_LinearToSmpte240MPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSmpte240MPreciseBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"acesCcToLinear", StringId::Desc_Math_AcesCcToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::acesCcToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToAcesCc", StringId::Desc_Math_LinearToAcesCc, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToAcesCcBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"rommRgbToLinear", StringId::Desc_Math_RommRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::rommRgbToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToRommRgb", StringId::Desc_Math_LinearToRommRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToRommRgbBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"rimmRgbToLinear", StringId::Desc_Math_RimmRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::rimmRgbToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToRimmRgb", StringId::Desc_Math_LinearToRimmRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToRimmRgbBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"erimmRgbToLinear", StringId::Desc_Math_ErimmRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::erimmRgbToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToErimmRgb", StringId::Desc_Math_LinearToErimmRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToErimmRgbBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"sLogToLinear", StringId::Desc_Math_SLogToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sLogToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToSLog", StringId::Desc_Math_LinearToSLog, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSLogBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"sLog3ToLinear", StringId::Desc_Math_SLog3ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sLog3ToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToSLog3", StringId::Desc_Math_LinearToSLog3, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSLog3Bridge, false, true },
		{ StringId::Desc_Category_Gamma,					"protuneToLinear", StringId::Desc_Math_ProtuneToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::protuneToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToProtune", StringId::Desc_Math_LinearToProtune, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToProtuneBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"canonLog2ToLinear", StringId::Desc_Math_CanonLog2ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::canonLog2ToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToCanonLog2", StringId::Desc_Math_LinearToCanonLog2, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToCanonLog2Bridge, false, true },
		{ StringId::Desc_Category_Gamma,					"canonLog3ToLinear", StringId::Desc_Math_CanonLog3ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::canonLog3ToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToCanonLog3", StringId::Desc_Math_LinearToCanonLog3, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToCanonLog3Bridge, false, true },
		{ StringId::Desc_Category_Gamma,					"aribStdB67ToLinear", StringId::Desc_Math_AribStdB67ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::aribStdB67ToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToAribStdB67", StringId::Desc_Math_LinearToAribStdB67, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToAribStdB67Bridge, false, true },
		{ StringId::Desc_Category_Gamma,					"panalogToLinear", StringId::Desc_Math_PanalogToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::panalogToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToPanalog", StringId::Desc_Math_LinearToPanalog, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToPanalogBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"crtProperToLinear", StringId::Desc_Math_CrtProperToLinear, { { DataType::Double, "val", StringId::Math_Param_Val } }, IntrinsicBridges::crtProperToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"crtProperToLinear", StringId::Desc_Math_CrtProperToLinear, { { DataType::Double, "val", StringId::Math_Param_Val }, { DataType::Double, "lw", StringId::Math_Param_Lw } }, IntrinsicBridges::crtProperToLinearBridge },
		{ StringId::Desc_Category_Gamma,					"crtProperToLinear", StringId::Desc_Math_CrtProperToLinear, { { DataType::Double, "val", StringId::Math_Param_Val }, { DataType::Double, "lw", StringId::Math_Param_Lw }, { DataType::Double, "b", StringId::Math_Param_B } }, IntrinsicBridges::crtProperToLinearBridge },
		{ StringId::Desc_Category_Gamma,					"linearToCrtProper", StringId::Desc_Math_LinearToCrtProper, { { DataType::Double, "val", StringId::Math_Param_Val } }, IntrinsicBridges::linearToCrtProperBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToCrtProper", StringId::Desc_Math_LinearToCrtProper, { { DataType::Double, "val", StringId::Math_Param_Val }, { DataType::Double, "lw", StringId::Math_Param_Lw } }, IntrinsicBridges::linearToCrtProperBridge },
		{ StringId::Desc_Category_Gamma,					"linearToCrtProper", StringId::Desc_Math_LinearToCrtProper, { { DataType::Double, "val", StringId::Math_Param_Val }, { DataType::Double, "lw", StringId::Math_Param_Lw }, { DataType::Double, "b", StringId::Math_Param_B } }, IntrinsicBridges::linearToCrtProperBridge },
		{ StringId::Desc_Category_Gamma,					"crtProper2ToLinear", StringId::Desc_Math_CrtProper2ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::crtProper2ToLinearBridge, false, true },
		{ StringId::Desc_Category_Gamma,					"linearToCrtProper2", StringId::Desc_Math_LinearToCrtProper2, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToCrtProper2Bridge, false, true },

		// == Colorspace Conversions.
		{ StringId::Desc_Category_ColorSpace,				"xyzToChromaticity", StringId::Desc_Func_XyzToChromaticity, { { DataType::Double, "x", StringId::Desc_Param_XyzX }, { DataType::Double, "y", StringId::Desc_Param_XyzY }, { DataType::Double, "z", StringId::Desc_Param_XyzZ } }, IntrinsicBridges::xyzToChromaticityBridge },
		{ StringId::Desc_Category_ColorSpace,				"chromaticityToXyz", StringId::Desc_Func_ChromaticityToXyz, { { DataType::Double, "chromaX", StringId::Desc_Param_ChromaX }, { DataType::Double, "chromaY", StringId::Desc_Param_ChromaY }, { DataType::Double, "y0", StringId::Desc_Param_XyzY } }, IntrinsicBridges::chromaticityToXyzBridge },
		
		{ StringId::Desc_Category_ColorSpace,				"rgbToHsl", StringId::Desc_Func_RgbToHsl, { { DataType::Double, "r", StringId::Desc_Param_ColorR }, { DataType::Double, "g", StringId::Desc_Param_ColorG }, { DataType::Double, "b", StringId::Desc_Param_ColorB } }, IntrinsicBridges::rgbToHslBridge },
		{ StringId::Desc_Category_ColorSpace,				"hslToRgb", StringId::Desc_Func_HslToRgb, { { DataType::Double, "h", StringId::Desc_Param_ColorH }, { DataType::Double, "s", StringId::Desc_Param_ColorS }, { DataType::Double, "l", StringId::Desc_Param_ColorL } }, IntrinsicBridges::hslToRgbBridge },
		
		{ StringId::Desc_Category_ColorSpace,				"rgbToHsv", StringId::Desc_Func_RgbToHsv, { { DataType::Double, "r", StringId::Desc_Param_ColorR }, { DataType::Double, "g", StringId::Desc_Param_ColorG }, { DataType::Double, "b", StringId::Desc_Param_ColorB } }, IntrinsicBridges::rgbToHsvBridge },
		{ StringId::Desc_Category_ColorSpace,				"hsvToRgb", StringId::Desc_Func_HsvToRgb, { { DataType::Double, "h", StringId::Desc_Param_ColorH }, { DataType::Double, "s", StringId::Desc_Param_ColorS }, { DataType::Double, "v", StringId::Desc_Param_ColorV } }, IntrinsicBridges::hsvToRgbBridge },
		
		{ StringId::Desc_Category_ColorSpace,				"rgbToYcbcr", StringId::Desc_Func_RgbToYcbcr, { { DataType::Double, "r", StringId::Desc_Param_ColorR }, { DataType::Double, "g", StringId::Desc_Param_ColorG }, { DataType::Double, "b", StringId::Desc_Param_ColorB } }, IntrinsicBridges::rgbToYcbcrBridge },
		{ StringId::Desc_Category_ColorSpace,				"rgbToYcbcr", StringId::Desc_Func_RgbToYcbcr, { { DataType::Double, "r", StringId::Desc_Param_ColorR }, { DataType::Double, "g", StringId::Desc_Param_ColorG }, { DataType::Double, "b", StringId::Desc_Param_ColorB }, { DataType::Double, "kr", StringId::Desc_Param_YcbcrKr } }, IntrinsicBridges::rgbToYcbcrBridge },
		{ StringId::Desc_Category_ColorSpace,				"rgbToYcbcr", StringId::Desc_Func_RgbToYcbcr, { { DataType::Double, "r", StringId::Desc_Param_ColorR }, { DataType::Double, "g", StringId::Desc_Param_ColorG }, { DataType::Double, "b", StringId::Desc_Param_ColorB }, { DataType::Double, "kr", StringId::Desc_Param_YcbcrKr }, { DataType::Double, "kb", StringId::Desc_Param_YcbcrKb } }, IntrinsicBridges::rgbToYcbcrBridge },
		{ StringId::Desc_Category_ColorSpace,				"rgbToYcbcr", StringId::Desc_Func_RgbToYcbcr, { { DataType::Double, "r", StringId::Desc_Param_ColorR }, { DataType::Double, "g", StringId::Desc_Param_ColorG }, { DataType::Double, "b", StringId::Desc_Param_ColorB }, { DataType::Double, "kr", StringId::Desc_Param_YcbcrKr }, { DataType::Double, "kb", StringId::Desc_Param_YcbcrKb }, { DataType::Double, "lumaRange", StringId::Desc_Param_LumaRange } }, IntrinsicBridges::rgbToYcbcrBridge },
		{ StringId::Desc_Category_ColorSpace,				"rgbToYcbcr", StringId::Desc_Func_RgbToYcbcr, { { DataType::Double, "r", StringId::Desc_Param_ColorR }, { DataType::Double, "g", StringId::Desc_Param_ColorG }, { DataType::Double, "b", StringId::Desc_Param_ColorB }, { DataType::Double, "kr", StringId::Desc_Param_YcbcrKr }, { DataType::Double, "kb", StringId::Desc_Param_YcbcrKb }, { DataType::Double, "lumaRange", StringId::Desc_Param_LumaRange }, { DataType::Double, "lumaOffset", StringId::Desc_Param_LumaOffset } }, IntrinsicBridges::rgbToYcbcrBridge },
		{ StringId::Desc_Category_ColorSpace,				"rgbToYcbcr", StringId::Desc_Func_RgbToYcbcr, { { DataType::Double, "r", StringId::Desc_Param_ColorR }, { DataType::Double, "g", StringId::Desc_Param_ColorG }, { DataType::Double, "b", StringId::Desc_Param_ColorB }, { DataType::Double, "kr", StringId::Desc_Param_YcbcrKr }, { DataType::Double, "kb", StringId::Desc_Param_YcbcrKb }, { DataType::Double, "lumaRange", StringId::Desc_Param_LumaRange }, { DataType::Double, "lumaOffset", StringId::Desc_Param_LumaOffset }, { DataType::Double, "chromaRange", StringId::Desc_Param_ChromaRange } }, IntrinsicBridges::rgbToYcbcrBridge },
		{ StringId::Desc_Category_ColorSpace,				"rgbToYcbcr", StringId::Desc_Func_RgbToYcbcr, { { DataType::Double, "r", StringId::Desc_Param_ColorR }, { DataType::Double, "g", StringId::Desc_Param_ColorG }, { DataType::Double, "b", StringId::Desc_Param_ColorB }, { DataType::Double, "kr", StringId::Desc_Param_YcbcrKr }, { DataType::Double, "kb", StringId::Desc_Param_YcbcrKb }, { DataType::Double, "lumaRange", StringId::Desc_Param_LumaRange }, { DataType::Double, "lumaOffset", StringId::Desc_Param_LumaOffset }, { DataType::Double, "chromaRange", StringId::Desc_Param_ChromaRange }, { DataType::Double, "chromaOffset", StringId::Desc_Param_ChromaOffset } }, IntrinsicBridges::rgbToYcbcrBridge },

		{ StringId::Desc_Category_ColorSpace,				"ycbcrToRgb", StringId::Desc_Func_YcbcrToRgb, { { DataType::Double, "y", StringId::Desc_Param_ColorYuvY }, { DataType::Double, "u", StringId::Desc_Param_ColorYuvU }, { DataType::Double, "v", StringId::Desc_Param_ColorYuvV } }, IntrinsicBridges::ycbcrToRgbBridge },
		{ StringId::Desc_Category_ColorSpace,				"ycbcrToRgb", StringId::Desc_Func_YcbcrToRgb, { { DataType::Double, "y", StringId::Desc_Param_ColorYuvY }, { DataType::Double, "u", StringId::Desc_Param_ColorYuvU }, { DataType::Double, "v", StringId::Desc_Param_ColorYuvV }, { DataType::Double, "kr", StringId::Desc_Param_YcbcrKr } }, IntrinsicBridges::ycbcrToRgbBridge },
		{ StringId::Desc_Category_ColorSpace,				"ycbcrToRgb", StringId::Desc_Func_YcbcrToRgb, { { DataType::Double, "y", StringId::Desc_Param_ColorYuvY }, { DataType::Double, "u", StringId::Desc_Param_ColorYuvU }, { DataType::Double, "v", StringId::Desc_Param_ColorYuvV }, { DataType::Double, "kr", StringId::Desc_Param_YcbcrKr }, { DataType::Double, "kb", StringId::Desc_Param_YcbcrKb } }, IntrinsicBridges::ycbcrToRgbBridge },
		{ StringId::Desc_Category_ColorSpace,				"ycbcrToRgb", StringId::Desc_Func_YcbcrToRgb, { { DataType::Double, "y", StringId::Desc_Param_ColorYuvY }, { DataType::Double, "u", StringId::Desc_Param_ColorYuvU }, { DataType::Double, "v", StringId::Desc_Param_ColorYuvV }, { DataType::Double, "kr", StringId::Desc_Param_YcbcrKr }, { DataType::Double, "kb", StringId::Desc_Param_YcbcrKb }, { DataType::Double, "lumaRange", StringId::Desc_Param_LumaRange } }, IntrinsicBridges::ycbcrToRgbBridge },
		{ StringId::Desc_Category_ColorSpace,				"ycbcrToRgb", StringId::Desc_Func_YcbcrToRgb, { { DataType::Double, "y", StringId::Desc_Param_ColorYuvY }, { DataType::Double, "u", StringId::Desc_Param_ColorYuvU }, { DataType::Double, "v", StringId::Desc_Param_ColorYuvV }, { DataType::Double, "kr", StringId::Desc_Param_YcbcrKr }, { DataType::Double, "kb", StringId::Desc_Param_YcbcrKb }, { DataType::Double, "lumaRange", StringId::Desc_Param_LumaRange }, { DataType::Double, "lumaOffset", StringId::Desc_Param_LumaOffset } }, IntrinsicBridges::ycbcrToRgbBridge },
		{ StringId::Desc_Category_ColorSpace,				"ycbcrToRgb", StringId::Desc_Func_YcbcrToRgb, { { DataType::Double, "y", StringId::Desc_Param_ColorYuvY }, { DataType::Double, "u", StringId::Desc_Param_ColorYuvU }, { DataType::Double, "v", StringId::Desc_Param_ColorYuvV }, { DataType::Double, "kr", StringId::Desc_Param_YcbcrKr }, { DataType::Double, "kb", StringId::Desc_Param_YcbcrKb }, { DataType::Double, "lumaRange", StringId::Desc_Param_LumaRange }, { DataType::Double, "lumaOffset", StringId::Desc_Param_LumaOffset }, { DataType::Double, "chromaRange", StringId::Desc_Param_ChromaRange } }, IntrinsicBridges::ycbcrToRgbBridge },
		{ StringId::Desc_Category_ColorSpace,				"ycbcrToRgb", StringId::Desc_Func_YcbcrToRgb, { { DataType::Double, "y", StringId::Desc_Param_ColorYuvY }, { DataType::Double, "u", StringId::Desc_Param_ColorYuvU }, { DataType::Double, "v", StringId::Desc_Param_ColorYuvV }, { DataType::Double, "kr", StringId::Desc_Param_YcbcrKr }, { DataType::Double, "kb", StringId::Desc_Param_YcbcrKb }, { DataType::Double, "lumaRange", StringId::Desc_Param_LumaRange }, { DataType::Double, "lumaOffset", StringId::Desc_Param_LumaOffset }, { DataType::Double, "chromaRange", StringId::Desc_Param_ChromaRange }, { DataType::Double, "chromaOffset", StringId::Desc_Param_ChromaOffset } }, IntrinsicBridges::ycbcrToRgbBridge },

		{ StringId::Desc_Category_ColorSpace,				"rgbToYuv", StringId::Desc_Func_RgbToYuv, { { DataType::Double, "r", StringId::Desc_Param_ColorR }, { DataType::Double, "g", StringId::Desc_Param_ColorG }, { DataType::Double, "b", StringId::Desc_Param_ColorB } }, IntrinsicBridges::rgbToYuvBridge },
		{ StringId::Desc_Category_ColorSpace,				"rgbToYuv", StringId::Desc_Func_RgbToYuv, { { DataType::Double, "r", StringId::Desc_Param_ColorR }, { DataType::Double, "g", StringId::Desc_Param_ColorG }, { DataType::Double, "b", StringId::Desc_Param_ColorB }, { DataType::Double, "kr", StringId::Desc_Param_AnalogYuvKr } }, IntrinsicBridges::rgbToYuvBridge },
		{ StringId::Desc_Category_ColorSpace,				"rgbToYuv", StringId::Desc_Func_RgbToYuv, { { DataType::Double, "r", StringId::Desc_Param_ColorR }, { DataType::Double, "g", StringId::Desc_Param_ColorG }, { DataType::Double, "b", StringId::Desc_Param_ColorB }, { DataType::Double, "kr", StringId::Desc_Param_AnalogYuvKr }, { DataType::Double, "kb", StringId::Desc_Param_AnalogYuvKb } }, IntrinsicBridges::rgbToYuvBridge },
		{ StringId::Desc_Category_ColorSpace,				"rgbToYuv", StringId::Desc_Func_RgbToYuv, { { DataType::Double, "r", StringId::Desc_Param_ColorR }, { DataType::Double, "g", StringId::Desc_Param_ColorG }, { DataType::Double, "b", StringId::Desc_Param_ColorB }, { DataType::Double, "kr", StringId::Desc_Param_AnalogYuvKr }, { DataType::Double, "kb", StringId::Desc_Param_AnalogYuvKb }, { DataType::Double, "wu", StringId::Desc_Param_YuvWu } }, IntrinsicBridges::rgbToYuvBridge },
		{ StringId::Desc_Category_ColorSpace,				"rgbToYuv", StringId::Desc_Func_RgbToYuv, { { DataType::Double, "r", StringId::Desc_Param_ColorR }, { DataType::Double, "g", StringId::Desc_Param_ColorG }, { DataType::Double, "b", StringId::Desc_Param_ColorB }, { DataType::Double, "kr", StringId::Desc_Param_AnalogYuvKr }, { DataType::Double, "kb", StringId::Desc_Param_AnalogYuvKb }, { DataType::Double, "wu", StringId::Desc_Param_YuvWu }, { DataType::Double, "wv", StringId::Desc_Param_YuvWv } }, IntrinsicBridges::rgbToYuvBridge },
			
		{ StringId::Desc_Category_ColorSpace,				"yuvToRgb", StringId::Desc_Func_YuvToRgb, { { DataType::Double, "y", StringId::Desc_Param_ColorYuvY }, { DataType::Double, "u", StringId::Desc_Param_ColorYuvU }, { DataType::Double, "v", StringId::Desc_Param_ColorYuvV } }, IntrinsicBridges::yuvToRgbBridge },
		{ StringId::Desc_Category_ColorSpace,				"yuvToRgb", StringId::Desc_Func_YuvToRgb, { { DataType::Double, "y", StringId::Desc_Param_ColorYuvY }, { DataType::Double, "u", StringId::Desc_Param_ColorYuvU }, { DataType::Double, "v", StringId::Desc_Param_ColorYuvV }, { DataType::Double, "kr", StringId::Desc_Param_AnalogYuvKr } }, IntrinsicBridges::yuvToRgbBridge },
		{ StringId::Desc_Category_ColorSpace,				"yuvToRgb", StringId::Desc_Func_YuvToRgb, { { DataType::Double, "y", StringId::Desc_Param_ColorYuvY }, { DataType::Double, "u", StringId::Desc_Param_ColorYuvU }, { DataType::Double, "v", StringId::Desc_Param_ColorYuvV }, { DataType::Double, "kr", StringId::Desc_Param_AnalogYuvKr }, { DataType::Double, "kb", StringId::Desc_Param_AnalogYuvKb } }, IntrinsicBridges::yuvToRgbBridge },
		{ StringId::Desc_Category_ColorSpace,				"yuvToRgb", StringId::Desc_Func_YuvToRgb, { { DataType::Double, "y", StringId::Desc_Param_ColorYuvY }, { DataType::Double, "u", StringId::Desc_Param_ColorYuvU }, { DataType::Double, "v", StringId::Desc_Param_ColorYuvV }, { DataType::Double, "kr", StringId::Desc_Param_AnalogYuvKr }, { DataType::Double, "kb", StringId::Desc_Param_AnalogYuvKb }, { DataType::Double, "wu", StringId::Desc_Param_YuvWu } }, IntrinsicBridges::yuvToRgbBridge },
		{ StringId::Desc_Category_ColorSpace,				"yuvToRgb", StringId::Desc_Func_YuvToRgb, { { DataType::Double, "y", StringId::Desc_Param_ColorYuvY }, { DataType::Double, "u", StringId::Desc_Param_ColorYuvU }, { DataType::Double, "v", StringId::Desc_Param_ColorYuvV }, { DataType::Double, "kr", StringId::Desc_Param_AnalogYuvKr }, { DataType::Double, "kb", StringId::Desc_Param_AnalogYuvKb }, { DataType::Double, "wu", StringId::Desc_Param_YuvWu }, { DataType::Double, "wv", StringId::Desc_Param_YuvWv } }, IntrinsicBridges::yuvToRgbBridge },

		// == SciPy.
		{ StringId::Desc_Category_SciPyIntegrate,			"simpson", StringId::Desc_Math_Simpson, { { DataType::Object, "y", StringId::Math_Param_Y } }, IntrinsicBridges::simpsonBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"simpson", StringId::Desc_Math_Simpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "dx", StringId::Math_Param_Dx } }, IntrinsicBridges::simpsonBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"simpson", StringId::Desc_Math_Simpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "x", StringId::Math_Param_XArray } }, IntrinsicBridges::simpsonBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"simpson", StringId::Desc_Math_Simpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::UInt64, "start", StringId::Math_Param_Start }, { DataType::UInt64, "count", StringId::Math_Param_Count }, { DataType::Any, "stride", StringId::Math_Param_Stride } }, IntrinsicBridges::simpsonBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"simpson", StringId::Desc_Math_Simpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::UInt64, "start", StringId::Math_Param_Start }, { DataType::UInt64, "stride", StringId::Math_Param_Stride }, { DataType::Any, "x", StringId::Math_Param_XArray } }, IntrinsicBridges::simpsonBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"simpson", StringId::Desc_Math_Simpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::UInt64, "start", StringId::Math_Param_Start }, { DataType::UInt64, "count", StringId::Math_Param_Count }, { DataType::UInt64, "stride", StringId::Math_Param_Stride }, { DataType::Double, "dx", StringId::Math_Param_Dx } }, IntrinsicBridges::simpsonBridge },

		{ StringId::Desc_Category_SciPyIntegrate,			"cumulative_simpson", StringId::Desc_Math_CumulativeSimpson, { { DataType::Object, "y", StringId::Math_Param_Y } }, IntrinsicBridges::cumulativeSimpsonBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"cumulative_simpson", StringId::Desc_Math_CumulativeSimpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "dx", StringId::Math_Param_Dx } }, IntrinsicBridges::cumulativeSimpsonBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"cumulative_simpson", StringId::Desc_Math_CumulativeSimpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "dx", StringId::Math_Param_Dx }, { DataType::Any, "initial", StringId::Math_Param_Initial } }, IntrinsicBridges::cumulativeSimpsonBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"cumulative_simpson", StringId::Desc_Math_CumulativeSimpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "x", StringId::Math_Param_XArray } }, IntrinsicBridges::cumulativeSimpsonBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"cumulative_simpson", StringId::Desc_Math_CumulativeSimpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "x", StringId::Math_Param_XArray }, { DataType::Any, "initial", StringId::Math_Param_Initial } }, IntrinsicBridges::cumulativeSimpsonBridge },

		{ StringId::Desc_Category_SciPyIntegrate,			"trapezoid", StringId::Desc_Math_Trapezoid, { { DataType::Object, "y", StringId::Math_Param_Y } }, IntrinsicBridges::trapezoidBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"trapezoid", StringId::Desc_Math_Trapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "dx", StringId::Math_Param_Dx } }, IntrinsicBridges::trapezoidBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"trapezoid", StringId::Desc_Math_Trapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "x", StringId::Math_Param_XArray } }, IntrinsicBridges::trapezoidBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"trapezoid", StringId::Desc_Math_Trapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::UInt64, "start", StringId::Math_Param_Start }, { DataType::UInt64, "count", StringId::Math_Param_Count }, { DataType::Any, "stride", StringId::Math_Param_Stride } }, IntrinsicBridges::trapezoidBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"trapezoid", StringId::Desc_Math_Trapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::UInt64, "start", StringId::Math_Param_Start }, { DataType::UInt64, "stride", StringId::Math_Param_Stride }, { DataType::Any, "x", StringId::Math_Param_XArray } }, IntrinsicBridges::trapezoidBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"trapezoid", StringId::Desc_Math_Trapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::UInt64, "start", StringId::Math_Param_Start }, { DataType::UInt64, "count", StringId::Math_Param_Count }, { DataType::UInt64, "stride", StringId::Math_Param_Stride }, { DataType::Double, "dx", StringId::Math_Param_Dx } }, IntrinsicBridges::trapezoidBridge },

		{ StringId::Desc_Category_SciPyIntegrate,			"cumulative_trapezoid", StringId::Desc_Math_CumulativeTrapezoid, { { DataType::Object, "y", StringId::Math_Param_Y } }, IntrinsicBridges::cumulativeTrapezoidBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"cumulative_trapezoid", StringId::Desc_Math_CumulativeTrapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "dx", StringId::Math_Param_Dx } }, IntrinsicBridges::cumulativeTrapezoidBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"cumulative_trapezoid", StringId::Desc_Math_CumulativeTrapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "dx", StringId::Math_Param_Dx }, { DataType::Any, "initial", StringId::Math_Param_Initial } }, IntrinsicBridges::cumulativeTrapezoidBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"cumulative_trapezoid", StringId::Desc_Math_CumulativeTrapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "x", StringId::Math_Param_XArray } }, IntrinsicBridges::cumulativeTrapezoidBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"cumulative_trapezoid", StringId::Desc_Math_CumulativeTrapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "x", StringId::Math_Param_XArray }, { DataType::Any, "initial", StringId::Math_Param_Initial } }, IntrinsicBridges::cumulativeTrapezoidBridge },

		{ StringId::Desc_Category_SciPyIntegrate,			"romb", StringId::Desc_Math_Romb, { { DataType::Object, "y", StringId::Math_Param_Y } }, IntrinsicBridges::rombBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"romb", StringId::Desc_Math_Romb, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Double, "dx", StringId::Math_Param_Dx } }, IntrinsicBridges::rombBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"romb", StringId::Desc_Math_Romb, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::UInt64, "start", StringId::Math_Param_Start }, { DataType::UInt64, "count", StringId::Math_Param_Count }, { DataType::UInt64, "stride", StringId::Math_Param_Stride } }, IntrinsicBridges::rombBridge },
		{ StringId::Desc_Category_SciPyIntegrate,			"romb", StringId::Desc_Math_Romb, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::UInt64, "start", StringId::Math_Param_Start }, { DataType::UInt64, "count", StringId::Math_Param_Count }, { DataType::UInt64, "stride", StringId::Math_Param_Stride }, { DataType::Double, "dx", StringId::Math_Param_Dx } }, IntrinsicBridges::rombBridge },

		// == Windowing.
		{ StringId::Desc_Category_SciPySignalWindows,		"barthann", StringId::Desc_Math_BarthannWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::barthannBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"bartlett", StringId::Desc_Math_BartlettWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::bartlettBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"blackman", StringId::Desc_Math_BlackmanWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::blackmanBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"blackmanharris", StringId::Desc_Math_BlackmanHarrisWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::blackmanHarrisBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"blackmanhuttal", StringId::Desc_Math_BlackmanNuttalWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::blackmanNuttalBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"bohman", StringId::Desc_Math_BohmanWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::bohmanBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"boxcar", StringId::Desc_Math_BoxcarWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::boxcarBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"chebwin", StringId::Desc_Math_ChebwinWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "at", StringId::Desc_Param_Attenuation } }, IntrinsicBridges::chebwinBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"cosine", StringId::Desc_Math_CosineWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::cosineBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"dpss", StringId::Desc_Math_DpssWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "nw", StringId::Desc_Param_Nw }, { DataType::UInt64, "kMax", StringId::Desc_Param_KMax } }, IntrinsicBridges::dpssBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"exponential", StringId::Desc_Math_ExponentialWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "tau", StringId::Desc_Param_Tau }, { DataType::Double, "center", StringId::Desc_Param_Center } }, IntrinsicBridges::exponentialBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"flatTop", StringId::Desc_Math_FlatTopWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::flatTopBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"gaussian", StringId::Desc_Math_GaussianWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "sigma", StringId::Desc_Param_Sigma } }, IntrinsicBridges::gaussianBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"general_cosine", StringId::Desc_Math_GeneralCosineWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Any, "aVals", StringId::Desc_Param_AVals } }, IntrinsicBridges::generalCosineBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"general_gaussian", StringId::Desc_Math_GeneralGaussianWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "p", StringId::Desc_Param_P }, { DataType::Double, "sigma", StringId::Desc_Param_Sigma } }, IntrinsicBridges::generalGaussianBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"general_hamming", StringId::Desc_Math_GeneralHammingWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "alpha", StringId::Desc_Param_Alpha } }, IntrinsicBridges::generalHammingBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"hann", StringId::Desc_Math_HannWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::hannBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"hamming", StringId::Desc_Math_HammingWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::hammingBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"kaiser", StringId::Desc_Math_KaiserWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "beta", StringId::Desc_Param_Beta } }, IntrinsicBridges::kaiserBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"kaiser_bessel_derived", StringId::Desc_Math_KaiserBesselDerivedWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "beta", StringId::Desc_Param_Beta } }, IntrinsicBridges::kaiserBesselDerivedBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"lanczos", StringId::Desc_Math_LanczosWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::lanczosBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"nuttall", StringId::Desc_Math_NuttallWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::nuttallBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"parzen", StringId::Desc_Math_ParzenWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::parzenBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"taylor", StringId::Desc_Math_TaylorWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Int64, "nBar", StringId::Desc_Param_NBar }, { DataType::Double, "sll", StringId::Desc_Param_Sll }, { DataType::Any, "norm", StringId::Desc_Param_Norm } }, IntrinsicBridges::taylorBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"triang", StringId::Desc_Math_TriangWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::triangBridge },
		{ StringId::Desc_Category_SciPySignalWindows,		"tukey", StringId::Desc_Math_TukeyWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "alpha", StringId::Desc_Param_Alpha } }, IntrinsicBridges::tukeyBridge },

		// == NumPy.
		{ StringId::Desc_Category_NumPy,					"ones", StringId::Desc_Math_Ones, { { DataType::UInt64, "count", StringId::Math_Param_Count } }, IntrinsicBridges::onesBridge },
		{ StringId::Desc_Category_NumPy,					"ones_like", StringId::Desc_Math_OnesLike, { { DataType::Object, "ref", StringId::Math_Param_RefArray } }, IntrinsicBridges::onesLikeBridge },
		{ StringId::Desc_Category_NumPy,					"zeros", StringId::Desc_Math_Zeros, { { DataType::UInt64, "count", StringId::Math_Param_Count } }, IntrinsicBridges::zerosBridge },
		{ StringId::Desc_Category_NumPy,					"zeros_like", StringId::Desc_Math_ZerosLike, { { DataType::Object, "ref", StringId::Math_Param_RefArray } }, IntrinsicBridges::zerosLikeBridge },
		{ StringId::Desc_Category_NumPy,					"full", StringId::Desc_Math_Full, { { DataType::UInt64, "count", StringId::Math_Param_Count }, { DataType::Double, "fill_value", StringId::Math_Param_FillValue } }, IntrinsicBridges::fullBridge },
		{ StringId::Desc_Category_NumPy,					"full_like", StringId::Desc_Math_FullLike, { { DataType::Object, "ref", StringId::Math_Param_RefArray }, { DataType::Double, "fill_value", StringId::Math_Param_FillValue } }, IntrinsicBridges::fullLikeBridge },

		{ StringId::Desc_Category_NumPy,					"linspace", StringId::Desc_Math_Linspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop } }, IntrinsicBridges::linspaceBridge },
		{ StringId::Desc_Category_NumPy,					"linspace", StringId::Desc_Math_Linspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop }, { DataType::UInt64, "num", StringId::Math_Param_Num } }, IntrinsicBridges::linspaceBridge },
		{ StringId::Desc_Category_NumPy,					"linspace", StringId::Desc_Math_Linspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop }, { DataType::UInt64, "num", StringId::Math_Param_Num }, { DataType::Integer, "endpoint", StringId::Math_Param_Endpoint } }, IntrinsicBridges::linspaceBridge },

		{ StringId::Desc_Category_NumPy,					"logspace", StringId::Desc_Math_Logspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop } }, IntrinsicBridges::logspaceBridge },
		{ StringId::Desc_Category_NumPy,					"logspace", StringId::Desc_Math_Logspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop }, { DataType::UInt64, "num", StringId::Math_Param_Num } }, IntrinsicBridges::logspaceBridge },
		{ StringId::Desc_Category_NumPy,					"logspace", StringId::Desc_Math_Logspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop }, { DataType::UInt64, "num", StringId::Math_Param_Num }, { DataType::Integer, "endpoint", StringId::Math_Param_Endpoint } }, IntrinsicBridges::logspaceBridge },
		{ StringId::Desc_Category_NumPy,					"logspace", StringId::Desc_Math_Logspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop }, { DataType::UInt64, "num", StringId::Math_Param_Num }, { DataType::Integer, "endpoint", StringId::Math_Param_Endpoint }, { DataType::Double, "base", StringId::Math_Param_Base } }, IntrinsicBridges::logspaceBridge },

		{ StringId::Desc_Category_NumPy,					"geomspace", StringId::Desc_Math_Geomspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop } }, IntrinsicBridges::geomspaceBridge },
		{ StringId::Desc_Category_NumPy,					"geomspace", StringId::Desc_Math_Geomspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop }, { DataType::UInt64, "num", StringId::Math_Param_Num } }, IntrinsicBridges::geomspaceBridge },
		{ StringId::Desc_Category_NumPy,					"geomspace", StringId::Desc_Math_Geomspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop }, { DataType::UInt64, "num", StringId::Math_Param_Num }, { DataType::Integer, "endpoint", StringId::Math_Param_Endpoint } }, IntrinsicBridges::geomspaceBridge },

		{ StringId::Desc_Category_NumPy,					"arange", StringId::Desc_Math_Arange, { { DataType::Double, "stop", StringId::Math_Param_Stop } }, IntrinsicBridges::arangeBridge },
		{ StringId::Desc_Category_NumPy,					"arange", StringId::Desc_Math_Arange, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop } }, IntrinsicBridges::arangeBridge },
		{ StringId::Desc_Category_NumPy,					"arange", StringId::Desc_Math_Arange, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop }, { DataType::Double, "step", StringId::Math_Param_Step } }, IntrinsicBridges::arangeBridge },

		{ StringId::Desc_Category_NumPy,					"sum", StringId::Desc_Math_Sum, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::sumBridge },
		{ StringId::Desc_Category_NumPy,					"prod", StringId::Desc_Math_Prod, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::prodBridge },
		{ StringId::Desc_Category_NumPy,					"mean", StringId::Desc_Math_Mean, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::meanBridge },
		{ StringId::Desc_Category_NumPy,					"median", StringId::Desc_Math_Median, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::medianBridge },
		{ StringId::Desc_Category_NumPy,					"std", StringId::Desc_Math_Std, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::stdBridge },
		{ StringId::Desc_Category_NumPy,					"var", StringId::Desc_Math_Var, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::varBridge },
		{ StringId::Desc_Category_NumPy,					"ptp", StringId::Desc_Math_Ptp, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::ptpBridge },
		{ StringId::Desc_Category_NumPy,					"argMin", StringId::Desc_Math_ArgMin, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::argMinBridge },
		{ StringId::Desc_Category_NumPy,					"argMax", StringId::Desc_Math_ArgMax, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::argMaxBridge },
		{ StringId::Desc_Category_NumPy,					"percentile", StringId::Desc_Math_Percentile, { { DataType::Object, "v", StringId::Math_Param_V }, { DataType::Double, "q", StringId::Math_Param_PercentileQ } }, IntrinsicBridges::percentileBridge },

		{ StringId::Desc_Category_NumPy,					"diff", StringId::Desc_Math_Diff, { { DataType::Object, "x", StringId::Math_Param_V } }, IntrinsicBridges::diffBridge },
		{ StringId::Desc_Category_NumPy,					"diff", StringId::Desc_Math_Diff, { { DataType::Object, "x", StringId::Math_Param_V }, { DataType::UInt64, "n", StringId::Math_Param_DiffN } }, IntrinsicBridges::diffBridge },
		
		{ StringId::Desc_Category_NumPy,					"cumSum", StringId::Desc_Math_CumSum, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::cumSumBridge },
		{ StringId::Desc_Category_NumPy,					"cumProd", StringId::Desc_Math_CumProd, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::cumProdBridge },
		
		{ StringId::Desc_Category_NumPy,					"ediff1d", StringId::Desc_Math_Ediff1d, { { DataType::Object, "ary", StringId::Math_Param_V } }, IntrinsicBridges::ediff1dBridge },
		{ StringId::Desc_Category_NumPy,					"ediff1d", StringId::Desc_Math_Ediff1d, { { DataType::Object, "ary", StringId::Math_Param_V }, { DataType::Object, "to_begin", StringId::Math_Param_ToBegin } }, IntrinsicBridges::ediff1dBridge },
		{ StringId::Desc_Category_NumPy,					"ediff1d", StringId::Desc_Math_Ediff1d, { { DataType::Object, "ary", StringId::Math_Param_V }, { DataType::Object, "to_begin", StringId::Math_Param_ToBegin }, { DataType::Object, "to_end", StringId::Math_Param_ToEnd } }, IntrinsicBridges::ediff1dBridge },

		{ StringId::Desc_Category_NumPy,					"clip", StringId::Desc_Math_Clip, { { DataType::Object, "v", StringId::Math_Param_V }, { DataType::Double, "minVal", StringId::Math_Param_MinVal }, { DataType::Double, "maxVal", StringId::Math_Param_MaxVal } }, IntrinsicBridges::clipBridge },
		{ StringId::Desc_Category_NumPy,					"roll", StringId::Desc_Math_Roll, { { DataType::Object, "v", StringId::Math_Param_V }, { DataType::Integer, "shift", StringId::Math_Param_Shift } }, IntrinsicBridges::rollBridge },
		{ StringId::Desc_Category_NumPy,					"concatenate", StringId::Desc_Math_Concatenate, { { DataType::Object, "v1", StringId::Math_Param_V }, { DataType::Object, "v2", StringId::Math_Param_V2 } }, IntrinsicBridges::concatenateBridge },
		{ StringId::Desc_Category_NumPy,					"repeat", StringId::Desc_Math_Repeat, { { DataType::Object, "v", StringId::Math_Param_V }, { DataType::UInt64, "repeats", StringId::Math_Param_Repeats } }, IntrinsicBridges::repeatBridge },
		{ StringId::Desc_Category_NumPy,					"tile", StringId::Desc_Math_Tile, { { DataType::Object, "v", StringId::Math_Param_V }, { DataType::UInt64, "reps", StringId::Math_Param_Repeats } }, IntrinsicBridges::tileBridge },
		{ StringId::Desc_Category_NumPy,					"pad", StringId::Desc_Math_Pad, { { DataType::Object, "v", StringId::Math_Param_V }, { DataType::UInt64, "padLeft", StringId::Math_Param_PadLeft }, { DataType::UInt64, "padRight", StringId::Math_Param_PadRight }, { DataType::Double, "constantValue", StringId::Math_Param_ConstantValue } }, IntrinsicBridges::padBridge },

		{ StringId::Desc_Category_NumPy,					"convolve", StringId::Desc_Math_Convolve, { { DataType::Object, "v1", StringId::Math_Param_V1 }, { DataType::Object, "v2", StringId::Math_Param_V2 } }, IntrinsicBridges::convolveBridge },
		{ StringId::Desc_Category_NumPy,					"correlate", StringId::Desc_Math_Correlate, { { DataType::Object, "a", StringId::Math_Param_A }, { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::correlateBridge },
		{ StringId::Desc_Category_NumPy,					"interp", StringId::Desc_Math_Interp, { { DataType::Object, "x", StringId::Math_Param_XInterp }, { DataType::Object, "xp", StringId::Math_Param_Xp }, { DataType::Object, "fp", StringId::Math_Param_Fp } }, IntrinsicBridges::interpBridge },

		// == DSP.
		{ StringId::Desc_Category_DSP,						"sinc_filter_lpf", StringId::Desc_Math_SincFilterLpf, { { DataType::Double, "hz", StringId::Desc_Param_Hz }, { DataType::Double, "fc", StringId::Desc_Param_Fc }, { DataType::UInt64, "m", StringId::Desc_Param_FilterWidthM } }, IntrinsicBridges::sincFilterLpfBridge },
		{ StringId::Desc_Category_DSP,						"sinc_filter_hpf", StringId::Desc_Math_SincFilterHpf, { { DataType::Double, "hz", StringId::Desc_Param_Hz }, { DataType::Double, "fc", StringId::Desc_Param_Fc }, { DataType::UInt64, "m", StringId::Desc_Param_FilterWidthM } }, IntrinsicBridges::sincFilterHpfBridge },
		{ StringId::Desc_Category_DSP,						"sinc_filter_bpf", StringId::Desc_Math_SincFilterBpf, { { DataType::Double, "hz", StringId::Desc_Param_Hz }, { DataType::Double, "f1", StringId::Desc_Param_F1 }, { DataType::Double, "f2", StringId::Desc_Param_F2 }, { DataType::UInt64, "m", StringId::Desc_Param_FilterWidthM } }, IntrinsicBridges::sincFilterBpfBridge },



#include "SimdBridgeTable.inl"

		// MIPS SIMD (__msa_*).
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_add_a_b",	StringId::Desc_Simd_MsaAddA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddAB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_add_a_h",	StringId::Desc_Simd_MsaAddA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddAH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_add_a_w",	StringId::Desc_Simd_MsaAddA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddAW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_add_a_d",	StringId::Desc_Simd_MsaAddA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddAD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_adds_s_b",	StringId::Desc_Simd_MsaAddsS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddsSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_adds_s_h",	StringId::Desc_Simd_MsaAddsS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddsSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_adds_s_w",	StringId::Desc_Simd_MsaAddsS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddsSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_adds_s_d",	StringId::Desc_Simd_MsaAddsS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddsSD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_adds_u_b",	StringId::Desc_Simd_MsaAddsU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddsUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_adds_u_h",	StringId::Desc_Simd_MsaAddsU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddsUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_adds_u_w",	StringId::Desc_Simd_MsaAddsU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddsUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_adds_u_d",	StringId::Desc_Simd_MsaAddsU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddsUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_adds_a_b",	StringId::Desc_Simd_MsaAddsA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddsAB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_adds_a_h",	StringId::Desc_Simd_MsaAddsA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddsAH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_adds_a_w",	StringId::Desc_Simd_MsaAddsA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddsAW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_adds_a_d",	StringId::Desc_Simd_MsaAddsA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddsAD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_addv_b",		StringId::Desc_Simd_MsaAddv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddvB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_addv_h",		StringId::Desc_Simd_MsaAddv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddvH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_addv_w",		StringId::Desc_Simd_MsaAddv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddvW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_addv_d",		StringId::Desc_Simd_MsaAddv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAddvD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_addvi_b",	StringId::Desc_Simd_MsaAddvi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaAddviB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_addvi_h",	StringId::Desc_Simd_MsaAddvi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaAddviH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_addvi_w",	StringId::Desc_Simd_MsaAddvi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaAddviW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_addvi_d",	StringId::Desc_Simd_MsaAddvi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaAddviD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_and_v",		StringId::Desc_Simd_MsaAndV,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAndV },
		
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_andi_b",		StringId::Desc_Simd_MsaAndi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaAndiB },
		
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_asub_s_b",	StringId::Desc_Simd_MsaAsubS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAsubSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_asub_s_h",	StringId::Desc_Simd_MsaAsubS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAsubSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_asub_s_w",	StringId::Desc_Simd_MsaAsubS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAsubSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_asub_s_d",	StringId::Desc_Simd_MsaAsubS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAsubSD },
		
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_asub_u_b",	StringId::Desc_Simd_MsaAsubU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAsubUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_asub_u_h",	StringId::Desc_Simd_MsaAsubU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAsubUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_asub_u_w",	StringId::Desc_Simd_MsaAsubU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAsubUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_asub_u_d",	StringId::Desc_Simd_MsaAsubU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAsubUD },
		
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ave_s_b",	StringId::Desc_Simd_MsaAveS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAveSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ave_s_h",	StringId::Desc_Simd_MsaAveS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAveSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ave_s_w",	StringId::Desc_Simd_MsaAveS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAveSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ave_s_d",	StringId::Desc_Simd_MsaAveS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAveSD },
		
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ave_u_b",	StringId::Desc_Simd_MsaAveU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAveUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ave_u_h",	StringId::Desc_Simd_MsaAveU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAveUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ave_u_w",	StringId::Desc_Simd_MsaAveU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAveUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ave_u_d",	StringId::Desc_Simd_MsaAveU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAveUD },
		
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_aver_s_b",	StringId::Desc_Simd_MsaAverS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAverSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_aver_s_h",	StringId::Desc_Simd_MsaAverS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAverSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_aver_s_w",	StringId::Desc_Simd_MsaAverS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAverSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_aver_s_d",	StringId::Desc_Simd_MsaAverS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAverSD },
		
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_aver_u_b",	StringId::Desc_Simd_MsaAverU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAverUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_aver_u_h",	StringId::Desc_Simd_MsaAverU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAverUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_aver_u_w",	StringId::Desc_Simd_MsaAverU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAverUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_aver_u_d",	StringId::Desc_Simd_MsaAverU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaAverUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bclr_b",		StringId::Desc_Simd_MsaBclr,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaBclrB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bclr_h",		StringId::Desc_Simd_MsaBclr,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaBclrH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bclr_w",		StringId::Desc_Simd_MsaBclr,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaBclrW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bclr_d",		StringId::Desc_Simd_MsaBclr,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaBclrD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bclri_b",	StringId::Desc_Simd_MsaBclri,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBclriB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bclri_h",	StringId::Desc_Simd_MsaBclri,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBclriH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bclri_w",	StringId::Desc_Simd_MsaBclri,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBclriW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bclri_d",	StringId::Desc_Simd_MsaBclri,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBclriD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_binsl_b",	StringId::Desc_Simd_MsaBinsl,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaBinslB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_binsl_h",	StringId::Desc_Simd_MsaBinsl,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaBinslH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_binsl_w",	StringId::Desc_Simd_MsaBinsl,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaBinslW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_binsl_d",	StringId::Desc_Simd_MsaBinsl,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaBinslD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_binsli_b",	StringId::Desc_Simd_MsaBinsli,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBinsliB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_binsli_h",	StringId::Desc_Simd_MsaBinsli,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBinsliH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_binsli_w",	StringId::Desc_Simd_MsaBinsli,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBinsliW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_binsli_d",	StringId::Desc_Simd_MsaBinsli,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBinsliD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_binsr_b",	StringId::Desc_Simd_MsaBinsr,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaBinsrB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_binsr_h",	StringId::Desc_Simd_MsaBinsr,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaBinsrH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_binsr_w",	StringId::Desc_Simd_MsaBinsr,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaBinsrW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_binsr_d",	StringId::Desc_Simd_MsaBinsr,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaBinsrD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_binsri_b",	StringId::Desc_Simd_MsaBinsri,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBinsriB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_binsri_h",	StringId::Desc_Simd_MsaBinsri,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBinsriH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_binsri_w",	StringId::Desc_Simd_MsaBinsri,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBinsriW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_binsri_d",	StringId::Desc_Simd_MsaBinsri,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBinsriD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bmnz_v",		StringId::Desc_Simd_MsaBmnz,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaBmnzV },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bmnzi_b",	StringId::Desc_Simd_MsaBmnzi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBmnziB },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bmz_v",		StringId::Desc_Simd_MsaBmz,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaBmzV },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bmzi_b",		StringId::Desc_Simd_MsaBmzi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBmziB },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bneg_b",		StringId::Desc_Simd_MsaBneg,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaBnegB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bneg_h",		StringId::Desc_Simd_MsaBneg,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaBnegH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bneg_w",		StringId::Desc_Simd_MsaBneg,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaBnegW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bneg_d",		StringId::Desc_Simd_MsaBneg,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaBnegD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bnegi_b",	StringId::Desc_Simd_MsaBnegi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBnegiB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bnegi_h",	StringId::Desc_Simd_MsaBnegi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBnegiH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bnegi_w",	StringId::Desc_Simd_MsaBnegi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBnegiW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bnegi_d",	StringId::Desc_Simd_MsaBnegi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBnegiD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bsel_v",		StringId::Desc_Simd_MsaBsel,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaBselV },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bseli_b",	StringId::Desc_Simd_MsaBseli,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBseliB },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bset_b",		StringId::Desc_Simd_MsaBset,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaBsetB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bset_h",		StringId::Desc_Simd_MsaBset,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaBsetH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bset_w",		StringId::Desc_Simd_MsaBset,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaBsetW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bset_d",		StringId::Desc_Simd_MsaBset,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaBsetD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bseti_b",	StringId::Desc_Simd_MsaBseti,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBsetiB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bseti_h",	StringId::Desc_Simd_MsaBseti,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBsetiH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bseti_w",	StringId::Desc_Simd_MsaBseti,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBsetiW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_bseti_d",	StringId::Desc_Simd_MsaBseti,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaBsetiD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_cast_to_scalar_double",	StringId::Desc_Simd_MsaCastToScalarDouble,	{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaCastToScalarDouble },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_cast_to_scalar_float",		StringId::Desc_Simd_MsaCastToScalarFloat,	{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaCastToScalarFloat },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_cast_to_vector_double",	StringId::Desc_Simd_MsaCastToVectorDouble,	{ { DataType::Double, "val", StringId::Simd_Param_Val } }, IntrinsicBridges::bridgeMsaCastToVectorDouble },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_cast_to_vector_float",		StringId::Desc_Simd_MsaCastToVectorFloat,	{ { DataType::Float, "val", StringId::Simd_Param_Val } }, IntrinsicBridges::bridgeMsaCastToVectorFloat },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ceq_b",		StringId::Desc_Simd_MsaCeq,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCeqB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ceq_h",		StringId::Desc_Simd_MsaCeq,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCeqH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ceq_w",		StringId::Desc_Simd_MsaCeq,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCeqW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ceq_d",		StringId::Desc_Simd_MsaCeq,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCeqD },
	
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ceqi_b",		StringId::Desc_Simd_MsaCeqi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCeqiB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ceqi_h",		StringId::Desc_Simd_MsaCeqi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCeqiH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ceqi_w",		StringId::Desc_Simd_MsaCeqi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCeqiW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ceqi_d",		StringId::Desc_Simd_MsaCeqi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCeqiD },
		
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_cfcmsa",		StringId::Desc_Simd_MsaCfcmsa,		{ { DataType::Integer, "cs", StringId::Simd_Param_Cs } }, IntrinsicBridges::bridgeMsaCfcmsa },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_cle_s_b",	StringId::Desc_Simd_MsaCleS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCleSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_cle_s_h",	StringId::Desc_Simd_MsaCleS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCleSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_cle_s_w",	StringId::Desc_Simd_MsaCleS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCleSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_cle_s_d",	StringId::Desc_Simd_MsaCleS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCleSD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_cle_u_b",	StringId::Desc_Simd_MsaCleU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCleUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_cle_u_h",	StringId::Desc_Simd_MsaCleU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCleUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_cle_u_w",	StringId::Desc_Simd_MsaCleU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCleUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_cle_u_d",	StringId::Desc_Simd_MsaCleU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCleUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clei_s_b",	StringId::Desc_Simd_MsaCleiS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCleiSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clei_s_h",	StringId::Desc_Simd_MsaCleiS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCleiSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clei_s_w",	StringId::Desc_Simd_MsaCleiS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCleiSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clei_s_d",	StringId::Desc_Simd_MsaCleiS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCleiSD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clei_u_b",	StringId::Desc_Simd_MsaCleiU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCleiUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clei_u_h",	StringId::Desc_Simd_MsaCleiU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCleiUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clei_u_w",	StringId::Desc_Simd_MsaCleiU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCleiUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clei_u_d",	StringId::Desc_Simd_MsaCleiU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCleiUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clt_s_b",	StringId::Desc_Simd_MsaClt,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCltSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clt_s_h",	StringId::Desc_Simd_MsaClt,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCltSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clt_s_w",	StringId::Desc_Simd_MsaClt,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCltSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clt_s_d",	StringId::Desc_Simd_MsaClt,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCltSD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clt_u_b",	StringId::Desc_Simd_MsaClt,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCltUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clt_u_h",	StringId::Desc_Simd_MsaClt,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCltUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clt_u_w",	StringId::Desc_Simd_MsaClt,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCltUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clt_u_d",	StringId::Desc_Simd_MsaClt,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaCltUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clti_s_b",	StringId::Desc_Simd_MsaClti,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCltiSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clti_s_h",	StringId::Desc_Simd_MsaClti,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCltiSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clti_s_w",	StringId::Desc_Simd_MsaClti,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCltiSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clti_s_d",	StringId::Desc_Simd_MsaClti,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCltiSD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clti_u_b",	StringId::Desc_Simd_MsaClti,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCltiUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clti_u_h",	StringId::Desc_Simd_MsaClti,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCltiUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clti_u_w",	StringId::Desc_Simd_MsaClti,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCltiUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_clti_u_d",	StringId::Desc_Simd_MsaClti,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaCltiUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_copy_s_b",	StringId::Desc_Simd_MsaCopy,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "index", StringId::Simd_Param_Index } }, IntrinsicBridges::bridgeMsaCopySB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_copy_s_h",	StringId::Desc_Simd_MsaCopy,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "index", StringId::Simd_Param_Index } }, IntrinsicBridges::bridgeMsaCopySH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_copy_s_w",	StringId::Desc_Simd_MsaCopy,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "index", StringId::Simd_Param_Index } }, IntrinsicBridges::bridgeMsaCopySW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_copy_s_d",	StringId::Desc_Simd_MsaCopy,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "index", StringId::Simd_Param_Index } }, IntrinsicBridges::bridgeMsaCopySD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_copy_u_b",	StringId::Desc_Simd_MsaCopy,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "index", StringId::Simd_Param_Index } }, IntrinsicBridges::bridgeMsaCopyUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_copy_u_h",	StringId::Desc_Simd_MsaCopy,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "index", StringId::Simd_Param_Index } }, IntrinsicBridges::bridgeMsaCopyUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_copy_u_w",	StringId::Desc_Simd_MsaCopy,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "index", StringId::Simd_Param_Index } }, IntrinsicBridges::bridgeMsaCopyUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_copy_u_d",	StringId::Desc_Simd_MsaCopy,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "index", StringId::Simd_Param_Index } }, IntrinsicBridges::bridgeMsaCopyUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_div_s_b",	StringId::Desc_Simd_MsaDiv,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDivSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_div_s_h",	StringId::Desc_Simd_MsaDiv,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDivSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_div_s_w",	StringId::Desc_Simd_MsaDiv,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDivSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_div_s_d",	StringId::Desc_Simd_MsaDiv,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDivSD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_div_u_b",	StringId::Desc_Simd_MsaDiv,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDivUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_div_u_h",	StringId::Desc_Simd_MsaDiv,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDivUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_div_u_w",	StringId::Desc_Simd_MsaDiv,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDivUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_div_u_d",	StringId::Desc_Simd_MsaDiv,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDivUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dotp_s_h",	StringId::Desc_Simd_MsaDotpS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDotpSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dotp_s_w",	StringId::Desc_Simd_MsaDotpS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDotpSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dotp_s_d",	StringId::Desc_Simd_MsaDotpS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDotpSD },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dotp_u_h",	StringId::Desc_Simd_MsaDotpU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDotpUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dotp_u_w",	StringId::Desc_Simd_MsaDotpU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDotpUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dotp_u_d",	StringId::Desc_Simd_MsaDotpU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDotpUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dpadd_s_h",	StringId::Desc_Simd_MsaDpaddS,		{ { DataType::Object, "c", StringId::Simd_Param_C }, { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDpaddSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dpadd_s_w",	StringId::Desc_Simd_MsaDpaddS,		{ { DataType::Object, "c", StringId::Simd_Param_C }, { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDpaddSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dpadd_s_d",	StringId::Desc_Simd_MsaDpaddS,		{ { DataType::Object, "c", StringId::Simd_Param_C }, { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDpaddSD },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dpadd_u_h",	StringId::Desc_Simd_MsaDpaddU,		{ { DataType::Object, "c", StringId::Simd_Param_C }, { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDpaddUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dpadd_u_w",	StringId::Desc_Simd_MsaDpaddU,		{ { DataType::Object, "c", StringId::Simd_Param_C }, { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDpaddUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dpadd_u_d",	StringId::Desc_Simd_MsaDpaddU,		{ { DataType::Object, "c", StringId::Simd_Param_C }, { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDpaddUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dpsub_s_h",	StringId::Desc_Simd_MsaDpsubS,		{ { DataType::Object, "c", StringId::Simd_Param_C }, { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDpsubSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dpsub_s_w",	StringId::Desc_Simd_MsaDpsubS,		{ { DataType::Object, "c", StringId::Simd_Param_C }, { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDpsubSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dpsub_s_d",	StringId::Desc_Simd_MsaDpsubS,		{ { DataType::Object, "c", StringId::Simd_Param_C }, { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDpsubSD },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dpsub_u_h",	StringId::Desc_Simd_MsaDpsubU,		{ { DataType::Object, "c", StringId::Simd_Param_C }, { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDpsubUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dpsub_u_w",	StringId::Desc_Simd_MsaDpsubU,		{ { DataType::Object, "c", StringId::Simd_Param_C }, { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDpsubUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_dpsub_u_d",	StringId::Desc_Simd_MsaDpsubU,		{ { DataType::Object, "c", StringId::Simd_Param_C }, { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaDpsubUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fadd_w",		StringId::Desc_Simd_MsaFadd,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFaddW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fadd_d",		StringId::Desc_Simd_MsaFadd,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFaddD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcaf_w",		StringId::Desc_Simd_MsaFcaf,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcafW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcaf_d",		StringId::Desc_Simd_MsaFcaf,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcafD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fceq_w",		StringId::Desc_Simd_MsaFceq,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFceqW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fceq_d",		StringId::Desc_Simd_MsaFceq,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFceqD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fclass_w",	StringId::Desc_Simd_MsaFclass,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFclassW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fclass_d",	StringId::Desc_Simd_MsaFclass,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFclassD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcle_w",		StringId::Desc_Simd_MsaFcle,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcleW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcle_d",		StringId::Desc_Simd_MsaFcle,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcleD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fclt_w",		StringId::Desc_Simd_MsaFclt,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcltW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fclt_d",		StringId::Desc_Simd_MsaFclt,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcltD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcne_w",		StringId::Desc_Simd_MsaFcne,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcneW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcne_d",		StringId::Desc_Simd_MsaFcne,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcneD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcor_w",		StringId::Desc_Simd_MsaFcor,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcorW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcor_d",		StringId::Desc_Simd_MsaFcor,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcorD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcueq_w",	StringId::Desc_Simd_MsaFcueq,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcueqW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcueq_d",	StringId::Desc_Simd_MsaFcueq,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcueqD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcule_w",	StringId::Desc_Simd_MsaFcule,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFculeW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcule_d",	StringId::Desc_Simd_MsaFcule,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFculeD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcult_w",	StringId::Desc_Simd_MsaFcult,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcultW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcult_d",	StringId::Desc_Simd_MsaFcult,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcultD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcun_w",		StringId::Desc_Simd_MsaFcun,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcunW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcun_d",		StringId::Desc_Simd_MsaFcun,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcunD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcune_w",	StringId::Desc_Simd_MsaFcune,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcuneW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fcune_d",	StringId::Desc_Simd_MsaFcune,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFcuneD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fdiv_w",		StringId::Desc_Simd_MsaFdiv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFdivW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fdiv_d",		StringId::Desc_Simd_MsaFdiv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFdivD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fexdo_h",	StringId::Desc_Simd_MsaFexdo,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFexdoH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fexdo_w",	StringId::Desc_Simd_MsaFexdo,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFexdoW },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fexp2_w",	StringId::Desc_Simd_MsaFexp2,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFexp2W },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fexp2_d",	StringId::Desc_Simd_MsaFexp2,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFexp2D },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fexupl_w",	StringId::Desc_Simd_MsaFexupl,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFexuplW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fexupl_d",	StringId::Desc_Simd_MsaFexupl,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFexuplD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fexupr_w",	StringId::Desc_Simd_MsaFexupr,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFexuprW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fexupr_d",	StringId::Desc_Simd_MsaFexupr,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFexuprD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ffint_s_w",	StringId::Desc_Simd_MsaFfintS,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFfintSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ffint_s_d",	StringId::Desc_Simd_MsaFfintS,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFfintSD },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ffint_u_w",	StringId::Desc_Simd_MsaFfintU,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFfintUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ffint_u_d",	StringId::Desc_Simd_MsaFfintU,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFfintUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ffql_w",		StringId::Desc_Simd_MsaFfql,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFfqlW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ffql_d",		StringId::Desc_Simd_MsaFfql,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFfqlD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ffqr_w",		StringId::Desc_Simd_MsaFfqr,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFfqrW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ffqr_d",		StringId::Desc_Simd_MsaFfqr,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFfqrD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fill_b",		StringId::Desc_Simd_MsaFill,		{ { DataType::Int64, "val", StringId::Simd_Param_Val } }, IntrinsicBridges::bridgeMsaFillB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fill_h",		StringId::Desc_Simd_MsaFill,		{ { DataType::Int64, "val", StringId::Simd_Param_Val } }, IntrinsicBridges::bridgeMsaFillH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fill_w",		StringId::Desc_Simd_MsaFill,		{ { DataType::Int64, "val", StringId::Simd_Param_Val } }, IntrinsicBridges::bridgeMsaFillW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fill_d",		StringId::Desc_Simd_MsaFill,		{ { DataType::Int64, "val", StringId::Simd_Param_Val } }, IntrinsicBridges::bridgeMsaFillD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_flog2_w",	StringId::Desc_Simd_MsaFlog2,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFlog2W },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_flog2_d",	StringId::Desc_Simd_MsaFlog2,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFlog2D },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fmadd_w",	StringId::Desc_Simd_MsaFmadd,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaFmaddW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fmadd_d",	StringId::Desc_Simd_MsaFmadd,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaFmaddD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fmax_w",		StringId::Desc_Simd_MsaFmax,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFmaxW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fmax_d",		StringId::Desc_Simd_MsaFmax,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFmaxD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fmax_a_w",	StringId::Desc_Simd_MsaFmaxA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFmaxAW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fmax_a_d",	StringId::Desc_Simd_MsaFmaxA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFmaxAD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fmin_w",		StringId::Desc_Simd_MsaFmin,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFminW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fmin_d",		StringId::Desc_Simd_MsaFmin,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFminD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fmin_a_w",	StringId::Desc_Simd_MsaFminA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFminAW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fmin_a_d",	StringId::Desc_Simd_MsaFminA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFminAD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fmsub_w",	StringId::Desc_Simd_MsaFmsub,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaFmsubW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fmsub_d",	StringId::Desc_Simd_MsaFmsub,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaFmsubD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fmul_w",		StringId::Desc_Simd_MsaFmul,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFmulW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fmul_d",		StringId::Desc_Simd_MsaFmul,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFmulD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_frcp_w",		StringId::Desc_Simd_MsaFrcp,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFrcpW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_frcp_d",		StringId::Desc_Simd_MsaFrcp,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFrcpD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_frint_w",	StringId::Desc_Simd_MsaFrint,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFrintW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_frint_d",	StringId::Desc_Simd_MsaFrint,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFrintD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_frsqrt_w",	StringId::Desc_Simd_MsaFrsqrt,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFrsqrtW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_frsqrt_d",	StringId::Desc_Simd_MsaFrsqrt,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFrsqrtD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsaf_w",		StringId::Desc_Simd_MsaFsaf,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsafW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsaf_d",		StringId::Desc_Simd_MsaFsaf,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsafD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fseq_w",		StringId::Desc_Simd_MsaFseq,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFseqW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fseq_d",		StringId::Desc_Simd_MsaFseq,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFseqD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsle_w",		StringId::Desc_Simd_MsaFsle,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsleW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsle_d",		StringId::Desc_Simd_MsaFsle,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsleD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fslt_w",		StringId::Desc_Simd_MsaFslt,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsltW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fslt_d",		StringId::Desc_Simd_MsaFslt,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsltD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsne_w",		StringId::Desc_Simd_MsaFsne,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsneW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsne_d",		StringId::Desc_Simd_MsaFsne,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsneD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsor_w",		StringId::Desc_Simd_MsaFsor,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsorW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsor_d",		StringId::Desc_Simd_MsaFsor,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsorD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsqrt_w",	StringId::Desc_Simd_MsaFsqrt,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFsqrtW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsqrt_d",	StringId::Desc_Simd_MsaFsqrt,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFsqrtD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsub_w",		StringId::Desc_Simd_MsaFsub,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsubW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsub_d",		StringId::Desc_Simd_MsaFsub,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsubD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsueq_w",	StringId::Desc_Simd_MsaFsueq,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsueqW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsueq_d",	StringId::Desc_Simd_MsaFsueq,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsueqD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsule_w",	StringId::Desc_Simd_MsaFsule,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsuleW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsule_d",	StringId::Desc_Simd_MsaFsule,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsuleD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsult_w",		StringId::Desc_Simd_MsaFsult,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsultW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsult_d",		StringId::Desc_Simd_MsaFsult,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsultD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsun_w",			StringId::Desc_Simd_MsaFsun,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsunW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsun_d",			StringId::Desc_Simd_MsaFsun,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsunD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsune_w",		StringId::Desc_Simd_MsaFsune,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsuneW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_fsune_d",		StringId::Desc_Simd_MsaFsune,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFsuneD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ftint_s_w",		StringId::Desc_Simd_MsaFtintS,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFtintSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ftint_s_d",		StringId::Desc_Simd_MsaFtintS,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFtintSD },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ftint_u_w",		StringId::Desc_Simd_MsaFtintU,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFtintUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ftint_u_d",		StringId::Desc_Simd_MsaFtintU,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFtintUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ftq_h",			StringId::Desc_Simd_MsaFtq,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFtqH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ftq_w",			StringId::Desc_Simd_MsaFtq,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaFtqW },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ftrunc_s_w",		StringId::Desc_Simd_MsaFtruncS,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFtruncSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ftrunc_s_d",		StringId::Desc_Simd_MsaFtruncS,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFtruncSD },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ftrunc_u_w",		StringId::Desc_Simd_MsaFtruncU,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFtruncUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ftrunc_u_d",		StringId::Desc_Simd_MsaFtruncU,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaFtruncUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_hadd_s_h",		StringId::Desc_Simd_MsaHaddS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaHaddSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_hadd_s_w",		StringId::Desc_Simd_MsaHaddS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaHaddSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_hadd_s_d",		StringId::Desc_Simd_MsaHaddS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaHaddSD },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_hadd_u_h",		StringId::Desc_Simd_MsaHaddU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaHaddUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_hadd_u_w",		StringId::Desc_Simd_MsaHaddU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaHaddUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_hadd_u_d",		StringId::Desc_Simd_MsaHaddU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaHaddUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_hsub_s_h",		StringId::Desc_Simd_MsaHsubS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaHsubSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_hsub_s_w",		StringId::Desc_Simd_MsaHsubS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaHsubSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_hsub_s_d",		StringId::Desc_Simd_MsaHsubS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaHsubSD },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_hsub_u_h",		StringId::Desc_Simd_MsaHsubU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaHsubUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_hsub_u_w",		StringId::Desc_Simd_MsaHsubU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaHsubUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_hsub_u_d",		StringId::Desc_Simd_MsaHsubU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaHsubUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ilvev_b",	StringId::Desc_Simd_MsaIlvev,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaIlvevB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ilvev_h",	StringId::Desc_Simd_MsaIlvev,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaIlvevH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ilvev_w",	StringId::Desc_Simd_MsaIlvev,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaIlvevW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ilvev_d",	StringId::Desc_Simd_MsaIlvev,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaIlvevD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ilvl_b",		StringId::Desc_Simd_MsaIlvl,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaIlvlB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ilvl_h",		StringId::Desc_Simd_MsaIlvl,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaIlvlH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ilvl_w",		StringId::Desc_Simd_MsaIlvl,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaIlvlW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ilvl_d",		StringId::Desc_Simd_MsaIlvl,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaIlvlD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ilvod_b",	StringId::Desc_Simd_MsaIlvod,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaIlvodB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ilvod_h",	StringId::Desc_Simd_MsaIlvod,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaIlvodH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ilvod_w",	StringId::Desc_Simd_MsaIlvod,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaIlvodW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ilvod_d",	StringId::Desc_Simd_MsaIlvod,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaIlvodD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ilvr_b",		StringId::Desc_Simd_MsaIlvr,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaIlvrB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ilvr_h",		StringId::Desc_Simd_MsaIlvr,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaIlvrH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ilvr_w",		StringId::Desc_Simd_MsaIlvr,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaIlvrW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ilvr_d",		StringId::Desc_Simd_MsaIlvr,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaIlvrD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_insert_b",	StringId::Desc_Simd_MsaInsert,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Any, "lane", StringId::Simd_Param_Lane }, { DataType::Any, "val", StringId::Simd_Param_Val } }, IntrinsicBridges::bridgeMsaInsertB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_insert_h",	StringId::Desc_Simd_MsaInsert,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Any, "lane", StringId::Simd_Param_Lane }, { DataType::Any, "val", StringId::Simd_Param_Val } }, IntrinsicBridges::bridgeMsaInsertH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_insert_w",	StringId::Desc_Simd_MsaInsert,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Any, "lane", StringId::Simd_Param_Lane }, { DataType::Any, "val", StringId::Simd_Param_Val } }, IntrinsicBridges::bridgeMsaInsertW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_insert_d",	StringId::Desc_Simd_MsaInsert,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Any, "lane", StringId::Simd_Param_Lane }, { DataType::Any, "val", StringId::Simd_Param_Val } }, IntrinsicBridges::bridgeMsaInsertD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_insve_b",	StringId::Desc_Simd_MsaInsve,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Any, "lane", StringId::Simd_Param_Lane }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaInsveB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_insve_h",	StringId::Desc_Simd_MsaInsve,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Any, "lane", StringId::Simd_Param_Lane }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaInsveH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_insve_w",	StringId::Desc_Simd_MsaInsve,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Any, "lane", StringId::Simd_Param_Lane }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaInsveW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_insve_d",	StringId::Desc_Simd_MsaInsve,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Any, "lane", StringId::Simd_Param_Lane }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaInsveD },

		/*
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ld_b",		StringId::Desc_Simd_MsaLd,			{ { DataType::Pointer, "ptr", StringId::Simd_Param_Ptr }, { DataType::Any, "offset", StringId::Simd_Param_Offset } }, IntrinsicBridges::bridgeMsaLdB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ld_h",		StringId::Desc_Simd_MsaLd,			{ { DataType::Pointer, "ptr", StringId::Simd_Param_Ptr }, { DataType::Any, "offset", StringId::Simd_Param_Offset } }, IntrinsicBridges::bridgeMsaLdH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ld_w",		StringId::Desc_Simd_MsaLd,			{ { DataType::Pointer, "ptr", StringId::Simd_Param_Ptr }, { DataType::Any, "offset", StringId::Simd_Param_Offset } }, IntrinsicBridges::bridgeMsaLdW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ld_d",		StringId::Desc_Simd_MsaLd,			{ { DataType::Pointer, "ptr", StringId::Simd_Param_Ptr }, { DataType::Any, "offset", StringId::Simd_Param_Offset } }, IntrinsicBridges::bridgeMsaLdD },
		*/

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ldi_b",		StringId::Desc_Simd_MsaLdi,			{ { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaLdiB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ldi_h",		StringId::Desc_Simd_MsaLdi,			{ { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaLdiH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ldi_w",		StringId::Desc_Simd_MsaLdi,			{ { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaLdiW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ldi_d",		StringId::Desc_Simd_MsaLdi,			{ { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaLdiD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_madd_q_h",	StringId::Desc_Simd_MsaMaddQ,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaMaddQH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_madd_q_w",	StringId::Desc_Simd_MsaMaddQ,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaMaddQW },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_maddr_q_h",	StringId::Desc_Simd_MsaMaddrQ,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaMaddrQH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_maddr_q_w",	StringId::Desc_Simd_MsaMaddrQ,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaMaddrQW },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_maddv_b",	StringId::Desc_Simd_MsaMaddv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaMaddvB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_maddv_h",	StringId::Desc_Simd_MsaMaddv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaMaddvH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_maddv_w",	StringId::Desc_Simd_MsaMaddv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaMaddvW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_maddv_d",	StringId::Desc_Simd_MsaMaddv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaMaddvD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_max_s_b",	StringId::Desc_Simd_MsaMaxS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMaxSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_max_s_h",	StringId::Desc_Simd_MsaMaxS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMaxSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_max_s_w",	StringId::Desc_Simd_MsaMaxS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMaxSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_max_s_d",	StringId::Desc_Simd_MsaMaxS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMaxSD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_max_u_b",	StringId::Desc_Simd_MsaMaxU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMaxUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_max_u_h",	StringId::Desc_Simd_MsaMaxU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMaxUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_max_u_w",	StringId::Desc_Simd_MsaMaxU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMaxUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_max_u_d",	StringId::Desc_Simd_MsaMaxU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMaxUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_max_a_b",	StringId::Desc_Simd_MsaMaxA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMaxAB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_max_a_h",	StringId::Desc_Simd_MsaMaxA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMaxAH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_max_a_w",	StringId::Desc_Simd_MsaMaxA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMaxAW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_max_a_d",	StringId::Desc_Simd_MsaMaxA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMaxAD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_maxi_s_b",	StringId::Desc_Simd_MsaMaxiS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaMaxiSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_maxi_s_h",	StringId::Desc_Simd_MsaMaxiS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaMaxiSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_maxi_s_w",	StringId::Desc_Simd_MsaMaxiS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaMaxiSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_maxi_s_d",	StringId::Desc_Simd_MsaMaxiS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaMaxiSD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_maxi_u_b",	StringId::Desc_Simd_MsaMaxiU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::UInt64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaMaxiUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_maxi_u_h",	StringId::Desc_Simd_MsaMaxiU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::UInt64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaMaxiUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_maxi_u_w",	StringId::Desc_Simd_MsaMaxiU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::UInt64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaMaxiUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_maxi_u_d",	StringId::Desc_Simd_MsaMaxiU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::UInt64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaMaxiUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_min_s_b",	StringId::Desc_Simd_MsaMinS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMinSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_min_s_h",	StringId::Desc_Simd_MsaMinS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMinSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_min_s_w",	StringId::Desc_Simd_MsaMinS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMinSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_min_s_d",	StringId::Desc_Simd_MsaMinS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMinSD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_min_u_b",	StringId::Desc_Simd_MsaMinU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMinUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_min_u_h",	StringId::Desc_Simd_MsaMinU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMinUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_min_u_w",	StringId::Desc_Simd_MsaMinU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMinUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_min_u_d",	StringId::Desc_Simd_MsaMinU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMinUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_min_a_b",	StringId::Desc_Simd_MsaMinA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMinAB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_min_a_h",	StringId::Desc_Simd_MsaMinA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMinAH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_min_a_w",	StringId::Desc_Simd_MsaMinA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMinAW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_min_a_d",	StringId::Desc_Simd_MsaMinA,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMinAD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mini_s_b",	StringId::Desc_Simd_MsaMiniS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaMiniSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mini_s_h",	StringId::Desc_Simd_MsaMiniS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaMiniSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mini_s_w",	StringId::Desc_Simd_MsaMiniS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaMiniSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mini_s_d",	StringId::Desc_Simd_MsaMiniS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaMiniSD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mini_u_b",	StringId::Desc_Simd_MsaMiniU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaMiniUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mini_u_h",	StringId::Desc_Simd_MsaMiniU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaMiniUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mini_u_w",	StringId::Desc_Simd_MsaMiniU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaMiniUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mini_u_d",	StringId::Desc_Simd_MsaMiniU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaMiniUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mod_s_b",	StringId::Desc_Simd_MsaModS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaModSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mod_s_h",	StringId::Desc_Simd_MsaModS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaModSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mod_s_w",	StringId::Desc_Simd_MsaModS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaModSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mod_s_d",	StringId::Desc_Simd_MsaModS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaModSD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mod_u_b",	StringId::Desc_Simd_MsaModU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaModUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mod_u_h",	StringId::Desc_Simd_MsaModU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaModUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mod_u_w",	StringId::Desc_Simd_MsaModU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaModUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mod_u_d",	StringId::Desc_Simd_MsaModU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaModUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_move_v",		StringId::Desc_Simd_MsaMoveV,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaMoveV },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_msub_q_h",	StringId::Desc_Simd_MsaMsubQ,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaMsubQH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_msub_q_w",	StringId::Desc_Simd_MsaMsubQ,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaMsubQW },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_msubr_q_h",	StringId::Desc_Simd_MsaMsubrQ,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaMsubrQH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_msubr_q_w",	StringId::Desc_Simd_MsaMsubrQ,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaMsubrQW },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_msubv_b",	StringId::Desc_Simd_MsaMsubv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaMsubvB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_msubv_h",	StringId::Desc_Simd_MsaMsubv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaMsubvH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_msubv_w",	StringId::Desc_Simd_MsaMsubv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaMsubvW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_msubv_d",	StringId::Desc_Simd_MsaMsubv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Object, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaMsubvD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mul_q_h",	StringId::Desc_Simd_MsaMulQ,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMulQH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mul_q_w",	StringId::Desc_Simd_MsaMulQ,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMulQW },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mulr_q_h",	StringId::Desc_Simd_MsaMulrQ,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMulrQH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mulr_q_w",	StringId::Desc_Simd_MsaMulrQ,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMulrQW },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mulv_b",		StringId::Desc_Simd_MsaMulv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMulvB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mulv_h",		StringId::Desc_Simd_MsaMulv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMulvH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mulv_w",		StringId::Desc_Simd_MsaMulv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMulvW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_mulv_d",		StringId::Desc_Simd_MsaMulv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaMulvD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_nloc_b",		StringId::Desc_Simd_MsaNloc,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaNlocB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_nloc_h",		StringId::Desc_Simd_MsaNloc,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaNlocH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_nloc_w",		StringId::Desc_Simd_MsaNloc,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaNlocW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_nloc_d",		StringId::Desc_Simd_MsaNloc,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaNlocD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_nlzc_b",		StringId::Desc_Simd_MsaNlzc,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaNlzcB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_nlzc_h",		StringId::Desc_Simd_MsaNlzc,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaNlzcH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_nlzc_w",		StringId::Desc_Simd_MsaNlzc,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaNlzcW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_nlzc_d",		StringId::Desc_Simd_MsaNlzc,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaNlzcD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_nor_v",		StringId::Desc_Simd_MsaNor,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaNorV },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_nori_b",		StringId::Desc_Simd_MsaNori,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaNoriB },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_or_v",		StringId::Desc_Simd_MsaOr,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaOrV },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_ori_b",		StringId::Desc_Simd_MsaOri,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaOriB },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_pckev_b",	StringId::Desc_Simd_MsaPckev,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaPckevB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_pckev_h",	StringId::Desc_Simd_MsaPckev,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaPckevH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_pckev_w",	StringId::Desc_Simd_MsaPckev,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaPckevW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_pckev_d",	StringId::Desc_Simd_MsaPckev,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaPckevD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_pckod_b",	StringId::Desc_Simd_MsaPckod,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaPckodB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_pckod_h",	StringId::Desc_Simd_MsaPckod,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaPckodH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_pckod_w",	StringId::Desc_Simd_MsaPckod,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaPckodW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_pckod_d",	StringId::Desc_Simd_MsaPckod,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaPckodD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_pcnt_b",		StringId::Desc_Simd_MsaPcnt,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaPcntB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_pcnt_h",		StringId::Desc_Simd_MsaPcnt,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaPcntH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_pcnt_w",		StringId::Desc_Simd_MsaPcnt,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaPcntW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_pcnt_d",		StringId::Desc_Simd_MsaPcnt,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaPcntD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sat_s_b",	StringId::Desc_Simd_MsaSatS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSatSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sat_s_h",	StringId::Desc_Simd_MsaSatS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSatSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sat_s_w",	StringId::Desc_Simd_MsaSatS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSatSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sat_s_d",	StringId::Desc_Simd_MsaSatS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSatSD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sat_u_b",	StringId::Desc_Simd_MsaSatU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSatUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sat_u_h",	StringId::Desc_Simd_MsaSatU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSatUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sat_u_w",	StringId::Desc_Simd_MsaSatU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSatUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sat_u_d",	StringId::Desc_Simd_MsaSatU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSatUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_shf_b",		StringId::Desc_Simd_MsaShf,			{ { DataType::Int64, "imm", StringId::Simd_Param_Imm }, { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaShfB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_shf_h",		StringId::Desc_Simd_MsaShf,			{ { DataType::Int64, "imm", StringId::Simd_Param_Imm }, { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaShfH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_shf_w",		StringId::Desc_Simd_MsaShf,			{ { DataType::Int64, "imm", StringId::Simd_Param_Imm }, { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaShfW },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sld_b",		StringId::Desc_Simd_MsaSld,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Int64, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaSldB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sld_h",		StringId::Desc_Simd_MsaSld,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Int64, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaSldH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sld_w",		StringId::Desc_Simd_MsaSld,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Int64, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaSldW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sld_d",		StringId::Desc_Simd_MsaSld,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Int64, "c", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaSldD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sldi_b",		StringId::Desc_Simd_MsaSldi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSldiB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sldi_h",		StringId::Desc_Simd_MsaSldi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSldiH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sldi_w",		StringId::Desc_Simd_MsaSldi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSldiW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sldi_d",		StringId::Desc_Simd_MsaSldi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSldiD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sll_b",		StringId::Desc_Simd_MsaSll,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSllB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sll_h",		StringId::Desc_Simd_MsaSll,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSllH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sll_w",		StringId::Desc_Simd_MsaSll,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSllW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sll_d",		StringId::Desc_Simd_MsaSll,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSllD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_slli_b",		StringId::Desc_Simd_MsaSlli,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSlliB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_slli_h",		StringId::Desc_Simd_MsaSlli,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSlliH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_slli_w",		StringId::Desc_Simd_MsaSlli,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSlliW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_slli_d",		StringId::Desc_Simd_MsaSlli,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSlliD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_splat_b",	StringId::Desc_Simd_MsaSplat,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "idx", StringId::Simd_Param_Idx } }, IntrinsicBridges::bridgeMsaSplatB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_splat_h",	StringId::Desc_Simd_MsaSplat,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "idx", StringId::Simd_Param_Idx } }, IntrinsicBridges::bridgeMsaSplatH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_splat_w",	StringId::Desc_Simd_MsaSplat,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "idx", StringId::Simd_Param_Idx } }, IntrinsicBridges::bridgeMsaSplatW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_splat_d",	StringId::Desc_Simd_MsaSplat,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "idx", StringId::Simd_Param_Idx } }, IntrinsicBridges::bridgeMsaSplatD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_splati_b",	StringId::Desc_Simd_MsaSplati,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSplatiB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_splati_h",	StringId::Desc_Simd_MsaSplati,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSplatiH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_splati_w",	StringId::Desc_Simd_MsaSplati,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSplatiW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_splati_d",	StringId::Desc_Simd_MsaSplati,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSplatiD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sra_b",		StringId::Desc_Simd_MsaSra,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSraB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sra_h",		StringId::Desc_Simd_MsaSra,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSraH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sra_w",		StringId::Desc_Simd_MsaSra,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSraW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_sra_d",		StringId::Desc_Simd_MsaSra,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSraD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srai_b",		StringId::Desc_Simd_MsaSrai,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSraiB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srai_h",		StringId::Desc_Simd_MsaSrai,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSraiH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srai_w",		StringId::Desc_Simd_MsaSrai,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSraiW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srai_d",		StringId::Desc_Simd_MsaSrai,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSraiD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srar_b",			StringId::Desc_Simd_MsaSrar,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSrarB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srar_h",			StringId::Desc_Simd_MsaSrar,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSrarH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srar_w",			StringId::Desc_Simd_MsaSrar,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSrarW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srar_d",			StringId::Desc_Simd_MsaSrar,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSrarD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srari_b",		StringId::Desc_Simd_MsaSrari,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSrariB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srari_h",		StringId::Desc_Simd_MsaSrari,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSrariH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srari_w",		StringId::Desc_Simd_MsaSrari,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSrariW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srari_d",		StringId::Desc_Simd_MsaSrari,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSrariD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srl_b",			StringId::Desc_Simd_MsaSrl,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSrlB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srl_h",			StringId::Desc_Simd_MsaSrl,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSrlH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srl_w",			StringId::Desc_Simd_MsaSrl,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSrlW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srl_d",			StringId::Desc_Simd_MsaSrl,			{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSrlD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srli_b",			StringId::Desc_Simd_MsaSrli,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSrliB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srli_h",			StringId::Desc_Simd_MsaSrli,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSrliH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srli_w",			StringId::Desc_Simd_MsaSrli,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSrliW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srli_d",			StringId::Desc_Simd_MsaSrli,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSrliD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srlr_b",			StringId::Desc_Simd_MsaSrlr,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSrlrB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srlr_h",			StringId::Desc_Simd_MsaSrlr,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSrlrH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srlr_w",			StringId::Desc_Simd_MsaSrlr,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSrlrW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srlr_d",			StringId::Desc_Simd_MsaSrlr,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSrlrD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srlri_b",		StringId::Desc_Simd_MsaSrlri,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSrlriB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srlri_h",		StringId::Desc_Simd_MsaSrlri,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSrlriH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srlri_w",		StringId::Desc_Simd_MsaSrlri,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSrlriW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_srlri_d",		StringId::Desc_Simd_MsaSrlri,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Int64, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSrlriD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subs_s_b",		StringId::Desc_Simd_MsaSubsS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubsSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subs_s_h",		StringId::Desc_Simd_MsaSubsS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubsSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subs_s_w",		StringId::Desc_Simd_MsaSubsS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubsSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subs_s_d",		StringId::Desc_Simd_MsaSubsS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubsSD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subs_u_b",		StringId::Desc_Simd_MsaSubsU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubsUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subs_u_h",		StringId::Desc_Simd_MsaSubsU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubsUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subs_u_w",		StringId::Desc_Simd_MsaSubsU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubsUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subs_u_d",		StringId::Desc_Simd_MsaSubsU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubsUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subsus_u_b",		StringId::Desc_Simd_MsaSubsusU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubsusUB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subsus_u_h",		StringId::Desc_Simd_MsaSubsusU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubsusUH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subsus_u_w",		StringId::Desc_Simd_MsaSubsusU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubsusUW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subsus_u_d",		StringId::Desc_Simd_MsaSubsusU,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubsusUD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subsuu_s_b",		StringId::Desc_Simd_MsaSubsuuS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubsuuSB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subsuu_s_h",		StringId::Desc_Simd_MsaSubsuuS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubsuuSH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subsuu_s_w",		StringId::Desc_Simd_MsaSubsuuS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubsuuSW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subsuu_s_d",		StringId::Desc_Simd_MsaSubsuuS,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubsuuSD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subv_b",			StringId::Desc_Simd_MsaSubv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubvB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subv_h",			StringId::Desc_Simd_MsaSubv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubvH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subv_w",			StringId::Desc_Simd_MsaSubv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubvW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subv_d",			StringId::Desc_Simd_MsaSubv,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaSubvD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subvi_b",		StringId::Desc_Simd_MsaSubvi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSubviB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subvi_h",		StringId::Desc_Simd_MsaSubvi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSubviH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subvi_w",		StringId::Desc_Simd_MsaSubvi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSubviW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_subvi_d",		StringId::Desc_Simd_MsaSubvi,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaSubviD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_test_bnz_b",		StringId::Desc_Simd_MsaTestBnz,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaTestBnzB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_test_bnz_h",		StringId::Desc_Simd_MsaTestBnz,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaTestBnzH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_test_bnz_w",		StringId::Desc_Simd_MsaTestBnz,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaTestBnzW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_test_bnz_d",		StringId::Desc_Simd_MsaTestBnz,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaTestBnzD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_test_bnz_v",		StringId::Desc_Simd_MsaTestBnz,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaTestBnzV },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_test_bz_b",		StringId::Desc_Simd_MsaTestBz,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaTestBzB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_test_bz_h",		StringId::Desc_Simd_MsaTestBz,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaTestBzH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_test_bz_w",		StringId::Desc_Simd_MsaTestBz,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaTestBzW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_test_bz_d",		StringId::Desc_Simd_MsaTestBz,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaTestBzD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_test_bz_v",		StringId::Desc_Simd_MsaTestBz,		{ { DataType::Object, "a", StringId::Simd_Param_A } }, IntrinsicBridges::bridgeMsaTestBzV },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_vshf_b",			StringId::Desc_Simd_MsaVshf,		{ { DataType::Object, "mask", StringId::Simd_Param_A }, { DataType::Object, "ws", StringId::Simd_Param_B }, { DataType::Object, "wt", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaVshfB },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_vshf_h",			StringId::Desc_Simd_MsaVshf,		{ { DataType::Object, "mask", StringId::Simd_Param_A }, { DataType::Object, "ws", StringId::Simd_Param_B }, { DataType::Object, "wt", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaVshfH },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_vshf_w",			StringId::Desc_Simd_MsaVshf,		{ { DataType::Object, "mask", StringId::Simd_Param_A }, { DataType::Object, "ws", StringId::Simd_Param_B }, { DataType::Object, "wt", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaVshfW },
		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_vshf_d",			StringId::Desc_Simd_MsaVshf,		{ { DataType::Object, "mask", StringId::Simd_Param_A }, { DataType::Object, "ws", StringId::Simd_Param_B }, { DataType::Object, "wt", StringId::Simd_Param_C } }, IntrinsicBridges::bridgeMsaVshfD },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_xor_v",			StringId::Desc_Simd_MsaXorV,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Object, "b", StringId::Simd_Param_B } }, IntrinsicBridges::bridgeMsaXorV },

		{ StringId::Desc_Category_SimdMipsMsa,				"__msa_xori_b",			StringId::Desc_Simd_MsaXori,		{ { DataType::Object, "a", StringId::Simd_Param_A }, { DataType::Integer, "imm", StringId::Simd_Param_Imm } }, IntrinsicBridges::bridgeMsaXoriB },
	};

	// == Functions.
	/**
	 * Compiles a string expression and populates the internal AST.
	 * 
	 * \param expression	The raw mathematical expression string.
	 * \param errorOut		Optional pointer to a string that will receive error details if compilation fails.
	 * \return				Returns true if compilation succeeded, false otherwise.
	 **/
	bool ExecutionContext::compile(const std::string& expression, std::wstring* errorOut) {
		try {
			reset();

			for (size_t i = 0; i < std::size(builtInConsts); ++i) {
				registerConstant(builtInConsts[i].name, builtInConsts[i].result);
			}
			for (size_t i = 0; i < std::size(builtInFunctions); ++i) {
				registerFunction(builtInFunctions[i].name, builtInFunctions[i].parameters, builtInFunctions[i].callback, builtInFunctions[i].operateOnVectorElements);
			}

			antlr4::ANTLRInputStream input(expression);
			ExprLexer lexer(&input);
			antlr4::CommonTokenStream tokens(&lexer);
			ExprParser parser(&tokens);

			parser.getInterpreter<antlr4::atn::ParserATNSimulator>()->setPredictionMode(antlr4::atn::PredictionMode::SLL);
			parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

			antlr4::tree::ParseTree* tree = nullptr;

			try {
				tree = parser.prog();
			}
			catch (antlr4::ParseCancellationException&) {
				tokens.reset();
				parser.reset();
				parser.setErrorHandler(std::make_shared<antlr4::DefaultErrorStrategy>());
				parser.getInterpreter<antlr4::atn::ParserATNSimulator>()->setPredictionMode(antlr4::atn::PredictionMode::LL);
				
				tree = parser.prog();
			}

			if (parser.getNumberOfSyntaxErrors() > 0) {
				throw ErrorCode::Syntax_Error;
			}

			AstBuilderVisitor visitor(*this);
			std::any resultAny = visitor.visit(tree);

			if (resultAny.has_value()) {
				rootIndex = std::any_cast<size_t>(resultAny);
				initialObjectsTotal = objects.size();
				return true;
			}
			else {
				if (errorOut) {
					(*errorOut) = L"Visitor failed to return a valid root node index.";
				}
				return false;
			}
		}
		catch (const std::bad_any_cast& e) {
			if (errorOut) {
				std::string tmp = e.what();
				(*errorOut) = std::wstring(L"AST visitor type mismatch: ") + std::wstring(tmp.begin(), tmp.end());
			}
			return false;
		}
		catch (const ErrorCode& e) {
			if (errorOut) {
				if (e == ErrorCode::Out_Of_Memory) {
					(*errorOut) = L"Memory allocation failed within the AstArena.";
				}
				else {
					(*errorOut) = L"An internal engine error occurred during compilation.";
				}
			}
			return false;
		}
		catch (const std::exception& e) {
			if (errorOut) {
				std::string tmp = e.what();
				(*errorOut) = std::wstring(L"Standard exception caught: ") + std::wstring(tmp.begin(), tmp.end());
			}
			return false;
		}
		catch (...) {
			if (errorOut) {
				(*errorOut) = L"An unknown critical error occurred during compilation.";
			}
			return false;
		}
	}

	/**
	 * Evaluates the currently compiled AST. Can be called multiple times.
	 * 
	 * \return				Returns the evaluated Result.
	 **/
	Result ExecutionContext::execute() {
		if (arena.nodes.empty()) {
			Result emptyRes;
			emptyRes.type = NumericConstant::Invalid;
			return emptyRes;
		}
		// All run-time-allocated objects will follow compile-time objects, and compile-time objects are never deleted.
		objects.resize(initialObjectsTotal);
		return arena.nodes[rootIndex]->evaluate((*this));
	}

	/**
	 * Resets the object back to scratch.
	 **/
	void ExecutionContext::reset() {
		// Clear objects first.  Who knows what kinds of resources they may need to access, so
		// don’t clear resources until objects are already gone.
		// Objects can delete other objects, so we have to use a special clearing process.
		for (size_t i = objects.size(); i--; ) {
			if (i < objects.size()) {
				if (objects[i].get()) {
					objects[i].reset();
				}
			}
		}
		objects.clear();
		initialObjectsTotal = 0;

		arena.nodes.clear();
		variables.clear();
		registeredConstants.clear();
		registeredFunctions.clear();
		userValue = Result{};
		userParms.clear();
		returnValue = Result{};
		rootIndex = 0;
		initialObjectsTotal = 0;

		// Don’t change settings such as treatAllAsHex.
	}

	/**
	 * Converts a Result into its string representation.
	 * Must be called within a try/catch block.
	 *
	 * \param res			The Result to convert.
	 * \param depth			The recursion depth for stringifying nested objects (defaults to 1).
	 * \param flags			Bitmask defining formatting rules (defaults to 0).
	 * \return				Returns the string representation of the Result.
	 **/
	std::string ExecutionContext::toString(const Result& res, int32_t depth, uint32_t flags) const {
		switch (res.type) {
			case NumericConstant::Unsigned : {
				return Text::toUnsigned(res.value.uintVal);
			}
			case NumericConstant::Signed : {
				return Text::toSigned(res.value.intVal);
			}
			case NumericConstant::Floating : {
				if (flags & ToStringFlags::ToStringFlag_LowQualityFloat) {
					return std::format("{:.17g}", res.value.doubleVal);
				}
				return Text::toDouble(res.value.doubleVal);
			}
			case NumericConstant::Object : {
				if (res.value.objectVal) {
					std::string utf8Str;
					if (res.value.objectVal->toString(utf8Str, depth, flags)) {
						return utf8Str;
					}
					return "[Object String Conversion Failed]";
				}
				return "<null>";
			}
			case NumericConstant::Invalid : {}
			default : {
				return "[Invalid or Uninitialized]";
			}
		}
	}

	/**
	 * Evaluates the currently compiled AST. Can be called multiple times.
	 * 
	 * \return			Returns the evaluated Result.
	 **/
	NumericConstant ExecutionContext::getCastType(NumericConstant left, NumericConstant right) {
		return left > right ? left : right;
	}

	/**
	 * Converts a result or object to a specified numeric type.
	 * 
	 * \param res			The source result to convert.
	 * \param target		The target numeric constant type.
	 * \return				Returns a new Result converted to the target type.
	 **/
	Result ExecutionContext::convertResult(const Result& res, NumericConstant target) {
		if (res.type == target) { return res; }

		Result out;
		out.type = target;

		if (res.type == NumericConstant::Floating) {
			switch (target) {
				case NumericConstant::Signed : {
					out.value.intVal = static_cast<int64_t>(res.value.doubleVal);
					break;
				}
				case NumericConstant::Unsigned : {
					out.value.uintVal = static_cast<uint64_t>(res.value.doubleVal);
					break;
				}
				case NumericConstant::Object : {
					out.type = NumericConstant::Invalid;
					out.value.objectVal = nullptr;
					break;
				}
				default : { break; }
			}
		}
		else if (res.type == NumericConstant::Signed) {
			switch (target) {
				case NumericConstant::Unsigned : {
					out.value.uintVal = static_cast<uint64_t>(res.value.intVal);
					break;
				}
				case NumericConstant::Floating : {
					out.value.doubleVal = static_cast<double>(res.value.intVal);
					break;
				}
				case NumericConstant::Object : {
					out.type = NumericConstant::Invalid;
					out.value.objectVal = nullptr;
					break;
				}
				default : { break; }
			}
		}
		else if (res.type == NumericConstant::Unsigned) {
			switch (target) {
				case NumericConstant::Floating : {
					out.value.doubleVal = static_cast<double>(res.value.uintVal);
					break;
				}
				case NumericConstant::Signed : {
					out.value.intVal = static_cast<int64_t>(res.value.uintVal);
					break;
				}
				case NumericConstant::Object : {
					out.type = NumericConstant::Invalid;
					out.value.objectVal = nullptr;
					break;
				}
				default : { break; }
			}
		}
		else if (res.type == NumericConstant::Object) {
			if (!res.value.objectVal) {
				out.type = NumericConstant::Invalid;
				out.value.objectVal = nullptr;
			}
			else {
				out.type = NumericConstant::Invalid;
				if (res.value.objectVal->type() & BuiltInType_String) {
					String * newStr = allocateObject<String>();
					if (newStr) {
						if (newStr->initializeFrom(res)) {
							out = newStr->createResult();
						}
						else {
							deallocateObject(newStr);
						}
					}
				}
				else {
					// TODO.
					out.type = NumericConstant::Invalid;
					out.value.objectVal = nullptr;
				}
			}
		}

		return out;
	}

	/**
	 * Casts a raw evaluated Result into the specific C-type expected by a function parameter.
	 * Applies standard C-truncation (e.g., 64-bit to 8-bit) and precision loss (double to float).
	 * 
	 * \param rawVal		The original 64-bit evaluated result.
	 * \param targetType	The explicit C data type to cast into.
	 * \return				Returns a newly formatted Result containing the truncated/casted value.
	 **/
	Result ExecutionContext::castArgument(const Result& rawVal, DataType targetType) const {
		if (rawVal.type == NumericConstant::Invalid) {
			return Result{};
		}
		Result out;
		
		// Helper lambda: Extracts the raw result as a double.
		auto getAsDouble = [&]() -> double {
			if (rawVal.type == NumericConstant::Floating) { return rawVal.value.doubleVal; }
			if (rawVal.type == NumericConstant::Signed) { return static_cast<double>(rawVal.value.intVal); }
			return static_cast<double>(rawVal.value.uintVal);
		};

		// Helper lambda: Extracts the raw result as an int64_t.
		auto getAsInt64 = [&]() -> int64_t {
			if (rawVal.type == NumericConstant::Signed) { return rawVal.value.intVal; }
			if (rawVal.type == NumericConstant::Unsigned) { return static_cast<int64_t>(rawVal.value.uintVal); }
			return static_cast<int64_t>(rawVal.value.doubleVal);
		};

		// Helper lambda: Extracts the raw result as a uint64_t.
		auto getAsUInt64 = [&]() -> uint64_t {
			if (rawVal.type == NumericConstant::Unsigned) { return rawVal.value.uintVal; }
			if (rawVal.type == NumericConstant::Signed) { return static_cast<uint64_t>(rawVal.value.intVal); }
			return static_cast<uint64_t>(rawVal.value.doubleVal);
		};

		switch (targetType) {
			case DataType::Int8 : {
				out.type = NumericConstant::Signed;
				out.value.intVal = static_cast<int8_t>(getAsInt64());
				break;
			}
			case DataType::UInt8 : {
				out.type = NumericConstant::Unsigned;
				out.value.uintVal = static_cast<uint8_t>(getAsUInt64());
				break;
			}
			case DataType::Int16 : {
				out.type = NumericConstant::Signed;
				out.value.intVal = static_cast<int16_t>(getAsInt64());
				break;
			}
			case DataType::UInt16 : {
				out.type = NumericConstant::Unsigned;
				out.value.uintVal = static_cast<uint16_t>(getAsUInt64());
				break;
			}
			case DataType::Int32 : {
				out.type = NumericConstant::Signed;
				out.value.intVal = static_cast<int32_t>(getAsInt64());
				break;
			}
			case DataType::UInt32 : {
				out.type = NumericConstant::Unsigned;
				out.value.uintVal = static_cast<uint32_t>(getAsUInt64());
				break;
			}
			case DataType::Int64 : {
				out.type = NumericConstant::Signed;
				out.value.intVal = getAsInt64();
				break;
			}
			case DataType::UInt64 : {
				out.type = NumericConstant::Unsigned;
				out.value.uintVal = getAsUInt64();
				break;
			}
			case DataType::Pointer : {
				out.type = NumericConstant::Unsigned;
				// Cast through uintptr_t to ensure architecture-accurate truncation on 32-bit builds.
				out.value.uintVal = static_cast<uint64_t>(static_cast<uintptr_t>(getAsUInt64()));
				break;
			}
			case DataType::BFloat16 : {
				out.type = NumericConstant::Floating;
				out.value.doubleVal = BFloat16(getAsDouble()).value();
				break;
			}
			case DataType::Float16 : {
				out.type = NumericConstant::Floating;
				out.value.doubleVal = Float16(getAsDouble()).value();
				break;
			}
			case DataType::Float : {
				out.type = NumericConstant::Floating;
				out.value.doubleVal = static_cast<float>(getAsDouble());
				break;
			}
			case DataType::Double : {
				out.type = NumericConstant::Floating;
				out.value.doubleVal = getAsDouble();
				break;
			}
			case DataType::Object : {
				if (rawVal.type == NumericConstant::Object) {
					// out can just be the given input directly.
					out = rawVal;
				}
				else {
					// We don’t know what type of object to make, so nothing to do but error.
					out.type = NumericConstant::Invalid;
					out.value.uintVal = 0;
				}
				break;
			}
			case DataType::String : {
				if (rawVal.type == NumericConstant::Object && rawVal.value.objectVal != nullptr && (rawVal.value.objectVal->type() & BuiltInType_String)) {
					out = rawVal;
				}
				else {
					ExecutionContext* nonConstCtx = const_cast<ExecutionContext*>(this);
					String* str = nonConstCtx->allocateObject<String>();
        
					if (str && str->initializeFrom(rawVal)) {
						out = str->createResult();
					}
					else {
						nonConstCtx->deallocateObject(str);
						out.type = NumericConstant::Invalid;
						out.value.uintVal = 0;
					}
				}
				break;
			}
			case DataType::Integer : {
				if (rawVal.type == NumericConstant::Unsigned || rawVal.type == NumericConstant::Signed) {
					out = rawVal;
				}
				else if (rawVal.type == NumericConstant::Object) {
					out.type = NumericConstant::Invalid;
					out.value.uintVal = 0;
					/*if (!rawVal.value.objectVal) {
						out.type = NumericConstant::Invalid;
						out.value.uintVal = 0;
					}
					else {
						out = rawVal.value.objectVal->convertTo(NumericConstant::Signed);
					}*/
				}
				else {
					out.type = NumericConstant::Signed;
					out.value.intVal = static_cast<int16_t>(getAsInt64());
				}
				break;
			}
			case DataType::Any : {
				out = rawVal;
				break;
			}
			case DataType::Variadic : {
				out = rawVal;
				break;
			}
		}
		
		return out;
	}

	/**
	 * Centralized evaluation helper for all math and compound operations.
	 *
	 * \param leftVal		The left operand.
	 * \param rightVal		The right operand.
	 * \param opType		The ExprLexer token representing the operation (e.g. ADD_ASSIGN).
	 * \return				Returns the resulting evaluation.
	 **/
	Result ExecutionContext::evaluateMath(const Result& leftVal, const Result& rightVal, int opType) const {
		if (leftVal.type == NumericConstant::Object) {
			if (!leftVal.value.objectVal) { return Result{}; }
			switch (opType) {
				case ExprLexer::ADD_ASSIGN : { return leftVal.value.objectVal->operator+=(rightVal); }
				case ExprLexer::SUB_ASSIGN : { return leftVal.value.objectVal->operator-=(rightVal); }
				case ExprLexer::MUL_ASSIGN : { return leftVal.value.objectVal->operator*=(rightVal); }
				case ExprLexer::DIV_ASSIGN : { return leftVal.value.objectVal->operator/=(rightVal); }
				case ExprLexer::MOD_ASSIGN : { return leftVal.value.objectVal->operator%=(rightVal); }
				case ExprLexer::AND_ASSIGN : { return leftVal.value.objectVal->operator&=(rightVal); }
				case ExprLexer::XOR_ASSIGN : { return leftVal.value.objectVal->operator^=(rightVal); }
				case ExprLexer::OR_ASSIGN :  { return leftVal.value.objectVal->operator|=(rightVal); }
				case ExprLexer::SHL_ASSIGN : { return leftVal.value.objectVal->operator<<=(rightVal); }
				case ExprLexer::SHR_ASSIGN : { return leftVal.value.objectVal->operator>>=(rightVal); }
				case ExprLexer::ADD : { return leftVal.value.objectVal->operator+(rightVal); }
				case ExprLexer::SUB : { return leftVal.value.objectVal->operator-(rightVal); }
				case ExprLexer::MUL : { return leftVal.value.objectVal->operator*(rightVal); }
				case ExprLexer::DIV : { return leftVal.value.objectVal->operator/(rightVal); }
				case ExprLexer::MOD : { return leftVal.value.objectVal->operator%(rightVal); }
				case ExprLexer::BIT_AND : { return leftVal.value.objectVal->operator&(rightVal); }
				case ExprLexer::BIT_XOR : { return leftVal.value.objectVal->operator^(rightVal); }
				case ExprLexer::BIT_OR :  { return leftVal.value.objectVal->operator|(rightVal); }
				case ExprLexer::SHL : { return leftVal.value.objectVal->operator<<(rightVal); }
				case ExprLexer::SHR : { return leftVal.value.objectVal->operator>>(rightVal); }
				default : { return Result{}; }
			}
		}
		if (rightVal.type == NumericConstant::Object && rightVal.value.objectVal && (rightVal.value.objectVal->type() & BuiltInType_Vector)) {
			// Arithmatic applied to each element in the vector.
			Vector* vec = static_cast<Vector*>(rightVal.value.objectVal);
			switch (opType) {
				// In-place assignment.
				case ExprLexer::ADD_ASSIGN : {}
				case ExprLexer::SUB_ASSIGN : {}
				case ExprLexer::MUL_ASSIGN : {}
				case ExprLexer::DIV_ASSIGN : {}
				case ExprLexer::MOD_ASSIGN : {}
				case ExprLexer::AND_ASSIGN : {}
				case ExprLexer::XOR_ASSIGN : {}
				case ExprLexer::OR_ASSIGN : {}
				case ExprLexer::SHL_ASSIGN : {}
				case ExprLexer::SHR_ASSIGN : {
					for (auto i = vec->arrayLength(); i--; ) {
						vec->directAccess(i) = evaluateMath(leftVal, vec->directAccess(i), opType);
					}
					return vec->createResult();
				}
				case ExprLexer::ADD : {}
				case ExprLexer::SUB : {}
				case ExprLexer::MUL : {}
				case ExprLexer::DIV : {}
				case ExprLexer::MOD : {}
				case ExprLexer::BIT_AND : {}
				case ExprLexer::BIT_XOR : {}
				case ExprLexer::BIT_OR :  {}
				case ExprLexer::SHL : {}
				case ExprLexer::SHR : {
					// Make a copy of the vector.
					Vector* copy = const_cast<ExecutionContext*>(this)->allocateObject<Vector>();
					if (!copy) { throw ErrorCode::Out_Of_Memory; }
					if (!copy->resize(vec->arrayLength())) {
						const_cast<ExecutionContext*>(this)->deallocateObject(copy);
						return Result{};
					}
					for (auto i = vec->arrayLength(); i--; ) {
						copy->directAccess(i) = evaluateMath(leftVal, vec->directAccess(i), opType);
					}
					return copy->createResult();
				}
				default : { return Result{}; }
			}
			
		}

		NumericConstant common = getCastType(leftVal.type, rightVal.type);
		Result l = const_cast<ExecutionContext*>(this)->convertResult(leftVal, common);
		Result r = const_cast<ExecutionContext*>(this)->convertResult(rightVal, common);
		Result out;
		out.type = common;

		if (common == NumericConstant::Floating) {
			switch (opType) {
				case ExprLexer::ADD_ASSIGN : {}
				case ExprLexer::ADD : { out.value.doubleVal = l.value.doubleVal + r.value.doubleVal; break; }
				case ExprLexer::SUB_ASSIGN : {}
				case ExprLexer::SUB : { out.value.doubleVal = l.value.doubleVal - r.value.doubleVal; break; }
				case ExprLexer::MUL_ASSIGN : {}
				case ExprLexer::MUL : { out.value.doubleVal = l.value.doubleVal * r.value.doubleVal; break; }
				case ExprLexer::DIV_ASSIGN : {}
				case ExprLexer::DIV : { out.value.doubleVal = l.value.doubleVal / r.value.doubleVal; break; }
				case ExprLexer::MOD_ASSIGN : {}
				case ExprLexer::MOD : { out.value.doubleVal = std::fmod(l.value.doubleVal, r.value.doubleVal); break; }
				default : { return Result{}; }
			}
		}
		else if (common == NumericConstant::Signed) {
			switch (opType) {
				case ExprLexer::ADD_ASSIGN : {}
				case ExprLexer::ADD : { out.value.intVal = l.value.intVal + r.value.intVal; break; }
				case ExprLexer::SUB_ASSIGN : {}
				case ExprLexer::SUB : { out.value.intVal = l.value.intVal - r.value.intVal; break; }
				case ExprLexer::MUL_ASSIGN : {}
				case ExprLexer::MUL : { out.value.intVal = l.value.intVal * r.value.intVal; break; }
				case ExprLexer::DIV_ASSIGN : {}
				case ExprLexer::DIV : { out.value.intVal = l.value.intVal / r.value.intVal; break; }
				case ExprLexer::MOD_ASSIGN : {}
				case ExprLexer::MOD : { out.value.intVal = l.value.intVal % r.value.intVal; break; }
				case ExprLexer::AND_ASSIGN : {}
				case ExprLexer::BIT_AND : { out.value.intVal = l.value.intVal & r.value.intVal; break; }
				case ExprLexer::XOR_ASSIGN : {}
				case ExprLexer::BIT_XOR : { out.value.intVal = l.value.intVal ^ r.value.intVal; break; }
				case ExprLexer::OR_ASSIGN :  {}
				case ExprLexer::BIT_OR :  { out.value.intVal = l.value.intVal | r.value.intVal; break; }
				case ExprLexer::SHL_ASSIGN : {}
				case ExprLexer::SHL : { out.value.intVal = l.value.intVal << r.value.intVal; break; }
				case ExprLexer::SHR_ASSIGN : {}
				case ExprLexer::SHR : { out.value.intVal = l.value.intVal >> r.value.intVal; break; }
				default : { return Result{}; }
			}
		}
		else if (common == NumericConstant::Unsigned) {
			switch (opType) {
				case ExprLexer::ADD_ASSIGN : {}
				case ExprLexer::ADD : { out.value.uintVal = l.value.uintVal + r.value.uintVal; break; }
				case ExprLexer::SUB_ASSIGN : {}
				case ExprLexer::SUB : { out.value.uintVal = l.value.uintVal - r.value.uintVal; break; }
				case ExprLexer::MUL_ASSIGN : {}
				case ExprLexer::MUL : { out.value.uintVal = l.value.uintVal * r.value.uintVal; break; }
				case ExprLexer::DIV_ASSIGN : {}
				case ExprLexer::DIV : { out.value.uintVal = l.value.uintVal / r.value.uintVal; break; }
				case ExprLexer::MOD_ASSIGN : {}
				case ExprLexer::MOD : { out.value.uintVal = l.value.uintVal % r.value.uintVal; break; }
				case ExprLexer::AND_ASSIGN : {}
				case ExprLexer::BIT_AND : { out.value.uintVal = l.value.uintVal & r.value.uintVal; break; }
				case ExprLexer::XOR_ASSIGN : {}
				case ExprLexer::BIT_XOR : { out.value.uintVal = l.value.uintVal ^ r.value.uintVal; break; }
				case ExprLexer::OR_ASSIGN :  {}
				case ExprLexer::BIT_OR :  { out.value.uintVal = l.value.uintVal | r.value.uintVal; break; }
				case ExprLexer::SHL_ASSIGN : {}
				case ExprLexer::SHL : { out.value.uintVal = l.value.uintVal << r.value.uintVal; break; }
				case ExprLexer::SHR_ASSIGN : {}
				case ExprLexer::SHR : { out.value.uintVal = l.value.uintVal >> r.value.uintVal; break; }
				default : { return Result{}; }
			}
		}
		else if (common == NumericConstant::Object) {
			if (!l.value.objectVal || !r.value.objectVal) { return Result{}; }
			switch (opType) {
				case ExprLexer::ADD_ASSIGN : { return l.value.objectVal->operator+=(r); }
				case ExprLexer::SUB_ASSIGN : { return l.value.objectVal->operator-=(r); }
				case ExprLexer::MUL_ASSIGN : { return l.value.objectVal->operator*=(r); }
				case ExprLexer::DIV_ASSIGN : { return l.value.objectVal->operator/=(r); }
				case ExprLexer::MOD_ASSIGN : { return l.value.objectVal->operator%=(r); }
				case ExprLexer::AND_ASSIGN : { return l.value.objectVal->operator&=(r); }
				case ExprLexer::XOR_ASSIGN : { return l.value.objectVal->operator^=(r); }
				case ExprLexer::OR_ASSIGN :  { return l.value.objectVal->operator|=(r); }
				case ExprLexer::SHL_ASSIGN : { return l.value.objectVal->operator<<=(r); }
				case ExprLexer::SHR_ASSIGN : { return l.value.objectVal->operator>>=(r); }
				case ExprLexer::ADD : { return l.value.objectVal->operator+(r); }
				case ExprLexer::SUB : { return l.value.objectVal->operator-(r); }
				case ExprLexer::MUL : { return l.value.objectVal->operator*(r); }
				case ExprLexer::DIV : { return l.value.objectVal->operator/(r); }
				case ExprLexer::MOD : { return l.value.objectVal->operator%(r); }
				case ExprLexer::BIT_AND : { return l.value.objectVal->operator&(r); }
				case ExprLexer::BIT_XOR : { return l.value.objectVal->operator^(r); }
				case ExprLexer::BIT_OR :  { return l.value.objectVal->operator|(r); }
				case ExprLexer::SHL : { return l.value.objectVal->operator<<(r); }
				case ExprLexer::SHR : { return l.value.objectVal->operator>>(r); }
				default : { return Result{}; }
			}
		}
		else {
			return Result{};
		}

		return out;
	}

	/**
	 * Gets the total number of built-in constants.
	 * 
	 * \return				Returns the number of built-in constants in the internal table.
	 **/
	size_t ExecutionContext::totalBuiltInConstants() { return std::size(builtInConsts); }

	/**
	 * Gets by index a built-in constant name and its value.
	 * 
	 * \param idx			The index of the item to get.
	 * \param value			Holds the value of the constant.
	 * \param category		On returns, this holds the string ID for the category of the constant.
	 * \return				Returns a constant pointer to the name of the built-in constant.
	 **/
	const char* ExecutionContext::getBuiltinConstant(size_t idx, Result& value, StringId& category) {
		if (idx >= std::size(builtInConsts)) { return nullptr; }

		value = builtInConsts[idx].result;
		category = builtInConsts[idx].category;
		return builtInConsts[idx].name;
	}

	/**
	 * Gets a built-in function by index.
	 * 
	 * \param idx			The index of the function definition to get.
	 * \return				Returns a pointer to the given function definition or nullptr.
	 **/
	const FunctionDef * ExecutionContext::getBuiltinFunction(size_t idx) {
		if (idx >= std::size(builtInFunctions)) { return nullptr; }
		return &builtInFunctions[idx];
	}

}	// namespace ve
