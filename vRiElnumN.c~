/* 
   Program to generate the paths, in velocity space, of a diffusion process for p/3 particles
   in a sphere of constant energy. The evolution of one velocity component is printed in a .dat file
   specifying the total number of particles used in the run. Result is compared with a one-dimensional
   Ornstein-Uhlenbeck process driven by the same noise term.
   An Euler method based on Kloeden,Platen,Schurz is used to generate the time evolution of the processes.

   Bruno Vieira Ribeiro - Universidade de Brasilia, 2013
*/

  #include<stdio.h>
  #include<math.h>
  #include<stdlib.h>
  #include<string.h>
  
  #include "Make2dArray.c"
  #include "wiener2.c"


/*Function Prototypes*/

int main()
{
	int nt,p,i,j,k;
	short fchoice;
    long seed,idum;
    double ti,tf,sum,dtk,c1;
//    double tk[NMAX],ou1[NMAX];
//    double wt[PMAX][NMAX],dw[PMAX][NMAX],v[PMAX][NMAX];
    FILE *dif, *data, *vel;
    char output[40], nome[40], output3[40];

// Read data from file

	mkdir("./figs", 0700);

    data = fopen("data2.in","r");
    fscanf(data,"%d",&nt);
    fscanf(data,"%d",&p);
    fscanf(data,"%li",&seed);
    fscanf(data,"%lf",&ti);
    fscanf(data,"%lf",&tf);
    fscanf(data,"%lf",&c1);
    fscanf(data,"%hi",&fchoice);
    fclose(data);
    
    double *tk=(double*)malloc((nt+1)*sizeof(double));
    double *ou1=(double*)malloc((nt+1)*sizeof(double));
    
    double** wt = DoubleArray(p,nt+1);
    double** dw = DoubleArray(p,nt+1);
    double** v  = DoubleArray(p,nt+1);

    sprintf(output, "./figs/D-%d-10c1-%g.dat", p,10*c1);
    dif = fopen(output,"w");
    sprintf(output3, "./figs/D-%d-10c1-%g--v3.dat", p,10*c1);
    vel = fopen(output3,"w");

//                                     //
//      generate wiener process        //

    idum = -seed;

    wiener2(nt,p,&idum,ti,tf,tk,wt);

    ou1[0] = c1;
    v[0][0] = c1;


/*   Prepare initial conditions   */

    for(j=1;j<p;j++)
        {
        v[j][0] = (p - c1*c1)/(p - 1.);
        }

/*   Generate Wiener increments   */

    for(k=0;k<nt;k++)
        {
        for(j=0;j<p;j++)
            {
            dw[j][k] = wt[j][k+1] - wt[j][k];
            }
        }    


/*   Euler scheme    */
    for(k=0;k<nt;k++)
        {
        dtk = tk[k+1]-tk[k];
        ou1[k+1] = ou1[k] + dw[0][k] - (0.5)*ou1[k]*dtk;
        sum = 0.0;
        for(i=0;i<p;i++)
            {
            sum = sum + v[i][k]*dw[i][k];
            }
        for(j=0;j<p;j++)
            {
            v[j][k+1]   = v[j][k] + dw[j][k] - (v[j][k]/(double)p)*sum - (1. - 1./(double)p)*(v[j][k]/2.)*dtk; 
            }
        fprintf(dif,"%le  %le  %le  %le \n",tk[k],v[0][k],ou1[k],(v[0][k]-ou1[k]));
        if (p==3)	fprintf(vel,"%le  %le\n",tk[k],(v[0][k]*v[0][k] + v[1][k]*v[1][k] + v[2][k]*v[2][k]));        
        }


    fclose(dif);
    
    
	FILE *pipe = popen("gnuplot","w");
	sprintf(nome,"D-%d-10c1-%g", p,10*c1);
	if(fchoice == 0)
	{
		fprintf(pipe, "call 'OU-plot-eps.gp' '%s' '%s' '%d' '%g'\n",nome,output,p,c1);
	}
	else if(fchoice == 1)
	{
		fprintf(pipe, "call 'OU-plot-png.gp' '%s' '%s' '%d' '%g'\n",nome,output,p,c1);
	}
	fclose(pipe);
    
    
    
	for(i=0; i<p; i++)
	{
		free(wt[i]);
	}
	free(wt);
	
	for(i=0; i<p; i++)
	{
		free(dw[i]);
	}
	free(dw);
	
	for(i=0; i<p; i++)
	{
		free(v[i]);
	}
	free(v);

    return;
}
