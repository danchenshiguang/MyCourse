#include<stdio.h> 
#include<stdlib.h>
# define  Max   100
int main()
{
	//fgetc 获取一个字节
	//fgets(string ,fp)  获取多个字节，即字符串
	//fread（string，10,2， fp） 10表示读取的长度，2表示读取的次数，存储在string中
	//fprintf("%s","dow")将控制台中的数打印到文件
	//fscanf("%s",$dsoa)将文件中的数据扫描入控制台 
	 //fseek(fp,1,SEEK_SET)1表示定位在文件参考点后1位的位置 SEEK_SET为头 SEEK_END为尾，SEEK_CUR为文件当前位置 
	 //ftell(fp);告诉文件指针的当前位置
	 //rewind(fp)将文件指针移到开头 
	FILE *fp;
	char ch;
	char string[Max];
	int fnow_point;
	
	if((fp=fopen("D:\\学习材料\\程序设计基础\\C库\\文件读写\\测试.txt","r"))==NULL)
	{
		printf("文件打开异常\n");
		exit(0);
	}
	fgets(string,3,fp);
	printf("%s\n",string);
	
	//指针在当前位置向后偏移一位 
	fseek(fp,1,SEEK_CUR); 
	fgets(string,3,fp);
	printf("%s\n",string);
	 
	fnow_point=ftell(fp);//记录当前指针位置 
	
	rewind(fp);//将文件指针移到文件的开头 
	fseek(fp,fnow_point,SEEK_CUR); 
	fgets(string,3,fp);
	printf("%s\n",string);
	
	//将文件指针的位置指向文件的末尾 
	fseek(fp,-3,SEEK_END);
	fgets(string,3,fp);
	printf("%s\n",string);
	fclose(fp);
	
}
