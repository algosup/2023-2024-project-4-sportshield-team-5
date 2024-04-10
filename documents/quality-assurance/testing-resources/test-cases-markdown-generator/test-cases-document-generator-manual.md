# SportShield Test Cases Markdown Document Generator Manual

## 1. Purpose

This script aims to enhance the creation of the test cases document following the recommended guidelines of Markdown files. From a JSON file containing a list of test cases, it creates the whole document containing those test cases in a easily readable and efficient manner.

## 2. Installation

1. Download and install Python latest version: `https://www.python.org/downloads/`
2. Clone the repository using `git clone https://github.com/algosup/2023-2024-project-4-sportshield-team-5.git`
3. Open a command line at the root of the folder
4. Make this folder your working directory: `cd documents/quality-assurance/testing-resources/test-cases-markdown-generator`
5. Run the server for your tests Put your JSON in the current directory and run the program using the following command: `python .\generate-test-cases-document.py`

## 3. Usage

The structure of a test case object in the JSON file is the following:

```json
{
    "test_id": 1, /* The unique identifier of the test case*/
    "test_name": "", /* A succinct yet explicit description of the test case purpose */
    "test_description": "", /* A more complete description of the test case */
    "test_requirements": [ /* The different rescources needed to realise in optimum conditions the test */
        {
          "tests": [] /* The test which must be validated before running this test */
        },
        {
          "hardware": [] /* The hardware required to run the test */
        },
        {
          "external_tools": [] /* Other tools than the provided hardware is required to run the test */
        }
    ],
    "test_type": "", /* Is the test executed by a program? */
    "test_criticity": 0, /* The importance of the tested feature */
    "steps_to_follow": [ /* List of the steps needed to run the test */
        {
          "step_number": 1, /* The step number*/
          "step_description": "Push to the dev or the main branch of the repository. This test will be run automatically by GitHub Actions." /* What needs to be done at this step */
        }
    ],
    "expected_result": "The code should compile without any error or warning.", /* What is exepected in case of a success ? */
    "test_data": { /* Additional data */
        "data": ""
    }
},
```
