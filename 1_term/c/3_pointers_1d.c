/*
* 27 задача
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void generate_randomly(float* nums, int nums_count)
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

    srand(time(0));

    for (float* num = nums; num != nums + nums_count; num++)
        *num = start + (float)rand() / (float)RAND_MAX * range;
}

void get_from_keyboard(float* nums, int nums_count)
{
    for (float* num = nums; num != nums + nums_count; num++)
    {
        do
        {
            printf("Enter element = ");
            scanf("%f", num);
        } while (*num < 0);
    }
}

void get_input(float** nums, int* nums_count)
{
    do
    {
        printf("Enter the size of an array (> 0) = ");
        scanf("%d", nums_count);
    } while (*nums_count <= 0);
    
    *nums = (float*)calloc(*nums_count, sizeof(float));
    
    int is_randomly_generated;
    
    do
    {
        printf("Would you like to generate values randomly? (1/0) ");
        scanf("%d", &is_randomly_generated);
    }
    while (is_randomly_generated != 0 && is_randomly_generated != 1);

    if (is_randomly_generated == 1)
        generate_randomly(*nums, *nums_count);
    else
        get_from_keyboard(*nums, *nums_count);
}

void print_float_array(float* array, int size)
{
    printf("Array = { ");
    
    for (float* elem = array; elem != array + size; elem++)
        printf(" %f", *elem);
        
    printf(" }\n");
}

int solve(float* nums, int nums_count, float* min_diff)
{
    float left_sum = 0.0f;
    float right_sum = 0.0f;
    
    for (float* num = nums + 1; num != nums + nums_count; num++)
        right_sum += *num;
        
    *min_diff = right_sum;
    int index = 0;
        
    for (int i = 0; i < nums_count - 1; i++)
    {
        float diff = fabs(left_sum - right_sum);
        
        if (diff < *min_diff)
        {
            *min_diff = diff;
            index = i;
        }
        
        left_sum += *(nums + i);
        right_sum -= *(nums + i + 1);
    }
    
    return index;
}

int main()
{
    float* nums;
    int nums_count;
    int running;
    
    do
    {
        get_input(&nums, &nums_count);
        print_float_array(nums, nums_count);
        
        float min_diff;
        int index = solve(nums, nums_count, &min_diff);
        
        free(nums);
        
        printf("Index = %d\nDifference = %f\n", index, min_diff);
        
        printf("Would you like to continue or exit the program? (1/0) ");
        scanf("%d", &running);
    }
    while (running == 1);

    return 0;
}
