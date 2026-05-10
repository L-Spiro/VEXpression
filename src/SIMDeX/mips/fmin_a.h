#if !defined(SIMDE_MIPS_MSA_FMIN_A_H)
#define SIMDE_MIPS_MSA_FMIN_A_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4f32
simde_msa_fmin_a_w(simde_v4f32 a, simde_v4f32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fmin_a_w(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vminq_f32(vabsq_f32(a), vabsq_f32(b));
  #else
    simde_v4f32_private
      a_ = simde_v4f32_to_private(a),
      b_ = simde_v4f32_to_private(b),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      float abs_a = simde_math_fabsf(a_.values[i]);
      float abs_b = simde_math_fabsf(b_.values[i]);
      r_.values[i] = (abs_a < abs_b) ? abs_a : abs_b;
    }

    return simde_v4f32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fmin_a_w
  #define __msa_fmin_a_w(a, b) simde_msa_fmin_a_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2f64
simde_msa_fmin_a_d(simde_v2f64 a, simde_v2f64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fmin_a_d(a, b);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vminq_f64(vabsq_f64(a), vabsq_f64(b));
  #else
    simde_v2f64_private
      a_ = simde_v2f64_to_private(a),
      b_ = simde_v2f64_to_private(b),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      double abs_a = simde_math_fabs(a_.values[i]);
      double abs_b = simde_math_fabs(b_.values[i]);
      r_.values[i] = (abs_a < abs_b) ? abs_a : abs_b;
    }

    return simde_v2f64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fmin_a_d
  #define __msa_fmin_a_d(a, b) simde_msa_fmin_a_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
