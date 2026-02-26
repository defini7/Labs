// Задача 27

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 4
#define HEIGHT 4

int main()
{
    int running;

    float input[HEIGHT][WIDTH];
    float output[HEIGHT][WIDTH];

    do
    {
        int is_randomly_generated;
    
        do
        {
            printf("Would you like to generate values randomly? (1/0) ");
            scanf("%d", &is_randomly_generated);
        }
        while (is_randomly_generated != 0 && is_randomly_generated != 1);
    
        if (is_randomly_generated == 1)
        {
            float start, end;
    
            do
            {
                printf("Enter start of a range = ");
                scanf("%f", &start);
    
                printf("Enter end of the range = ");
                scanf("%f", &end);
            }
            while (start < 0.0f || end < 0.0f);
            
            if (start > end)
            {
                float temp = start;
                start = end;
                end = temp;
            }
    
            float range = end - start + 1.0f;
    
            if ((int)range >= RAND_MAX)
                printf("Warning: your range length exceeds RAND_MAX=%d!\n", RAND_MAX);
    
            srand(time(NULL));

            for (int i = 0; i < HEIGHT; i++)
                for (int j = 0; j < WIDTH; j++)
                    input[i][j] = start + (float)rand() / (float)RAND_MAX * range;
    
            printf("Generated matrix:\n");
    
            for (int i = 0; i < HEIGHT; i++)
            {
                for (int j = 0; j < WIDTH; j++)
                    printf("%f ", input[i][j]);

                putchar('\n');
            }
    
            putchar('\n');
        }
        else
        {
            printf("Enter your %dx%d matrix:\n", WIDTH, HEIGHT);

            for (int i = 0; i < HEIGHT; i++)
                for (int j = 0; j < WIDTH; j++)
                    scanf("%f", &input[i][j]);
        }

        int sort_direction = -1;

        if (WIDTH == HEIGHT)
        {
            for (int i = 0; i < HEIGHT - 1; i++)
            {
                int last = WIDTH - 1 - i;

                for (int j = 0; j < last; j++)
                    if (input[i][j] != input[HEIGHT - 1 - j][last])
                    {
                        sort_direction = 1;
                        break;
                    }
            }
        }
        else
            sort_direction = 1;

        for (int i = 0; i < WIDTH; i++)
        {
            output[HEIGHT - 2][i] = input[HEIGHT - 1][i];
            output[HEIGHT - 1][i] = i;
        }

        float temp_index;
        int swapped = 1;

        for (int i = 0; i < WIDTH - 1 && swapped == 1; i++)
        {
            swapped = 0;

            for (int j = 0; j < WIDTH - 1 - i; j++)
            {
                float current_value = output[HEIGHT - 2][j];
                float next_value = output[HEIGHT - 2][j + 1];

                if ((current_value > next_value) && sort_direction == 1 || (current_value < next_value) && sort_direction == -1)
                {
                    output[HEIGHT - 2][j] = output[HEIGHT - 2][j + 1];
                    output[HEIGHT - 2][j + 1] = current_value;

                    temp_index = output[HEIGHT - 1][j];

                    output[HEIGHT - 1][j] = output[HEIGHT - 1][j + 1];
                    output[HEIGHT - 1][j + 1] = temp_index;

                    swapped = 1;
                }
            }
        }

        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                output[i][j] = input[i][(int)output[HEIGHT - 1][j]];

        printf("Output:\n");

        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
                printf("%f ", output[i][j]);

            putchar('\n');
        }

        do
        {
            printf("Would you like to continue or exit the program? (1/0) ");
            scanf("%d", &running);
        }
        while (running != 0 && running != 1);
    }
    while (running == 1);

    return 0;
}
