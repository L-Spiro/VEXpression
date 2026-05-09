#if !defined(SIMDE_MIPS_MSA_CAST_TO_SCALAR_DOUBLE_H)
#define SIMDE_MIPS_MSA_CAST_TO_SCALAR_DOUBLE_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_float64
simde_msa_cast_to_scalar_double(simde_v2f64 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_cast_to_scalar_double(a);
  #else
    simde_v2f64_private a_ = simde_v2f64_to_private(a);
    return a_.values[0];
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_cast_to_scalar_double
  #define __msa_cast_to_scalar_double(a) simde_msa_cast_to_scalar_double((a))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
