#if !defined(SIMDE_MIPS_MSA_SPLATI_H)
#define SIMDE_MIPS_MSA_SPLATI_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_splati_b(a, imm) __msa_splati_b((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v16i8
  simde_msa_splati_b(simde_v16i8 a, const int imm) {
    simde_v16i8_private a_ = simde_v16i8_to_private(a), r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[imm & 15];
    }
    return simde_v16i8_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_splati_b
  #define __msa_splati_b(a, imm) simde_msa_splati_b((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_splati_h(a, imm) __msa_splati_h((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v8i16
  simde_msa_splati_h(simde_v8i16 a, const int imm) {
    simde_v8i16_private a_ = simde_v8i16_to_private(a), r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[imm & 7];
    }
    return simde_v8i16_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_splati_h
  #define __msa_splati_h(a, imm) simde_msa_splati_h((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_splati_w(a, imm) __msa_splati_w((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v4i32
  simde_msa_splati_w(simde_v4i32 a, const int imm) {
    simde_v4i32_private a_ = simde_v4i32_to_private(a), r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[imm & 3];
    }
    return simde_v4i32_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_splati_w
  #define __msa_splati_w(a, imm) simde_msa_splati_w((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_splati_d(a, imm) __msa_splati_d((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v2i64
  simde_msa_splati_d(simde_v2i64 a, const int imm) {
    simde_v2i64_private a_ = simde_v2i64_to_private(a), r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[imm & 1];
    }
    return simde_v2i64_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_splati_d
  #define __msa_splati_d(a, imm) simde_msa_splati_d((a), (imm))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
