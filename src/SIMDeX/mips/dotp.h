#if !defined(SIMDE_MIPS_MSA_DOTP_H)
#define SIMDE_MIPS_MSA_DOTP_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_dotp_s_h(simde_v16i8 a, simde_v16i8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_dotp_s_h(a, b);
  #else
    simde_v8i16_private r_;
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      b_ = simde_v16i8_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] =
        (HEDLEY_STATIC_CAST(int16_t, a_.values[i * 2]) * HEDLEY_STATIC_CAST(int16_t, b_.values[i * 2])) +
        (HEDLEY_STATIC_CAST(int16_t, a_.values[(i * 2) + 1]) * HEDLEY_STATIC_CAST(int16_t, b_.values[(i * 2) + 1]));
    }

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_dotp_s_h
  #define __msa_dotp_s_h(a, b) simde_msa_dotp_s_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_dotp_s_w(simde_v8i16 a, simde_v8i16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_dotp_s_w(a, b);
  #else
    simde_v4i32_private r_;
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b);

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128i = _mm_madd_epi16(a_.m128i, b_.m128i);
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_i32x4_dot_i16x8_s(a_.v128, b_.v128);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] =
          (HEDLEY_STATIC_CAST(int32_t, a_.values[i * 2]) * HEDLEY_STATIC_CAST(int32_t, b_.values[i * 2])) +
          (HEDLEY_STATIC_CAST(int32_t, a_.values[(i * 2) + 1]) * HEDLEY_STATIC_CAST(int32_t, b_.values[(i * 2) + 1]));
      }
    #endif

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_dotp_s_w
  #define __msa_dotp_s_w(a, b) simde_msa_dotp_s_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_dotp_s_d(simde_v4i32 a, simde_v4i32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_dotp_s_d(a, b);
  #else
    simde_v2i64_private r_;
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] =
        (HEDLEY_STATIC_CAST(int64_t, a_.values[i * 2]) * HEDLEY_STATIC_CAST(int64_t, b_.values[i * 2])) +
        (HEDLEY_STATIC_CAST(int64_t, a_.values[(i * 2) + 1]) * HEDLEY_STATIC_CAST(int64_t, b_.values[(i * 2) + 1]));
    }

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_dotp_s_d
  #define __msa_dotp_s_d(a, b) simde_msa_dotp_s_d((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8u16
simde_msa_dotp_u_h(simde_v16u8 a, simde_v16u8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_dotp_u_h(a, b);
  #else
    simde_v8u16_private r_;
    simde_v16u8_private
      a_ = simde_v16u8_to_private(a),
      b_ = simde_v16u8_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] =
        (HEDLEY_STATIC_CAST(uint16_t, a_.values[i * 2]) * HEDLEY_STATIC_CAST(uint16_t, b_.values[i * 2])) +
        (HEDLEY_STATIC_CAST(uint16_t, a_.values[(i * 2) + 1]) * HEDLEY_STATIC_CAST(uint16_t, b_.values[(i * 2) + 1]));
    }

    return simde_v8u16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_dotp_u_h
  #define __msa_dotp_u_h(a, b) simde_msa_dotp_u_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4u32
simde_msa_dotp_u_w(simde_v8u16 a, simde_v8u16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_dotp_u_w(a, b);
  #else
    simde_v4u32_private r_;
    simde_v8u16_private
      a_ = simde_v8u16_to_private(a),
      b_ = simde_v8u16_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] =
        (HEDLEY_STATIC_CAST(uint32_t, a_.values[i * 2]) * HEDLEY_STATIC_CAST(uint32_t, b_.values[i * 2])) +
        (HEDLEY_STATIC_CAST(uint32_t, a_.values[(i * 2) + 1]) * HEDLEY_STATIC_CAST(uint32_t, b_.values[(i * 2) + 1]));
    }

    return simde_v4u32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_dotp_u_w
  #define __msa_dotp_u_w(a, b) simde_msa_dotp_u_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2u64
simde_msa_dotp_u_d(simde_v4u32 a, simde_v4u32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_dotp_u_d(a, b);
  #else
    simde_v2u64_private r_;
    simde_v4u32_private
      a_ = simde_v4u32_to_private(a),
      b_ = simde_v4u32_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] =
        (HEDLEY_STATIC_CAST(uint64_t, a_.values[i * 2]) * HEDLEY_STATIC_CAST(uint64_t, b_.values[i * 2])) +
        (HEDLEY_STATIC_CAST(uint64_t, a_.values[(i * 2) + 1]) * HEDLEY_STATIC_CAST(uint64_t, b_.values[(i * 2) + 1]));
    }

    return simde_v2u64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_dotp_u_d
  #define __msa_dotp_u_d(a, b) simde_msa_dotp_u_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
