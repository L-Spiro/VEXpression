import sys

def get_printable_ranges():
    """
    Finds consecutive ranges of characters where .isprintable() is True.
    Returns a list of (start, end) tuples.
    """
    ranges = []
    start_point = None
    
    for i in range(sys.maxunicode + 1):
        is_printable = chr(i).isprintable()
        
        # Start of a new range
        if is_printable and start_point is None:
            start_point = i
        
        # End of a range (found a non-printable char)
        elif not is_printable and start_point is not None:
            ranges.append((start_point, i - 1))
            start_point = None
            
    # Close the last range if it reached the end of Unicode
    if start_point is not None:
        ranges.append((start_point, sys.maxunicode))
        
    return ranges

def format_as_cpp(ranges):
    """Prints the ranges in a format suitable for a C++ struct array."""
    print(f"// Found {len(ranges)} printable ranges")
    print("struct UnicodeRange { uint32_t start; uint32_t end; };")
    print("const UnicodeRange unicodePrintableRanges[] = {")
    
    for start, end in ranges:
        print(f"    {{ 0x{start:04X}, 0x{end:04X} }},")
        
    print("};")

if __name__ == "__main__":
    printable_ranges = get_printable_ranges()
    format_as_cpp(printable_ranges)
    