#include "ExecutionContext.h"
#include "IntrinsicBridges.h"
#include "../Compiler/AstBuilderVisitor.h"
#include "../../generated/ExprLexer.h"
#include "../../generated/ExprParser.h"

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

			antlr4::tree::ParseTree* tree = parser.prog();

			AstBuilderVisitor visitor(*this);
			std::any resultAny = visitor.visit(tree);

			if (resultAny.has_value()) {
				rootIndex = std::any_cast<size_t>(resultAny);
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
		return arena.nodes[rootIndex]->evaluate(*this);
	}

	/**
	 * Resets the object back to scratch.
	 **/
	void ExecutionContext::reset() {
		// Clear objects first.  Who knows what kinds of resources they may need to access, so
		// don’t clear resources until objects are already gone.
		objects.clear();

		arena.nodes.clear();
		variables.clear();
		registeredConstants.clear();
		registeredFunctions.clear();
		rootIndex = 0;

		// Don’t change settings such as treatAllAsHex.
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
			case DataType::Any : {
				out = rawVal;
				break;
			}
		}
		
		return out;
	}

}	// namespace ve
