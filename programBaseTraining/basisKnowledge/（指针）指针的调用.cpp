#include<stdio.h> 
int main()
{
	int w=343;
	int*p1=&w;
	int *p2=p1;
	int **p3=&p2;
	printf("��ַ%p\n",p2);
	printf("��ַ%p\n",p1);
	printf("��ַ%p\n",&w);
	printf("��ַ%p\n",*p3);	
}
