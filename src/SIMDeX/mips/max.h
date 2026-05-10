#if !defined(SIMDE_MIPS_MSA_MAX_H)
#define SIMDE_MIPS_MSA_MAX_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#define SIMDE_MIPS_MSA_GENERATE_MAX_S_(Element_Type, suffix) \
  SIMDE_FUNCTION_ATTRIBUTES \
  simde_##Element_Type simde_msa_max_s_##suffix(simde_##Element_Type a, simde_##Element_Type b) { \
    simde_##Element_Type##_private a_ = simde_##Element_Type##_to_private(a); \
    simde_##Element_Type##_private b_ = simde_##Element_Type##_to_private(b); \
    simde_##Element_Type##_private r_; \
    SIMDE_VECTORIZE \
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) { \
      r_.values[i] = (a_.values[i] > b_.values[i]) ? a_.values[i] : b_.values[i]; \
    } \
    return simde_##Element_Type##_from_private(r_); \
  }

SIMDE_MIPS_MSA_GENERATE_MAX_S_(v16i8, b)
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_max_s_b
  #define __msa_max_s_b(a, b) simde_msa_max_s_b((a), (b))
#endif

SIMDE_MIPS_MSA_GENERATE_MAX_S_(v8i16, h)
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_max_s_h
  #define __msa_max_s_h(a, b) simde_msa_max_s_h((a), (b))
#endif

SIMDE_MIPS_MSA_GENERATE_MAX_S_(v4i32, w)
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_max_s_w
  #define __msa_max_s_w(a, b) simde_msa_max_s_w((a), (b))
#endif

SIMDE_MIPS_MSA_GENERATE_MAX_S_(v2i64, d)
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_max_s_d
  #define __msa_max_s_d(a, b) simde_msa_max_s_d((a), (b))
#endif

#define SIMDE_MIPS_MSA_GENERATE_MAX_U_(Element_Type, suffix) \
  SIMDE_FUNCTION_ATTRIBUTES \
  simde_##Element_Type simde_msa_max_u_##suffix(simde_##Element_Type a, simde_##Element_Type b) { \
    simde_##Element_Type##_private a_ = simde_##Element_Type##_to_private(a); \
    simde_##Element_Type##_private b_ = simde_##Element_Type##_to_private(b); \
    simde_##Element_Type##_private r_; \
    SIMDE_VECTORIZE \
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) { \
      r_.values[i] = (a_.values[i] > b_.values[i]) ? a_.values[i] : b_.values[i]; \
    } \
    return simde_##Element_Type##_from_private(r_); \
  }

SIMDE_MIPS_MSA_GENERATE_MAX_U_(v16u8, b)
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_max_u_b
  #define __msa_max_u_b(a, b) simde_msa_max_u_b((a), (b))
#endif

SIMDE_MIPS_MSA_GENERATE_MAX_U_(v8u16, h)
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_max_u_h
  #define __msa_max_u_h(a, b) simde_msa_max_u_h((a), (b))
#endif

SIMDE_MIPS_MSA_GENERATE_MAX_U_(v4u32, w)
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_max_u_w
  #define __msa_max_u_w(a, b) simde_msa_max_u_w((a), (b))
#endif

SIMDE_MIPS_MSA_GENERATE_MAX_U_(v2u64, d)
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_max_u_d
  #define __msa_max_u_d(a, b) simde_msa_max_u_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
