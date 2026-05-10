#if !defined(SIMDE_MIPS_MSA_LDI_H)
#define SIMDE_MIPS_MSA_LDI_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_ldi_b(imm) __msa_ldi_b(imm)
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v16i8 simde_msa_ldi_b(const int imm) {
    simde_v16i8_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(int8_t, imm);
    }

    return simde_v16i8_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ldi_b
  #define __msa_ldi_b(imm) simde_msa_ldi_b(imm)
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_ldi_h(imm) __msa_ldi_h(imm)
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v8i16 simde_msa_ldi_h(const int imm) {
    simde_v8i16_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(int16_t, imm);
    }

    return simde_v8i16_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ldi_h
  #define __msa_ldi_h(imm) simde_msa_ldi_h(imm)
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_ldi_w(imm) __msa_ldi_w(imm)
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v4i32 simde_msa_ldi_w(const int imm) {
    simde_v4i32_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(int32_t, imm);
    }

    return simde_v4i32_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ldi_w
  #define __msa_ldi_w(imm) simde_msa_ldi_w(imm)
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_ldi_d(imm) __msa_ldi_d(imm)
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v2i64 simde_msa_ldi_d(const int imm) {
    simde_v2i64_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(int64_t, imm);
    }

    return simde_v2i64_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ldi_d
  #define __msa_ldi_d(imm) simde_msa_ldi_d(imm)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
