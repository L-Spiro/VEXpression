#if !defined(SIMDE_MIPS_MSA_CAST_TO_SCALAR_FLOAT_H)
#define SIMDE_MIPS_MSA_CAST_TO_SCALAR_FLOAT_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_float32
simde_msa_cast_to_scalar_float(simde_v4f32 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_cast_to_scalar_float(a);
  #else
    simde_v4f32_private a_ = simde_v4f32_to_private(a);
    return a_.values[0];
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_cast_to_scalar_float
  #define __msa_cast_to_scalar_float(a) simde_msa_cast_to_scalar_float((a))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
