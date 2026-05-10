#if !defined(SIMDE_MIPS_MSA_SUBSUU_H)
#define SIMDE_MIPS_MSA_SUBSUU_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_subsuu_s_b(simde_v16u8 a, simde_v16u8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_subsuu_s_b(a, b);
  #else
    simde_v16u8_private a_ = simde_v16u8_to_private(a);
    simde_v16u8_private b_ = simde_v16u8_to_private(b);
    simde_v16i8_private r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int16_t diff = HEDLEY_STATIC_CAST(int16_t, a_.values[i]) - HEDLEY_STATIC_CAST(int16_t, b_.values[i]);
      r_.values[i] = HEDLEY_STATIC_CAST(int8_t, (diff > INT8_MAX) ? INT8_MAX : ((diff < INT8_MIN) ? INT8_MIN : diff));
    }
    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_subsuu_s_b
  #define __msa_subsuu_s_b(a, b) simde_msa_subsuu_s_b((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_subsuu_s_h(simde_v8u16 a, simde_v8u16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_subsuu_s_h(a, b);
  #else
    simde_v8u16_private a_ = simde_v8u16_to_private(a);
    simde_v8u16_private b_ = simde_v8u16_to_private(b);
    simde_v8i16_private r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int32_t diff = HEDLEY_STATIC_CAST(int32_t, a_.values[i]) - HEDLEY_STATIC_CAST(int32_t, b_.values[i]);
      r_.values[i] = HEDLEY_STATIC_CAST(int16_t, (diff > INT16_MAX) ? INT16_MAX : ((diff < INT16_MIN) ? INT16_MIN : diff));
    }
    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_subsuu_s_h
  #define __msa_subsuu_s_h(a, b) simde_msa_subsuu_s_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_subsuu_s_w(simde_v4u32 a, simde_v4u32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_subsuu_s_w(a, b);
  #else
    simde_v4u32_private a_ = simde_v4u32_to_private(a);
    simde_v4u32_private b_ = simde_v4u32_to_private(b);
    simde_v4i32_private r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int64_t diff = HEDLEY_STATIC_CAST(int64_t, a_.values[i]) - HEDLEY_STATIC_CAST(int64_t, b_.values[i]);
      r_.values[i] = HEDLEY_STATIC_CAST(int32_t, (diff > INT32_MAX) ? INT32_MAX : ((diff < INT32_MIN) ? INT32_MIN : diff));
    }
    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_subsuu_s_w
  #define __msa_subsuu_s_w(a, b) simde_msa_subsuu_s_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_subsuu_s_d(simde_v2u64 a, simde_v2u64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_subsuu_s_d(a, b);
  #else
    simde_v2u64_private a_ = simde_v2u64_to_private(a);
    simde_v2u64_private b_ = simde_v2u64_to_private(b);
    simde_v2i64_private r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      if (a_.values[i] >= b_.values[i]) {
        uint64_t diff = a_.values[i] - b_.values[i];
        r_.values[i] = (diff > INT64_MAX) ? INT64_MAX : HEDLEY_STATIC_CAST(int64_t, diff);
      } else {
        uint64_t diff = b_.values[i] - a_.values[i];
        r_.values[i] = (diff > (HEDLEY_STATIC_CAST(uint64_t, INT64_MAX) + 1)) ? INT64_MIN : -HEDLEY_STATIC_CAST(int64_t, diff);
      }
    }
    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_subsuu_s_d
  #define __msa_subsuu_s_d(a, b) simde_msa_subsuu_s_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
