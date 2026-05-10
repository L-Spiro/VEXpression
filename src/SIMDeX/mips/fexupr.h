#if !defined(SIMDE_MIPS_MSA_FEXUPR_H)
#define SIMDE_MIPS_MSA_FEXUPR_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4f32
simde_msa_fexupr_w(simde_v8i16 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fexupr_w(a);
  #else
    simde_v8i16_private a_ = simde_v8i16_to_private(a);
    simde_v4f32_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      /* Right half corresponds to the lower 4 elements */
      r_.values[i] = simde_float16_to_float32(HEDLEY_STATIC_CAST(simde_float16, a_.values[i]));
    }

    return simde_v4f32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fexupr_w
  #define __msa_fexupr_w(a) simde_msa_fexupr_w(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2f64
simde_msa_fexupr_d(simde_v4f32 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fexupr_d(a);
  #else
    simde_v4f32_private a_ = simde_v4f32_to_private(a);
    simde_v2f64_private r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128d = _mm_cvtps_pd(a_.m128);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = HEDLEY_STATIC_CAST(simde_float64, a_.values[i]);
      }
    #endif

    return simde_v2f64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fexupr_d
  #define __msa_fexupr_d(a) simde_msa_fexupr_d(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
