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
    // Initialize variables to hold original color values
    float originalR[height][width];
    float originalG[height][width];
    float originalB[height][width];

    // Calculate blur average value
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blurAvgR = 0;
            float blurAvgG = 0;
            float blurAvgB = 0;
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
                    blurAvgR = round(blurAvgR / 4);
                    blurAvgG = round(blurAvgG / 4);
                    blurAvgB = round(blurAvgB / 4);
                    image[i][j].rgbtRed = (int)blurAvgR;
                    image[i][j].rgbtGreen = (int)blurAvgG;
                    image[i][j].rgbtBlue = (int)blurAvgB;
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
                            if (k == (i - 1))
                            {
                                blurAvgR = originalR[k][j] + originalR[k][j + 1];
                                blurAvgG = originalG[k][j] + originalG[k][j + 1];
                                blurAvgB = originalB[k][j] + originalB[k][j + 1];
                                k++;
                            }
                            originalR[k][l] = image[k][l].rgbtRed;
                            originalG[k][l] = image[k][l].rgbtGreen;
                            originalB[k][l] = image[k][l].rgbtBlue;

                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = round(blurAvgR / 4);
                    blurAvgG = round(blurAvgG / 4);
                    blurAvgB = round(blurAvgB / 4);
                    image[i][j].rgbtRed = (int)blurAvgR;
                    image[i][j].rgbtGreen = (int)blurAvgG;
                    image[i][j].rgbtBlue = (int)blurAvgB;
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
                            if (k == (i - 1))
                            {
                                blurAvgR = originalR[k][j] + originalR[k][j + 1];
                                blurAvgG = originalG[k][j] + originalG[k][j + 1];
                                blurAvgB = originalB[k][j] + originalB[k][j + 1];
                                k++;
                            }
                            originalR[k][l] = image[k][l].rgbtRed;
                            originalG[k][l] = image[k][l].rgbtGreen;
                            originalB[k][l] = image[k][l].rgbtBlue;

                            blurAvgR += image[k][l].rgbtRed;
                            blurAvgG += image[k][l].rgbtGreen;
                            blurAvgB += image[k][l].rgbtBlue;
                        }
                    }
                    blurAvgR = round(blurAvgR / 6);
                    blurAvgG = round(blurAvgG / 6);
                    blurAvgB = round(blurAvgB / 6);
                    image[i][j].rgbtRed = (int)blurAvgR;
                    image[i][j].rgbtGreen = (int)blurAvgG;
                    image[i][j].rgbtBlue = (int)blurAvgB;
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
                    blurAvgR = round(blurAvgR / 4);
                    blurAvgG = round(blurAvgG / 4);
                    blurAvgB = round(blurAvgB / 4);
                    image[i][j].rgbtRed = (int)blurAvgR;
                    image[i][j].rgbtGreen = (int)blurAvgG;
                    image[i][j].rgbtBlue = (int)blurAvgB;
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
                            if (k == (i - 1))
                            {
                                blurAvgR = originalR[k][j - 1] + originalR[k][j];
                                blurAvgG = originalG[k][j - 1] + originalG[k][j];
                                blurAvgB = originalB[k][j - 1] + originalB[k][j];
                                k++;
                            }
                            if (k == i && l == (j - 1))
                            {
                                blurAvgR += originalR[k][l];
                                blurAvgG += originalG[k][l];
                                blurAvgB += originalB[k][l];
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
                    blurAvgR = round(blurAvgR / 4);
                    blurAvgG = round(blurAvgG / 4);
                    blurAvgB = round(blurAvgB / 4);
                    image[i][j].rgbtRed = (int)blurAvgR;
                    image[i][j].rgbtGreen = (int)blurAvgG;
                    image[i][j].rgbtBlue = (int)blurAvgB;
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
                            if (k == (i - 1))
                            {
                                blurAvgR = originalR[k][j - 1] + originalR[k][j];
                                blurAvgG = originalG[k][j - 1] + originalG[k][j];
                                blurAvgB = originalB[k][j - 1] + originalB[k][j];
                                k++;
                            }
                            if (k == i && l == (j - 1))
                            {
                                blurAvgR += originalR[k][l];
                                blurAvgG += originalG[k][l];
                                blurAvgB += originalB[k][l];
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
                    blurAvgR = round(blurAvgR / 6);
                    blurAvgG = round(blurAvgG / 6);
                    blurAvgB = round(blurAvgB / 6);
                    image[i][j].rgbtRed = (int)blurAvgR;
                    image[i][j].rgbtGreen = (int)blurAvgG;
                    image[i][j].rgbtBlue = (int)blurAvgB;
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
                        // Average one column before, current column, and one column after
                        for (int l = (j - 1); l <= (j + 1); l++)
                        {
                            if (k == i && l == (j - 1))
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
                    blurAvgR = round(blurAvgR / 6);
                    blurAvgG = round(blurAvgG / 6);
                    blurAvgB = round(blurAvgB / 6);
                    image[i][j].rgbtRed = (int)blurAvgR;
                    image[i][j].rgbtGreen = (int)blurAvgG;
                    image[i][j].rgbtBlue = (int)blurAvgB;
                }
                // Row Edge Case 2: MIDDLE COLUMNS, LAST ROW
                else if (i == (height - 1))
                {
                    // Average one row before and current row
                    for (int k = (i - 1); k <= i; k++)
                    {
                        // Average one column before, current column, and one column after
                        for (int l = (j - 1); l <= (j + 1); l++)
                        {
                            if (k == (i - 1))
                            {
                                blurAvgR = originalR[k][j - 1] + originalR[k][j] + originalR[k][j + 1];
                                blurAvgG = originalG[k][j - 1] + originalG[k][j] + originalG[k][j + 1];
                                blurAvgB = originalB[k][j - 1] + originalB[k][j] + originalB[k][j + 1];
                                k++;
                            }
                            if (k == i && l == (j - 1))
                            {
                                blurAvgR += originalR[k][l];
                                blurAvgG += originalG[k][l];
                                blurAvgB += originalB[k][l];
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
                    blurAvgR = round(blurAvgR / 6);
                    blurAvgG = round(blurAvgG / 6);
                    blurAvgB = round(blurAvgB / 6);
                    image[i][j].rgbtRed = (int)blurAvgR;
                    image[i][j].rgbtGreen = (int)blurAvgG;
                    image[i][j].rgbtBlue = (int)blurAvgB;
                }
                // --- All Other Row Cases ---
                // MIDDLE COLUMNS, MIDDLE ROWS
                else
                {
                    // Average one row before, current row, and one row after
                    for (int k = (i - 1); k <= (i + 1); k++)
                    {
                        // Average one column before, current column, and one column after
                        for (int l = (j - 1); l <= (j + 1); l++)
                        {
                            if (k == (i - 1))
                            {
                                blurAvgR = originalR[k][j - 1] + originalR[k][j] + originalR[k][j + 1];
                                blurAvgG = originalG[k][j - 1] + originalG[k][j] + originalG[k][j + 1];
                                blurAvgB = originalB[k][j - 1] + originalB[k][j] + originalB[k][j + 1];
                                k++;
                            }
                            if (k == i && l == (j - 1))
                            {
                                blurAvgR += originalR[k][l];
                                blurAvgG += originalG[k][l];
                                blurAvgB += originalB[k][l];
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
                    blurAvgR = round(blurAvgR / 9);
                    blurAvgG = round(blurAvgG / 9);
                    blurAvgB = round(blurAvgB / 9);
                    image[i][j].rgbtRed = (int)blurAvgR;
                    image[i][j].rgbtGreen = (int)blurAvgG;
                    image[i][j].rgbtBlue = (int)blurAvgB;
                }
            }
        }
    }
    return;
}
