n = int(input())
nums = []

for _ in range(n):
    nums.append(int(input()))

cubed = list(map(lambda x: x**3, nums))

print(sum(cubed))
