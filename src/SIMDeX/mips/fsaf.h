#if !defined(SIMDE_MIPS_MSA_FSAF_H)
#define SIMDE_MIPS_MSA_FSAF_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_fsaf_w(simde_v4f32 a, simde_v4f32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fsaf_w(a, b);
  #else
    simde_v4f32_private
      a_ = simde_v4f32_to_private(a),
      b_ = simde_v4f32_to_private(b);
    simde_v4i32_private r_;

    #if defined(SIMDE_X86_SSE_NATIVE)
      /* _mm_cmp_ps with OQ or _mm_comilt forces FPU exception on QNaN/SNaN */
      (void)_mm_cmplt_ps(a_.m128, b_.m128); 
      r_.m128i = _mm_setzero_si128();
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        /* Relational < and > strictly raise invalid op exception on Quiet NaNs in C */
        volatile bool dummy = (a_.values[i] < b_.values[i]) || (a_.values[i] > b_.values[i]);
        (void)dummy;
        r_.values[i] = 0;
      }
    #endif

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fsaf_w
  #define __msa_fsaf_w(a, b) simde_msa_fsaf_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_fsaf_d(simde_v2f64 a, simde_v2f64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fsaf_d(a, b);
  #else
    simde_v2f64_private
      a_ = simde_v2f64_to_private(a),
      b_ = simde_v2f64_to_private(b);
    simde_v2i64_private r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      (void)_mm_cmplt_pd(a_.m128d, b_.m128d);
      r_.m128i = _mm_setzero_si128();
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        volatile bool dummy = (a_.values[i] < b_.values[i]) || (a_.values[i] > b_.values[i]);
        (void)dummy;
        r_.values[i] = 0;
      }
    #endif

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fsaf_d
  #define __msa_fsaf_d(a, b) simde_msa_fsaf_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
