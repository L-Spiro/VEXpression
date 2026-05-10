#if !defined(SIMDE_MIPS_MSA_FEXP2_H)
#define SIMDE_MIPS_MSA_FEXP2_H

#include <simde/mips/msa/types.h>
#include <math.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4f32
simde_msa_fexp2_w(simde_v4f32 a, simde_v4i32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fexp2_w(a, b);
  #else
    simde_v4f32_private a_ = simde_v4f32_to_private(a);
    simde_v4i32_private b_ = simde_v4i32_to_private(b);
    simde_v4f32_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = ldexpf(a_.values[i], b_.values[i]);
    }

    return simde_v4f32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fexp2_w
  #define __msa_fexp2_w(a, b) simde_msa_fexp2_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2f64
simde_msa_fexp2_d(simde_v2f64 a, simde_v2i64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fexp2_d(a, b);
  #else
    simde_v2f64_private a_ = simde_v2f64_to_private(a);
    simde_v2i64_private b_ = simde_v2i64_to_private(b);
    simde_v2f64_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      /* Safe explicit cast to ensure the int64 exponent works with standard ldexp */
      r_.values[i] = ldexp(a_.values[i], HEDLEY_STATIC_CAST(int, b_.values[i]));
    }

    return simde_v2f64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fexp2_d
  #define __msa_fexp2_d(a, b) simde_msa_fexp2_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
