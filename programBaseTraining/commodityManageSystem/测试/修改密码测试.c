#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  Max   1000
struct superAdministrator//��������Ա�Ľṹ�� 
{
	int account;//��������Ա���˻� 	int 6λ�� 
	int password;//��������Ա������    int 6λ�� 
	struct superAdministrator *next;//ָ����һ����������Ա��ָ�� 
};typedef  struct superAdministrator  SuperAdministrator;
/***************************
�������� superAdministratorCreateList() ���ܣ�������������Ա��������   ͷ�ڵ� 
*********************************/
SuperAdministrator* superAdministratorCreateList()
{
	SuperAdministrator*headNode=(SuperAdministrator*)malloc(sizeof(SuperAdministrator));
	headNode->account=0;
	headNode->password=0;
	headNode->next=NULL;
 } 
  /*****************************
 �������� createSuperAdministrator()   ���ܣ�����һ����������Ա������λ 
 ********************************/
  SuperAdministrator*createSuperAdministrator(int account,)
  {
  	SuperAdministrator*headNode=(SuperAdministrator*)malloc(sizeof(SuperAdministrator));
  	
  }
