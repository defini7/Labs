#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Ограничимся размером буффера для сохранения строк, считанных с терминала
#define CAP_SIZE 256

// Небезопасно получаем символ с клавиатуры
char get_char(const char* message);

// Считываем все символы из файла
// Возвращаемое значение: NULL - если не удалось открыть файл или выделить память под буффер,
// а иначе - указатель на считанные символы
// Параметры: size - длинна строки без '\0'
char* read_file(const char* filename, int* size);

// Записывает слова в текст
// Параметры:
// 1) filename - имя файла для записи
// 1) words - слова для записи
// 2) words_count - кол-во слов для записи
// Возвращаемое значение:
// 1) true - все было успешно записано
// 2) false - не открылся файл или не записалось слово
bool write_file(const char* filename, char** words, int words_count);

// !!! ОСТОРОЖНО !!! Небезопасная функция
// Считываем строку с консоли (максимальная длина строки CAP_SIZE)
// Параметры: message - перед считыванием выведем в консоль: "<message>: "
// Возвращаемое значение: указатель на строку
char* read_from_console(const char* message);

// Если с клавиатуры получаем y/Y, то возвращаем true, а если n/N, то false
// Если ввели не y/Y/n/N, то просим ввести заново
bool get_approval(const char* message);

// Считываем строку с файла или с консоли
// Параметры: length - длина строки, которая установится внутри функции
// Возвращаемое значение:
// 1) NULL - если не удалось выделить память под строку или не открылся файл
// 2) Указатель на строку - в остальных случаях
char* get_input(int* length);

// Считает слова в тексте
// Параметры: text - массив символов с 0 в конце
// Возвращаемое значение: 0 - если text == NULL
int count_words(const char* text);

// Ищет все слова в тексте
// 
// Параметры:
// 1) text - текст, который будем разбивать на слова
// 2) words_count - кол-во слов, которое будет установлено внутри функции
// 
// Возвращаемое значение:
// 1) NULL - нет слов в тексте или не удалось выделить память под слово или массив слов,
// 2) Указатель на массив слов - в остальных случаях
char** find_words(const char* text, int* words_count);

// Возвращает true, если слово является палиндромом, а иначе - false
bool is_palindrome(const char* word);

// Ищет палиндромы в тексте
// Параметры:
// 1) text - текст, в котором будем искать палиндромы
// 2) palindromes_count - кол-во палиндромов в тексте, которое установится внутри функции
// Возвращаемое значение:
// 1) NULL - не удалось выделить память или найти палиндромы
// 2) Указатель на массив с палиндромами - в остальных случаях
char** find_palindromes(const char* text, int* palindromes_count);

int main()
{
	do
	{
		// Получаем данные с файла/клавиатуры
		int size;
		char* data = get_input(&size);

        if (!data)
        {
            printf("No data has been read!\n");
            continue;
        }

		// Ищем палиндромы
		int palindromes_count;
		char** palindromes = find_palindromes(data, &palindromes_count);

		for (int i = 0; i < palindromes_count; i++)
			printf("%d) %s\n", i + 1, palindromes[i]);

		// Спрашиваем, хочет ли пользователь записать найденные палиндромы в файл
		if (get_approval("Would you like to write everything into a file? (y/n)"))
			write_file("output.txt", palindromes, palindromes_count);

		// Освобождаем память

		for (int i = 0; i < palindromes_count; i++)
			free(palindromes[i]);

		free(palindromes);
		free(data);
	}
	while (get_approval("Would you like to rerun the program? (y/n)"));

	return 0;
}

char get_char(const char* message)
{
	// 0 - символ, 1 - \n
	char s[2];

	printf("%s ", message);

	// Считываем символ и новую строку
	scanf("%s", &s);

	// Возвращаем только символ
	return s[0];
}

char* read_file(const char* filename, int* size)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL) return NULL;

	// Получаем размер файла
	fseek(file, 0, SEEK_END);
	*size = ftell(file);
	rewind(file);

	// Выделяем память под строку
	char* buffer = (char*)malloc(*size + 1);
	if (!buffer) return NULL;

	// Считываем все символы
	int c, i = 0;
	while ((c = fgetc(file)) != EOF)
		buffer[i++] = c;

	buffer[*size] = '\0';

	fclose(file);
	return buffer;
}

bool write_file(const char* filename, char** words, int words_count)
{
	FILE* file = fopen(filename, "w");
	if (!file) return false;

	for (int i = 0; i < words_count; i++)
	{
		int bytes = strlen(words[i]);

		// Записываем слово в файл и проверям на успешность
		// (количество записанных байтов и размер слова должны совпадать)
		if (fwrite(words[i], sizeof(char), bytes, file) != bytes)
			return false;

		// Переходим на новую строку
		if (fwrite("\n", sizeof(char), 1, file) != 1)
			return false;
	}

	fclose(file);
	return true;
}

