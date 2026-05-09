#if !defined(SIMDE_MIPS_MSA_BSELI_H)
#define SIMDE_MIPS_MSA_BSELI_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_bseli_b(a, b, imm) __msa_bseli_b((a), (b), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v16u8
  simde_msa_bseli_b(simde_v16u8 a, simde_v16u8 b, const int imm) {
    simde_v16u8_private
      a_ = simde_v16u8_to_private(a),
      b_ = simde_v16u8_to_private(b),
      r_;

    /* * MIPS MSA BSELI.B instruction semantics:
     * wd = (ws & ~imm) | (wd & imm)
     * a corresponds to wd, b corresponds to ws.
     */
    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = (a_.values & HEDLEY_STATIC_CAST(uint8_t, imm)) | (b_.values & HEDLEY_STATIC_CAST(uint8_t, ~imm));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] & HEDLEY_STATIC_CAST(uint8_t, imm)) | (b_.values[i] & HEDLEY_STATIC_CAST(uint8_t, ~imm));
      }
    #endif

    return simde_v16u8_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_bseli_b
  #define __msa_bseli_b(a, b, imm) simde_msa_bseli_b((a), (b), (imm))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
