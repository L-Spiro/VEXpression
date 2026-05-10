#if !defined(SIMDE_MIPS_MSA_VSHF_H)
#define SIMDE_MIPS_MSA_VSHF_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_vshf_b(simde_v16i8 mask, simde_v16i8 a, simde_v16i8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_vshf_b(mask, a, b);
  #else
    simde_v16i8_private
      mask_ = simde_v16i8_to_private(mask),
      a_ = simde_v16i8_to_private(a),
      b_ = simde_v16i8_to_private(b),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint8_t idx = mask_.values[i] & 31;
      r_.values[i] = (idx < 16) ? a_.values[idx] : b_.values[idx - 16];
    }

    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_vshf_b
  #define __msa_vshf_b(mask, a, b) simde_msa_vshf_b((mask), (a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_vshf_h(simde_v8i16 mask, simde_v8i16 a, simde_v8i16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_vshf_h(mask, a, b);
  #else
    simde_v8i16_private
      mask_ = simde_v8i16_to_private(mask),
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint8_t idx = mask_.values[i] & 15;
      r_.values[i] = (idx < 8) ? a_.values[idx] : b_.values[idx - 8];
    }

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_vshf_h
  #define __msa_vshf_h(mask, a, b) simde_msa_vshf_h((mask), (a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_vshf_w(simde_v4i32 mask, simde_v4i32 a, simde_v4i32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_vshf_w(mask, a, b);
  #else
    simde_v4i32_private
      mask_ = simde_v4i32_to_private(mask),
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint8_t idx = mask_.values[i] & 7;
      r_.values[i] = (idx < 4) ? a_.values[idx] : b_.values[idx - 4];
    }

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_vshf_w
  #define __msa_vshf_w(mask, a, b) simde_msa_vshf_w((mask), (a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_vshf_d(simde_v2i64 mask, simde_v2i64 a, simde_v2i64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_vshf_d(mask, a, b);
  #else
    simde_v2i64_private
      mask_ = simde_v2i64_to_private(mask),
      a_ = simde_v2i64_to_private(a),
      b_ = simde_v2i64_to_private(b),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint8_t idx = mask_.values[i] & 3;
      r_.values[i] = (idx < 2) ? a_.values[idx] : b_.values[idx - 2];
    }

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_vshf_d
  #define __msa_vshf_d(mask, a, b) simde_msa_vshf_d((mask), (a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
