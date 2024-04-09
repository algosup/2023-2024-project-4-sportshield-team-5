from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from bs4 import BeautifulSoup
import json
import functions
import defines
import variables

def getPage(url): # Get the page source of the given URL
    driver = webdriver.Chrome() # Use Chrome as the browser
    driver.get(url)

    try:
        WebDriverWait(driver, 10).until( # Wait for the page to load
            EC.presence_of_element_located((By.TAG_NAME, "body")) # Wait for the body tag to be present
        )

        page = driver.page_source # Get the page source
    finally:
        driver.quit() # Close the browser

    return page # Return the page source

def getFileNames(page): # Get the names of the files in the codebase
    soup = BeautifulSoup(page, "html.parser") # Parse the page source
    script_tag = soup.find('script', attrs={'type': 'application/json', 'data-target': 'react-app.embeddedData'}) # Find the script tag containing the file names
    if script_tag: # If the script tag is found
        json_content = script_tag.string # Get the JSON content of the script tag
        
        data = json.loads(json_content) # Load the JSON content

        if "payload" in data and "tree" in data["payload"]: # Check if the tree is present in the JSON content
            items = data["payload"]["tree"]["items"] # Get the items in the tree
            file_names = [item["name"] for item in items] # Get the names of the files
            return file_names # Return the names of the files
        else:
            return None
    else:
        return None

def getCode(page): # Get the code from the page source
    soup = BeautifulSoup(page, "html.parser") 
    code = soup.find('textarea', id='read-only-cursor-text-area') # Find the textarea containing the code
    if code: # If the code is found
        return code.string # Return the code
    else:
        return None

def AnalyseFile(file_name:str, codebase_url:str): # Analyse the given file
    file_url = codebase_url + "/" + file_name
    page = getPage(file_url) # Get the page source of the file
    if page:
        code = getCode(page) # Get the code from the page source
        if code:
            if functions.detect_camel_case_functions(code) == False: # Check if the function names are in camelCase
                return -1
            if defines.detect_defines(code) == False: # Check if the definition names are in COBOL_CASE
                return -2            
            if variables.detect_variables(code) == False: # Check if the variable names are in snake_case
                return -3
            return 0
        else:
            return -4 # No code found
    else:
        return 404 # Page not found

def linter(codebase_url: str):
    incorrect_files = []
    error_type = []
    error_type_dict = {-1: "Function names are not in camelCase", -2: "Definition names are not in COBOL_CASE", -3: "Variable names are not in snake_case", -4: "No code found", 404: "Page not found"} # Dictionary to map error codes to error messages
    page = getPage(codebase_url) # Get the page source of the codebase
    if page:
        file_names = getFileNames(page) # Get the names of the files in the codebase
        if file_names:
            for file_name in file_names:
                if AnalyseFile(file_name) != 0: # Analyse the file
                    incorrect_files.append(file_name) # Add the file name to the list of incorrect files
                    error_type.append(error_type_dict[AnalyseFile(file_name)]) # Add the error type to the list of error types
            if incorrect_files == [] and error_type == []: # If no incorrect files are found
                return True, "/" # Return True and an empty string
            else:
                return incorrect_files, error_type # Return the list of incorrect files and the list of error types
        else:
            print("No file names found.")
    else:
        print("No page found.")
