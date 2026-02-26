/*
* 27 задача
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUMS_COUNT 10

int main()
{
    float nums[NUMS_COUNT];
    int running;
    
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
    
            printf("Generated array = { ");
    
            for (int i = 0; i < NUMS_COUNT; i++)
            {
                nums[i] = start + (float)rand() / (float)RAND_MAX * range;
                printf("%f ", nums[i]);
            }
    
            printf("}\n");
        }
        else
        {
            for (int i = 0; i < NUMS_COUNT; i++)
            {
                do
                {
                    printf("Enter element %d = ", i);
                    scanf("%f", &nums[i]);
                } while (nums[i] < 0);
            }
        }
        
        float left_sum = 0;
        float right_sum = 0;
        
        for (int i = 1; i < NUMS_COUNT; i++)
            right_sum += nums[i];
            
        float min_diff = right_sum;
        int answer = 0;
            
        for (int i = 0; i < NUMS_COUNT - 1; i++)
        {
            float diff = fabs(left_sum - right_sum);
            
            if (diff < min_diff)
            {
                min_diff = diff;
                answer = i;
            }
            
            left_sum += nums[i];
            right_sum -= nums[i + 1];
        }
        
        printf("Index = %d\nDifference = %f\n", answer, min_diff);
        
        printf("Would you like to continue or exit the program? (1/0) ");
        scanf("%d", &running);
    }
    while (running == 1);

    return 0;
}

/*#include <stdio.h>
#include <math.h>

double get_left_part_element(double x, int element_index /* starting from 1 *//*)
{
    if (element_index == 0)
        return 1.0;

    return (double)element_index / (x + (double)element_index) * get_left_part_element(x, element_index - 1);
}

double get_left_part(double x, int elements_count)
{
    if (elements_count == 1)
        return 1.0 / (x + 1.0);

    return get_left_part_element(x, elements_count) + get_left_part(x, elements_count - 1);
}

double get_right_part(double x)
{
    return 1.0 / (x - 1.0);
}

int main()
{
    double x = 0.0;
    
    int running = 0;
    int elements_count = 0;
    
    do
    {
        do
        {
            printf("Enter X: ");
            scanf("%lf", &x);
        }
        while (x <= 1.0);
        
        do
        {
            printf("Enter number of elements: ");
            scanf("%d", &elements_count);
        }
        while (elements_count <= 0);
        
        double left = get_left_part(x, elements_count);
        double right = get_right_part(x);
        
        printf("Left part: %lf\n", left);
        printf("Right part: %lf\n", right);
        
        printf("Error: %lf\n", fabs(right - left));
        
        do
        {
            printf("Continue? (1/0): ");
            scanf("%d", &running);
        }
        while (running != 0 && running != 1);
    }
    while (running == 1);
    
    return 0;
}*/

