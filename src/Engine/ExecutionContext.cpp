#include "../../generated/ExprLexer.h"
#include "../../generated/ExprParser.h"
#include "../Compiler/AstBuilderVisitor.h"
#include "ExecutionContext.h"
#include "IntrinsicBridges.h"

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
		{ "M_E",							Result::make( M_E ), },
		{ "M_LOG2E",						Result::make( M_LOG2E ), },
		{ "M_LOG10E",						Result::make( M_LOG10E ), },
		{ "M_LN2",							Result::make( M_LN2 ), },
		{ "M_LN10",							Result::make( M_LN10 ), },
		{ "M_PI",							Result::make( M_PI ), },
		{ "M_PI_2",							Result::make( M_PI_2 ), },
		{ "M_PI_4",							Result::make( M_PI_4 ), },
		{ "M_1_PI",							Result::make( M_1_PI ), },
		{ "M_2_PI",							Result::make( M_2_PI ), },
		{ "M_2_SQRTPI",						Result::make( M_2_SQRTPI ), },
		{ "M_SQRT2",						Result::make( M_SQRT2 ), },
		{ "M_SQRT1_2",						Result::make( M_SQRT1_2 ), },

		// == Character Limits (<climits>)
		{ "CHAR_BIT",						Result::make( CHAR_BIT ), },
		{ "MB_LEN_MAX",						Result::make( MB_LEN_MAX ), },
		{ "CHAR_MIN",						Result::make( CHAR_MIN ), },
		{ "CHAR_MAX",						Result::make( CHAR_MAX ), },
		{ "SCHAR_MIN",						Result::make( SCHAR_MIN ), },
		{ "SCHAR_MAX",						Result::make( SCHAR_MAX ), },
		{ "UCHAR_MAX",						Result::make( UCHAR_MAX ), },

		// == Standard Integer Limits (<climits>)
		{ "SHRT_MIN",						Result::make( SHRT_MIN ), },
		{ "SHRT_MAX",						Result::make( SHRT_MAX ), },
		{ "USHRT_MAX",						Result::make( USHRT_MAX ), },
		{ "INT_MIN",						Result::make( INT_MIN ), },
		{ "INT_MAX",						Result::make( INT_MAX ), },
		{ "UINT_MAX",						Result::make( UINT_MAX ), },
		{ "LONG_MIN",						Result::make( LONG_MIN ), },
		{ "LONG_MAX",						Result::make( LONG_MAX ), },
		{ "ULONG_MAX",						Result::make( ULONG_MAX ), },
		{ "LLONG_MIN",						Result::make( LLONG_MIN ), },
		{ "LLONG_MAX",						Result::make( LLONG_MAX ), },
		{ "ULLONG_MAX",						Result::make( ULLONG_MAX ), },

		// == Fixed-Width Integer Limits (<cstdint>)
		{ "INT8_MIN",						Result::make( INT8_MIN ), },
		{ "INT8_MAX",						Result::make( INT8_MAX ), },
		{ "UINT8_MAX",						Result::make( UINT8_MAX ), },
		{ "INT16_MIN",						Result::make( INT16_MIN ), },
		{ "INT16_MAX",						Result::make( INT16_MAX ), },
		{ "UINT16_MAX",						Result::make( UINT16_MAX ), },
		{ "INT32_MIN",						Result::make( INT32_MIN ), },
		{ "INT32_MAX",						Result::make( INT32_MAX ), },
		{ "UINT32_MAX",						Result::make( UINT32_MAX ), },
		{ "INT64_MIN",						Result::make( INT64_MIN ), },
		{ "INT64_MAX",						Result::make( INT64_MAX ), },
		{ "UINT64_MAX",						Result::make( UINT64_MAX ), },

		// == Floating-Point Characteristics & Limits (<cfloat>)
		{ "FLT_RADIX",						Result::make( FLT_RADIX ), },
		{ "DECIMAL_DIG",					Result::make( DECIMAL_DIG ), },
		{ "FLT_DECIMAL_DIG",				Result::make( FLT_DECIMAL_DIG ), },
		{ "DBL_DECIMAL_DIG",				Result::make( DBL_DECIMAL_DIG ), },
		{ "LDBL_DECIMAL_DIG",				Result::make( LDBL_DECIMAL_DIG ), },
		{ "FLT_MIN",						Result::make( FLT_MIN ), },
		{ "DBL_MIN",						Result::make( DBL_MIN ), },
		{ "LDBL_MIN",						Result::make( LDBL_MIN ), },
		{ "FLT_TRUE_MIN",					Result::make( FLT_TRUE_MIN ), },
		{ "DBL_TRUE_MIN",					Result::make( DBL_TRUE_MIN ), },
		{ "LDBL_TRUE_MIN",					Result::make( LDBL_TRUE_MIN ), },
		{ "FLT_MAX",						Result::make( FLT_MAX ), },
		{ "DBL_MAX",						Result::make( DBL_MAX ), },
		{ "LDBL_MAX",						Result::make( LDBL_MAX ), },
		{ "FLT_EPSILON",					Result::make( FLT_EPSILON ), },
		{ "DBL_EPSILON",					Result::make( DBL_EPSILON ), },
		{ "LDBL_EPSILON",					Result::make( LDBL_EPSILON ), },
		{ "FLT_DIG",						Result::make( FLT_DIG ), },
		{ "DBL_DIG",						Result::make( DBL_DIG ), },
		{ "LDBL_DIG",						Result::make( LDBL_DIG ), },
		{ "FLT_MANT_DIG",					Result::make( FLT_MANT_DIG ), },
		{ "DBL_MANT_DIG",					Result::make( DBL_MANT_DIG ), },
		{ "LDBL_MANT_DIG",					Result::make( LDBL_MANT_DIG ), },
		{ "FLT_MIN_EXP",					Result::make( FLT_MIN_EXP ), },
		{ "DBL_MIN_EXP",					Result::make( DBL_MIN_EXP ), },
		{ "LDBL_MIN_EXP",					Result::make( LDBL_MIN_EXP ), },
		{ "FLT_MIN_10_EXP",					Result::make( FLT_MIN_10_EXP ), },
		{ "DBL_MIN_10_EXP",					Result::make( DBL_MIN_10_EXP ), },
		{ "LDBL_MIN_10_EXP",				Result::make( LDBL_MIN_10_EXP ), },
		{ "FLT_MAX_EXP",					Result::make( FLT_MAX_EXP ), },
		{ "DBL_MAX_EXP",					Result::make( DBL_MAX_EXP ), },
		{ "LDBL_MAX_EXP",					Result::make( LDBL_MAX_EXP ), },
		{ "FLT_MAX_10_EXP",					Result::make( FLT_MAX_10_EXP ), },
		{ "DBL_MAX_10_EXP",					Result::make( DBL_MAX_10_EXP ), },
		{ "LDBL_MAX_10_EXP",				Result::make( LDBL_MAX_10_EXP ), },

		// == Time (<ctime>)
		{ "CLOCKS_PER_SEC",					Result::make( CLOCKS_PER_SEC ), },

		// == Floating-Point Specials (<cmath>)
		{ "INFINITY",						Result::make( INFINITY ), },
		{ "NAN",							Result::make( NAN ), },
		{ "HUGE_VAL",						Result::make( HUGE_VAL ), },
		{ "HUGE_VALF",						Result::make( HUGE_VALF ), },
		{ "HUGE_VALL",						Result::make( HUGE_VALL ), },

		// == Maximum-Width Integer Limits (<cstdint>)
		{ "INTMAX_MIN",						Result::make( INTMAX_MIN ), },
		{ "INTMAX_MAX",						Result::make( INTMAX_MAX ), },
		{ "UINTMAX_MAX",					Result::make( UINTMAX_MAX ), },

		// == Pointer & Size Limits (<cstdint>)
		{ "INTPTR_MIN",						Result::make( INTPTR_MIN ), },
		{ "INTPTR_MAX",						Result::make( INTPTR_MAX ), },
		{ "UINTPTR_MAX",					Result::make( UINTPTR_MAX ), },
		{ "PTRDIFF_MIN",					Result::make( PTRDIFF_MIN ), },
		{ "PTRDIFF_MAX",					Result::make( PTRDIFF_MAX ), },
		{ "SIZE_MAX",						Result::make( SIZE_MAX ), },

		// == Wide Character & Atomic Limits (<cstdint>)
		{ "SIG_ATOMIC_MIN",					Result::make( SIG_ATOMIC_MIN ), },
		{ "SIG_ATOMIC_MAX",					Result::make( SIG_ATOMIC_MAX ), },
		{ "WCHAR_MIN",						Result::make( WCHAR_MIN ), },
		{ "WCHAR_MAX",						Result::make( WCHAR_MAX ), },
		{ "WINT_MIN",						Result::make( WINT_MIN ), },
		{ "WINT_MAX",						Result::make( WINT_MAX ), },

		// == Common C-Library Constants (<cstdlib> / <cstdio>)
		{ "RAND_MAX",						Result::make( RAND_MAX ), },
		//{ "EOF",							Result::make( EOF ), },

		// == Custom
		{ "_PI_",							Result::make( 3.1415926535897932384626433832795 ), },
		{ "_HALFPI_",						Result::make( 1.5707963267948966192313216916398 ), },
		{ "_E_",							Result::make( 2.7182818284590452353602874713527 ), },
		{ "_ZETA_",							Result::make( 1.202056903159594285399738161511449990764986292 ), },
		{ "_GR_",							Result::make( 1.6180339887498948482045868343656381177203091798057628621 ), },
		{ "_GOLDENRATIO_",					Result::make( 1.6180339887498948482045868343656381177203091798057628621 ), },
		{ "_GOLDENR_",						Result::make( 1.6180339887498948482045868343656381177203091798057628621 ), },
		{ "_GOLDENRAT_",					Result::make( 1.6180339887498948482045868343656381177203091798057628621 ), },
		{ "_GRATIO_",						Result::make( 1.6180339887498948482045868343656381177203091798057628621 ), },
		{ "_EULER_",						Result::make( 0.5772156649015328606065120900824024310421 ), },
		{ "_EULERMASCHERONI_",				Result::make( 0.5772156649015328606065120900824024310421 ), },
		{ "_MASCHERONI_",					Result::make( 0.5772156649015328606065120900824024310421 ), },
		{ "_EM_",							Result::make( 0.5772156649015328606065120900824024310421 ), },
		{ "_K_",							Result::make( 2.685452001065306445309714835481795693820382293994462953051152345557218 ), },
		{ "_KHINCHIN_",						Result::make( 2.685452001065306445309714835481795693820382293994462953051152345557218 ), },
		{ "_A_",							Result::make( 1.2824271291006226368753425688697917277676889273250011920637400217404 ), },
		{ "_GLAISHER_",						Result::make( 1.2824271291006226368753425688697917277676889273250011920637400217404 ), },
		{ "_GLAISHERKINKELIN_",				Result::make( 1.2824271291006226368753425688697917277676889273250011920637400217404 ), },
		{ "_KINKELIN_",						Result::make( 1.2824271291006226368753425688697917277676889273250011920637400217404 ), },
		{ "_M1_",							Result::make( 0.26149721284764278375542683860869585 ), },
		{ "_MEISSEL_",						Result::make( 0.26149721284764278375542683860869585 ), },
		{ "_MEISSELMERTENS_",				Result::make( 0.26149721284764278375542683860869585 ), },
		{ "_MERTENS_",						Result::make( 0.26149721284764278375542683860869585 ), },
		{ "_B_",							Result::make( 0.28016949902386913303 ), },
		{ "_BERNSTEIN_",					Result::make( 0.28016949902386913303 ), },
		{ "_LAMDA_",						Result::make( 0.30366300289873265859744812190155623 ), },
		{ "_LAMBDA_",						Result::make( 0.30366300289873265859744812190155623 ), },
		{ "_GWK_",							Result::make( 0.30366300289873265859744812190155623 ), },
		{ "_GAUSS_",						Result::make( 0.30366300289873265859744812190155623 ), },
		{ "_KUZMIN_",						Result::make( 0.30366300289873265859744812190155623 ), },
		{ "_WIRSING_",						Result::make( 0.30366300289873265859744812190155623 ), },
		{ "_GAUSSKUZMINWIRSING_",			Result::make( 0.30366300289873265859744812190155623 ), },
		{ "_SIGMA_",						Result::make( 0.35323637185499598454351655043268201 ), },
		{ "_HSMC_",							Result::make( 0.35323637185499598454351655043268201 ), },
		{ "_HSM_",							Result::make( 0.35323637185499598454351655043268201 ), },
		{ "_HAFNER_",						Result::make( 0.35323637185499598454351655043268201 ), },
		{ "_SARNAK_",						Result::make( 0.35323637185499598454351655043268201 ), },
		{ "_MCCURLEY_",						Result::make( 0.35323637185499598454351655043268201 ), },
		{ "_HAFNERSARNAKMCCURLEY_",			Result::make( 0.35323637185499598454351655043268201 ), },
		{ "_OMEGA_",						Result::make( 0.56714329040978387299996866221035554 ), },
		{ "_MU_",							Result::make( 0.62432998854355087099293638310083724 ), },
		{ "_GOLOMB_",						Result::make( 0.62432998854355087099293638310083724 ), },
		{ "_DICKMAN_",						Result::make( 0.62432998854355087099293638310083724 ), },
		{ "_GOLOMBDICKMAN_",				Result::make( 0.62432998854355087099293638310083724 ), },
		{ "_GD_",							Result::make( 0.62432998854355087099293638310083724 ), },
		{ "_CAHEN_",						Result::make( 0.6434105462 ), },
		{ "_C2_",							Result::make( 0.66016181584686957392781211001455577 ), },
		{ "_TWINPRIME_",					Result::make( 0.66016181584686957392781211001455577 ), },
		{ "_TP_",							Result::make( 0.66016181584686957392781211001455577 ), },
		{ "_LAPLACE_",						Result::make( 0.66274341934918158097474209710925290 ), },
		{ "_BETA_",							Result::make( 0.70258 ), },
		{ "_EMBREE_",						Result::make( 0.70258 ), },
		{ "_TREFETHEN_",					Result::make( 0.70258 ), },
		{ "_EMBREETREFETHEN_",				Result::make( 0.70258 ), },
		{ "_LANDAU_",						Result::make( 0.76422365358922066299069873125009232 ), },
		{ "_LANDAURAMANUJAN_",				Result::make( 0.76422365358922066299069873125009232 ), },
		{ "_ALLADI_",						Result::make( 0.8093940205 ), },
		{ "_GRINSTEAD_",					Result::make( 0.8093940205 ), },
		{ "_ALLADIGRINSTEAD_",				Result::make( 0.8093940205 ), },
		{ "_B4_",							Result::make( 0.87058838 ), },
		{ "_BRUN_",							Result::make( 0.87058838 ), },
		{ "_BRUNPRIMEQUADRUPLETS_",			Result::make( 0.87058838 ), },
		{ "_BRUNPQ_",						Result::make( 0.87058838 ), },
		{ "_BRUNPRIMEQUAD_",				Result::make( 0.87058838 ), },
		{ "_BRUNPRIMEQ_",					Result::make( 0.87058838 ), },
		{ "_CATALAN_",						Result::make( 0.91596559417721901505460351493238411 ), },
		{ "_LENGYEL_",						Result::make( 1.0986858055 ), },
		{ "_LENG_",							Result::make( 1.0986858055 ), },
		{ "_VISWANATH_",					Result::make( 1.13198824 ), },
		{ "_VISWAN_",						Result::make( 1.13198824 ), },
		{ "_VIS_",							Result::make( 1.13198824 ), },
		{ "_ZETA3_",						Result::make( 1.20205690315959428539973816151144999 ), },
		{ "_APERY_",						Result::make( 1.20205690315959428539973816151144999 ), },
		{ "_CONWAY_",						Result::make( 1.30357726903429639125709911215255189 ), },
		{ "_THETA_",						Result::make( 1.30637788386308069046861449260260571 ), },
		{ "_MILL_",							Result::make( 1.30637788386308069046861449260260571 ), },
		{ "_RHO_",							Result::make( 1.32471795724474602596090885447809734 ), },
		{ "_PLASTIC_",						Result::make( 1.32471795724474602596090885447809734 ), },
		{ "_RAMANUJAN_",					Result::make( 1.45136923488338105028396848589202744 ), },
		{ "_RAMAN_",						Result::make( 1.45136923488338105028396848589202744 ), },
		{ "_RAMAMU_",						Result::make( 1.45136923488338105028396848589202744 ), },
		{ "_SOLDNER_",						Result::make( 1.45136923488338105028396848589202744 ), },
		{ "_RAMANUJANSOLDNER_",				Result::make( 1.45136923488338105028396848589202744 ), },
		{ "_RS_",							Result::make( 1.45136923488338105028396848589202744 ), },
		{ "_RAMASOLDNER_",					Result::make( 1.45136923488338105028396848589202744 ), },
		{ "_RAMASOL_",						Result::make( 1.45136923488338105028396848589202744 ), },
		{ "_BLACKHOUSE_",					Result::make( 1.45607494858268967139959535111654356 ), },
		{ "_BH_",							Result::make( 1.45607494858268967139959535111654356 ), },
		{ "_PORTER_",						Result::make( 1.4670780794 ), },
		{ "_LIEB_",							Result::make( 1.5396007178 ), },
		{ "_SQUAREICE_",					Result::make( 1.5396007178 ), },
		{ "_SQICE_",						Result::make( 1.5396007178 ), },
		{ "_EB_",							Result::make( 1.60669515241529176378330152319092458 ), },
		{ "_ERDOS_",						Result::make( 1.60669515241529176378330152319092458 ), },
		{ "_BORWEIN_",						Result::make( 1.60669515241529176378330152319092458 ), },
		{ "_ERDOSBORWEIN_",					Result::make( 1.60669515241529176378330152319092458 ), },
		{ "_NIVEN_",						Result::make( 1.70521114010536776428855145343450816 ), },
		{ "_NIV_",							Result::make( 1.70521114010536776428855145343450816 ), },
		{ "_B2_",							Result::make( 1.902160583104 ), },
		{ "_BRUN2_",						Result::make( 1.902160583104 ), },
		{ "_BRUNTWINPRIME_",				Result::make( 1.902160583104 ), },
		{ "_BRUNTP_",						Result::make( 1.902160583104 ), },
		{ "_P2_",							Result::make( 2.29558714939263807403429804918949039 ), },
		{ "_PARABOLIC_",					Result::make( 2.29558714939263807403429804918949039 ), },
		{ "_ALPHA_",						Result::make( 2.50290787509589282228390287321821578 ), },
		{ "_FEIGENBAUM_",					Result::make( 2.50290787509589282228390287321821578 ), },
		{ "_FEIGENBAUMA_",					Result::make( 2.50290787509589282228390287321821578 ), },
		{ "_SIERP_",						Result::make( 2.58498175957925321706589358738317116 ), },
		{ "_SIERPINSKI_",					Result::make( 2.58498175957925321706589358738317116 ), },
		{ "_F_",							Result::make( 2.80777024202851936522150118655777293 ), },
		{ "_FRANSEN_",						Result::make( 2.80777024202851936522150118655777293 ), },
		{ "_ROBINSON_",						Result::make( 2.80777024202851936522150118655777293 ), },
		{ "_FRANSENROBINSON_",				Result::make( 2.80777024202851936522150118655777293 ), },
		{ "_LEVY_",							Result::make( 3.27582291872181115978768188245384386 ), },
		{ "_PSI_",							Result::make( 3.35988566624317755317201130291892717 ), },
		{ "_RECIPROCALFIBONACCI_",			Result::make( 3.35988566624317755317201130291892717 ), },
		{ "_RECIPFIBONACCI_",				Result::make( 3.35988566624317755317201130291892717 ), },
		{ "_RFIBONACCI_",					Result::make( 3.35988566624317755317201130291892717 ), },
		{ "_RF_",							Result::make( 3.35988566624317755317201130291892717 ), },
		{ "_DELTA_",						Result::make( 4.66920160910299067185320382046620161 ), },
		{ "_FEIGENBAUMD_",					Result::make( 4.66920160910299067185320382046620161 ), },

	};

	/** The static list of built-in functions. */
	const FunctionDef ExecutionContext::builtInFunctions[] = {
		// == Pow
		{ "pow", StringId::Desc_Pow, { { DataType::Double, "x", StringId::Desc_MathParam_PowX }, { DataType::Double, "y", StringId::VE_STR_POW_PARAM_Y } }, IntrinsicBridges::powBridge },
		{ "powf", StringId::Desc_Pow, { { DataType::Float, "x", StringId::Desc_MathParam_PowX }, { DataType::Float, "y", StringId::VE_STR_POW_PARAM_Y } }, IntrinsicBridges::powfBridge },

		// == Trigonometry
		{ "sin", StringId::Desc_Sin, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::sinBridge },
		{ "sinf", StringId::Desc_Sin, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::sinfBridge },
		
		{ "cos", StringId::Desc_Cos, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::cosBridge },
		{ "cosf", StringId::Desc_Cos, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::cosfBridge },
		
		{ "tan", StringId::Desc_Tan, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::tanBridge },
		{ "tanf", StringId::Desc_Tan, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::tanfBridge },

		// == Inverse Trigonometry
		{ "asin", StringId::Desc_Asin, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::asinBridge },
		{ "asinf", StringId::Desc_Asin, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::asinfBridge },
		
		{ "acos", StringId::Desc_Acos, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::acosBridge },
		{ "acosf", StringId::Desc_Acos, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::acosfBridge },
		
		{ "atan", StringId::Desc_Atan, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::atanBridge },
		{ "atanf", StringId::Desc_Atan, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::atanfBridge },
		
		{ "atan2", StringId::Desc_Atan2, { { DataType::Double, "y", StringId::Desc_MathParam_Y }, { DataType::Double, "x", StringId::Desc_MathParam_X } }, IntrinsicBridges::atan2Bridge },
		{ "atan2f", StringId::Desc_Atan2, { { DataType::Float, "y", StringId::Desc_MathParam_Y }, { DataType::Float, "x", StringId::Desc_MathParam_X } }, IntrinsicBridges::atan2fBridge },

		// == Exponential & Logarithmic
		{ "exp", StringId::Desc_Exp, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::expBridge },
		{ "expf", StringId::Desc_Exp, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::expfBridge },
		
		{ "log", StringId::Desc_Log, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::logBridge },
		{ "logf", StringId::Desc_Log, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::logfBridge },
		
		{ "log10", StringId::Desc_Log10, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log10Bridge },
		{ "log10f", StringId::Desc_Log10, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log10fBridge },

		// == Roots
		{ "sqrt", StringId::Desc_Sqrt, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::sqrtBridge },
		{ "sqrtf", StringId::Desc_Sqrt, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::sqrtfBridge },
		
		{ "cbrt", StringId::Desc_Cbrt, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::cbrtBridge },
		{ "cbrtf", StringId::Desc_Cbrt, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::cbrtfBridge },

		// == Rounding & Absolute Value
		{ "ceil", StringId::Desc_Ceil, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::ceilBridge },
		{ "ceilf", StringId::Desc_Ceil, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::ceilfBridge },
		
		{ "floor", StringId::Desc_Floor, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::floorBridge },
		{ "floorf", StringId::Desc_Floor, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::floorfBridge },
		
		{ "abs", StringId::Desc_Abs, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::absBridge },
		{ "fabs", StringId::Desc_Abs, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::fabsBridge },
		{ "fabsf", StringId::Desc_Abs, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::fabsfBridge },

		// == Hyperbolics
		{ "cosh", StringId::Desc_CosH, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::coshBridge },
		{ "coshf", StringId::Desc_CosH, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::coshfBridge },
		{ "sinh", StringId::Desc_SinH, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::sinhBridge },
		{ "sinhf", StringId::Desc_SinH, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::sinhfBridge },
		{ "tanh", StringId::Desc_TanH, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::tanhBridge },
		{ "tanhf", StringId::Desc_TanH, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::tanhfBridge },
		{ "acosh", StringId::Desc_AcosH, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::acoshBridge },
		{ "acoshf", StringId::Desc_AcosH, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::acoshfBridge },
		{ "asinh", StringId::Desc_AsinH, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::asinhBridge },
		{ "asinhf", StringId::Desc_AsinH, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::asinhfBridge },
		{ "atanh", StringId::Desc_AtanH, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::atanhBridge },
		{ "atanhf", StringId::Desc_AtanH, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::atanhfBridge },

		// == Extended Exponents & Logs
		{ "log2", StringId::Desc_Log2, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log2Bridge },
		{ "log2f", StringId::Desc_Log2, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log2fBridge },
		{ "exp2", StringId::Desc_Exp2, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::exp2Bridge },
		{ "exp2f", StringId::Desc_Exp2, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::exp2fBridge },
		{ "expm1", StringId::Desc_ExpM1, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::expm1Bridge },
		{ "expm1f", StringId::Desc_ExpM1, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::expm1fBridge },
		{ "ilogb", StringId::Desc_Log, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::ilogbBridge },
		{ "ilogbf", StringId::Desc_Log, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::ilogbfBridge },
		{ "log1p", StringId::Desc_Log, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log1pBridge },
		{ "log1pf", StringId::Desc_Log, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log1pfBridge },
		{ "logb", StringId::Desc_Log, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::logbBridge },
		{ "logbf", StringId::Desc_Log, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::logbfBridge },

		// == Misc Math
		{ "hypot", StringId::Desc_Hypot, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::hypotBridge },
		{ "hypotf", StringId::Desc_Hypot, { { DataType::Float, "x", StringId::Desc_MathParam_X }, { DataType::Float, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::hypotfBridge },
		{ "tgamma", StringId::Desc_TGamma, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::tgammaBridge },
		{ "tgammaf", StringId::Desc_TGamma, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::tgammafBridge },
		{ "lgamma", StringId::Desc_LGamma, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::lgammaBridge },
		{ "lgammaf", StringId::Desc_LGamma, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::lgammafBridge },
		{ "trunc", StringId::Desc_Trunc, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::truncBridge },
		{ "truncf", StringId::Desc_Trunc, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::truncfBridge },
		{ "round", StringId::Desc_Round, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::roundBridge },
		{ "roundf", StringId::Desc_Round, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::roundfBridge },
		{ "nearbyint", StringId::Desc_NearbyInt, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::nearbyintBridge },
		{ "nearbyintf", StringId::Desc_NearbyInt, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::nearbyintfBridge },

		// == Mod / Remainder
		{ "mod", StringId::Desc_Fmod, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::fmodBridge },
		{ "fmod", StringId::Desc_Fmod, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::fmodBridge },
		{ "fmodf", StringId::Desc_Fmod, { { DataType::Float, "x", StringId::Desc_MathParam_X }, { DataType::Float, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::fmodfBridge },
		{ "remainder", StringId::Desc_Remainder, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::remainderBridge },
		{ "remainderf", StringId::Desc_Remainder, { { DataType::Float, "x", StringId::Desc_MathParam_X }, { DataType::Float, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::remainderfBridge },
		// TODO: { "remquo", StringId::Desc_Fmod, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y }, { DataType::Pointer, "quo", StringId::VE_STR_MATH_PARAM_PTR } }, IntrinsicBridges::remquoBridge },
		
		// == Bounds & MADD
		{ "nextafter", StringId::Desc_NextAfter, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::nextafterBridge },
		{ "nextafterf", StringId::Desc_NextAfter, { { DataType::Float, "x", StringId::Desc_MathParam_X }, { DataType::Float, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::nextafterfBridge },
		{ "nexttoward", StringId::Desc_NextToward, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::nexttowardBridge },
		{ "nexttowardf", StringId::Desc_NextToward, { { DataType::Float, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::nexttowardfBridge },
		{ "dim", StringId::Desc_Fdim, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::fdimBridge },
		{ "fdim", StringId::Desc_Fdim, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::fdimBridge },
		{ "fdimf", StringId::Desc_Fdim, { { DataType::Float, "x", StringId::Desc_MathParam_X }, { DataType::Float, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::fdimfBridge },
		{ "max", StringId::Desc_Max, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::fmaxBridge },
		{ "min", StringId::Desc_Min, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::fminBridge },
		{ "madd", StringId::Desc_Fma, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y }, { DataType::Double, "z", StringId::Desc_MathParam_Z } }, IntrinsicBridges::fmaBridge },
		{ "fma", StringId::Desc_Fma, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y }, { DataType::Double, "z", StringId::Desc_MathParam_Z } }, IntrinsicBridges::fmaBridge },
		
		// == Type Identification / Logic
		{ "isnan", StringId::Desc_IsNan, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::isnanBridge },
		{ "isinf", StringId::Desc_IsInf, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::isinfBridge },

		// == Custom Helpers
		{ "rand", StringId::Desc_Rand, { }, IntrinsicBridges::randBridge },
		{ "deg", StringId::Desc_Deg, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::degBridge },
		{ "rad", StringId::Desc_Rad, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::radBridge },

		// == Bit Manipulation (<bit>)
		{ "byteswap16", StringId::Desc_ByteSwap16, { { DataType::UInt16, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::byteswap16Bridge },
		{ "byteswap32", StringId::Desc_ByteSwap32, { { DataType::UInt32, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::byteswap32Bridge },
		{ "byteswap64", StringId::Desc_ByteSwap, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::byteswap64Bridge },
		{ "byteswap", StringId::Desc_ByteSwap, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::byteswap64Bridge },
		{ "has_single_bit", StringId::Desc_HasSingleBit, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::has_single_bitBridge },
		{ "bit_ceil", StringId::Desc_BitCeil, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::bit_ceilBridge },
		{ "bit_floor", StringId::Desc_BitFloor, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::bit_floorBridge },
		{ "bit_width", StringId::Desc_BitWidth, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::bit_widthBridge },
		{ "rotl", StringId::Desc_RotL, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val }, { DataType::Int32, "s", StringId::Desc_BitParamS } }, IntrinsicBridges::rotlBridge },
		{ "rotr", StringId::Desc_RotR, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val }, { DataType::Int32, "s", StringId::Desc_BitParamS } }, IntrinsicBridges::rotrBridge },
		{ "countl_zero", StringId::Desc_CountLZero, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::countl_zeroBridge },
		{ "countl_one", StringId::Desc_CountLOne, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::countl_oneBridge },
		{ "countr_zero", StringId::Desc_CountRZero, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::countr_zeroBridge },
		{ "countr_one", StringId::Desc_CountROne, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::countr_oneBridge },
		{ "popcount", StringId::Desc_PopCount, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::popcountBridge },

		// == HTML
		{ "htmlCount", StringId::Desc_HtmlCount, {}, IntrinsicBridges::htmlCountBridge },
		{ "htmlName", StringId::Desc_HtmlName, { { DataType::Int64, "index", StringId::Desc_HtmlName_Index } }, IntrinsicBridges::htmlNameBridge },
		{ "htmlChar", StringId::Desc_HtmlChar, { { DataType::Int64, "indexOrName", StringId::Desc_HtmlChar_Arg } }, IntrinsicBridges::htmlCharBridge },

		// == Strings
		{ "capitalize", StringId::Desc_String_Capitalize, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::capitalizeBridge },
		{ "casefold", StringId::Desc_String_Casefold, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::casefoldBridge },
		{ "center", StringId::Desc_String_Center, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width } }, IntrinsicBridges::centerBridge },
		{ "center", StringId::Desc_String_Center, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width }, { DataType::Any, "fillchar", StringId::String_Param_FillChar } }, IntrinsicBridges::centerBridge },
		{ "count", StringId::Desc_String_Count, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub } }, IntrinsicBridges::countBridge },
		{ "count", StringId::Desc_String_Count, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub }, { DataType::Any, "start", StringId::String_Param_Start } }, IntrinsicBridges::countBridge },
		{ "count", StringId::Desc_String_Count, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub }, { DataType::Any, "start", StringId::String_Param_Start }, { DataType::Any, "end", StringId::String_Param_End } }, IntrinsicBridges::countBridge },
		{ "encode", StringId::Desc_String_Encode, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "encoding", StringId::String_Param_Encoding } }, IntrinsicBridges::encodeBridge },
		{ "encode", StringId::Desc_String_Encode, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "encoding", StringId::String_Param_Encoding }, { DataType::Any, "errors", StringId::String_Param_Errors } }, IntrinsicBridges::encodeBridge },
		{ "endswith", StringId::Desc_String_EndsWith, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "suffix", StringId::String_Param_Suffix } }, IntrinsicBridges::endsWithBridge },
		{ "endswith", StringId::Desc_String_EndsWith, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "suffix", StringId::String_Param_Suffix }, { DataType::Any, "start", StringId::String_Param_Start } }, IntrinsicBridges::endsWithBridge },
		{ "endswith", StringId::Desc_String_EndsWith, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "suffix", StringId::String_Param_Suffix }, { DataType::Any, "start", StringId::String_Param_Start }, { DataType::Any, "end", StringId::String_Param_End } }, IntrinsicBridges::endsWithBridge },
		{ "expandtabs", StringId::Desc_String_ExpandTabs, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::expandTabsBridge },
		{ "expandtabs", StringId::Desc_String_ExpandTabs, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "tabsize", StringId::String_Param_TabSize } }, IntrinsicBridges::expandTabsBridge },
		{ "find", StringId::Desc_String_Find, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub } }, IntrinsicBridges::findBridge },
		{ "find", StringId::Desc_String_Find, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub }, { DataType::Any, "start", StringId::String_Param_Start } }, IntrinsicBridges::findBridge },
		{ "find", StringId::Desc_String_Find, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub }, { DataType::Any, "start", StringId::String_Param_Start }, { DataType::Any, "end", StringId::String_Param_End } }, IntrinsicBridges::findBridge },
		{ "format", StringId::Desc_String_Format, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Variadic } }, IntrinsicBridges::formatBridge },
		{ "index", StringId::Desc_String_Find, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub } }, IntrinsicBridges::findBridge },
		{ "index", StringId::Desc_String_Find, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub }, { DataType::Any, "start", StringId::String_Param_Start } }, IntrinsicBridges::findBridge },
		{ "index", StringId::Desc_String_Find, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "sub", StringId::String_Param_Sub }, { DataType::Any, "start", StringId::String_Param_Start }, { DataType::Any, "end", StringId::String_Param_End } }, IntrinsicBridges::findBridge },
		{ "isalnum", StringId::Desc_String_IsAlnum, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isAlnumBridge },
		{ "isalpha", StringId::Desc_String_IsAlpha, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isAlphaBridge },
		{ "isascii", StringId::Desc_String_IsAscii, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isAsciiBridge },
		{ "isdecimal", StringId::Desc_String_IsDecimal, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isDecimalBridge },
		{ "isdigit", StringId::Desc_String_IsDigit, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isDigitBridge },
		{ "isidentifier", StringId::Desc_String_IsIdentifier, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::isIdentifierBridge },
		{ "isnumeric", StringId::Desc_String_IsNumeric, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isNumericBridge },
		{ "isprintable", StringId::Desc_String_IsPrintable, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isPrintableBridge },
		{ "isspace", StringId::Desc_String_IsSpace, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isSpaceBridge },
		{ "istitle", StringId::Desc_String_IsTitle, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::isTitleBridge },
		{ "isupper", StringId::Desc_String_IsUpper, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isUpperBridge },
		{ "ljust", StringId::Desc_String_LJust, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width } }, IntrinsicBridges::ljustBridge },
		{ "ljust", StringId::Desc_String_LJust, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width }, { DataType::Any, "fillchar", StringId::String_Param_Fillchar } }, IntrinsicBridges::ljustBridge },
		{ "lower", StringId::Desc_String_Lower, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::lowerBridge },
		{ "lstrip", StringId::Desc_String_LStrip, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::lstripBridge },
		{ "lstrip", StringId::Desc_String_LStrip, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "chars", StringId::String_Param_Chars } }, IntrinsicBridges::lstripBridge },
		{ "removeprefix", StringId::Desc_String_RemovePrefix, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "prefix", StringId::String_Param_Prefix } }, IntrinsicBridges::removePrefixBridge },
		{ "removesuffix", StringId::Desc_String_RemoveSuffix, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "suffix", StringId::String_Param_Suffix_RemoveSuffix } }, IntrinsicBridges::removeSuffixBridge },
		{ "replace", StringId::Desc_String_Replace, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "old", StringId::String_Param_Old }, { DataType::String, "new", StringId::String_Param_New } }, IntrinsicBridges::replaceBridge },
		{ "replace", StringId::Desc_String_Replace, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "old", StringId::String_Param_Old }, { DataType::String, "new", StringId::String_Param_New }, { DataType::Integer, "count", StringId::String_Param_Count } }, IntrinsicBridges::replaceBridge },
		{ "rfind", StringId::Desc_String_RFind, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "sub", StringId::String_Param_Sub_RFind } }, IntrinsicBridges::rfindBridge },
		{ "rfind", StringId::Desc_String_RFind, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "sub", StringId::String_Param_Sub_RFind }, { DataType::Integer, "start", StringId::String_Param_Start_RFind } }, IntrinsicBridges::rfindBridge },
		{ "rfind", StringId::Desc_String_RFind, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "sub", StringId::String_Param_Sub_RFind }, { DataType::Integer, "start", StringId::String_Param_Start_RFind }, { DataType::Integer, "end", StringId::String_Param_End_RFind } }, IntrinsicBridges::rfindBridge },
		{ "rindex", StringId::Desc_String_RFind, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "sub", StringId::String_Param_Sub_RFind } }, IntrinsicBridges::rfindBridge },
		{ "rindex", StringId::Desc_String_RFind, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "sub", StringId::String_Param_Sub_RFind }, { DataType::Integer, "start", StringId::String_Param_Start_RFind } }, IntrinsicBridges::rfindBridge },
		{ "rindex", StringId::Desc_String_RFind, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "sub", StringId::String_Param_Sub_RFind }, { DataType::Integer, "start", StringId::String_Param_Start_RFind }, { DataType::Integer, "end", StringId::String_Param_End_RFind } }, IntrinsicBridges::rfindBridge },
		{ "rjust", StringId::Desc_String_RJust, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width } }, IntrinsicBridges::rjustBridge },
		{ "rjust", StringId::Desc_String_RJust, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width }, { DataType::String, "fillchar", StringId::String_Param_Fillchar } }, IntrinsicBridges::rjustBridge },
		{ "rstrip", StringId::Desc_String_RStrip, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::rstripBridge },
		{ "rstrip", StringId::Desc_String_RStrip, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "chars", StringId::String_Param_Chars } }, IntrinsicBridges::rstripBridge },
		{ "startswith", StringId::Desc_String_StartsWith, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "prefix", StringId::String_Param_Prefix } }, IntrinsicBridges::startsWithBridge },
		{ "startswith", StringId::Desc_String_StartsWith, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "prefix", StringId::String_Param_Prefix }, { DataType::Integer, "start", StringId::String_Param_Start } }, IntrinsicBridges::startsWithBridge },
		{ "startswith", StringId::Desc_String_StartsWith, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "prefix", StringId::String_Param_Prefix }, { DataType::Integer, "start", StringId::String_Param_Start }, { DataType::Integer, "end", StringId::String_Param_End } }, IntrinsicBridges::startsWithBridge },
		{ "strip", StringId::Desc_String_Strip, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::stripBridge },
		{ "strip", StringId::Desc_String_Strip, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "chars", StringId::String_Param_Chars } }, IntrinsicBridges::stripBridge },
		{ "swapcase", StringId::Desc_String_SwapCase, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::swapcaseBridge },
		{ "title", StringId::Desc_String_Title, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::titleBridge },
		{ "upper", StringId::Desc_String_Upper, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::upperBridge },
		{ "zfill", StringId::Desc_String_ZFill, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width } }, IntrinsicBridges::zfillBridge },

		// == Strings/Vectors
		{ "at", StringId::Desc_Object_At, { { DataType::Any, "obj", StringId::String_Param_Target }, { DataType::Integer, "index", StringId::String_Param_Index } }, IntrinsicBridges::atBridge },
		{ "len", StringId::Desc_Object_Len, { { DataType::Any, "obj", StringId::String_Param_Target } }, IntrinsicBridges::lengthBridge },
		{ "push_back", StringId::Desc_Object_PushBack, { { DataType::Any, "obj", StringId::String_Param_Target }, { DataType::Any, "val", StringId::String_Param_Item } }, IntrinsicBridges::pushBackBridge },
		{ "size", StringId::Desc_Object_Size, { { DataType::Any, "obj", StringId::String_Param_Target } }, IntrinsicBridges::lengthBridge },

		// == Custom API.
		{ "min", StringId::Desc_Math_Min, { { DataType::Any, "x", StringId::Math_Param_X }, { DataType::Any, "y", StringId::Math_Param_Y } }, IntrinsicBridges::minBridge },
		{ "max", StringId::Desc_Math_Max, { { DataType::Any, "x", StringId::Math_Param_X }, { DataType::Any, "y", StringId::Math_Param_Y } }, IntrinsicBridges::maxBridge },
		{ "clamp", StringId::Desc_Math_Clamp, { { DataType::Any, "val", StringId::Math_Param_Val }, { DataType::Any, "minVal", StringId::Math_Param_Min }, { DataType::Any, "maxVal", StringId::Math_Param_Max } }, IntrinsicBridges::clampBridge },
		{ "frac", StringId::Desc_Math_Frac, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::fracBridge },
		{ "step", StringId::Desc_Math_Step, { { DataType::Double, "edge", StringId::Math_Param_Edge }, { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::stepBridge },
		{ "sinc", StringId::Desc_Math_Sinc, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sincBridge },
		{ "relativeEpsilon", StringId::Desc_Math_RelativeEpsilon, { { DataType::Double, "left", StringId::Math_Param_Left }, { DataType::Double, "right", StringId::Math_Param_Right }, { DataType::Double, "epsilon", StringId::Math_Param_Epsilon } }, IntrinsicBridges::relativeEpsilonBridge },
		{ "sinExact", StringId::Desc_Math_SinExact, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sinExactBridge },
		{ "cosExact", StringId::Desc_Math_CosExact, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::cosExactBridge },
		{ "lcm", StringId::Desc_Math_Lcm, { { DataType::Integer, "x", StringId::Math_Param_X }, { DataType::Integer, "y", StringId::Math_Param_Y } }, IntrinsicBridges::lcmBridge },
		//{ "lcmChecked", StringId::Desc_Math_LcmChecked, { { DataType::Integer, "x", StringId::Math_Param_X }, { DataType::Integer, "y", StringId::Math_Param_Y } }, IntrinsicBridges::lcmCheckedBridge },

		// == Gamma Functions.
		{ "linearToSRgb", StringId::Desc_Math_LinearToSRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSRgbBridge },
		{ "sRgbToLinear", StringId::Desc_Math_SRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sRgbToLinearBridge },
		{ "pow2_2ToLinear", StringId::Desc_Math_Pow2_2ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::pow2_2ToLinearBridge },
		{ "linearToPow2_2", StringId::Desc_Math_LinearToPow2_2, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToPow2_2Bridge },
		{ "smpte240MToLinear", StringId::Desc_Math_Smpte240MToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::smpte240MToLinearBridge },
		{ "linearToSmpte240M", StringId::Desc_Math_LinearToSmpte240M, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSmpte240MBridge },
		{ "sLog2ToLinear", StringId::Desc_Math_SLog2ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sLog2ToLinearBridge },
		{ "linearToSLog2", StringId::Desc_Math_LinearToSLog2, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSLog2Bridge },
		{ "canonLogToLinear", StringId::Desc_Math_CanonLogToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::canonLogToLinearBridge },
		{ "linearToCanonLog", StringId::Desc_Math_LinearToCanonLog, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToCanonLogBridge },
		{ "viperToLinear", StringId::Desc_Math_ViperToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::viperToLinearBridge },
		{ "linearToViper", StringId::Desc_Math_LinearToViper, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToViperBridge },
		{ "acesCgToLinear", StringId::Desc_Math_AcesCgToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::acesCgToLinearBridge },
		{ "linearToAcesCg", StringId::Desc_Math_LinearToAcesCg, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToAcesCgBridge },
		{ "sRgbToLinearPrecise", StringId::Desc_Math_SRgbToLinearPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sRgbToLinearPreciseBridge },
		{ "linearToSRgbPrecise", StringId::Desc_Math_LinearToSRgbPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSRgbPreciseBridge },
		{ "colorLcdToLinear", StringId::Desc_Math_ColorLcdToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::colorLcdToLinearBridge },
		{ "linearToColorLcd", StringId::Desc_Math_LinearToColorLcd, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToColorLcdBridge },
		{ "smpte170MToLinear", StringId::Desc_Math_Smpte170MToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::smpte170MToLinearBridge },
		{ "linearToSmpte170M", StringId::Desc_Math_LinearToSmpte170M, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSmpte170MBridge },
		{ "smpte170MToLinearPrecise", StringId::Desc_Math_Smpte170MToLinearPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::smpte170MToLinearPreciseBridge },
		{ "linearToSmpte170MPrecise", StringId::Desc_Math_LinearToSmpte170MPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSmpte170MPreciseBridge },
		{ "dciP3ToLinear", StringId::Desc_Math_DciP3ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::dciP3ToLinearBridge },
		{ "linearToDciP3", StringId::Desc_Math_LinearToDciP3, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToDciP3Bridge },
		{ "genericRgbToLinear", StringId::Desc_Math_GenericRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::genericRgbToLinearBridge },
		{ "linearToGenericRgb", StringId::Desc_Math_LinearToGenericRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToGenericRgbBridge },
		{ "pow2_8ToLinear", StringId::Desc_Math_Pow2_8ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::pow2_8ToLinearBridge },
		{ "linearToPow2_8", StringId::Desc_Math_LinearToPow2_8, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToPow2_8Bridge },
		{ "adobeRgbToLinear", StringId::Desc_Math_AdobeRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::adobeRgbToLinearBridge },
		{ "linearToAdobeRgb", StringId::Desc_Math_LinearToAdobeRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToAdobeRgbBridge },
		{ "smpte240MToLinearPrecise", StringId::Desc_Math_Smpte240MToLinearPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::smpte240MToLinearPreciseBridge },
		{ "linearToSmpte240MPrecise", StringId::Desc_Math_LinearToSmpte240MPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSmpte240MPreciseBridge },
		{ "acesCcToLinear", StringId::Desc_Math_AcesCcToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::acesCcToLinearBridge },
		{ "linearToAcesCc", StringId::Desc_Math_LinearToAcesCc, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToAcesCcBridge },
		{ "rommRgbToLinear", StringId::Desc_Math_RommRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::rommRgbToLinearBridge },
		{ "linearToRommRgb", StringId::Desc_Math_LinearToRommRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToRommRgbBridge },
		{ "rimmRgbToLinear", StringId::Desc_Math_RimmRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::rimmRgbToLinearBridge },
		{ "linearToRimmRgb", StringId::Desc_Math_LinearToRimmRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToRimmRgbBridge },
		{ "erimmRgbToLinear", StringId::Desc_Math_ErimmRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::erimmRgbToLinearBridge },
		{ "linearToErimmRgb", StringId::Desc_Math_LinearToErimmRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToErimmRgbBridge },
		{ "sLogToLinear", StringId::Desc_Math_SLogToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sLogToLinearBridge },
		{ "linearToSLog", StringId::Desc_Math_LinearToSLog, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSLogBridge },
		{ "sLog3ToLinear", StringId::Desc_Math_SLog3ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sLog3ToLinearBridge },
		{ "linearToSLog3", StringId::Desc_Math_LinearToSLog3, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSLog3Bridge },
		{ "protuneToLinear", StringId::Desc_Math_ProtuneToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::protuneToLinearBridge },
		{ "linearToProtune", StringId::Desc_Math_LinearToProtune, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToProtuneBridge },
		{ "canonLog2ToLinear", StringId::Desc_Math_CanonLog2ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::canonLog2ToLinearBridge },
		{ "linearToCanonLog2", StringId::Desc_Math_LinearToCanonLog2, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToCanonLog2Bridge },
		{ "canonLog3ToLinear", StringId::Desc_Math_CanonLog3ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::canonLog3ToLinearBridge },
		{ "linearToCanonLog3", StringId::Desc_Math_LinearToCanonLog3, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToCanonLog3Bridge },
		{ "aribStdB67ToLinear", StringId::Desc_Math_AribStdB67ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::aribStdB67ToLinearBridge },
		{ "linearToAribStdB67", StringId::Desc_Math_LinearToAribStdB67, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToAribStdB67Bridge },
		{ "panalogToLinear", StringId::Desc_Math_PanalogToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::panalogToLinearBridge },
		{ "linearToPanalog", StringId::Desc_Math_LinearToPanalog, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToPanalogBridge },
		{ "crtProperToLinear", StringId::Desc_Math_CrtProperToLinear, { { DataType::Double, "val", StringId::Math_Param_Val } }, IntrinsicBridges::crtProperToLinearBridge },
		{ "crtProperToLinear", StringId::Desc_Math_CrtProperToLinear, { { DataType::Double, "val", StringId::Math_Param_Val }, { DataType::Double, "lw", StringId::Math_Param_Lw } }, IntrinsicBridges::crtProperToLinearBridge },
		{ "crtProperToLinear", StringId::Desc_Math_CrtProperToLinear, { { DataType::Double, "val", StringId::Math_Param_Val }, { DataType::Double, "lw", StringId::Math_Param_Lw }, { DataType::Double, "b", StringId::Math_Param_B } }, IntrinsicBridges::crtProperToLinearBridge },
		{ "linearToCrtProper", StringId::Desc_Math_LinearToCrtProper, { { DataType::Double, "val", StringId::Math_Param_Val } }, IntrinsicBridges::linearToCrtProperBridge },
		{ "linearToCrtProper", StringId::Desc_Math_LinearToCrtProper, { { DataType::Double, "val", StringId::Math_Param_Val }, { DataType::Double, "lw", StringId::Math_Param_Lw } }, IntrinsicBridges::linearToCrtProperBridge },
		{ "linearToCrtProper", StringId::Desc_Math_LinearToCrtProper, { { DataType::Double, "val", StringId::Math_Param_Val }, { DataType::Double, "lw", StringId::Math_Param_Lw }, { DataType::Double, "b", StringId::Math_Param_B } }, IntrinsicBridges::linearToCrtProperBridge },
		{ "crtProper2ToLinear", StringId::Desc_Math_CrtProper2ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::crtProper2ToLinearBridge },
		{ "linearToCrtProper2", StringId::Desc_Math_LinearToCrtProper2, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToCrtProper2Bridge },
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
		// TODO: errorOut should go through a localizer.
		try {
			reset();

			for (size_t i = 0; i < std::size(builtInConsts); ++i) {
				registerConstant( builtInConsts[i].name, builtInConsts[i].result );
			}
			for (size_t i = 0; i < std::size(builtInFunctions); ++i) {
				registerFunction(builtInFunctions[i].name, builtInFunctions[i].parameters, builtInFunctions[i].callback);
			}

			antlr4::ANTLRInputStream input(expression);
			ExprLexer lexer(&input);
			antlr4::CommonTokenStream tokens(&lexer);
			ExprParser parser(&tokens);
			parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

			antlr4::tree::ParseTree* tree = parser.prog();
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
		return arena.nodes[rootIndex]->evaluate(*this);
	}

	/**
	 * Resets the object back to scratch.
	 **/
	void ExecutionContext::reset() {
		// Clear objects first.  Who knows what kinds of resources they may need to access, so
		// don’t clear resources until objects are already gone.
		objects.clear();
		initialObjectsTotal = 0;

		arena.nodes.clear();
		variables.clear();
		registeredConstants.clear();
		registeredFunctions.clear();
		rootIndex = 0;

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
	 * Converts a Result into its formatted string representation.
	 * Must be called within a try/catch block.
	 *
	 * \param res			The Result to convert.
	 * \param formatStr		The format string to apply.
	 * \param flags			Bitmask defining formatting rules (defaults to 0).
	 * \return				Returns the formatted string representation of the Result.
	 **/
	std::string ExecutionContext::formattedString(const Result& res, const std::string& formatStr, uint32_t flags) const {
		switch (res.type) {
			case NumericConstant::Unsigned : {
				return std::vformat(formatStr, std::make_format_args(res.value.uintVal));
			}
			case NumericConstant::Signed : {
				return std::vformat(formatStr, std::make_format_args(res.value.intVal));
			}
			case NumericConstant::Floating : {
				return std::vformat(formatStr, std::make_format_args(res.value.doubleVal));
			}
			case NumericConstant::Object : {
				if (res.value.objectVal) {
					return res.value.objectVal->formattedString(formatStr, flags);
				}
				return "<null>";
			}
			case NumericConstant::Invalid :
			default : {
				return "";
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
					break;
				}
				default : { break; }
			}
		}
		else if (res.type == NumericConstant::Object) {
			if (!res.value.objectVal) {
				out.type = NumericConstant::Invalid;
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
			if (!leftVal.value.objectVal) { return Result{ .type = NumericConstant::Invalid }; }
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
				default : { return Result{ .type = NumericConstant::Invalid }; }
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
				default : { return Result{ .type = NumericConstant::Invalid }; }
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
				default : { return Result{ .type = NumericConstant::Invalid }; }
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
				default : { return Result{ .type = NumericConstant::Invalid }; }
			}
		}
		else if (common == NumericConstant::Object) {
			if (!l.value.objectVal || !r.value.objectVal) { return Result{ .type = NumericConstant::Invalid }; }
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
				default : { return Result{ .type = NumericConstant::Invalid }; }
			}
		}
		else {
			return Result{ .type = NumericConstant::Invalid };
		}

		return out;
	}

}	// namespace ve
