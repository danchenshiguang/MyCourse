#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n;
	int account=0;
	printf("����������n\n");
	scanf("%d",&n);
	while(n!=0)
	{
		n/=10;
		account++;
	}
	printf("\n���������λ��Ϊ%d",account);
}
