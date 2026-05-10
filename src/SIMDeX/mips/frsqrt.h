#if !defined(SIMDE_MIPS_MSA_FRSQRT_H)
#define SIMDE_MIPS_MSA_FRSQRT_H

#include <simde/mips/msa/types.h>
#include <simde/simde-math.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4f32
simde_msa_frsqrt_w(simde_v4f32 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_frsqrt_w(a);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vrsqrteq_f32(a);
  #else
    simde_v4f32_private
      a_ = simde_v4f32_to_private(a),
      r_;

    #if defined(SIMDE_X86_SSE_NATIVE)
      r_.m128 = _mm_rsqrt_ps(a_.m128);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = 1.0f / simde_math_sqrtf(a_.values[i]);
      }
    #endif

    return simde_v4f32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_frsqrt_w
  #define __msa_frsqrt_w(a) simde_msa_frsqrt_w(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2f64
simde_msa_frsqrt_d(simde_v2f64 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_frsqrt_d(a);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vrsqrteq_f64(a);
  #else
    simde_v2f64_private
      a_ = simde_v2f64_to_private(a),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = 1.0 / simde_math_sqrt(a_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = 1.0 / simde_math_sqrt(a_.values[i]);
      }
    #endif

    return simde_v2f64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_frsqrt_d
  #define __msa_frsqrt_d(a) simde_msa_frsqrt_d(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
