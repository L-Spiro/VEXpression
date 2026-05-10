#if !defined(SIMDE_MIPS_MSA_FMIN_H)
#define SIMDE_MIPS_MSA_FMIN_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4f32
simde_msa_fmin_w(simde_v4f32 a, simde_v4f32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fmin_w(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vminq_f32(a, b);
  #elif defined(SIMDE_X86_SSE_NATIVE)
    return _mm_min_ps(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_f32x4_min(a, b);
  #else
    simde_v4f32_private
      a_ = simde_v4f32_to_private(a),
      b_ = simde_v4f32_to_private(b),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] < b_.values[i]) ? a_.values[i] : b_.values[i];
    }

    return simde_v4f32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fmin_w
  #define __msa_fmin_w(a, b) simde_msa_fmin_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2f64
simde_msa_fmin_d(simde_v2f64 a, simde_v2f64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fmin_d(a, b);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vminq_f64(a, b);
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_min_pd(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_f64x2_min(a, b);
  #else
    simde_v2f64_private
      a_ = simde_v2f64_to_private(a),
      b_ = simde_v2f64_to_private(b),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] < b_.values[i]) ? a_.values[i] : b_.values[i];
    }

    return simde_v2f64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fmin_d
  #define __msa_fmin_d(a, b) simde_msa_fmin_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
