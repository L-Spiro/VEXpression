#if !defined(SIMDE_MIPS_MSA_MIN_A_H)
#define SIMDE_MIPS_MSA_MIN_A_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8 simde_msa_min_a_b(simde_v16i8 a, simde_v16i8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_min_a_b(a, b);
  #else
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      b_ = simde_v16i8_to_private(b),
      r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int8_t abs_a = (a_.values[i] < 0) ? -a_.values[i] : a_.values[i];
      int8_t abs_b = (b_.values[i] < 0) ? -b_.values[i] : b_.values[i];
      r_.values[i] = (abs_a < abs_b) ? a_.values[i] : b_.values[i];
    }
    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_min_a_b
  #define __msa_min_a_b(a, b) simde_msa_min_a_b((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16 simde_msa_min_a_h(simde_v8i16 a, simde_v8i16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_min_a_h(a, b);
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b),
      r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int16_t abs_a = (a_.values[i] < 0) ? -a_.values[i] : a_.values[i];
      int16_t abs_b = (b_.values[i] < 0) ? -b_.values[i] : b_.values[i];
      r_.values[i] = (abs_a < abs_b) ? a_.values[i] : b_.values[i];
    }
    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_min_a_h
  #define __msa_min_a_h(a, b) simde_msa_min_a_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32 simde_msa_min_a_w(simde_v4i32 a, simde_v4i32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_min_a_w(a, b);
  #else
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b),
      r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int32_t abs_a = (a_.values[i] < 0) ? -a_.values[i] : a_.values[i];
      int32_t abs_b = (b_.values[i] < 0) ? -b_.values[i] : b_.values[i];
      r_.values[i] = (abs_a < abs_b) ? a_.values[i] : b_.values[i];
    }
    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_min_a_w
  #define __msa_min_a_w(a, b) simde_msa_min_a_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64 simde_msa_min_a_d(simde_v2i64 a, simde_v2i64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_min_a_d(a, b);
  #else
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      b_ = simde_v2i64_to_private(b),
      r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int64_t abs_a = (a_.values[i] < 0) ? -a_.values[i] : a_.values[i];
      int64_t abs_b = (b_.values[i] < 0) ? -b_.values[i] : b_.values[i];
      r_.values[i] = (abs_a < abs_b) ? a_.values[i] : b_.values[i];
    }
    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_min_a_d
  #define __msa_min_a_d(a, b) simde_msa_min_a_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
