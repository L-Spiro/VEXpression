#if !defined(SIMDE_MIPS_MSA_BMNZI_H)
#define SIMDE_MIPS_MSA_BMNZI_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_bmnzi_b(a, b, imm) __msa_bmnzi_b((a), (b), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v16u8
  simde_msa_bmnzi_b(simde_v16u8 a, simde_v16u8 b, const int imm) {
    simde_v16u8_private
      a_ = simde_v16u8_to_private(a),
      b_ = simde_v16u8_to_private(b),
      r_;

    const uint8_t mask = HEDLEY_STATIC_CAST(uint8_t, imm);
    const uint8_t inv_mask = HEDLEY_STATIC_CAST(uint8_t, ~mask);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = (b_.values & mask) | (a_.values & inv_mask);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (b_.values[i] & mask) | (a_.values[i] & inv_mask);
      }
    #endif

    return simde_v16u8_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_bmnzi_b
  #define __msa_bmnzi_b(a, b, imm) simde_msa_bmnzi_b((a), (b), (imm))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
