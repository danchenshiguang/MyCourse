#include<stdio.h> 
#include<stdlib.h>
int main()
{
	FILE * ofile;
	char ch;
	char string[100];
	char newString[100];
	//��ȫ���ļ��ķ�ʽ 
	if((ofile=fopen("D:\\ѧϰ����\\������ƻ���\\C��\\�ļ���д\\д���ַ���.txt","r"))==NULL)
	{
		printf("FILE OPEN WRONG");
		exit(0) ;
	}
	fgets(newString,sizeof(string),ofile);
	printf("%s",newString);
	fclose(ofile);
}
