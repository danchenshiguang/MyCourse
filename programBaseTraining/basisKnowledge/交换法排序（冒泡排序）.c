#include<stdio.h>
#define n   10
int main()
{
	int a[]={1,2,4,5,6,3,9,0,7,8};
	int i=0,j,mid;
	for(i;i<n-1;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(a[i]>a[j])
			{
				mid=a[i];
				a[i]=a[j];
				a[j]=mid;
			}
		}
	} 
	i=0;
	while(i<10)
	{
		printf("%d",a[i]);
		i++; 
	}
}
