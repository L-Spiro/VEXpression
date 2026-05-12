#if !defined(SIMDE_MIPS_MSA_SLD_H)
#define SIMDE_MIPS_MSA_SLD_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_sld_b(simde_v16i8 a, simde_v16i8 b, int32_t c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_sld_b(a, b, c);
  #else
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      b_ = simde_v16i8_to_private(b),
      r_;

    size_t count = sizeof(r_.values) / sizeof(r_.values[0]);
    size_t n = HEDLEY_STATIC_CAST(size_t, HEDLEY_STATIC_CAST(uint32_t, c)) % count;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < count ; i++) {
      r_.values[i] = (i + n < count) ? a_.values[i + n] : b_.values[i + n - count];
    }

    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_sld_b
  #define __msa_sld_b(a, b, c) simde_msa_sld_b((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_sld_h(simde_v8i16 a, simde_v8i16 b, int32_t c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_sld_h(a, b, c);
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b),
      r_;

    size_t count = sizeof(r_.values) / sizeof(r_.values[0]);
    size_t n = HEDLEY_STATIC_CAST(size_t, HEDLEY_STATIC_CAST(uint32_t, c)) % count;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < count ; i++) {
      r_.values[i] = (i + n < count) ? a_.values[i + n] : b_.values[i + n - count];
    }

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_sld_h
  #define __msa_sld_h(a, b, c) simde_msa_sld_h((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_sld_w(simde_v4i32 a, simde_v4i32 b, int32_t c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_sld_w(a, b, c);
  #else
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b),
      r_;

    size_t count = sizeof(r_.values) / sizeof(r_.values[0]);
    size_t n = HEDLEY_STATIC_CAST(size_t, HEDLEY_STATIC_CAST(uint32_t, c)) % count;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < count ; i++) {
      r_.values[i] = (i + n < count) ? a_.values[i + n] : b_.values[i + n - count];
    }

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_sld_w
  #define __msa_sld_w(a, b, c) simde_msa_sld_w((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_sld_d(simde_v2i64 a, simde_v2i64 b, int32_t c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_sld_d(a, b, c);
  #else
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      b_ = simde_v2i64_to_private(b),
      r_;

    size_t count = sizeof(r_.values) / sizeof(r_.values[0]);
    size_t n = HEDLEY_STATIC_CAST(size_t, HEDLEY_STATIC_CAST(uint32_t, c)) % count;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < count ; i++) {
      r_.values[i] = (i + n < count) ? a_.values[i + n] : b_.values[i + n - count];
    }

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_sld_d
  #define __msa_sld_d(a, b, c) simde_msa_sld_d((a), (b), (c))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
