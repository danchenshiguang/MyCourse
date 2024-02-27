#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct superAdministrator//超级管理员的结构体 
{
	int account;//超级管理员的账户 	int 6位数 
	int password;//超级管理员的密码    int 6位数 
	struct superAdministrator *next;//指向下一个超级管理员的指针 
};typedef  struct superAdministrator  SuperAdministrator;
SuperAdministrator* superAdministratorCreateList()
{
	SuperAdministrator*headNode=(SuperAdministrator*)malloc(sizeof(SuperAdministrator));
	headNode->account=0;
	headNode->password=0;
	headNode->next=NULL;
	return headNode;
 } 
SuperAdministrator*createSuperAdministrator(int account,int password)
{
 	SuperAdministrator*node=(SuperAdministrator*)malloc(sizeof(SuperAdministrator));
  	node->account=account;
  	node->password=password;
  	node->next=NULL;
}
void  wandSuperAdministrator(SuperAdministrator*head,int account,int password)
{
	SuperAdministrator* newNode=createSuperAdministrator( account, password);
	//结构体指针
	 SuperAdministrator*p=head;
	 //判断，当前节点的指针是否为空
	while (p->next!=NULL) 
	{
		p=p->next;
	}
	p->next=newNode;
} 
int main()
{
	FILE *fp;
	fp=fopen("D:\\学习材料\\软件实训\\电商管理系统\\超级管理员名单.txt","w+");
	if(fp==NULL)
	{
		printf("文件打开异常\n");
		exit(0); 
	}
	SuperAdministrator newNode;
	SuperAdministrator *head =superAdministratorCreateList();
	wandSuperAdministrator(head,202014,202014);
	SuperAdministrator*p=head->next;
//	while(p)
//	{
//		printf("%d\n",p->account);
//		printf("%d\n",p->password);
//		p=p->next;
//	}
//	p=head->next;
	while(p)
	{
		fwrite(p,sizeof(SuperAdministrator),1,fp);
		p=p->next;
	}
	fclose(fp);
	fp=fopen("D:\\学习材料\\软件实训\\电商管理系统\\超级管理员名单.txt","r+");
	if(fp==NULL)
	{
		printf("文件打开异常\n");
		exit(0); 
	}
	p=head->next;
	while(p)
	{
		fread(&newNode,sizeof(SuperAdministrator),1,fp);
		p=p->next;
	}
	printf("%d\n",newNode.account);
	printf("%d\n",newNode.password);
	
	fclose(fp);
}
