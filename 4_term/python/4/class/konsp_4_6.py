from itertools import permutations, combinations

s = "RGUNG"

unique_letters = sorted(set(s))

ordered_pairs = ["".join(p) for p in permutations(unique_letters, 2)]
ordered_pairs = list(dict.fromkeys(ordered_pairs))

print("Случай 1 (порядок важен):")
print(ordered_pairs)
print(f"Количество: {len(ordered_pairs)}")

unordered_pairs = ["".join(p) for p in combinations(unique_letters, 2)]

print("\nСлучай 2 (порядок не важен):")
print(unordered_pairs)
print(f"Количество: {len(unordered_pairs)}")