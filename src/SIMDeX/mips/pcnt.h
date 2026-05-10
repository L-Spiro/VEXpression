#if !defined(SIMDE_MIPS_MSA_PCNT_H)
#define SIMDE_MIPS_MSA_PCNT_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_pcnt_b(simde_v16i8 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_pcnt_b(a);
  #else
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint8_t v = HEDLEY_STATIC_CAST(uint8_t, a_.values[i]);
      uint8_t c = 0;
      while (v) {
        c += v & 1;
        v >>= 1;
      }
      r_.values[i] = c;
    }

    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_pcnt_b
  #define __msa_pcnt_b(a) simde_msa_pcnt_b(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_pcnt_h(simde_v8i16 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_pcnt_h(a);
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint16_t v = HEDLEY_STATIC_CAST(uint16_t, a_.values[i]);
      uint16_t c = 0;
      while (v) {
        c += v & 1;
        v >>= 1;
      }
      r_.values[i] = HEDLEY_STATIC_CAST(int16_t, c);
    }

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_pcnt_h
  #define __msa_pcnt_h(a) simde_msa_pcnt_h(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_pcnt_w(simde_v4i32 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_pcnt_w(a);
  #else
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint32_t v = HEDLEY_STATIC_CAST(uint32_t, a_.values[i]);
      uint32_t c = 0;
      while (v) {
        c += v & 1;
        v >>= 1;
      }
      r_.values[i] = HEDLEY_STATIC_CAST(int32_t, c);
    }

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_pcnt_w
  #define __msa_pcnt_w(a) simde_msa_pcnt_w(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_pcnt_d(simde_v2i64 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_pcnt_d(a);
  #else
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint64_t v = HEDLEY_STATIC_CAST(uint64_t, a_.values[i]);
      uint64_t c = 0;
      while (v) {
        c += v & 1;
        v >>= 1;
      }
      r_.values[i] = HEDLEY_STATIC_CAST(int64_t, c);
    }

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_pcnt_d
  #define __msa_pcnt_d(a) simde_msa_pcnt_d(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
