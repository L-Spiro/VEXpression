#if !defined(SIMDE_MIPS_MSA_AVE_H)
#define SIMDE_MIPS_MSA_AVE_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_ave_s_b(simde_v16i8 a, simde_v16i8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ave_s_b(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vhaddq_s8(a, b);
  #else
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      b_ = simde_v16i8_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = (a_.values & b_.values) + ((a_.values ^ b_.values) >> 1);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] & b_.values[i]) + ((a_.values[i] ^ b_.values[i]) >> 1);
      }
    #endif

    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ave_s_b
  #define __msa_ave_s_b(a, b) simde_msa_ave_s_b((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_ave_s_h(simde_v8i16 a, simde_v8i16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ave_s_h(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vhaddq_s16(a, b);
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128i = _mm_add_epi16(_mm_and_si128(a_.m128i, b_.m128i), _mm_srai_epi16(_mm_xor_si128(a_.m128i, b_.m128i), 1));
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = (a_.values & b_.values) + ((a_.values ^ b_.values) >> 1);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] & b_.values[i]) + ((a_.values[i] ^ b_.values[i]) >> 1);
      }
    #endif

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ave_s_h
  #define __msa_ave_s_h(a, b) simde_msa_ave_s_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_ave_s_w(simde_v4i32 a, simde_v4i32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ave_s_w(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vhaddq_s32(a, b);
  #else
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128i = _mm_add_epi32(_mm_and_si128(a_.m128i, b_.m128i), _mm_srai_epi32(_mm_xor_si128(a_.m128i, b_.m128i), 1));
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = (a_.values & b_.values) + ((a_.values ^ b_.values) >> 1);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] & b_.values[i]) + ((a_.values[i] ^ b_.values[i]) >> 1);
      }
    #endif

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ave_s_w
  #define __msa_ave_s_w(a, b) simde_msa_ave_s_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_ave_s_d(simde_v2i64 a, simde_v2i64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ave_s_d(a, b);
  #else
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      b_ = simde_v2i64_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = (a_.values & b_.values) + ((a_.values ^ b_.values) >> 1);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] & b_.values[i]) + ((a_.values[i] ^ b_.values[i]) >> 1);
      }
    #endif

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ave_s_d
  #define __msa_ave_s_d(a, b) simde_msa_ave_s_d((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v16u8
simde_msa_ave_u_b(simde_v16u8 a, simde_v16u8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ave_u_b(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vhaddq_u8(a, b);
  #else
    simde_v16u8_private
      a_ = simde_v16u8_to_private(a),
      b_ = simde_v16u8_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = (a_.values & b_.values) + ((a_.values ^ b_.values) >> 1);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] & b_.values[i]) + ((a_.values[i] ^ b_.values[i]) >> 1);
      }
    #endif

    return simde_v16u8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ave_u_b
  #define __msa_ave_u_b(a, b) simde_msa_ave_u_b((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8u16
simde_msa_ave_u_h(simde_v8u16 a, simde_v8u16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ave_u_h(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vhaddq_u16(a, b);
  #else
    simde_v8u16_private
      a_ = simde_v8u16_to_private(a),
      b_ = simde_v8u16_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128i = _mm_add_epi16(_mm_and_si128(a_.m128i, b_.m128i), _mm_srli_epi16(_mm_xor_si128(a_.m128i, b_.m128i), 1));
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = (a_.values & b_.values) + ((a_.values ^ b_.values) >> 1);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] & b_.values[i]) + ((a_.values[i] ^ b_.values[i]) >> 1);
      }
    #endif

    return simde_v8u16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ave_u_h
  #define __msa_ave_u_h(a, b) simde_msa_ave_u_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4u32
simde_msa_ave_u_w(simde_v4u32 a, simde_v4u32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ave_u_w(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vhaddq_u32(a, b);
  #else
    simde_v4u32_private
      a_ = simde_v4u32_to_private(a),
      b_ = simde_v4u32_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128i = _mm_add_epi32(_mm_and_si128(a_.m128i, b_.m128i), _mm_srli_epi32(_mm_xor_si128(a_.m128i, b_.m128i), 1));
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = (a_.values & b_.values) + ((a_.values ^ b_.values) >> 1);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] & b_.values[i]) + ((a_.values[i] ^ b_.values[i]) >> 1);
      }
    #endif

    return simde_v4u32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ave_u_w
  #define __msa_ave_u_w(a, b) simde_msa_ave_u_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2u64
simde_msa_ave_u_d(simde_v2u64 a, simde_v2u64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ave_u_d(a, b);
  #else
    simde_v2u64_private
      a_ = simde_v2u64_to_private(a),
      b_ = simde_v2u64_to_private(b),
      r_;

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128i = _mm_add_epi64(_mm_and_si128(a_.m128i, b_.m128i), _mm_srli_epi64(_mm_xor_si128(a_.m128i, b_.m128i), 1));
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = (a_.values & b_.values) + ((a_.values ^ b_.values) >> 1);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] & b_.values[i]) + ((a_.values[i] ^ b_.values[i]) >> 1);
      }
    #endif

    return simde_v2u64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ave_u_d
  #define __msa_ave_u_d(a, b) simde_msa_ave_u_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
