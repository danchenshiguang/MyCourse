# include<stdio.h>
void swap( int a, int b);
void newSwap(int *a,int *b);
int  main() 
{
	int a=5;
	int b= 6;
	swap(a,b);
	printf("交换后a=%d,b=%d\n",a,b);
	newSwap(&a,&b);
	printf("再次交换后a=%d,b=%d\n",a,b);
	return 0;
	
}
void swap( int a, int b)
{
	int t=0;
	t = a;
	a = b;
	b = t;
}//错误，调用函数时，只能调入值。a,b存在自己的生存空间， 离开他们的块，他们就不会生存 
void newSwap(int *a,int *b)
{
	int t;
	t=*a;
	*a=*b;
	*b=t;
}
 

