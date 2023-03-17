import random

def generate_line():
    digits = "1296"
    line = ""
    for i in range(5):
        d1 = random.choice(digits)
        d2 = random.choice(digits)
        line += d1 + d2 + d1 + d2
    return line

def generate_map(num_lines):
    map = ""
    for i in range(num_lines//2):
        line = generate_line()
        line = line.replace("22", "29").replace("99", "96")
        zeros = ""
        for j in range(5):
            zeros += "0" if random.random() < 0.2 else ""
        line = zeros + line + zeros[::-1]
        map += line
        
    for i in range(num_lines//2, num_lines):
        line = generate_line()
        line = line.replace("22", "29").replace("99", "96")
        zeros = ""
        for j in range(5):
            zeros += "0" if random.random() < 0.2 else ""
        line = zeros + line + zeros[::-1]
        map += line 
    return map
    
m = generate_map(100)    
f = open("1.tmf", "w")
f.write("TMF")
f.write(chr(5))
for char in m:
    s = chr(int(char,16))
    f.write(s)
f.close()