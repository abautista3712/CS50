#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask user what their name is and save value of string in variable 'name'
    string name = get_string("What is your name?\n");

    // Print formatted text with variable 'name'
    printf("hello, %s\n", name);
}