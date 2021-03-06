#include <stdio.h>
#include <stdlib.h>

#define MESHX 1000

#define ntime 20000
#define deltat 0.1
#define deltax 1.0
#define saveT 100

// #define DIRICHLET
#define NEUMANN
#ifdef DIRICHLET
 #define const_back 0.5
 #define const_front 0.5
#endif

void apply_bc();
void update (double *c_new, double *c_old);
void writetofile (FILE *fp, double *c);
void initialize(double *c);


void main (){
	long x,t;
	double c_old[MESHX];
	double c_new[MESHX];
	double inv_deltax2 = 1.0/(deltax*deltax);
	char filename[1000];
	FILE *fp;
	
	initialize (c_old);
	
	for (t=0;t<ntime ;t++){
	for (x=1;x<MESHX-1;x++)
	{
		c_new[x]=c_old[x]+ 10*deltat*inv_deltax2*(c_old[x+1] - 2*c_old[x] + c_old[x-1]);
	}
		apply_bc(c_new);
		update (c_new, c_old);
		if (t%saveT == 0){
		sprintf(filename,"composition%ld.dat", t);
		fp=fopen (filename,"w");
		writetofile (fp, c_new);
		fclose (fp);
	}
  }
}
void initialize(double *c)
{
 long x;
  for (x=0 ; x<MESHX/2; x++)
  {
	  c[x] = 0.1;
  }
  for (x=MESHX/2; x<MESHX; x++)
  {
	  c[x] = 0.5;
  }
}
void apply_bc(double *c)
{
#ifdef NEUMANN
 c[0] = c[1];
 c[MESHX-1] = c[MESHX-2];
#endif

#ifdef DIRICHLET
 c[0] = const_back;
 c[MESHX-1] = const_front;
#endif
}

void update (double *c_new, double *c_old)
{
long x;
for (x=0;x<MESHX;x++)
{
	c_old[x] = c_new[x];
}
}

void writetofile (FILE *fp, double *c) 
{
 long x;
 for (x=0;x<MESHX;x++)
 {
		fprintf (fp, "%le %le\n",x*deltax, c[x]);
 }	
}
