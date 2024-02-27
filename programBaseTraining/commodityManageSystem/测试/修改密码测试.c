#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  Max   1000
struct superAdministrator//超级管理员的结构体 
{
	int account;//超级管理员的账户 	int 6位数 
	int password;//超级管理员的密码    int 6位数 
	struct superAdministrator *next;//指向下一个超级管理员的指针 
};typedef  struct superAdministrator  SuperAdministrator;
/***************************
函数名： superAdministratorCreateList() 功能：创建超级管理员名单链表   头节点 
*********************************/
SuperAdministrator* superAdministratorCreateList()
{
	SuperAdministrator*headNode=(SuperAdministrator*)malloc(sizeof(SuperAdministrator));
	headNode->account=0;
	headNode->password=0;
	headNode->next=NULL;
 } 
  /*****************************
 函数名： createSuperAdministrator()   功能：创建一个超级管理员的链表单位 
 ********************************/
  SuperAdministrator*createSuperAdministrator(int account,)
  {
  	SuperAdministrator*headNode=(SuperAdministrator*)malloc(sizeof(SuperAdministrator));
  	
  }
