source = input()

nums = list(map(int, source.split('#')))

max_idx = nums.index(max(nums))
min_idx = nums.index(min(nums))

nums[max_idx], nums[min_idx] = nums[min_idx], nums[max_idx]

print(nums)
