data = input('Строка: ')
char = input('Символ: ')

prev_idx = 0
poses = []

while (i := data.find(char, prev_idx)) != -1:
    poses.append(i)
    prev_idx = i + 1

print(poses, sum(poses))
