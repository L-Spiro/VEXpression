#if !defined(SIMDE_MIPS_MSA_SUBSUS_H)
#define SIMDE_MIPS_MSA_SUBSUS_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16u8
simde_msa_subsus_u_b(simde_v16u8 a, simde_v16i8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_subsus_u_b(a, b);
  #else
    simde_v16u8_private a_ = simde_v16u8_to_private(a);
    simde_v16i8_private b_ = simde_v16i8_to_private(b);
    simde_v16u8_private r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int16_t diff = HEDLEY_STATIC_CAST(int16_t, a_.values[i]) - HEDLEY_STATIC_CAST(int16_t, b_.values[i]);
      r_.values[i] = HEDLEY_STATIC_CAST(uint8_t, (diff > UINT8_MAX) ? UINT8_MAX : ((diff < 0) ? 0 : diff));
    }
    return simde_v16u8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_subsus_u_b
  #define __msa_subsus_u_b(a, b) simde_msa_subsus_u_b((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8u16
simde_msa_subsus_u_h(simde_v8u16 a, simde_v8i16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_subsus_u_h(a, b);
  #else
    simde_v8u16_private a_ = simde_v8u16_to_private(a);
    simde_v8i16_private b_ = simde_v8i16_to_private(b);
    simde_v8u16_private r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int32_t diff = HEDLEY_STATIC_CAST(int32_t, a_.values[i]) - HEDLEY_STATIC_CAST(int32_t, b_.values[i]);
      r_.values[i] = HEDLEY_STATIC_CAST(uint16_t, (diff > UINT16_MAX) ? UINT16_MAX : ((diff < 0) ? 0 : diff));
    }
    return simde_v8u16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_subsus_u_h
  #define __msa_subsus_u_h(a, b) simde_msa_subsus_u_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4u32
simde_msa_subsus_u_w(simde_v4u32 a, simde_v4i32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_subsus_u_w(a, b);
  #else
    simde_v4u32_private a_ = simde_v4u32_to_private(a);
    simde_v4i32_private b_ = simde_v4i32_to_private(b);
    simde_v4u32_private r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int64_t diff = HEDLEY_STATIC_CAST(int64_t, a_.values[i]) - HEDLEY_STATIC_CAST(int64_t, b_.values[i]);
      r_.values[i] = HEDLEY_STATIC_CAST(uint32_t, (diff > UINT32_MAX) ? UINT32_MAX : ((diff < 0) ? 0 : diff));
    }
    return simde_v4u32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_subsus_u_w
  #define __msa_subsus_u_w(a, b) simde_msa_subsus_u_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2u64
simde_msa_subsus_u_d(simde_v2u64 a, simde_v2i64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_subsus_u_d(a, b);
  #else
    simde_v2u64_private a_ = simde_v2u64_to_private(a);
    simde_v2i64_private b_ = simde_v2i64_to_private(b);
    simde_v2u64_private r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      if (b_.values[i] < 0) {
        if (a_.values[i] > UINT64_MAX + b_.values[i]) { r_.values[i] = UINT64_MAX; }
        else { r_.values[i] = a_.values[i] - b_.values[i]; }
      } else {
        if (a_.values[i] < HEDLEY_STATIC_CAST(uint64_t, b_.values[i])) { r_.values[i] = 0; }
        else { r_.values[i] = a_.values[i] - b_.values[i]; }
      }
    }
    return simde_v2u64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_subsus_u_d
  #define __msa_subsus_u_d(a, b) simde_msa_subsus_u_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
