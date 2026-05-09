#if !defined(SIMDE_MIPS_MSA_BCLR_H)
#define SIMDE_MIPS_MSA_BCLR_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16u8
simde_msa_bclr_b(simde_v16u8 a, simde_v16u8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_bclr_b(a, b);
  #else
    simde_v16u8_private
      a_ = simde_v16u8_to_private(a),
      b_ = simde_v16u8_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = a_.values & ~(HEDLEY_STATIC_CAST(__typeof__(r_.values), 1) << (b_.values & 7));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = a_.values[i] & ~(HEDLEY_STATIC_CAST(uint8_t, 1) << (b_.values[i] & 7));
      }
    #endif

    return simde_v16u8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_bclr_b
  #define __msa_bclr_b(a, b) simde_msa_bclr_b((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8u16
simde_msa_bclr_h(simde_v8u16 a, simde_v8u16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_bclr_h(a, b);
  #else
    simde_v8u16_private
      a_ = simde_v8u16_to_private(a),
      b_ = simde_v8u16_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = a_.values & ~(HEDLEY_STATIC_CAST(__typeof__(r_.values), 1) << (b_.values & 15));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = a_.values[i] & ~(HEDLEY_STATIC_CAST(uint16_t, 1) << (b_.values[i] & 15));
      }
    #endif

    return simde_v8u16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_bclr_h
  #define __msa_bclr_h(a, b) simde_msa_bclr_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4u32
simde_msa_bclr_w(simde_v4u32 a, simde_v4u32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_bclr_w(a, b);
  #else
    simde_v4u32_private
      a_ = simde_v4u32_to_private(a),
      b_ = simde_v4u32_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = a_.values & ~(HEDLEY_STATIC_CAST(__typeof__(r_.values), 1) << (b_.values & 31));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = a_.values[i] & ~(HEDLEY_STATIC_CAST(uint32_t, 1) << (b_.values[i] & 31));
      }
    #endif

    return simde_v4u32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_bclr_w
  #define __msa_bclr_w(a, b) simde_msa_bclr_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2u64
simde_msa_bclr_d(simde_v2u64 a, simde_v2u64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_bclr_d(a, b);
  #else
    simde_v2u64_private
      a_ = simde_v2u64_to_private(a),
      b_ = simde_v2u64_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = a_.values & ~(HEDLEY_STATIC_CAST(__typeof__(r_.values), 1) << (b_.values & 63));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = a_.values[i] & ~(HEDLEY_STATIC_CAST(uint64_t, 1) << (b_.values[i] & 63));
      }
    #endif

    return simde_v2u64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_bclr_d
  #define __msa_bclr_d(a, b) simde_msa_bclr_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
