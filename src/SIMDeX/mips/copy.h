#if !defined(SIMDE_MIPS_MSA_COPY_H)
#define SIMDE_MIPS_MSA_COPY_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_copy_s_b(a, imm) __msa_copy_s_b((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  int8_t
  simde_msa_copy_s_b(simde_v16i8 a, const int imm) {
    simde_v16i8_private a_ = simde_v16i8_to_private(a);
    return a_.values[imm & 15];
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_copy_s_b
  #define __msa_copy_s_b(a, imm) simde_msa_copy_s_b((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_copy_s_h(a, imm) __msa_copy_s_h((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  int16_t
  simde_msa_copy_s_h(simde_v8i16 a, const int imm) {
    simde_v8i16_private a_ = simde_v8i16_to_private(a);
    return a_.values[imm & 7];
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_copy_s_h
  #define __msa_copy_s_h(a, imm) simde_msa_copy_s_h((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_copy_s_w(a, imm) __msa_copy_s_w((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  int32_t
  simde_msa_copy_s_w(simde_v4i32 a, const int imm) {
    simde_v4i32_private a_ = simde_v4i32_to_private(a);
    return a_.values[imm & 3];
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_copy_s_w
  #define __msa_copy_s_w(a, imm) simde_msa_copy_s_w((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_copy_s_d(a, imm) __msa_copy_s_d((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  int64_t
  simde_msa_copy_s_d(simde_v2i64 a, const int imm) {
    simde_v2i64_private a_ = simde_v2i64_to_private(a);
    return a_.values[imm & 1];
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_copy_s_d
  #define __msa_copy_s_d(a, imm) simde_msa_copy_s_d((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_copy_u_b(a, imm) __msa_copy_u_b((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  uint8_t
  simde_msa_copy_u_b(simde_v16u8 a, const int imm) {
    simde_v16u8_private a_ = simde_v16u8_to_private(a);
    return a_.values[imm & 15];
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_copy_u_b
  #define __msa_copy_u_b(a, imm) simde_msa_copy_u_b((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_copy_u_h(a, imm) __msa_copy_u_h((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  uint16_t
  simde_msa_copy_u_h(simde_v8u16 a, const int imm) {
    simde_v8u16_private a_ = simde_v8u16_to_private(a);
    return a_.values[imm & 7];
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_copy_u_h
  #define __msa_copy_u_h(a, imm) simde_msa_copy_u_h((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_copy_u_w(a, imm) __msa_copy_u_w((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  uint32_t
  simde_msa_copy_u_w(simde_v4u32 a, const int imm) {
    simde_v4u32_private a_ = simde_v4u32_to_private(a);
    return a_.values[imm & 3];
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_copy_u_w
  #define __msa_copy_u_w(a, imm) simde_msa_copy_u_w((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_copy_u_d(a, imm) __msa_copy_u_d((a), (imm))
#else
  SIMDE_FUNCTION_ATTRIBUTES
  uint64_t
  simde_msa_copy_u_d(simde_v2u64 a, const int imm) {
    simde_v2u64_private a_ = simde_v2u64_to_private(a);
    return a_.values[imm & 1];
  }
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_copy_u_d
  #define __msa_copy_u_d(a, imm) simde_msa_copy_u_d((a), (imm))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
