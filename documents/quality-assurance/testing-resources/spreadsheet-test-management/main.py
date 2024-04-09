import gspread
from google.oauth2.service_account import Credentials
import json
import time
import linter

scopes = [
    "https://www.googleapis.com/auth/spreadsheets"
]
creds = Credentials.from_service_account_file("credentials.json", scopes=scopes)
client = gspread.authorize(creds)

sheet_id = "1vLu0oecECq-B2gHba6w_XQCSSX2-hDMr_QxqF_5rOWs"
workbook = client.open_by_key(sheet_id)

worksheet_list = map(lambda x: x.title, workbook.worksheets())
validated_test = {i: False for i in range(1, 55)}

f = open("test_cases.json", "r")
data = json.load(f)
f.close()

def verify_worksheets_existence():
    i = 0
    for test in data["tests"]:
        i += 1
        if (test["test_name"] not in worksheet_list):
            created_worksheet = workbook.add_worksheet(title=f"{i}. {test["test_name"]}", rows=100, cols=20)
            initialize_worksheet(created_worksheet, test)
    return
            

def initialize_worksheet(current_worksheet: gspread.Worksheet, test: dict):
    
    time.sleep(2) # Avoid Google API rate limit (300 write requests/min)
    
    current_worksheet.update_acell("A1", "Test Name")
    current_worksheet.update_acell("B1", "Test ID")
    current_worksheet.update_acell("C1", "Test Description")
    current_worksheet.update_acell("D1", "Test Execution Count")
    current_worksheet.update_acell("E1", "Expected Result")
    current_worksheet.update_acell("A2", test["test_name"])
    current_worksheet.update_acell("B2", test["test_id"])
    current_worksheet.update_acell("C2", test["test_description"])
    current_worksheet.update_acell("D2", 0)
    current_worksheet.update_acell("E2", test["expected_result"])
    current_worksheet.update_acell("B5", "Execution Date & Time")
    current_worksheet.update_acell("C5", "Execution ID")
    current_worksheet.update_acell("D5", "Status")
    current_worksheet.update_acell("E5", "Result")
    current_worksheet.update_acell("F5", "Addtional Notes")

    current_worksheet.format(["A1: E1", "B5: F5"], {"textFormat": {"bold": True}})
    return
        
def run_tests():    
    for i, test in enumerate(data["tests"], start=1):
        worksheet = workbook.worksheet(f"{i}. {test["test_name"]}")
        test_run_id = int(worksheet.acell("D2").value) + 1
        test_required_and_not_validated = False

        if len(test["test_requirements"][0]["tests"]) != 0:
            for required_test in test["test_requirements"][0]["tests"]:
                if not validated_test[required_test]:
                    print(f"❌ - Test {i} requires test {required_test} to be validated first")
                    test_required_and_not_validated = True
                    break  # Skip to next iteration of the outer loop

        if test_required_and_not_validated:
            continue

        if test["test_type"] == "automated":
            print(f"Please wait while we run automatically the test \"{test['test_name']}\" for you...")
            test_result, test_comment
            if test["test_id"] == 0:
                test_result, test_comment = True, "/" # Placholder as link with GiHub API is not done yet
            if test["test_id"] == 1:
                test_result, test_comment = linter.linter()

            if test_result == False:
                validated_test[i] = True
                
                worksheet.update_acell(f"B{test_run_id + 5}", time.strftime("%Y-%m-%d %H:%M:%S"))
                worksheet.update_acell(f"C{test_run_id + 5}", str(test_run_id))
                worksheet.update_acell(f"D{test_run_id + 5}", "Success")
                worksheet.update_acell(f"E{test_run_id + 5}", "The expected result was met.")
                worksheet.update_acell(f"F{test_run_id + 5}", "/")
                
                worksheet.format(f"D{test_run_id + 5}", {"backgroundColor": {"red": 0.0, "green": 1.0, "blue": 0.0}})
                
            else:
                validated_test[i] = False
                
                worksheet.update_acell(f"B{test_run_id + 5}", time.strftime("%Y-%m-%d %H:%M:%S"))
                worksheet.update_acell(f"C{test_run_id + 5}", str(test_run_id))
                worksheet.update_acell(f"D{test_run_id + 5}", "Failed")
                worksheet.update_acell(f"E{test_run_id + 5}", "The expected result was not met.")
                worksheet.update_acell(f"F{test_run_id + 5}", str(test_comment))
                
                worksheet.format(f"D{test_run_id + 5}", {"backgroundColor": {"red": 1.0, "green": 0.0, "blue": 0.0}})


        elif test["test_type"] == "manual":
            print(f"Please run manually the test \"{test['test_name']}\"")
            print("Follow the following steps:\n\n\n")
            for step in test["steps_to_follow"]:
                print(f"Step {step['step_number']}: {step['step_description']}")
            print("\n\n\n")
            match = input(f"Does the result match the expected result? \"{test['test_name']}\" [y/n]:")
            if match == "y":
                validated_test[i] = True
                
                worksheet.update_acell(f"B{test_run_id + 5}", time.strftime("%Y-%m-%d %H:%M:%S"))
                worksheet.update_acell(f"C{test_run_id + 5}", str(test_run_id))
                worksheet.update_acell(f"D{test_run_id + 5}", "Success")
                worksheet.update_acell(f"E{test_run_id + 5}", "The expected result was met.")
                worksheet.update_acell(f"F{test_run_id + 5}", "/")
                
                worksheet.format(f"D{test_run_id + 5}", {"backgroundColor": {"red": 0.0, "green": 1.0, "blue": 0.0}})

            else:
                validated_test[i] = False
                notes = input("Could you add some notes to explain why the test failed?")
                
                worksheet.update_acell(f"B{test_run_id + 5}", time.strftime("%Y-%m-%d %H:%M:%S"))
                worksheet.update_acell(f"C{test_run_id + 5}", str(test_run_id))
                worksheet.update_acell(f"D{test_run_id + 5}", "Failed")
                worksheet.update_acell(f"E{test_run_id + 5}", "The expected result was not met.")
                worksheet.update_acell(f"F{test_run_id + 5}", str(notes))
                worksheet.format(f"D{test_run_id + 5}", {"backgroundColor": {"red": 1.0, "green": 0.0, "blue": 0.0}})
    return

if __name__ == "__main__":
    verify_worksheets_existence()
    run_tests()

# values_list = sheet.sheet1.row_values(1)
# columns = sheet.sheet1.col_values(1)

# print(columns)
# print(values_list)
