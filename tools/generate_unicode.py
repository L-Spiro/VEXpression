import unicodedata

def generate_unicode_table(output_filename="../src/Foundation/UnicodeData.inl"):
    entries = []
    
    # The prefixes for algorithmic names that we will parse dynamically in C++
    algorithmic_prefixes = (
        "CJK UNIFIED IDEOGRAPH-",
        "CJK COMPATIBILITY IDEOGRAPH-",
        "KHITAN SMALL SCRIPT CHARACTER-",
        "NUSHU CHARACTER-",
        "TANGUT COMPONENT-"
    )
    
    # Iterate over all possible Unicode code points (0 to 0x10FFFF)
    for i in range(0x110000):
        char = chr(i)
        try:
            name = unicodedata.name(char)
            # Explicitly exclude the algorithmic blocks
            if name and not name.startswith(algorithmic_prefixes):
                entries.append((name, i))
        except ValueError:
            # Code point has no name
            pass

    # Sort alphabetically by name to allow std::lower_bound binary searching in C++
    entries.sort(key=lambda x: x[0])

    with open(output_filename, "w", encoding="utf-8") as f:
        f.write("#include \"Unicode.h\"\n")
        f.write("\n")
        f.write("#include <cstdint>\n")
        f.write("#include <cstddef>\n")
        f.write("\n")
        f.write("namespace ve {\n")
        f.write("\n")
        f.write("\tconst Unicode::UnicodeNameEntry Unicode::unicodeNames[] = {\n")
        f.write("#ifdef _NAMED_ESCAPES\n")

        for name, code in entries:
            f.write(f'\t\t{{ "{name}", {len(name)}, 0x{code:04X} }},\n')

        f.write("#else\t// #ifdef _NAMED_ESCAPES\n")
        f.write("\t\t{ nullptr, 0, 0 }\n")
        f.write("#endif\t// #ifdef _NAMED_ESCAPES\n")
        f.write("\t};\n")
        f.write("\n")
        f.write("#ifdef _NAMED_ESCAPES\n")
        f.write(f"\tconst size_t Unicode::numUnicodeNames = {len(entries)};\n")
        f.write("#else\t// #ifdef _NAMED_ESCAPES\n")
        f.write("\tconst size_t Unicode::numUnicodeNames = 0;\n")
        f.write("#endif\t// #ifdef _NAMED_ESCAPES\n")
        f.write("\n")
        f.write("}\t// namespace ve\n")
        
    print(f"Successfully generated {len(entries)} entries into {output_filename}")

if __name__ == "__main__":
    generate_unicode_table()