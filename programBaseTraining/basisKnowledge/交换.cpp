# include<stdio.h>
void swap( int a, int b);
void newSwap(int *a,int *b);
int  main() 
{
	int a=5;
	int b= 6;
	swap(a,b);
	printf("������a=%d,b=%d\n",a,b);
	newSwap(&a,&b);
	printf("�ٴν�����a=%d,b=%d\n",a,b);
	return 0;
	
}
void swap( int a, int b)
{
	int t=0;
	t = a;
	a = b;
	b = t;
}//���󣬵��ú���ʱ��ֻ�ܵ���ֵ��a,b�����Լ�������ռ䣬 �뿪���ǵĿ飬���ǾͲ������� 
void newSwap(int *a,int *b)
{
	int t;
	t=*a;
	*a=*b;
	*b=t;
}
 

