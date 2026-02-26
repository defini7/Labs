#include <iostream>
#include <print>
#include <sstream>
#include <string>
#include <optional>
#include <fstream>

struct Words
{
	std::string* data = nullptr;
	size_t count;

	Words(size_t count = 0) : count(count)
	{
		if (count == 0) return;
		if (data) delete[] data;
		data = new std::string[count];
	}

	Words(const Words& other)
	{
		count = other.count;

		if (data) delete[] data;
		data = new std::string[count];

		std::memcpy(data, other.data, sizeof(std::string) * count);
	}

	~Words()
	{
		if (data)
			delete[] data;

		count = 0;
	}

};

char get_char(const std::string_view message);

std::optional<std::string> read_file(const std::string_view filename);

bool write_file(const std::string_view filename, const Words& words);

std::string get_string(const std::string_view message);

bool get_approval(const std::string_view message);

std::optional<std::string> get_input();

size_t count_words(const std::string_view text);

std::optional<Words> find_words(const std::string_view text);

bool is_palindrome(const std::string_view word);

std::optional<Words> find_palindromes(const std::string_view text);

int main()
{
	do
	{
		// Получаем данные с файла/клавиатуры
		std::optional<std::string> data = get_input();

        if (!data)
        {
            std::cout << "No data has been read!" << std::endl;
            continue;
        }

		// Ищем палиндромы
		std::optional<Words> palindromes = find_palindromes(*data);
		for (int i = 0; i < palindromes->count; i++)
			std::print("{}) {}\n", i + 1, palindromes->data[i]);

		// Спрашиваем, хочет ли пользователь записать найденные палиндромы в файл
		if (get_approval("Would you like to write everything into a file? (y/n)"))
			write_file("output.txt", *palindromes);
	}
	while (get_approval("Would you like to rerun the program? (y/n)"));

	return 0;
}

char get_char(const std::string_view message)
{
	char c;

	std::cout << message << ": ";
	std::cin >> c;

	return c;
}

std::optional<std::string> read_file(const std::string_view filename)
{
	std::ifstream ifs(filename.data());
	if (!ifs.is_open()) return std::nullopt;

	std::ostringstream ss;
	ss << ifs.rdbuf();
	return ss.str();
}

bool write_file(const std::string_view filename, const Words& words)
{
	std::ofstream ofs(filename.data());
	if (!ofs.is_open()) return false;

	for (int i = 0; i < words.count; i++)
		ofs << words.data[i] << std::endl;

	return true;
}

std::string get_string(const std::string_view message)
{
	std::cout << message << ": ";
	
	std::string s;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, s);

	s.append(1, '\n');

	return s;
}

bool get_approval(const std::string_view message)
{
	char answer;
	do
	{
		answer = tolower(get_char(message));
	} while (answer != 'y' && answer != 'n');

	return answer == 'y';
}

std::optional<std::string> get_input()
{
	// Спрашиваем откуда хотим считать данные: с файла или с консоли
	if (get_approval("Would you like to read a string from a file? (y/n)"))
	{
		// Считываем с файла
		return read_file("input.txt");
	}
	
	// Считываем с консоли
	return get_string("Enter a string");
}

size_t count_words(const std::string_view text)
{
	if (text.empty()) return 0;

	bool reading_invalid_symbols = true;
	size_t count = 0;

	for (char c : text)
	{
		// Проверяем, что текущий символ не пробел и не знак пунктуации
		if (!isalpha(c))
		{
			// Если так оказалось, то будем пропускать их
			reading_invalid_symbols = true;
		}
		else if (reading_invalid_symbols)
		{
			// Как только пропустили все ненужные символы,
			// прибавляем счетчик слов
			reading_invalid_symbols = false;
			count++;
		}
	}

	return count;
}

std::optional<Words> find_words(const std::string_view text)
{
	Words words(count_words(text));
	if (!words.data) return std::nullopt;

	// Сохраняем указатель на текущее слово
	size_t start = -1;
	size_t i = 0;
	std::string* current_word = words.data;

	bool parsing_word = false;

	for (char c : text)
	{
		// Является ли символ буквой? ...
		if (isalpha(c))
		{
			// ... Да! Поэтому, если мы на данный момент еще
			// не парсим другое слово, то сохраняем индекс начала слова
			if (!parsing_word)
			{
				start = i;
				parsing_word = true;
			}
		}
		else
		{
			// ... Нет! Значит, что если мы на данный момент парсим слово,
			// то оно должно было закончиться
			if (parsing_word)
			{
				size_t chars_count = i - start;

				// Сохраняем слово
				std::string s(text.substr(start, chars_count));
				*current_word = s;

				// Сбрасываем вспомогательные переменные
				parsing_word = false;
				start = -1;

				// Переходим на следующее слово
				current_word++;
			}

			// Если мы не парсим слово и текущий символ не буква, то просто пропускаем его
		}

		i++;
	}

	return words;
}

bool is_palindrome(const std::string_view word)
{
	size_t len = word.length();

	for (int i = 0; i < len / 2; i++)
	{
		if (tolower(word[i]) != tolower(word[len - i - 1]))
			return false;
	}

	return true;
}

std::optional<Words> find_palindromes(const std::string_view text)
{
	// Разбиваем текст на слова
	std::optional<Words> words = find_words(text);
	if (!words) return std::nullopt;

	size_t palindromes_count = 0;

	// Будем хранит индексы на палиндромы
	size_t* palindromes_indecies = new size_t[words->count];
	if (!palindromes_indecies)
	{
		// Освобождаем память
		return std::nullopt;
	}

	for (size_t i = 0; i < words->count; i++)
	{
		// Если слово является палиндромом, то сохраняем на него индекс
		// и увеличиваем счетчик палиндромов
		if (is_palindrome(words->data[i]))
			palindromes_indecies[palindromes_count++] = i;
	}

	// Не нашли палиндромы
	if (palindromes_count == 0)
		return std::nullopt;

	// Выделяем память под палиндромы
	Words palindromes(palindromes_count);
	if (!palindromes.data)
	{
		delete[] palindromes_indecies;
		return std::nullopt;
	}

	for (size_t i = 0; i < palindromes_count; i++)
		palindromes.data[i] = words->data[palindromes_indecies[i]];

	delete[] palindromes_indecies;
	return palindromes;
}
