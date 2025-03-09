import os
from pathlib import Path

ORIGINAL_DIR = Path(__file__).parent.parent / "sprites" / "pawn"  / "idle" / "right"
CONVERTED_DIR = Path(__file__).parent.parent / "sprites" / "pawn"  / "idle" / "left"

WIDTH = 64

files = {}

for filename in os.listdir(ORIGINAL_DIR):
    lines = []

    if os.path.isdir(ORIGINAL_DIR / filename):
        continue

    with open(ORIGINAL_DIR / filename) as f:
        for line in f.readlines():
            if len(line) >= WIDTH:
                line = line[0] + line[1:WIDTH][::-1] + line[WIDTH:]
            lines.append(line)
    
    files[filename] = "".join(lines)


for filename, filecontent in files.items():
    os.makedirs(CONVERTED_DIR, exist_ok=True)
    with open(CONVERTED_DIR / filename, "w") as file:
        file.write(filecontent)


# for line in [
# "eeOOOO@@$%%%%######%%%%$@@OOOOee",
# "eO6708888888888888888888888076Oe",
# "O450888888888888888888888888054O",
# "O398888888888888888888888888893O",
# "Oq88888wwwwwwwwwwwwwwwwww88888qO",
# "+w88888 =;:>,<1221<,>:;= 88888w+",
# "+w88888 &-:>,<1221<,>:-& 88888w+",
# "+w88888                  88888w+",
# "+w88888 eeeeeeeeeeeeeeee 88888w+",
# "+w88888XeeeeeeeeeeeeeeeeX88888w+",
# "+wwwwwwXeeeeeeeeeeeeeeeeXwwwwww+",
# "+o****.XeeeeeeeeeeeeeeeeX.****o+",
# "+w88888XeeeeeeeeeeeeeeeeX88888w+",
# "+w88888XeeeeeeeeeeeeeeeeX88888w+",
# "+w88888XeeeeeeeeeeeeeeeeX88888w+",
# "+w88888XeeeeeeeeeeeeeeeeX88888w+"
# ][::-1]:
#     print(f"\"{line}\",")