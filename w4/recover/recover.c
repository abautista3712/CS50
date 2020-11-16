#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Declare Buffer Array
    typedef uint8_t BYTE;
    BYTE buffer[512];

    // Declare Target File
    FILE *img;

    // Check Usage: Require one command-line input
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open File
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    // Initialize Variables
    int JPEGcount = 0;
    bool JPEGfound = false;

    // Read/Recover JPEG Data
    while (fread(&buffer, sizeof(buffer), 1, file) == 1)
    {
        char filename[8];

        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (JPEGcount == 0)
            {
                // Make New JPEG
                sprintf(filename, "%03i.jpg", JPEGcount);
                img = fopen(filename, "w");

                // Write File
                fwrite(&buffer, sizeof(buffer), 1, img);

                printf("1st JPEG FOUND\n");
                JPEGfound = true;
                JPEGcount++;
            }
            else
            {
                // Close Previous JPEG
                fclose(img);

                // Make New JPEG
                sprintf(filename, "%03i.jpg", JPEGcount);
                img = fopen(filename, "w");

                // Write File
                fwrite(&buffer, sizeof(buffer), 1, img);

                JPEGcount++;
                printf("JPEG FOUND\n");
                printf("%i\n", JPEGcount);
            }
        }
        else
        {
            if (JPEGfound == true)
            {
                fwrite(&buffer, sizeof(buffer), 1, img);

                printf("...\n");
            }
            else
            {
                printf("END\n");
            }
        }
    }
    fclose(file);
}
