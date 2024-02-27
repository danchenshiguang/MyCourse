#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  Max   1000
void loginSuperAdmin()//进入超级管理员界面 
{
	while(1)
	{
		int choice;
		printf("0>退出\n");
		printf("1>超级管理员登录\n");
		printf("输入：");
		scanf("%d",&choice);
			while(choice>1||choice<0)
		{
			printf("输入错误，请重试\n?");
			scanf("%d",&choice);
		}
		switch(choice)
		{
			case 0:
				break;
			case 1:
				printf("choice 为 1");
				break;			
			default:
				break; 		
		}
		if(choice==0)
		break;
	}
}
void loginAdmin()//进入管理员界面 
{
	while(1)
	{
		int choice;
		printf("0>退出\n");
		printf("1>管理员登录\n");
		printf("输入：");
		scanf("%d\n",&choice);
		while(choice>1||choice<0)
		{
			printf("输入错误，请重试\n?");
			scanf("%d\n",&choice);
		}
		switch(choice)
		{
			case 0:
				exit(0) ; 
				break;
			case 1:
				printf("choice 为 1");				
				break;
			default:
				break; 	
		}	
		if(choice==0)
			break;	
	}

}
void loginUser()//进入用户界面
{
	while(1)
	{
		int choice;
		printf("0>退出\n");
		printf("1>管理员登录\n");
		printf("输入：");
		scanf("%d\n",&choice);
			while(choice>1||choice<0)
		{
			printf("输入错误，请重试\n?");
			scanf("%d",&choice);
		}
		switch(choice)
		{
			case 0:
				break;
			case 1:
				printf("choice 为 1");
				break;			
			default:
				break; 				
		}
		if(choice==0)
			break;						
	}

 } 
int main()
{
	while(1)
	{
		int choice;
		printf("请选择您要进行的操作\n");
		printf("0>退出\n"); 	
		printf("1>超级管理员登录\n"); 
		printf("2>管理员登录\n"); 
		printf("3>用户登录\n");
		printf("?");
		scanf("%d",&choice) ;
		printf("%d",choice);
		while(choice>3||choice<0)
		{
			printf("输入错误，请重试\n?");
			scanf("%d",&choice);
		}
		switch(choice)
		{
			case 0:
				exit(0);
				break;
			case 1:
				loginSuperAdmin();
				break;
			case 2:
				loginAdmin();
				break;			
			case 3:
				loginUser();
				break;
			default:  break;	
		}
	 	if(choice==0)
	 	break;
	
	}

}
