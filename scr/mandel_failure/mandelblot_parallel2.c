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

  //#pragma omp parallel for
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
  while(1){
    #pragma omp parallel //while
    while (1) {
      a += 2.0*VS/STEP;
      //double a1 = 2.0*VS/STEP;
      b = C0i-VS; 
      while(1){
	b += 2.0*VS/STEP;
	printf("%1.14e %1.14e %1.14e\n", a, b, mandelbrot(a, b));
	//printf("\n"); // これがないとgnuplotでエラーが出る
	if (b>=C0i+VS) {
	  break;
	}
      }
  
      //if (a != a1) {
      //printf("\n");
      //a += a1;
      //}
      //printf("\n");
      //if (a>=C0r+VS) {
	break;
	//}
    }
    printf("\n");
    if(a>=C0r+VS){
      break;
    }
  }
  return 0;
}

