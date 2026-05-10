#if !defined(SIMDE_MIPS_MSA_INSVE_H)
#define SIMDE_MIPS_MSA_INSVE_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_insve_b(a, imm, b) __msa_insve_b((a), (imm), (b))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v16i8 simde_msa_insve_b(simde_v16i8 a, const int imm, simde_v16i8 b) {
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      b_ = simde_v16i8_to_private(b);
    
    a_.values[imm & 15] = b_.values[0];
    return simde_v16i8_from_private(a_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_insve_b
  #define __msa_insve_b(a, imm, b) simde_msa_insve_b((a), (imm), (b))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_insve_h(a, imm, b) __msa_insve_h((a), (imm), (b))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v8i16 simde_msa_insve_h(simde_v8i16 a, const int imm, simde_v8i16 b) {
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b);
    
    a_.values[imm & 7] = b_.values[0];
    return simde_v8i16_from_private(a_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_insve_h
  #define __msa_insve_h(a, imm, b) simde_msa_insve_h((a), (imm), (b))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_insve_w(a, imm, b) __msa_insve_w((a), (imm), (b))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v4i32 simde_msa_insve_w(simde_v4i32 a, const int imm, simde_v4i32 b) {
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b);
    
    a_.values[imm & 3] = b_.values[0];
    return simde_v4i32_from_private(a_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_insve_w
  #define __msa_insve_w(a, imm, b) simde_msa_insve_w((a), (imm), (b))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_insve_d(a, imm, b) __msa_insve_d((a), (imm), (b))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v2i64 simde_msa_insve_d(simde_v2i64 a, const int imm, simde_v2i64 b) {
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      b_ = simde_v2i64_to_private(b);
    
    a_.values[imm & 1] = b_.values[0];
    return simde_v2i64_from_private(a_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_insve_d
  #define __msa_insve_d(a, imm, b) simde_msa_insve_d((a), (imm), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
