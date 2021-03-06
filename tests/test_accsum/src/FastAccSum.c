//#######################################
//## Author: Eric Petit
//## Mail eric.petit@prism.uvsq.fr
//#######################################

#include "all_header.h"




double FastAccSumIn(double *, unsigned int ); 

double FastAccSum(double *p, unsigned int n) {
  double *q, r;
  
  q = (double *)malloc(sizeof(double)*n);
  memcpy(q, p, sizeof(double)*n);
  r = FastAccSumIn(q, n);
  free(q);
  return r;
}


double FastAccSumIn(double *p, unsigned int n) {
	double res=0,abssum=0,sum=0,t=0,t_prime=0;
	int i=0;
	double sigma=0 , sigmaO=0 , sigma_prime=0 , T=0 , q=0 , tau=0, phi=0, tau2=0,u=0;
	double lim=ETA_DBL/URD_DBL;
	
	
	
	for(i=0;i<n;i++)
	{
		abssum+=fabs(p[i]);
		sum+=p[i];
	}
	
	T=abssum/(1-((double)n*URD_DBL));
	
	if ((T) <= (lim)) return sum;
	
	t_prime=0;
	//int m=0;
	do
	{
		//m++;
		sigmaO=(double)(2.*T/(1.-(3.*n+1.)*URD_DBL));
		sigma=sigmaO;
		for(i=0;i<n;i++)
		{
			sigma_prime= sigma+p[i];
			q=sigma_prime-sigma;
			p[i]=p[i]-q;
			sigma=sigma_prime;
		}
		
		tau=sigma-sigmaO;
		//printf("tau=%f\n",tau);
		t=t_prime;
		t_prime=t+tau;
		if (t_prime==0) 
			return res=FastAccSumIn(p,n);
		
		q=sigmaO/(2*URD_DBL);
		u=fabs(q/(1-URD_DBL)-q);
		
		phi= ((2*n*(n+2)*URD_DBL)*u)/(1-5*URD_DBL);
		
		T=fmin(     ((3./2.+4*URD_DBL)*(n*URD_DBL))*(sigmaO)    ,   2*n*URD_DBL*u  );
	}while(!((fabs(t_prime)>=phi)|| (4*T<=lim)) );
	//printf("m=%d\n",m);
	
	tau2=(t-t_prime)+tau;
	
	sum=0;
	for(i=0;i<n;i++)
	{
		sum+=p[i];
	}
	
	res=t_prime+(tau2+(sum));
	
	return res;
}
