#include<stdio.h> 
int main()
{
	int a=1;
	int b=2;
	int c=3;
	int d=4;
	int e=5;
	//����ָ������
	int *p1[5] ={&a,&b,&c,&d,&e};
	//ѭ������
	int i;
	for(i=0;i<5;i++) 
	{
		printf("%d\t",*p1[i]);
	}
	printf("\n%d\n",*p1);
	printf("%d\n",*p1[0]); 

}

