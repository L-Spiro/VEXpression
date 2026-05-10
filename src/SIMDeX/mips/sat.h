#if !defined(SIMDE_MIPS_MSA_SAT_H)
#define SIMDE_MIPS_MSA_SAT_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_sat_s_b(a, imm) __msa_sat_s_b((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v16i8
  simde_msa_sat_s_b(simde_v16i8 a, const int imm) {
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      r_;

    int32_t limit_max = (1 << imm) - 1;
    int32_t limit_min = -(1 << imm);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(int8_t, 
        (a_.values[i] > limit_max) ? limit_max : ((a_.values[i] < limit_min) ? limit_min : a_.values[i]));
    }
    return simde_v16i8_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_sat_s_b
  #define __msa_sat_s_b(a, imm) simde_msa_sat_s_b((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_sat_s_h(a, imm) __msa_sat_s_h((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v8i16
  simde_msa_sat_s_h(simde_v8i16 a, const int imm) {
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      r_;

    int32_t limit_max = (1 << imm) - 1;
    int32_t limit_min = -(1 << imm);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(int16_t, 
        (a_.values[i] > limit_max) ? limit_max : ((a_.values[i] < limit_min) ? limit_min : a_.values[i]));
    }
    return simde_v8i16_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_sat_s_h
  #define __msa_sat_s_h(a, imm) simde_msa_sat_s_h((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_sat_s_w(a, imm) __msa_sat_s_w((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v4i32
  simde_msa_sat_s_w(simde_v4i32 a, const int imm) {
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      r_;

    int64_t limit_max = (INT64_C(1) << imm) - 1;
    int64_t limit_min = -(INT64_C(1) << imm);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(int32_t, 
        (a_.values[i] > limit_max) ? limit_max : ((a_.values[i] < limit_min) ? limit_min : a_.values[i]));
    }
    return simde_v4i32_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_sat_s_w
  #define __msa_sat_s_w(a, imm) simde_msa_sat_s_w((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_sat_s_d(a, imm) __msa_sat_s_d((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v2i64
  simde_msa_sat_s_d(simde_v2i64 a, const int imm) {
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      r_;

    /* Careful avoiding undefined shift if imm == 63 */
    int64_t limit_max = (imm == 63) ? INT64_MAX : (INT64_C(1) << imm) - 1;
    int64_t limit_min = (imm == 63) ? INT64_MIN : -(INT64_C(1) << imm);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(int64_t, 
        (a_.values[i] > limit_max) ? limit_max : ((a_.values[i] < limit_min) ? limit_min : a_.values[i]));
    }
    return simde_v2i64_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_sat_s_d
  #define __msa_sat_s_d(a, imm) simde_msa_sat_s_d((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_sat_u_b(a, imm) __msa_sat_u_b((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v16u8
  simde_msa_sat_u_b(simde_v16u8 a, const int imm) {
    simde_v16u8_private
      a_ = simde_v16u8_to_private(a),
      r_;

    uint32_t limit_max = (UINT32_C(1) << (imm + 1)) - 1;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(uint8_t, (a_.values[i] > limit_max) ? limit_max : a_.values[i]);
    }
    return simde_v16u8_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_sat_u_b
  #define __msa_sat_u_b(a, imm) simde_msa_sat_u_b((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_sat_u_h(a, imm) __msa_sat_u_h((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v8u16
  simde_msa_sat_u_h(simde_v8u16 a, const int imm) {
    simde_v8u16_private
      a_ = simde_v8u16_to_private(a),
      r_;

    uint32_t limit_max = (UINT32_C(1) << (imm + 1)) - 1;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(uint16_t, (a_.values[i] > limit_max) ? limit_max : a_.values[i]);
    }
    return simde_v8u16_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_sat_u_h
  #define __msa_sat_u_h(a, imm) simde_msa_sat_u_h((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_sat_u_w(a, imm) __msa_sat_u_w((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v4u32
  simde_msa_sat_u_w(simde_v4u32 a, const int imm) {
    simde_v4u32_private
      a_ = simde_v4u32_to_private(a),
      r_;

    uint64_t limit_max = (UINT64_C(1) << (imm + 1)) - 1;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(uint32_t, (a_.values[i] > limit_max) ? limit_max : a_.values[i]);
    }
    return simde_v4u32_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_sat_u_w
  #define __msa_sat_u_w(a, imm) simde_msa_sat_u_w((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_sat_u_d(a, imm) __msa_sat_u_d((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v2u64
  simde_msa_sat_u_d(simde_v2u64 a, const int imm) {
    simde_v2u64_private
      a_ = simde_v2u64_to_private(a),
      r_;

    uint64_t limit_max = (imm == 63) ? UINT64_MAX : (UINT64_C(1) << (imm + 1)) - 1;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = HEDLEY_STATIC_CAST(uint64_t, (a_.values[i] > limit_max) ? limit_max : a_.values[i]);
    }
    return simde_v2u64_from_private(r_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_sat_u_d
  #define __msa_sat_u_d(a, imm) simde_msa_sat_u_d((a), (imm))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
