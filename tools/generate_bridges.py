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
    "_max_epi64",
    "_max_epu64",
    "_may_i_use_",       # Missing: CPU feature detection macros
    "_min_epi64",
    "_min_epu64",
    "_MM_GET_",          # Missing: MXCSR State macros
    "_MM_SET_",          
    "_MM_TRANSPOSE",     # Missing: Matrix Transpose macros
    "_movedup_pd",       # Missing AVX-512 specific moves and duplications
    "_movehdup_ps",
    "_moveldup_ps",
    "_mulhi_epu16",      # Missing specific integer multiplications
    "_mullo_epi64",
    "_mullox_epi64",
    "_mwait",            # Missing OS/System instructions
    "_or_epi32",         # Intel doesn't natively have _mm_or_epi32/64, aliases missing
    "_or_epi64",
    "_pdep_",
    "_permute_pd",       # Missing AVX-512 permutations
    "_permute_ps",
    "_permutevar_",
    "_permutex_",
    "_pext_",
    "_popcnt",
    "_ptwrite",
    "_rcp14_",           # Missing AVX-512 approximations (RCP14)
    "_rdpid",
    "_rdsspd",
    "_readfsbase",
    "_readgsbase",
    "_reduce_",          # Missing AVX-512 horizontal reduction operations
    "_rotl",
    "_rotr",
    "_rotwl",
    "_rotwr",
    "_rsqrt14_",
    "_saveprevssp",
    "_serialize",
    "_setssbsy",
    "_sha1",             # Missing specific Cryptography ops
    "_sha256",
    "_sha512",           
    "_shldi_",
    "_shldv_",
    "_shrdi_",
    "_shrdv_",
    "_mm512_shuffle_epi32",
    "_mm512_shufflehi_epi16",
    "_mm512_shufflelo_epi16",
    "_sllv_epi16",
    "_sm3",              
    "_sm4",              
    "_sra_epi64",
    "_srai_epi64",
    "_srav_",
    "_mm512_sra_",
    "_mm512_srai_",
    "_stui",
    "_testui",
    "_tile_",            # Missing: AMX Tile ops
    "_tzcnt",
    "_undefined",
    "_wbinvd",
    "_wbnoinvd",
    "_writefsbase",
    "_writegsbase",
    "_xbegin",           # Missing TSX transactional memory instructions
    "_xend",
    "_xor_epi32",
    "_xor_epi64",
    "_xresldtrk",
    "_xsusldtrk",
    "_xtest",
    "_zeroall",          # Missing: AVX State clearing
    "_zeroupper",        
    "_zext"
]

def getBaseType(rawType):
    """Strips const, volatile, and pointer asterisks to get the base type."""
    base = rawType.replace("const", "").replace("volatile", "").strip()
    return base.rstrip("*").strip()

def isPointer(rawType):
    return "*" in rawType

def getEngineDataType(rawType):
    """Maps intrinsic C types to the engine's DataType enum."""
    if isPointer(rawType):
        return "DataType::Any"
    
    base = getBaseType(rawType)
    
    if base.startswith("__m") or "128" in base or "256" in base or "512" in base or "64" in base or "x" in base:
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
    is_simd_return = baseRet.startswith("__m") or "128" in baseRet or "256" in baseRet or "512" in baseRet or "64" in baseRet or "x" in baseRet
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
        is_vector = baseType.startswith("__m") or "128" in baseType or "256" in baseType or "512" in baseType or "64" in baseType or "x" in baseType
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

        is_vector = baseType.startswith("__m") or "128" in baseType or "256" in baseType or "512" in baseType or "64" in baseType or "x" in baseType
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

            cppCode += f"\t\t\tResult castedArg{i} = context->castArgument(args[{i}], {engineDataType});\n"
            cppCode += f"\t\t\tif (castedArg{i}.type == NumericConstant::Invalid) {{\n"
            cppCode += f"\t\t\t\treturn Result{{}};\n"
            cppCode += f"\t\t\t}}\n"
            cppCode += f"\t\t\t{baseType} {pName} = static_cast<{baseType}>(castedArg{i}.value.{extractCast});\n"
        
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
    with open("SimdBridgeTable.inc", "w", encoding="utf-8") as f:
        f.write("\n".join(allTableEntries))
        f.write("\n")
        
    # Write Strings/Descriptions
    with open("SimdDescriptions.inl", "w", encoding="utf-8") as f:
        f.write("\n".join(allDescriptions))
        f.write("\n")

    print(f"Successfully generated bindings for {sum(bridge_counts.values())} distinct intrinsic overloads.")

if __name__ == "__main__":
    main()