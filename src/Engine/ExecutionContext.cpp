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
		{ "pow", StringId::VE_STR_POW_DESC, { { DataType::Double, "x", StringId::VE_STR_POW_PARAM_X }, { DataType::Double, "y", StringId::VE_STR_POW_PARAM_Y } }, IntrinsicBridges::powBridge },
		{ "powf", StringId::VE_STR_POW_DESC, { { DataType::Float, "x", StringId::VE_STR_POW_PARAM_X }, { DataType::Float, "y", StringId::VE_STR_POW_PARAM_Y } }, IntrinsicBridges::powfBridge },

		// == Trigonometry
		{ "sin", StringId::VE_STR_SIN_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_ANGLE } }, IntrinsicBridges::sinBridge },
		{ "sinf", StringId::VE_STR_SIN_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_ANGLE } }, IntrinsicBridges::sinfBridge },
		
		{ "cos", StringId::VE_STR_COS_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_ANGLE } }, IntrinsicBridges::cosBridge },
		{ "cosf", StringId::VE_STR_COS_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_ANGLE } }, IntrinsicBridges::cosfBridge },
		
		{ "tan", StringId::VE_STR_TAN_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_ANGLE } }, IntrinsicBridges::tanBridge },
		{ "tanf", StringId::VE_STR_TAN_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_ANGLE } }, IntrinsicBridges::tanfBridge },

		// == Inverse Trigonometry
		{ "asin", StringId::VE_STR_ASIN_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::asinBridge },
		{ "asinf", StringId::VE_STR_ASIN_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::asinfBridge },
		
		{ "acos", StringId::VE_STR_ACOS_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::acosBridge },
		{ "acosf", StringId::VE_STR_ACOS_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::acosfBridge },
		
		{ "atan", StringId::VE_STR_ATAN_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::atanBridge },
		{ "atanf", StringId::VE_STR_ATAN_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::atanfBridge },
		
		{ "atan2", StringId::VE_STR_ATAN2_DESC, { { DataType::Double, "y", StringId::VE_STR_MATH_PARAM_Y }, { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_X } }, IntrinsicBridges::atan2Bridge },
		{ "atan2f", StringId::VE_STR_ATAN2_DESC, { { DataType::Float, "y", StringId::VE_STR_MATH_PARAM_Y }, { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_X } }, IntrinsicBridges::atan2fBridge },

		// == Exponential & Logarithmic
		{ "exp", StringId::VE_STR_EXP_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::expBridge },
		{ "expf", StringId::VE_STR_EXP_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::expfBridge },
		
		{ "log", StringId::VE_STR_LOG_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::logBridge },
		{ "logf", StringId::VE_STR_LOG_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::logfBridge },
		
		{ "log10", StringId::VE_STR_LOG10_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::log10Bridge },
		{ "log10f", StringId::VE_STR_LOG10_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::log10fBridge },

		// == Roots
		{ "sqrt", StringId::VE_STR_SQRT_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::sqrtBridge },
		{ "sqrtf", StringId::VE_STR_SQRT_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::sqrtfBridge },
		
		{ "cbrt", StringId::VE_STR_CBRT_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::cbrtBridge },
		{ "cbrtf", StringId::VE_STR_CBRT_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::cbrtfBridge },

		// == Rounding & Absolute Value
		{ "ceil", StringId::VE_STR_CEIL_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::ceilBridge },
		{ "ceilf", StringId::VE_STR_CEIL_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::ceilfBridge },
		
		{ "floor", StringId::VE_STR_FLOOR_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::floorBridge },
		{ "floorf", StringId::VE_STR_FLOOR_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::floorfBridge },
		
		{ "abs", StringId::VE_STR_ABS_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::absBridge },
		{ "fabs", StringId::VE_STR_ABS_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::fabsBridge },
		{ "fabsf", StringId::VE_STR_ABS_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::fabsfBridge },

		// == Hyperbolics
		{ "cosh", StringId::VE_STR_COSH_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_ANGLE } }, IntrinsicBridges::coshBridge },
		{ "coshf", StringId::VE_STR_COSH_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_ANGLE } }, IntrinsicBridges::coshfBridge },
		{ "sinh", StringId::VE_STR_SINH_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_ANGLE } }, IntrinsicBridges::sinhBridge },
		{ "sinhf", StringId::VE_STR_SINH_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_ANGLE } }, IntrinsicBridges::sinhfBridge },
		{ "tanh", StringId::VE_STR_TANH_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_ANGLE } }, IntrinsicBridges::tanhBridge },
		{ "tanhf", StringId::VE_STR_TANH_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_ANGLE } }, IntrinsicBridges::tanhfBridge },
		{ "acosh", StringId::VE_STR_ACOSH_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::acoshBridge },
		{ "acoshf", StringId::VE_STR_ACOSH_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::acoshfBridge },
		{ "asinh", StringId::VE_STR_ASINH_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::asinhBridge },
		{ "asinhf", StringId::VE_STR_ASINH_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::asinhfBridge },
		{ "atanh", StringId::VE_STR_ATANH_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::atanhBridge },
		{ "atanhf", StringId::VE_STR_ATANH_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::atanhfBridge },

		// == Extended Exponents & Logs
		{ "log2", StringId::VE_STR_LOG2_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::log2Bridge },
		{ "log2f", StringId::VE_STR_LOG2_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::log2fBridge },
		{ "exp2", StringId::VE_STR_EXP2_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::exp2Bridge },
		{ "exp2f", StringId::VE_STR_EXP2_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::exp2fBridge },
		{ "expm1", StringId::VE_STR_EXPM1_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::expm1Bridge },
		{ "expm1f", StringId::VE_STR_EXPM1_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::expm1fBridge },
		{ "ilogb", StringId::VE_STR_LOG_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::ilogbBridge },
		{ "ilogbf", StringId::VE_STR_LOG_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::ilogbfBridge },
		{ "log1p", StringId::VE_STR_LOG_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::log1pBridge },
		{ "log1pf", StringId::VE_STR_LOG_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::log1pfBridge },
		{ "logb", StringId::VE_STR_LOG_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::logbBridge },
		{ "logbf", StringId::VE_STR_LOG_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::logbfBridge },

		// == Misc Math
		{ "hypot", StringId::VE_STR_HYPOT_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Double, "y", StringId::VE_STR_MATH_PARAM_Y } }, IntrinsicBridges::hypotBridge },
		{ "hypotf", StringId::VE_STR_HYPOT_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Float, "y", StringId::VE_STR_MATH_PARAM_Y } }, IntrinsicBridges::hypotfBridge },
		{ "tgamma", StringId::VE_STR_TGAMMA_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::tgammaBridge },
		{ "tgammaf", StringId::VE_STR_TGAMMA_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::tgammafBridge },
		{ "lgamma", StringId::VE_STR_LGAMMA_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::lgammaBridge },
		{ "lgammaf", StringId::VE_STR_LGAMMA_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::lgammafBridge },
		{ "trunc", StringId::VE_STR_TRUNC_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::truncBridge },
		{ "truncf", StringId::VE_STR_TRUNC_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::truncfBridge },
		{ "round", StringId::VE_STR_ROUND_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::roundBridge },
		{ "roundf", StringId::VE_STR_ROUND_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::roundfBridge },
		{ "nearbyint", StringId::VE_STR_ROUND_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::nearbyintBridge },
		{ "nearbyintf", StringId::VE_STR_ROUND_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::nearbyintfBridge },

		// == Mod / Remainder
		{ "mod", StringId::VE_STR_FMOD_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Double, "y", StringId::VE_STR_MATH_PARAM_Y } }, IntrinsicBridges::fmodBridge },
		{ "fmod", StringId::VE_STR_FMOD_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Double, "y", StringId::VE_STR_MATH_PARAM_Y } }, IntrinsicBridges::fmodBridge },
		{ "fmodf", StringId::VE_STR_FMOD_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Float, "y", StringId::VE_STR_MATH_PARAM_Y } }, IntrinsicBridges::fmodfBridge },
		{ "remainder", StringId::VE_STR_FMOD_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Double, "y", StringId::VE_STR_MATH_PARAM_Y } }, IntrinsicBridges::remainderBridge },
		{ "remainderf", StringId::VE_STR_FMOD_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Float, "y", StringId::VE_STR_MATH_PARAM_Y } }, IntrinsicBridges::remainderfBridge },
		// TODO: { "remquo", StringId::VE_STR_FMOD_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Double, "y", StringId::VE_STR_MATH_PARAM_Y }, { DataType::Pointer, "quo", StringId::VE_STR_MATH_PARAM_PTR } }, IntrinsicBridges::remquoBridge },
		
		// == Bounds & MADD
		{ "nextafter", StringId::VE_STR_MAX_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Double, "y", StringId::VE_STR_MATH_PARAM_Y } }, IntrinsicBridges::nextafterBridge },
		{ "nextafterf", StringId::VE_STR_MAX_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Float, "y", StringId::VE_STR_MATH_PARAM_Y } }, IntrinsicBridges::nextafterfBridge },
		{ "nexttoward", StringId::VE_STR_MAX_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Double, "y", StringId::VE_STR_MATH_PARAM_Y } }, IntrinsicBridges::nexttowardBridge },
		{ "nexttowardf", StringId::VE_STR_MAX_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Double, "y", StringId::VE_STR_MATH_PARAM_Y } }, IntrinsicBridges::nexttowardfBridge },
		{ "dim", StringId::VE_STR_MAX_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Double, "y", StringId::VE_STR_MATH_PARAM_Y } }, IntrinsicBridges::fdimBridge },
		{ "fdim", StringId::VE_STR_MAX_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Double, "y", StringId::VE_STR_MATH_PARAM_Y } }, IntrinsicBridges::fdimBridge },
		{ "fdimf", StringId::VE_STR_MAX_DESC, { { DataType::Float, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Float, "y", StringId::VE_STR_MATH_PARAM_Y } }, IntrinsicBridges::fdimfBridge },
		{ "max", StringId::VE_STR_MAX_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Double, "y", StringId::VE_STR_MATH_PARAM_Y } }, IntrinsicBridges::fmaxBridge },
		{ "min", StringId::VE_STR_MIN_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Double, "y", StringId::VE_STR_MATH_PARAM_Y } }, IntrinsicBridges::fminBridge },
		{ "madd", StringId::VE_STR_FMA_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Double, "y", StringId::VE_STR_MATH_PARAM_Y }, { DataType::Double, "z", StringId::VE_STR_MATH_PARAM_Z } }, IntrinsicBridges::fmaBridge },
		{ "fma", StringId::VE_STR_FMA_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_X }, { DataType::Double, "y", StringId::VE_STR_MATH_PARAM_Y }, { DataType::Double, "z", StringId::VE_STR_MATH_PARAM_Z } }, IntrinsicBridges::fmaBridge },
		
		// == Type Identification / Logic
		{ "isnan", StringId::VE_STR_ISNAN_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::isnanBridge },
		{ "isinf", StringId::VE_STR_ISINF_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::isinfBridge },

		// == Custom Helpers
		{ "rand", StringId::VE_STR_RAND_DESC, { }, IntrinsicBridges::randBridge },
		{ "deg", StringId::VE_STR_DEG_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_ANGLE } }, IntrinsicBridges::degBridge },
		{ "rad", StringId::VE_STR_RAD_DESC, { { DataType::Double, "x", StringId::VE_STR_MATH_PARAM_ANGLE } }, IntrinsicBridges::radBridge },

		// == Bit Manipulation (<bit>)
		{ "byteswap16", StringId::VE_STR_BYTESWAP16_DESC, { { DataType::UInt16, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::byteswap16Bridge },
		{ "byteswap32", StringId::VE_STR_BYTESWAP32_DESC, { { DataType::UInt32, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::byteswap32Bridge },
		{ "byteswap64", StringId::VE_STR_BYTESWAP_DESC, { { DataType::UInt64, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::byteswap64Bridge },
		{ "byteswap", StringId::VE_STR_BYTESWAP_DESC, { { DataType::UInt64, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::byteswap64Bridge },
		{ "has_single_bit", StringId::VE_STR_HAS_SINGLE_BIT_DESC, { { DataType::UInt64, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::has_single_bitBridge },
		{ "bit_ceil", StringId::VE_STR_BIT_CEIL_DESC, { { DataType::UInt64, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::bit_ceilBridge },
		{ "bit_floor", StringId::VE_STR_BIT_FLOOR_DESC, { { DataType::UInt64, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::bit_floorBridge },
		{ "bit_width", StringId::VE_STR_BIT_WIDTH_DESC, { { DataType::UInt64, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::bit_widthBridge },
		{ "rotl", StringId::VE_STR_ROTL_DESC, { { DataType::UInt64, "x", StringId::VE_STR_MATH_PARAM_VAL }, { DataType::Int32, "s", StringId::VE_STR_BIT_PARAM_S } }, IntrinsicBridges::rotlBridge },
		{ "rotr", StringId::VE_STR_ROTR_DESC, { { DataType::UInt64, "x", StringId::VE_STR_MATH_PARAM_VAL }, { DataType::Int32, "s", StringId::VE_STR_BIT_PARAM_S } }, IntrinsicBridges::rotrBridge },
		{ "countl_zero", StringId::VE_STR_COUNTL_ZERO_DESC, { { DataType::UInt64, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::countl_zeroBridge },
		{ "countl_one", StringId::VE_STR_COUNTL_ONE_DESC, { { DataType::UInt64, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::countl_oneBridge },
		{ "countr_zero", StringId::VE_STR_COUNTR_ZERO_DESC, { { DataType::UInt64, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::countr_zeroBridge },
		{ "countr_one", StringId::VE_STR_COUNTR_ONE_DESC, { { DataType::UInt64, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::countr_oneBridge },
		{ "popcount", StringId::VE_STR_POPCOUNT_DESC, { { DataType::UInt64, "x", StringId::VE_STR_MATH_PARAM_VAL } }, IntrinsicBridges::popcountBridge },
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
		arena.nodes.clear();
		variables.clear();
		registeredConstants.clear();
		registeredFunctions.clear();
		rootIndex = 0;
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
				// TODO.
				out.type = NumericConstant::Invalid; 
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
		}
		
		return out;
	}

}	// namespace ve
