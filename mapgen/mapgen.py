import random
import argparse

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

# Stage name definitions
names = ["Earth", "Moonbase", "Mercury", "Venus", "Mars", "Jupiter", \
         "Saturn", "Uranus", "Neptune", "Pluto cities" ]

# Background file names
backgrounds = ["earth.png", "moonbase.png", "mercury.png", "venus.png", "mars.png",  \
               "jupiter.png", "saturn.png", "uranus.png", "neptune.png", "pluto.png" ]

# Each map has a color theme, which is used for the HUD text color and the fog color
colorthemes = ["\x80\xAA\xFF", "\x82\x68\x91" ]

###################################################################################################

# Gaps and special fields randomly replaces regular tiles with the probablities below
gap_probablity = [0.2, 0.2 ]
speedup_probablity = [0.05, 0.05 ]
slowdown_probablity = [0.02, 0.02 ]

# Map starting patterns
prefix = [ \
         #0  
         "16161 16161 16161 16161 16161 16161 16161 16161", \
         # 1 
         "00A00 00A00 00A00 00700 00700 00700 00700 00700 00700 00700" \
         "00700 00700 00700 00700 00700 00700 00700 00700 00700 00700" \
         "00700 00700 00700 00700 00700 00700 00700 00700 00700 00700" \
         "00700 00700 00700 00700 00700 00700 00700 00700 00700 00700" \
         "00A00 00A00 00A00 00A00 00A00 00A00 00A00 00A00 00A00 00A00" \
         "00000 00000 00000 00000 00000 00000 00000 00000 00000 00000" \
         "00000 00000 00000 00000 00000 CCCCC CCCCC CCCCC CCCCC CCCCC" \
         "CCCCC CCCCC CCCCC CCCCC CCCCC CCCCC CCCCC CCCCC CCCCC CCCCC" \
         "74447 47474 44744 47474 74447"
         ]

# Finish line pattern - same for all maps
end =    "F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 " \
         "F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 " \
         "F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 " \
         "F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 " \
         "F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 " \
         "F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 " \
         "F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 " \
         "F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 " \

# Randomly chosen patterns
random_patterns = [ \
                   #0
                   ["16161 61616 16161 61616 16161 61616 16161 61616", \
                   "99999", "36363 63636 36363 63636 36363 63636 36363 63636", \
                   "91919 19191 91919 19191 91919 19191 91919 19191"], \
                   #1
                   ["49494 94949 49494 94949 49494 94949 49494 94949", \
                    "71717 17171 71717 17171 71717 17171 71717 17171 ",
                    "77777", "74447 47474 44744 47474 74447 47474 44744 47474" ] \
                  ]

###################################################################################################

# Generates a map from a predefined number of randomly chosen patterns
def generate_map(num_lines, map_index):

    # Initialize the map with the hardcoded map starting tiles
    map = prefix[map_index]

    # Add random patterns   
    for i in range(num_lines):
        line = random.choice(random_patterns[map_index])
        line = line
        line = list(line)

        # Add special tiles for some challenge
        for i in range(len(line)):
            letter = line[i]
            line[i] = "0" if random.random() < gap_probablity[map_index] else line[i]
            line[i] = "A" if random.random() < speedup_probablity[map_index] else line[i]
            line[i] = "C" if random.random() < slowdown_probablity[map_index] else line[i]
   
        line = ''.join(line)

        map += line

    map += end
    return map

###################################################################################################    

# Generate the map, then remove the heper spaces    
print("Selected stage: " + names[args.stage] + "\nPattern:")
m = generate_map(MAP_LEN, args.stage)  
m = m.replace(" ", "")
print(m)  

f = open(args.outfile, "w")

# Write header
f.write("TMF")

# Write metadata
f.write(colorthemes[args.stage])
f.write(names[args.stage] + "\0")
f.write(backgrounds[args.stage] + "\0")

# Convert map tile letters to the ASCII code they represent 
for char in m:
    s = chr(int(char,16))
    f.write(s)

# Close file
f.close()
print("\n\nSuccess! Generated file: " + args.outfile)