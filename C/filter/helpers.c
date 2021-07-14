#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            // gray color
            int GrayAvg = round((red + green + blue) / 3);

            // make sure the red, green, and blue values are all the same value
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = GrayAvg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            // swap the pixels
            // create temp array to store the pixels
            // width - (j + 1) is opposite position
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create the same pixels array of the original image
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // set the values
            float SumRed = 0;
            float SumGreen = 0;
            float SumBlue = 0;
            int count = 0;

            // check if the pixel out of the edge or corner, pass this pixel
            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++)
                {
                    if (i + a < 0 || i + a >= height)
                    {
                        continue;
                    }

                    if (j + b < 0 || j + b >= width)
                    {
                        continue;
                    }

                    // if the pixel exist, plus the RGB values
                    SumRed += tmp[i + a][j + b].rgbtRed;
                    SumGreen += tmp[i + a][j + b].rgbtGreen;
                    SumBlue += tmp[i + a][j + b].rgbtBlue;
                    count++;
                }
            }

            // averaging the color values of neighboring pixels
            image[i][j].rgbtRed = round(SumRed / count);
            image[i][j].rgbtGreen = round(SumGreen / count);
            image[i][j].rgbtBlue = round(SumBlue / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create the same pixels array of the original image
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    // create the sobel operator array
    int Gx [3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy [3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // set the values
            int Gx_red = 0;
            int Gx_green = 0;
            int Gx_blue = 0;
            int Gy_red = 0;
            int Gy_green = 0;
            int Gy_blue = 0;

            // check if the pixel out of the edge or corner, pass this pixel
            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++)
                {
                    if (i + a < 0 || i + a >= height)
                    {
                        continue;
                    }

                    if (j + b < 0 || j + b >= width)
                    {
                        continue;
                    }

                    Gx_red += tmp[i + a][j + b].rgbtRed * Gx[a + 1][b + 1];
                    Gx_green += tmp[i + a][j + b].rgbtGreen * Gx[a + 1][b + 1];
                    Gx_blue += tmp[i + a][j + b].rgbtBlue * Gx[a + 1][b + 1];
                    Gy_red += tmp[i + a][j + b].rgbtRed * Gy[a + 1][b + 1];
                    Gy_green += tmp[i + a][j + b].rgbtGreen * Gy[a + 1][b + 1];
                    Gy_blue += tmp[i + a][j + b].rgbtBlue * Gy[a + 1][b + 1];
                }
            }

            // combine Gx and Gy into a single value since each channel can only take on one value
            int sqrt_red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int sqrt_green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int sqrt_blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));

            // set the cap number 255
            if (sqrt_red > 255)
            {
                sqrt_red = 255;
            }
            if (sqrt_green > 255)
            {
                sqrt_green = 255;
            }
            if (sqrt_blue > 255)
            {
                sqrt_blue = 255;
            }

            image[i][j].rgbtRed = sqrt_red;
            image[i][j].rgbtGreen = sqrt_green;
            image[i][j].rgbtBlue = sqrt_blue;
        }
    }
    return;
}
