#if !defined(SIMDE_MIPS_MSA_BINSLI_H)
#define SIMDE_MIPS_MSA_BINSLI_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_binsli_b(a, b, imm) __msa_binsli_b((a), (b), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v16u8
  simde_msa_binsli_b(simde_v16u8 a, simde_v16u8 b, const int imm) {
    simde_v16u8_private
      a_ = simde_v16u8_to_private(a),
      b_ = simde_v16u8_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      const uint8_t mask = HEDLEY_STATIC_CAST(uint8_t, UINT8_MAX << (7 - imm));
      r_.values = (a_.values & ~mask) | (b_.values & mask);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        uint8_t mask = HEDLEY_STATIC_CAST(uint8_t, UINT8_MAX << (7 - imm));
        r_.values[i] = (a_.values[i] & ~mask) | (b_.values[i] & mask);
      }
    #endif

    return simde_v16u8_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_binsli_b
  #define __msa_binsli_b(a, b, imm) simde_msa_binsli_b((a), (b), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_binsli_h(a, b, imm) __msa_binsli_h((a), (b), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v8u16
  simde_msa_binsli_h(simde_v8u16 a, simde_v8u16 b, const int imm) {
    simde_v8u16_private
      a_ = simde_v8u16_to_private(a),
      b_ = simde_v8u16_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      const uint16_t mask = HEDLEY_STATIC_CAST(uint16_t, UINT16_MAX << (15 - imm));
      r_.values = (a_.values & ~mask) | (b_.values & mask);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        uint16_t mask = HEDLEY_STATIC_CAST(uint16_t, UINT16_MAX << (15 - imm));
        r_.values[i] = (a_.values[i] & ~mask) | (b_.values[i] & mask);
      }
    #endif

    return simde_v8u16_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_binsli_h
  #define __msa_binsli_h(a, b, imm) simde_msa_binsli_h((a), (b), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_binsli_w(a, b, imm) __msa_binsli_w((a), (b), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v4u32
  simde_msa_binsli_w(simde_v4u32 a, simde_v4u32 b, const int imm) {
    simde_v4u32_private
      a_ = simde_v4u32_to_private(a),
      b_ = simde_v4u32_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      const uint32_t mask = HEDLEY_STATIC_CAST(uint32_t, UINT32_MAX << (31 - imm));
      r_.values = (a_.values & ~mask) | (b_.values & mask);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        uint32_t mask = HEDLEY_STATIC_CAST(uint32_t, UINT32_MAX << (31 - imm));
        r_.values[i] = (a_.values[i] & ~mask) | (b_.values[i] & mask);
      }
    #endif

    return simde_v4u32_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_binsli_w
  #define __msa_binsli_w(a, b, imm) simde_msa_binsli_w((a), (b), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_binsli_d(a, b, imm) __msa_binsli_d((a), (b), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v2u64
  simde_msa_binsli_d(simde_v2u64 a, simde_v2u64 b, const int imm) {
    simde_v2u64_private
      a_ = simde_v2u64_to_private(a),
      b_ = simde_v2u64_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      const uint64_t mask = HEDLEY_STATIC_CAST(uint64_t, UINT64_MAX << (63 - imm));
      r_.values = (a_.values & ~mask) | (b_.values & mask);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        uint64_t mask = HEDLEY_STATIC_CAST(uint64_t, UINT64_MAX << (63 - imm));
        r_.values[i] = (a_.values[i] & ~mask) | (b_.values[i] & mask);
      }
    #endif

    return simde_v2u64_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_binsli_d
  #define __msa_binsli_d(a, b, imm) simde_msa_binsli_d((a), (b), (imm))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
