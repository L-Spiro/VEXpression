#if !defined(SIMDE_MIPS_MSA_SPLAT_H)
#define SIMDE_MIPS_MSA_SPLAT_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_splat_b(simde_v16i8 a, int n) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_splat_b(a, n);
  #else
    simde_v16i8_private a_ = simde_v16i8_to_private(a), r_;
    int idx = n & 15;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[idx];
    }
    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_splat_b
  #define __msa_splat_b(a, n) simde_msa_splat_b((a), (n))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_splat_h(simde_v8i16 a, int n) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_splat_h(a, n);
  #else
    simde_v8i16_private a_ = simde_v8i16_to_private(a), r_;
    int idx = n & 7;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[idx];
    }
    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_splat_h
  #define __msa_splat_h(a, n) simde_msa_splat_h((a), (n))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_splat_w(simde_v4i32 a, int n) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_splat_w(a, n);
  #else
    simde_v4i32_private a_ = simde_v4i32_to_private(a), r_;
    int idx = n & 3;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[idx];
    }
    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_splat_w
  #define __msa_splat_w(a, n) simde_msa_splat_w((a), (n))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_splat_d(simde_v2i64 a, int n) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_splat_d(a, n);
  #else
    simde_v2i64_private a_ = simde_v2i64_to_private(a), r_;
    int idx = n & 1;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = a_.values[idx];
    }
    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_splat_d
  #define __msa_splat_d(a, n) simde_msa_splat_d((a), (n))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
