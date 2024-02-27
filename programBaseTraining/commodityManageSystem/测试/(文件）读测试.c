#include<stdio.h> 
#include<stdlib.h>
#define  MAX  100
int main()
{
	FILE *fp;
	fp=fopen("D:\\学习材料\\软件实训\\电商管理系统\\超级管理员名单.txt","r+");
	char string[MAX];
	char view1[MAX];
	char view2[MAX];
	int i=0,j=0;
	if(fp==NULL)
	{
		printf("文件打开异常\n");
		exit(0);
	}
	for(;!feof(fp);)
	{
		for(i=0;i<MAX;i++)
		{
			view1[i]='\0';
			view2[i]='\0';
		}
		fgets(string,sizeof(string),fp);
		for(i=0,j=0;string[i]!='_';j++,i++)
		{
			view1[i]=string[i];
		}
		i++;
		for(j=0;string[i]!='_';j++,i++)
		{
			view2[j]=string[i];
		}
		printf("%s\n",view1);
		printf("%s",view2);
	}
	fclose(fp);
	
}
