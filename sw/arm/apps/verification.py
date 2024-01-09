import os
import subprocess
import datetime

cwd = os.getcwd()
command = "python3 "
file1 = open('unit_tests.txt', 'w')
now = datetime.datetime.now()

list_of_tests = [] 
current_path = os.listdir(cwd)

for entity in current_path:
    if os.path.isdir(entity):
        list_of_tests.append(entity)

if '.ipynb_checkpoints' in list_of_tests:
    list_of_tests.remove('.ipynb_checkpoints')

list_of_tests.sort()
print("Total number of applications to be tested:", len(list_of_tests))

L = []
L.append("Verification Script Started: " + now.strftime("%m/%d/%Y, %H:%M:%S") + "\n")
allPassed = True
for unit_test in list_of_tests:
    for file in os.listdir(unit_test):
        if file[-3:] == ".py": #check if it is a Python script
            complete_test_path = os.path.join(unit_test, file)
            proc = subprocess.Popen(command + complete_test_path, stdout=subprocess.PIPE, shell=True)
            (out, err) = proc.communicate()

            if "Test Passed!" in out.decode():
                print("[PASSED] -------", unit_test)
                L.append("[PASSED] ------- " + unit_test + "\n")
            else:
                print("[FAILED] -------", unit_test)
                L.append("[FAILED] ------- " + unit_test + "\n")
                allPassed = False

if allPassed:
    print("All unit tests passed!")
else:
    print("Some tests failed!")

file1.writelines(L)
file1.close()