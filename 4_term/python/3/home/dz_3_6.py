with open("6.txt", encoding="utf-8") as f:
    lines = f.readlines()

content = ""

for i, line in enumerate(lines):
    trimmed = line.rstrip("\r\n")

    if trimmed.endswith("-"):
        content += trimmed[:-1]
    else:
        content += trimmed + " "

words = []
word = ""

for c in content:
    if "a" <= c.lower() <= "z":
        word += c
    elif word != "":
        words.append(word)
        word = ""

if word:
    words.append(word)

removed_indices = set()

for i in range(len(words) - 1, -1, -1):
    if i in removed_indices:
        continue
    
    word = words[i]
    reversed_word = word[::-1]
    
    for j in range(len(words) - 1, i, -1):
        if j in removed_indices:
            continue
        
        if words[j].lower() == reversed_word.lower():
            removed_indices.add(i)
            removed_indices.add(j)
            break

result = [words[i] for i in range(len(words)) if i not in removed_indices]

with open("6_out.txt", "w", encoding="utf-8") as f:
    f.write(" ".join(result))
