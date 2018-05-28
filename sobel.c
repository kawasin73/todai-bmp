#include "bitmap.h"
#include <math.h>
#include <stdio.h>

Rgb getRgb(Image *img, int i, int j);

void Sobel(Image *img, double *tmpMap)
{
    char filterH[9] = {-1, 0, 1,
                       -2, 0, 2,
                       -1, 0, 1};
    char filterV[9] = {1, 2, 1,
                       0, 0, 0,
                       -1, -2, -1};
    int i, j, k, l, m;
    Rgb tmpRgb;
    unsigned int index;
    unsigned char gray;

    double sumHR, sumHG, sumHB, sumVR, sumVG, sumVB, min, max = 0;

    for (i = 0; i < img->height; i++)
    {
        for (j = 0; j < img->width; j++)
        {
            sumHR = sumHG = sumHB = sumVR = sumVG = sumVB = 0;
            for (k = 0; k < 3; k++)
            {
                for (l = 0; l < 3; l++)
                {
                    m = k * 3 + l;
                    tmpRgb = getRgb(img, i + k - 1, j + l - 1);
                    sumHR += filterH[m] * tmpRgb.r;
                    sumHG += filterH[m] * tmpRgb.g;
                    sumHB += filterH[m] * tmpRgb.b;
                    sumVR += filterV[m] * tmpRgb.r;
                    sumVG += filterV[m] * tmpRgb.g;
                    sumVB += filterV[m] * tmpRgb.b;
                }
            }
            index = img->width * i + j;
            tmpMap[index] = (sqrt(pow(sumHR, 2) + pow(sumVR, 2)) + sqrt(pow(sumHG, 2) + pow(sumVG, 2)) + sqrt(pow(sumHB, 2) + pow(sumVB, 2)));
            if (tmpMap[index] > max)
            {
                max = tmpMap[index];
            }
            if (tmpMap[index] < min)
            {
                min = tmpMap[index];
            }
        }
    }

    for (i = 0; i < img->height; i++)
    {
        for (j = 0; j < img->width; j++)
        {
            index = img->width * i + j;
            img->data[index].r = img->data[index].g = img->data[index].b = (tmpMap[index] - min) * 255 / (max - min);
        }
    }
}

Rgb getRgb(Image *img, int i, int j)
{
    Rgb result = {0, 0, 0};
    if (i < 0 || i >= img->height || j < 0 || j >= img->width)
    {
        return result;
    }
    return img->data[i * img->width + j];
}
