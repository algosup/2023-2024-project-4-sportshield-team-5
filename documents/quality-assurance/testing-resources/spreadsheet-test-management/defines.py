# This file is used as a test for coding conventions.
# It is used to ensure all definition names are in COBOL_CASE.
# This is part of the testing suite created for the project and launched automatically via the test runner.

import re

def detect_defines(cpp_code):
    lines = cpp_code.split("\n") # Split the C++ code into lines
    defines_count = 0 # The number of detected defines in the C++ code
    defines_str = "" # The string containing all the detected define names
    
    for line in lines: 
        if line.startswith("#define"): # Check if the line is a define
            defines_count += 1 # Increment the number of detected defines
            defines_str += line.split(" ")[1] + "\n" # Get the raw define name
    
    matches = re.findall(r'[A-Z_]+', defines_str) # Find all matches of the pattern in the C++ code

    return len(matches) == defines_count # If the number of matches is different from the number of detected defines, at least one is not in COBOL_CASE
