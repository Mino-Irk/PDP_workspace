#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define         X_RESN  800       /* x resolution */
#define         Y_RESN  800       /* y resolution */
#define         X_MIN   -2.0
#define         X_MAX    2.0
#define         Y_MIN   -2.0
#define         Y_MAX    2.0


typedef struct complextype
{
  float real, imag;
} Compl;


int main ( int argc, char* argv[])
{

  /* Mandlebrot variables */
  int i, j, k;
  Compl   z, c;
  float   lengthsq, temp;
  int maxIterations;
  int res[X_RESN][Y_RESN]; 


         
  /* Calculate and draw points */
  maxIterations = atoi( argv[1] );
#pragma omp parallel for shared(res,maxIterations) private(i,j,z,c,k,temp,lengthsq)
  for(i=0; i < Y_RESN; i++) 
    for(j=0; j < X_RESN; j++) {
      z.real = z.imag = 0.0;
      c.real = X_MIN + j * (X_MAX - X_MIN)/X_RESN;
      c.imag = Y_MAX - i * (Y_MAX - Y_MIN)/Y_RESN;
      k = 0;

      do  {    /* iterate for pixel color */

	temp = z.real*z.real - z.imag*z.imag + c.real;
	z.imag = 2.0*z.real*z.imag + c.imag;
	z.real = temp;
	lengthsq = z.real*z.real+z.imag*z.imag;
	k++;

      } while (lengthsq < 4.0 && k < maxIterations);

      if (k >= maxIterations) res[i][j] = 0;
      else res[i][j] = 1;

    }
  printf("%d\n", res[0][0]);
         

  /* Program Finished */
  return 0;
}
