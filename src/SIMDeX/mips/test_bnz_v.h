#if !defined(SIMDE_MIPS_MSA_TEST_BNZ_V_H)
#define SIMDE_MIPS_MSA_TEST_BNZ_V_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
int
simde_msa_test_bnz_v(simde_v16u8 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_test_bnz_v(a);
  #else
    simde_v16u8_private a_ = simde_v16u8_to_private(a);
    int result = 0;
    SIMDE_VECTORIZE_REDUCTION(|:result)
    for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
      result |= (a_.values[i] != 0);
    }
    return result ? 1 : 0;
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_test_bnz_v
  #define __msa_test_bnz_v(a) simde_msa_test_bnz_v(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
