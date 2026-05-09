#if !defined(SIMDE_MIPS_MSA_BSEL_V_H)
#define SIMDE_MIPS_MSA_BSEL_V_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v16u8
simde_msa_bsel_v(simde_v16u8 a, simde_v16u8 b, simde_v16u8 c) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_bsel_v(a, b, c);
  #elif defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vbslq_u8(a, c, b);
  #elif defined(SIMDE_POWER_ALTIVEC_P6_NATIVE)
    return vec_sel(b, c, a);
  #else
    simde_v16u8_private
      r_,
      a_ = simde_v16u8_to_private(a),
      b_ = simde_v16u8_to_private(b),
      c_ = simde_v16u8_to_private(c);

    #if defined(SIMDE_X86_SSE2_NATIVE)
      r_.m128i = _mm_or_si128(_mm_and_si128(a_.m128i, c_.m128i), _mm_andnot_si128(a_.m128i, b_.m128i));
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.v128 = wasm_v128_bitselect(c_.v128, b_.v128, a_.v128);
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR)
      r_.values = (a_.values & c_.values) | (~a_.values & b_.values);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = (a_.values[i] & c_.values[i]) | (~a_.values[i] & b_.values[i]);
      }
    #endif

    return simde_v16u8_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_bsel_v
  #define __msa_bsel_v(a, b, c) simde_msa_bsel_v((a), (b), (c))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
