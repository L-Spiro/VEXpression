#if !defined(SIMDE_MIPS_MSA_FEXDO_H)
#define SIMDE_MIPS_MSA_FEXDO_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4f32
simde_msa_fexdo_h(simde_v8i16 a, simde_v8i16 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fexdo_h(a, b);
  #else
    simde_v8i16_private
      a_ = simde_v8i16_to_private(a),
      b_ = simde_v8i16_to_private(b);
    simde_v4f32_private r_;

    /* Extends the 'down' (right/lower) halves of wt (b) and ws (a) */
    uint16_t tmp[4] = {
      HEDLEY_STATIC_CAST(uint16_t, b_.values[0]),
      HEDLEY_STATIC_CAST(uint16_t, b_.values[1]),
      HEDLEY_STATIC_CAST(uint16_t, a_.values[0]),
      HEDLEY_STATIC_CAST(uint16_t, a_.values[1])
    };

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < 4 ; i++) {
      simde_float16 f16;
      simde_memcpy(&f16, &tmp[i], sizeof(f16));
      r_.values[i] = simde_float16_to_float32(f16);
    }

    return simde_v4f32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fexdo_h
  #define __msa_fexdo_h(a, b) simde_msa_fexdo_h((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2f64
simde_msa_fexdo_w(simde_v4f32 a, simde_v4f32 b) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fexdo_w(a, b);
  #else
    simde_v4f32_private
      a_ = simde_v4f32_to_private(a),
      b_ = simde_v4f32_to_private(b);
    simde_v2f64_private r_;

    r_.values[0] = b_.values[0];
    r_.values[1] = a_.values[0];

    return simde_v2f64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fexdo_w
  #define __msa_fexdo_w(a, b) simde_msa_fexdo_w((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
