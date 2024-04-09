# This file is used as a test for coding conventions.
# It is used to ensure all variables names are in snake_case.
# This is part of the testing suite created for the project and launched automatically via the test runner.

import re

# The different C++ types
cpp_types = ("void", "int", "float", "double", "char", "bool", "string")

def detect_variables(cpp_code):
    variables_str = "" # The string containing all the detected variable names
    variables_count = 0 # The number of detected variables in the C++ code
    
    lines = cpp_code.split("\n") # Split the C++ code into lines
    
    for line in lines:
        if line.startswith(cpp_types) and "=" in line: # Check if the line is a variable declaration
            variables_count += 1 # Increment the number of detected variables
            variable = str(line).split(" ")[1].replace(";", "") + "\n" # Get the raw variable name
            for substring in cpp_types: # Remove the C++ types from the variable name (mainly in params if they were touching the open bracket)
                if substring in variable:
                    variable = variable.replace(substring, "") # Remove the C++ type
            variables_str += variable
    
    # Regular expression pattern to match snake case variable names with multiple words
    pattern = r'\b[a-z]+(?:_[a-z]*)+\b'

    # Find all matches of the pattern in the C++ code
    matches = re.findall(pattern, variables_str)
    
    for match in matches:
        if str(match)[0].isupper(): # If the first character of the match is uppercase, it's not snake case
            matches.remove(match)

    return len(matches) == variables_count # If the number of matches is different from the number of detected variables, at least one is not in snake_case
    # Else all the variable names are in snake_case
    