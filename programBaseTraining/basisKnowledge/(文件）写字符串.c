#include<stdio.h> 
#include<stdlib.h>
int main()
{
	FILE * ofile;
	char ch;
	char string[100];
	//��ȫ���ļ��ķ�ʽ 
	if((ofile=fopen("D:\\ѧϰ����\\������ƻ���\\C��\\�ļ���д\\д���ַ���.txt","w"))==NULL)
	{
		printf("FILE OPEN WRONG");
		exit(0) ;
	}
	printf("please input a string :");
	gets(string);//�Ӽ�������һ���ַ���������̨���� 
	fputs(string,ofile);//��string�����д�룩���ļ� 
	fclose(ofile);
}
