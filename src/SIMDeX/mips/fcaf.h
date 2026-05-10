#if !defined(SIMDE_MIPS_MSA_FCAF_H)
#define SIMDE_MIPS_MSA_FCAF_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_fcaf_w(simde_v4f32 a, simde_v4f32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fcaf_w(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    /* vceqq_f32 cleanly evaluates the floats for sNaNs in NEON, then we return 0 */
    (void)vceqq_f32(a, b);
    return vdupq_n_s32(0);
  #else
    simde_v4i32_private r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      /* _mm_cmpeq_ps forces FPU evaluation, updating the CSR if an sNaN is present */
      (void)_mm_cmpeq_ps(simde_v4f32_to_private(a).m128, simde_v4f32_to_private(b).m128);
      r_.m128i = _mm_setzero_si128();
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      (void)wasm_f32x4_eq(simde_v4f32_to_private(a).v128, simde_v4f32_to_private(b).v128);
      r_.v128 = wasm_i32x4_const(0, 0, 0, 0);
    #else
      simde_v4f32_private
        a_ = simde_v4f32_to_private(a),
        b_ = simde_v4f32_to_private(b);

      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        /* Volatile forces the compiler to evaluate the comparison for exceptions */
        volatile bool dummy = (a_.values[i] == b_.values[i]);
        (void)dummy;
        r_.values[i] = 0;
      }
    #endif

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fcaf_w
  #define __msa_fcaf_w(a, b) simde_msa_fcaf_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_fcaf_d(simde_v2f64 a, simde_v2f64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fcaf_d(a, b);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    (void)vceqq_f64(a, b);
    return vreinterpretq_s64_s32(vdupq_n_s32(0));
  #else
    simde_v2i64_private r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      (void)_mm_cmpeq_pd(simde_v2f64_to_private(a).m128d, simde_v2f64_to_private(b).m128d);
      r_.m128i = _mm_setzero_si128();
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      (void)wasm_f64x2_eq(simde_v2f64_to_private(a).v128, simde_v2f64_to_private(b).v128);
      r_.v128 = wasm_i64x2_const(0, 0);
    #else
      simde_v2f64_private
        a_ = simde_v2f64_to_private(a),
        b_ = simde_v2f64_to_private(b);

      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        volatile bool dummy = (a_.values[i] == b_.values[i]);
        (void)dummy;
        r_.values[i] = 0;
      }
    #endif

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fcaf_d
  #define __msa_fcaf_d(a, b) simde_msa_fcaf_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
