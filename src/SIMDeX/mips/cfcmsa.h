#if !defined(SIMDE_MIPS_MSA_CFCMSA_H)
#define SIMDE_MIPS_MSA_CFCMSA_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_cfcmsa(cs) __msa_cfcmsa((cs))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  int32_t
  simde_msa_cfcmsa(const int cs) {
    (void)cs;
    
    /* Hardware control registers (e.g., MSACSR for floating-point 
     * rounding modes and exception flags) are architecture-specific.
     * For the portable software fallback, we safely return 0. */
    return 0;
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_cfcmsa
  #define __msa_cfcmsa(cs) simde_msa_cfcmsa((cs))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
