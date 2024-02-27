#include <stdio.h>
#include <stdlib.h>
#define N  9
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main()
{
	int  a[]={1,8,2,4,3,6,5,0,9,7};
	int i=0,j,k;
	int mid1,mid2;
	for(i;i<N-1;i++)
	{
	
		for(j=i+1;j<N;j++)
		{
			k=i;
			if(a[j]>a[k])
			k=j;
		} 
		if(k!=i)
		{
			mid1=a[k];
			a[k]=a[i];
			a[i]=mid1;
			mid2=k;
			k=i;
			i=mid2;
		}
	}
	for(i=0;i<N;i++)
	{
		printf("%d",a[i]);
	}
		return 0;
}
