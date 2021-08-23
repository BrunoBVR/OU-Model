#include<stdio.h>
#include<math.h>
#include<stdlib.h>

double** DoubleArray(int nx, int ny)
{

	double** array;
	int i;

	array = (double**) malloc(nx*sizeof(double*));
	
	for (i=0; i<nx; i++)
		array[i] = (double*) malloc(ny*sizeof(double));
		
	return array;

}
