#if !defined(SIMDE_MIPS_MSA_FFINT_H)
#define SIMDE_MIPS_MSA_FFINT_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4f32
simde_msa_ffint_s_w(simde_v4i32 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ffint_s_w(a);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vcvtq_f32_s32(a);
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_cvtepi32_ps(a);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_f32x4_convert_i32x4(a);
  #else
    simde_v4i32_private a_ = simde_v4i32_to_private(a);
    simde_v4f32_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(simde_float32, a_.values[i]);
    }

    return simde_v4f32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ffint_s_w
  #define __msa_ffint_s_w(a) simde_msa_ffint_s_w(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2f64
simde_msa_ffint_s_d(simde_v2i64 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ffint_s_d(a);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vcvtq_f64_s64(a);
  #else
    simde_v2i64_private a_ = simde_v2i64_to_private(a);
    simde_v2f64_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(simde_float64, a_.values[i]);
    }

    return simde_v2f64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ffint_s_d
  #define __msa_ffint_s_d(a) simde_msa_ffint_s_d(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4f32
simde_msa_ffint_u_w(simde_v4u32 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ffint_u_w(a);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vcvtq_f32_u32(a);
  #else
    simde_v4u32_private a_ = simde_v4u32_to_private(a);
    simde_v4f32_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(simde_float32, a_.values[i]);
    }

    return simde_v4f32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ffint_u_w
  #define __msa_ffint_u_w(a) simde_msa_ffint_u_w(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2f64
simde_msa_ffint_u_d(simde_v2u64 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ffint_u_d(a);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vcvtq_f64_u64(a);
  #else
    simde_v2u64_private a_ = simde_v2u64_to_private(a);
    simde_v2f64_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(simde_float64, a_.values[i]);
    }

    return simde_v2f64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ffint_u_d
  #define __msa_ffint_u_d(a) simde_msa_ffint_u_d(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
