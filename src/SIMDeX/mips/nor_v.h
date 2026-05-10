#if !defined(SIMDE_MIPS_MSA_NOR_V_H)
#define SIMDE_MIPS_MSA_NOR_V_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16u8
simde_msa_nor_v(simde_v16u8 a, simde_v16u8 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_nor_v(a, b);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vmvnq_u8(vorrq_u8(a, b));
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_andnot_si128(_mm_or_si128(a, b), _mm_set1_epi32(~0));
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_v128_not(wasm_v128_or(a, b));
  #else
    simde_v16u8_private
      a_ = simde_v16u8_to_private(a),
      b_ = simde_v16u8_to_private(b),
      r_;

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = ~(a_.values | b_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = ~(a_.values[i] | b_.values[i]);
      }
    #endif

    return simde_v16u8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_nor_v
  #define __msa_nor_v(a, b) simde_msa_nor_v((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
