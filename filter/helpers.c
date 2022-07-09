#include "helpers.h"


// Custom includes & prototypes
#include <math.h>
RGBTRIPLE px_blur(int height, int width, int px_i, int px_j, RGBTRIPLE old[height][width]);
RGBTRIPLE px_edges(int height, int width, int px_i, int px_j, RGBTRIPLE old[height][width]);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Variables
    int i;
    int j;
    int avg;

    // Filter
    for (i = 0; i != height; i++)
    {
        for (j = 0; j != width; j++)
        {
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
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
    // Variables
    int i;
    int j;
    int reverse = width;
    RGBTRIPLE buffer;

    // Filter
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
            image[i][j] = px_blur(height, width, i, j, old);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            image[i][j] = px_edges(height, width, i, j, old);
        }
    }
    return;
}


// Custom: Grid loop to calculate and return a BLUR pixel
RGBTRIPLE px_blur(int height, int width, int px_i, int px_j, RGBTRIPLE old[height][width])
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

    // Average numbers and send a result
    blue = round(blue / total);
    green = round(green / total);
    red = round(red / total);

    RGBTRIPLE result = {blue, green, red};

    return result;
}

// Custom: Grid loop to calculate and return EDGES pixel
RGBTRIPLE px_edges(int height, int width, int px_i, int px_j, RGBTRIPLE old[height][width])
{
    // Variables
    int i;
    int j;

    float gx_blue = 0;
    float gx_green = 0;
    float gx_red = 0;

    float gy_blue = 0;
    float gy_green = 0;
    float gy_red = 0;

    int gi;
    int gj;

    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] =
    {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    // Actual grid checking
    for (i = px_i - 1; i != px_i + 2; i++)
    {
        if (i >= 0 && i <= height - 1)
        {
            for (j = px_j - 1; j != px_j + 2; j++)
            {
                if (j >= 0 && j <= width - 1)
                {
                    gi = i - px_i + 1;
                    gj = j - px_j + 1;

                    gx_blue += old[i][j].rgbtBlue * gx[gi][gj];
                    gx_green += old[i][j].rgbtGreen * gx[gi][gj];
                    gx_red += old[i][j].rgbtRed * gx[gi][gj];

                    gy_blue += old[i][j].rgbtBlue * gy[gi][gj];
                    gy_green += old[i][j].rgbtGreen * gy[gi][gj];
                    gy_red += old[i][j].rgbtRed * gy[gi][gj];
                }
            }
        }
    }

    // Square root of gx^2 + gy^2 for each color (using gx_color instead of initializing 3 new vars)
    gx_blue = round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));
    gx_green = round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
    gx_red = round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));

    // Capping at 255 (you can use an array of bgr and then have a loop there, though it might be an overengineered solution)
    if (gx_blue > 255)
    {
        gx_blue = 255;
    }
    if (gx_green > 255)
    {
        gx_green = 255;
    }
    if (gx_red > 255)
    {
        gx_red = 255;
    }

    // Returning the result!
    RGBTRIPLE result = {gx_blue, gx_green, gx_red};
    return result;
}