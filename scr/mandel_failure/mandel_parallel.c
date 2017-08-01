
/*
  マンデルブロ集合計算プログラム
 
*/
#include <stdio.h>
#include <math.h>
 
#define C0r     -0.743  // 計算する場所の中心座標（実数部）
#define C0i      0.1145 // 計算する場所の中心座標（虚数部）
#define VS       1  // 計算する場所の中心座標からの範囲（±VS）
 
#define NMAX     20000  // 計算の繰り返し上限
#define STEP     800.0  // 計算する刻み
 
 
double mandelbrot(double a, double b){
  double x = 0.0;
  double y = 0.0;
  double x1, y1;
 
  int n;
 
  for (n = 1; n <= NMAX; n++) {
    x1 = x * x - y * y + a;
    y1 = 2.0 * x * y + b;
    if ( x1 * x1 + y1 * y1 > 4.0) return log(n); // 発散
    x = x1;
    y = y1;
  }
  return 0; // 計算の繰り返し上限到達
}
 
 
int main() {
  double a, b;
  a = C0r-VS;
  b = C0i-VS;
  //printf("%1.14e\n",a);
  //#pragma omp parallel
  //{
  #pragma omp parallel for ordered
  //for (a = C0r-VS; a < C0r+VS; a += 2.0*VS/STEP) {
  for(int i=0; i<801; i++){
    //#pragma omp parallel for ordered
      for(int j=0; j<801; j++){
	//for (b = C0i-VS; b < C0i+VS; b += 2.0*VS/STEP) {
	#pragma omp ordered
	{
	  printf("%1.14e %1.14e %1.14e\n", a, b, mandelbrot(a, b));
	  //mandelbrot(a,b);
	b += 2.0*VS/STEP;
	}
      }
    b = C0i-VS;
    a += 2.0*VS/STEP;
    printf("\n"); // これがないとgnuplotでエラーが出る
    //}
  }
  return 0;
}

