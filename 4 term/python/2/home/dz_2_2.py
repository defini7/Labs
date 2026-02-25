nums = []

with open('complex.txt') as file:
    for line in file:
        nums.append(complex(line))

old_nums = nums[:]

nums.sort(key=lambda z: abs(z))

print('Старые:', old_nums)
print('Новые:', nums)
