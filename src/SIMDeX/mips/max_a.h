#if !defined(SIMDE_MIPS_MSA_MAX_A_H)
#define SIMDE_MIPS_MSA_MAX_A_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#define SIMDE_MIPS_MSA_GENERATE_MAX_A_(Element_Type, Scalar_Type, suffix) \
  SIMDE_FUNCTION_ATTRIBUTES \
  simde_##Element_Type simde_msa_max_a_##suffix(simde_##Element_Type a, simde_##Element_Type b) { \
    simde_##Element_Type##_private a_ = simde_##Element_Type##_to_private(a); \
    simde_##Element_Type##_private b_ = simde_##Element_Type##_to_private(b); \
    simde_##Element_Type##_private r_; \
    SIMDE_VECTORIZE \
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) { \
      Scalar_Type abs_a = (a_.values[i] < 0) ? -a_.values[i] : a_.values[i]; \
      Scalar_Type abs_b = (b_.values[i] < 0) ? -b_.values[i] : b_.values[i]; \
      r_.values[i] = (abs_a > abs_b) ? abs_a : abs_b; \
    } \
    return simde_##Element_Type##_from_private(r_); \
  }

SIMDE_MIPS_MSA_GENERATE_MAX_A_(v16i8, int8_t, b)
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_max_a_b
  #define __msa_max_a_b(a, b) simde_msa_max_a_b((a), (b))
#endif

SIMDE_MIPS_MSA_GENERATE_MAX_A_(v8i16, int16_t, h)
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_max_a_h
  #define __msa_max_a_h(a, b) simde_msa_max_a_h((a), (b))
#endif

SIMDE_MIPS_MSA_GENERATE_MAX_A_(v4i32, int32_t, w)
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_max_a_w
  #define __msa_max_a_w(a, b) simde_msa_max_a_w((a), (b))
#endif

SIMDE_MIPS_MSA_GENERATE_MAX_A_(v2i64, int64_t, d)
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_max_a_d
  #define __msa_max_a_d(a, b) simde_msa_max_a_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
