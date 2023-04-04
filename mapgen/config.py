#########################################################################################################
# This ugly file is the configuration of stage names, patterns used by the mapgen tool.
# This was used for most of the maps, but some parts were in the actual assets folder were done/fixed by hand
# so not all information is represented here which were used, but it can be a starting point for own maps
# Anyways, a good hex editor will always come handy to fix/edit some parts of the maps

# Stage name definitions
names = ["Earth", "Moonbase", "Mercury", "Acidic rain on venus", "Mars", "Jupiter", \
         "Saturn", "Uranus", "Neptune", "Pluto cities" ]

# Background file names
backgrounds = ["earth.png", "moonbase.png", "mercury.png", "venus.png", "mars.png",  \
               "jupiter.png", "saturn.png", "uranus.png", "neptune.png", "pluto.png" ]

# Each map has a color theme, which is used for the HUD text color and the fog color
colorthemes = [b"\x80\xaa\xff", b"\x82\x68\x91", b"\xff\xe4\x59", b"\xbd\xb2\xb2", b"\xc7\xe3\xe7", \
               b"\xfc\xc2\xb1", b"\xb3\x6b\x48", b"\x9d\xbb\xbd", b"\x45\xe4\xfa" ]

#########################################################################################################

# Gaps and special fields randomly replaces regular tiles with the probablities below
gap_probablity =      [0.1,  0.2,   0.2, 0.05, 0.01, 0.1, 0.3, 0.2, 0.2 ]
speedup_probablity =  [0.05, 0.05, 0.05, 0.07, 0.07, 0.07, 0.05, 0.02, 0.02 ]
slowdown_probablity = [0.02, 0.02, 0.02, 0.01, 0.00, 0.01, 0.01, 0.02, 0.02]

#########################################################################################################

# Map starting patterns
prefix = [ \
         #0  
         "11111 11611 11611 66666 11611 11611 11111", \
         # 1 
         "00A00 00A00 00A00 00700 00700 00700 00700 00700 00700 00700" \
         "00700 00700 00700 00700 00700 00700 00700 00700 00700 00700" \
         "00700 00700 00700 00700 00700 00700 00700 00700 00700 00700" \
         "00700 00700 00700 00700 00700 00700 00700 00700 00700 00700" \
         "00A00 00A00 00A00 00A00 00A00 00A00 00A00 00A00 00A00 00A00" \
         "00000 00000 00000 00000 00000 00000 00000 00000 00000 00000" \
         "00000 00000 00000 00000 00000 CCCCC CCCCC CCCCC CCCCC CCCCC" \
         "CCCCC CCCCC CCCCC CCCCC CCCCC CCCCC CCCCC CCCCC CCCCC CCCCC" \
         "74447 47474 44744 47474 74447", \
         #2
         "0", \
         #3
         "64E46 E646E 64E46 E646E 64E46", \
         #4
         "44444 55555 45554 44544 44A44 44544 45554 55555 44444 AAAAA AAAAA AAAAA", \
         #5
         "67676 66766 67676 66766 67676",
         #6
         "44444 44444 06660 06660 00400 00400 00400 00400 00400 00400" \
         "06660 06660 44444 44444", \
         #7
         "AAAAA AAAAA 9E9E9 E9E9E 9E9E9 E9E9E"\
         "9E9E9 E9E9E 90009 90009 E000E 90009 E000E 90009 E000E 99999 99999 99999", \
         #8
         "33333 33333 33333 33B33 33B33 33B33 B3B3B 3BBB3 33B33 33333 00003 00003" \
         "00003 00003 00003 00003 00003 00003 00003 00033 00333 03333 33333 AAAAA" ]

# Finish line pattern - same for all maps
end =    "F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 " \
         "F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 " \
         "F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 " \
         "F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 " \
         "F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 " \
         "F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 " \
         "F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 " \
         "F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 F8F8F 8F8F8 " \

#########################################################################################################

