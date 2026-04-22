import codecs
import pkgutil
import encodings
import re

def get_encoding_id(name):
    """
    Attempts to resolve a canonical name to its numerical ID.
    (Windows Code Page or IANA MIBenum digit)
    """
    # 1. Known mapping for standard encodings that don't have digits in the name
    special_cases = {
        'ascii': 3,          # US-ASCII
        'utf-8': 65001,      # Windows/Standard UTF-8
        'utf-16': 1200,      # UTF-16 LE
        'utf-16-be': 1201,
        'utf-32': 12000,
        'latin-1': 28591,    # ISO-8859-1
    }
    
    if name in special_cases:
        return special_cases[name]

    # 2. Extract digits from names like 'cp1252', 'iso8859-15', 'hp-roman8'
    # This covers the vast majority of legacy/system IDs
    match = re.search(r'(\d+)', name.replace('-', ''))
    if match:
        return int(match.group(1))
    
    return None # No standard numerical ID found

def list_encodings_with_ids():
    unique_ids = {} # { ID : Canonical Name }
    
    # Walk the packages
    for loader, module_name, is_pkg in pkgutil.walk_packages(encodings.__path__):
        if is_pkg or module_name.startswith('_') or module_name == 'aliases':
            continue
            
        try:
            # Get canonical name
            canon = codecs.lookup(module_name).name
            
            # Get numerical ID
            numeric_id = get_encoding_id(canon)
            
            if numeric_id is not None:
                # One String to One ID (Keyed by ID to prevent duplicates)
                unique_ids[numeric_id] = canon
        except:
            continue

    return unique_ids

if __name__ == "__main__":
    id_map = list_encodings_with_ids()
    
    print(f"{'ID':<8} | {'CANONICAL NAME'}")
    print("-" * 30)
    
    # Sort by ID for a clean list
    for eid in sorted(id_map.keys()):
        print(f"{eid:<8} | {id_map[eid]}")

    print("-" * 30)
    print(f"Total Identified Encodings: {len(id_map)}")