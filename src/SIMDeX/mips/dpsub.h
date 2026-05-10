#if !defined(SIMDE_MIPS_MSA_DPSUB_H)
#define SIMDE_MIPS_MSA_DPSUB_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_dpsub_s_h(simde_v8i16 a, simde_v16i8 b, simde_v16i8 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_dpsub_s_h(a, b, c);
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      r_;
    simde_v16i8_private
      b_ = simde_v16i8_to_private(b),
      c_ = simde_v16i8_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[i] - (
        (HEDLEY_STATIC_CAST(int16_t, b_.values[2 * i]) * HEDLEY_STATIC_CAST(int16_t, c_.values[2 * i])) +
        (HEDLEY_STATIC_CAST(int16_t, b_.values[(2 * i) + 1]) * HEDLEY_STATIC_CAST(int16_t, c_.values[(2 * i) + 1]))
      );
    }

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_dpsub_s_h
  #define __msa_dpsub_s_h(a, b, c) simde_msa_dpsub_s_h((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_dpsub_s_w(simde_v4i32 a, simde_v8i16 b, simde_v8i16 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_dpsub_s_w(a, b, c);
  #else
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      r_;
    simde_v8i16_private
      b_ = simde_v8i16_to_private(b),
      c_ = simde_v8i16_to_private(c);

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128i = _mm_sub_epi32(a_.m128i, _mm_madd_epi16(b_.m128i, c_.m128i));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = a_.values[i] - (
          (HEDLEY_STATIC_CAST(int32_t, b_.values[2 * i]) * HEDLEY_STATIC_CAST(int32_t, c_.values[2 * i])) +
          (HEDLEY_STATIC_CAST(int32_t, b_.values[(2 * i) + 1]) * HEDLEY_STATIC_CAST(int32_t, c_.values[(2 * i) + 1]))
        );
      }
    #endif

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_dpsub_s_w
  #define __msa_dpsub_s_w(a, b, c) simde_msa_dpsub_s_w((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_dpsub_s_d(simde_v2i64 a, simde_v4i32 b, simde_v4i32 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_dpsub_s_d(a, b, c);
  #else
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      r_;
    simde_v4i32_private
      b_ = simde_v4i32_to_private(b),
      c_ = simde_v4i32_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[i] - (
        (HEDLEY_STATIC_CAST(int64_t, b_.values[2 * i]) * HEDLEY_STATIC_CAST(int64_t, c_.values[2 * i])) +
        (HEDLEY_STATIC_CAST(int64_t, b_.values[(2 * i) + 1]) * HEDLEY_STATIC_CAST(int64_t, c_.values[(2 * i) + 1]))
      );
    }

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_dpsub_s_d
  #define __msa_dpsub_s_d(a, b, c) simde_msa_dpsub_s_d((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8u16
simde_msa_dpsub_u_h(simde_v8u16 a, simde_v16u8 b, simde_v16u8 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_dpsub_u_h(a, b, c);
  #else
    simde_v8u16_private
      a_ = simde_v8u16_to_private(a),
      r_;
    simde_v16u8_private
      b_ = simde_v16u8_to_private(b),
      c_ = simde_v16u8_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[i] - (
        (HEDLEY_STATIC_CAST(uint16_t, b_.values[2 * i]) * HEDLEY_STATIC_CAST(uint16_t, c_.values[2 * i])) +
        (HEDLEY_STATIC_CAST(uint16_t, b_.values[(2 * i) + 1]) * HEDLEY_STATIC_CAST(uint16_t, c_.values[(2 * i) + 1]))
      );
    }

    return simde_v8u16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_dpsub_u_h
  #define __msa_dpsub_u_h(a, b, c) simde_msa_dpsub_u_h((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4u32
simde_msa_dpsub_u_w(simde_v4u32 a, simde_v8u16 b, simde_v8u16 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_dpsub_u_w(a, b, c);
  #else
    simde_v4u32_private
      a_ = simde_v4u32_to_private(a),
      r_;
    simde_v8u16_private
      b_ = simde_v8u16_to_private(b),
      c_ = simde_v8u16_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[i] - (
        (HEDLEY_STATIC_CAST(uint32_t, b_.values[2 * i]) * HEDLEY_STATIC_CAST(uint32_t, c_.values[2 * i])) +
        (HEDLEY_STATIC_CAST(uint32_t, b_.values[(2 * i) + 1]) * HEDLEY_STATIC_CAST(uint32_t, c_.values[(2 * i) + 1]))
      );
    }

    return simde_v4u32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_dpsub_u_w
  #define __msa_dpsub_u_w(a, b, c) simde_msa_dpsub_u_w((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2u64
simde_msa_dpsub_u_d(simde_v2u64 a, simde_v4u32 b, simde_v4u32 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_dpsub_u_d(a, b, c);
  #else
    simde_v2u64_private
      a_ = simde_v2u64_to_private(a),
      r_;
    simde_v4u32_private
      b_ = simde_v4u32_to_private(b),
      c_ = simde_v4u32_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[i] - (
        (HEDLEY_STATIC_CAST(uint64_t, b_.values[2 * i]) * HEDLEY_STATIC_CAST(uint64_t, c_.values[2 * i])) +
        (HEDLEY_STATIC_CAST(uint64_t, b_.values[(2 * i) + 1]) * HEDLEY_STATIC_CAST(uint64_t, c_.values[(2 * i) + 1]))
      );
    }

    return simde_v2u64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_dpsub_u_d
  #define __msa_dpsub_u_d(a, b, c) simde_msa_dpsub_u_d((a), (b), (c))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
