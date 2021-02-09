#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //run through each pixel and change the rgbt values to the average of the current values of each pixel.
    for (int i = 0; i <height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;
            float avg = ((blue + green + red)/3);
            float grey = round(avg);
            image[i][j].rgbtBlue = grey;
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtRed = grey;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;

            float sepiaRed = ((blue * .189) + (green * .769) + (red * .393));
            float finalSR = round(sepiaRed);
            if (finalSR < 0)
            {
                finalSR = 0;
            }
            if (finalSR > 255)
            {
                finalSR = 255;
            }

            float sepiaGreen = ((blue * .168) + (green * .686) + (red * .349));
            float finalSG = round(sepiaGreen);
            if (finalSG < 0)
            {
                finalSG = 0;
            }
            if (finalSG > 255)
            {
                finalSG = 255;
            }
            float sepiaBlue = ((blue * .131) + (green * .534) + (red * .272));
            float finalSB = round(sepiaBlue);
            if (finalSB < 0)
            {
                finalSB = 0;
            }
            if (finalSB > 255)
            {
                finalSB = 255;
            }



            image[i][j].rgbtBlue = finalSB;
            image[i][j].rgbtGreen = finalSG;
            image[i][j].rgbtRed = finalSR;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Need to swap the pixels or each row with it's horizontal oppoiste- so in a row of 10, 0 swaps with 10, 1 swaps with 9 etc. but you only want it to go half the array -
    //as otherwise it'll go back to the start
    //i = length.width - i?
    //until int length.width/2? how to swap an array struct? for loop <width/2
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
           int tempBlue = image[i][j].rgbtBlue;
           int tempGreen = image[i][j].rgbtGreen;
           int tempRed = image[i][j].rgbtRed;
          
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
           
           image[i][width  - 1 - j].rgbtBlue = tempBlue;
           image[i][width  - 1 - j].rgbtGreen = tempGreen;   
           image[i][width  - 1 - j].rgbtRed = tempRed;


        }
    }
    return;
}

