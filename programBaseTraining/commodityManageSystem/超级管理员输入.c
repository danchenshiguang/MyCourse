#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct superAdministrator//��������Ա�Ľṹ�� 
{
	int account;//��������Ա���˻� 	int 6λ�� 
	int password;//��������Ա������    int 6λ�� 
	struct superAdministrator *next;//ָ����һ����������Ա��ָ�� 
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
	//�ṹ��ָ��
	 SuperAdministrator*p=head;
	 //�жϣ���ǰ�ڵ��ָ���Ƿ�Ϊ��
	while (p->next!=NULL) 
	{
		p=p->next;
	}
	p->next=newNode;
} 
int main()
{
	FILE *fp;
	fp=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��������Ա����.txt","w+");
	if(fp==NULL)
	{
		printf("�ļ����쳣\n");
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
	fp=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��������Ա����.txt","r+");
	if(fp==NULL)
	{
		printf("�ļ����쳣\n");
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
