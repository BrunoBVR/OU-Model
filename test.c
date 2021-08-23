#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int main()

{

	int i,n=100;
	double p;
	
	for(i=0;i<n;i++)
	{
		p = (double)(i%2)*M_PI;
		printf("%g\n",p);
	}
	

	return 0;

}
