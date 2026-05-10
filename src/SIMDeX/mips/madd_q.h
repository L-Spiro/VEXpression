#if !defined(SIMDE_MIPS_MSA_MADD_Q_H)
#define SIMDE_MIPS_MSA_MADD_Q_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_madd_q_h(simde_v8i16 a, simde_v8i16 b, simde_v8i16 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_madd_q_h(a, b, c);
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b),
      c_ = simde_v8i16_to_private(c),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int32_t p = HEDLEY_STATIC_CAST(int32_t, b_.values[i]) * HEDLEY_STATIC_CAST(int32_t, c_.values[i]);
      int16_t q = (p == INT32_C(0x40000000)) ? INT16_MAX : HEDLEY_STATIC_CAST(int16_t, p >> 15);
      int32_t sum = HEDLEY_STATIC_CAST(int32_t, a_.values[i]) + HEDLEY_STATIC_CAST(int32_t, q);
      r_.values[i] = (sum > INT16_MAX) ? INT16_MAX : ((sum < INT16_MIN) ? INT16_MIN : HEDLEY_STATIC_CAST(int16_t, sum));
    }

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_madd_q_h
  #define __msa_madd_q_h(a, b, c) simde_msa_madd_q_h((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_madd_q_w(simde_v4i32 a, simde_v4i32 b, simde_v4i32 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_madd_q_w(a, b, c);
  #else
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b),
      c_ = simde_v4i32_to_private(c),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int64_t p = HEDLEY_STATIC_CAST(int64_t, b_.values[i]) * HEDLEY_STATIC_CAST(int64_t, c_.values[i]);
      int32_t q = (p == INT64_C(0x4000000000000000)) ? INT32_MAX : HEDLEY_STATIC_CAST(int32_t, p >> 31);
      int64_t sum = HEDLEY_STATIC_CAST(int64_t, a_.values[i]) + HEDLEY_STATIC_CAST(int64_t, q);
      r_.values[i] = (sum > INT32_MAX) ? INT32_MAX : ((sum < INT32_MIN) ? INT32_MIN : HEDLEY_STATIC_CAST(int32_t, sum));
    }

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_madd_q_w
  #define __msa_madd_q_w(a, b, c) simde_msa_madd_q_w((a), (b), (c))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
