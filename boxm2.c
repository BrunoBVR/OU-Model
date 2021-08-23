/*
   Box-Muller gaussian generator

   Bruno Vieira Ribeiro - Universidade de Brasilia, 2013
*/

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "ran2.c"



//float ran2(long *);

void boxm2(long n, long p, long *idum, double **x)
{
    long i,j;
    double xx,yy;

    for (j=0;j<p;j++)
        {
        for (i=0;i<n;i++)
            {
            xx =(double) ran2(idum);
            yy =(double) ran2(idum);

            x[j][i] = sqrt(-2.*log(xx))*sin((double)(i%2)*(M_PI_2) - 2.*M_PI*yy);
            }
        }
    return;

}
