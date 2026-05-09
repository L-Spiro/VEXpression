#if !defined(SIMDE_MIPS_MSA_ASUB_H)
#define SIMDE_MIPS_MSA_ASUB_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_asub_s_b(simde_v16i8 a, simde_v16i8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_asub_s_b(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vreinterpretq_s8_u8(vabdq_s8(a, b));
  #elif defined(SIMDE_POWER_ALTIVEC_P6_NATIVE)
    return vec_sub(vec_max(a, b), vec_min(a, b));
  #else
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      b_ = simde_v16i8_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE4_1_NATIVE)
      r_.m128i = _mm_sub_epi8(_mm_max_epi8(a_.m128i, b_.m128i), _mm_min_epi8(a_.m128i, b_.m128i));
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_i8x16_sub(wasm_i8x16_max_s(a_.v128, b_.v128), wasm_i8x16_min_s(a_.v128, b_.v128));
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      const __typeof__(a_.values) a_greater_b = HEDLEY_REINTERPRET_CAST(__typeof__(a_.values), a_.values > b_.values);
      r_.values =
        ((a_.values - b_.values) & a_greater_b) |
        ((b_.values - a_.values) & ~a_greater_b);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] > b_.values[i]) ? (a_.values[i] - b_.values[i]) : (b_.values[i] - a_.values[i]);
      }
    #endif

    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_asub_s_b
  #define __msa_asub_s_b(a, b) simde_msa_asub_s_b((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_asub_s_h(simde_v8i16 a, simde_v8i16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_asub_s_h(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vreinterpretq_s16_u16(vabdq_s16(a, b));
  #elif defined(SIMDE_POWER_ALTIVEC_P6_NATIVE)
    return vec_sub(vec_max(a, b), vec_min(a, b));
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE4_1_NATIVE)
      r_.m128i = _mm_sub_epi16(_mm_max_epi16(a_.m128i, b_.m128i), _mm_min_epi16(a_.m128i, b_.m128i));
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_i16x8_sub(wasm_i16x8_max_s(a_.v128, b_.v128), wasm_i16x8_min_s(a_.v128, b_.v128));
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      const __typeof__(a_.values) a_greater_b = HEDLEY_REINTERPRET_CAST(__typeof__(a_.values), a_.values > b_.values);
      r_.values =
        ((a_.values - b_.values) & a_greater_b) |
        ((b_.values - a_.values) & ~a_greater_b);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] > b_.values[i]) ? (a_.values[i] - b_.values[i]) : (b_.values[i] - a_.values[i]);
      }
    #endif

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_asub_s_h
  #define __msa_asub_s_h(a, b) simde_msa_asub_s_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_asub_s_w(simde_v4i32 a, simde_v4i32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_asub_s_w(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vreinterpretq_s32_u32(vabdq_s32(a, b));
  #elif defined(SIMDE_POWER_ALTIVEC_P6_NATIVE)
    return vec_sub(vec_max(a, b), vec_min(a, b));
  #else
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE4_1_NATIVE)
      r_.m128i = _mm_sub_epi32(_mm_max_epi32(a_.m128i, b_.m128i), _mm_min_epi32(a_.m128i, b_.m128i));
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_i32x4_sub(wasm_i32x4_max_s(a_.v128, b_.v128), wasm_i32x4_min_s(a_.v128, b_.v128));
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      const __typeof__(a_.values) a_greater_b = HEDLEY_REINTERPRET_CAST(__typeof__(a_.values), a_.values > b_.values);
      r_.values =
        ((a_.values - b_.values) & a_greater_b) |
        ((b_.values - a_.values) & ~a_greater_b);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] > b_.values[i]) ? (a_.values[i] - b_.values[i]) : (b_.values[i] - a_.values[i]);
      }
    #endif

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_asub_s_w
  #define __msa_asub_s_w(a, b) simde_msa_asub_s_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_asub_s_d(simde_v2i64 a, simde_v2i64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_asub_s_d(a, b);
  #else
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      b_ = simde_v2i64_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      const __typeof__(a_.values) a_greater_b = HEDLEY_REINTERPRET_CAST(__typeof__(a_.values), a_.values > b_.values);
      r_.values =
        ((a_.values - b_.values) & a_greater_b) |
        ((b_.values - a_.values) & ~a_greater_b);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] > b_.values[i]) ? (a_.values[i] - b_.values[i]) : (b_.values[i] - a_.values[i]);
      }
    #endif

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_asub_s_d
  #define __msa_asub_s_d(a, b) simde_msa_asub_s_d((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v16u8
