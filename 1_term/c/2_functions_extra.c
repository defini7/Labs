#include <stdio.h>
#include <math.h>

double get_left_part_element(double x, int element_index /* starting from 1 */)
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
}
