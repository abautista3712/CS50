#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = (int)(round(.393 * image[i][j].rgbtRed) + round(.769 * image[i][j].rgbtGreen) + round(.189 * image[i][j].rgbtBlue));
            int sepiaGreen = (int)(round(.349 * image[i][j].rgbtRed) + round(.686 * image[i][j].rgbtGreen) + round(.168 * image[i][j].rgbtBlue));
            int sepiaBlue = (int)(round(.272 * image[i][j].rgbtRed) + round(.534 * image[i][j].rgbtGreen) + round(.131 * image[i][j].rgbtBlue));

            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    // void swap(int *a, int *b)
    // {
    //     int tmp = *a;
    //     *a = *b;
    //     *b = tmp;
    // }
    // for (int i = 0; i < height; i++)
    // {
    //     for (int j = 0; j < width; j++)
    //     {

    //         image[i][j].rgbtRed = avg;
    //         image[i][j].rgbtGreen = avg;
    //         image[i][j].rgbtBlue = avg;
    //     }
    // }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Calculate blur average value
    // int blurAvgR = 0;
    // int blurAvgG = 0;
    // int blurAvgB = 0;

    // Column Number
    for (int i = 0; i <= 6; i++)
    {
        // Row Number
        for (int j = 0; j <= 6; j++)
        {
            printf("%i ", image[i][j].rgbtRed);
            // Edge Cases
            if (j == 0 || j == 6)
            {
                // printf("[] ");
            }
            // Sum One Row Value Before and One Row Value After
            else
            {
                int blurAvgR = 0;
                if (i == 0 || i == 6)
                {
                }
                else
                {
                    for (int k = (i - 1); k <= (i + 1); k++)
                    {
                        for (int l = (j - 1); l <= (j + 1); l++)
                        {
                            blurAvgR += image[k][l].rgbtRed;
                        }
                    }
                }
                printf("[%i] ", blurAvgR);
            }
        }

        // printf("= %i", blurAvgR);
        printf("\n");
    }
    return;
}
