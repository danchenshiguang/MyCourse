#include<stdio.h> 
#include<stdlib.h>
int main()
{
	FILE * ofile;
	char ch;
	char string[100];
	char newString[100];
	//安全打开文件的方式 
	if((ofile=fopen("D:\\学习材料\\程序设计基础\\C库\\文件读写\\写入字符串.txt","r"))==NULL)
	{
		printf("FILE OPEN WRONG");
		exit(0) ;
	}
	fgets(newString,sizeof(string),ofile);
	printf("%s",newString);
	fclose(ofile);
}
