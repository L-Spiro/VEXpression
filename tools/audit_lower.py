import unicodedata

def generate_lower_table():
    print("// C++ Table: All characters impacted by lower-casing")
    print("// This includes all characters where char.lower() != char")
    print("struct LowerCase_Table {")
    print("\tchar32_t    uniChar;")
    print("\tchar32_t    loweredResult[3]; // Supports 1-to-N mappings")
    print("\tuint32_t    newSize;")
    print("};\n")

    print("const LowerCase_Table lower_mappings[] = {")

    count = 0
    # Iterate through the full Unicode range
    for i in range(0x110000):
        # Skip surrogate pairs
        if 0xD800 <= i <= 0xDFFF:
            continue
            
        try:
            char = chr(i)
            lowered_str = char.lower()
            
            # THE FILTER: Only keep if the character actually changed
            if lowered_str != char:
                lowered_codepoints = [ord(c) for c in lowered_str]
                size = len(lowered_codepoints)
                
                # Format the original character in hex
                orig_hex = f"0x{i:08X}"
                
                # Pad the results array to 3 elements (as defined in the struct)
                padded_results = lowered_codepoints + [0] * (3 - size)
                results_hex = ", ".join(f"0x{cp:08X}" for cp in padded_results)
                
                # Get the Unicode name for the comment
                try:
                    name = unicodedata.name(char)
                except ValueError:
                    name = "UNKNOWN"

                # Print the C++ struct entry
                # Example: { 0x00000041, { 0x00000061, 0x00000000, 0x00000000 }, 1 }, // A -> a (LATIN CAPITAL LETTER A)
                print(f"\t{{ {orig_hex}, {{ {results_hex} }}, {size} }}, // {char} -> {lowered_str} ({name})")
                count += 1
                
        except (ValueError, OverflowError):
            continue

    print("};")
    print(f"\nconst size_t lower_mappings_count = {count};")

if __name__ == "__main__":
    generate_lower_table()