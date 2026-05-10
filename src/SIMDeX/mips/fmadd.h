#if !defined(SIMDE_MIPS_MSA_FMADD_H)
#define SIMDE_MIPS_MSA_FMADD_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4f32
simde_msa_fmadd_w(simde_v4f32 a, simde_v4f32 b, simde_v4f32 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fmadd_w(a, b, c);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vmlaq_f32(a, b, c);
  #elif defined(SIMDE_X86_FMA_NATIVE)
    return _mm_fmadd_ps(b, c, a);
  #else
    simde_v4f32_private
      a_ = simde_v4f32_to_private(a),
      b_ = simde_v4f32_to_private(b),
      c_ = simde_v4f32_to_private(c),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[i] + (b_.values[i] * c_.values[i]);
    }

    return simde_v4f32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fmadd_w
  #define __msa_fmadd_w(a, b, c) simde_msa_fmadd_w((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2f64
simde_msa_fmadd_d(simde_v2f64 a, simde_v2f64 b, simde_v2f64 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fmadd_d(a, b, c);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vfmaq_f64(a, b, c);
  #elif defined(SIMDE_X86_FMA_NATIVE)
    return _mm_fmadd_pd(b, c, a);
  #else
    simde_v2f64_private
      a_ = simde_v2f64_to_private(a),
      b_ = simde_v2f64_to_private(b),
      c_ = simde_v2f64_to_private(c),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[i] + (b_.values[i] * c_.values[i]);
    }

    return simde_v2f64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fmadd_d
  #define __msa_fmadd_d(a, b, c) simde_msa_fmadd_d((a), (b), (c))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
