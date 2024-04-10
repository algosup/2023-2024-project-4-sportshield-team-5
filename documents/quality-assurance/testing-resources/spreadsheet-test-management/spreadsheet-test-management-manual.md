# SportShield Test Report Speadsheet Management Manual

## 1. Purpose

This script aims to enhance the creation and the management of the test report spreadsheet With an automatic fill in. From a JSON file containing a list of test cases, it creates the whole spreadsheet. All the testing values can be consulted with a simple glance.

## 2. Installation

1. Download and install Python latest version: `https://www.python.org/downloads/`
2. Clone the repository using `git clone https://github.com/algosup/2023-2024-project-4-sportshield-team-5.git`
3. Open a command line at the root of the folder
4. Make this folder your working directory: `cd documents/quality-assurance/testing-resources/test-cases-markdown-generator`
5. Install the required packages on your system: `pip install -r requirements.txt`
6. Generate a Google Cloud API Key using Google Sheets API on [Google Cloud Console](https://console.cloud.google.com/welcome?hl=fr&project=automation-gsheets)
7. Place the credentials.json you are going to obtain from Google Cloud console in a file named `credentials.json`.
8. Place your JSON file including your test cases in the current directory and run the program using the following command: `python .\main.py`

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

When executing the testing procedure, you will have to fill in the program with the result you got on the executed test case. If the test fails, you will have the possibility to add a comment describing in details what was not working.