char* read_from_console(const char* message)
{
	char* data = (char*)malloc(CAP_SIZE);
	if (!data) return NULL;

	printf("%s: ", message);
	getchar();
	fgets(data, CAP_SIZE, stdin);

	return data;
}

bool get_approval(const char* message)
{
	char answer;
	do
	{
		answer = tolower(get_char(message));
	} while (answer != 'y' && answer != 'n');

	return answer == 'y';
}

char* get_input(int* length)
{
	// Спрашиваем откуда хотим считать данные (с файла или с консоли)
	char* data;

	if (get_approval("Would you like to enter a string from a file? (y/n)"))
	{
		// Считываем с файла
		data = read_file("input.txt", length);
	}
	else
	{
		// Считываем с консоли
		data = read_from_console("Enter a string");
		if (data) *length = strlen(data);
	}

	return data;
}

int count_words(const char* text)
{
	if (!text) return 0;

	bool reading_invalid_symbols = true;
	int count = 0;

	while (*text)
	{
		// Проверяем, что текущий символ не пробел и не знак пунктуации
		if (!isalpha(*text))
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

		text++;
	}

	return count;
}

char** find_words(const char* text, int* words_count)
{
	// Считаем слова
	*words_count = count_words(text);
	if (*words_count == 0) return NULL;

	// Выделяем память под слова
	char** words = (char**)calloc(*words_count, sizeof(char*));
	if (!words) return NULL;

	// Сохраняем указатель на текущее слово
	char** current_word = words;
	int start = -1;

	bool parsing_word = false;

	for (int i = 0; text[i] != '\0'; i++)
	{
		// Является ли символ буквой? ...
		if (isalpha(text[i]))
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
				int chars_count = i - start;

				// Выделяем память под слово
				*current_word = (char*)calloc(chars_count + 1, sizeof(char));
				if (!(*current_word)) return words;

				// Переносим слово в буффер
				strncpy(*current_word, text + start, chars_count);

				// Ставим в конец 0
				(*current_word)[chars_count] = '\0';

				// Сбрасываем вспомогательные переменные
				parsing_word = false;
				start = -1;

				// Переходим на следующее слово
				current_word++;
			}

			// Если мы не парсим слово и текущий символ не буква, то просто пропускаем его
		}
	}

	return words;
}

bool is_palindrome(const char* word)
{
	int length = strlen(word);

	for (int i = 0; i < length / 2; i++)
	{
		if (word[i] != word[length - i - 1])
			return false;
	}

	return true;
}

char** find_palindromes(const char* text, int* palindromes_count)
{
	int words_count;
	*palindromes_count = 0;

	// Разбиваем текст на слова
	char** words = find_words(text, &words_count);
	if (!words) return NULL;

	// Будем хранит индексы на палиндромы
	int* palindromes_indecies = (int*)calloc(words_count, sizeof(int));
	if (!palindromes_indecies)
	{
		// Освобождаем память
		for (int i = 0; i < words_count; i++) free(words[i]);
		free(words);
		return NULL;
	}

	for (int i = 0; i < words_count; i++)
	{
		// Если слово является палиндромом, то сохраняем на него индекс
		// и увеличиваем счетчик палиндромов
		if (is_palindrome(words[i]))
		{
			palindromes_indecies[*palindromes_count] = i;
			(*palindromes_count)++;
		}
	}

	// Не нашли палиндромы
	if (*palindromes_count == 0)
		return NULL;

	// Выделяем память под палиндромы
	char** palindromes = (char**)calloc(*palindromes_count, sizeof(char*));
	if (!palindromes)
	{
		// Освобождаем память
		for (int i = 0; i < words_count; i++) free(words[i]);
		free(words);
		free(palindromes_indecies);
		return NULL;
	}

	for (int i = 0; i < *palindromes_count; i++)
	{
		// Получаем палиндром по индексу
		char* word = words[palindromes_indecies[i]];

		// Выделяем память под палиндром
		palindromes[i] = (char*)calloc(strlen(word) + 1, sizeof(char));
		if (!palindromes[i])
		{
			// Освобождаем память
			for (int j = 0; j < words_count; j++) free(words[j]);
			for (int j = 0; j < i; j++) free(palindromes[j]);
			free(words);
			free(palindromes);
			return NULL;
		}

		// Переносим символы в палиндром
		strcpy(palindromes[i], word);
	}

	for (int i = 0; i < words_count; i++)
		free(words[i]);

	free(words);
	free(palindromes_indecies);

	return palindromes;
}
