with open('file.txt', encoding='utf-8') as file:
    line = file.readline()
    
for c in ' .,…;:?!—-()«»\'"/':
    line = line.replace(c, '$')

words = line.lower().split('$')
freq = {}

for word in words:
    if len(word) > 0:
        if word not in freq:
            freq[word] = 0

        freq[word] += 1

min_freq = min(freq.values())

rarest_words = [word for word in freq if freq[word] == min_freq]

print(min(rarest_words))