# Randomly chosen patterns
random_patterns = [ \
                   #0
                   ["16161 61616 16161 61616 16161 61616 16161 61616", \
                   "99999", "36363 63636 36363 63636 36363 63636 36363 63636", \
                   "91919 19191 91919 19191 91919 19191 91919 19191"], \
                   #1
                   ["49494 94949 49494 94949 49494 94949 49494 94949", \
                    "71717 17171 71717 17171 71717 17171 71717 17171 ",
                    "77777", "74447 47474 44744 47474 74447 47474 44744 47474" ], \
                   [""],
                   #3
                   ["66066 66066 66066 66066 66066 66066 66066 66066 66066 66066" \
                    "60606 60606 60606 60606 60606 60606 60606 60606 60606 60606" \
                    "60006 60006 60006 60006 60006 60006 60006 60006 60006 60006", \
                    "E6E6E 6E6E6 E6E6E 6E6E6 E6E6E 6E6E6 E6E6E 6E6E6 E6E6E 6E6E6" \
                    "E6E6E 6E6E6 E6E6E 6E6E6 E6E6E 6E6E6 E6E6E 6E6E6 E6E6E 6E6E6", \
                    "46464 64646 46464 64646 46464 64646 46464 64646 46464 64646" \
                    "46464 64646 46464 64646 46464 64646 46464 64646 46464 64646"], \
                   #4
                   ["46464 64646 46464 64646 46464 64646 46464 64646" \
                    "46464 64646 46464 64646 46464 64646 46464 64646", \
                   "55555", "54545 45454 54545 45454 54545 45454 54545 45454", \
                   "00500 00400 40504 00400 00500 50405 00500 00400" \
                   "40504 00400 00500 50405 00500 00400 40504 00400 00400", 
                   "00000 60400 60400 60400 60400 60000 60000 00004 00604 00604 00604 00604 00604 00000"], \
                   #5
                   ["67676 76767 67676 76767 67676 76767 67676 76767 67676 76767", \
                    "66666", "77777", \
                    "06000 07000 06000 07000 06000 07000 06000 07000 06000 07000" \
                    "06700 07600 00700 00600 00700 00600 00700 00600 00700 00600" \
                    "00760 00670 00060 00070 00060 00070 00060 00070 00060 00070" ], \
                   #6
                    ["56565 65656 56565 65656 56565 65656 56565 65656", \
                    "44444", "66666", "E6E6E 6E6E6 E6E6E 6E6E6 E6E6E 6E6E6 E6E6E 6E6E6", \
                    "C4C4C 4C4C4 C4C4C 4C4C4 C4C4C 4C4C4 C4C4C 4C4C4"], \
                    #7
                    ["9E9E9 E9E9E 9E9E9 E9E9E 9E9E9 E9E9E 90009 E000E 90009 E000E 90009 E000E 90009 E000E 99999 99999 99999",
                     "19191 91919 19191 91919 19191 91919 19191 91919 19191 91919", \
                     "E010E 10E01 E010E 10E01 E010E 10E01 E010E 10E01 E010E 10E01 E010E 10E01" \
                     "0E1E0 01E10 0E1E0 01E10 0E1E0 01E10 0E1E0 01E10 0E1E0 01E10 0E1E0 01E10"], \
                    #8
                    ["DD0DD DD0DD DD0DD DD0DD DD0DD DD0DD DD0DD DD0DD DD0DD DD0DD" \
                    "D0D0D D0D0D D0D0D D0D0D D0D0D D0D0D D0D0D D0D0D D0D0D D0D0D" \
                    "D000D D000D D000D D000D D000D D000D D000D D000D D000D D000D", \
                    "B3B3B 3B3B3 B3B3B 3B3B3 B3B3B 3B3B3 B3B3B 3B3B3 B3B3B 3B3B3" \
                    "B3B3B 3B3B3 B3B3B 3B3B3 B3B3B 3B3B3 B3B3B 3B3B3 B3B3B 3B3B3", \
                    "1B1B1 B1B1B 1B1B1 B1B1B 1B1B1 B1B1B 1B1B1 B1B1B 1B1B1 B1B1B" \
                    "1B1B1 B1B1B 1B1B1 B1B1B 1B1B1 B1B1B 1B1B1 B1B1B 1B1B1 B1B1B"], \
                  ]
