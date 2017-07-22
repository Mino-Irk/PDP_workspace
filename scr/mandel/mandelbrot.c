#include<math.h>
#include<complex.h>
#include<GL/glut.h>
using namespace std;

typedef complex<double> cox_t;

int scale=2000;
double m=2.0;

void mandelbrot()
{
  int i;
  int x, y;
  double limit = 1e8;
  int iter = 50;
  double color;

  for(x=-scale; x<scale; x++){
    // OpenMPを有効にすると生成するグラフィックが乱れる。
    // マルチスレッド考慮されていないステートマシンのOpenGLの内部でコマンドが混乱するのだと思われる.
    // 下の1行を削除するだけで正常動作する。
    # pragma omp parallel 
    for(y=-scale; y<scale; y++){
      cox_t c((x*1./scale)*m, (y*1./scale)*m), z(0, 0);

      for(i=0; i<iter; i++){
	z = z*z + c;
	if(abs(z) > limit){
	  // 発散
	  color = (double)i/iter;
	  glColor3d(color, color, color);
	  glVertex2d((x*1./scale), (y*1./scale));
	  break;
	}
      }
      if(i==iter){
	glColor3d(0,0,0); glVertex2d((x*1./scale), (y*1./scale));
      }
    }
  }
}

void display()
{
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
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
  glutMainLoop();
  return 0;
}
