#include<stdio.h> 
int main()
{
	//&��ȡַ����*��ȡֵ�� 
	char a='f';
	int b=123;
	char *s1=&a;
	int *s2=&b;
	//ͨ��ָ�룬��ȡֵ
	printf("a=%c\n",*s1) ;
	printf("b=%d\n",*s2);
	printf("��ַ��%x\n",s2); 
	printf("��ַ��%x\n",&b);
	//ͨ��ָ�룬�޸ı��������ֵ
	*s1='h';
	printf("����a��%c",a);
	//int ռ2�ֽ� charռ 1�ֽ� float 4 double 8 
	//ָ�������ռ�ֽ�
	printf("s1ռ�ֽ�%d\n",sizeof(s1));
	printf("s2ռ�ֽ�%d\n",sizeof(s2)); 
	//��ӡ��ַ   ʹ��%p 
	printf("s2�ĵ�ַ%p\n",s2);
	printf("s2�ĵ�ַ%p\n",&b);
	printf("s2�ĵ�ַ%p\n",&s2);
	printf("s2�ĵ�ַ%p\n",*s2);
	printf("s2�ĵ�ַ%p\n",b);
	//void ����ָ���ʾͨ������ָ�룬һ�㲻����ʹ��	

}

