#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n;
	int account=0;
	printf("请输入整数n\n");
	scanf("%d",&n);
	while(n!=0)
	{
		n/=10;
		account++;
	}
	printf("\n这个整数的位数为%d",account);
}
