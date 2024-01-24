# Import the X-HEEP Python class
from pynq import x_heep

# Load the X-HEEP bitstream
x_heep = x_heep()

# Choose which memory bank to be written in X-HEEP
# First bank = 0
# Second bank = 1

x_heep.init_r_obi(2)

#Write the whole memory bank with squared index value
#Third memory bank (32kB each) is starting 0x00010000
for a,b in enumerate(range(0,0x00010000,0x00000004)):
    data = a ** 2
    x_heep.write_r_obi(data, b, 0x00010000)

allMatch = True
#Read the previously written whole memory bank and compare values
for a,b in enumerate(range(0,0x00008000,0x00000004)):
    data_read = x_heep.read_r_obi(b, 0x00008000)
    if data_read != a**2:
        allMatch = False
        print("Data does not match!")
        break
        
if allMatch:
    print("Test Passed!")
else:
    print("Test Failed!")