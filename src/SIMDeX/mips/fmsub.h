#if !defined(SIMDE_MIPS_MSA_FMSUB_H)
#define SIMDE_MIPS_MSA_FMSUB_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4f32
simde_msa_fmsub_w(simde_v4f32 a, simde_v4f32 b, simde_v4f32 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fmsub_w(a, b, c);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE) && defined(__ARM_FEATURE_FMA)
    return vmlsq_f32(a, b, c);
  #else
    simde_v4f32_private
      a_ = simde_v4f32_to_private(a),
      b_ = simde_v4f32_to_private(b),
      c_ = simde_v4f32_to_private(c),
      r_;

    #if defined(SIMDE_X86_FMA_NATIVE)
      r_.m128 = _mm_fnmadd_ps(b_.m128, c_.m128, a_.m128);
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_f32x4_sub(a_.v128, wasm_f32x4_mul(b_.v128, c_.v128));
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = a_.values - (b_.values * c_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = a_.values[i] - (b_.values[i] * c_.values[i]);
      }
    #endif

    return simde_v4f32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fmsub_w
  #define __msa_fmsub_w(a, b, c) simde_msa_fmsub_w((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2f64
simde_msa_fmsub_d(simde_v2f64 a, simde_v2f64 b, simde_v2f64 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fmsub_d(a, b, c);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vmlsq_f64(a, b, c);
  #else
    simde_v2f64_private
      a_ = simde_v2f64_to_private(a),
      b_ = simde_v2f64_to_private(b),
      c_ = simde_v2f64_to_private(c),
      r_;

    #if defined(SIMDE_X86_FMA_NATIVE)
      r_.m128d = _mm_fnmadd_pd(b_.m128d, c_.m128d, a_.m128d);
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_f64x2_sub(a_.v128, wasm_f64x2_mul(b_.v128, c_.v128));
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = a_.values - (b_.values * c_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = a_.values[i] - (b_.values[i] * c_.values[i]);
      }
    #endif

    return simde_v2f64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fmsub_d
  #define __msa_fmsub_d(a, b, c) simde_msa_fmsub_d((a), (b), (c))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
