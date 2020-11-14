#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Declare Buffer Array
    typedef uint8_t BYTE;
    BYTE buffer[512];

    // Require one command-line input
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open File
    FILE *file = fopen("argv[1]", "r");
    if (file == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    // Read/Recover JPEG Data
    while (fread(buffer, sizeof(buffer), 1, file) == 1)

        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] == 0xe0 ||
             buffer[3] == 0xe1 ||
             buffer[3] == 0xe2 ||
             buffer[3] == 0xe3 ||
             buffer[3] == 0xe4 ||
             buffer[3] == 0xe5 ||
             buffer[3] == 0xe6 ||
             buffer[3] == 0xe7 ||
             buffer[3] == 0xe8 ||
             buffer[3] == 0xe9 ||
             buffer[3] == 0xea ||
             buffer[3] == 0xeb ||
             buffer[3] == 0xec ||
             buffer[3] == 0xed ||
             buffer[3] == 0xee ||
             buffer[3] == 0xef))
        {
            printf("Maybe\n");
        }
        else
        {
            printf("No\n");
        }

    fclose(file);
}
