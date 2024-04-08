import json

# Open the test cases file
f = open("test_cases.json", "r") # Read the content
data = json.load(f) # Put in JSON format the content of the file
f.close() # Close the file

test_cases_names_list = [] # List of test cases names

# Beginning of the markdown file
file_content = """# Test Cases

## Overview

This document outlines the different critical points of the software which will be tested. Those tests will ensure the device can be used in production by anyone without significant bug.

## Criticity

The test cases are defined by a criticity level, indicating the importance of the feature in the system and the inner workings of the device.
"""

# We are going to iterate over the test cases and create the markdown file from them
for i in data["tests"]:
    criticity_emojis = ["🟣", "🔴", "🟠", "🟡", "🟢"]
    requirements_text = ""
    steps_text = ""
    test_cases_names_list.append(i["test_name"]) #We save the name of the test case in a list

    if len(i["test_requirements"][0]["tests"]) != 0: # Check if some test need to be done before the realisation of the test
        requirements_text += "**Tests:**\n\n"
        for test in range(len(i["test_requirements"][0]["tests"])): # Iterate over the tests
            if test == len(i["test_requirements"][0]["tests"]) - 1:
                requirements_text += f"- {str(i["test_requirements"][0]["tests"][test])} - {str(test_cases_names_list[i["test_requirements"][0]["tests"][test]])}\n\n"
                # The second argument of the test_requirements is the name of the test case
                # In this case, it can be used as we are sure the name is already saved in the list
                # In the future, add security to check if the name is in the list
            else:
                requirements_text += f"- {str(i["test_requirements"][0]["tests"][test])} - {str(test_cases_names_list[i["test_requirements"][0]["tests"][test]])}\n"
    
    if len(i["test_requirements"][1]["hardware"]) != 0: # Check if some hardware is needed for the test
        requirements_text += "**Hardware:**\n\n"
        for hardware in range(len(i["test_requirements"][1]["hardware"])): # Iterate over the required hardware
            if hardware == len(i["test_requirements"][1]["hardware"]) - 1:
                requirements_text += f"- {str(i["test_requirements"][1]["hardware"][hardware])}\n" # Add the hardware to the requirements text
            else:
                requirements_text += f"- {str(i["test_requirements"][1]["hardware"][hardware])}" # Add the hardware to the requirements text
    
    if len(i["test_requirements"][2]["external_tools"]) != 0: # Check if some external tools are needed for the test
        requirements_text += "**External Tools:**\n\n"
        for external_tool in range(len(i["test_requirements"][2]["external_tools"])): # Iterate over the external tools
            if external_tool == len(i["test_requirements"][2]["external_tools"]) - 1:
                requirements_text += f"- {str(i["test_requirements"][2]["external_tools"][external_tool])}\n"
            else:
                requirements_text += f"- {str(i["test_requirements"][2]["external_tools"][external_tool])}"

    if len(i["steps_to_follow"]) != 0: # Check if there are steps to follow for the test
        steps_text += "**Steps:**\n\n"
        for step in range(len(i["steps_to_follow"])):
            if step == len(i["steps_to_follow"]) - 1:
                steps_text += f"{str(i["steps_to_follow"][step]["step_number"])}. {str(i["steps_to_follow"][step]["step_description"])}\n" # Add the step number and description to the steps text
            else:
                steps_text += f"{str(i["steps_to_follow"][step]["step_number"])}. {str(i["steps_to_follow"][step]["step_description"])}\n" # Add the step number and description to the steps text

    test_case_output_string = f""" 
### {i["test_id"]}. {i["test_name"]}

| ID | {i["test_id"]} |
| --- | --- |
| Name | {i["test_name"]} |
| Test Description | {i["test_description"]} |
| Test Type | {str(i["test_type"]).capitalize()} |
| Test Criticity | {criticity_emojis[int(i["test_criticity"])]} |

{requirements_text}
{steps_text}""" # Test case output string

    file_content += test_case_output_string # Add the test case output string to the file content

file = open("test-cases.md", "w", encoding="utf-8") # Open the markdown file
file.write(file_content) # Write the content of the file
file.close() # Close the file