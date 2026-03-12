import string
from collections import Counter


def find_words(text):
    translator = str.maketrans("", "", string.punctuation)
    text = text.translate(translator).lower()
    
    words = text.split()
    
    if not words:
        print("В файле нет слов")
        return
    
    word_counts = Counter(words)
    print(word_counts)
    max_count = max(word_counts.values())
    
    most_frequent = [word for word, count in word_counts.items() if count == max_count]
    
    print(f"Самое частое слово встречается {max_count} раз:")

    for word in sorted(most_frequent):
        print(word.upper())


with open("2.txt", "r", encoding="utf-8") as file:
    find_words(file.read())