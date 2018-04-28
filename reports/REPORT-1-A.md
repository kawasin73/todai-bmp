# 課題Aレポート

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

グレースケールの書き出しは以下の`gray.c`のソースコードで実現します。

```c:gray.c
#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>

void GrayScale(Image *img);

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

    GrayScale(colorimg);

    if (Write_Bmp(argv[2], colorimg))
    {
        exit(1);
    }

    Free_Image(colorimg);

    return 0;
}

void GrayScale(Image *img)
{
    int i, j;
    unsigned int index;
    unsigned char color;

    for (i = 0; i < img->height; i++)
    {
        for (j = 0; j < img->width; j++)
        {
            index = img->width * i + j;
            color = img->data[index].r * 0.299 + img->data[index].g * 0.587 + img->data[index].b * 0.114;
            img->data[index].r = img->data[index].g = img->data[index].b = color;
        }
    }
}

```

グレースケールへの変換は`void GrayScale(Image *img)`で行なっています。
この関数の中では、１ピクセルずつRGBの値をグレースケールの値に変換し、変換した値は、R,G,Bの全てに代入しなおしています。

### 結果

元画像はこれです。

![元画像](./sample.bmp)

変換されたグレースケールの画像はこれです。

![グレースケール画像](./gray.bmp)
