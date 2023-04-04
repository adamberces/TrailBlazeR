import random
import argparse

import config

# Number of patterns to choose per stage
MAP_LEN = 20

# Parse the index of the stage to be generated
parser = argparse.ArgumentParser(description='Trailblazer TMF map generator')
parser.add_argument('-s', '--stage', type=int, help='Stage number (0-9)', required=True)    
parser.add_argument('-o', '--outfile', type=str, help='Path of the TMF file to be generated', required=True)   
args = parser.parse_args()

if args.stage > 9 or args.stage < 0:
    print("Stage index must be between 0 and 9")
    exit(1)

###################################################################################################

# Generates a map from a predefined number of randomly chosen patterns
def generate_map(num_lines, map_index):

    # Initialize the map with the hardcoded map starting tiles
    map = config.prefix[map_index]

    # Add random patterns   
    for i in range(num_lines):
        line = random.choice(config.random_patterns[map_index]).replace(" ", "")
        line = list(line)
       
        # Add special tiles for some challenge
        for i in range(1, len(line) - 1):
            letter = line[i]
            # Don't fill gaps and dont make gaps/special fields near gaps defined in the pattern
            if line[i] != "0" and line[i-1] != "0" and line[i+1] != "0" and line[i] != "A" and line[i] != "C":
                line[i] = "0" if random.random() < config.gap_probablity[map_index] else line[i]
                line[i] = "A" if random.random() < config.speedup_probablity[map_index] else line[i]
                line[i] = "C" if random.random() < config.slowdown_probablity[map_index] else line[i]

        line = ''.join(line)
        map += line
        
    map += config.end
    return map

###################################################################################################    

# Generate the map, then remove the heper spaces    
print("Selected stage: " + config.names[args.stage])
m = generate_map(MAP_LEN, args.stage)  
m = m.replace(" ", "")
print("Generated tiles: " + str(len(m)) + " Pattern: \n")
print(m)  

# Create empty bytearray for output
ba = bytearray()

# Prepare header
header = "TMF"
meta = config.names[args.stage] + "\0" + config.backgrounds[args.stage] + "\0"
ba.extend(header.encode('utf-8'))
ba.extend(config.colorthemes[args.stage])
ba.extend(meta.encode('utf-8'))

# Convert map tile letters to the hexadecimal number they represent
for char in m:
    ba.extend(int(char, 16).to_bytes(length=1, byteorder='big'))

# Write file
f = open(args.outfile, "wb")
f.write(ba)
f.close()
print("\n\nSuccess! Generated file: " + args.outfile)