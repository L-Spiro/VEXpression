#if !defined(SIMDE_MIPS_MSA_FEXUPL_H)
#define SIMDE_MIPS_MSA_FEXUPL_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4f32
simde_msa_fexupl_w(simde_v8i16 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fexupl_w(a);
  #else
    simde_v8i16_private a_ = simde_v8i16_to_private(a);
    simde_v4f32_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      /* Left half corresponds to the upper 4 elements */
      r_.values[i] = simde_float16_to_float32(HEDLEY_STATIC_CAST(simde_float16, a_.values[i + 4]));
    }

    return simde_v4f32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fexupl_w
  #define __msa_fexupl_w(a) simde_msa_fexupl_w(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2f64
simde_msa_fexupl_d(simde_v4f32 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fexupl_d(a);
  #else
    simde_v4f32_private a_ = simde_v4f32_to_private(a);
    simde_v2f64_private r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128d = _mm_cvtps_pd(_mm_castsi128_ps(_mm_srli_si128(_mm_castps_si128(a_.m128), 8)));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = HEDLEY_STATIC_CAST(simde_float64, a_.values[i + 2]);
      }
    #endif

    return simde_v2f64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fexupl_d
  #define __msa_fexupl_d(a) simde_msa_fexupl_d(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
