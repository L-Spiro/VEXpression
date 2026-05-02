#include "../../generated/ExprLexer.h"
#include "../../generated/ExprParser.h"
#include "../Compiler/AstBuilderVisitor.h"
#include "BFloat16.h"
#include "ExecutionContext.h"
#include "Float16.h"
#include "IntrinsicBridges.h"
#include "SimdBridges.h"

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

		// == SIMD.
		{ "_MM_HINT_NTA",					Result::make( SIMDE_MM_HINT_NTA ), },
		{ "_MM_HINT_T0",					Result::make( SIMDE_MM_HINT_T0 ), },
		{ "_MM_HINT_T1",					Result::make( SIMDE_MM_HINT_T1 ), },
		{ "_MM_HINT_T2",					Result::make( SIMDE_MM_HINT_T2 ), },
		{ "_MM_HINT_ENTA",					Result::make( SIMDE_MM_HINT_ENTA ), },

		{ "_MM_HINT_IT0",					Result::make( 7 ), },
		{ "_MM_HINT_IT1",					Result::make( 6 ), },
		{ "_MM_EXCEPT_MASK",				Result::make( SIMDE_MM_EXCEPT_MASK ), },
		{ "_MM_EXCEPT_INVALID",				Result::make( SIMDE_MM_EXCEPT_INVALID ), },
		{ "_MM_EXCEPT_DENORM",				Result::make( SIMDE_MM_EXCEPT_DENORM ), },
		{ "_MM_EXCEPT_DIV_ZERO",			Result::make( SIMDE_MM_EXCEPT_DIV_ZERO ), },
		{ "_MM_EXCEPT_OVERFLOW",			Result::make( SIMDE_MM_EXCEPT_OVERFLOW ), },
		{ "_MM_EXCEPT_UNDERFLOW",			Result::make( SIMDE_MM_EXCEPT_UNDERFLOW ), },
		{ "_MM_EXCEPT_INEXACT",				Result::make( SIMDE_MM_EXCEPT_INEXACT ), },

		{ "_MM_MASK_MASK",					Result::make( SIMDE_MM_MASK_MASK ), },
		{ "_MM_MASK_INVALID",				Result::make( SIMDE_MM_MASK_INVALID ), },
		{ "_MM_MASK_DENORM",				Result::make( SIMDE_MM_MASK_DENORM ), },
		{ "_MM_MASK_DIV_ZERO",				Result::make( SIMDE_MM_MASK_DIV_ZERO ), },
		{ "_MM_MASK_OVERFLOW",				Result::make( SIMDE_MM_MASK_OVERFLOW ), },
		{ "_MM_MASK_UNDERFLOW",				Result::make( SIMDE_MM_MASK_UNDERFLOW ), },
		{ "_MM_MASK_INEXACT",				Result::make( SIMDE_MM_MASK_INEXACT ), },

		{ "_MM_ROUND_MASK",					Result::make( 0x6000 ), },
		{ "_MM_ROUND_NEAREST",				Result::make( SIMDE_MM_ROUND_NEAREST ), },
		{ "_MM_ROUND_DOWN",					Result::make( SIMDE_MM_ROUND_DOWN ), },
		{ "_MM_ROUND_UP",					Result::make( SIMDE_MM_ROUND_UP ), },
		{ "_MM_ROUND_TOWARD_ZERO",			Result::make( SIMDE_MM_ROUND_TOWARD_ZERO ), },

		{ "_MM_FLUSH_ZERO_MASK",			Result::make( SIMDE_MM_FLUSH_ZERO_MASK ), },
		{ "_MM_FLUSH_ZERO_ON",				Result::make( SIMDE_MM_FLUSH_ZERO_ON ), },
		{ "_MM_FLUSH_ZERO_OFF",				Result::make( SIMDE_MM_FLUSH_ZERO_OFF ), },

		{ "_MM_K0_REG8",					Result::make( 0xff ), },
		{ "_MM_K0_REG16",					Result::make( 0xffff ), },
		{ "_MM_K0_REG32",					Result::make( 0xffffffff ), },
		{ "_MM_K0_REG64",					Result::make( 0xffffffffffffffff ), },

		{ "_MM_BROADCAST32_NONE",			Result::make( 0 ), },
		{ "_MM_BROADCAST_16X16",			Result::make( 0 ), },
		{ "_MM_BROADCAST_1X16",				Result::make( 1 ), },
		{ "_MM_BROADCAST_4X16",				Result::make( 2 ), },

		{ "_MM_BROADCAST64_NONE",			Result::make( 0 ), },
		{ "_MM_BROADCAST_8X8",				Result::make( 0 ), },
		{ "_MM_BROADCAST_1X8",				Result::make( 1 ), },
		{ "_MM_BROADCAST_4X8",				Result::make( 2 ), },

		{ "_MM_ROUND_MODE_NEAREST",			Result::make( 0 ), },
		{ "_MM_ROUND_MODE_DOWN",			Result::make( 1 ), },
		{ "_MM_ROUND_MODE_UP",				Result::make( 2 ), },
		{ "_MM_ROUND_MODE_TOWARD_ZERO",		Result::make( 3 ), },
		{ "_MM_ROUND_MODE_DEFAULT",			Result::make( 4 ), },
		{ "_MM_ROUND_MODE_NO_EXC",			Result::make( 8 ), },

		{ "_MM_EXPADJ_NONE",				Result::make( 0 ), },
		{ "_MM_EXPADJ_4",					Result::make( 1 ), },
		{ "_MM_EXPADJ_5",					Result::make( 2 ), },
		{ "_MM_EXPADJ_8",					Result::make( 3 ), },
		{ "_MM_EXPADJ_16",					Result::make( 4 ), },
		{ "_MM_EXPADJ_24",					Result::make( 5 ), },
		{ "_MM_EXPADJ_31",					Result::make( 6 ), },
		{ "_MM_EXPADJ_32",					Result::make( 7 ), },

		{ "_MM_SCALE_1",					Result::make( 1 ), },
		{ "_MM_SCALE_2",					Result::make( 2 ), },
		{ "_MM_SCALE_4",					Result::make( 4 ), },
		{ "_MM_SCALE_8",					Result::make( 8 ), },

		{ "_MM_FIXUP_NO_CHANGE",			Result::make( 0 ), },
		{ "_MM_FIXUP_NEG_INF",				Result::make( 1 ), },
		{ "_MM_FIXUP_NEG_ZERO",				Result::make( 2 ), },
		{ "_MM_FIXUP_POS_ZERO",				Result::make( 3 ), },
		{ "_MM_FIXUP_POS_INF",				Result::make( 4 ), },
		{ "_MM_FIXUP_NAN",					Result::make( 5 ), },
		{ "_MM_FIXUP_MAX_FLOAT",			Result::make( 6 ), },
		{ "_MM_FIXUP_MIN_FLOAT",			Result::make( 7 ), },

		{ "_MM_MANT_NORM_1_2",				Result::make( 0 ), },
		{ "_MM_MANT_NORM_p5_2",				Result::make( 1 ), },
		{ "_MM_MANT_NORM_p5_1",				Result::make( 2 ), },
		{ "_MM_MANT_NORM_p75_1p5",			Result::make( 3 ), },

		{ "_MM_MANT_SIGN_src",				Result::make( 0 ), },
		{ "_MM_MANT_SIGN_zero",				Result::make( 1 ), },
		{ "_MM_MANT_SIGN_nan",				Result::make( 2 ), },

		{ "_MM_CMPINT_EQ",					Result::make( SIMDE_MM_CMPINT_EQ ), },
		{ "_MM_CMPINT_LT",					Result::make( SIMDE_MM_CMPINT_LT ), },
		{ "_MM_CMPINT_LE",					Result::make( SIMDE_MM_CMPINT_LE ), },
		{ "_MM_CMPINT_UNUSED",				Result::make( SIMDE_MM_CMPINT_FALSE ), },
		{ "_MM_CMPINT_NE",					Result::make( SIMDE_MM_CMPINT_NE ), },
		{ "_MM_CMPINT_NLT",					Result::make( SIMDE_MM_CMPINT_NLT ), },
		{ "_MM_CMPINT_GE",					Result::make( SIMDE_MM_CMPINT_NLT ), },
		{ "_MM_CMPINT_NLE",					Result::make( SIMDE_MM_CMPINT_NLE ), },
		{ "_MM_CMPINT_GT",					Result::make( SIMDE_MM_CMPINT_NLE ), },

		{ "_MM_PERM_AAAA",					Result::make( 0x00 ), },
		{ "_MM_PERM_AAAB",					Result::make( 0x01 ), },
		{ "_MM_PERM_AAAC",					Result::make( 0x02 ), },
		{ "_MM_PERM_AAAD",					Result::make( 0x03 ), },
		{ "_MM_PERM_AABA",					Result::make( 0x04 ), },
		{ "_MM_PERM_AABB",					Result::make( 0x05 ), },
		{ "_MM_PERM_AABC",					Result::make( 0x06 ), },
		{ "_MM_PERM_AABD",					Result::make( 0x07 ), },
		{ "_MM_PERM_AACA",					Result::make( 0x08 ), },
		{ "_MM_PERM_AACB",					Result::make( 0x09 ), },
		{ "_MM_PERM_AACC",					Result::make( 0x0A ), },
		{ "_MM_PERM_AACD",					Result::make( 0x0B ), },
		{ "_MM_PERM_AADA",					Result::make( 0x0C ), },
		{ "_MM_PERM_AADB",					Result::make( 0x0D ), },
		{ "_MM_PERM_AADC",					Result::make( 0x0E ), },
		{ "_MM_PERM_AADD",					Result::make( 0x0F ), },
		{ "_MM_PERM_ABAA",					Result::make( 0x10 ), },
		{ "_MM_PERM_ABAB",					Result::make( 0x11 ), },
		{ "_MM_PERM_ABAC",					Result::make( 0x12 ), },
		{ "_MM_PERM_ABAD",					Result::make( 0x13 ), },
		{ "_MM_PERM_ABBA",					Result::make( 0x14 ), },
		{ "_MM_PERM_ABBB",					Result::make( 0x15 ), },
		{ "_MM_PERM_ABBC",					Result::make( 0x16 ), },
		{ "_MM_PERM_ABBD",					Result::make( 0x17 ), },
		{ "_MM_PERM_ABCA",					Result::make( 0x18 ), },
		{ "_MM_PERM_ABCB",					Result::make( 0x19 ), },
		{ "_MM_PERM_ABCC",					Result::make( 0x1A ), },
		{ "_MM_PERM_ABCD",					Result::make( 0x1B ), },
		{ "_MM_PERM_ABDA",					Result::make( 0x1C ), },
		{ "_MM_PERM_ABDB",					Result::make( 0x1D ), },
		{ "_MM_PERM_ABDC",					Result::make( 0x1E ), },
		{ "_MM_PERM_ABDD",					Result::make( 0x1F ), },
		{ "_MM_PERM_ACAA",					Result::make( 0x20 ), },
		{ "_MM_PERM_ACAB",					Result::make( 0x21 ), },
		{ "_MM_PERM_ACAC",					Result::make( 0x22 ), },
		{ "_MM_PERM_ACAD",					Result::make( 0x23 ), },
		{ "_MM_PERM_ACBA",					Result::make( 0x24 ), },
		{ "_MM_PERM_ACBB",					Result::make( 0x25 ), },
		{ "_MM_PERM_ACBC",					Result::make( 0x26 ), },
		{ "_MM_PERM_ACBD",					Result::make( 0x27 ), },
		{ "_MM_PERM_ACCA",					Result::make( 0x28 ), },
		{ "_MM_PERM_ACCB",					Result::make( 0x29 ), },
		{ "_MM_PERM_ACCC",					Result::make( 0x2A ), },
		{ "_MM_PERM_ACCD",					Result::make( 0x2B ), },
		{ "_MM_PERM_ACDA",					Result::make( 0x2C ), },
		{ "_MM_PERM_ACDB",					Result::make( 0x2D ), },
		{ "_MM_PERM_ACDC",					Result::make( 0x2E ), },
		{ "_MM_PERM_ACDD",					Result::make( 0x2F ), },
		{ "_MM_PERM_ADAA",					Result::make( 0x30 ), },
		{ "_MM_PERM_ADAB",					Result::make( 0x31 ), },
		{ "_MM_PERM_ADAC",					Result::make( 0x32 ), },
		{ "_MM_PERM_ADAD",					Result::make( 0x33 ), },
		{ "_MM_PERM_ADBA",					Result::make( 0x34 ), },
		{ "_MM_PERM_ADBB",					Result::make( 0x35 ), },
		{ "_MM_PERM_ADBC",					Result::make( 0x36 ), },
		{ "_MM_PERM_ADBD",					Result::make( 0x37 ), },
		{ "_MM_PERM_ADCA",					Result::make( 0x38 ), },
		{ "_MM_PERM_ADCB",					Result::make( 0x39 ), },
		{ "_MM_PERM_ADCC",					Result::make( 0x3A ), },
		{ "_MM_PERM_ADCD",					Result::make( 0x3B ), },
		{ "_MM_PERM_ADDA",					Result::make( 0x3C ), },
		{ "_MM_PERM_ADDB",					Result::make( 0x3D ), },
		{ "_MM_PERM_ADDC",					Result::make( 0x3E ), },
		{ "_MM_PERM_ADDD",					Result::make( 0x3F ), },
		{ "_MM_PERM_BAAA",					Result::make( 0x40 ), },
		{ "_MM_PERM_BAAB",					Result::make( 0x41 ), },
		{ "_MM_PERM_BAAC",					Result::make( 0x42 ), },
		{ "_MM_PERM_BAAD",					Result::make( 0x43 ), },
		{ "_MM_PERM_BABA",					Result::make( 0x44 ), },
		{ "_MM_PERM_BABB",					Result::make( 0x45 ), },
		{ "_MM_PERM_BABC",					Result::make( 0x46 ), },
		{ "_MM_PERM_BABD",					Result::make( 0x47 ), },
		{ "_MM_PERM_BACA",					Result::make( 0x48 ), },
		{ "_MM_PERM_BACB",					Result::make( 0x49 ), },
		{ "_MM_PERM_BACC",					Result::make( 0x4A ), },
		{ "_MM_PERM_BACD",					Result::make( 0x4B ), },
		{ "_MM_PERM_BADA",					Result::make( 0x4C ), },
		{ "_MM_PERM_BADB",					Result::make( 0x4D ), },
		{ "_MM_PERM_BADC",					Result::make( 0x4E ), },
		{ "_MM_PERM_BADD",					Result::make( 0x4F ), },
		{ "_MM_PERM_BBAA",					Result::make( 0x50 ), },
		{ "_MM_PERM_BBAB",					Result::make( 0x51 ), },
		{ "_MM_PERM_BBAC",					Result::make( 0x52 ), },
		{ "_MM_PERM_BBAD",					Result::make( 0x53 ), },
		{ "_MM_PERM_BBBA",					Result::make( 0x54 ), },
		{ "_MM_PERM_BBBB",					Result::make( 0x55 ), },
		{ "_MM_PERM_BBBC",					Result::make( 0x56 ), },
		{ "_MM_PERM_BBBD",					Result::make( 0x57 ), },
		{ "_MM_PERM_BBCA",					Result::make( 0x58 ), },
		{ "_MM_PERM_BBCB",					Result::make( 0x59 ), },
		{ "_MM_PERM_BBCC",					Result::make( 0x5A ), },
		{ "_MM_PERM_BBCD",					Result::make( 0x5B ), },
		{ "_MM_PERM_BBDA",					Result::make( 0x5C ), },
		{ "_MM_PERM_BBDB",					Result::make( 0x5D ), },
		{ "_MM_PERM_BBDC",					Result::make( 0x5E ), },
		{ "_MM_PERM_BBDD",					Result::make( 0x5F ), },
		{ "_MM_PERM_BCAA",					Result::make( 0x60 ), },
		{ "_MM_PERM_BCAB",					Result::make( 0x61 ), },
		{ "_MM_PERM_BCAC",					Result::make( 0x62 ), },
		{ "_MM_PERM_BCAD",					Result::make( 0x63 ), },
		{ "_MM_PERM_BCBA",					Result::make( 0x64 ), },
		{ "_MM_PERM_BCBB",					Result::make( 0x65 ), },
		{ "_MM_PERM_BCBC",					Result::make( 0x66 ), },
		{ "_MM_PERM_BCBD",					Result::make( 0x67 ), },
		{ "_MM_PERM_BCCA",					Result::make( 0x68 ), },
		{ "_MM_PERM_BCCB",					Result::make( 0x69 ), },
		{ "_MM_PERM_BCCC",					Result::make( 0x6A ), },
		{ "_MM_PERM_BCCD",					Result::make( 0x6B ), },
		{ "_MM_PERM_BCDA",					Result::make( 0x6C ), },
		{ "_MM_PERM_BCDB",					Result::make( 0x6D ), },
		{ "_MM_PERM_BCDC",					Result::make( 0x6E ), },
		{ "_MM_PERM_BCDD",					Result::make( 0x6F ), },
		{ "_MM_PERM_BDAA",					Result::make( 0x70 ), },
		{ "_MM_PERM_BDAB",					Result::make( 0x71 ), },
		{ "_MM_PERM_BDAC",					Result::make( 0x72 ), },
		{ "_MM_PERM_BDAD",					Result::make( 0x73 ), },
		{ "_MM_PERM_BDBA",					Result::make( 0x74 ), },
		{ "_MM_PERM_BDBB",					Result::make( 0x75 ), },
		{ "_MM_PERM_BDBC",					Result::make( 0x76 ), },
		{ "_MM_PERM_BDBD",					Result::make( 0x77 ), },
		{ "_MM_PERM_BDCA",					Result::make( 0x78 ), },
		{ "_MM_PERM_BDCB",					Result::make( 0x79 ), },
		{ "_MM_PERM_BDCC",					Result::make( 0x7A ), },
		{ "_MM_PERM_BDCD",					Result::make( 0x7B ), },
		{ "_MM_PERM_BDDA",					Result::make( 0x7C ), },
		{ "_MM_PERM_BDDB",					Result::make( 0x7D ), },
		{ "_MM_PERM_BDDC",					Result::make( 0x7E ), },
		{ "_MM_PERM_BDDD",					Result::make( 0x7F ), },
		{ "_MM_PERM_CAAA",					Result::make( 0x80 ), },
		{ "_MM_PERM_CAAB",					Result::make( 0x81 ), },
		{ "_MM_PERM_CAAC",					Result::make( 0x82 ), },
		{ "_MM_PERM_CAAD",					Result::make( 0x83 ), },
		{ "_MM_PERM_CABA",					Result::make( 0x84 ), },
		{ "_MM_PERM_CABB",					Result::make( 0x85 ), },
		{ "_MM_PERM_CABC",					Result::make( 0x86 ), },
		{ "_MM_PERM_CABD",					Result::make( 0x87 ), },
		{ "_MM_PERM_CACA",					Result::make( 0x88 ), },
		{ "_MM_PERM_CACB",					Result::make( 0x89 ), },
		{ "_MM_PERM_CACC",					Result::make( 0x8A ), },
		{ "_MM_PERM_CACD",					Result::make( 0x8B ), },
		{ "_MM_PERM_CADA",					Result::make( 0x8C ), },
		{ "_MM_PERM_CADB",					Result::make( 0x8D ), },
		{ "_MM_PERM_CADC",					Result::make( 0x8E ), },
		{ "_MM_PERM_CADD",					Result::make( 0x8F ), },
		{ "_MM_PERM_CBAA",					Result::make( 0x90 ), },
		{ "_MM_PERM_CBAB",					Result::make( 0x91 ), },
		{ "_MM_PERM_CBAC",					Result::make( 0x92 ), },
		{ "_MM_PERM_CBAD",					Result::make( 0x93 ), },
		{ "_MM_PERM_CBBA",					Result::make( 0x94 ), },
		{ "_MM_PERM_CBBB",					Result::make( 0x95 ), },
		{ "_MM_PERM_CBBC",					Result::make( 0x96 ), },
		{ "_MM_PERM_CBBD",					Result::make( 0x97 ), },
		{ "_MM_PERM_CBCA",					Result::make( 0x98 ), },
		{ "_MM_PERM_CBCB",					Result::make( 0x99 ), },
		{ "_MM_PERM_CBCC",					Result::make( 0x9A ), },
		{ "_MM_PERM_CBCD",					Result::make( 0x9B ), },
		{ "_MM_PERM_CBDA",					Result::make( 0x9C ), },
		{ "_MM_PERM_CBDB",					Result::make( 0x9D ), },
		{ "_MM_PERM_CBDC",					Result::make( 0x9E ), },
		{ "_MM_PERM_CBDD",					Result::make( 0x9F ), },
		{ "_MM_PERM_CCAA",					Result::make( 0xA0 ), },
		{ "_MM_PERM_CCAB",					Result::make( 0xA1 ), },
		{ "_MM_PERM_CCAC",					Result::make( 0xA2 ), },
		{ "_MM_PERM_CCAD",					Result::make( 0xA3 ), },
		{ "_MM_PERM_CCBA",					Result::make( 0xA4 ), },
		{ "_MM_PERM_CCBB",					Result::make( 0xA5 ), },
		{ "_MM_PERM_CCBC",					Result::make( 0xA6 ), },
		{ "_MM_PERM_CCBD",					Result::make( 0xA7 ), },
		{ "_MM_PERM_CCCA",					Result::make( 0xA8 ), },
		{ "_MM_PERM_CCCB",					Result::make( 0xA9 ), },
		{ "_MM_PERM_CCCC",					Result::make( 0xAA ), },
		{ "_MM_PERM_CCCD",					Result::make( 0xAB ), },
		{ "_MM_PERM_CCDA",					Result::make( 0xAC ), },
		{ "_MM_PERM_CCDB",					Result::make( 0xAD ), },
		{ "_MM_PERM_CCDC",					Result::make( 0xAE ), },
		{ "_MM_PERM_CCDD",					Result::make( 0xAF ), },
		{ "_MM_PERM_CDAA",					Result::make( 0xB0 ), },
		{ "_MM_PERM_CDAB",					Result::make( 0xB1 ), },
		{ "_MM_PERM_CDAC",					Result::make( 0xB2 ), },
		{ "_MM_PERM_CDAD",					Result::make( 0xB3 ), },
		{ "_MM_PERM_CDBA",					Result::make( 0xB4 ), },
		{ "_MM_PERM_CDBB",					Result::make( 0xB5 ), },
		{ "_MM_PERM_CDBC",					Result::make( 0xB6 ), },
		{ "_MM_PERM_CDBD",					Result::make( 0xB7 ), },
		{ "_MM_PERM_CDCA",					Result::make( 0xB8 ), },
		{ "_MM_PERM_CDCB",					Result::make( 0xB9 ), },
		{ "_MM_PERM_CDCC",					Result::make( 0xBA ), },
		{ "_MM_PERM_CDCD",					Result::make( 0xBB ), },
		{ "_MM_PERM_CDDA",					Result::make( 0xBC ), },
		{ "_MM_PERM_CDDB",					Result::make( 0xBD ), },
		{ "_MM_PERM_CDDC",					Result::make( 0xBE ), },
		{ "_MM_PERM_CDDD",					Result::make( 0xBF ), },
		{ "_MM_PERM_DAAA",					Result::make( 0xC0 ), },
		{ "_MM_PERM_DAAB",					Result::make( 0xC1 ), },
		{ "_MM_PERM_DAAC",					Result::make( 0xC2 ), },
		{ "_MM_PERM_DAAD",					Result::make( 0xC3 ), },
		{ "_MM_PERM_DABA",					Result::make( 0xC4 ), },
		{ "_MM_PERM_DABB",					Result::make( 0xC5 ), },
		{ "_MM_PERM_DABC",					Result::make( 0xC6 ), },
		{ "_MM_PERM_DABD",					Result::make( 0xC7 ), },
		{ "_MM_PERM_DACA",					Result::make( 0xC8 ), },
		{ "_MM_PERM_DACB",					Result::make( 0xC9 ), },
		{ "_MM_PERM_DACC",					Result::make( 0xCA ), },
		{ "_MM_PERM_DACD",					Result::make( 0xCB ), },
		{ "_MM_PERM_DADA",					Result::make( 0xCC ), },
		{ "_MM_PERM_DADB",					Result::make( 0xCD ), },
		{ "_MM_PERM_DADC",					Result::make( 0xCE ), },
		{ "_MM_PERM_DADD",					Result::make( 0xCF ), },
		{ "_MM_PERM_DBAA",					Result::make( 0xD0 ), },
		{ "_MM_PERM_DBAB",					Result::make( 0xD1 ), },
		{ "_MM_PERM_DBAC",					Result::make( 0xD2 ), },
		{ "_MM_PERM_DBAD",					Result::make( 0xD3 ), },
		{ "_MM_PERM_DBBA",					Result::make( 0xD4 ), },
		{ "_MM_PERM_DBBB",					Result::make( 0xD5 ), },
		{ "_MM_PERM_DBBC",					Result::make( 0xD6 ), },
		{ "_MM_PERM_DBBD",					Result::make( 0xD7 ), },
		{ "_MM_PERM_DBCA",					Result::make( 0xD8 ), },
		{ "_MM_PERM_DBCB",					Result::make( 0xD9 ), },
		{ "_MM_PERM_DBCC",					Result::make( 0xDA ), },
		{ "_MM_PERM_DBCD",					Result::make( 0xDB ), },
		{ "_MM_PERM_DBDA",					Result::make( 0xDC ), },
		{ "_MM_PERM_DBDB",					Result::make( 0xDD ), },
		{ "_MM_PERM_DBDC",					Result::make( 0xDE ), },
		{ "_MM_PERM_DBDD",					Result::make( 0xDF ), },
		{ "_MM_PERM_DCAA",					Result::make( 0xE0 ), },
		{ "_MM_PERM_DCAB",					Result::make( 0xE1 ), },
		{ "_MM_PERM_DCAC",					Result::make( 0xE2 ), },
		{ "_MM_PERM_DCAD",					Result::make( 0xE3 ), },
		{ "_MM_PERM_DCBA",					Result::make( 0xE4 ), },
		{ "_MM_PERM_DCBB",					Result::make( 0xE5 ), },
		{ "_MM_PERM_DCBC",					Result::make( 0xE6 ), },
		{ "_MM_PERM_DCBD",					Result::make( 0xE7 ), },
		{ "_MM_PERM_DCCA",					Result::make( 0xE8 ), },
		{ "_MM_PERM_DCCB",					Result::make( 0xE9 ), },
		{ "_MM_PERM_DCCC",					Result::make( 0xEA ), },
		{ "_MM_PERM_DCCD",					Result::make( 0xEB ), },
		{ "_MM_PERM_DCDA",					Result::make( 0xEC ), },
		{ "_MM_PERM_DCDB",					Result::make( 0xED ), },
		{ "_MM_PERM_DCDC",					Result::make( 0xEE ), },
		{ "_MM_PERM_DCDD",					Result::make( 0xEF ), },
		{ "_MM_PERM_DDAA",					Result::make( 0xF0 ), },
		{ "_MM_PERM_DDAB",					Result::make( 0xF1 ), },
		{ "_MM_PERM_DDAC",					Result::make( 0xF2 ), },
		{ "_MM_PERM_DDAD",					Result::make( 0xF3 ), },
		{ "_MM_PERM_DDBA",					Result::make( 0xF4 ), },
		{ "_MM_PERM_DDBB",					Result::make( 0xF5 ), },
		{ "_MM_PERM_DDBC",					Result::make( 0xF6 ), },
		{ "_MM_PERM_DDBD",					Result::make( 0xF7 ), },
		{ "_MM_PERM_DDCA",					Result::make( 0xF8 ), },
		{ "_MM_PERM_DDCB",					Result::make( 0xF9 ), },
		{ "_MM_PERM_DDCC",					Result::make( 0xFA ), },
		{ "_MM_PERM_DDCD",					Result::make( 0xFB ), },
		{ "_MM_PERM_DDDA",					Result::make( 0xFC ), },
		{ "_MM_PERM_DDDB",					Result::make( 0xFD ), },
		{ "_MM_PERM_DDDC",					Result::make( 0xFE ), },
		{ "_MM_PERM_DDDD",					Result::make( 0xFF ), },

		{ "_MM_FROUND_TO_NEAREST_INT",		Result::make( SIMDE_MM_FROUND_TO_NEAREST_INT ), },
		{ "_MM_FROUND_TO_NEG_INF",			Result::make( SIMDE_MM_FROUND_TO_NEG_INF ), },
		{ "_MM_FROUND_TO_POS_INF",			Result::make( SIMDE_MM_FROUND_TO_POS_INF ), },
		{ "_MM_FROUND_TO_ZERO",				Result::make( SIMDE_MM_FROUND_TO_ZERO ), },
		{ "_MM_FROUND_CUR_DIRECTION",		Result::make( SIMDE_MM_FROUND_CUR_DIRECTION ), },

		{ "_MM_FROUND_RAISE_EXC",			Result::make( SIMDE_MM_FROUND_RAISE_EXC ), },
		{ "_MM_FROUND_NO_EXC",				Result::make( SIMDE_MM_FROUND_NO_EXC ), },

		{ "_MM_FROUND_NINT",				Result::make( SIMDE_MM_FROUND_NINT ), },
		{ "_MM_FROUND_FLOOR",				Result::make( SIMDE_MM_FROUND_FLOOR ), },
		{ "_MM_FROUND_CEIL",				Result::make( SIMDE_MM_FROUND_CEIL ), },
		{ "_MM_FROUND_TRUNC",				Result::make( SIMDE_MM_FROUND_TRUNC ), },
		{ "_MM_FROUND_RINT",				Result::make( SIMDE_MM_FROUND_RINT ), },
		{ "_MM_FROUND_NEARBYINT",			Result::make( SIMDE_MM_FROUND_NEARBYINT ), },
		
		{ "_SIDD_UBYTE_OPS",				Result::make( SIMDE_SIDD_UBYTE_OPS ), },
		{ "_SIDD_UWORD_OPS",				Result::make( SIMDE_SIDD_UWORD_OPS ), },
		{ "_SIDD_SBYTE_OPS",				Result::make( SIMDE_SIDD_SBYTE_OPS ), },
		{ "_SIDD_SWORD_OPS",				Result::make( SIMDE_SIDD_SWORD_OPS ), },
		
		{ "_SIDD_CMP_EQUAL_ANY",			Result::make( SIMDE_SIDD_CMP_EQUAL_ANY ), },
		{ "_SIDD_CMP_RANGES",				Result::make( SIMDE_SIDD_CMP_RANGES ), },
		{ "_SIDD_CMP_EQUAL_EACH",			Result::make( SIMDE_SIDD_CMP_EQUAL_EACH ), },
		{ "_SIDD_CMP_EQUAL_ORDERED",		Result::make( SIMDE_SIDD_CMP_EQUAL_ORDERED ), },
		
		{ "_SIDD_POSITIVE_POLARITY",		Result::make( SIMDE_SIDD_POSITIVE_POLARITY ), },
		{ "_SIDD_NEGATIVE_POLARITY",		Result::make( SIMDE_SIDD_NEGATIVE_POLARITY ), },
		{ "_SIDD_MASKED_POSITIVE_POLARITY",	Result::make( SIMDE_SIDD_MASKED_POSITIVE_POLARITY ), },
		{ "_SIDD_MASKED_NEGATIVE_POLARITY",	Result::make( SIMDE_SIDD_MASKED_NEGATIVE_POLARITY ), },
		
		{ "_SIDD_LEAST_SIGNIFICANT",		Result::make( SIMDE_SIDD_LEAST_SIGNIFICANT ), },
		{ "_SIDD_MOST_SIGNIFICANT",			Result::make( SIMDE_SIDD_MOST_SIGNIFICANT ), },
		
		{ "_SIDD_BIT_MASK",					Result::make( SIMDE_SIDD_BIT_MASK ), },
		{ "_SIDD_UNIT_MASK",				Result::make( SIMDE_SIDD_UNIT_MASK ), },
		
		{ "_MM_DENORMALS_ZERO_MASK",		Result::make( 0x0040 ), },
		{ "_MM_DENORMALS_ZERO_ON",			Result::make( 0x0040 ), },
		{ "_MM_DENORMALS_ZERO_OFF",			Result::make( 0x0000 ), },
	};

	/** The static list of built-in functions. */
	const FunctionDef ExecutionContext::builtInFunctions[] = {
		// == Pow
		{ "pow", StringId::Desc_Pow, { { DataType::Double, "x", StringId::Desc_MathParam_PowX }, { DataType::Double, "y", StringId::VE_STR_POW_PARAM_Y } }, IntrinsicBridges::powBridge, false },
		{ "powf", StringId::Desc_Pow, { { DataType::Float, "x", StringId::Desc_MathParam_PowX }, { DataType::Float, "y", StringId::VE_STR_POW_PARAM_Y } }, IntrinsicBridges::powfBridge, false },

		// == Trigonometry
		{ "sin", StringId::Desc_Sin, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::sinBridge, false, true },
		{ "sinf", StringId::Desc_Sin, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::sinfBridge, false, true },
		
		{ "cos", StringId::Desc_Cos, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::cosBridge, false, true },
		{ "cosf", StringId::Desc_Cos, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::cosfBridge, false, true },
		
		{ "tan", StringId::Desc_Tan, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::tanBridge, false, true },
		{ "tanf", StringId::Desc_Tan, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::tanfBridge, false, true },

		// == Inverse Trigonometry
		{ "asin", StringId::Desc_Asin, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::asinBridge, false, true },
		{ "asinf", StringId::Desc_Asin, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::asinfBridge, false, true },
		
		{ "acos", StringId::Desc_Acos, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::acosBridge, false, true },
		{ "acosf", StringId::Desc_Acos, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::acosfBridge, false, true },
		
		{ "atan", StringId::Desc_Atan, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::atanBridge, false, true },
		{ "atanf", StringId::Desc_Atan, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::atanfBridge, false, true },
		
		{ "atan2", StringId::Desc_Atan2, { { DataType::Double, "y", StringId::Desc_MathParam_Y }, { DataType::Double, "x", StringId::Desc_MathParam_X } }, IntrinsicBridges::atan2Bridge },
		{ "atan2f", StringId::Desc_Atan2, { { DataType::Float, "y", StringId::Desc_MathParam_Y }, { DataType::Float, "x", StringId::Desc_MathParam_X } }, IntrinsicBridges::atan2fBridge },

		// == Exponential & Logarithmic
		{ "exp", StringId::Desc_Exp, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::expBridge, false, true },
		{ "expf", StringId::Desc_Exp, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::expfBridge, false, true },
		
		{ "log", StringId::Desc_Log, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::logBridge, false, true },
		{ "logf", StringId::Desc_Log, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::logfBridge, false, true },
		
		{ "log10", StringId::Desc_Log10, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log10Bridge, false, true },
		{ "log10f", StringId::Desc_Log10, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log10fBridge, false, true },

		// == Roots
		{ "sqrt", StringId::Desc_Sqrt, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::sqrtBridge, false, true },
		{ "sqrtf", StringId::Desc_Sqrt, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::sqrtfBridge, false, true },
		
		{ "cbrt", StringId::Desc_Cbrt, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::cbrtBridge, false, true },
		{ "cbrtf", StringId::Desc_Cbrt, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::cbrtfBridge, false, true },

		// == Rounding & Absolute Value
		{ "ceil", StringId::Desc_Ceil, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::ceilBridge, false, true },
		{ "ceilf", StringId::Desc_Ceil, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::ceilfBridge, false, true },
		
		{ "floor", StringId::Desc_Floor, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::floorBridge, false, true },
		{ "floorf", StringId::Desc_Floor, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::floorfBridge, false, true },
		
		{ "abs", StringId::Desc_Abs, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::absBridge, false, true },
		{ "fabs", StringId::Desc_Abs, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::fabsBridge, false, true },
		{ "fabsf", StringId::Desc_Abs, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::fabsfBridge, false, true },

		// == Hyperbolics
		{ "cosh", StringId::Desc_CosH, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::coshBridge, false, true },
		{ "coshf", StringId::Desc_CosH, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::coshfBridge, false, true },
		{ "sinh", StringId::Desc_SinH, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::sinhBridge, false, true },
		{ "sinhf", StringId::Desc_SinH, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::sinhfBridge, false, true },
		{ "tanh", StringId::Desc_TanH, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::tanhBridge, false, true },
		{ "tanhf", StringId::Desc_TanH, { { DataType::Float, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::tanhfBridge, false, true },
		{ "acosh", StringId::Desc_AcosH, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::acoshBridge, false, true },
		{ "acoshf", StringId::Desc_AcosH, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::acoshfBridge, false, true },
		{ "asinh", StringId::Desc_AsinH, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::asinhBridge, false, true },
		{ "asinhf", StringId::Desc_AsinH, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::asinhfBridge, false, true },
		{ "atanh", StringId::Desc_AtanH, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::atanhBridge, false, true },
		{ "atanhf", StringId::Desc_AtanH, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::atanhfBridge, false, true },

		// == Extended Exponents & Logs
		{ "log2", StringId::Desc_Log2, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log2Bridge, false, true },
		{ "log2f", StringId::Desc_Log2, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log2fBridge, false, true },
		{ "exp2", StringId::Desc_Exp2, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::exp2Bridge, false, true },
		{ "exp2f", StringId::Desc_Exp2, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::exp2fBridge, false, true },
		{ "expm1", StringId::Desc_ExpM1, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::expm1Bridge, false, true },
		{ "expm1f", StringId::Desc_ExpM1, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::expm1fBridge, false, true },
		{ "ilogb", StringId::Desc_Log, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::ilogbBridge, false, true },
		{ "ilogbf", StringId::Desc_Log, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::ilogbfBridge, false, true },
		{ "log1p", StringId::Desc_Log, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log1pBridge, false, true },
		{ "log1pf", StringId::Desc_Log, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::log1pfBridge, false, true },
		{ "logb", StringId::Desc_Log, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::logbBridge, false, true },
		{ "logbf", StringId::Desc_Log, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::logbfBridge, false, true },

		// == Misc Math
		{ "hypot", StringId::Desc_Hypot, { { DataType::Double, "x", StringId::Desc_MathParam_X }, { DataType::Double, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::hypotBridge },
		{ "hypotf", StringId::Desc_Hypot, { { DataType::Float, "x", StringId::Desc_MathParam_X }, { DataType::Float, "y", StringId::Desc_MathParam_Y } }, IntrinsicBridges::hypotfBridge },
		{ "tgamma", StringId::Desc_TGamma, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::tgammaBridge, false, true },
		{ "tgammaf", StringId::Desc_TGamma, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::tgammafBridge, false, true },
		{ "lgamma", StringId::Desc_LGamma, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::lgammaBridge, false, true },
		{ "lgammaf", StringId::Desc_LGamma, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::lgammafBridge, false, true },
		{ "trunc", StringId::Desc_Trunc, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::truncBridge, false, true },
		{ "truncf", StringId::Desc_Trunc, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::truncfBridge, false, true },
		{ "round", StringId::Desc_Round, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::roundBridge, false, true },
		{ "roundf", StringId::Desc_Round, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::roundfBridge, false, true },
		{ "nearbyint", StringId::Desc_NearbyInt, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::nearbyintBridge, false, true },
		{ "nearbyintf", StringId::Desc_NearbyInt, { { DataType::Float, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::nearbyintfBridge, false, true },

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
		{ "isnan", StringId::Desc_IsNan, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::isnanBridge, false, true },
		{ "isinf", StringId::Desc_IsInf, { { DataType::Double, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::isinfBridge, false, true },

		// == Custom Helpers
		{ "rand", StringId::Desc_Rand, { }, IntrinsicBridges::randBridge },
		{ "deg", StringId::Desc_Deg, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::degBridge, false, true },
		{ "rad", StringId::Desc_Rad, { { DataType::Double, "x", StringId::Desc_MathParam_Angle } }, IntrinsicBridges::radBridge, false, true },

		// == Bit Manipulation (<bit>)
		{ "byteswap16", StringId::Desc_ByteSwap16, { { DataType::UInt16, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::byteswap16Bridge, false, true },
		{ "byteswap32", StringId::Desc_ByteSwap32, { { DataType::UInt32, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::byteswap32Bridge, false, true },
		{ "byteswap64", StringId::Desc_ByteSwap, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::byteswap64Bridge, false, true },
		{ "byteswap", StringId::Desc_ByteSwap, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::byteswap64Bridge, false, true },
		{ "has_single_bit", StringId::Desc_HasSingleBit, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::has_single_bitBridge, false, true },
		{ "bit_ceil", StringId::Desc_BitCeil, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::bit_ceilBridge, false, true },
		{ "bit_floor", StringId::Desc_BitFloor, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::bit_floorBridge, false, true },
		{ "bit_width", StringId::Desc_BitWidth, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::bit_widthBridge, false, true },
		{ "rotl", StringId::Desc_RotL, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val }, { DataType::Int32, "s", StringId::Desc_BitParamS } }, IntrinsicBridges::rotlBridge },
		{ "rotr", StringId::Desc_RotR, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val }, { DataType::Int32, "s", StringId::Desc_BitParamS } }, IntrinsicBridges::rotrBridge },
		{ "countl_zero", StringId::Desc_CountLZero, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::countl_zeroBridge, false, true },
		{ "countl_one", StringId::Desc_CountLOne, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::countl_oneBridge, false, true },
		{ "countr_zero", StringId::Desc_CountRZero, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::countr_zeroBridge, false, true },
		{ "countr_one", StringId::Desc_CountROne, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::countr_oneBridge, false, true },
		{ "popcount", StringId::Desc_PopCount, { { DataType::UInt64, "x", StringId::Desc_MathParam_Val } }, IntrinsicBridges::popcountBridge, false, true },

		// == HTML
		{ "htmlCount", StringId::Desc_HtmlCount, {}, IntrinsicBridges::htmlCountBridge },
		{ "htmlName", StringId::Desc_HtmlName, { { DataType::Int64, "index", StringId::Desc_HtmlName_Index } }, IntrinsicBridges::htmlNameBridge, false, true },
		{ "htmlChar", StringId::Desc_HtmlChar, { { DataType::Int64, "indexOrName", StringId::Desc_HtmlChar_Arg } }, IntrinsicBridges::htmlCharBridge, false, true },

		// == Strings
		{ "capitalize", StringId::Desc_String_Capitalize, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::capitalizeBridge, false, true },
		{ "casefold", StringId::Desc_String_Casefold, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::casefoldBridge, false, true },
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
		{ "isalnum", StringId::Desc_String_IsAlnum, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isAlnumBridge, false, true },
		{ "isalpha", StringId::Desc_String_IsAlpha, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isAlphaBridge, false, true },
		{ "isascii", StringId::Desc_String_IsAscii, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isAsciiBridge, false, true },
		{ "isdecimal", StringId::Desc_String_IsDecimal, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isDecimalBridge, false, true },
		{ "isdigit", StringId::Desc_String_IsDigit, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isDigitBridge, false, true },
		{ "isidentifier", StringId::Desc_String_IsIdentifier, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::isIdentifierBridge, false, true },
		{ "isnumeric", StringId::Desc_String_IsNumeric, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isNumericBridge, false, true },
		{ "isprintable", StringId::Desc_String_IsPrintable, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isPrintableBridge, false, true },
		{ "isspace", StringId::Desc_String_IsSpace, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isSpaceBridge, false, true },
		{ "istitle", StringId::Desc_String_IsTitle, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::isTitleBridge, false, true },
		{ "isupper", StringId::Desc_String_IsUpper, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::isUpperBridge, false, true },
		{ "join", StringId::Desc_String_Join, { { DataType::String, "separator", StringId::Desc_Param_Separator }, { DataType::Any, "iterable", StringId::Desc_Param_Iterable } }, IntrinsicBridges::joinBridge },
		{ "ljust", StringId::Desc_String_LJust, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width } }, IntrinsicBridges::ljustBridge },
		{ "ljust", StringId::Desc_String_LJust, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width }, { DataType::Any, "fillchar", StringId::String_Param_Fillchar } }, IntrinsicBridges::ljustBridge },
		{ "lower", StringId::Desc_String_Lower, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::lowerBridge, false, true },
		{ "lstrip", StringId::Desc_String_LStrip, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::lstripBridge, false, true },
		{ "lstrip", StringId::Desc_String_LStrip, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "chars", StringId::String_Param_Chars } }, IntrinsicBridges::lstripBridge },
		{ "partition", StringId::Desc_String_Partition, { { DataType::String, "separator", StringId::Desc_Param_Separator } }, IntrinsicBridges::partitionBridge },
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
		{ "rpartition", StringId::Desc_String_RPartition, { { DataType::String, "separator", StringId::Desc_Param_Separator } }, IntrinsicBridges::rpartitionBridge },
		{ "rstrip", StringId::Desc_String_RStrip, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::rstripBridge, false, true },
		{ "rstrip", StringId::Desc_String_RStrip, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "chars", StringId::String_Param_Chars } }, IntrinsicBridges::rstripBridge },
		{ "split", StringId::Desc_String_Split, { { DataType::String, "separator", StringId::Desc_Param_Separator } }, IntrinsicBridges::splitBridge },
		{ "split", StringId::Desc_String_Split, { { DataType::String, "separator", StringId::Desc_Param_Separator }, { DataType::Int64, "maxsplit", StringId::Desc_Param_MaxSplit } }, IntrinsicBridges::splitBridge },
		{ "splitlines", StringId::Desc_String_SplitLines, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::splitlinesBridge },
		{ "splitlines", StringId::Desc_String_SplitLines, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Any, "keepends", StringId::Desc_Param_KeepEnds } }, IntrinsicBridges::splitlinesBridge },
		{ "startswith", StringId::Desc_String_StartsWith, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "prefix", StringId::String_Param_Prefix } }, IntrinsicBridges::startsWithBridge },
		{ "startswith", StringId::Desc_String_StartsWith, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "prefix", StringId::String_Param_Prefix }, { DataType::Integer, "start", StringId::String_Param_Start } }, IntrinsicBridges::startsWithBridge },
		{ "startswith", StringId::Desc_String_StartsWith, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "prefix", StringId::String_Param_Prefix }, { DataType::Integer, "start", StringId::String_Param_Start }, { DataType::Integer, "end", StringId::String_Param_End } }, IntrinsicBridges::startsWithBridge },
		{ "strip", StringId::Desc_String_Strip, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::stripBridge, false, true },
		{ "strip", StringId::Desc_String_Strip, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::String, "chars", StringId::String_Param_Chars } }, IntrinsicBridges::stripBridge },
		{ "swapcase", StringId::Desc_String_SwapCase, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::swapcaseBridge, false, true },
		{ "title", StringId::Desc_String_Title, { { DataType::String, "str", StringId::String_Param_Target } }, IntrinsicBridges::titleBridge, false, true },
		{ "upper", StringId::Desc_String_Upper, { { DataType::Any, "str", StringId::String_Param_Target } }, IntrinsicBridges::upperBridge, false, true },
		{ "zfill", StringId::Desc_String_ZFill, { { DataType::String, "str", StringId::String_Param_Target }, { DataType::Int64, "width", StringId::String_Param_Width } }, IntrinsicBridges::zfillBridge },

		// == Strings/Vectors
		{ "append", StringId::Desc_Intrinsic_Append, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject }, { DataType::Any, "val", StringId::Desc_Param_Item } }, IntrinsicBridges::appendBridge },
		{ "at", StringId::Desc_Object_At, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject }, { DataType::Integer, "index", StringId::String_Param_Index } }, IntrinsicBridges::atBridge },
		{ "clear", StringId::Desc_Intrinsic_Clear, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject } }, IntrinsicBridges::clearBridge },
		{ "copy", StringId::Desc_Intrinsic_Copy, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject } }, IntrinsicBridges::copyBridge },
		{ "len", StringId::Desc_Object_Len, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject } }, IntrinsicBridges::lengthBridge },
		{ "pop", StringId::Desc_Intrinsic_Pop, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject } }, IntrinsicBridges::popBridge },
		{ "pop", StringId::Desc_Intrinsic_Pop, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject }, { DataType::Int32, "index", StringId::Desc_Param_PopIndex } }, IntrinsicBridges::popBridge },
		{ "pop_back", StringId::Desc_Intrinsic_Pop, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject } }, IntrinsicBridges::popBridge },
		{ "push_back", StringId::Desc_Object_PushBack, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject }, { DataType::Any, "val", StringId::String_Param_Item } }, IntrinsicBridges::pushBackBridge },
		{ "remove", StringId::Desc_Intrinsic_Remove, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject }, { DataType::Any, "val", StringId::Desc_Param_RemoveValue } }, IntrinsicBridges::removeBridge },
		{ "reverse", StringId::Desc_Intrinsic_Reverse, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject } }, IntrinsicBridges::reverseBridge },
		{ "size", StringId::Desc_Object_Size, { { DataType::Any, "obj", StringId::Desc_Param_TargetObject } }, IntrinsicBridges::lengthBridge },

		// == Custom API.
		{ "min", StringId::Desc_Math_Min, { { DataType::Any, "x", StringId::Math_Param_X }, { DataType::Any, "y", StringId::Math_Param_Y } }, IntrinsicBridges::minBridge },
		{ "max", StringId::Desc_Math_Max, { { DataType::Any, "x", StringId::Math_Param_X }, { DataType::Any, "y", StringId::Math_Param_Y } }, IntrinsicBridges::maxBridge },
		{ "clamp", StringId::Desc_Math_Clamp, { { DataType::Any, "val", StringId::Math_Param_Val }, { DataType::Any, "minVal", StringId::Math_Param_Min }, { DataType::Any, "maxVal", StringId::Math_Param_Max } }, IntrinsicBridges::clampBridge },
		{ "frac", StringId::Desc_Math_Frac, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::fracBridge, false, true },
		{ "step", StringId::Desc_Math_Step, { { DataType::Double, "edge", StringId::Math_Param_Edge }, { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::stepBridge },
		{ "sinc", StringId::Desc_Math_Sinc, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sincBridge, false, true },
		{ "relativeEpsilon", StringId::Desc_Math_RelativeEpsilon, { { DataType::Double, "left", StringId::Math_Param_Left }, { DataType::Double, "right", StringId::Math_Param_Right }, { DataType::Double, "epsilon", StringId::Math_Param_Epsilon } }, IntrinsicBridges::relativeEpsilonBridge },
		{ "sinExact", StringId::Desc_Math_SinExact, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sinExactBridge, false, true },
		{ "cosExact", StringId::Desc_Math_CosExact, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::cosExactBridge, false, true },
		{ "lcm", StringId::Desc_Math_Lcm, { { DataType::Integer, "x", StringId::Math_Param_X }, { DataType::Integer, "y", StringId::Math_Param_Y } }, IntrinsicBridges::lcmBridge },
		//{ "lcmChecked", StringId::Desc_Math_LcmChecked, { { DataType::Integer, "x", StringId::Math_Param_X }, { DataType::Integer, "y", StringId::Math_Param_Y } }, IntrinsicBridges::lcmCheckedBridge },

		// == Gamma Functions.
		{ "linearToSRgb", StringId::Desc_Math_LinearToSRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSRgbBridge, false, true },
		{ "sRgbToLinear", StringId::Desc_Math_SRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sRgbToLinearBridge, false, true },
		{ "pow2_2ToLinear", StringId::Desc_Math_Pow2_2ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::pow2_2ToLinearBridge, false, true },
		{ "linearToPow2_2", StringId::Desc_Math_LinearToPow2_2, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToPow2_2Bridge, false, true },
		{ "smpte240MToLinear", StringId::Desc_Math_Smpte240MToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::smpte240MToLinearBridge, false, true },
		{ "linearToSmpte240M", StringId::Desc_Math_LinearToSmpte240M, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSmpte240MBridge, false, true },
		{ "sLog2ToLinear", StringId::Desc_Math_SLog2ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sLog2ToLinearBridge, false, true },
		{ "linearToSLog2", StringId::Desc_Math_LinearToSLog2, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSLog2Bridge, false, true },
		{ "canonLogToLinear", StringId::Desc_Math_CanonLogToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::canonLogToLinearBridge, false, true },
		{ "linearToCanonLog", StringId::Desc_Math_LinearToCanonLog, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToCanonLogBridge, false, true },
		{ "viperToLinear", StringId::Desc_Math_ViperToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::viperToLinearBridge, false, true },
		{ "linearToViper", StringId::Desc_Math_LinearToViper, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToViperBridge, false, true },
		{ "acesCgToLinear", StringId::Desc_Math_AcesCgToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::acesCgToLinearBridge, false, true },
		{ "linearToAcesCg", StringId::Desc_Math_LinearToAcesCg, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToAcesCgBridge, false, true },
		{ "sRgbToLinearPrecise", StringId::Desc_Math_SRgbToLinearPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sRgbToLinearPreciseBridge, false, true },
		{ "linearToSRgbPrecise", StringId::Desc_Math_LinearToSRgbPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSRgbPreciseBridge, false, true },
		{ "colorLcdToLinear", StringId::Desc_Math_ColorLcdToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::colorLcdToLinearBridge, false, true },
		{ "linearToColorLcd", StringId::Desc_Math_LinearToColorLcd, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToColorLcdBridge, false, true },
		{ "smpte170MToLinear", StringId::Desc_Math_Smpte170MToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::smpte170MToLinearBridge, false, true },
		{ "linearToSmpte170M", StringId::Desc_Math_LinearToSmpte170M, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSmpte170MBridge, false, true },
		{ "smpte170MToLinearPrecise", StringId::Desc_Math_Smpte170MToLinearPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::smpte170MToLinearPreciseBridge, false, true },
		{ "linearToSmpte170MPrecise", StringId::Desc_Math_LinearToSmpte170MPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSmpte170MPreciseBridge, false, true },
		{ "dciP3ToLinear", StringId::Desc_Math_DciP3ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::dciP3ToLinearBridge, false, true },
		{ "linearToDciP3", StringId::Desc_Math_LinearToDciP3, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToDciP3Bridge, false, true },
		{ "genericRgbToLinear", StringId::Desc_Math_GenericRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::genericRgbToLinearBridge, false, true },
		{ "linearToGenericRgb", StringId::Desc_Math_LinearToGenericRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToGenericRgbBridge, false, true },
		{ "pow2_8ToLinear", StringId::Desc_Math_Pow2_8ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::pow2_8ToLinearBridge, false, true },
		{ "linearToPow2_8", StringId::Desc_Math_LinearToPow2_8, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToPow2_8Bridge, false, true },
		{ "adobeRgbToLinear", StringId::Desc_Math_AdobeRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::adobeRgbToLinearBridge, false, true },
		{ "linearToAdobeRgb", StringId::Desc_Math_LinearToAdobeRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToAdobeRgbBridge, false, true },
		{ "smpte240MToLinearPrecise", StringId::Desc_Math_Smpte240MToLinearPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::smpte240MToLinearPreciseBridge, false, true },
		{ "linearToSmpte240MPrecise", StringId::Desc_Math_LinearToSmpte240MPrecise, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSmpte240MPreciseBridge, false, true },
		{ "acesCcToLinear", StringId::Desc_Math_AcesCcToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::acesCcToLinearBridge, false, true },
		{ "linearToAcesCc", StringId::Desc_Math_LinearToAcesCc, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToAcesCcBridge, false, true },
		{ "rommRgbToLinear", StringId::Desc_Math_RommRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::rommRgbToLinearBridge, false, true },
		{ "linearToRommRgb", StringId::Desc_Math_LinearToRommRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToRommRgbBridge, false, true },
		{ "rimmRgbToLinear", StringId::Desc_Math_RimmRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::rimmRgbToLinearBridge, false, true },
		{ "linearToRimmRgb", StringId::Desc_Math_LinearToRimmRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToRimmRgbBridge, false, true },
		{ "erimmRgbToLinear", StringId::Desc_Math_ErimmRgbToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::erimmRgbToLinearBridge, false, true },
		{ "linearToErimmRgb", StringId::Desc_Math_LinearToErimmRgb, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToErimmRgbBridge, false, true },
		{ "sLogToLinear", StringId::Desc_Math_SLogToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sLogToLinearBridge, false, true },
		{ "linearToSLog", StringId::Desc_Math_LinearToSLog, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSLogBridge, false, true },
		{ "sLog3ToLinear", StringId::Desc_Math_SLog3ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::sLog3ToLinearBridge, false, true },
		{ "linearToSLog3", StringId::Desc_Math_LinearToSLog3, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToSLog3Bridge, false, true },
		{ "protuneToLinear", StringId::Desc_Math_ProtuneToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::protuneToLinearBridge, false, true },
		{ "linearToProtune", StringId::Desc_Math_LinearToProtune, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToProtuneBridge, false, true },
		{ "canonLog2ToLinear", StringId::Desc_Math_CanonLog2ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::canonLog2ToLinearBridge, false, true },
		{ "linearToCanonLog2", StringId::Desc_Math_LinearToCanonLog2, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToCanonLog2Bridge, false, true },
		{ "canonLog3ToLinear", StringId::Desc_Math_CanonLog3ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::canonLog3ToLinearBridge, false, true },
		{ "linearToCanonLog3", StringId::Desc_Math_LinearToCanonLog3, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToCanonLog3Bridge, false, true },
		{ "aribStdB67ToLinear", StringId::Desc_Math_AribStdB67ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::aribStdB67ToLinearBridge, false, true },
		{ "linearToAribStdB67", StringId::Desc_Math_LinearToAribStdB67, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToAribStdB67Bridge, false, true },
		{ "panalogToLinear", StringId::Desc_Math_PanalogToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::panalogToLinearBridge, false, true },
		{ "linearToPanalog", StringId::Desc_Math_LinearToPanalog, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToPanalogBridge, false, true },
		{ "crtProperToLinear", StringId::Desc_Math_CrtProperToLinear, { { DataType::Double, "val", StringId::Math_Param_Val } }, IntrinsicBridges::crtProperToLinearBridge, false, true },
		{ "crtProperToLinear", StringId::Desc_Math_CrtProperToLinear, { { DataType::Double, "val", StringId::Math_Param_Val }, { DataType::Double, "lw", StringId::Math_Param_Lw } }, IntrinsicBridges::crtProperToLinearBridge },
		{ "crtProperToLinear", StringId::Desc_Math_CrtProperToLinear, { { DataType::Double, "val", StringId::Math_Param_Val }, { DataType::Double, "lw", StringId::Math_Param_Lw }, { DataType::Double, "b", StringId::Math_Param_B } }, IntrinsicBridges::crtProperToLinearBridge },
		{ "linearToCrtProper", StringId::Desc_Math_LinearToCrtProper, { { DataType::Double, "val", StringId::Math_Param_Val } }, IntrinsicBridges::linearToCrtProperBridge, false, true },
		{ "linearToCrtProper", StringId::Desc_Math_LinearToCrtProper, { { DataType::Double, "val", StringId::Math_Param_Val }, { DataType::Double, "lw", StringId::Math_Param_Lw } }, IntrinsicBridges::linearToCrtProperBridge },
		{ "linearToCrtProper", StringId::Desc_Math_LinearToCrtProper, { { DataType::Double, "val", StringId::Math_Param_Val }, { DataType::Double, "lw", StringId::Math_Param_Lw }, { DataType::Double, "b", StringId::Math_Param_B } }, IntrinsicBridges::linearToCrtProperBridge },
		{ "crtProper2ToLinear", StringId::Desc_Math_CrtProper2ToLinear, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::crtProper2ToLinearBridge, false, true },
		{ "linearToCrtProper2", StringId::Desc_Math_LinearToCrtProper2, { { DataType::Double, "x", StringId::Math_Param_X } }, IntrinsicBridges::linearToCrtProper2Bridge, false, true },

		// == SciPy.
		{ "simpson", StringId::Desc_Math_Simpson, { { DataType::Object, "y", StringId::Math_Param_Y } }, IntrinsicBridges::simpsonBridge },
		{ "simpson", StringId::Desc_Math_Simpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "dx", StringId::Math_Param_Dx } }, IntrinsicBridges::simpsonBridge },
		{ "simpson", StringId::Desc_Math_Simpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "x", StringId::Math_Param_XArray } }, IntrinsicBridges::simpsonBridge },
		{ "simpson", StringId::Desc_Math_Simpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::UInt64, "start", StringId::Math_Param_Start }, { DataType::UInt64, "count", StringId::Math_Param_Count }, { DataType::Any, "stride", StringId::Math_Param_Stride } }, IntrinsicBridges::simpsonBridge },
		{ "simpson", StringId::Desc_Math_Simpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::UInt64, "start", StringId::Math_Param_Start }, { DataType::UInt64, "stride", StringId::Math_Param_Stride }, { DataType::Any, "x", StringId::Math_Param_XArray } }, IntrinsicBridges::simpsonBridge },
		{ "simpson", StringId::Desc_Math_Simpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::UInt64, "start", StringId::Math_Param_Start }, { DataType::UInt64, "count", StringId::Math_Param_Count }, { DataType::UInt64, "stride", StringId::Math_Param_Stride }, { DataType::Double, "dx", StringId::Math_Param_Dx } }, IntrinsicBridges::simpsonBridge },

		{ "cumulative_simpson", StringId::Desc_Math_CumulativeSimpson, { { DataType::Object, "y", StringId::Math_Param_Y } }, IntrinsicBridges::cumulativeSimpsonBridge },
		{ "cumulative_simpson", StringId::Desc_Math_CumulativeSimpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "dx", StringId::Math_Param_Dx } }, IntrinsicBridges::cumulativeSimpsonBridge },
		{ "cumulative_simpson", StringId::Desc_Math_CumulativeSimpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "dx", StringId::Math_Param_Dx }, { DataType::Any, "initial", StringId::Math_Param_Initial } }, IntrinsicBridges::cumulativeSimpsonBridge },
		{ "cumulative_simpson", StringId::Desc_Math_CumulativeSimpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "x", StringId::Math_Param_XArray } }, IntrinsicBridges::cumulativeSimpsonBridge },
		{ "cumulative_simpson", StringId::Desc_Math_CumulativeSimpson, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "x", StringId::Math_Param_XArray }, { DataType::Any, "initial", StringId::Math_Param_Initial } }, IntrinsicBridges::cumulativeSimpsonBridge },

		{ "trapezoid", StringId::Desc_Math_Trapezoid, { { DataType::Object, "y", StringId::Math_Param_Y } }, IntrinsicBridges::trapezoidBridge },
		{ "trapezoid", StringId::Desc_Math_Trapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "dx", StringId::Math_Param_Dx } }, IntrinsicBridges::trapezoidBridge },
		{ "trapezoid", StringId::Desc_Math_Trapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "x", StringId::Math_Param_XArray } }, IntrinsicBridges::trapezoidBridge },
		{ "trapezoid", StringId::Desc_Math_Trapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::UInt64, "start", StringId::Math_Param_Start }, { DataType::UInt64, "count", StringId::Math_Param_Count }, { DataType::Any, "stride", StringId::Math_Param_Stride } }, IntrinsicBridges::trapezoidBridge },
		{ "trapezoid", StringId::Desc_Math_Trapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::UInt64, "start", StringId::Math_Param_Start }, { DataType::UInt64, "stride", StringId::Math_Param_Stride }, { DataType::Any, "x", StringId::Math_Param_XArray } }, IntrinsicBridges::trapezoidBridge },
		{ "trapezoid", StringId::Desc_Math_Trapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::UInt64, "start", StringId::Math_Param_Start }, { DataType::UInt64, "count", StringId::Math_Param_Count }, { DataType::UInt64, "stride", StringId::Math_Param_Stride }, { DataType::Double, "dx", StringId::Math_Param_Dx } }, IntrinsicBridges::trapezoidBridge },

		{ "cumulative_trapezoid", StringId::Desc_Math_CumulativeTrapezoid, { { DataType::Object, "y", StringId::Math_Param_Y } }, IntrinsicBridges::cumulativeTrapezoidBridge },
		{ "cumulative_trapezoid", StringId::Desc_Math_CumulativeTrapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "dx", StringId::Math_Param_Dx } }, IntrinsicBridges::cumulativeTrapezoidBridge },
		{ "cumulative_trapezoid", StringId::Desc_Math_CumulativeTrapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "dx", StringId::Math_Param_Dx }, { DataType::Any, "initial", StringId::Math_Param_Initial } }, IntrinsicBridges::cumulativeTrapezoidBridge },
		{ "cumulative_trapezoid", StringId::Desc_Math_CumulativeTrapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "x", StringId::Math_Param_XArray } }, IntrinsicBridges::cumulativeTrapezoidBridge },
		{ "cumulative_trapezoid", StringId::Desc_Math_CumulativeTrapezoid, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Any, "x", StringId::Math_Param_XArray }, { DataType::Any, "initial", StringId::Math_Param_Initial } }, IntrinsicBridges::cumulativeTrapezoidBridge },

		{ "romb", StringId::Desc_Math_Romb, { { DataType::Object, "y", StringId::Math_Param_Y } }, IntrinsicBridges::rombBridge },
		{ "romb", StringId::Desc_Math_Romb, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::Double, "dx", StringId::Math_Param_Dx } }, IntrinsicBridges::rombBridge },
		{ "romb", StringId::Desc_Math_Romb, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::UInt64, "start", StringId::Math_Param_Start }, { DataType::UInt64, "count", StringId::Math_Param_Count }, { DataType::UInt64, "stride", StringId::Math_Param_Stride } }, IntrinsicBridges::rombBridge },
		{ "romb", StringId::Desc_Math_Romb, { { DataType::Object, "y", StringId::Math_Param_Y }, { DataType::UInt64, "start", StringId::Math_Param_Start }, { DataType::UInt64, "count", StringId::Math_Param_Count }, { DataType::UInt64, "stride", StringId::Math_Param_Stride }, { DataType::Double, "dx", StringId::Math_Param_Dx } }, IntrinsicBridges::rombBridge },

		// == NumPy.
		{ "ones", StringId::Desc_Math_Ones, { { DataType::UInt64, "count", StringId::Math_Param_Count } }, IntrinsicBridges::onesBridge },
		{ "ones_like", StringId::Desc_Math_OnesLike, { { DataType::Object, "ref", StringId::Math_Param_RefArray } }, IntrinsicBridges::onesLikeBridge },
		{ "zeros", StringId::Desc_Math_Zeros, { { DataType::UInt64, "count", StringId::Math_Param_Count } }, IntrinsicBridges::zerosBridge },
		{ "zeros_like", StringId::Desc_Math_ZerosLike, { { DataType::Object, "ref", StringId::Math_Param_RefArray } }, IntrinsicBridges::zerosLikeBridge },
		{ "full", StringId::Desc_Math_Full, { { DataType::UInt64, "count", StringId::Math_Param_Count }, { DataType::Double, "fill_value", StringId::Math_Param_FillValue } }, IntrinsicBridges::fullBridge },
		{ "full_like", StringId::Desc_Math_FullLike, { { DataType::Object, "ref", StringId::Math_Param_RefArray }, { DataType::Double, "fill_value", StringId::Math_Param_FillValue } }, IntrinsicBridges::fullLikeBridge },

		{ "linspace", StringId::Desc_Math_Linspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop } }, IntrinsicBridges::linspaceBridge },
		{ "linspace", StringId::Desc_Math_Linspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop }, { DataType::UInt64, "num", StringId::Math_Param_Num } }, IntrinsicBridges::linspaceBridge },
		{ "linspace", StringId::Desc_Math_Linspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop }, { DataType::UInt64, "num", StringId::Math_Param_Num }, { DataType::Integer, "endpoint", StringId::Math_Param_Endpoint } }, IntrinsicBridges::linspaceBridge },

		{ "logspace", StringId::Desc_Math_Logspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop } }, IntrinsicBridges::logspaceBridge },
		{ "logspace", StringId::Desc_Math_Logspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop }, { DataType::UInt64, "num", StringId::Math_Param_Num } }, IntrinsicBridges::logspaceBridge },
		{ "logspace", StringId::Desc_Math_Logspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop }, { DataType::UInt64, "num", StringId::Math_Param_Num }, { DataType::Integer, "endpoint", StringId::Math_Param_Endpoint } }, IntrinsicBridges::logspaceBridge },
		{ "logspace", StringId::Desc_Math_Logspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop }, { DataType::UInt64, "num", StringId::Math_Param_Num }, { DataType::Integer, "endpoint", StringId::Math_Param_Endpoint }, { DataType::Double, "base", StringId::Math_Param_Base } }, IntrinsicBridges::logspaceBridge },

		{ "geomspace", StringId::Desc_Math_Geomspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop } }, IntrinsicBridges::geomspaceBridge },
		{ "geomspace", StringId::Desc_Math_Geomspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop }, { DataType::UInt64, "num", StringId::Math_Param_Num } }, IntrinsicBridges::geomspaceBridge },
		{ "geomspace", StringId::Desc_Math_Geomspace, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop }, { DataType::UInt64, "num", StringId::Math_Param_Num }, { DataType::Integer, "endpoint", StringId::Math_Param_Endpoint } }, IntrinsicBridges::geomspaceBridge },

		{ "arange", StringId::Desc_Math_Arange, { { DataType::Double, "stop", StringId::Math_Param_Stop } }, IntrinsicBridges::arangeBridge },
		{ "arange", StringId::Desc_Math_Arange, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop } }, IntrinsicBridges::arangeBridge },
		{ "arange", StringId::Desc_Math_Arange, { { DataType::Double, "start", StringId::Math_Param_LinspaceStart }, { DataType::Double, "stop", StringId::Math_Param_Stop }, { DataType::Double, "step", StringId::Math_Param_Step } }, IntrinsicBridges::arangeBridge },

		{ "sum", StringId::Desc_Math_Sum, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::sumBridge },
		{ "prod", StringId::Desc_Math_Prod, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::prodBridge },
		{ "mean", StringId::Desc_Math_Mean, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::meanBridge },
		{ "median", StringId::Desc_Math_Median, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::medianBridge },
		{ "std", StringId::Desc_Math_Std, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::stdBridge },
		{ "var", StringId::Desc_Math_Var, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::varBridge },
		{ "ptp", StringId::Desc_Math_Ptp, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::ptpBridge },
		{ "argMin", StringId::Desc_Math_ArgMin, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::argMinBridge },
		{ "argMax", StringId::Desc_Math_ArgMax, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::argMaxBridge },
		{ "percentile", StringId::Desc_Math_Percentile, { { DataType::Object, "v", StringId::Math_Param_V }, { DataType::Double, "q", StringId::Math_Param_PercentileQ } }, IntrinsicBridges::percentileBridge },

		{ "diff", StringId::Desc_Math_Diff, { { DataType::Object, "x", StringId::Math_Param_V } }, IntrinsicBridges::diffBridge },
		{ "diff", StringId::Desc_Math_Diff, { { DataType::Object, "x", StringId::Math_Param_V }, { DataType::UInt64, "n", StringId::Math_Param_DiffN } }, IntrinsicBridges::diffBridge },
		
		{ "cumSum", StringId::Desc_Math_CumSum, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::cumSumBridge },
		{ "cumProd", StringId::Desc_Math_CumProd, { { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::cumProdBridge },
		
		{ "ediff1d", StringId::Desc_Math_Ediff1d, { { DataType::Object, "ary", StringId::Math_Param_V } }, IntrinsicBridges::ediff1dBridge },
		{ "ediff1d", StringId::Desc_Math_Ediff1d, { { DataType::Object, "ary", StringId::Math_Param_V }, { DataType::Object, "to_begin", StringId::Math_Param_ToBegin } }, IntrinsicBridges::ediff1dBridge },
		{ "ediff1d", StringId::Desc_Math_Ediff1d, { { DataType::Object, "ary", StringId::Math_Param_V }, { DataType::Object, "to_begin", StringId::Math_Param_ToBegin }, { DataType::Object, "to_end", StringId::Math_Param_ToEnd } }, IntrinsicBridges::ediff1dBridge },

		{ "clip", StringId::Desc_Math_Clip, { { DataType::Object, "v", StringId::Math_Param_V }, { DataType::Double, "minVal", StringId::Math_Param_MinVal }, { DataType::Double, "maxVal", StringId::Math_Param_MaxVal } }, IntrinsicBridges::clipBridge },
		{ "roll", StringId::Desc_Math_Roll, { { DataType::Object, "v", StringId::Math_Param_V }, { DataType::Integer, "shift", StringId::Math_Param_Shift } }, IntrinsicBridges::rollBridge },
		{ "concatenate", StringId::Desc_Math_Concatenate, { { DataType::Object, "v1", StringId::Math_Param_V }, { DataType::Object, "v2", StringId::Math_Param_V2 } }, IntrinsicBridges::concatenateBridge },
		{ "repeat", StringId::Desc_Math_Repeat, { { DataType::Object, "v", StringId::Math_Param_V }, { DataType::UInt64, "repeats", StringId::Math_Param_Repeats } }, IntrinsicBridges::repeatBridge },
		{ "tile", StringId::Desc_Math_Tile, { { DataType::Object, "v", StringId::Math_Param_V }, { DataType::UInt64, "reps", StringId::Math_Param_Repeats } }, IntrinsicBridges::tileBridge },
		{ "pad", StringId::Desc_Math_Pad, { { DataType::Object, "v", StringId::Math_Param_V }, { DataType::UInt64, "padLeft", StringId::Math_Param_PadLeft }, { DataType::UInt64, "padRight", StringId::Math_Param_PadRight }, { DataType::Double, "constantValue", StringId::Math_Param_ConstantValue } }, IntrinsicBridges::padBridge },

		{ "convolve", StringId::Desc_Math_Convolve, { { DataType::Object, "v1", StringId::Math_Param_V1 }, { DataType::Object, "v2", StringId::Math_Param_V2 } }, IntrinsicBridges::convolveBridge },
		{ "correlate", StringId::Desc_Math_Correlate, { { DataType::Object, "a", StringId::Math_Param_A }, { DataType::Object, "v", StringId::Math_Param_V } }, IntrinsicBridges::correlateBridge },
		{ "interp", StringId::Desc_Math_Interp, { { DataType::Object, "x", StringId::Math_Param_XInterp }, { DataType::Object, "xp", StringId::Math_Param_Xp }, { DataType::Object, "fp", StringId::Math_Param_Fp } }, IntrinsicBridges::interpBridge },

		// == Windowing.
		{ "barthann", StringId::Desc_Math_BarthannWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::barthannBridge },
		{ "bartlett", StringId::Desc_Math_BartlettWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::bartlettBridge },
		{ "blackman", StringId::Desc_Math_BlackmanWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::blackmanBridge },
		{ "blackmanharris", StringId::Desc_Math_BlackmanHarrisWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::blackmanHarrisBridge },
		{ "blackmanhuttal", StringId::Desc_Math_BlackmanNuttalWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::blackmanNuttalBridge },
		{ "bohman", StringId::Desc_Math_BohmanWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::bohmanBridge },
		{ "boxcar", StringId::Desc_Math_BoxcarWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::boxcarBridge },
		{ "chebwin", StringId::Desc_Math_ChebwinWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "at", StringId::Desc_Param_Attenuation } }, IntrinsicBridges::chebwinBridge },
		{ "cosine", StringId::Desc_Math_CosineWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::cosineBridge },
		{ "dpss", StringId::Desc_Math_DpssWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "nw", StringId::Desc_Param_Nw }, { DataType::UInt64, "kMax", StringId::Desc_Param_KMax } }, IntrinsicBridges::dpssBridge },
		{ "exponential", StringId::Desc_Math_ExponentialWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "tau", StringId::Desc_Param_Tau }, { DataType::Double, "center", StringId::Desc_Param_Center } }, IntrinsicBridges::exponentialBridge },
		{ "flatTop", StringId::Desc_Math_FlatTopWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::flatTopBridge },
		{ "gaussian", StringId::Desc_Math_GaussianWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "sigma", StringId::Desc_Param_Sigma } }, IntrinsicBridges::gaussianBridge },
		{ "general_cosine", StringId::Desc_Math_GeneralCosineWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Any, "aVals", StringId::Desc_Param_AVals } }, IntrinsicBridges::generalCosineBridge },
		{ "general_gaussian", StringId::Desc_Math_GeneralGaussianWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "p", StringId::Desc_Param_P }, { DataType::Double, "sigma", StringId::Desc_Param_Sigma } }, IntrinsicBridges::generalGaussianBridge },
		{ "general_hamming", StringId::Desc_Math_GeneralHammingWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "alpha", StringId::Desc_Param_Alpha } }, IntrinsicBridges::generalHammingBridge },
		{ "hann", StringId::Desc_Math_HannWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::hannBridge },
		{ "hamming", StringId::Desc_Math_HammingWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::hammingBridge },
		{ "kaiser", StringId::Desc_Math_KaiserWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "beta", StringId::Desc_Param_Beta } }, IntrinsicBridges::kaiserBridge },
		{ "kaiser_bessel_derived", StringId::Desc_Math_KaiserBesselDerivedWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "beta", StringId::Desc_Param_Beta } }, IntrinsicBridges::kaiserBesselDerivedBridge },
		{ "lanczos", StringId::Desc_Math_LanczosWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::lanczosBridge },
		{ "nuttall", StringId::Desc_Math_NuttallWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::nuttallBridge },
		{ "parzen", StringId::Desc_Math_ParzenWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::parzenBridge },
		{ "taylor", StringId::Desc_Math_TaylorWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Int64, "nBar", StringId::Desc_Param_NBar }, { DataType::Double, "sll", StringId::Desc_Param_Sll }, { DataType::Any, "norm", StringId::Desc_Param_Norm } }, IntrinsicBridges::taylorBridge },
		{ "triang", StringId::Desc_Math_TriangWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples } }, IntrinsicBridges::triangBridge },
		{ "tukey", StringId::Desc_Math_TukeyWindow, { { DataType::UInt64, "n", StringId::Desc_Param_Samples }, { DataType::Double, "alpha", StringId::Desc_Param_Alpha } }, IntrinsicBridges::tukeyBridge },

		{ "sinc_filter_lpf", StringId::Desc_Math_SincFilterLpf, { { DataType::Double, "hz", StringId::Desc_Param_Hz }, { DataType::Double, "fc", StringId::Desc_Param_Fc }, { DataType::UInt64, "m", StringId::Desc_Param_FilterWidthM } }, IntrinsicBridges::sincFilterLpfBridge },
		{ "sinc_filter_hpf", StringId::Desc_Math_SincFilterHpf, { { DataType::Double, "hz", StringId::Desc_Param_Hz }, { DataType::Double, "fc", StringId::Desc_Param_Fc }, { DataType::UInt64, "m", StringId::Desc_Param_FilterWidthM } }, IntrinsicBridges::sincFilterHpfBridge },
		{ "sinc_filter_bpf", StringId::Desc_Math_SincFilterBpf, { { DataType::Double, "hz", StringId::Desc_Param_Hz }, { DataType::Double, "f1", StringId::Desc_Param_F1 }, { DataType::Double, "f2", StringId::Desc_Param_F2 }, { DataType::UInt64, "m", StringId::Desc_Param_FilterWidthM } }, IntrinsicBridges::sincFilterBpfBridge },

#include "SimdBridgeTable.inl"
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
				registerFunction(builtInFunctions[i].name, builtInFunctions[i].parameters, builtInFunctions[i].callback, builtInFunctions[i].operateOnVectorElements);
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

}	// namespace ve
