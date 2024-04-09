# This file is used as a test for coding conventions.
# It is used to ensure all function names are in camelCase.
# This is part of the testing suite created for the project and launched automatically via the test runner.

import re

# The different C++ types
cpp_types = ("void", "int", "float", "double", "char", "bool", "string")

# Check if the function names in the C++ code are in camel case
# @param cpp_code The C++ code to check
# @return True if all the function names are in camel case, False otherwise
def detect_camel_case_functions(cpp_code):
    functions_str = "" # The string containing all the detected function names
    functions_count = 0 # The number of detected functions in the C++ code
    
    lines = cpp_code.split("\n") # Split the C++ code into lines
    
    for line in lines:
        if line.startswith(cpp_types) and "=" not in line: # Check if the line is a function declaration
            functions_count += 1 # Increment the number of detected functions
            function = str(line).split(" ")[1].replace("(", "").replace(")", "") + "\n" # Get the raw function name
            for substring in cpp_types: # Remove the C++ types from the function name (mainly in params if they were touching the open bracket)
                if substring in function:
                    function = function.replace(substring, "") # Remove the C++ type
            functions_str += function
    
    # Regular expression pattern to match camel case function names with multiple words
    pattern = r'\b[a-z]+(?:[A-Z][a-z]*)+\b'

    # Find all matches of the pattern in the C++ code
    matches = re.findall(pattern, functions_str)
    
    for match in matches:
        if str(match)[0].isupper(): # If the first character of the match is uppercase, it's not camel case
            matches.remove(match)

    return len(matches) == functions_count # If the number of matches is different from the number of detected functions, at least one is not in camelCase
    # Else all the function names are in camel case