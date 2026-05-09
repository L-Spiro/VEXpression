#if !defined(SIMDE_MIPS_MSA_CEQI_H)
#define SIMDE_MIPS_MSA_CEQI_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_ceqi_b(a, imm) __msa_ceqi_b((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v16i8
  simde_msa_ceqi_b(simde_v16i8 a, const int imm) {
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.values = HEDLEY_STATIC_CAST(__typeof__(r_.values), a_.values == imm);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] == imm) ? HEDLEY_STATIC_CAST(int8_t, -1) : 0;
      }
    #endif

    return simde_v16i8_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ceqi_b
  #define __msa_ceqi_b(a, imm) simde_msa_ceqi_b((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_ceqi_h(a, imm) __msa_ceqi_h((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v8i16
  simde_msa_ceqi_h(simde_v8i16 a, const int imm) {
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.values = HEDLEY_STATIC_CAST(__typeof__(r_.values), a_.values == imm);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] == imm) ? HEDLEY_STATIC_CAST(int16_t, -1) : 0;
      }
    #endif

    return simde_v8i16_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ceqi_h
  #define __msa_ceqi_h(a, imm) simde_msa_ceqi_h((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_ceqi_w(a, imm) __msa_ceqi_w((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v4i32
  simde_msa_ceqi_w(simde_v4i32 a, const int imm) {
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.values = HEDLEY_STATIC_CAST(__typeof__(r_.values), a_.values == imm);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] == imm) ? HEDLEY_STATIC_CAST(int32_t, -1) : 0;
      }
    #endif

    return simde_v4i32_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ceqi_w
  #define __msa_ceqi_w(a, imm) simde_msa_ceqi_w((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_ceqi_d(a, imm) __msa_ceqi_d((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v2i64
  simde_msa_ceqi_d(simde_v2i64 a, const int imm) {
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.values = HEDLEY_STATIC_CAST(__typeof__(r_.values), a_.values == imm);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] == imm) ? HEDLEY_STATIC_CAST(int64_t, -1) : 0;
      }
    #endif

    return simde_v2i64_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ceqi_d
  #define __msa_ceqi_d(a, imm) simde_msa_ceqi_d((a), (imm))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
