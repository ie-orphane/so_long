import os
from pathlib import Path

ORIGINAL_DIR = Path(__file__).parent / "sheep"
# CONVERTED_DIR = Path(__file__).parent / "out"
CONVERTED_DIR = Path(__file__).parent.parent / "textures" / "sheep"

ORIGINAL_WIDTH = 128
CONVERTED_WIDTH = 64
NONE_CHAR = "+"

WIDTH = 55
HEIGHT = 48
GROUND = 92

files = {}

for filename in os.listdir(ORIGINAL_DIR):
    lines = []
    count = 0

    if os.path.isdir(ORIGINAL_DIR / filename):
        continue

    # print()

    with open(ORIGINAL_DIR / filename) as f:
        for index, line in enumerate(f.readlines()):
            if line[line.find("\"")+1:line.rfind("\"")] == NONE_CHAR * ORIGINAL_WIDTH and not (GROUND - (HEIGHT // 2))  < index < GROUND:
                continue
            if len(line) >= ORIGINAL_WIDTH:
                count += 1
                # print(line[line.find("\"")+1:line.rfind("\"")][CONVERTED_WIDTH//2:-CONVERTED_WIDTH//2], end="\n")
                line = "\"" + line[line.find("\"")+1:line.rfind("\"")][38:-35] + "\",\n"
            lines.append(line.replace("128 128", f"{WIDTH} {HEIGHT}"))
    for _ in range(1):
        lines.insert(-1, f"\"{NONE_CHAR*WIDTH}\",\n")
    for _ in range(HEIGHT - count - 1):
        lines.insert(lines.index("/* pixels */\n") + 1, f"\"{NONE_CHAR*WIDTH}\",\n")

    files[filename] = "".join(lines)
    # print(len(lines))


for filename, filecontent in files.items():
    os.makedirs(CONVERTED_DIR, exist_ok=True)
    with open(CONVERTED_DIR / filename, "w") as file:
        file.write(filecontent)
