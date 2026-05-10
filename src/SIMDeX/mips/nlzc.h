#if !defined(SIMDE_MIPS_MSA_NLZC_H)
#define SIMDE_MIPS_MSA_NLZC_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_nlzc_b(simde_v16i8 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_nlzc_b(a);
  #else
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int8_t v = a_.values[i];
      int8_t count = 0;
      for (int j = 7; j >= 0; j--) {
        if (v & (1 << j)) break;
        count++;
      }
      r_.values[i] = count;
    }

    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_nlzc_b
  #define __msa_nlzc_b(a) simde_msa_nlzc_b(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_nlzc_h(simde_v8i16 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_nlzc_h(a);
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int16_t v = a_.values[i];
      int16_t count = 0;
      for (int j = 15; j >= 0; j--) {
        if (v & (1 << j)) break;
        count++;
      }
      r_.values[i] = count;
    }

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_nlzc_h
  #define __msa_nlzc_h(a) simde_msa_nlzc_h(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_nlzc_w(simde_v4i32 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_nlzc_w(a);
  #else
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int32_t v = a_.values[i];
      int32_t count = 0;
      for (int j = 31; j >= 0; j--) {
        if (v & (1 << j)) break;
        count++;
      }
      r_.values[i] = count;
    }

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_nlzc_w
  #define __msa_nlzc_w(a) simde_msa_nlzc_w(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_nlzc_d(simde_v2i64 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_nlzc_d(a);
  #else
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      int64_t v = a_.values[i];
      int64_t count = 0;
      for (int j = 63; j >= 0; j--) {
        if (v & (INT64_C(1) << j)) break;
        count++;
      }
      r_.values[i] = count;
    }

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_nlzc_d
  #define __msa_nlzc_d(a) simde_msa_nlzc_d(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
