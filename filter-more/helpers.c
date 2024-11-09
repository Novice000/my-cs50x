#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0; i < height; i++)
    {
        for(int j=0; j<width;j++)
        {
            int average_pixel= round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0);
            image[i][j].rgbtRed= average_pixel;
            image[i][j].rgbtGreen= average_pixel;
            image[i][j].rgbtBlue= average_pixel;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int r_width= ceil(width/2);
    for(int i=0; i < height; i++)
    {
        for(int j=0; j<r_width;j++)
        {
            RGBTRIPLE temp= image[i][j];
            image[i][j] = image[i][width -1 -j];
            image[i][width -1 -j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for(int i =0; i< height; i++)
    {
        int lower_row = (i-1<0)?i:i-1;
        int upper_row = (i+1==height)?i:i+1;
        for(int j = 0; j < width; j++)
        {
            int lower_col= (j-1<0)?j:j-1;
            int upper_col= (j+1==width)?j:j+1;
            int red= 0;
            int green= 0;
            int blue= 0;
            float counter= 0;

            for(int a= lower_row; a <= upper_row; a++)
            {
                for(int b= lower_col; b <= upper_col; b++)
                {
                    red += image[a][b].rgbtRed;
                    green += image[a][b].rgbtGreen;
                    blue += image[a][b].rgbtBlue;
                    counter++;
                }
            }
            temp[i][j].rgbtRed = round(red/counter);
            temp[i][j].rgbtGreen= round(green/counter);
            temp[i][j].rgbtBlue= round(blue/counter);
        }
    }
    for(int h=0; h<height;h++){
        for(int w=0; w< width; w++)
        {
            image[h][w]= temp[h][w];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int Gx[3][3]= {{-1,0,1},{-2,0,2},{-1,0,1}};
    int Gy[3][3]= {{-1,-2,-1},{0,0,0},{1,2,1}};
    int red, blue, green, red_y, blue_y, green_y;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            red = blue = green = red_y = blue_y = green_y= 0;

            for(int h=-1; h <= 1; h++)
            {
                for(int w = -1; w <= 1; w++)
                {
                    if(j + w<0 || i + h < 0 || j + w > width -1 || i + h > height - 1)
                    {
                        continue;
                    }

                    red+= image[i+h][j+w].rgbtRed * Gx[h+1][w+1];
                    blue += image[i+h][j+w].rgbtBlue * Gx[h+1][w+1];
                    green+= image[i+h][j+w].rgbtGreen * Gx[h+1][w+1];


                    red_y+= image[i+h][j+w].rgbtRed * Gy[h+1][w+1];
                    blue_y += image[i+h][j+w].rgbtBlue * Gy[h+1][w+1];
                    green_y += image[i+h][j+w].rgbtGreen * Gy[h+1][w+1];

                }
            }

            int GxR = round(sqrt((red*red)+(red_y*red_y)));
            int GxG = round(sqrt((green*green)+(green_y*green_y)));
            int GxB = round(sqrt((blue*blue)+(blue_y*blue_y)));

            temp[i][j].rgbtRed= (GxR>255)?255:GxR;
            temp[i][j].rgbtBlue= (GxB>255)?255:GxB;
            temp[i][j].rgbtGreen= (GxG>255)?255:GxG;
        }
    }
            for(int k=0; k< height;k++){
                 for(int l=0; l< width; l++)
                {
                image[k][l] = temp[k][l];
                }
             }
    }

