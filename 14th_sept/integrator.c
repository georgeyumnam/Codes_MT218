#include <stdio.h>
#include <stdlib.h>

#define xrange 1
#define yrange 1

#define NRAM 10000000


void main ()
{
		double x,y;
		long accept=0;
		
		long iter;
		
		for (iter=0;iter<NRAM; iter++)
		{
			x=xrange*drand48();
			y=yrange*drand48();
			
			if (y<=x*x*x)
			{
				accept++;
			}
		}
		printf("area = %le\n",(double)(accept)/(double)(NRAM)*1.0);
}
