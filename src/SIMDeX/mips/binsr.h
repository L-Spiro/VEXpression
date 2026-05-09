#if !defined(SIMDE_MIPS_MSA_BINSR_H)
#define SIMDE_MIPS_MSA_BINSR_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16u8
simde_msa_binsr_b(simde_v16u8 a, simde_v16u8 b, simde_v16u8 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_binsr_b(a, b, c);
  #else
    simde_v16u8_private
      a_ = simde_v16u8_to_private(a),
      b_ = simde_v16u8_to_private(b),
      c_ = simde_v16u8_to_private(c),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint8_t n = c_.values[i] & 7;
      uint8_t mask = HEDLEY_STATIC_CAST(uint8_t, (1 << n) - 1);
      r_.values[i] = (a_.values[i] & ~mask) | (b_.values[i] & mask);
    }

    return simde_v16u8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_binsr_b
  #define __msa_binsr_b(a, b, c) simde_msa_binsr_b((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8u16
simde_msa_binsr_h(simde_v8u16 a, simde_v8u16 b, simde_v8u16 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_binsr_h(a, b, c);
  #else
    simde_v8u16_private
      a_ = simde_v8u16_to_private(a),
      b_ = simde_v8u16_to_private(b),
      c_ = simde_v8u16_to_private(c),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint16_t n = c_.values[i] & 15;
      uint16_t mask = HEDLEY_STATIC_CAST(uint16_t, (1 << n) - 1);
      r_.values[i] = (a_.values[i] & ~mask) | (b_.values[i] & mask);
    }

    return simde_v8u16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_binsr_h
  #define __msa_binsr_h(a, b, c) simde_msa_binsr_h((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4u32
simde_msa_binsr_w(simde_v4u32 a, simde_v4u32 b, simde_v4u32 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_binsr_w(a, b, c);
  #else
    simde_v4u32_private
      a_ = simde_v4u32_to_private(a),
      b_ = simde_v4u32_to_private(b),
      c_ = simde_v4u32_to_private(c),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint32_t n = c_.values[i] & 31;
      uint32_t mask = (UINT32_C(1) << n) - 1;
      r_.values[i] = (a_.values[i] & ~mask) | (b_.values[i] & mask);
    }

    return simde_v4u32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_binsr_w
  #define __msa_binsr_w(a, b, c) simde_msa_binsr_w((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2u64
simde_msa_binsr_d(simde_v2u64 a, simde_v2u64 b, simde_v2u64 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_binsr_d(a, b, c);
  #else
    simde_v2u64_private
      a_ = simde_v2u64_to_private(a),
      b_ = simde_v2u64_to_private(b),
      c_ = simde_v2u64_to_private(c),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint64_t n = c_.values[i] & 63;
      uint64_t mask = (UINT64_C(1) << n) - 1;
      r_.values[i] = (a_.values[i] & ~mask) | (b_.values[i] & mask);
    }

    return simde_v2u64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_binsr_d
  #define __msa_binsr_d(a, b, c) simde_msa_binsr_d((a), (b), (c))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
