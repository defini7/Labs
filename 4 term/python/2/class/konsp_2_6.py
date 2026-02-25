with open('file.txt', encoding='utf-8') as file:
    data = file.read()

for c in ' .,…;:?!—-()«»\'"/':
    data = data.replace(c, '')

print(data)

freq = {}

for c in data:
    if c not in freq:
        freq[c] = 0

    freq[c] += 1

max_freq = max(freq.values())

for key in freq:
    if freq[key] == max_freq:
        print(key)
