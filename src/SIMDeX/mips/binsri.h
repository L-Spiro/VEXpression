#if !defined(SIMDE_MIPS_MSA_BINSRI_H)
#define SIMDE_MIPS_MSA_BINSRI_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_binsri_b(a, b, imm) __msa_binsri_b((a), (b), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v16u8
  simde_msa_binsri_b(simde_v16u8 a, simde_v16u8 b, const int imm) {
    simde_v16u8_private
      a_ = simde_v16u8_to_private(a),
      b_ = simde_v16u8_to_private(b),
      r_;

    const uint8_t mask = HEDLEY_STATIC_CAST(uint8_t, 0xFF) >> (imm & 7);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = (a_.values & ~mask) | (b_.values & mask);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] & ~mask) | (b_.values[i] & mask);
      }
    #endif

    return simde_v16u8_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_binsri_b
  #define __msa_binsri_b(a, b, imm) simde_msa_binsri_b((a), (b), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_binsri_h(a, b, imm) __msa_binsri_h((a), (b), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v8u16
  simde_msa_binsri_h(simde_v8u16 a, simde_v8u16 b, const int imm) {
    simde_v8u16_private
      a_ = simde_v8u16_to_private(a),
      b_ = simde_v8u16_to_private(b),
      r_;

    const uint16_t mask = HEDLEY_STATIC_CAST(uint16_t, 0xFFFF) >> (imm & 15);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = (a_.values & ~mask) | (b_.values & mask);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] & ~mask) | (b_.values[i] & mask);
      }
    #endif

    return simde_v8u16_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_binsri_h
  #define __msa_binsri_h(a, b, imm) simde_msa_binsri_h((a), (b), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_binsri_w(a, b, imm) __msa_binsri_w((a), (b), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v4u32
  simde_msa_binsri_w(simde_v4u32 a, simde_v4u32 b, const int imm) {
    simde_v4u32_private
      a_ = simde_v4u32_to_private(a),
      b_ = simde_v4u32_to_private(b),
      r_;

    const uint32_t mask = HEDLEY_STATIC_CAST(uint32_t, 0xFFFFFFFF) >> (imm & 31);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = (a_.values & ~mask) | (b_.values & mask);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] & ~mask) | (b_.values[i] & mask);
      }
    #endif

    return simde_v4u32_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_binsri_w
  #define __msa_binsri_w(a, b, imm) simde_msa_binsri_w((a), (b), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_binsri_d(a, b, imm) __msa_binsri_d((a), (b), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v2u64
  simde_msa_binsri_d(simde_v2u64 a, simde_v2u64 b, const int imm) {
    simde_v2u64_private
      a_ = simde_v2u64_to_private(a),
      b_ = simde_v2u64_to_private(b),
      r_;

    const uint64_t mask = ~HEDLEY_STATIC_CAST(uint64_t, 0) >> (imm & 63);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = (a_.values & ~mask) | (b_.values & mask);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] & ~mask) | (b_.values[i] & mask);
      }
    #endif

    return simde_v2u64_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_binsri_d
  #define __msa_binsri_d(a, b, imm) simde_msa_binsri_d((a), (b), (imm))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
