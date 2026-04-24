import sys

def generate_cpp_array():
    """
    Identifies all uppercase Unicode characters and formats them 
    into a C++ uint32_t array initialization.
    """
    uppercase_points = []

    # Collect all uppercase code points
    for i in range(sys.maxunicode + 1):
        if chr(i).isupper():
            uppercase_points.append(i)

    # Print the C++ header
    print(f"// Total uppercase characters found: {len(uppercase_points)}")
    print("\tconst uint32_t Character::unicodeUppercaseTable[] = {")

    # Format the points into rows of 10 for readability
    line_buffer = []
    for count, code_point in enumerate(uppercase_points, 1):
        # Format as 0x000000 style hex
        line_buffer.append(f"0x{code_point:04X}")
        
        if count % 10 == 0:
            print("\t\t" + ", ".join(line_buffer) + ",")
            line_buffer = []

    # Print any remaining items
    if line_buffer:
        print("\t\t" + ", ".join(line_buffer))

    print("\t};")

if __name__ == "__main__":
    generate_cpp_array()
    