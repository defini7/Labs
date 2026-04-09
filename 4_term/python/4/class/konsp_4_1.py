with open("1.txt", "r") as f:
    text = f.read()

max_len = 0
current_len = 1

if len(text) == 0:
    max_len = 0
if len(text) == 1:
    max_len = 1
else:
    for i in range(1, len(text)):
        if text[i-1] in "WSC" and text[i] in "WSC":
            current_len = 1
        else:
            current_len += 1
        
        if current_len > max_len:
            max_len = current_len