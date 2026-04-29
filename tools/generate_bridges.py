import json
import sys

# Whitelist of vector types currently supported by the SimdRegister union
SUPPORTED_VECTORS = {
    "m64", "m128", "m128d", "m128i", 
    "m256", "m256d", "m256i", 
    "m512", "m512d", "m512i", 
    "v128", 
    "int8x8", "int16x4", "int32x2", "int64x1", 
    "uint8x8", "uint16x4", "uint32x2", "uint64x1", 
    "float32x2", "float64x1", 
    "int8x16", "int16x8", "int32x4", "int64x2", 
    "uint8x16", "uint16x8", "uint32x4", "uint64x2", 
    "float32x4", "float64x2"
}

# Substrings of intrinsics that SIMDe does not currently support, implements incorrectly, or require imm8 switch wrapping.
MISSING_IN_SIMDE = [
    "_m_empty",          # Triggers macro parameter errors
    "_round",            # AVX-512 rounding modes missing
    "_aes",              # Missing specific AES/Cryptography features
    "_alignr_epi32",     # Missing specific alignment types
    "_alignr_epi64",
    "_mm512_alignr_epi8",
    "_andn_",
    "_bextr",            # Missing BMI1/BMI2 bit manipulation
    "_bit_scan_",
    "_blsi",
    "_blsmsk",
    "_blsr",
    "_broadcast_i32",    # Missing integer broadcasts
    "_broadcast_i64",
    "_broadcastmb",      # Missing: AVX-512 mask broadcasts
    "_broadcastmw",
    "_bslli_epi128",     # Missing specific bit shifts
    "_bsrli_epi128",
    "_bswap",            
    "_bzhi_",
    "_castf32_u32",      # Missing specific casts
    "_castu32_f32",
    "_clui",             # Missing system/specialty instructions
    "_cpu_feature",      # Missing: CPU feature detection strings
    "_cvtepi16_epi",     # Missing down-casting conversions
    "_cvtepi32_epi", 
    "_cvtepi64_epi", 
    "_cvtepi8_epi",
    "_cvtepi32_pd", 
    "_cvtepi64_pd", 
    "_cvtepi64_ps",
    "_cvtepu16_epi", 
    "_cvtepu32_epi", 
    "_cvtepu64_epi", 
    "_cvtepu8_epi",
    "_cvtepu32_pd", 
    "_cvtepu64_pd", 
    "_cvtepu64_ps",
    "_cvti32_sd",        # Missing specific scalar conversions
    "_cvti32_ss",
    "_cvtness_sbh",      # Missing half-precision (FP16) conversions
    "_cvtpd_epi",        
    "_cvtpd_epu",
    "_cvtpd_ps",
    "_cvtps_epi",
    "_cvtps_epu",
    "_cvtps_pd",
    "_cvtps_ph",
    "_cvtsh_ss",
    "_cvtsbh_ss",
    "_cvtsd_f64",
    "_cvtsd_i32",
    "_cvtsd_u32",
    "_cvtsepi",
    "_cvtsi128_si16",
    "_cvtsi16_si128",
    "_cvtsi512_si32",
    "_cvtss_f32",
    "_cvtss_i32",
    "_cvtss_sh",
    "_cvtss_u32",
    "_cvtepi32lo_pd",
    "_cvtepu32lo_pd",
    "_cvtpslo_pd",
    "_cvttpd_",
    "_cvttps_",
    "_cvttsd_",
    "_cvttss_",
    "_cvtu32_",
    "_cvtusepi",
    "_dpb",              # Missing VNNI Neural Network ops
    "_dpw",              
    "_epi8_mask",        # Missing: AVX-512 mask-returning comparisons (signed)
    "_epi16_mask",
    "_epi32_mask",
    "_epi64_mask",
    "_epu8_mask",        # Missing: AVX-512 mask-returning comparisons (unsigned)
    "_epu16_mask",
    "_epu32_mask",
    "_epu64_mask",
    "_extractf",         # Vector extraction/insertion 
    "_extracti",
    "_free",             # Missing: Memory management macros
    "_insertf",
    "_inserti",
    "_fmaddsub_",        # Missing FMA math variants
    "_fmsubadd_",
    "_get_ssp",          # Missing CET shadow stack instructions
    "_getexp_",
    "_getmant_",
    "_hreset",           
    "_inc_ssp",
    "_incssp",
    "_loadiwkey",        
    "_lrotl",
    "_lrotr",
    "_lzcnt_",           # Missing specific zero-counting/math operations
    "_madd52",
    "_malloc",           # Missing: Memory management macros

    # --- Targeted AVX-512 Mask Exclusions ---
    "_mm256_mask_abs_", "_mm256_maskz_abs_",
    "_mm512_mask_abs_", "_mm512_maskz_abs_",
    "_mask_add_epi8", "_maskz_add_epi8",
    "_mask_add_pd", "_maskz_add_pd",
    "_mask_add_ps", "_maskz_add_ps",
    "_mask_add_sd", "_maskz_add_sd",
    "_mask_adds_epu16", "_maskz_adds_epu16",
    "_mask_adds_epu8", "_maskz_adds_epu8",
    "_mask_and_epi32", "_maskz_and_epi32",
    "_mask_and_epi64", "_maskz_and_epi64",
    "_mask_and_pd", "_maskz_and_pd",
    "_mask_and_ps", "_maskz_and_ps",
    "_mask_andnot_epi32", "_maskz_andnot_epi32",
    "_mask_andnot_epi64", "_maskz_andnot_epi64",
    "_mask_andnot_pd", "_maskz_andnot_pd",
    "_mask_andnot_ps", "_maskz_andnot_ps",
    "_mask_broadcastb_epi8", "_maskz_broadcastb_epi8",
    "_mask_broadcastd_epi32", "_maskz_broadcastd_epi32",
    "_mask_broadcastq_epi64", "_maskz_broadcastq_epi64",
    "_mask_broadcastsd_pd", "_maskz_broadcastsd_pd",
    "_mask_broadcastss_ps", "_maskz_broadcastss_ps",
    "_mask_broadcastw_epi16", "_maskz_broadcastw_epi16",
    "_mask_compress_epi16", "_maskz_compress_epi16",
    "_mask_compress_epi32", "_maskz_compress_epi32",
    "_mask_compress_epi64", "_maskz_compress_epi64",
    "_mask_compress_epi8", "_maskz_compress_epi8",
    "_mask_compress_pd", "_maskz_compress_pd",
    "_mask_compress_ps", "_maskz_compress_ps",
    "_mask_cvtepi32_ps", "_maskz_cvtepi32_ps",
    "_mask_cvtepu32_ps", "_maskz_cvtepu32_ps",
    "_mask_cvtph_ps", "_maskz_cvtph_ps",
    "_mask_cvtsd_ss", "_maskz_cvtsd_ss",
    "_mask_cvtss_sd", "_maskz_cvtss_sd",
    "_mask_div_pd", "_maskz_div_pd",
    "_mask_div_ps", "_maskz_div_ps",
    "_mask_div_sd", "_maskz_div_sd",
    "_mask_div_ss", "_maskz_div_ss",
    "_mask_expand_epi16", "_maskz_expand_epi16",
    "_mask_expand_epi32", "_maskz_expand_epi32",
    "_mask_expand_epi64", "_maskz_expand_epi64",
    "_mask_expand_epi8", "_maskz_expand_epi8",
    "_mask_expand_pd", "_maskz_expand_pd",
    "_mask_expand_ps", "_maskz_expand_ps",
    "_mask_fmadd_pd", "_mask3_fmadd_pd", "_maskz_fmadd_pd",
    "_mask_fmadd_ps", "_mask3_fmadd_ps", "_maskz_fmadd_ps",
    "_mask_fmadd_sd", "_mask3_fmadd_sd", "_maskz_fmadd_sd",
    "_mask_fmadd_ss", "_mask3_fmadd_ss", "_maskz_fmadd_ss",
    "_mask_fmsub_pd", "_mask3_fmsub_pd", "_maskz_fmsub_pd",
    "_mask_fmsub_ps", "_mask3_fmsub_ps", "_maskz_fmsub_ps",
    "_mask_fmsub_sd", "_mask3_fmsub_sd", "_maskz_fmsub_sd",
    "_mask_fmsub_ss", "_mask3_fmsub_ss", "_maskz_fmsub_ss",
    "_mask_fnmadd_pd", "_mask3_fnmadd_pd", "_maskz_fnmadd_pd",
    "_mask_fnmadd_ps", "_mask3_fnmadd_ps", "_maskz_fnmadd_ps",
    "_mask_fnmadd_sd", "_mask3_fnmadd_sd", "_maskz_fnmadd_sd",
    "_mask_fnmadd_ss", "_mask3_fnmadd_ss", "_maskz_fnmadd_ss",
    "_mask_fnmsub_pd", "_mask3_fnmsub_pd", "_maskz_fnmsub_pd",
    "_mask_fnmsub_ps", "_mask3_fnmsub_ps", "_maskz_fnmsub_ps",
    "_mask_fnmsub_sd", "_mask3_fnmsub_sd", "_maskz_fnmsub_sd",
    "_mask_fnmsub_ss", "_mask3_fnmsub_ss", "_maskz_fnmsub_ss",
    "_mask_max_epi16", "_maskz_max_epi16",
    "_mask_max_epi32", "_maskz_max_epi32",
    "_mask_max_epi8", "_maskz_max_epi8",
    "_mask_max_epu16", "_maskz_max_epu16",
    "_mask_max_epu32", "_maskz_max_epu32",
    "_mask_max_epu8", "_maskz_max_epu8",
    "_mask_max_pd", "_maskz_max_pd",
    "_mask_max_ps", "_maskz_max_ps",
    "_mask_max_sd", "_maskz_max_sd",
    "_mask_max_ss", "_maskz_max_ss",
    "_mask_min_epi16", "_maskz_min_epi16",
    "_mask_min_epi32", "_maskz_min_epi32",
    "_mask_min_epi8", "_maskz_min_epi8",
    "_mask_min_epu16", "_maskz_min_epu16",
    "_mask_min_epu32", "_maskz_min_epu32",
    "_mask_min_epu8", "_maskz_min_epu8",
    "_mask_min_pd", "_maskz_min_pd",
    "_mask_min_ps", "_maskz_min_ps",
    "_mask_min_sd", "_maskz_min_sd",
    "_mask_min_ss", "_maskz_min_ss",
    "_mask_move_sd", "_maskz_move_sd",
    "_mask_move_ss", "_maskz_move_ss",
    "_mask_mul_epi32", "_maskz_mul_epi32",
    "_mask_mul_epu32", "_maskz_mul_epu32",
    "_mask_mul_pd", "_maskz_mul_pd",
    "_mask_mul_ps", "_maskz_mul_ps",
    "_mask_mul_sd", "_maskz_mul_sd",
    "_mask_mul_ss", "_maskz_mul_ss",
    "_mask_mulhi_epi16", "_maskz_mulhi_epi16",
    "_mask_mulhrs_epi16", "_maskz_mulhrs_epi16",
    "_mask_mullo_epi16", "_maskz_mullo_epi16",
    "_mask_mullo_epi32", "_maskz_mullo_epi32",
    "_mask_or_pd", "_maskz_or_pd",
    "_mask_or_ps", "_maskz_or_ps",
    "_mask_packs_epi16", "_maskz_packs_epi16",
    "_mask_packs_epi32", "_maskz_packs_epi32",
    "_mask_packus_epi16", "_maskz_packus_epi16",
    "_mask_packus_epi32", "_maskz_packus_epi32",
    "_mask_set1_epi16", "_maskz_set1_epi16",
    "_mask_set1_epi32", "_maskz_set1_epi32",
    "_mask_set1_epi64", "_maskz_set1_epi64",
    "_mask_set1_epi8", "_maskz_set1_epi8",
    "_mask_shuffle_epi8", "_maskz_shuffle_epi8",
    "_mask_sll_epi16", "_maskz_sll_epi16",
    "_mask_sll_epi32", "_maskz_sll_epi32",
    "_mask_sll_epi64", "_maskz_sll_epi64",
    "_mask_sllv_epi32", "_maskz_sllv_epi32",
    "_mask_sllv_epi64", "_maskz_sllv_epi64",
    "_mask_sqrt_pd", "_maskz_sqrt_pd",
    "_mask_sqrt_ps", "_maskz_sqrt_ps",
    "_mask_sqrt_sd", "_maskz_sqrt_sd",
    "_mask_sqrt_ss", "_maskz_sqrt_ss",
    "_mask_sra_epi16", "_maskz_sra_epi16",
    "_mask_sra_epi32", "_maskz_sra_epi32",
    "_mask_srl_epi16", "_maskz_srl_epi16",
    "_mask_srl_epi32", "_maskz_srl_epi32",
    "_mask_srl_epi64", "_maskz_srl_epi64",
    "_mask_srlv_epi16", "_maskz_srlv_epi16",
    "_mask_srlv_epi32", "_maskz_srlv_epi32",
    "_mask_srlv_epi64", "_maskz_srlv_epi64",
    "_mask_sub_epi16", "_maskz_sub_epi16",
    "_mask_sub_epi32", "_maskz_sub_epi32",
    "_mask_sub_epi64", "_maskz_sub_epi64",
    "_mask_sub_epi8", "_maskz_sub_epi8",
    "_mm_mask_sub_ps", "_mm_maskz_sub_ps",
    "_mm256_mask_sub_ps", "_mm256_maskz_sub_ps",
    "_mm_mask_sub_sd", "_mm_maskz_sub_sd",
    "_mm_mask_sub_ss", "_mm_maskz_sub_ss",
    "_mask_sub_pd", "_maskz_sub_pd",
    "_mask_subs_epi16", "_maskz_subs_epi16",
    "_mask_subs_epi8", "_maskz_subs_epi8",
    "_mask_subs_epu16", "_maskz_subs_epu16",
    "_mask_subs_epu8", "_maskz_subs_epu8",
    "_mask_xor_pd", "_maskz_xor_pd",
    "_mask_xor_ps", "_maskz_xor_ps",

    # --- K-Mask Logical / Conversions ---
    "_int2mask", "_mask2int", "_kadd", "_kand", "_kandn", "_kmov",
    "_knot", "_kor", "_ktest", "_kunpack", "_kxnor", "_kxor",
    
    # --- System / Hardware / Non-SIMD Specific ---
    "_castf64_u64", "_castu64_f64",
    "_rdpmc", "_rdsspq_i64", "_rdtsc",
    "_senduipi", "_tpause", "_umwait",
    "_urdmsr", "_uwrmsr", "_xgetbv", "_xsetbv",

    # --- Specific type casts missing in SIMDe ---
    "_cvtmask", "_cvtu64_", "_cvti64_", "_cvtsd_i64", "_cvtsd_u64", "_cvtss_i64", "_cvtss_u64",

    "_max_epi64", "_max_epu64",
    "_may_i_use_",       # Missing: CPU feature detection macros
    "_min_epi64", "_min_epu64",
    "_MM_GET_",          # Missing: MXCSR State macros
    "_MM_SET_",          
    "_MM_TRANSPOSE",     # Missing: Matrix Transpose macros
    "_movedup_pd",       # Missing AVX-512 specific moves and duplications
    "_movehdup_ps", "_moveldup_ps",
    "_mulhi_epu16",      # Missing specific integer multiplications
    "_mullo_epi64", "_mullox_epi64",
    "_mwait",            # Missing OS/System instructions
    "_or_epi32",         # Intel doesn't natively have _mm_or_epi32/64, aliases missing
    "_or_epi64",
    "_pd_mask",          # Missing: AVX-512 float/double mask comparisons
    "_ps_mask",
    "_pdep_",
    "_permute_pd",       # Missing AVX-512 permutations
    "_permute_ps", "_permutevar_", "_permutex_",
    "_pext_", "_popcnt", "_ptwrite",
    "_rcp14_",           # Missing AVX-512 approximations (RCP14)
    "_rdpid", "_rdsspd", "_readfsbase", "_readgsbase",
    "_reduce_",          # Missing AVX-512 horizontal reduction operations
    "_rotl", "_rotr", "_rotwl", "_rotwr",
    "_rsqrt14_", "_saveprevssp", "_serialize", "_setssbsy",
    "_sha1",             # Missing specific Cryptography ops
    "_sha256", "_sha512",           
    "_shldi_", "_shldv_", "_shrdi_", "_shrdv_",
    "_mm512_shuffle_epi32", "_mm512_shufflehi_epi16", "_mm512_shufflelo_epi16",
    "_sllv_epi16", "_sm3", "_sm4",              
    "_sra_epi64", "_srai_epi64", "_srav_",
    "_mm512_sra_", "_mm512_srai_",
    "_stui", "_testui",
    "_tile_",            # Missing: AMX Tile ops
    "_tzcnt", "_undefined", "_wbinvd", "_wbnoinvd",
    "_writefsbase", "_writegsbase",
    "_xbegin",           # Missing TSX transactional memory instructions
    "_xend", "_xor_epi32", "_xor_epi64",
    "_xresldtrk", "_xsusldtrk", "_xtest",
    "_zeroall",          # Missing: AVX State clearing
    "_zeroupper", "_zext"
]

