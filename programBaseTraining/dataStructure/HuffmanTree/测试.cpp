#include<stdio.h>
int *m(int *k)
{
	k[1]=1;
	k[0]=2;
	return k;
}
int main()
{
	int k[2];
	m(k);
	printf("%d",k[0]);
}