// Blur image
/*void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // need to run a loop through each pixel in the width, averaging the colour of each pixel, and each surrounding pixel. 
            //so the corners are [i][j] i, j+1. i+1, j i+1, j + 1. 
            //normal pixels are the average colours of all the 9 pixels around it (including the original)
            // but you need to change the copy of it every time- as otherwise it'll get the wrong averages
          imageCopy[i][j] = image [i][j];
            
        }
    }
     for (int i = 0; i < height; i++)
    {
        int red = 0;
        int green = 0;
        int blue = 0;
        int counter = 0;
        for (int j = 0; j < width; j++)
        {
            // break it down over each surrounding pixel
            // top left
            if (i - 1 >= 0 && j - 1 >= 0 )
            {
                red += imageCopy[i - 1][j - 1].rgbtRed;
                blue += imageCopy[i - 1][j - 1].rgbtBlue;
                green += imageCopy[i - 1][j - 1].rgbtGreen;
                counter ++;
            }
            //top middle
            if (i - 1 >= 0 && j >= 0)
            {
                red += imageCopy[i - 1][j].rgbtRed;
                blue += imageCopy[i - 1][j].rgbtBlue;
                green += imageCopy[i - 1][j].rgbtGreen;
                counter ++;
            }
            //top right
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >=0 && j + 1 < width))
            {
                red += imageCopy[i - 1][j + 1].rgbtRed;
                blue += imageCopy[i - 1][j + 1].rgbtBlue;
                green += imageCopy[i - 1][j + 1].rgbtGreen;
                counter ++;
            }
            // middle left
            if (i >= 0 && j - 1 >= 0)
            {
                red += imageCopy[i][j - 1].rgbtRed;
                blue += imageCopy[i][j - 1].rgbtBlue;
                green += imageCopy[i][j - 1].rgbtGreen;
                counter ++;
            }
            //middle
            if (i >= 0 && j >= 0)
                red += imageCopy[i][j].rgbtRed;
                blue += imageCopy[i][j].rgbtBlue;
                green += imageCopy[i][j].rgbtGreen;
                counter ++;
            
            //middle right
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                red += imageCopy[i][j + 1].rgbtRed;
                blue += imageCopy[i][j + 1].rgbtBlue;
                green += imageCopy[i][j + 1].rgbtGreen;
                counter ++;
            }
            //bottom right
            if ((i + 1 >= 0 && j -1 >= 0) && (i + 1 < height && j -1 >= 0))
            {
                red += imageCopy[i + 1][j - 1].rgbtRed;
                blue += imageCopy[i + 1][j - 1].rgbtBlue;
                green += imageCopy[i + 1][j - 1].rgbtGreen;
                counter ++;
            }
            //bottom middle
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                red += imageCopy[i - 1][j].rgbtRed;
                blue += imageCopy[i - 1][j].rgbtBlue;
                green += imageCopy[i - 1][j].rgbtGreen;
                counter ++;
            }
            //bottom right
            if ((i + 1 >=0 && j + 1 >= 0) && (i + 1 < height&& j + 1 < width))
            {
                red += imageCopy[i + 1][j + 1].rgbtRed;
                blue += imageCopy[i + 1][j + 1].rgbtBlue;
                green += imageCopy[i + 1][j + 1].rgbtGreen;
                counter ++;
            }
            image[i][j].rgbtRed = round (red / counter * 1.0);
            image[i][j].rgbtBlue = round (blue/ counter * 1.0);
            image[i][j].rgbtGreen = round (green/counter * 1.0);
        }
    }
    return;
}*/
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE ogImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ogImage[i][j] = image[i][j];
        }
    }

    for (int i = 0, red, green, blue, counter; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = green = blue = counter = 0;

            if (i >= 0 && j >= 0)
            {
                red += ogImage[i][j].rgbtRed;
                green += ogImage[i][j].rgbtGreen;
                blue += ogImage[i][j].rgbtBlue;
                counter++;
            }
            if (i >= 0 && j - 1 >= 0)
            {
                red += ogImage[i][j-1].rgbtRed;
                green += ogImage[i][j-1].rgbtGreen;
                blue += ogImage[i][j-1].rgbtBlue;
                counter++;
            }
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                red += ogImage[i][j+1].rgbtRed;
                green += ogImage[i][j+1].rgbtGreen;
                blue += ogImage[i][j+1].rgbtBlue;
                counter++;
            }
            if (i - 1 >= 0 && j >= 0)
            {
                red += ogImage[i-1][j].rgbtRed;
                green += ogImage[i-1][j].rgbtGreen;
                blue += ogImage[i-1][j].rgbtBlue;
                counter++;
            }
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                red += ogImage[i-1][j-1].rgbtRed;
                green += ogImage[i-1][j-1].rgbtGreen;
                blue += ogImage[i-1][j-1].rgbtBlue;
                counter++;
            }
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                red += ogImage[i-1][j+1].rgbtRed;
                green += ogImage[i-1][j+1].rgbtGreen;
                blue += ogImage[i-1][j+1].rgbtBlue;
                counter++;
            }
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                red += ogImage[i+1][j].rgbtRed;
                green += ogImage[i+1][j].rgbtGreen;
                blue += ogImage[i+1][j].rgbtBlue;
                counter++;
            }
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                red += ogImage[i+1][j-1].rgbtRed;
                green += ogImage[i+1][j-1].rgbtGreen;
                blue += ogImage[i+1][j-1].rgbtBlue;
                counter++;
            }
            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                red += ogImage[i+1][j+1].rgbtRed;
                green += ogImage[i+1][j+1].rgbtGreen;
                blue += ogImage[i+1][j+1].rgbtBlue;
                counter++;
            }

            image[i][j].rgbtRed = round(red / (counter * 1.0));
            image[i][j].rgbtGreen = round(green / (counter * 1.0));
            image[i][j].rgbtBlue = round(blue / (counter * 1.0));
        }
    }

    return;
}
