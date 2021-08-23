  #include<stdio.h>
  #include<math.h>
  #include<stdlib.h>

  
  #include "Make2dArray.c"
  #include "wiener2.c"

/*    Function Prototypes    */

//void wiener2(long, long, long *, double, double, double [], double [][NMAX]);

int main()
{

    long nt,ns,p,i,j,k,l,seed,idum;
    double ti,tf,sum,dtk,c1,error;
    FILE *dif, *data, *err;
    char output[20];

/*    generate ns paths    */
    err = fopen("AbsErr.dat","w");

    ns=500;
    error=0.0;
 
    for(l=0;l<=ns;l++)
        { 
/*    Read data from file    */

        data = fopen("data2.in","r");
        fscanf(data,"%li",&nt);
        fscanf(data,"%li",&p);
        fscanf(data,"%li",&seed);
        fscanf(data,"%lf",&ti);
        fscanf(data,"%lf",&tf);
        fscanf(data,"%lf",&c1);
        fclose(data);

        idum = -seed;
        
        
    double *tk=(double*)malloc((nt+1)*sizeof(double));
    double *ou1=(double*)malloc((nt+1)*sizeof(double));
    
    double** wt = DoubleArray(p,nt+1);
    double** dw = DoubleArray(p,nt+1);
    double** v  = DoubleArray(p,nt+1);


/*    Generate wiener process    */

        idum = idum - l;

        wiener2(nt,p,&idum,ti,tf,tk,wt);

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
        }


        error = error + fabs(v[0][nt]-ou1[nt])/(double)ns;

        fprintf(err,"%li  %le \n",l,fabs(v[0][nt]-ou1[nt])/(double)ns);

 

    }
   printf("=============================================\n");
   printf("  Absolute error= %lf\n",error);
   printf("  ns=  %li\n",ns);
   printf("  p= %li\n",p);
   printf("=============================================\n\n");

    fclose(err);
    return;
}
