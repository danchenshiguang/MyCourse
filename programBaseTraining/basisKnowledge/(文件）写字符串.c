#include<stdio.h> 
#include<stdlib.h>
int main()
{
	FILE * ofile;
	char ch;
	char string[100];
	//安全打开文件的方式 
	if((ofile=fopen("D:\\学习材料\\程序设计基础\\C库\\文件读写\\写入字符串.txt","w"))==NULL)
	{
		printf("FILE OPEN WRONG");
		exit(0) ;
	}
	printf("please input a string :");
	gets(string);//从键盘输入一串字符串到控制台程序 
	fputs(string,ofile);//将string输出（写入）到文件 
	fclose(ofile);
}
