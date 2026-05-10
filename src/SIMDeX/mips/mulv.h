#if !defined(SIMDE_MIPS_MSA_MULV_H)
#define SIMDE_MIPS_MSA_MULV_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_mulv_b(simde_v16i8 a, simde_v16i8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_mulv_b(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vmulq_s8(a, b);
  #else
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      b_ = simde_v16i8_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = a_.values * b_.values;
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = a_.values[i] * b_.values[i];
      }
    #endif

    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_mulv_b
  #define __msa_mulv_b(a, b) simde_msa_mulv_b((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_mulv_h(simde_v8i16 a, simde_v8i16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_mulv_h(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vmulq_s16(a, b);
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_mullo_epi16(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i16x8_mul(a, b);
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = a_.values * b_.values;
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = a_.values[i] * b_.values[i];
      }
    #endif

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_mulv_h
  #define __msa_mulv_h(a, b) simde_msa_mulv_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_mulv_w(simde_v4i32 a, simde_v4i32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_mulv_w(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vmulq_s32(a, b);
  #elif defined(SIMDE_X86_SSE4_1_NATIVE)
    return _mm_mullo_epi32(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i32x4_mul(a, b);
  #else
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = a_.values * b_.values;
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = a_.values[i] * b_.values[i];
      }
    #endif

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_mulv_w
  #define __msa_mulv_w(a, b) simde_msa_mulv_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_mulv_d(simde_v2i64 a, simde_v2i64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_mulv_d(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i64x2_mul(a, b);
  #else
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      b_ = simde_v2i64_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = a_.values * b_.values;
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = a_.values[i] * b_.values[i];
      }
    #endif

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_mulv_d
  #define __msa_mulv_d(a, b) simde_msa_mulv_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
