#if !defined(SIMDE_MIPS_MSA_MSUBV_H)
#define SIMDE_MIPS_MSA_MSUBV_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_msubv_b(simde_v16i8 c, simde_v16i8 a, simde_v16i8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_msubv_b(c, a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vmlsq_s8(c, a, b);
  #else
    simde_v16i8_private
      c_ = simde_v16i8_to_private(c),
      a_ = simde_v16i8_to_private(a),
      b_ = simde_v16i8_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = c_.values - (a_.values * b_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = c_.values[i] - (a_.values[i] * b_.values[i]);
      }
    #endif

    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_msubv_b
  #define __msa_msubv_b(c, a, b) simde_msa_msubv_b((c), (a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_msubv_h(simde_v8i16 c, simde_v8i16 a, simde_v8i16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_msubv_h(c, a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vmlsq_s16(c, a, b);
  #else
    simde_v8i16_private
      c_ = simde_v8i16_to_private(c),
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = c_.values - (a_.values * b_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = c_.values[i] - (a_.values[i] * b_.values[i]);
      }
    #endif

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_msubv_h
  #define __msa_msubv_h(c, a, b) simde_msa_msubv_h((c), (a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_msubv_w(simde_v4i32 c, simde_v4i32 a, simde_v4i32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_msubv_w(c, a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vmlsq_s32(c, a, b);
  #else
    simde_v4i32_private
      c_ = simde_v4i32_to_private(c),
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = c_.values - (a_.values * b_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = c_.values[i] - (a_.values[i] * b_.values[i]);
      }
    #endif

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_msubv_w
  #define __msa_msubv_w(c, a, b) simde_msa_msubv_w((c), (a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_msubv_d(simde_v2i64 c, simde_v2i64 a, simde_v2i64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_msubv_d(c, a, b);
  #else
    simde_v2i64_private
      c_ = simde_v2i64_to_private(c),
      a_ = simde_v2i64_to_private(a),
      b_ = simde_v2i64_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = c_.values - (a_.values * b_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = c_.values[i] - (a_.values[i] * b_.values[i]);
      }
    #endif

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_msubv_d
  #define __msa_msubv_d(c, a, b) simde_msa_msubv_d((c), (a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
