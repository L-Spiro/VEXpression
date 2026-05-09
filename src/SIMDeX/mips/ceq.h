#if !defined(SIMDE_MIPS_MSA_CEQ_H)
#define SIMDE_MIPS_MSA_CEQ_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16i8
simde_msa_ceq_b(simde_v16i8 a, simde_v16i8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ceq_b(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vreinterpretq_s8_u8(vceqq_s8(a, b));
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_cmpeq_epi8(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i8x16_eq(a, b);
  #elif defined(SIMDE_POWER_ALTIVEC_P6_NATIVE)
    return HEDLEY_REINTERPRET_CAST(SIMDE_POWER_ALTIVEC_VECTOR(signed char), vec_cmpeq(a, b));
  #else
    simde_v16i8_private
      a_ = simde_v16i8_to_private(a),
      b_ = simde_v16i8_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = HEDLEY_REINTERPRET_CAST(__typeof__(r_.values), (a_.values == b_.values));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] == b_.values[i]) ? ~HEDLEY_STATIC_CAST(int8_t, 0) : 0;
      }
    #endif

    return simde_v16i8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ceq_b
  #define __msa_ceq_b(a, b) simde_msa_ceq_b((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v8i16
simde_msa_ceq_h(simde_v8i16 a, simde_v8i16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ceq_h(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vreinterpretq_s16_u16(vceqq_s16(a, b));
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_cmpeq_epi16(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i16x8_eq(a, b);
  #elif defined(SIMDE_POWER_ALTIVEC_P6_NATIVE)
    return HEDLEY_REINTERPRET_CAST(SIMDE_POWER_ALTIVEC_VECTOR(signed short), vec_cmpeq(a, b));
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = HEDLEY_REINTERPRET_CAST(__typeof__(r_.values), (a_.values == b_.values));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] == b_.values[i]) ? ~HEDLEY_STATIC_CAST(int16_t, 0) : 0;
      }
    #endif

    return simde_v8i16_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ceq_h
  #define __msa_ceq_h(a, b) simde_msa_ceq_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_ceq_w(simde_v4i32 a, simde_v4i32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ceq_w(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vreinterpretq_s32_u32(vceqq_s32(a, b));
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_cmpeq_epi32(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i32x4_eq(a, b);
  #elif defined(SIMDE_POWER_ALTIVEC_P6_NATIVE)
    return HEDLEY_REINTERPRET_CAST(SIMDE_POWER_ALTIVEC_VECTOR(signed int), vec_cmpeq(a, b));
  #else
    simde_v4i32_private
      a_ = simde_v4i32_to_private(a),
      b_ = simde_v4i32_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = HEDLEY_REINTERPRET_CAST(__typeof__(r_.values), (a_.values == b_.values));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] == b_.values[i]) ? ~HEDLEY_STATIC_CAST(int32_t, 0) : 0;
      }
    #endif

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ceq_w
  #define __msa_ceq_w(a, b) simde_msa_ceq_w((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_ceq_d(simde_v2i64 a, simde_v2i64 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_ceq_d(a, b);
  #elif defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vreinterpretq_s64_u64(vceqq_s64(a, b));
  #elif defined(SIMDE_X86_SSE4_1_NATIVE)
    return _mm_cmpeq_epi64(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i64x2_eq(a, b);
  #elif defined(SIMDE_POWER_ALTIVEC_P8_NATIVE)
    return HEDLEY_REINTERPRET_CAST(SIMDE_POWER_ALTIVEC_VECTOR(signed long long), vec_cmpeq(a, b));
  #else
    simde_v2i64_private
      a_ = simde_v2i64_to_private(a),
      b_ = simde_v2i64_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = HEDLEY_REINTERPRET_CAST(__typeof__(r_.values), (a_.values == b_.values));
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] == b_.values[i]) ? ~HEDLEY_STATIC_CAST(int64_t, 0) : 0;
      }
    #endif

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_ceq_d
  #define __msa_ceq_d(a, b) simde_msa_ceq_d((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
