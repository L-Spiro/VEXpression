#if !defined(SIMDE_MIPS_MSA_TEST_BZ_H)
#define SIMDE_MIPS_MSA_TEST_BZ_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
int
simde_msa_test_bz_b(simde_v16i8 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_test_bz_b(a);
  #else
    simde_v16i8_private a_ = simde_v16i8_to_private(a);
    int result = 1;
    SIMDE_VECTORIZE_REDUCTION(&:result)
    for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
      result &= (a_.values[i] == 0);
    }
    return result;
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_test_bz_b
  #define __msa_test_bz_b(a) simde_msa_test_bz_b(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
int
simde_msa_test_bz_h(simde_v8i16 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_test_bz_h(a);
  #else
    simde_v8i16_private a_ = simde_v8i16_to_private(a);
    int result = 1;
    SIMDE_VECTORIZE_REDUCTION(&:result)
    for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
      result &= (a_.values[i] == 0);
    }
    return result;
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_test_bz_h
  #define __msa_test_bz_h(a) simde_msa_test_bz_h(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
int
simde_msa_test_bz_w(simde_v4i32 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_test_bz_w(a);
  #else
    simde_v4i32_private a_ = simde_v4i32_to_private(a);
    int result = 1;
    SIMDE_VECTORIZE_REDUCTION(&:result)
    for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
      result &= (a_.values[i] == 0);
    }
    return result;
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_test_bz_w
  #define __msa_test_bz_w(a) simde_msa_test_bz_w(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
int
simde_msa_test_bz_d(simde_v2i64 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_test_bz_d(a);
  #else
    simde_v2i64_private a_ = simde_v2i64_to_private(a);
    int result = 1;
    SIMDE_VECTORIZE_REDUCTION(&:result)
    for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
      result &= (a_.values[i] == 0);
    }
    return result;
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_test_bz_d
  #define __msa_test_bz_d(a) simde_msa_test_bz_d(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
