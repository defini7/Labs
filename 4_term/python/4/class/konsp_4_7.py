import time
from itertools import permutations
from collections import Counter


def is_anagram_with_itertools(word1, word2):
    if len(word1) != len(word2):
        return False
    
    word1 = word1.lower()
    word2 = word2.lower()

    for perm in set(permutations(word1)):
        if "".join(perm) == word2:
            return True
    
    return False


def is_anagram_with_counter(word1, word2):
    if len(word1) != len(word2):
        return False
    
    word1 = word1.lower()
    word2 = word2.lower()
    
    return Counter(word1) == Counter(word2)


word1 = input("Введите первое слово: ").strip()
word2 = input("Введите второе слово: ").strip()

start = time.perf_counter()
result_itertools = is_anagram_with_itertools(word1, word2)
end = time.perf_counter()
time_itertools = end - start

print("\nITERTOOLS:")
print(f"   Результат: {result_itertools}")
print(f"   Время: {time_itertools:.8f} секунд")

start = time.perf_counter()
result_counter = is_anagram_with_counter(word1, word2)
end = time.perf_counter()
time_counter = end - start

print("\nCOUNTER:")
print(f"   Результат: {result_counter}")
print(f"   Время: {time_counter:.8f} секунд")

print("\n" + "-" * 60)

if time_itertools < time_counter:
    print(f"itertools быстрее на {time_counter - time_itertools:.8f} сек")
else:
    print(f"Counter быстрее на {time_itertools - time_counter:.8f} сек")