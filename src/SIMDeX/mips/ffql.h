#if !defined(SIMDE_MIPS_MSA_FFQL_H)
#define SIMDE_MIPS_MSA_FFQL_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4f32
simde_msa_ffql_w(simde_v8i16 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ffql_w(a);
  #else
    simde_v8i16_private a_ = simde_v8i16_to_private(a);
    simde_v4f32_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      /* Left half -> upper 4 elements. Convert Q15. */
      r_.values[i] = HEDLEY_STATIC_CAST(simde_float32, a_.values[i + 4]) / 32768.0f;
    }

    return simde_v4f32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ffql_w
  #define __msa_ffql_w(a) simde_msa_ffql_w(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2f64
simde_msa_ffql_d(simde_v4i32 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ffql_d(a);
  #else
    simde_v4i32_private a_ = simde_v4i32_to_private(a);
    simde_v2f64_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      /* Left half -> upper 2 elements. Convert Q31. */
      r_.values[i] = HEDLEY_STATIC_CAST(simde_float64, a_.values[i + 2]) / 2147483648.0;
    }

    return simde_v2f64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ffql_d
  #define __msa_ffql_d(a) simde_msa_ffql_d(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
