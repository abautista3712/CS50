#include <stdio.h>
#include <cs50.h>

int main(void)
{
    float n;
    n = get_float("Input total change owed: ");
    printf("%.2f\n", n);
}