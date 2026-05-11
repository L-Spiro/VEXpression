#if !defined(SIMDE_MIPS_MSA_CLEI_H)
#define SIMDE_MIPS_MSA_CLEI_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_clei_s_b(a, imm) __msa_clei_s_b((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v16i8
  simde_msa_clei_s_b(simde_v16i8 a, const int imm) {
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] <= HEDLEY_STATIC_CAST(int8_t, imm)) ? ~HEDLEY_STATIC_CAST(int8_t, 0) : 0;
    }

    return simde_v16i8_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_clei_s_b
  #define __msa_clei_s_b(a, imm) simde_msa_clei_s_b((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_clei_s_h(a, imm) __msa_clei_s_h((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v8i16
  simde_msa_clei_s_h(simde_v8i16 a, const int imm) {
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] <= HEDLEY_STATIC_CAST(int16_t, imm)) ? ~HEDLEY_STATIC_CAST(int16_t, 0) : 0;
    }

    return simde_v8i16_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_clei_s_h
  #define __msa_clei_s_h(a, imm) simde_msa_clei_s_h((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_clei_s_w(a, imm) __msa_clei_s_w((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v4i32
  simde_msa_clei_s_w(simde_v4i32 a, const int imm) {
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] <= HEDLEY_STATIC_CAST(int32_t, imm)) ? ~HEDLEY_STATIC_CAST(int32_t, 0) : 0;
    }

    return simde_v4i32_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_clei_s_w
  #define __msa_clei_s_w(a, imm) simde_msa_clei_s_w((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_clei_s_d(a, imm) __msa_clei_s_d((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v2i64
  simde_msa_clei_s_d(simde_v2i64 a, const int imm) {
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] <= HEDLEY_STATIC_CAST(int64_t, imm)) ? ~HEDLEY_STATIC_CAST(int64_t, 0) : 0;
    }

    return simde_v2i64_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_clei_s_d
  #define __msa_clei_s_d(a, imm) simde_msa_clei_s_d((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_clei_u_b(a, imm) __msa_clei_u_b((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v16u8
  simde_msa_clei_u_b(simde_v16u8 a, const int imm) {
    simde_v16u8_private r_;
    simde_v16u8_private a_ = simde_v16u8_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] <= HEDLEY_STATIC_CAST(uint8_t, imm)) ? ~HEDLEY_STATIC_CAST(int8_t, 0) : 0;
    }

    return simde_v16u8_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_clei_u_b
  #define __msa_clei_u_b(a, imm) simde_msa_clei_u_b((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_clei_u_h(a, imm) __msa_clei_u_h((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v8u16
  simde_msa_clei_u_h(simde_v8u16 a, const int imm) {
    simde_v8u16_private r_;
    simde_v8u16_private a_ = simde_v8u16_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] <= HEDLEY_STATIC_CAST(uint16_t, imm)) ? ~HEDLEY_STATIC_CAST(int16_t, 0) : 0;
    }

    return simde_v8u16_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_clei_u_h
  #define __msa_clei_u_h(a, imm) simde_msa_clei_u_h((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_clei_u_w(a, imm) __msa_clei_u_w((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v4u32
  simde_msa_clei_u_w(simde_v4u32 a, const int imm) {
    simde_v4u32_private r_;
    simde_v4u32_private a_ = simde_v4u32_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] <= HEDLEY_STATIC_CAST(uint32_t, imm)) ? ~HEDLEY_STATIC_CAST(int32_t, 0) : 0;
    }

    return simde_v4u32_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_clei_u_w
  #define __msa_clei_u_w(a, imm) simde_msa_clei_u_w((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_clei_u_d(a, imm) __msa_clei_u_d((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v2u64
  simde_msa_clei_u_d(simde_v2u64 a, const int imm) {
    simde_v2u64_private r_;
    simde_v2u64_private a_ = simde_v2u64_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] <= HEDLEY_STATIC_CAST(uint64_t, imm)) ? ~HEDLEY_STATIC_CAST(int64_t, 0) : 0;
    }

    return simde_v2u64_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_clei_u_d
  #define __msa_clei_u_d(a, imm) simde_msa_clei_u_d((a), (imm))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
