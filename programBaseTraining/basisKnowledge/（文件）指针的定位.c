#include<stdio.h> 
#include<stdlib.h>
# define  Max   100
int main()
{
	//fgetc ��ȡһ���ֽ�
	//fgets(string ,fp)  ��ȡ����ֽڣ����ַ���
	//fread��string��10,2�� fp�� 10��ʾ��ȡ�ĳ��ȣ�2��ʾ��ȡ�Ĵ������洢��string��
	//fprintf("%s","dow")������̨�е�����ӡ���ļ�
	//fscanf("%s",$dsoa)���ļ��е�����ɨ�������̨ 
	 //fseek(fp,1,SEEK_SET)1��ʾ��λ���ļ��ο����1λ��λ�� SEEK_SETΪͷ SEEK_ENDΪβ��SEEK_CURΪ�ļ���ǰλ�� 
	 //ftell(fp);�����ļ�ָ��ĵ�ǰλ��
	 //rewind(fp)���ļ�ָ���Ƶ���ͷ 
	FILE *fp;
	char ch;
	char string[Max];
	int fnow_point;
	
	if((fp=fopen("D:\\ѧϰ����\\������ƻ���\\C��\\�ļ���д\\����.txt","r"))==NULL)
	{
		printf("�ļ����쳣\n");
		exit(0);
	}
	fgets(string,3,fp);
	printf("%s\n",string);
	
	//ָ���ڵ�ǰλ�����ƫ��һλ 
	fseek(fp,1,SEEK_CUR); 
	fgets(string,3,fp);
	printf("%s\n",string);
	 
	fnow_point=ftell(fp);//��¼��ǰָ��λ�� 
	
	rewind(fp);//���ļ�ָ���Ƶ��ļ��Ŀ�ͷ 
	fseek(fp,fnow_point,SEEK_CUR); 
	fgets(string,3,fp);
	printf("%s\n",string);
	
	//���ļ�ָ���λ��ָ���ļ���ĩβ 
	fseek(fp,-3,SEEK_END);
	fgets(string,3,fp);
	printf("%s\n",string);
	fclose(fp);
	
}
