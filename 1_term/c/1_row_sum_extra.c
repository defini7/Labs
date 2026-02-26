#include <stdio.h>
#include <math.h>

int main()
{
    int running = 0;
    
    do
    {
        double numerator = 1.0;
        double denominator = 1.0;
        double sum = 0.0;
        
        double x = 0.0;
        double desiredError;
        
        do
        {
            printf("Enter X: ");
            scanf("%lf", &x);
        } while (x <= 1.0 || x == 2.0);
        
        printf("Enter desired error value: ");
        scanf("%lf", &desiredError);
        
        double formula = 1.0 / (x - 1.0);
        int n = 0;
        
        while (fabs(formula - sum) > desiredError)
        {
            double i = n + 1;
            
            numerator *= i;
            denominator *= (double)x + i;
            
            //printf("%lf %lf\n", numerator, denominator);
            
            sum += numerator / denominator;
            
            n++;
        }
        
        printf("Result BY formula: %lf\n", formula);
        printf("Result WITHOUT formula: %lf\n", sum);
        
        printf("Actual error value: %lf\n", formula - sum);
        printf("You need %d elements to reach desired error value\n", n);
        
        do
        {
            printf("Continue? (1/0): ");
            scanf("%d", &running);
        } while (running != 0 && running != 1);
        
    } while (running == 1);
    
    return 0;
}