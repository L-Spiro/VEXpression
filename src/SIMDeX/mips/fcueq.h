#if !defined(SIMDE_MIPS_MSA_FCUEQ_H)
#define SIMDE_MIPS_MSA_FCUEQ_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_fcueq_w(simde_v4f32 a, simde_v4f32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fcueq_w(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vreinterpretq_s32_u32(vmvnq_u32(vorrq_u32(vcltq_f32(a, b), vcgtq_f32(a, b))));
  #else
    simde_v4f32_private
      a_ = simde_v4f32_to_private(a),
      b_ = simde_v4f32_to_private(b);
    simde_v4i32_private r_;

    #if defined(SIMDE_X86_SSE_NATIVE)
      r_.m128i = _mm_castps_si128(_mm_or_ps(_mm_cmpunord_ps(a_.m128, b_.m128), _mm_cmpeq_ps(a_.m128, b_.m128)));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        /* Evaluates to true if either is NaN, OR they are equal */
        r_.values[i] = (!(a_.values[i] < b_.values[i]) && !(a_.values[i] > b_.values[i])) ? ~INT32_C(0) : INT32_C(0);
      }
    #endif

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fcueq_w
  #define __msa_fcueq_w(a, b) simde_msa_fcueq_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_fcueq_d(simde_v2f64 a, simde_v2f64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fcueq_d(a, b);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vreinterpretq_s64_u64(vmvnq_u64(vorrq_u64(vcltq_f64(a, b), vcgtq_f64(a, b))));
  #else
    simde_v2f64_private
      a_ = simde_v2f64_to_private(a),
      b_ = simde_v2f64_to_private(b);
    simde_v2i64_private r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128i = _mm_castpd_si128(_mm_or_pd(_mm_cmpunord_pd(a_.m128d, b_.m128d), _mm_cmpeq_pd(a_.m128d, b_.m128d)));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (!(a_.values[i] < b_.values[i]) && !(a_.values[i] > b_.values[i])) ? ~INT64_C(0) : INT64_C(0);
      }
    #endif

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fcueq_d
  #define __msa_fcueq_d(a, b) simde_msa_fcueq_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
