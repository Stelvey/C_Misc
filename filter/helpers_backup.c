#include "helpers.h"


//Custom includes & prototypes
#include <math.h>
RGBTRIPLE grid(int height, int width, int px_i, int px_j, RGBTRIPLE old[height][width]);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i;
    int j;
    int avg;

    for (i = 0; i != height; i++)
    {
        for (j = 0; j != width; j++)
        {
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i;
    int j;
    int reverse = width;
    RGBTRIPLE buffer;

    for (i = 0; i != height; i++)
    {
        j = 0;
        while (j < reverse)
        {
            reverse = width - j - 1;

            buffer = image[i][j];
            image[i][j] = image[i][reverse];
            image[i][reverse] = buffer;

            j++;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Variables
    int i;
    int j;
    RGBTRIPLE old[height][width];

    for (i = 0; i != height; i++)
    {
        for (j = 0; j != width; j++)
        {
            old[i][j] = image[i][j];
        }
    }

    // Filter
    for (i = 0; i != height; i++)
    {
        for (j = 0; j != width; j++)
        {
            image[i][j] = grid(height, width, i, j, old);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}


RGBTRIPLE grid(int height, int width, int px_i, int px_j, RGBTRIPLE old[height][width])
{
    // Variables
    int i;
    int j;

    float blue = 0;
    float green = 0;
    float red = 0;

    int total = 0;

    // Actual grid checking
    for (i = px_i - 1; i != px_i + 2; i++)
    {
        if (i >= 0 && i <= height - 1)
        {
            for (j = px_j - 1; j != px_j + 2; j++)
            {
                if (j >= 0 && j <= width - 1)
                {
                    blue += old[i][j].rgbtBlue;
                    green += old[i][j].rgbtGreen;
                    red += old[i][j].rgbtRed;

                    total++;
                }
            }
        }
    }

    blue = round(blue / total);
    green = round(green / total);
    red = round(red / total);

    RGBTRIPLE result = {blue, green, red};

    return result;
}