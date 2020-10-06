#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long creditNum;
    do
    {
        creditNum = get_long("Input CC number to see if valid: ");
    }

    while (creditNum <= 0);
    {
        printf("%li\n", creditNum);
    }
}