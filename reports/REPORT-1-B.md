# 課題Bレポート

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

サーモグラフィーの書き出しは以下の`thermo.c`のソースコードで実現します。

```c:thermo.c
#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>

void ThermoScale(Image *img);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: program <inputfile> <outputfile>\n");
        exit(1);
    }

    Image *colorimg;

    if ((colorimg = Read_Bmp(argv[1])) == NULL)
    {
        exit(1);
    }

    ThermoScale(colorimg);

    if (Write_Bmp(argv[2], colorimg))
    {
        exit(1);
    }

    Free_Image(colorimg);

    return 0;
}

unsigned char thermoR(unsigned char v)
{
    if (v < 128)
    {
        return 0;
    }
    else if (v < 192)
    {
        return (v - 128) * 4;
    }
    else
    {
        return 255;
    }
}

unsigned char thermoG(unsigned char v)
{
    if (v < 64)
    {
        return (v - 64) * 4;
    }
    else if (v < 192)
    {
        return 255;
    }
    else
    {
        return (255 - v) * 4;
    }
}

unsigned char thermoB(unsigned char v)
{
    if (v <= 64)
    {
        return 255;
    }
    else if (v < 128)
    {
        return (127 - v) * 4;
    }
    else
    {
        return 0;
    }
}

void ThermoScale(Image *img)
{
    int i, j;
    unsigned int index;
    unsigned char gray;
    for (i = 0; i < img->height; i++)
    {
        for (j = 0; j < img->width; j++)
        {
            index = i * img->width + j;
            gray = img->data[index].r * 0.299 + img->data[index].g * 0.587 + img->data[index].b * 0.114;

            img->data[index].r = thermoR(gray);
            img->data[index].g = thermoG(gray);
            img->data[index].b = thermoB(gray);
        }
    }
}

```

まず、課題Aの結果のようにグレースケールに変換します。
その後、R,G,Bのそれぞれの値を、`thermoR()`, `thermoG()`, `thermoB()`でサーモグラフィーの値に変換します。
これによって標準画像からサーモグラフィーを出力することができます。

### 結果

元画像はこれです。

![元画像](./sample.bmp)

変換されたサーモグラフィーの画像はこれです。

![サーモグラフィー画像](./thermo.bmp)
