#include<stdio.h> 
int main()
{
	int w=343;
	int*p1=&w;
	int *p2=p1;
	int **p3=&p2;
	printf("地址%p\n",p2);
	printf("地址%p\n",p1);
	printf("地址%p\n",&w);
	printf("地址%p\n",*p3);	
}
