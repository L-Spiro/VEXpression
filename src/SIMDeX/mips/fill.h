#if !defined(SIMDE_MIPS_MSA_FILL_H)
#define SIMDE_MIPS_MSA_FILL_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_fill_b(int32_t a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fill_b(a);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vdupq_n_s8(HEDLEY_STATIC_CAST(int8_t, a));
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_set1_epi8(HEDLEY_STATIC_CAST(int8_t, a));
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i8x16_splat(HEDLEY_STATIC_CAST(int8_t, a));
  #else
    simde_v16i8_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(int8_t, a);
    }

    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fill_b
  #define __msa_fill_b(a) simde_msa_fill_b(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_fill_h(int32_t a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fill_h(a);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vdupq_n_s16(HEDLEY_STATIC_CAST(int16_t, a));
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_set1_epi16(HEDLEY_STATIC_CAST(int16_t, a));
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i16x8_splat(HEDLEY_STATIC_CAST(int16_t, a));
  #else
    simde_v8i16_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(int16_t, a);
    }

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fill_h
  #define __msa_fill_h(a) simde_msa_fill_h(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_fill_w(int32_t a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fill_w(a);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vdupq_n_s32(a);
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_set1_epi32(a);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i32x4_splat(a);
  #else
    simde_v4i32_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a;
    }

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fill_w
  #define __msa_fill_w(a) simde_msa_fill_w(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_fill_d(int64_t a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fill_d(a);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vdupq_n_s64(a);
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_set1_epi64x(a);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i64x2_splat(a);
  #else
    simde_v2i64_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a;
    }

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fill_d
  #define __msa_fill_d(a) simde_msa_fill_d(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
