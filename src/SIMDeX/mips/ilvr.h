#if !defined(SIMDE_MIPS_MSA_ILVR_H)
#define SIMDE_MIPS_MSA_ILVR_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_ilvr_b(simde_v16i8 a, simde_v16i8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ilvr_b(a, b);
  #else
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      b_ = simde_v16i8_to_private(b),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < 8 ; i++) {
      r_.values[2 * i]     = b_.values[i];
      r_.values[2 * i + 1] = a_.values[i];
    }

    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ilvr_b
  #define __msa_ilvr_b(a, b) simde_msa_ilvr_b((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_ilvr_h(simde_v8i16 a, simde_v8i16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ilvr_h(a, b);
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < 4 ; i++) {
      r_.values[2 * i]     = b_.values[i];
      r_.values[2 * i + 1] = a_.values[i];
    }

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ilvr_h
  #define __msa_ilvr_h(a, b) simde_msa_ilvr_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_ilvr_w(simde_v4i32 a, simde_v4i32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ilvr_w(a, b);
  #else
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < 2 ; i++) {
      r_.values[2 * i]     = b_.values[i];
      r_.values[2 * i + 1] = a_.values[i];
    }

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ilvr_w
  #define __msa_ilvr_w(a, b) simde_msa_ilvr_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_ilvr_d(simde_v2i64 a, simde_v2i64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ilvr_d(a, b);
  #else
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      b_ = simde_v2i64_to_private(b),
      r_;

    r_.values[0] = b_.values[0];
    r_.values[1] = a_.values[0];

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ilvr_d
  #define __msa_ilvr_d(a, b) simde_msa_ilvr_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
