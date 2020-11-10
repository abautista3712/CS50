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
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= 300; j++)
        {
            int blurAvgR = 0;
            int blurAvgG = 0;
            int blurAvgB = 0;
            // --- Column Edge Cases ---
            // Edge Case 1: COLUMN 1
            if (j == 0)
            {
                // --- Row Edge Cases ---
                // Row Edge Case 1: COLUMN 1, ROW 1
                if (i == 0)
                {
                    // Average current row and one row after
                    for (int k = i; k <= (i + 1); k++)
                    {
                        // Average current column and one column after
                        for (int l = j; l <= (j + 1); l++)
                        {
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 9);
                    blurAvgG = (blurAvgG / 9);
                    blurAvgB = (blurAvgB / 9);
                    image[i][j].rgbtRed = blurAvgR;
                    image[i][j].rgbtGreen = blurAvgG;
                    image[i][j].rgbtBlue = blurAvgB;
                }
                // Row Edge Case 2: COLUMN 1, ROW 6
                else if (i == height)
                {
                    // Average one row before and current row
                    for (int k = (i - 1); k <= i; k++)
                    {
                        // Average current column and one column after
                        for (int l = j; l <= (j + 1); l++)
                        {
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 9);
                    blurAvgG = (blurAvgG / 9);
                    blurAvgB = (blurAvgB / 9);
                    image[i][j].rgbtRed = blurAvgR;
                    image[i][j].rgbtGreen = blurAvgG;
                    image[i][j].rgbtBlue = blurAvgB;
                }
                // --- All Other Row Cases ---
                // COLUMN 1, ROWS 2-5
                else
                {
                    // Average one row before, current row, and one row after
                    for (int k = (i - 1); k <= (i + 1); k++)
                    {
                        // Average current column and one column after
                        for (int l = j; l <= (j + 1); l++)
                        {
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 9);
                    blurAvgG = (blurAvgG / 9);
                    blurAvgB = (blurAvgB / 9);
                    image[i][j].rgbtRed = blurAvgR;
                    image[i][j].rgbtGreen = blurAvgG;
                    image[i][j].rgbtBlue = blurAvgB;
                }
            }
            // Edge Case 2: COLUMN 6
            else if (j == (300 - 1))
            {
                // --- Row Edge Cases ---
                // Row Edge Case 1: COLUMN 6, ROW 1
                if (i == 0)
                {
                    // Average current row and one row after
                    for (int k = i; k <= i + 1; k++)
                    {
                        // Average one column before and current column
                        for (int l = (j - 1); l <= j; l++)
                        {
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 9);
                    blurAvgG = (blurAvgG / 9);
                    blurAvgB = (blurAvgB / 9);
                    image[i][j].rgbtRed = blurAvgR;
                    image[i][j].rgbtGreen = blurAvgG;
                    image[i][j].rgbtBlue = blurAvgB;
                }
                // Row Edge Case 2: COLUMN 6, ROW 6
                else if (i == (height - 1))
                {
                    // Average one row before and current row
                    for (int k = (i - 1); k <= i; k++)
                    {
                        // Average one column before and current column
                        for (int l = (j - 1); l <= j; l++)
                        {
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 9);
                    blurAvgG = (blurAvgG / 9);
                    blurAvgB = (blurAvgB / 9);
                    image[i][j].rgbtRed = blurAvgR;
                    image[i][j].rgbtGreen = blurAvgG;
                    image[i][j].rgbtBlue = blurAvgB;
                }
                // --- All Other Row Cases ---
                // COLUMN 6, ROWS 2-5
                else
                {
                    // Average one row before, current row, and one row after
                    for (int k = (i - 1); k <= (i + 1); k++)
                    {
                        // Average one column before and current column
                        for (int l = (j - 1); l <= j; l++)
                        {
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 9);
                    blurAvgG = (blurAvgG / 9);
                    blurAvgB = (blurAvgB / 9);
                    image[i][j].rgbtRed = blurAvgR;
                    image[i][j].rgbtGreen = blurAvgG;
                    image[i][j].rgbtBlue = blurAvgB;
                }
            }
            // --- All Other Column Cases ---
            // COLUMNS 2-5
            else
            {
                // --- Row Edge Cases ---
                // Row Edge Case 1: COLUMNS 2-5, ROW 1
                if (i == 0)
                {
                    // Average one row before, current row, and one row after
                    for (int k = i; k <= (i + 1); k++)
                    {
                        // Average one column before, current column and one column after
                        for (int l = (j - 1); l <= (j + 1); l++)
                        {
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 9);
                    blurAvgG = (blurAvgG / 9);
                    blurAvgB = (blurAvgB / 9);
                    image[i][j].rgbtRed = blurAvgR;
                    image[i][j].rgbtGreen = blurAvgG;
                    image[i][j].rgbtBlue = blurAvgB;
                }
                // Row Edge Case 2: COLUMNS 2-5, ROW 6
                else if (i == (height - 1))
                {
                    // Average one row before, current row, and one row after
                    for (int k = (i - 1); k <= i; k++)
                    {
                        // Average one column before, current column and one column after
                        for (int l = (j - 1); l <= (j + 1); l++)
                        {
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 9);
                    blurAvgG = (blurAvgG / 9);
                    blurAvgB = (blurAvgB / 9);
                    image[i][j].rgbtRed = blurAvgR;
                    image[i][j].rgbtGreen = blurAvgG;
                    image[i][j].rgbtBlue = blurAvgB;
                }
                // --- All Other Row Cases ---
                // COLUMNS 2-5, ROWS 2-5
                else
                {
                    // Average one row before, current row, and one row after
                    for (int k = (i - 1); k <= (i + 1); k++)
                    {
                        // Average one column before, current column and one column after
                        for (int l = (j - 1); l <= (j + 1); l++)
                        {
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 9);
                    blurAvgG = (blurAvgG / 9);
                    blurAvgB = (blurAvgB / 9);
                    image[i][j].rgbtRed = blurAvgR;
                    image[i][j].rgbtGreen = blurAvgG;
                    image[i][j].rgbtBlue = blurAvgB;
                }
            }
        }
    }
    return;
}
