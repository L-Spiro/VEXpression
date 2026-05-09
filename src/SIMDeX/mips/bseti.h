#if !defined(SIMDE_MIPS_MSA_BSETI_H)
#define SIMDE_MIPS_MSA_BSETI_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_bseti_b(a, imm) __msa_bseti_b((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v16u8
  simde_msa_bseti_b(simde_v16u8 a, const int imm) {
    simde_v16u8_private
      a_ = simde_v16u8_to_private(a),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = a_.values | (HEDLEY_STATIC_CAST(uint8_t, 1) << (imm & 7));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = a_.values[i] | (HEDLEY_STATIC_CAST(uint8_t, 1) << (imm & 7));
      }
    #endif

    return simde_v16u8_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_bseti_b
  #define __msa_bseti_b(a, imm) simde_msa_bseti_b((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_bseti_h(a, imm) __msa_bseti_h((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v8u16
  simde_msa_bseti_h(simde_v8u16 a, const int imm) {
    simde_v8u16_private
      a_ = simde_v8u16_to_private(a),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = a_.values | (HEDLEY_STATIC_CAST(uint16_t, 1) << (imm & 15));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = a_.values[i] | (HEDLEY_STATIC_CAST(uint16_t, 1) << (imm & 15));
      }
    #endif

    return simde_v8u16_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_bseti_h
  #define __msa_bseti_h(a, imm) simde_msa_bseti_h((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_bseti_w(a, imm) __msa_bseti_w((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v4u32
  simde_msa_bseti_w(simde_v4u32 a, const int imm) {
    simde_v4u32_private
      a_ = simde_v4u32_to_private(a),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = a_.values | (HEDLEY_STATIC_CAST(uint32_t, 1) << (imm & 31));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = a_.values[i] | (HEDLEY_STATIC_CAST(uint32_t, 1) << (imm & 31));
      }
    #endif

    return simde_v4u32_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_bseti_w
  #define __msa_bseti_w(a, imm) simde_msa_bseti_w((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_bseti_d(a, imm) __msa_bseti_d((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v2u64
  simde_msa_bseti_d(simde_v2u64 a, const int imm) {
    simde_v2u64_private
      a_ = simde_v2u64_to_private(a),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = a_.values | (HEDLEY_STATIC_CAST(uint64_t, 1) << (imm & 63));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = a_.values[i] | (HEDLEY_STATIC_CAST(uint64_t, 1) << (imm & 63));
      }
    #endif

    return simde_v2u64_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_bseti_d
  #define __msa_bseti_d(a, imm) simde_msa_bseti_d((a), (imm))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
