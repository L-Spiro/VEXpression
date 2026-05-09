#if !defined(SIMDE_MIPS_MSA_CLT_H)
#define SIMDE_MIPS_MSA_CLT_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_clt_s_b(simde_v16i8 a, simde_v16i8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_clt_s_b(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vreinterpretq_s8_u8(vcltq_s8(a, b));
  #elif defined(SIMDE_POWER_ALTIVEC_P6_NATIVE)
    return HEDLEY_REINTERPRET_CAST(simde_v16i8, vec_cmplt(a, b));
  #else
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      b_ = simde_v16i8_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128i = _mm_cmplt_epi8(a_.m128i, b_.m128i);
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_i8x16_lt(a_.v128, b_.v128);
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = HEDLEY_REINTERPRET_CAST(__typeof__(r_.values), a_.values < b_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] < b_.values[i]) ? -1 : 0;
      }
    #endif

    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_clt_s_b
  #define __msa_clt_s_b(a, b) simde_msa_clt_s_b((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_clt_s_h(simde_v8i16 a, simde_v8i16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_clt_s_h(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vreinterpretq_s16_u16(vcltq_s16(a, b));
  #elif defined(SIMDE_POWER_ALTIVEC_P6_NATIVE)
    return HEDLEY_REINTERPRET_CAST(simde_v8i16, vec_cmplt(a, b));
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128i = _mm_cmplt_epi16(a_.m128i, b_.m128i);
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_i16x8_lt(a_.v128, b_.v128);
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = HEDLEY_REINTERPRET_CAST(__typeof__(r_.values), a_.values < b_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] < b_.values[i]) ? -1 : 0;
      }
    #endif

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_clt_s_h
  #define __msa_clt_s_h(a, b) simde_msa_clt_s_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_clt_s_w(simde_v4i32 a, simde_v4i32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_clt_s_w(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vreinterpretq_s32_u32(vcltq_s32(a, b));
  #elif defined(SIMDE_POWER_ALTIVEC_P6_NATIVE)
    return HEDLEY_REINTERPRET_CAST(simde_v4i32, vec_cmplt(a, b));
  #else
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128i = _mm_cmplt_epi32(a_.m128i, b_.m128i);
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_i32x4_lt(a_.v128, b_.v128);
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = HEDLEY_REINTERPRET_CAST(__typeof__(r_.values), a_.values < b_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] < b_.values[i]) ? -1 : 0;
      }
    #endif

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_clt_s_w
  #define __msa_clt_s_w(a, b) simde_msa_clt_s_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_clt_s_d(simde_v2i64 a, simde_v2i64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_clt_s_d(a, b);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vreinterpretq_s64_u64(vcltq_s64(a, b));
  #elif defined(SIMDE_POWER_ALTIVEC_P8_NATIVE)
    return HEDLEY_REINTERPRET_CAST(simde_v2i64, vec_cmplt(a, b));
  #else
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      b_ = simde_v2i64_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE4_2_NATIVE)
      r_.m128i = _mm_cmpgt_epi64(b_.m128i, a_.m128i);
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_i64x2_lt(a_.v128, b_.v128);
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = HEDLEY_REINTERPRET_CAST(__typeof__(r_.values), a_.values < b_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] < b_.values[i]) ? -1 : 0;
      }
    #endif

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_clt_s_d
  #define __msa_clt_s_d(a, b) simde_msa_clt_s_d((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v16u8
simde_msa_clt_u_b(simde_v16u8 a, simde_v16u8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_clt_u_b(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vcltq_u8(a, b);
  #elif defined(SIMDE_POWER_ALTIVEC_P6_NATIVE)
    return HEDLEY_REINTERPRET_CAST(simde_v16u8, vec_cmplt(a, b));
  #else
    simde_v16u8_private
      a_ = simde_v16u8_to_private(a),
      b_ = simde_v16u8_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128i = _mm_andnot_si128(_mm_cmpeq_epi8(a_.m128i, b_.m128i), _mm_cmpeq_epi8(_mm_min_epu8(a_.m128i, b_.m128i), a_.m128i));
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_i8x16_lt_u(a_.v128, b_.v128);
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = HEDLEY_REINTERPRET_CAST(__typeof__(r_.values), a_.values < b_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] < b_.values[i]) ? uint8_t(0xFF) : 0;
      }
    #endif

    return simde_v16u8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_clt_u_b
  #define __msa_clt_u_b(a, b) simde_msa_clt_u_b((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8u16
simde_msa_clt_u_h(simde_v8u16 a, simde_v8u16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_clt_u_h(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vcltq_u16(a, b);
  #elif defined(SIMDE_POWER_ALTIVEC_P6_NATIVE)
    return HEDLEY_REINTERPRET_CAST(simde_v8u16, vec_cmplt(a, b));
  #else
    simde_v8u16_private
      a_ = simde_v8u16_to_private(a),
      b_ = simde_v8u16_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE4_1_NATIVE)
      r_.m128i = _mm_andnot_si128(_mm_cmpeq_epi16(a_.m128i, b_.m128i), _mm_cmpeq_epi16(_mm_min_epu16(a_.m128i, b_.m128i), a_.m128i));
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_i16x8_lt_u(a_.v128, b_.v128);
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = HEDLEY_REINTERPRET_CAST(__typeof__(r_.values), a_.values < b_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] < b_.values[i]) ? uint16_t(0xFFFF) : 0;
      }
    #endif

    return simde_v8u16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_clt_u_h
  #define __msa_clt_u_h(a, b) simde_msa_clt_u_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4u32
simde_msa_clt_u_w(simde_v4u32 a, simde_v4u32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_clt_u_w(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vcltq_u32(a, b);
  #elif defined(SIMDE_POWER_ALTIVEC_P6_NATIVE)
    return HEDLEY_REINTERPRET_CAST(simde_v4u32, vec_cmplt(a, b));
  #else
    simde_v4u32_private
      a_ = simde_v4u32_to_private(a),
      b_ = simde_v4u32_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE4_1_NATIVE)
      r_.m128i = _mm_andnot_si128(_mm_cmpeq_epi32(a_.m128i, b_.m128i), _mm_cmpeq_epi32(_mm_min_epu32(a_.m128i, b_.m128i), a_.m128i));
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_i32x4_lt_u(a_.v128, b_.v128);
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = HEDLEY_REINTERPRET_CAST(__typeof__(r_.values), a_.values < b_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] < b_.values[i]) ? uint32_t(0xFFFFFFFF) : 0;
      }
    #endif

    return simde_v4u32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_clt_u_w
  #define __msa_clt_u_w(a, b) simde_msa_clt_u_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2u64
simde_msa_clt_u_d(simde_v2u64 a, simde_v2u64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_clt_u_d(a, b);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vcltq_u64(a, b);
  #elif defined(SIMDE_POWER_ALTIVEC_P8_NATIVE)
    return HEDLEY_REINTERPRET_CAST(simde_v2u64, vec_cmplt(a, b));
  #else
    simde_v2u64_private
      a_ = simde_v2u64_to_private(a),
      b_ = simde_v2u64_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = HEDLEY_REINTERPRET_CAST(__typeof__(r_.values), a_.values < b_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] < b_.values[i]) ? uint64_t(0xFFFFFFFFFFFFFFFF) : 0;
      }
    #endif

    return simde_v2u64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_clt_u_d
  #define __msa_clt_u_d(a, b) simde_msa_clt_u_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
