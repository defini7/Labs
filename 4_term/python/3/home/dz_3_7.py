from string import whitespace
from collections import Counter


with open("7.txt") as f:
    content = f.read()

    for c in whitespace:
        content = content.replace(c, "")

counts = Counter(content)

for key in counts:
    if counts[key] == 2:
        print(key)
