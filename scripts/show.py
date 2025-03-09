import sys
from pathlib import Path

if (len(sys.argv) < 2):
    print("Usage: python3 show.py <filepath>")
    exit(1)

file_path = Path(__file__).parent.parent / "textures" / (sys.argv[-1] + ".xpm")
try:
    with open(file_path) as f:
        pixels = []
        for line in f.read().splitlines():
            if (len(line) >= 64):
                pixels.append(line[line.find('\"')+1:line.rfind('\"')])
        
        for index, pixel in enumerate(pixels):
            print(f"{index:<3}  {pixel}")
except FileNotFoundError:
    print(f"File '{file_path}' not found")
    exit(1)
