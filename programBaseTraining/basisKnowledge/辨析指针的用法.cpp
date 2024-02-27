#include<stdio.h>
int main()
{
	int *p;
	int a=1;
	p=&a;
	printf("%d\n",p) ;
	printf("%p\n",p);
	printf("%d\n",*p);
	printf("%p\n",*p);
	printf("%d\n",a);
	printf("%p\n",a);
	printf("%d\n",&a);
	printf("%p\n",&a);
 } 
