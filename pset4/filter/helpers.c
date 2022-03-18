#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])//чб
{
    float gray;

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            // усредняет интенсивность цвета, а затем применяет одно и то же значение ко всем цветам, чтобы получить серый
            gray = round((image[j][i].rgbtGreen + image[j][i].rgbtBlue + image[j][i].rgbtRed) / 3.0);

            image[j][i].rgbtBlue = gray;
            image[j][i].rgbtGreen = gray;
            image[j][i].rgbtRed = gray;
        }
    }
    return;
}




// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])//старина
{
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            int redsepia = round(0.393 * image[j][i].rgbtRed + 0.769 * image[j][i].rgbtGreen + 0.189 * image[j][i].rgbtBlue);
            int greensepia = round(0.349 * image[j][i].rgbtRed + 0.686 * image[j][i].rgbtGreen + 0.168 * image[j][i].rgbtBlue);
            int bluesepia = round(0.272 * image[j][i].rgbtRed + 0.534 * image[j][i].rgbtGreen + 0.131 * image[j][i].rgbtBlue);
            if(redsepia > 255)
            {
                redsepia = 255;
            }
            if(greensepia > 255)
            {
                greensepia = 255;
            }
            if(bluesepia > 255)
            {
                bluesepia = 255;
            }
            image[j][i].rgbtGreen = greensepia;
            image[j][i].rgbtRed = redsepia;
            image[j][i].rgbtBlue = bluesepia;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])//перевертыш
{
    int blue = 0;
    int green = 0;
    int red = 0;

    for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width / 2; i++)
        {
            blue = image[j][i].rgbtBlue;
            green = image[j][i].rgbtGreen;
            red = image[j][i].rgbtRed;
            image[j][i].rgbtBlue = image[j][width - i - 1].rgbtBlue;
            image[j][i].rgbtGreen = image[j][width - i - 1].rgbtGreen;
            image[j][i].rgbtRed = image[j][width - i - 1].rgbtRed;
            image[j][width - i - 1].rgbtBlue = blue;
            image[j][width - i - 1].rgbtGreen = green;
            image[j][width - i - 1].rgbtRed = red;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])//замыленное
{
    RGBTRIPLE arr[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
    {
        arr[i][j] = image[i][j];
    }
}
float red, blue, green;
float counter = 0;

for(int i = 0; i < height; i++)
{
    for(int j = 0; j < width; j++)
    {
        for(int k = -1; k < 2; k++)
        {
            for(int l = -1; l < 2; l++)
            {
                if(i + k >= 0 && j + l >= 0 && i + k <= height - 1 && j + l <= width - 1)
                {
                    red += arr[i + k][j + l].rgbtRed;
                    blue += arr[i + k][j + l].rgbtBlue;
                    green += arr[i + k][j + l].rgbtGreen;
                    counter++;
                }

            }
        }
        red = red / counter;
        green = green / counter;
        blue = blue / counter;

        image[i][j].rgbtRed = round(red);
        image[i][j].rgbtGreen = round(green);
        image[i][j].rgbtBlue = round(blue);
        counter = 0;
        red = 0;
        green = 0;
        blue = 0;
    }
}
return;


}
