import sys

def generate_cpp_array():
    """
    Identifies all digitcase Unicode characters and formats them 
    into a C++ uint32_t array initialization.
    """
    digitcase_points = []

    # Collect all digitcase code points
    for i in range(sys.maxunicode + 1):
        if chr(i).isdigit():
            digitcase_points.append(i)

    # Print the C++ header
    print(f"// Total digitcase characters found: {len(digitcase_points)}")
    print("\tconst uint32_t Character::unicodeDigitTable[] = {")

    # Format the points into rows of 10 for readability
    line_buffer = []
    for count, code_point in enumerate(digitcase_points, 1):
        # Format as 0x000000 style hex
        line_buffer.append(f"0x{code_point:04X}")
        
        if count % 10 == 0:
            print("\t" + ", ".join(line_buffer) + ",")
            line_buffer = []

    # Print any remaining items
    if line_buffer:
        print("\t" + ", ".join(line_buffer))

    print("};")

if __name__ == "__main__":
    generate_cpp_array()
    