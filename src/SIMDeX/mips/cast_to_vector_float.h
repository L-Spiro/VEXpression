#if !defined(SIMDE_MIPS_MSA_CAST_TO_VECTOR_FLOAT_H)
#define SIMDE_MIPS_MSA_CAST_TO_VECTOR_FLOAT_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

#if defined(SIMDE_MIPS_MSA_NATIVE)
  #define simde_msa_cast_to_vector_float(a) __msa_cast_to_vector_float(a)
#endif

// Generate explicit strongly-typed helper functions
#define SIMDE_MSA_CAST_TO_VECTOR_FLOAT_IMPL(T, T_name) \
  SIMDE_FUNCTION_ATTRIBUTES simde_v4f32 simde_x_msa_cast_to_vector_float_##T_name(T a) { \
    simde_v4f32_private r_; \
    simde_memcpy(&r_, &a, sizeof(r_)); \
    return simde_v4f32_from_private(r_); \
  }

SIMDE_MSA_CAST_TO_VECTOR_FLOAT_IMPL(simde_v16i8, v16i8)
SIMDE_MSA_CAST_TO_VECTOR_FLOAT_IMPL(simde_v16u8, v16u8)
SIMDE_MSA_CAST_TO_VECTOR_FLOAT_IMPL(simde_v8i16, v8i16)
SIMDE_MSA_CAST_TO_VECTOR_FLOAT_IMPL(simde_v8u16, v8u16)
SIMDE_MSA_CAST_TO_VECTOR_FLOAT_IMPL(simde_v4i32, v4i32)
SIMDE_MSA_CAST_TO_VECTOR_FLOAT_IMPL(simde_v4u32, v4u32)
SIMDE_MSA_CAST_TO_VECTOR_FLOAT_IMPL(simde_v2i64, v2i64)
SIMDE_MSA_CAST_TO_VECTOR_FLOAT_IMPL(simde_v2u64, v2u64)
SIMDE_MSA_CAST_TO_VECTOR_FLOAT_IMPL(simde_v4f32, v4f32)
SIMDE_MSA_CAST_TO_VECTOR_FLOAT_IMPL(simde_v2f64, v2f64)

#undef SIMDE_MSA_CAST_TO_VECTOR_FLOAT_IMPL


#if !defined(simde_msa_cast_to_vector_float)
  #if defined(__cplusplus)
    SIMDE_FUNCTION_ATTRIBUTES simde_v4f32 simde_msa_cast_to_vector_float(simde_v16i8 a) { return simde_x_msa_cast_to_vector_float_v16i8(a); }
    SIMDE_FUNCTION_ATTRIBUTES simde_v4f32 simde_msa_cast_to_vector_float(simde_v16u8 a) { return simde_x_msa_cast_to_vector_float_v16u8(a); }
    SIMDE_FUNCTION_ATTRIBUTES simde_v4f32 simde_msa_cast_to_vector_float(simde_v8i16 a) { return simde_x_msa_cast_to_vector_float_v8i16(a); }
    SIMDE_FUNCTION_ATTRIBUTES simde_v4f32 simde_msa_cast_to_vector_float(simde_v8u16 a) { return simde_x_msa_cast_to_vector_float_v8u16(a); }
    SIMDE_FUNCTION_ATTRIBUTES simde_v4f32 simde_msa_cast_to_vector_float(simde_v4i32 a) { return simde_x_msa_cast_to_vector_float_v4i32(a); }
    SIMDE_FUNCTION_ATTRIBUTES simde_v4f32 simde_msa_cast_to_vector_float(simde_v4u32 a) { return simde_x_msa_cast_to_vector_float_v4u32(a); }
    SIMDE_FUNCTION_ATTRIBUTES simde_v4f32 simde_msa_cast_to_vector_float(simde_v2i64 a) { return simde_x_msa_cast_to_vector_float_v2i64(a); }
    SIMDE_FUNCTION_ATTRIBUTES simde_v4f32 simde_msa_cast_to_vector_float(simde_v2u64 a) { return simde_x_msa_cast_to_vector_float_v2u64(a); }
    SIMDE_FUNCTION_ATTRIBUTES simde_v4f32 simde_msa_cast_to_vector_float(simde_v4f32 a) { return simde_x_msa_cast_to_vector_float_v4f32(a); }
    SIMDE_FUNCTION_ATTRIBUTES simde_v4f32 simde_msa_cast_to_vector_float(simde_v2f64 a) { return simde_x_msa_cast_to_vector_float_v2f64(a); }
  #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
    #define simde_msa_cast_to_vector_float(a) \
      _Generic((a), \
        simde_v16i8: simde_x_msa_cast_to_vector_float_v16i8, \
        simde_v16u8: simde_x_msa_cast_to_vector_float_v16u8, \
        simde_v8i16: simde_x_msa_cast_to_vector_float_v8i16, \
        simde_v8u16: simde_x_msa_cast_to_vector_float_v8u16, \
        simde_v4i32: simde_x_msa_cast_to_vector_float_v4i32, \
        simde_v4u32: simde_x_msa_cast_to_vector_float_v4u32, \
        simde_v2i64: simde_x_msa_cast_to_vector_float_v2i64, \
        simde_v2u64: simde_x_msa_cast_to_vector_float_v2u64, \
        simde_v4f32: simde_x_msa_cast_to_vector_float_v4f32, \
        simde_v2f64: simde_x_msa_cast_to_vector_float_v2f64  \
      )(a)
  #elif defined(SIMDE_VECTOR_SUBSCRIPT)
    #define simde_msa_cast_to_vector_float(a) HEDLEY_REINTERPRET_CAST(simde_v4f32, (a))
  #else
    #define simde_msa_cast_to_vector_float(a) simde_x_msa_cast_to_vector_float_v4i32(a) 
  #endif
#endif

#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_cast_to_vector_float
  #define __msa_cast_to_vector_float(a) simde_msa_cast_to_vector_float(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
