#if !defined(SIMDE_MIPS_MSA_SHF_H)
#define SIMDE_MIPS_MSA_SHF_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_shf_b(a, imm) __msa_shf_b((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v16i8
  simde_msa_shf_b(simde_v16i8 a, const int imm) {
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i += 4) {
      r_.values[i + 0] = a_.values[i + ((imm >> 0) & 3)];
      r_.values[i + 1] = a_.values[i + ((imm >> 2) & 3)];
      r_.values[i + 2] = a_.values[i + ((imm >> 4) & 3)];
      r_.values[i + 3] = a_.values[i + ((imm >> 6) & 3)];
    }

    return simde_v16i8_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_shf_b
  #define __msa_shf_b(a, imm) simde_msa_shf_b((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_shf_h(a, imm) __msa_shf_h((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v8i16
  simde_msa_shf_h(simde_v8i16 a, const int imm) {
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i += 4) {
      r_.values[i + 0] = a_.values[i + ((imm >> 0) & 3)];
      r_.values[i + 1] = a_.values[i + ((imm >> 2) & 3)];
      r_.values[i + 2] = a_.values[i + ((imm >> 4) & 3)];
      r_.values[i + 3] = a_.values[i + ((imm >> 6) & 3)];
    }

    return simde_v8i16_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_shf_h
  #define __msa_shf_h(a, imm) simde_msa_shf_h((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_shf_w(a, imm) __msa_shf_w((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v4i32
  simde_msa_shf_w(simde_v4i32 a, const int imm) {
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i += 4) {
      r_.values[i + 0] = a_.values[i + ((imm >> 0) & 3)];
      r_.values[i + 1] = a_.values[i + ((imm >> 2) & 3)];
      r_.values[i + 2] = a_.values[i + ((imm >> 4) & 3)];
      r_.values[i + 3] = a_.values[i + ((imm >> 6) & 3)];
    }

    return simde_v4i32_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_shf_w
  #define __msa_shf_w(a, imm) simde_msa_shf_w((a), (imm))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
