#include <stdio.h>
#include <math.h>

double calculate_left_part(double x, int elements_count);
double calculate_right_part(double x);

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
        
        double left = calculate_left_part(x, elements_count);
        double right = calculate_right_part(x);
        
        printf("Result BY formula: %f\n", left);
        printf("Result WITHOUT formula: %f\n", right);
        
        printf("Error: %f\n", fabs(right - left));
        
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

double calculate_left_part(double x, int elements_count)
{
    double sum = 0.0;
    double numerator = 1.0;
    double denominator = 1.0;
    
    for (int i = 1; i <= elements_count; i++)
    {
        numerator *= (double)i;
        denominator *= x + (double)i;
        
        sum += numerator / denominator;
    }
    
    return sum;
}

double calculate_right_part(double x)
{
    return 1.0 / (x - 1.0);
}