simde_msa_asub_u_b(simde_v16u8 a, simde_v16u8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_asub_u_b(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vabdq_u8(a, b);
  #elif defined(SIMDE_POWER_ALTIVEC_P6_NATIVE)
    return vec_sub(vec_max(a, b), vec_min(a, b));
  #else
    simde_v16u8_private
      a_ = simde_v16u8_to_private(a),
      b_ = simde_v16u8_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128i = _mm_sub_epi8(_mm_max_epu8(a_.m128i, b_.m128i), _mm_min_epu8(a_.m128i, b_.m128i));
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_i8x16_sub(wasm_i8x16_max_u(a_.v128, b_.v128), wasm_i8x16_min_u(a_.v128, b_.v128));
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      const __typeof__(a_.values) a_greater_b = HEDLEY_REINTERPRET_CAST(__typeof__(a_.values), a_.values > b_.values);
      r_.values =
        ((a_.values - b_.values) & a_greater_b) |
        ((b_.values - a_.values) & ~a_greater_b);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] > b_.values[i]) ? (a_.values[i] - b_.values[i]) : (b_.values[i] - a_.values[i]);
      }
    #endif

    return simde_v16u8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_asub_u_b
  #define __msa_asub_u_b(a, b) simde_msa_asub_u_b((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8u16
simde_msa_asub_u_h(simde_v8u16 a, simde_v8u16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_asub_u_h(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vabdq_u16(a, b);
  #elif defined(SIMDE_POWER_ALTIVEC_P6_NATIVE)
    return vec_sub(vec_max(a, b), vec_min(a, b));
  #else
    simde_v8u16_private
      a_ = simde_v8u16_to_private(a),
      b_ = simde_v8u16_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE4_1_NATIVE)
      r_.m128i = _mm_sub_epi16(_mm_max_epu16(a_.m128i, b_.m128i), _mm_min_epu16(a_.m128i, b_.m128i));
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_i16x8_sub(wasm_i16x8_max_u(a_.v128, b_.v128), wasm_i16x8_min_u(a_.v128, b_.v128));
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      const __typeof__(a_.values) a_greater_b = HEDLEY_REINTERPRET_CAST(__typeof__(a_.values), a_.values > b_.values);
      r_.values =
        ((a_.values - b_.values) & a_greater_b) |
        ((b_.values - a_.values) & ~a_greater_b);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] > b_.values[i]) ? (a_.values[i] - b_.values[i]) : (b_.values[i] - a_.values[i]);
      }
    #endif

    return simde_v8u16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_asub_u_h
  #define __msa_asub_u_h(a, b) simde_msa_asub_u_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4u32
simde_msa_asub_u_w(simde_v4u32 a, simde_v4u32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_asub_u_w(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vabdq_u32(a, b);
  #elif defined(SIMDE_POWER_ALTIVEC_P6_NATIVE)
    return vec_sub(vec_max(a, b), vec_min(a, b));
  #else
    simde_v4u32_private
      a_ = simde_v4u32_to_private(a),
      b_ = simde_v4u32_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE4_1_NATIVE)
      r_.m128i = _mm_sub_epi32(_mm_max_epu32(a_.m128i, b_.m128i), _mm_min_epu32(a_.m128i, b_.m128i));
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_i32x4_sub(wasm_i32x4_max_u(a_.v128, b_.v128), wasm_i32x4_min_u(a_.v128, b_.v128));
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      const __typeof__(a_.values) a_greater_b = HEDLEY_REINTERPRET_CAST(__typeof__(a_.values), a_.values > b_.values);
      r_.values =
        ((a_.values - b_.values) & a_greater_b) |
        ((b_.values - a_.values) & ~a_greater_b);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] > b_.values[i]) ? (a_.values[i] - b_.values[i]) : (b_.values[i] - a_.values[i]);
      }
    #endif

    return simde_v4u32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_asub_u_w
  #define __msa_asub_u_w(a, b) simde_msa_asub_u_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2u64
simde_msa_asub_u_d(simde_v2u64 a, simde_v2u64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_asub_u_d(a, b);
  #else
    simde_v2u64_private
      a_ = simde_v2u64_to_private(a),
      b_ = simde_v2u64_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      const __typeof__(a_.values) a_greater_b = HEDLEY_REINTERPRET_CAST(__typeof__(a_.values), a_.values > b_.values);
      r_.values =
        ((a_.values - b_.values) & a_greater_b) |
        ((b_.values - a_.values) & ~a_greater_b);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] > b_.values[i]) ? (a_.values[i] - b_.values[i]) : (b_.values[i] - a_.values[i]);
      }
    #endif

    return simde_v2u64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_asub_u_d
  #define __msa_asub_u_d(a, b) simde_msa_asub_u_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif