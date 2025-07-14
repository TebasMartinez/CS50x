#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each column in row
        for (int j = 0; j < width; j++)
        {
            float average =
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            BYTE new_pixel = round(average);
            image[i][j].rgbtRed = new_pixel;
            image[i][j].rgbtGreen = new_pixel;
            image[i][j].rgbtBlue = new_pixel;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each column in row
        for (int j = 0; j < width; j++)
        {
            double averagered = (0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) +
                                (0.189 * image[i][j].rgbtBlue);
            int sepiaRed = round(averagered);
            double averagegreen = (0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) +
                                  (0.168 * image[i][j].rgbtBlue);
            int sepiaGreen = round(averagegreen);
            double averageblue = (0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) +
                                 (0.131 * image[i][j].rgbtBlue);
            int sepiaBlue = round(averageblue);
            if (sepiaRed < 255)
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }
            if (sepiaGreen < 255)
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }
            if (sepiaBlue < 255)
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each column in row
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE firstpixel = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = firstpixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each column, so each pixel in the row
        for (int j = 0; j < width; j++)
        {
            float redtotal = 0;
            float greentotal = 0;
            float bluetotal = 0;
            float averagecount = 0;

            // For each surrounding pixels
            for (int nexti = -1; nexti <= 1; nexti++)
            {
                for (int nextj = -1; nextj <= 1; nextj++)
                {
                    int newi = i + nexti;
                    int newj = j + nextj;

                    // Skip if pixel doesn't exist
                    if (newi < 0 || newi >= height || newj < 0 || newj >= width)
                    {
                        continue;
                    }

                    // If pixel exists, count it in the totals
                    redtotal += copy[newi][newj].rgbtRed;
                    greentotal += copy[newi][newj].rgbtGreen;
                    bluetotal += copy[newi][newj].rgbtBlue;
                    averagecount++;
                }
            }

            image[i][j].rgbtRed = round(redtotal / averagecount);
            image[i][j].rgbtGreen = round(greentotal / averagecount);
            image[i][j].rgbtBlue = round(bluetotal / averagecount);
        }
    }
    return;
}
