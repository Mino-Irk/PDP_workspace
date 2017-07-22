//
// OpenMPを使った並列マンデルブロ集合 ＋　ストライプ描画
//
#include<cmath>
#include<complex>
#include<omp.h>
#include<GL/glut.h>
using namespace std;

typedef complex<double> cox_t;

const int scale=512;
const double m=2.;
const double limit = 1e8;
const int iter = 50;

const int division = 4; // 分割数

void inner_loop(int x)
{
  double color;
  int i, y;
  cox_t c, z;
  // 検査する点によって負担の大きさが異なるので動的に割り振る
  // 共有変数はprivateで指定する。しない場合は共有変数になる。ループ変数はprivateになる。
# pragma omp parallel for schedule(dynamic, 1) private(c,z,i,color)
  for(y=-scale; y<scale; y++){
    c.real() = (x*1./scale)*m;
    c.imag() = (y*1./scale)*m;
    z.real() = z.imag() = 0.0;
    for(i=0; i<iter; i++){
      z = z*z + c;
      if(abs(z) > limit){
	// 発散
	color = (double)i/iter;
	glColor3d(color, color, color);
	glVertex2d((x*1./scale), (y*1./scale));
	break; // 関数の先ではbreakできる？
      }
    }
    if(i == iter){
      glColor3d(0,0,0); glVertex2d((x*1./scale), (y*1./scale));
    }
  }
}

void mandelbrot()
{
  int i, x;

  for(i=0; i<division; i++){
    for(x=-scale + i; x<scale; x += division){
      // x列目を描画
      inner_loop(x);
      glFlush();
    }
  }
}

void display()
{
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINT);
  mandelbrot();
  glEnd();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutCreateWindow("mandelbrot");
  glutDisplayFunc(display);

  glutMainLoop();
  return 0;
}
