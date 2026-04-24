import sys

def generate_cpp_array():
    """
    Identifies all lowercase Unicode characters and formats them 
    into a C++ uint32_t array initialization.
    """
    lowercase_points = []

    # Collect all lowercase code points
    for i in range(sys.maxunicode + 1):
        if chr(i).islower():
            lowercase_points.append(i)

    # Print the C++ header
    print(f"// Total lowercase characters found: {len(lowercase_points)}")
    print("\tconst uint32_t Character::unicodeLowercaseTable[] = {")

    # Format the points into rows of 10 for readability
    line_buffer = []
    for count, code_point in enumerate(lowercase_points, 1):
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
    