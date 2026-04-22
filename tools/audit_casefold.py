import unicodedata

def generate_casefold_extras():
    print("// C++ Table: Casefold-specific mappings (Excluding standard toLower results)")
    print("// These are the characters where casefold() provides 'extra' normalization.")
    print("struct Casefold_Table {")
    print("\tchar32_t    uniChar;")
    print("\tchar32_t    lowerdResult[3];")
    print("\tuint32_t    newSize;")
    print("};\n")

    print("const Casefold_Table casefold_extras[] = {")

    count = 0
    for i in range(0x110000):
        if 0xD800 <= i <= 0xDFFF:
            continue
            
        try:
            char = chr(i)
            folded = char.casefold()
            lowered = char#char.lower()
            
            # THE FILTER: Only keep if casefold did something DIFFERENT than lower
            if folded != lowered:
                folded_codepoints = [ord(c) for c in folded]
                size = len(folded_codepoints)
                
                orig_hex = f"0x{i:08X}"
                padded_results = folded_codepoints + [0] * (3 - size)
                results_hex = ", ".join(f"0x{cp:08X}" for cp in padded_results)
                
                try:
                    name = unicodedata.name(char)
                except ValueError:
                    name = "UNKNOWN"

                # Printing the visual result in the comment as requested
                print(f"\t{{ {orig_hex}, {{ {results_hex} }}, {size} }}, // {char} -> {folded} ({name})")
                count += 1
                
        except (ValueError, OverflowError):
            continue

    print("};")
    print(f"\nconst size_t casefold_extras_count = {count};")

if __name__ == "__main__":
    generate_casefold_extras()
