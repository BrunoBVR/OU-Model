/*
   Wiener path generator. Generates 2*p independent paths.

   Bruno Vieira Ribeiro - Universidade de Brasilia, 2013
*/

  #include<stdio.h>
  #include<math.h>
  #include<stdlib.h>


  #include "boxm2.c"
//  #include "Make2dArray.c"

/*Function Prototypes*/


void wiener2(long n, long p, long *idum, double ti, double tf, double *tk, double **wt)
{
    long i,k;
    double delta,sqdelta;
    double** x = DoubleArray(p,n);
    

    delta = (tf - ti)/((double)n);
    sqdelta = sqrt(delta);
    tk[0] = 0.0;

/*   Prepare initial conditions   */
    for (i=0;i<p;i++)
        {
        wt[i][0] = 0.0;
        }

    boxm2(n,p,idum,x);


    for(k=0;k<n;k++)
        {
        tk[k+1]  = tk[k] + delta;
        for (i=0;i<p;i++)
            {
            wt[i][k+1] = wt[i][k] + x[i][k]*sqdelta;
            }
        }
        
	for(i=0; i<p; i++)
	{
		free(x[i]);
	}
	free(x);

    return;
}
