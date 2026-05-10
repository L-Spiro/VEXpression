#if !defined(SIMDE_MIPS_MSA_MAXI_H)
#define SIMDE_MIPS_MSA_MAXI_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#define SIMDE_MIPS_MSA_GENERATE_MAXI_S_(Element_Type, Cast_Type, suffix) \
  SIMDE_FUNCTION_ATTRIBUTES \
  simde_##Element_Type simde_msa_maxi_s_##suffix(simde_##Element_Type a, const int imm) { \
    simde_##Element_Type##_private a_ = simde_##Element_Type##_to_private(a); \
    simde_##Element_Type##_private r_; \
    SIMDE_VECTORIZE \
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) { \
      r_.values[i] = (a_.values[i] > HEDLEY_STATIC_CAST(Cast_Type, imm)) ? a_.values[i] : HEDLEY_STATIC_CAST(Cast_Type, imm); \
    } \
    return simde_##Element_Type##_from_private(r_); \
  }

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_maxi_s_b(a, imm) __msa_maxi_s_b((a), (imm))
#else
  SIMDE_MIPS_MSA_GENERATE_MAXI_S_(v16i8, int8_t, b)
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_maxi_s_b
  #define __msa_maxi_s_b(a, imm) simde_msa_maxi_s_b((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_maxi_s_h(a, imm) __msa_maxi_s_h((a), (imm))
#else
  SIMDE_MIPS_MSA_GENERATE_MAXI_S_(v8i16, int16_t, h)
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_maxi_s_h
  #define __msa_maxi_s_h(a, imm) simde_msa_maxi_s_h((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_maxi_s_w(a, imm) __msa_maxi_s_w((a), (imm))
#else
  SIMDE_MIPS_MSA_GENERATE_MAXI_S_(v4i32, int32_t, w)
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_maxi_s_w
  #define __msa_maxi_s_w(a, imm) simde_msa_maxi_s_w((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_maxi_s_d(a, imm) __msa_maxi_s_d((a), (imm))
#else
  SIMDE_MIPS_MSA_GENERATE_MAXI_S_(v2i64, int64_t, d)
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_maxi_s_d
  #define __msa_maxi_s_d(a, imm) simde_msa_maxi_s_d((a), (imm))
#endif

#define SIMDE_MIPS_MSA_GENERATE_MAXI_U_(Element_Type, Cast_Type, suffix) \
  SIMDE_FUNCTION_ATTRIBUTES \
  simde_##Element_Type simde_msa_maxi_u_##suffix(simde_##Element_Type a, const int imm) { \
    simde_##Element_Type##_private a_ = simde_##Element_Type##_to_private(a); \
    simde_##Element_Type##_private r_; \
    SIMDE_VECTORIZE \
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) { \
      r_.values[i] = (a_.values[i] > HEDLEY_STATIC_CAST(Cast_Type, imm)) ? a_.values[i] : HEDLEY_STATIC_CAST(Cast_Type, imm); \
    } \
    return simde_##Element_Type##_from_private(r_); \
  }

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_maxi_u_b(a, imm) __msa_maxi_u_b((a), (imm))
#else
  SIMDE_MIPS_MSA_GENERATE_MAXI_U_(v16u8, uint8_t, b)
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_maxi_u_b
  #define __msa_maxi_u_b(a, imm) simde_msa_maxi_u_b((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_maxi_u_h(a, imm) __msa_maxi_u_h((a), (imm))
#else
  SIMDE_MIPS_MSA_GENERATE_MAXI_U_(v8u16, uint16_t, h)
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_maxi_u_h
  #define __msa_maxi_u_h(a, imm) simde_msa_maxi_u_h((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_maxi_u_w(a, imm) __msa_maxi_u_w((a), (imm))
#else
  SIMDE_MIPS_MSA_GENERATE_MAXI_U_(v4u32, uint32_t, w)
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_maxi_u_w
  #define __msa_maxi_u_w(a, imm) simde_msa_maxi_u_w((a), (imm))
#endif

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_maxi_u_d(a, imm) __msa_maxi_u_d((a), (imm))
#else
  SIMDE_MIPS_MSA_GENERATE_MAXI_U_(v2u64, uint64_t, d)
#endif
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_maxi_u_d
  #define __msa_maxi_u_d(a, imm) simde_msa_maxi_u_d((a), (imm))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
