#if !defined(SIMDE_MIPS_MSA_FTRUNC_H)
#define SIMDE_MIPS_MSA_FTRUNC_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_ftrunc_s_w(simde_v4f32 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ftrunc_s_w(a);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vcvtq_s32_f32(a);
  #else
    simde_v4f32_private a_ = simde_v4f32_to_private(a);
    simde_v4i32_private r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128i = _mm_cvttps_epi32(a_.m128);
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_i32x4_trunc_sat_f32x4(a_.v128);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = HEDLEY_STATIC_CAST(int32_t, a_.values[i]);
      }
    #endif

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ftrunc_s_w
  #define __msa_ftrunc_s_w(a) simde_msa_ftrunc_s_w(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_ftrunc_s_d(simde_v2f64 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ftrunc_s_d(a);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vcvtq_s64_f64(a);
  #else
    simde_v2f64_private a_ = simde_v2f64_to_private(a);
    simde_v2i64_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(int64_t, a_.values[i]);
    }

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ftrunc_s_d
  #define __msa_ftrunc_s_d(a) simde_msa_ftrunc_s_d(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4u32
simde_msa_ftrunc_u_w(simde_v4f32 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ftrunc_u_w(a);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vcvtq_u32_f32(a);
  #else
    simde_v4f32_private a_ = simde_v4f32_to_private(a);
    simde_v4u32_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(uint32_t, a_.values[i]);
    }

    return simde_v4u32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ftrunc_u_w
  #define __msa_ftrunc_u_w(a) simde_msa_ftrunc_u_w(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2u64
simde_msa_ftrunc_u_d(simde_v2f64 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ftrunc_u_d(a);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vcvtq_u64_f64(a);
  #else
    simde_v2f64_private a_ = simde_v2f64_to_private(a);
    simde_v2u64_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(uint64_t, a_.values[i]);
    }

    return simde_v2u64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ftrunc_u_d
  #define __msa_ftrunc_u_d(a) simde_msa_ftrunc_u_d(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
