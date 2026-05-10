#if !defined(SIMDE_MIPS_MSA_FCLASS_H)
#define SIMDE_MIPS_MSA_FCLASS_H

#include <simde/mips/msa/types.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_v4i32
simde_msa_fclass_w(simde_v4f32 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fclass_w(a);
  #else
    simde_v4f32_private a_ = simde_v4f32_to_private(a);
    simde_v4i32_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint32_t u;
      simde_memcpy(&u, &a_.values[i], sizeof(u));
      
      uint32_t sign = u >> 31;
      uint32_t exp = (u >> 23) & 0xFF;
      uint32_t frac = u & 0x7FFFFF;
      int32_t cls = 0;
      
      if (exp == 0xFF) {
        if (frac == 0) { 
          cls = sign ? (1 << 2) : (1 << 9); 
        } else { 
          /* MSA enforces NAN2008: QNaN MSB is 1, SNaN MSB is 0 */
          cls = (frac & 0x400000) ? (1 << 1) : (1 << 0); 
        }
      } else if (exp == 0) {
        if (frac == 0) { 
          cls = sign ? (1 << 5) : (1 << 6); 
        } else { 
          cls = sign ? (1 << 4) : (1 << 7); 
        }
      } else {
        cls = sign ? (1 << 3) : (1 << 8);
      }
      
      r_.values[i] = cls;
    }

    return simde_v4i32_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fclass_w
  #define __msa_fclass_w(a) simde_msa_fclass_w(a)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_v2i64
simde_msa_fclass_d(simde_v2f64 a) {
  #if defined(SIMDE_MIPS_MSA_NATIVE)
    return __msa_fclass_d(a);
  #else
    simde_v2f64_private a_ = simde_v2f64_to_private(a);
    simde_v2i64_private r_;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      uint64_t u;
      simde_memcpy(&u, &a_.values[i], sizeof(u));
      
      uint32_t sign = u >> 63;
      uint32_t exp = (u >> 52) & 0x7FF;
      uint64_t frac = u & 0xFFFFFFFFFFFFF;
      int64_t cls = 0;
      
      if (exp == 0x7FF) {
        if (frac == 0) { 
          cls = sign ? (1 << 2) : (1 << 9); 
        } else { 
          cls = (frac & 0x8000000000000ULL) ? (1 << 1) : (1 << 0); 
        }
      } else if (exp == 0) {
        if (frac == 0) { 
          cls = sign ? (1 << 5) : (1 << 6); 
        } else { 
          cls = sign ? (1 << 4) : (1 << 7); 
        }
      } else {
        cls = sign ? (1 << 3) : (1 << 8);
      }
      
      r_.values[i] = cls;
    }

    return simde_v2i64_from_private(r_);
  #endif
}
#if defined(SIMDE_MIPS_MSA_ENABLE_NATIVE_ALIASES)
  #undef __msa_fclass_d
  #define __msa_fclass_d(a) simde_msa_fclass_d(a)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif
