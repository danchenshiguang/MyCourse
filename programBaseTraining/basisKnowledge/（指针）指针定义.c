#include<stdio.h> 
int main()
{
	//&是取址符，*是取值符 
	char a='f';
	int b=123;
	char *s1=&a;
	int *s2=&b;
	//通过指针，获取值
	printf("a=%c\n",*s1) ;
	printf("b=%d\n",*s2);
	printf("地址是%x\n",s2); 
	printf("地址是%x\n",&b);
	//通过指针，修改变量里面的值
	*s1='h';
	printf("现在a是%c",a);
	//int 占2字节 char占 1字节 float 4 double 8 
	//指针变量所占字节
	printf("s1占字节%d\n",sizeof(s1));
	printf("s2占字节%d\n",sizeof(s2)); 
	//打印地址   使用%p 
	printf("s2的地址%p\n",s2);
	printf("s2的地址%p\n",&b);
	printf("s2的地址%p\n",&s2);
	printf("s2的地址%p\n",*s2);
	printf("s2的地址%p\n",b);
	//void 类型指针表示通用类型指针，一般不建议使用	

}

