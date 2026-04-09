import re
import sys


def find_words(text):
    words = re.split(r"[/\d]+", text)
    words = [w for w in words if w]
    
    result = []
    
    for word in words:
        if re.fullmatch(r"[^жЖрРкК]*[кК][^жЖрРкК]*[кК][^жЖрРкК]*[кК][^жЖрРкК]*", word):
            result.append(word)
    
    return result


filename = input("\nВведите имя файла: ").strip()

try:
    with open(filename, "r", encoding="utf-8") as f:
        text = f.read()
except FileNotFoundError:
    print(f"Файл не найден!")
    sys.exit(1)
except Exception as e:
    print(f"Ошибка при чтении файла: {e}")
    sys.exit(1)

found_words = find_words(text)

if found_words:
    print(f"Количество слов: {len(found_words)}")

    for i, word in enumerate(found_words, 1):
        print(f"{i}. {word}")
else:
    print("Слова, удовлетворяющие условиям, не найдены")
