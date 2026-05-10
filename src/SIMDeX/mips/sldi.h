#if !defined(SIMDE_MIPS_MSA_SLDI_H)
#define SIMDE_MIPS_MSA_SLDI_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_sldi_b(a, b, imm) __msa_sldi_b((a), (b), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v16i8
  simde_msa_sldi_b(simde_v16i8 a, simde_v16i8 b, const int imm) {
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      b_ = simde_v16i8_to_private(b),
      r_;

    size_t count = sizeof(r_.values) / sizeof(r_.values[0]);
    size_t n = imm % count;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < count ; i++) {
      r_.values[i] = (i + n < count) ? b_.values[i + n] : a_.values[i + n - count];
    }

    return simde_v16i8_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_sldi_b
  #define __msa_sldi_b(a, b, imm) simde_msa_sldi_b((a), (b), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_sldi_h(a, b, imm) __msa_sldi_h((a), (b), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v8i16
  simde_msa_sldi_h(simde_v8i16 a, simde_v8i16 b, const int imm) {
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b),
      r_;

    size_t count = sizeof(r_.values) / sizeof(r_.values[0]);
    size_t n = imm % count;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < count ; i++) {
      r_.values[i] = (i + n < count) ? b_.values[i + n] : a_.values[i + n - count];
    }

    return simde_v8i16_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_sldi_h
  #define __msa_sldi_h(a, b, imm) simde_msa_sldi_h((a), (b), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_sldi_w(a, b, imm) __msa_sldi_w((a), (b), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v4i32
  simde_msa_sldi_w(simde_v4i32 a, simde_v4i32 b, const int imm) {
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b),
      r_;

    size_t count = sizeof(r_.values) / sizeof(r_.values[0]);
    size_t n = imm % count;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < count ; i++) {
      r_.values[i] = (i + n < count) ? b_.values[i + n] : a_.values[i + n - count];
    }

    return simde_v4i32_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_sldi_w
  #define __msa_sldi_w(a, b, imm) simde_msa_sldi_w((a), (b), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_sldi_d(a, b, imm) __msa_sldi_d((a), (b), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v2i64
  simde_msa_sldi_d(simde_v2i64 a, simde_v2i64 b, const int imm) {
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      b_ = simde_v2i64_to_private(b),
      r_;

    size_t count = sizeof(r_.values) / sizeof(r_.values[0]);
    size_t n = imm % count;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < count ; i++) {
      r_.values[i] = (i + n < count) ? b_.values[i + n] : a_.values[i + n - count];
    }

    return simde_v2i64_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_sldi_d
  #define __msa_sldi_d(a, b, imm) simde_msa_sldi_d((a), (b), (imm))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
