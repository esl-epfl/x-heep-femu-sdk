import os
import subprocess

cwd = os.getcwd()
command = "python3 "

list_of_tests = os.listdir(cwd)
list_of_tests.remove(os.path.basename(__file__))
list_of_tests = ["hello_world"]

print("Total number of applications to be tested:", len(list_of_tests))

for unit_test in list_of_tests:
    for file in os.listdir(unit_test):
        if file[-3:] == ".py": #check if it is a Python script
            complete_test_path = os.path.join(unit_test, file)
            proc = subprocess.Popen(command + complete_test_path, stdout=subprocess.PIPE, shell=True)
            (out, err) = proc.communicate()

            if "Test Passed!" in out.decode():
                print("[PASSED] -------", unit_test)
            else:
                print("[FAILED] -------", unit_test)

print("all good")