#if !defined(SIMDE_MIPS_MSA_SUBS_H)
#define SIMDE_MIPS_MSA_SUBS_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_subs_s_b(simde_v16i8 a, simde_v16i8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_subs_s_b(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqsubq_s8(a, b);
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_subs_epi8(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i8x16_sub_sat(a, b);
  #else
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      b_ = simde_v16i8_to_private(b),
      r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int16_t diff = HEDLEY_STATIC_CAST(int16_t, a_.values[i]) - HEDLEY_STATIC_CAST(int16_t, b_.values[i]);
      r_.values[i] = HEDLEY_STATIC_CAST(int8_t, (diff > INT8_MAX) ? INT8_MAX : ((diff < INT8_MIN) ? INT8_MIN : diff));
    }
    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_subs_s_b
  #define __msa_subs_s_b(a, b) simde_msa_subs_s_b((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_subs_s_h(simde_v8i16 a, simde_v8i16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_subs_s_h(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqsubq_s16(a, b);
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_subs_epi16(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i16x8_sub_sat(a, b);
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b),
      r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int32_t diff = HEDLEY_STATIC_CAST(int32_t, a_.values[i]) - HEDLEY_STATIC_CAST(int32_t, b_.values[i]);
      r_.values[i] = HEDLEY_STATIC_CAST(int16_t, (diff > INT16_MAX) ? INT16_MAX : ((diff < INT16_MIN) ? INT16_MIN : diff));
    }
    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_subs_s_h
  #define __msa_subs_s_h(a, b) simde_msa_subs_s_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_subs_s_w(simde_v4i32 a, simde_v4i32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_subs_s_w(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqsubq_s32(a, b);
  #else
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b),
      r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int64_t diff = HEDLEY_STATIC_CAST(int64_t, a_.values[i]) - HEDLEY_STATIC_CAST(int64_t, b_.values[i]);
      r_.values[i] = HEDLEY_STATIC_CAST(int32_t, (diff > INT32_MAX) ? INT32_MAX : ((diff < INT32_MIN) ? INT32_MIN : diff));
    }
    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_subs_s_w
  #define __msa_subs_s_w(a, b) simde_msa_subs_s_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_subs_s_d(simde_v2i64 a, simde_v2i64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_subs_s_d(a, b);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vqsubq_s64(a, b);
  #else
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      b_ = simde_v2i64_to_private(b),
      r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      /* Safe saturation avoiding 128-bit ints */
      if (a_.values[i] >= 0 && b_.values[i] < 0 && a_.values[i] > INT64_MAX + b_.values[i]) {
        r_.values[i] = INT64_MAX;
      } else if (a_.values[i] < 0 && b_.values[i] > 0 && a_.values[i] < INT64_MIN + b_.values[i]) {
        r_.values[i] = INT64_MIN;
      } else {
        r_.values[i] = a_.values[i] - b_.values[i];
      }
    }
    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_subs_s_d
  #define __msa_subs_s_d(a, b) simde_msa_subs_s_d((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v16u8
simde_msa_subs_u_b(simde_v16u8 a, simde_v16u8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_subs_u_b(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqsubq_u8(a, b);
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_subs_epu8(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i8x16_sub_sat_u(a, b);
  #else
    simde_v16u8_private
      a_ = simde_v16u8_to_private(a),
      b_ = simde_v16u8_to_private(b),
      r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] > b_.values[i]) ? (a_.values[i] - b_.values[i]) : 0;
    }
    return simde_v16u8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_subs_u_b
  #define __msa_subs_u_b(a, b) simde_msa_subs_u_b((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8u16
simde_msa_subs_u_h(simde_v8u16 a, simde_v8u16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_subs_u_h(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqsubq_u16(a, b);
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_subs_epu16(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i16x8_sub_sat_u(a, b);
  #else
    simde_v8u16_private
      a_ = simde_v8u16_to_private(a),
      b_ = simde_v8u16_to_private(b),
      r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] > b_.values[i]) ? (a_.values[i] - b_.values[i]) : 0;
    }
    return simde_v8u16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_subs_u_h
  #define __msa_subs_u_h(a, b) simde_msa_subs_u_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4u32
simde_msa_subs_u_w(simde_v4u32 a, simde_v4u32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_subs_u_w(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqsubq_u32(a, b);
  #else
    simde_v4u32_private
      a_ = simde_v4u32_to_private(a),
      b_ = simde_v4u32_to_private(b),
      r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] > b_.values[i]) ? (a_.values[i] - b_.values[i]) : 0;
    }
    return simde_v4u32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_subs_u_w
  #define __msa_subs_u_w(a, b) simde_msa_subs_u_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2u64
simde_msa_subs_u_d(simde_v2u64 a, simde_v2u64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_subs_u_d(a, b);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vqsubq_u64(a, b);
  #else
    simde_v2u64_private
      a_ = simde_v2u64_to_private(a),
      b_ = simde_v2u64_to_private(b),
      r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] > b_.values[i]) ? (a_.values[i] - b_.values[i]) : 0;
    }
    return simde_v2u64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_subs_u_d
  #define __msa_subs_u_d(a, b) simde_msa_subs_u_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
