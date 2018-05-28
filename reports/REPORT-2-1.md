# 課題1レポート

この課題のソースコードは[https://github.com/kawasin73/todai-bmp](https://github.com/kawasin73/todai-bmp)にアップロードしています。

以下の2つのソースコードは、[物理のかぎしっぽ](http://hooktail.org/computer/index.php?Bitmap%A5%D5%A5%A1%A5%A4%A5%EB%A4%F2%C6%FE%BD%D0%CE%CF%A4%B7%A4%C6%A4%DF%A4%EB)から引用しました。

- `bitmap.h`
- `bitmap.c`

`bitmap.h`と`bitmap.c` は、以下の機能を提供しています。

- Bitmap画像ファイルの読み込み(`Read_Bmp`)
- Bitmap画像のファイルへの書き込み(`Write_Bmp`)
- Bitmap画像を表す`Image`構造体の定義

このソースコードはダウンロードしたものをそのまま利用しているため解説は省略します。

## ソースコード

勾配画像の書き出しは以下の`sobel.c` と `sobel-main.c`のソースコードで実現します。

### sobel.c

```c:sobel.c
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

```

縦方向のソーベルフィルタは、`filterV` で表現されている、3 * 3 のフィルタです。
横方向のソーベルフィルタは、`filterH` で表現されている、3 * 3 のフィルタです。

それぞれのピクセルについて、縦方向と横方向の R, G, B の要素のソーベルフィルタによる畳み込みを行います。
それらの R, G, B それぞれの縦方向の値と横方向の値の勾配の値を計算し、足し合わせて `tmpMap` に格納します。
ここでは、畳み込みにおける `1/8` と、R, G ,B の3つの勾配の平均のための `1/3` は計算しません。それは、この後で 0 ~ 255 に正規化するため、この段階で平均化する必要がないからです。

`tmpMap` は外部でアロケーションされたものが提供されます。`tmpMap`は、画像の縦 * 横の要素数以上の長さである必要があります。
内部でアロケーションしてもよかったのですが、もし、`tmpMap`を使い回すことを考えて、外部から注入できるようにしました。

それぞれのピクセルで計算された勾配の値は、`img->data`には代入せず、`tmpMap`に代入します。
理由は2つあります。

1つ目は、0 ~ 255 へのスケーリングによる正規化をするためです。スケーリングによる正規化のためには、全ての勾配の値の最大値と最小値がわかっている必要があります。しかし、一つ一つのピクセルの計算の段階では、最大値、最小値はわからないため、スケーリングさせることができません。RGBは、`unsigned char`であり、0 ~ 255 の整数の値域しかなく、正規化する前のデータを保存しようとするとオーバーフローしてしまいます。

2つ目は、他のピクセルの勾配の計算に影響を与えてしまうからです。あるピクセルの勾配の値で画像のピクセル値を上書きした場合、その後に計算される上下左右のピクセルの勾配の計算に影響を与えてしまいます。ソーベルフィルタの計算は畳み込み計算であるため、全てのピクセルの勾配の計算が終わるまでピクセルの値は変更することができません。

全てのピクセルの勾配を計算した後に、`tmpMap`の値を正規化して`img->data`に上書きしています。

ピクセルのRGBの値の取得には、`Rgb getRgb(Image *img, int i, int j)`を使います。画像の縁のピクセルの畳み込み計算に使う上下左右のピクセルには、画像の範囲外の値が使われることがあります。今回は、範囲外のピクセルは、`{r: 0, g: 0, b: 0}` として計算し、画像の縁であっても他のピクセルと同様にエラーなく計算できるようにするようにしました。

### sobel-main.c

```c:sobel-main.c
#include "bitmap.h"
#include "sobel.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: program <inputfile> <outputfile>\n");
        exit(1);
    }

    Image *colorimg;
    double *tmpMap;

    if ((colorimg = Read_Bmp(argv[1])) == NULL)
    {
        exit(1);
    }

    if ((tmpMap = (double *)malloc(sizeof(double) * colorimg->height * colorimg->width)) == NULL)
    {
        fprintf(stderr, "Allocation error\n");
        exit(1);
    }

    Sobel(colorimg, tmpMap);

    if (Write_Bmp(argv[2], colorimg))
    {
        exit(1);
    }

    free(tmpMap);
    Free_Image(colorimg);

    return 0;
}

```

`Sobel(colorimg, tmpMap);` を実行して、画像を生成します。`tmpMap` は、動的にアロケーションし、終了前に解放します。

### 結果

元画像はこれです。

![元画像](./sample.bmp)

変換された勾配画像はこれです。

![勾配画像](./sobel.bmp)
