#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  Max   1000
void loginSuperAdmin()//���볬������Ա���� 
{
	while(1)
	{
		int choice;
		printf("0>�˳�\n");
		printf("1>��������Ա��¼\n");
		printf("���룺");
		scanf("%d",&choice);
			while(choice>1||choice<0)
		{
			printf("�������������\n?");
			scanf("%d",&choice);
		}
		switch(choice)
		{
			case 0:
				break;
			case 1:
				printf("choice Ϊ 1");
				break;			
			default:
				break; 		
		}
		if(choice==0)
		break;
	}
}
void loginAdmin()//�������Ա���� 
{
	while(1)
	{
		int choice;
		printf("0>�˳�\n");
		printf("1>����Ա��¼\n");
		printf("���룺");
		scanf("%d\n",&choice);
		while(choice>1||choice<0)
		{
			printf("�������������\n?");
			scanf("%d\n",&choice);
		}
		switch(choice)
		{
			case 0:
				exit(0) ; 
				break;
			case 1:
				printf("choice Ϊ 1");				
				break;
			default:
				break; 	
		}	
		if(choice==0)
			break;	
	}

}
void loginUser()//�����û�����
{
	while(1)
	{
		int choice;
		printf("0>�˳�\n");
		printf("1>����Ա��¼\n");
		printf("���룺");
		scanf("%d\n",&choice);
			while(choice>1||choice<0)
		{
			printf("�������������\n?");
			scanf("%d",&choice);
		}
		switch(choice)
		{
			case 0:
				break;
			case 1:
				printf("choice Ϊ 1");
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
		printf("��ѡ����Ҫ���еĲ���\n");
		printf("0>�˳�\n"); 	
		printf("1>��������Ա��¼\n"); 
		printf("2>����Ա��¼\n"); 
		printf("3>�û���¼\n");
		printf("?");
		scanf("%d",&choice) ;
		printf("%d",choice);
		while(choice>3||choice<0)
		{
			printf("�������������\n?");
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
