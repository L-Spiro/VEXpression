#if !defined(SIMDE_MIPS_MSA_CAST_TO_VECTOR_DOUBLE_H)
#define SIMDE_MIPS_MSA_CAST_TO_VECTOR_DOUBLE_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_cast_to_vector_double(a) __msa_cast_to_vector_double((a))
#elif defined(__cplusplus)
  SIMDE_FUNCTION_ATTRIBUTES simde_v2f64 simde_msa_cast_to_vector_double(simde_v16i8 a) { return simde_x_v16i8_to_v2f64(a); }
  SIMDE_FUNCTION_ATTRIBUTES simde_v2f64 simde_msa_cast_to_vector_double(simde_v8i16 a) { return simde_x_v8i16_to_v2f64(a); }
  SIMDE_FUNCTION_ATTRIBUTES simde_v2f64 simde_msa_cast_to_vector_double(simde_v4i32 a) { return simde_x_v4i32_to_v2f64(a); }
  SIMDE_FUNCTION_ATTRIBUTES simde_v2f64 simde_msa_cast_to_vector_double(simde_v2i64 a) { return simde_x_v2i64_to_v2f64(a); }
  SIMDE_FUNCTION_ATTRIBUTES simde_v2f64 simde_msa_cast_to_vector_double(simde_v16u8 a) { return simde_x_v16u8_to_v2f64(a); }
  SIMDE_FUNCTION_ATTRIBUTES simde_v2f64 simde_msa_cast_to_vector_double(simde_v8u16 a) { return simde_x_v8u16_to_v2f64(a); }
  SIMDE_FUNCTION_ATTRIBUTES simde_v2f64 simde_msa_cast_to_vector_double(simde_v4u32 a) { return simde_x_v4u32_to_v2f64(a); }
  SIMDE_FUNCTION_ATTRIBUTES simde_v2f64 simde_msa_cast_to_vector_double(simde_v2u64 a) { return simde_x_v2u64_to_v2f64(a); }
  SIMDE_FUNCTION_ATTRIBUTES simde_v2f64 simde_msa_cast_to_vector_double(simde_v4f32 a) { return simde_x_v4f32_to_v2f64(a); }
  SIMDE_FUNCTION_ATTRIBUTES simde_v2f64 simde_msa_cast_to_vector_double(simde_v2f64 a) { return a; }
#elif defined(SIMDE_GENERIC_)
  #define simde_msa_cast_to_vector_double(a) \
    (SIMDE_GENERIC_((a), \
      simde_v16i8: simde_x_v16i8_to_v2f64, \
      simde_v8i16: simde_x_v8i16_to_v2f64, \
      simde_v4i32: simde_x_v4i32_to_v2f64, \
      simde_v2i64: simde_x_v2i64_to_v2f64, \
      simde_v16u8: simde_x_v16u8_to_v2f64, \
      simde_v8u16: simde_x_v8u16_to_v2f64, \
      simde_v4u32: simde_x_v4u32_to_v2f64, \
      simde_v2u64: simde_x_v2u64_to_v2f64, \
      simde_v4f32: simde_x_v4f32_to_v2f64, \
      simde_v2f64: simde_x_v2f64_to_v2f64 \
    )(a))
#else
  /* Legacy C89 Fallback - Exploits SIMDe's safe MAY_ALIAS structs */
  #define simde_msa_cast_to_vector_double(a) (*HEDLEY_REINTERPRET_CAST(const simde_v2f64*, &(a)))
#endif

#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_cast_to_vector_double
  #define __msa_cast_to_vector_double(a) simde_msa_cast_to_vector_double((a))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
