import random

prefix = "1616116161161611616116161161611616116161"
end = "F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8F8"

def generate_line():
    patterns = [ "1616161616161616161616161616161616161616", "99999", "3636363636363636363636363636363636363636", "9191919191919191919191919191919191919191" ]
    #patterns = ["49494949494949494949"]
    return random.choice(patterns)

def generate_map(num_lines):
    map = prefix

    for i in range(num_lines):
        line = generate_line()
        
        line = list(line)

        for i in range(len(line)):
            letter = line[i]
            line[i] = "0" if random.random() < 0.2 else line[i]
            line[i] = "A" if random.random() < 0.05 else line[i]
            line[i] = "C" if random.random() < 0.02 else line[i]
   
        line = ''.join(line)

        map += line
    map += end
    return map
    
m = generate_map(50)  
print(m)  
f = open("C:/cmdre/TrailBlazeR/bin/assets/maps/0.tmf", "w")

f.write("TMF")

# Color theme
f.write(chr(int("00",16)))
f.write(chr(int("00",16)))
f.write(chr(int("FE",16)))

f.write("Earth\0")
f.write("earth.png\0")

for char in m:
    s = chr(int(char,16))
    f.write(s)
f.close()