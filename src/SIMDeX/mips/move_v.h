#if !defined(SIMDE_MIPS_MSA_MOVE_V_H)
#define SIMDE_MIPS_MSA_MOVE_V_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16u8 simde_msa_move_v(simde_v16u8 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_move_v(a);
  #else
    return a;
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_move_v
  #define __msa_move_v(a) simde_msa_move_v(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
