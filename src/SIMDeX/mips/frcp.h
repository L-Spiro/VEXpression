#if !defined(SIMDE_MIPS_MSA_FRCP_H)
#define SIMDE_MIPS_MSA_FRCP_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4f32
simde_msa_frcp_w(simde_v4f32 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_frcp_w(a);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vrecpeq_f32(a);
  #else
    simde_v4f32_private
      a_ = simde_v4f32_to_private(a),
      r_;

    #if defined(SIMDE_X86_SSE_NATIVE)
      r_.m128 = _mm_rcp_ps(a_.m128);
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = 1.0f / a_.values;
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = 1.0f / a_.values[i];
      }
    #endif

    return simde_v4f32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_frcp_w
  #define __msa_frcp_w(a) simde_msa_frcp_w(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2f64
simde_msa_frcp_d(simde_v2f64 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_frcp_d(a);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vrecpeq_f64(a);
  #else
    simde_v2f64_private
      a_ = simde_v2f64_to_private(a),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = 1.0 / a_.values;
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = 1.0 / a_.values[i];
      }
    #endif

    return simde_v2f64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_frcp_d
  #define __msa_frcp_d(a) simde_msa_frcp_d(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
