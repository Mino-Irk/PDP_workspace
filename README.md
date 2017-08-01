# PDP_workspace
##OpenMPの使い方
ソースコードのコンパイル時に
`gcc -openmp -o 実行ファイルの名前 ソースコード名`
でコンパイルしてもらうとOpenMPが適応された実行ファイルが生成されます．

##同梱されているファイルについて
###mandel_success
* mand.c：並列化に成功したプログラム
* mand：mand.cをOpenMP無効でコンパイルした実行ファイル
* mandel_parallel：mand.cをOpenMP有効でコンパイルした実行ファイル
* success.png：プログラム実行時のターミナルのスクショ

###mandel_failure
* mandelblot.c：並列化なしのプログラム(エラーなし)
* mandel_parallel.c：OpenMP有効でコンパイルしたものの，全く並列化されておらず，実行時間も変わらなかったプログラム
* mandel_parallel2.c：実行時間がmandelblot.cの4分の1にはなっているが，実際は並列化処理を行ったことで出力値が4分の1欠けてしまっていたプログラム
* mandelblot.txt：mandelblot.cで出力された値のtxt．
* png.gnuplot：出力されたtxtを元にマンデルブロ描写を行うプログラム．出力後のファイルの名前の変更はこっちで．
* mandelblot_parallel.png：mandelblot\_parallel2.cで出力された値から生成した画像．値が4分の1欠けているためかちょっとぶれている
* mandelblot.png：mandelblot.pngから出力された値(mendelblot.txt)から生成した画像．
=======
## 締め切り

8/2(水)1限 8分のプレゼン

## スライド場所
https://docs.google.com/presentation/d/1mg4OD05SSERKyA4I5dSIsmybVc1s-LkoAoY159igv7s/edit#slide=id.p

## リポジトリ内容
+ 実験ソースコード
+ 最終報告書

