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
	int nt,p,i,j,k,l,frms=1000,frame=10;
	short fchoice;
    long seed,idum;
    double ti,tf,sum,dtk,c1;
    FILE *dif, *data;
    char output[40], nome[40];


// Read data from file

	
	mkdir("./figs", 0700);
	mkdir("./pics", 0700);

    data = fopen("data2.in","r");
    fscanf(data,"%d",&nt);
    fscanf(data,"%d",&p);
    fscanf(data,"%li",&seed);
    fscanf(data,"%lf",&ti);
    fscanf(data,"%lf",&tf);
    fscanf(data,"%lf",&c1);
    fscanf(data,"%hi",&fchoice);
    fclose(data);

//                                     //

	for (l=1;l<frms;l++)
	{
    double *tk=(double*)malloc((nt+1)*sizeof(double));
    double *ou1=(double*)malloc((nt+1)*sizeof(double));
	
	dif = fopen("temp.dat","w");
	p += 3;
	
    double** wt = DoubleArray(p,nt+1);
    double** dw = DoubleArray(p,nt+1);
    double** v  = DoubleArray(p,nt+1);
    
    idum = -seed;

//      generate wiener process        //

    wiener2(nt,p,&idum,ti,tf,tk,wt);
   
/*   Prepare initial conditions   */

    ou1[0] = c1;
    v[0][0] = c1;

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
        }


    fclose(dif);
	
	
/*		Animation loop		*/	
	
         if (l%frame==0)
             {
              FILE *pipe = popen("gnuplot","w");
              
              if(l<10)
              sprintf(nome,"00000%i", l/frame);
              else if(l<100)
              sprintf(nome,"0000%i", l/frame);
              else if(l<1000)
              sprintf(nome,"000%i", l/frame);
              else if(l<10000)
              sprintf(nome,"00%i", l/frame);
              else if(l<100000)
              sprintf(nome,"0%i", l/frame);
              
              fprintf(pipe, "call 'OU-plot-png--vid.gp' '%s' 'temp.dat' '%d' '%g'\n",nome,p,c1);
              fclose(pipe);
             }	
             
             
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
		
		free(tk);
		free(ou1);
		
		printf("step = %i\n",l);
	
	}
    
    
    


    return;
}
