#if !defined(SIMDE_MIPS_MSA_SRLR_H)
#define SIMDE_MIPS_MSA_SRLR_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_srlr_b(simde_v16i8 a, simde_v16i8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_srlr_b(a, b);
  #else
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      b_ = simde_v16i8_to_private(b),
      r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint8_t shift = b_.values[i] & 7;
      uint8_t val = HEDLEY_STATIC_CAST(uint8_t, a_.values[i]);
      r_.values[i] = HEDLEY_STATIC_CAST(int8_t, (shift == 0) ? val : ((val >> shift) + ((val >> (shift - 1)) & 1)));
    }
    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_srlr_b
  #define __msa_srlr_b(a, b) simde_msa_srlr_b((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_srlr_h(simde_v8i16 a, simde_v8i16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_srlr_h(a, b);
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b),
      r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint16_t shift = b_.values[i] & 15;
      uint16_t val = HEDLEY_STATIC_CAST(uint16_t, a_.values[i]);
      r_.values[i] = HEDLEY_STATIC_CAST(int16_t, (shift == 0) ? val : ((val >> shift) + ((val >> (shift - 1)) & 1)));
    }
    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_srlr_h
  #define __msa_srlr_h(a, b) simde_msa_srlr_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_srlr_w(simde_v4i32 a, simde_v4i32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_srlr_w(a, b);
  #else
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b),
      r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint32_t shift = b_.values[i] & 31;
      uint32_t val = HEDLEY_STATIC_CAST(uint32_t, a_.values[i]);
      r_.values[i] = HEDLEY_STATIC_CAST(int32_t, (shift == 0) ? val : ((val >> shift) + ((val >> (shift - 1)) & 1)));
    }
    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_srlr_w
  #define __msa_srlr_w(a, b) simde_msa_srlr_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_srlr_d(simde_v2i64 a, simde_v2i64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_srlr_d(a, b);
  #else
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      b_ = simde_v2i64_to_private(b),
      r_;
    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint64_t shift = b_.values[i] & 63;
      uint64_t val = HEDLEY_STATIC_CAST(uint64_t, a_.values[i]);
      r_.values[i] = HEDLEY_STATIC_CAST(int64_t, (shift == 0) ? val : ((val >> shift) + ((val >> (shift - 1)) & 1)));
    }
    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_srlr_d
  #define __msa_srlr_d(a, b) simde_msa_srlr_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
