#if !defined(SIMDE_MIPS_MSA_INSERT_H)
#define SIMDE_MIPS_MSA_INSERT_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_insert_b(a, imm, val) __msa_insert_b((a), (imm), (val))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v16i8 simde_msa_insert_b(simde_v16i8 a, const int imm, int val) {
    simde_v16i8_private a_ = simde_v16i8_to_private(a);
    a_.values[imm & 15] = HEDLEY_STATIC_CAST(int8_t, val);
    return simde_v16i8_from_private(a_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_insert_b
  #define __msa_insert_b(a, imm, val) simde_msa_insert_b((a), (imm), (val))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_insert_h(a, imm, val) __msa_insert_h((a), (imm), (val))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v8i16 simde_msa_insert_h(simde_v8i16 a, const int imm, int val) {
    simde_v8i16_private a_ = simde_v8i16_to_private(a);
    a_.values[imm & 7] = HEDLEY_STATIC_CAST(int16_t, val);
    return simde_v8i16_from_private(a_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_insert_h
  #define __msa_insert_h(a, imm, val) simde_msa_insert_h((a), (imm), (val))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_insert_w(a, imm, val) __msa_insert_w((a), (imm), (val))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v4i32 simde_msa_insert_w(simde_v4i32 a, const int imm, int val) {
    simde_v4i32_private a_ = simde_v4i32_to_private(a);
    a_.values[imm & 3] = HEDLEY_STATIC_CAST(int32_t, val);
    return simde_v4i32_from_private(a_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_insert_w
  #define __msa_insert_w(a, imm, val) simde_msa_insert_w((a), (imm), (val))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_insert_d(a, imm, val) __msa_insert_d((a), (imm), (val))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  simde_v2i64 simde_msa_insert_d(simde_v2i64 a, const int imm, int64_t val) {
    simde_v2i64_private a_ = simde_v2i64_to_private(a);
    a_.values[imm & 1] = val;
    return simde_v2i64_from_private(a_);
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_insert_d
  #define __msa_insert_d(a, imm, val) simde_msa_insert_d((a), (imm), (val))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
