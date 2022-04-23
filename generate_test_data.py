import random
import string

outputdir = "data/"
u32max = 4294967295
s32min = -2147483648
s32max = 2147483647

dtWidth = 5000
dtHeight= 5000

# Generate a data table of unsigned ints in csv
with open(outputdir + f"ui_{dtWidth}_{dtHeight}.csv", 'w') as f :
    dt = [[random.randint(0, u32max) for x in range(dtWidth)] for y in range(dtHeight)]
    for row in dt:
        f.write(",".join([str(x) for x in row]) + ",\n") 

# Generate a data table of signed ints in csv
with open(outputdir + f"si_{dtWidth}_{dtHeight}.csv", 'w') as f :
    dt = [[random.randint(s32min, s32max) for x in range(dtWidth)] for y in range(dtHeight)]
    for row in dt:
        f.write(",".join([str(x) for x in row]) + ",\n") 

# Generate a data table of strings in csv
with open(outputdir + f"str_{dtWidth}_{dtHeight}.csv", 'w') as f :
    dt = [["".join([random.choice(string.ascii_lowercase) for x in range(random.randint(5, 10))]) for x in range(dtWidth)] for y in range(dtHeight)]
    for row in dt:
        f.write(",".join([str(x) for x in row]) + ",\n") 

# Generate a data table of chars in csv
with open(outputdir + f"chr_{dtWidth}_{dtHeight}.csv", 'w') as f :
    dt = [["".join(random.choice(string.ascii_lowercase)) for x in range(dtWidth)] for y in range(dtHeight)]
    for row in dt:
        f.write(",".join([str(x) for x in row]) + ",\n") 

# Generate a data table of floats in csv
with open(outputdir + f"f_{dtWidth}_{dtHeight}.csv", 'w') as f :
    dt = [[random.uniform(-30000000.0, 30000000.0) for x in range(dtWidth)] for y in range(dtHeight)]
    for row in dt:
        f.write(",".join([str(x) for x in row]) + ",\n") 