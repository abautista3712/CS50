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
            int avg = round((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
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
            int sepiaRed = round((float)(.393 * image[i][j].rgbtRed) + (float)(.769 * image[i][j].rgbtGreen) + (float)(.189 * image[i][j].rgbtBlue));
            int sepiaGreen = round((float)(.349 * image[i][j].rgbtRed) + (float)(.686 * image[i][j].rgbtGreen) + (float)(.168 * image[i][j].rgbtBlue));
            int sepiaBlue = round((float)(.272 * image[i][j].rgbtRed) + (float)(.534 * image[i][j].rgbtGreen) + (float)(.131 * image[i][j].rgbtBlue));

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
    int reflectVal = (width - 1);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int tmpR = 0;
            int tmpG = 0;
            int tmpB = 0;

            tmpR = image[i][j].rgbtRed;
            tmpG = image[i][j].rgbtGreen;
            tmpB = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][reflectVal].rgbtRed;
            image[i][j].rgbtGreen = image[i][reflectVal].rgbtGreen;
            image[i][j].rgbtBlue = image[i][reflectVal].rgbtBlue;

            image[i][reflectVal].rgbtRed = tmpR;
            image[i][reflectVal].rgbtGreen = tmpG;
            image[i][reflectVal].rgbtBlue = tmpB;

            if (reflectVal >= 0)
            {
                reflectVal = reflectVal - 1;
            }
        }
        reflectVal = (width - 1);
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int originalR[height][width];
    int originalG[height][width];
    int originalB[height][width];

    // Calculate blur average value
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            int blurAvgR = 0;
            int blurAvgG = 0;
            int blurAvgB = 0;

            // printf("%i ", image[i][j].rgbtRed);
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
                            originalR[k][l] = image[k][l].rgbtRed;
                            originalG[k][l] = image[k][l].rgbtGreen;
                            originalB[k][l] = image[k][l].rgbtBlue;
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 4);
                    blurAvgG = (blurAvgG / 4);
                    blurAvgB = (blurAvgB / 4);
                    image[i][j].rgbtRed = (int) blurAvgR;
                    image[i][j].rgbtGreen = (int) blurAvgG;
                    image[i][j].rgbtBlue = (int) blurAvgB;
                    // printf("[%i] ", image[i][j].rgbtRed);
                }
                // Row Edge Case 2: COLUMN 1, LAST ROW
                else if (i == (height - 1))
                {
                    // Average one row before and current row
                    for (int k = (i - 1); k <= i; k++)
                    {
                        // Average current column and one column after
                        for (int l = j; l <= (j + 1); l++)
                        {
                            // originalR[k][l] = image[k][l].rgbtRed;
                            // printf("originalR[%i][%i] = %i\n", k, l, originalR[k][l]);
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 4);
                    blurAvgG = (blurAvgG / 4);
                    blurAvgB = (blurAvgB / 4);
                    // printf("[%i] ", blurAvgR);
                    image[i][j].rgbtRed = (int) blurAvgR;
                    image[i][j].rgbtGreen = (int) blurAvgG;
                    image[i][j].rgbtBlue = (int) blurAvgB;
                }
                // --- All Other Row Cases ---
                // COLUMN 1, MIDDLE ROWS
                else
                {
                    // Average one row before, current row, and one row after
                    for (int k = (i - 1); k <= (i + 1); k++)
                    {
                        // Average current column and one column after
                        for (int l = j; l <= (j + 1); l++)
                        {
                            // originalR[k][l] = image[k][l].rgbtRed;
                            // printf("originalR[%i][%i] = %i\n", k, l, originalR[k][l]);
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 6);
                    blurAvgG = (blurAvgG / 6);
                    blurAvgB = (blurAvgB / 6);
                    // printf("[%i] ", blurAvgR);
                    image[i][j].rgbtRed = (int) blurAvgR;
                    image[i][j].rgbtGreen = (int) blurAvgG;
                    image[i][j].rgbtBlue = (int) blurAvgB;
                }
            }
            // Edge Case 2: LAST COLUMN
            else if (j == (width - 1))
            {
                // --- Row Edge Cases ---
                // Row Edge Case 1: LAST COLUMN, ROW 1
                if (i == 0)
                {
                    // Average current row and one row after
                    for (int k = i; k <= i + 1; k++)
                    {
                        // Average one column before and current column
                        for (int l = (j - 1); l <= j; l++)
                        {
                            // originalR[k][l] = image[k][l].rgbtRed;
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 4);
                    blurAvgG = (blurAvgG / 4);
                    blurAvgB = (blurAvgB / 4);
                    image[i][j].rgbtRed = (int) blurAvgR;
                    image[i][j].rgbtGreen = (int) blurAvgG;
                    image[i][j].rgbtBlue = (int) blurAvgB;
                }
                // Row Edge Case 2: LAST COLUMN, LAST ROW
                else if (i == (height - 1))
                {
                    // Average one row before and current row
                    for (int k = (i - 1); k <= i; k++)
                    {
                        // Average one column before and current column
                        for (int l = (j - 1); l <= j; l++)
                        {
                            // originalR[k][l] = image[k][l].rgbtRed;
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 4);
                    blurAvgG = (blurAvgG / 4);
                    blurAvgB = (blurAvgB / 4);
                    image[i][j].rgbtRed = (int) blurAvgR;
                    image[i][j].rgbtGreen = (int) blurAvgG;
                    image[i][j].rgbtBlue = (int) blurAvgB;
                }
                // --- All Other Row Cases ---
                // LAST COLUMN, MIDDLE ROWS
                else
                {
                    // Average one row before, current row, and one row after
                    for (int k = (i - 1); k <= (i + 1); k++)
                    {
                        // Average one column before and current column
                        for (int l = (j - 1); l <= j; l++)
                        {
                            // originalR[k][l] = image[k][l].rgbtRed;
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 6);
                    blurAvgG = (blurAvgG / 6);
                    blurAvgB = (blurAvgB / 6);
                    image[i][j].rgbtRed = (int) blurAvgR;
                    image[i][j].rgbtGreen = (int) blurAvgG;
                    image[i][j].rgbtBlue = (int) blurAvgB;
                }
            }
            // --- All Other Column Cases ---
            // MIDDLE COLUMNS
            else
            {
                // --- Row Edge Cases ---
                // Row Edge Case 1: MIDDLE COLUMNS, ROW 1
                if (i == 0)
                {
                    // Average current row and one row after
                    for (int k = i; k <= (i + 1); k++)
                    {
                        // Average one column before (from tmp value), current column and one column after
                        for (int l = (j - 1); l <= (j + 1); l++)
                        {
                            if (k == 0 && l == (j - 1))
                            {
                                blurAvgR = originalR[k][l];
                                blurAvgG = originalG[k][l];
                                blurAvgB = originalB[k][l];
                                l++;
                            }
                            originalR[k][l] = image[k][l].rgbtRed;
                            originalG[k][l] = image[k][l].rgbtGreen;
                            originalB[k][l] = image[k][l].rgbtBlue;

                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 6);
                    blurAvgG = (blurAvgG / 6);
                    blurAvgB = (blurAvgB / 6);
                    // printf("[%i] ", blurAvgR);
                    image[i][j].rgbtRed = blurAvgR;
                    image[i][j].rgbtGreen = blurAvgG;
                    image[i][j].rgbtBlue = blurAvgB;
                }
                // Row Edge Case 2: MIDDLE COLUMNS, LAST ROW
                else if (i == (height - 1))
                {
                    // Average one row before and current row
                    for (int k = (i - 1); k <= i; k++)
                    {
                        // Average one column before, current column and one column after
                        for (int l = (j - 1); l <= (j + 1); l++)
                        {
                            // originalR[k][l] = image[k][l].rgbtRed;
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 6);
                    blurAvgG = (blurAvgG / 6);
                    blurAvgB = (blurAvgB / 6);
                    image[i][j].rgbtRed = (int) blurAvgR;
                    image[i][j].rgbtGreen = (int) blurAvgG;
                    image[i][j].rgbtBlue = (int) blurAvgB;
                }
                // --- All Other Row Cases ---
                // MIDDLE COLUMNS, MIDDLE ROWS
                else
                {
                    // Average one row before, current row, and one row after
                    for (int k = (i - 1); k <= (i + 1); k++)
                    {
                        // Average one column before, current column and one column after
                        for (int l = (j - 1); l <= (j + 1); l++)
                        {
                            // printf("i = %i\n", i);
                            // printf("j = %i\n", j);
                            // printf("k = %i\n", k);
                            // printf("l = %i\n", l);
                            // originalR[i][j] = image[k][l].rgbtRed;
                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = (blurAvgR / 9);
                    blurAvgG = (blurAvgG / 9);
                    blurAvgB = (blurAvgB / 9);
                    image[i][j].rgbtRed = (int) blurAvgR;
                    image[i][j].rgbtGreen = (int) blurAvgG;
                    image[i][j].rgbtBlue = (int) blurAvgB;
                }
            }
        }
        // printf("\n");
    }
    return;
}
