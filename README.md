# todai-bitmap

東京大学・画像処理工学の授業課題

- レポート課題1
  - 課題A: 視感度特性に基づいて、RGB画像をグレースケール画像に変換
  - 課題B: 標準画像からサーモグラフィーを生成
  - 課題C: ポスタリゼーション、ソラリゼーション、あるいは、その他の自由課題を一つ
- レポート課題2
  - 課題1: 勾配画像の生成
  - 課題2: 2値化

これらをC言語で実装しています。

## Macでのbitmap画像の生成

ImageMagickを利用

```bash
convert sample.jpg -type truecolor -rotate 90 sample.bmp
```

## インストールと実行

macOSで動かすことを想定しています。
また、`gcc`、`make`がインストールされていることを想定しています。

```bash
# ソースコードのダウンロード
git clone https://github.com/kawasin73/todai-bmp && cd todai-bmp
# コンパイル
make
# 課題A
./gray sample.bmp gray.bmp
# 課題B
./thermo sample.bmp thermo.bmp
# 課題C 4段階のポスタリゼーション
./post sample.bmp post.bmp

# 2 課題1 画像のエッジ
./sobel-main sample.bmp sobel.bmp

# 2 課題2 2値化
./sobel-binary sample.bmp edge.bmp

# ビルド結果と生成物の削除
make clean
rm gray.bmp thermo.bmp post.bmp sobel.bmp edge.bmp
```

## LISENCE

以下の3つのソースコードは、[物理のかぎしっぽ](http://hooktail.org/computer/index.php?Bitmap%A5%D5%A5%A1%A5%A4%A5%EB%A4%F2%C6%FE%BD%D0%CE%CF%A4%B7%A4%C6%A4%DF%A4%EB)から引用しました。

- `copybmp.c`
- `bitmap.c`
- `bitmap.h`

それ以外のファイルについては、MITライセンスとします。
