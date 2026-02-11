strings = [
    input(),
    input(),
    input()
]

print()

for s in strings:
    for i in range(len(s) - 1, -1, -1):
        print(s[i], end='')
    print()
