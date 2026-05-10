#if !defined(SIMDE_MIPS_MSA_MADDV_H)
#define SIMDE_MIPS_MSA_MADDV_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_maddv_b(simde_v16i8 a, simde_v16i8 b, simde_v16i8 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_maddv_b(a, b, c);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vmlaq_s8(a, b, c);
  #else
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      b_ = simde_v16i8_to_private(b),
      c_ = simde_v16i8_to_private(c),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[i] + (b_.values[i] * c_.values[i]);
    }

    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_maddv_b
  #define __msa_maddv_b(a, b, c) simde_msa_maddv_b((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_maddv_h(simde_v8i16 a, simde_v8i16 b, simde_v8i16 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_maddv_h(a, b, c);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vmlaq_s16(a, b, c);
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_add_epi16(a, _mm_mullo_epi16(b, c));
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i16x8_add(a, wasm_i16x8_mul(b, c));
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b),
      c_ = simde_v8i16_to_private(c),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[i] + (b_.values[i] * c_.values[i]);
    }

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_maddv_h
  #define __msa_maddv_h(a, b, c) simde_msa_maddv_h((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_maddv_w(simde_v4i32 a, simde_v4i32 b, simde_v4i32 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_maddv_w(a, b, c);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vmlaq_s32(a, b, c);
  #elif defined(SIMDE_X86_SSE4_1_NATIVE)
    return _mm_add_epi32(a, _mm_mullo_epi32(b, c));
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i32x4_add(a, wasm_i32x4_mul(b, c));
  #else
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b),
      c_ = simde_v4i32_to_private(c),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[i] + (b_.values[i] * c_.values[i]);
    }

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_maddv_w
  #define __msa_maddv_w(a, b, c) simde_msa_maddv_w((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_maddv_d(simde_v2i64 a, simde_v2i64 b, simde_v2i64 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_maddv_d(a, b, c);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i64x2_add(a, wasm_i64x2_mul(b, c));
  #else
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      b_ = simde_v2i64_to_private(b),
      c_ = simde_v2i64_to_private(c),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[i] + (b_.values[i] * c_.values[i]);
    }

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_maddv_d
  #define __msa_maddv_d(a, b, c) simde_msa_maddv_d((a), (b), (c))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
