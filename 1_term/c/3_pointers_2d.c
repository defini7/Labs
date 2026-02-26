// Задача 27

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Меняем местами float
void SwapFloat(float* a, float* b);

// Заполняем матрицу data числами от rangeStart до rangeEnd
void FillRandomly(float** data, int width, int height, float rangeStart, float rangeEnd);\

// Вводим матрицу размером width на height в data
void InputMatrix(float** data, int width, int height);

// Выделяем память под 2D массив
float** Allocate2DArray(int width, int height);

// Освобождаем 2D массив
void Free2DArray(float** data, int width);

// Выводим 2D массив
void Print2DArray(float** data, int width, int height);

// Вводим промежуток, в котором будут генерироваться числа
void InputRange(float* start, float* end);

// Вводим размеры матрицы с клавиатуры
void InputSize(int* width, int* height);

// Спрашиваем пользователя, хочет ли он выполнить алгоритм заново
void InputRunningFlag(int* running);

// Спрашиваем пользователя, хочет ли он сгенерировать числа случайным образом
int InputRandomFlag();

// Вводим данные с клавиатуры
float** GetInput(int* width, int* height);

// Решаем задачу 27
float** Solve(float** input, int width, int height);

int main()
{
    int running;

    do
    {
        int width, height;

        float** input = GetInput(&width, &height);
        float** output = Solve(input, width, height);

        // Выводим выходную матрицу и просим начать программу заново
        Print2DArray(output, width, height);
        InputRunningFlag(&running);

        // Освобождаем память
        Free2DArray(input, height);
        Free2DArray(output, height);
    } while (running == 1);

    return 0;
}

void SwapFloat(float* a, float* b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

void FillRandomly(float** data, int width, int height, float rangeStart, float rangeEnd)
{
    srand(time(NULL));

    float range = rangeEnd - rangeStart;

    if ((int)range >= RAND_MAX)
        printf("Warning: your range length exceeds RAND_MAX=%d!\n", RAND_MAX);

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            *(*(data + y) + x) = rangeStart + (float)rand() / (float)RAND_MAX * range;
}

void InputMatrix(float** data, int width, int height)
{
    printf("Enter your %dx%d matrix:\n", width, height);

    // Запрашиваем матрицу с клавиатуры
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            scanf("%f", *(data + y) + x);
}

float** Allocate2DArray(int width, int height)
{
    // Выделяем память под столбцы
    float** data = (float**)malloc(height * sizeof(float*)); // sizeof float**...

    for (int i = 0; i < height; i++)
    {
        // Выделяем память под столбцы
        *(data + i) = (float*)malloc(width * sizeof(float));
    }

    return data;
}

void Free2DArray(float** data, int width)
{
    // Освобождаем столбцы
    for (int i = 0; i < width; i++)
    {
        float* ptr = *(data + i);
        if (ptr) free(ptr);
        ptr = NULL;
    }

    // Освобождаем память под столбцы
    free(data);
    data = NULL;
}

void InputSize(int* width, int* height)
{
    // Спрашиваем ширину пока она <= 0
    do
    {
        printf("Enter the width: ");
        scanf("%d", width);
    } while (*width <= 0);

    // Спрашиваем высоту пока она <= 0
    do
    {
        printf("Enter the height: ");
        scanf("%d", height);
    } while (*height <= 0);
}

int InputRandomFlag()
{
    int generateRandomly;

    // Спрашиваем значение флага, пока оно не равно 1 или 0
    do
    {
        printf("Would you like to generate values randomly? (1/0) ");
        scanf("%d", &generateRandomly);
    } while (generateRandomly != 0 && generateRandomly != 1);

    return generateRandomly;
}

void InputRange(float* start, float* end)
{
    // Спрашиваем начало и конец отрезка, пока один из них меньше 0
    do
    {
        printf("Enter start of a range = ");
        scanf("%f", start);

        printf("Enter end of the range = ");
        scanf("%f", end);
    } while (*start < 0.0f || *end < 0.0f);

    // Меняем местами, если start > end
    if (*start > *end)
        SwapFloat(start, end);
}

void Print2DArray(float** data, int width, int height)
{
    putchar('\n');

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
            printf("%f ", *(*(data + y) + x));

        putchar('\n');
    }
}

float** GetInput(int* width, int* height)
{
    InputSize(width, height);

    float** input = Allocate2DArray(*width, *height);
    int generateRandomly = InputRandomFlag();

    if (generateRandomly == 1)
    {
        float start, end;
        InputRange(&start, &end);

        // Заполняем случайно и выводим
        FillRandomly(input, *width, *height, start, end);
        Print2DArray(input, *width, *height);
    }
    else
    {
        // Вводим с клавиатуры
        InputMatrix(input, *width, *height);
    }

    return input;
}

float** Solve(float** input, int width, int height)
{
    float** output = Allocate2DArray(width, height);

    // Если 1, то не симметрична и сортируем в порядке возрастания, а если 0, то симметрична
    // и сортируем в порядке убывания
    int sortDirection = 1;

    // Проверяем на симметричность только квадратные матрицы
    if (width == height)
    {
        sortDirection = -1;

        for (int y = 0; y < height - 1; y++)
        {
            int last = height - 1 - y;

            for (int x = 0; x < last; x++)
                if (*(*(input + y) + x) != *(*(input + height - 1 - x) + last))
                {
                    sortDirection = 1;
                    break;
                }
        }
    }

    // Сохраняем в последней строке output индексы последних элементов input,
    // а в предпоследней строке значения
    for (int x = 0; x < width; x++)
    {
        *(*(output + height - 2) + x) = *(*(input + height - 1) + x);
        *(*(output + height - 1) + x) = (float)x;
    }

    int swapped = 1;

    for (int y = 0; y < height - 1 && swapped == 1; y++)
    {
        swapped = 0;

        for (int x = 0; x < width - 1 - y; x++)
        {
            float currentValue = *(*(output + height - 2) + x);
            float nextValue = *(*(output + height - 2) + x + 1);

            if ((currentValue > nextValue) && sortDirection == 1 || (currentValue < nextValue) && sortDirection == -1)
            {
                // Меняем значения местами
                *(*(output + height - 2) + x) = *(*(output + height - 2) + x + 1);
                *(*(output + height - 2) + x + 1) = currentValue;

                // Меняем индексы местами
                SwapFloat(*(output + height - 1) + x, *(output + height - 1) + x + 1);

                swapped = 1;
            }
        }

        // Если swapped == 0, то ничего не поменяли местами => выходим из цикла
    }

    // До этого сортировали только индексы по значениям,
    // а теперь переносим значения в столбцах
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            *(*(output + y) + x) = *(*(input + y) + (int)(*(*(output + height - 1) + x)));

    // Таким образом избавились от дополнительного массива

    return output;
}

void InputRunningFlag(int* running)
{
    do
    {
        printf("Would you like to continue or exit the program? (1/0) ");
        scanf("%d", running);
    } while (*running != 0 && *running != 1);
}
