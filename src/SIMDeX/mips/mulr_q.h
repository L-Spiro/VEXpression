#if !defined(SIMDE_MIPS_MSA_MULR_Q_H)
#define SIMDE_MIPS_MSA_MULR_Q_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_mulr_q_h(simde_v8i16 a, simde_v8i16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_mulr_q_h(a, b);
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int32_t prod = HEDLEY_STATIC_CAST(int32_t, a_.values[i]) * HEDLEY_STATIC_CAST(int32_t, b_.values[i]);
      r_.values[i] = (prod == INT32_C(0x40000000)) ? INT16_MAX : HEDLEY_STATIC_CAST(int16_t, (prod + INT32_C(0x4000)) >> 15);
    }

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_mulr_q_h
  #define __msa_mulr_q_h(a, b) simde_msa_mulr_q_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_mulr_q_w(simde_v4i32 a, simde_v4i32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_mulr_q_w(a, b);
  #else
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int64_t prod = HEDLEY_STATIC_CAST(int64_t, a_.values[i]) * HEDLEY_STATIC_CAST(int64_t, b_.values[i]);
      r_.values[i] = (prod == INT64_C(0x4000000000000000)) ? INT32_MAX : HEDLEY_STATIC_CAST(int32_t, (prod + INT64_C(0x40000000)) >> 31);
    }

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_mulr_q_w
  #define __msa_mulr_q_w(a, b) simde_msa_mulr_q_w((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
