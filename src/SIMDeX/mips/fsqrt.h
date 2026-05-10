#if !defined(SIMDE_MIPS_MSA_FSQRT_H)
#define SIMDE_MIPS_MSA_FSQRT_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4f32
simde_msa_fsqrt_w(simde_v4f32 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fsqrt_w(a);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vsqrtq_f32(a);
  #else
    simde_v4f32_private
      a_ = simde_v4f32_to_private(a),
      r_;

    #if defined(SIMDE_X86_SSE_NATIVE)
      r_.m128 = _mm_sqrt_ps(a_.m128);
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_f32x4_sqrt(a_.v128);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = simde_math_sqrtf(a_.values[i]);
      }
    #endif

    return simde_v4f32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fsqrt_w
  #define __msa_fsqrt_w(a) simde_msa_fsqrt_w(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2f64
simde_msa_fsqrt_d(simde_v2f64 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fsqrt_d(a);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vsqrtq_f64(a);
  #else
    simde_v2f64_private
      a_ = simde_v2f64_to_private(a),
      r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128d = _mm_sqrt_pd(a_.m128d);
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_f64x2_sqrt(a_.v128);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = simde_math_sqrt(a_.values[i]);
      }
    #endif

    return simde_v2f64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fsqrt_d
  #define __msa_fsqrt_d(a) simde_msa_fsqrt_d(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