def getBaseType(rawType):
    """Strips const, volatile, and pointer asterisks to get the base type."""
    base = rawType.replace("const", "").replace("volatile", "").strip()
    base = base.rstrip("*").strip()
    
    # Translate specific MSVC datatypes into stdint implementations
    base = base.replace("unsigned __int64", "uint64_t")
    base = base.replace("__int64", "int64_t")
    base = base.replace("__int32", "int32_t")
    base = base.replace("__int16", "int16_t")
    base = base.replace("__int8", "int8_t")
    
    return base

def isPointer(rawType):
    return "*" in rawType

def isSimdVector(baseType):
    """Determines if a type is a true SIMD vector vs a scalar/mask."""
    b = baseType.lower()
    if "mmask" in b: return False
    if b in ["int64_t", "uint64_t", "int32_t", "uint32_t", "int16_t", "uint16_t", "int8_t", "uint8_t", "float", "double", "int", "unsigned int", "long long"]: return False
    if b.startswith("__m"): return True
    if "128" in b or "256" in b or "512" in b: return True
    if b == "m64": return True
    if "x" in b: return True
    return False

def getEngineDataType(rawType):
    """Maps intrinsic C types to the engine's DataType enum."""
    if isPointer(rawType):
        return "DataType::Any"
    
    base = getBaseType(rawType)
    
    if isSimdVector(base):
        return "DataType::Any"
    
    if "double" in base:
        return "DataType::Double"
    if "float" in base:
        return "DataType::Float"
    if "int64" in base or "long long" in base:
        return "DataType::Int64"
    if "uint64" in base:
        return "DataType::UInt64"
    
    return "DataType::Int32"

