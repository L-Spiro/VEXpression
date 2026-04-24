import sys

def get_decimal_ranges():
    """
    Finds consecutive ranges of characters where .isdecimal() is True.
    Returns a list of (start, end) tuples.
    """
    ranges = []
    start_point = None
    
    for i in range(sys.maxunicode + 1):
        #is_decimal = chr(i).isdigit() and not chr(i).isdecimal()
        is_decimal = chr(i).isdecimal()
        
        # Start of a new range
        if is_decimal and start_point is None:
            start_point = i
        
        # End of a range (found a non-decimal char)
        elif not is_decimal and start_point is not None:
            ranges.append((start_point, i - 1))
            start_point = None
            
    # Close the last range if it reached the end of Unicode
    if start_point is not None:
        ranges.append((start_point, sys.maxunicode))
        
    return ranges

def format_as_cpp(ranges):
    """Prints the ranges in a format suitable for a C++ struct array."""
    print(f"// Found {len(ranges)} decimal ranges")
    print("struct UnicodeRange { uint32_t start; uint32_t end; };")
    print("const UnicodeRange unicodeDecimalRanges[] = {")
    
    for start, end in ranges:
        print(f"    {{ 0x{start:04X}, 0x{end:04X} }},")
        
    print("};")

if __name__ == "__main__":
    decimal_ranges = get_decimal_ranges()
    format_as_cpp(decimal_ranges)
    