#include<stdio.h> 
int main()
{
	//定义数组
	int m[5] ={1,4,3,2,5};
	//定义数组指针
	//用一个指针变量存储数组的首地址  数组名和数字下标为0的地址是一样的 
	int (*p1)=m;
	int (*p2) [5]=&m;
	int i;
	for(i=0;i<5;i++) 
	{
		printf("%d\t",*(p1+i));
	}
	printf("\n**************\n");
	for(i=0;i<5;i++) 
	{
		printf("%d\t",*p1+i);//wrong，数组指针的偏移量不能这样表示。 
	}	
	printf("\n**************\n");
	for(i=0;i<5;i++) 
	{
		printf("%d\t",*(*p2+i));
	}
	printf("\n%d",**p2) ;
}

