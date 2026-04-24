import sys

def generate_cpp_array():
    """
    Identifies all numericcase Unicode characters and formats them 
    into a C++ uint32_t array initialization.
    """
    numericcase_points = []

    # Collect all numericcase code points
    for i in range(sys.maxunicode + 1):
        if chr(i).isnumeric():
            numericcase_points.append(i)

    # Print the C++ header
    print(f"// Total numericcase characters found: {len(numericcase_points)}")
    print("\tconst uint32_t Character::unicodeNumericTable[] = {")

    # Format the points into rows of 10 for readability
    line_buffer = []
    for count, code_point in enumerate(numericcase_points, 1):
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
    