#include <stdio.h>

int main()
{
    double numerator;
    double denominator;
    double sum;
    
    double x = 0.0;
    int n = 0;
    int running = 0;
    
    do
    {
        numerator = 1.0;
        denominator = 1.0;
        sum = 0.0;
        
        do
        {
            printf("Enter X: ");
            scanf("%lf", &x);
        } while (x <= 1.0);
        
        do
        {
            printf("Enter N: ");
            scanf("%d", &n);
        } while (n <= 0);
        
        for (int i = 1; i <= n; i++)
        {
            numerator *= (double)i;
            denominator *= x + (double)i;
            
            sum += (double)numerator / (double)denominator;
        }
        
        double formula = 1.0 / (x - 1.0);
        
        printf("Result BY formula: %f\n", formula);
        printf("Result WITHOUT formula: %f\n", sum);
        
        printf("Error: %f\n", formula - sum);
        
        do
        {
            printf("Continue? (1/0): ");
            scanf("%d", &running);
        } while (running != 0 && running != 1);
        
    } while (running == 1);
    
    return 0;
}