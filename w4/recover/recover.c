#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    BYTE buffer[512];

    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen("argv[1]", "r");
    if (file == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    fread(buffer, 3, 1, file);

    if (buffer[0] == 0xff &&
        buffer[1] == 0xd8 &&
        buffer[2] == 0xff &&
        (buffer[3] && 0xf0 == 0xe0))
    {
        printf("Maybe\n");
    }
    else
    {
        printf("No\n");
    }

    fclose(file);
}