def escapeCppString(s):
    """Escapes strings to safely insert them into C++ string literals."""
    if not s:
        return ""
    s = s.replace('\\', '\\\\')
    s = s.replace('"', '\\"')
    s = s.replace('\n', '\\n')
    s = s.replace('\t', '\\t')
    s = s.replace('\r', '')
    return s

def generateBridgeCode(intrinsicJson, bridge_counts, desc_counts):
    sig = intrinsicJson.get("signature", {})
    name = sig.get("name", "")
    rettype = sig.get("rettype", "void")
    params = sig.get("params", [])
    
    # Check for empty/void parameter lists
    if len(params) == 1 and params[0].get("type", "").strip() == "void":
        params = []
    
    rawDesc = intrinsicJson.get("description", "")
    rawOp = intrinsicJson.get("operation", "")
    
    if not name:
        return "", "", ""

    # Generate unique camelCase bridge name with suffix
    base_bridge_name = f"bridge{name.replace('_', ' ').title().replace(' ', '')}"
    base_bridge_name = base_bridge_name[:6] + base_bridge_name[6].upper() + base_bridge_name[7:]
    
    b_count = bridge_counts.get(base_bridge_name, 0) + 1
    bridge_counts[base_bridge_name] = b_count
    bridgeFuncName = f"{base_bridge_name}_{b_count}" if b_count > 1 else base_bridge_name

    # Generate unique String ID with suffix
    base_desc_id = "Desc_" + name.lstrip('_').replace('__', '_')
    d_count = desc_counts.get(base_desc_id, 0) + 1
    desc_counts[base_desc_id] = d_count
    descId = f"{base_desc_id}_{d_count}" if d_count > 1 else base_desc_id
    
    descText = escapeCppString(rawDesc)
    if rawOp:
        descText += "\\n\\n" + escapeCppString(rawOp)
        
    descEntry = f'VE_STR1({descId}, "{descText}")'

    unimplemented = False
    unimplemented_reason = ""

    # 1. Catch missing SIMDe implementations early
    if any(m in name for m in MISSING_IN_SIMDE) or name == "_mm512_setzero":
        unimplemented = True
        unimplemented_reason = "Intrinsic is currently missing or broken in SIMDe."

    # 2. Check return type for unsupported engine features early
    baseRet = getBaseType(rettype)
    is_simd_return = isSimdVector(baseRet)
    retUnionMember = ""
    if is_simd_return:
        retUnionMember = baseRet.replace("__", "").replace("_t", "")
        if retUnionMember not in SUPPORTED_VECTORS:
            unimplemented = True
            unimplemented_reason = f"Unsupported SIMD return type '{rettype}'."

    # 3. Check parameter types for unsupported features
    for param in params:
        pType = param.get("type", "int")
        pName = param.get("name", "arg").lower()
        baseType = getBaseType(pType)
        isPtr = isPointer(pType)
        is_vector = isSimdVector(baseType)
        unionMember = baseType.replace("__", "").replace("_t", "") if is_vector else ""

        if isPtr:
            unimplemented = True
            unimplemented_reason = f"Pointer parameter extraction not implemented for '{pType}'."
        elif is_vector and unionMember not in SUPPORTED_VECTORS:
            unimplemented = True
            unimplemented_reason = f"Unsupported SIMD vector parameter type '{pType}'."
        elif "imm" in pName:
            unimplemented = True
            unimplemented_reason = f"Requires compile-time constant for parameter '{pName}'."

    cppCode = ""
    if unimplemented:
        cppCode += f"\t\t#if 0 // TODO: {unimplemented_reason}\n"

    cppCode += f"\t\t/**\n"
    cppCode += f"\t\t * Bridge for {name}.\n"
    cppCode += f"\t\t *\n"
    cppCode += f"\t\t * \\param context\t\tThe execution context containing variables and runtime states.\n"
    cppCode += f"\t\t * \\param args\t\t\tThe list of arguments passed to the intrinsic.\n"
    cppCode += f"\t\t * \\return\t\t\t\tReturns the result of the intrinsic, or an invalid Result on failure.\n"
    cppCode += f"\t\t **/\n"
    cppCode += f"\t\tstatic Result {bridgeFuncName}(ExecutionContext* context, const std::vector<Result>& args) {{\n"
    
    if params:
        cppCode += f"\t\t\tif (args.size() != {len(params)}) {{\n\t\t\t\treturn Result{{}};\n\t\t\t}}\n\n"

    callArgs = []
    tableParams = []

    for i, param in enumerate(params):
        pName = param.get("name", f"arg{i}")
        if not pName:
            pName = f"arg{i}"
            
        pType = param.get("type", "int")
        baseType = getBaseType(pType)
        isPtr = isPointer(pType)
        
        # Build Table Definition Parameter
        engineDataType = getEngineDataType(pType)
        tableParams.append(f"{{ {engineDataType}, \"{pName}\", StringId::None }}")

        is_vector = isSimdVector(baseType)
        unionMember = baseType.replace("__", "").replace("_t", "") if is_vector else ""

        if isPtr:
            cppCode += f"\t\t\t{baseType}* {pName} = nullptr; // Pointer logic required\n"
        elif is_vector:
            enumType = f"Simd_{unionMember}"
            simdeType = baseType.replace("__", "simde__") if baseType.startswith("__") else f"simde_{baseType}"
            
            cppCode += f"\t\t\tif (args[{i}].type != NumericConstant::Object || !args[{i}].value.objectVal || !(args[{i}].value.objectVal->type() & BuiltInType_Simd)) {{\n"
            cppCode += f"\t\t\t\treturn Result{{}};\n"
            cppCode += f"\t\t\t}}\n"
            cppCode += f"\t\t\tSimdObject* simdArg{i} = static_cast<SimdObject*>(args[{i}].value.objectVal);\n"
            cppCode += f"\t\t\tif (simdArg{i}->regType != {enumType}) {{\n"
            cppCode += f"\t\t\t\treturn Result{{}};\n"
            cppCode += f"\t\t\t}}\n"
            cppCode += f"\t\t\t{simdeType} {pName} = simdArg{i}->reg.{unionMember};\n"
        else:
            extractCast = "intVal"
            if "float" in baseType or "double" in baseType:
                extractCast = "doubleVal"
            elif "unsigned" in baseType or "uint" in baseType or "mask" in baseType:
                extractCast = "uintVal"

            castType = baseType.replace("__", "simde__") if baseType.startswith("__") else baseType

            cppCode += f"\t\t\tResult castedArg{i} = context->castArgument(args[{i}], {engineDataType});\n"
            cppCode += f"\t\t\tif (castedArg{i}.type == NumericConstant::Invalid) {{\n"
            cppCode += f"\t\t\t\treturn Result{{}};\n"
            cppCode += f"\t\t\t}}\n"
            cppCode += f"\t\t\t{castType} {pName} = static_cast<{castType}>(castedArg{i}.value.{extractCast});\n"
        
        callArgs.append(pName)
        cppCode += "\n"

    simdeName = name.replace("_mm", "simde_mm") if name.startswith("_mm") else "simde" + name
    callString = f"{simdeName}({', '.join(callArgs)})"
    
    if rettype == "void":
        cppCode += f"\t\t\t{callString};\n"
        cppCode += f"\t\t\treturn Result{{}};\n"
    elif is_simd_return:
        enumType = f"Simd_{retUnionMember}"
        cppCode += f"\t\t\tSimdObject* outObj = context->allocateObject<SimdObject>();\n"
        cppCode += f"\t\t\tif (!outObj) {{\n"
        cppCode += f"\t\t\t\treturn Result{{}};\n"
        cppCode += f"\t\t\t}}\n"
        cppCode += f"\t\t\toutObj->regType = {enumType};\n"
        cppCode += f"\t\t\toutObj->reg.{retUnionMember} = {callString};\n"
        cppCode += f"\t\t\treturn outObj->createResult();\n"
    else:
        cppCode += f"\t\t\treturn Result::make(static_cast<int64_t>({callString}));\n"
            
    cppCode += f"\t\t}}\n"
    
    if unimplemented:
        cppCode += f"\t\t#endif\n"
    cppCode += "\n"

    paramString = f"{{ {', '.join(tableParams)} }}" if tableParams else "{}"
    tableEntry = f'\t\t{{ "{name}", StringId::{descId}, {paramString}, SimdBridges::{bridgeFuncName} }},'
    
    # Comment out the table entry if we flagged it as unimplemented
    if unimplemented:
        tableEntry = f'\t\t// {tableEntry.strip()}'
    
    return cppCode, tableEntry, descEntry

