def max_spaces(text):
    max_spaces = 0
    spaces = 0

    for c in text:
        if c == " ":
            spaces += 1
        else:
            max_spaces = max(max_spaces, spaces)
            spaces = 0

    return max(max_spaces, spaces)


with open("3.txt", encoding="utf-8") as f:
    text = f.read()

spaces_count = max_spaces(text)
spaces = spaces_count * " "

while text.find(spaces) != -1:
    text = text.replace(spaces, "*")

with open("3_out.txt", "w", encoding="utf-8") as f:
    f.write(text)
