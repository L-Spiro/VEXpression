#if !defined(SIMDE_MIPS_MSA_FTQ_H)
#define SIMDE_MIPS_MSA_FTQ_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_ftq_h(simde_v4f32 a, simde_v4f32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ftq_h(a, b);
  #else
    simde_v4f32_private
      a_ = simde_v4f32_to_private(a),
      b_ = simde_v4f32_to_private(b);
    simde_v8i16_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < 4 ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(int16_t, simde_math_roundf(a_.values[i] * 32768.0f));
      r_.values[i + 4] = HEDLEY_STATIC_CAST(int16_t, simde_math_roundf(b_.values[i] * 32768.0f));
    }

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ftq_h
  #define __msa_ftq_h(a, b) simde_msa_ftq_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_ftq_w(simde_v2f64 a, simde_v2f64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ftq_w(a, b);
  #else
    simde_v2f64_private
      a_ = simde_v2f64_to_private(a),
      b_ = simde_v2f64_to_private(b);
    simde_v4i32_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < 2 ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(int32_t, simde_math_round(a_.values[i] * 2147483648.0));
      r_.values[i + 2] = HEDLEY_STATIC_CAST(int32_t, simde_math_round(b_.values[i] * 2147483648.0));
    }

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ftq_w
  #define __msa_ftq_w(a, b) simde_msa_ftq_w((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