def main():
    if len(sys.argv) < 2:
        print("Usage: python generate_bridges.py <path_to_json>")
        return

    jsonPath = sys.argv[1]
    with open(jsonPath, 'r') as f:
        data = json.load(f)

    allBridges = []
    allTableEntries = []
    allDescriptions = []
    
    bridge_counts = {}
    desc_counts = {}

    for instructionSet, intrinsics in data.items():
        allBridges.append(f"\t\t// =========================================================================\n\t\t// {instructionSet}\n\t\t// =========================================================================")
        allTableEntries.append(f"\t\t// {instructionSet}")
        allDescriptions.append(f"// =========================================================================\n// {instructionSet}\n// =========================================================================")
        
        for intrinsic in intrinsics:
            bridgeCode, tableEntry, descEntry = generateBridgeCode(intrinsic, bridge_counts, desc_counts)
            if bridgeCode:
                allBridges.append(bridgeCode)
                allTableEntries.append(tableEntry)
                allDescriptions.append(descEntry)

    # Write Bridges Wrapper
    with open("SimdBridges.h", "w", encoding="utf-8") as f:
        f.write("#pragma once\n\n")
        f.write("#include \"SimdObject.h\"\n")
        f.write("#include \"../Engine/ExecutionContext.h\"\n")
        f.write("#include <vector>\n\n")
        f.write("namespace ve {\n\n")
        f.write("\tclass SimdBridges {\n")
        f.write("\tpublic :\n")
        f.write("\n".join(allBridges))
        f.write("\t};\n\n")
        f.write("} // namespace ve\n")

    # Write Registration Table
    with open("SimdBridgeTable.inl", "w", encoding="utf-8") as f:
        f.write("\n".join(allTableEntries))
        f.write("\n")
        
    # Write Strings/Descriptions
    with open("SimdDescriptions.inl", "w", encoding="utf-8") as f:
        f.write("\n".join(allDescriptions))
        f.write("\n")

    print(f"Successfully generated bindings for {sum(bridge_counts.values())} distinct intrinsic overloads.")

if __name__ == "__main__":
    main()