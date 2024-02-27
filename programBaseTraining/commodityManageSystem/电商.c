#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  Max   100

/******************************************************************************************
��Ʒ���� 
********************************************************************************************/ 
struct description
{
	char name[15];
	int code;//4λ 
	double price;//�ۼ�	
	double weight;
	int kind;//1-3
};typedef struct description Description;
struct productInfo
{
	Description description;
	int stock;//������� 
	double cost;//�ɱ�
	double profit; 
	int sales;
};typedef struct product ProductInfo;
struct productList
{
	struct productInfo productInfo;
	struct productList* next;	
};typedef struct productList ProductList;
struct item
{
	Description description;
	int quantity;//��������� 
};typedef struct item Item;
struct discountCoupon//�Ż�ȯ�ṹ�� 
{
	int kind;
	float discount;//�ۿ� 
};typedef  struct discountCoupon DiscountCoupon;
struct itemList
{
	Item item;
	struct itemList *next;
};typedef struct itemList ItemList;

/*****************************************************************************************
�˿ͱ��� 
*****************************************************************************************/ 

struct customer//�˿ͽṹ�� 
{
	ItemList shoppingCart;//
	char name[10];
	int ID;//6λ�� 
	int password;// 6λ�� 
	int gender;//1:female  2:male
	int isVIP;//1:no  2:yes
	double vipDiscount;
	long long telNum; 
	int salary;//1:<3000   2:3000-6000 3:6000-10000 4:10000-20000 5:>20000
	DiscountCoupon discountCoupon[10];//�Żݾ����������� 
};typedef struct customer Customer;

 

struct customerList		//	�����˿�����  ���� 
{
	Customer customer;
	struct customerList  *next;	
};typedef  struct customerList CustomerList;

/************************************************************************************************
��������Ա���� 
***********************************************************************************************/ 

struct superAdministrator//��������Ա�Ľṹ�� 
{
	int account;//��������Ա���˻� 	int 6λ�� 
	int password;//��������Ա������    int 6λ�� 
	struct superAdministrator *next;//ָ����һ����������Ա��ָ�� 
};typedef  struct superAdministrator  SuperAdministrator;

/*******************************************************************************************
����Ա����
***********************************************************************************************/ 
struct administrator//����Ա�Ľṹ�� 
{
	int account;//6λ�� 
	int password;//6λ�� 
	char name[10];
	int gender;//1��ʾ�У�2��ʾŮ 
	long long  telNum;//11λ 
	double salary;//3000��
	struct administrator * next;	
};typedef struct administrator  Administrator;
/********��������********************************/ 

SuperAdministrator* superAdministratorCreateList(); 
SuperAdministrator*createSuperAdministrator(int account,int password);
void  wandSuperAdministrator(SuperAdministrator*head,int account,int password);
void readFile_SuperAdministrator(SuperAdministrator* headSuperAdministrator,char *fileName);
void changeSuAdminPassword(SuperAdministrator*head);
void wandAdministrator(Administrator*head,int account,int password,	char *name,	int gender,	long long  telNum,double salary);
 void readFile_Administrator(Administrator* headAdministrator,char *fileName);
Administrator *administratorCreateList();
 Administrator   *createAdministrator();
 void  addAdministrator(Administrator*headAdministrator);
 void readFile_customer(CustomerList* headCustomer,char *fileName);
 CustomerList* creatHeadCustomer();
 CustomerList* createNode(Customer newCustomer);
 void setVIPDiscount(CustomerList*headCustomer);
 void setCouponDiscount(CustomerList*curCustomer);
 void wand(CustomerList *headCustomer,Customer newCustomer);
 void wandProduct();
/***********************************************************************************************************

��������Ա������������������������Ա���ֺ��� 

*************************************************************************************************************/


/***************************
�������� superAdministratorCreateList() ���ܣ�������������Ա��������   ͷ�ڵ� 
*********************************/
SuperAdministrator* superAdministratorCreateList()
{
	SuperAdministrator*headNode=(SuperAdministrator*)malloc(sizeof(SuperAdministrator));
	headNode->account=0;
	headNode->password=0;
	headNode->next=NULL;
	return headNode;
 } 
 
 /*****************************
 �������� createSuperAdministrator()   ���ܣ�����һ����������Ա������λ 
 ********************************/
  SuperAdministrator*createSuperAdministrator(int account,int password)
  {
  	SuperAdministrator*node=(SuperAdministrator*)malloc(sizeof(SuperAdministrator));
  	node->account=account;
  	node->password=password;
  	node->next=NULL;
  	return node;
  }
  
/****************************
������   wandSuperAdministrator()    ���ܣ����ļ��еĳ�������Ա����Ϣ����һ������λ 
*****************************/
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

/***************************************
readFile_SuperAdministrator()    ���ܣ����ļ��ж�ȡ��������Ա���� 
****************************/
void readFile_SuperAdministrator(SuperAdministrator* headSuperAdministrator,char *fileName)
{
	SuperAdministrator node;
	int account=0;
	int password=0;
	struct superAdministrator *next=NULL;
//	SuperAdministrator *p=headSuperAdministrator->next;

	FILE *fp;
	fp=fopen(fileName,"r+");
//	printf("echo\n");
	if(fp==NULL)
	{
		printf("Error\n");
		exit(0);
	}
	do
	{
//		fread(&account,sizeof(account),1,fp);
//		fread(&password,sizeof(password),1,fp);
//		fread(next,sizeof(next),1,fp);
		fread(&node,sizeof(SuperAdministrator),1,fp);
//		printf("echo:2\n");			
		wandSuperAdministrator(headSuperAdministrator,node.account,node.password);	
	}	while(feof(fp)==0);
//	while(p)
//	{
//		printf("%d",p->account);
//		printf("%d",p->password);
//		p=p->next;
//	}
//	p=headSuperAdministrator->next;	
}

/*******************************
 ��������  changeSuAdminPassword()  ���ܣ� �޸ĳ�������Ա����
************************************/
void changeSuAdminPassword(SuperAdministrator*head)
{
	readFile_SuperAdministrator(head,"D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��������Ա����.txt");
	SuperAdministrator *p=head->next;
	
//	while(p)
//	{
//		printf("%d",p->account);
//		printf("%d",p->password);
//		p=p->next;
//	}
//	p=head->next;
	FILE * fp;
	fp=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��������Ա����.txt","w+");
	if(fp==NULL)
	{
		printf("�ļ���ʧ��\n");
		exit(0);
	}
	int account=0;
	int password=0;
	while(1)
	{
		int isRight1=0;
		int newPassword1=0;
		int newPassword2=-1;
		printf("�����볬������Ա�˻�\n?");
		scanf("%d",&account);
		printf("�����볬������Ա����\n?");
		scanf("%d",&password);
		while(account!=p->account&&password!=p->password)
		{
			p=p->next;
			if(p==NULL)
			{
				printf("��֤ʧ�ܣ�������");
				isRight1=1;
				break;
			}
		}
		if(isRight1==1)
		{
			continue;
		}
		while(1)
		{
			printf("������������\n?");
			scanf("%d",&newPassword1);
			printf("���ٴ�����������\n?");
			scanf("%d",&newPassword2);
			if(newPassword1==newPassword2&&(newPassword1<1000000&&newPassword1>=100000))
			{
				p->password=newPassword1;
				printf("�޸�����ɹ�\n");
				break;
			}
			else
			{
				printf("�������������\n"); 
				printf("1>�˳�  2>����\n?"); 
				scanf("%d",&isRight1);
				if(isRight1==1)
				{
					break;
				}
			}			
		}
		break;	
	}
	p=head->next;
	while(p)
	{
		fwrite(p,sizeof(p),1,fp);
		p=p->next;
	}
	fclose(fp);
}



/***********************************************************************************************************



��������Ա��������������������Ա���ֺ��� 



*************************************************************************************************************/

/*********************************
wandSuperAdministrator()     ���ܣ� ���ļ��й���Ա����Ϣ����һ������λ 
**************************************/
void wandAdministrator(Administrator*head,int account,int password,	char *name,	int gender,	long long  telNum,double salary)
{
	Administrator* newNode=(Administrator*)malloc(sizeof(Administrator));
	newNode->account=account;
	newNode->password=password;
	strcpy(newNode->name,name);
	newNode->gender=gender;
	newNode->telNum=telNum;
	newNode->salary=salary;	
	newNode->next=NULL;
	
	Administrator* p=head;
	 //�жϣ���ǰ�ڵ��ָ���Ƿ�Ϊ��
	while (p->next!=NULL) 
	{
		p=p->next;
	}
	p->next=newNode;
 } 
/*************************************
readFile_Administrator()	���ܣ����ļ��ж�ȡ����Ա����
**********************************/
 void readFile_Administrator(Administrator* headAdministrator,char *fileName)
{
	Administrator node;
	int account=0;
	int password=0;
	char name[10];
	int gender=0;
	long long  telNum=0;//11λ 
	double salary;//3000��
	struct administator * next=NULL;
		
	
	FILE *fp;
	if((fp=fopen(fileName,"r"))==NULL)
	{
		printf("Error\n");
		exit(0);
	}
		do
		{
//			fread(&account,sizeof(account),1,fp);
//			fread(&password,sizeof(password),1,fp);
//			fread(name,sizeof(name),1,fp);
//			fread(&gender,sizeof(gender),1,fp);	
//			fread(&telNum,sizeof(telNum),1,fp);				
//			fread(&salary,sizeof(salary),1,fp);
//			fread(next,sizeof(next),1,fp);
			fread(&node,sizeof(Administrator),1,fp);											
			wandAdministrator(headAdministrator,node.account,node.password,node.name,node.gender,node.telNum,node.salary);
		}	while(!feof(fp));
}

/*******************************
��������administratorCreateList() ���ܣ���������Ա��������    ͷ�ڵ� 
****************************/
Administrator *administratorCreateList()
{
	Administrator *headNode=(Administrator *) malloc(sizeof(Administrator));
	headNode->account=0;
	headNode->password=0;
//	headNode->name=NULL;
	headNode->gender=0;
	headNode->telNum=0;
	headNode->salary=0;
	headNode->next=NULL;
	return headNode;
}
/*******************************
�������� createAdministrator()   ���ܣ� ����һ������Ա������λ 
************************************/
Administrator   *createAdministrator()
{
	int account;
	int password;
	char name[10];
	int gender;
	long long telNum;
	double salary;
	int isFull=0;
	Administrator *node=(Administrator *) malloc(sizeof(Administrator));
	while(1)
	{
		while(1)//����˻� 
		{
			int n=0;
			int isSix=0;
			printf("������Ҫ��ӹ���Ա���˻���\n");
			printf("?") ;
			scanf("%d",&account);
			printf("\n���������:%d\n",account);
			n=account;
			while(n!=0)//�ж������Ƿ�Ϊ��λ���� 
			{
				n/=10;
				isSix++;
			}
			if(isSix!=6)
			{
				int is=-1; 
				printf("�������������\n");
				printf("�˳��밴0,������1\n");
				scanf("%d",&is);
				if(is==1)
				{
					continue;
				}
				else if (is!=1) 
				{
					break;
				}
			}
			isFull++;
			break;	
		}
		while(1)//������� 
		{
			int n=0;
			int isSix=0;	
			printf("������Ҫ��ӹ���Ա�����룺\n");
			printf("?") ;
			scanf("%d",&password);
			printf("\n�������������:%d\n",password);
			n=password;
			while(n!=0)//�ж������Ƿ�Ϊ��λ���� 
			{
				n/=10;
				isSix++;
			}
			if(isSix!=6)
			{
				int is=-1; 
				printf("�������������\n");
				printf("�˳��밴0,������1\n");
				scanf("%d",&is);
				if(is==1)
				{
					continue;
				}
				else if(is!=1) 
				{
					break;
				}
			}
			isFull++;			
			break;	
		}
		while(1)//��ӹ���Ա������ 
		{	
			printf("������Ҫ��ӹ���Ա������:\n");
			printf("?") ;
			scanf("%s",name);
			printf("\n�������������:%s\n",name);
			int length =strlen(name);
			//�ж�����������Ƿ�Ϸ� 
			if(length<1)
			{
				int is=-1; 
				printf("�����������������\n");
				printf("�˳��밴0,������1\n");
				scanf("%d",&is);
				if(is==1)
				{
					continue;
				}
				else if(is!=1) 
				{
					break;
				}
			}
			isFull++;			
			break;	
		}
		while(1)//��ӹ���Ա���Ա� 
		{	
			printf("������Ҫ��ӹ���Ա���Ա�\n1��2Ů");
			printf("?");
			scanf("%d",&gender);
			setbuf(stdin,NULL);
			//�ж�������Ա��Ƿ�Ϸ� 
			if(gender==1)
			{
				printf("������Ĺ���Ա�Ա�Ϊ��\n");
				isFull++;					
				break;
			}
			else if(gender==2)
			{
				printf("������Ĺ���Ա�Ա�ΪŮ\n");
				isFull++;				
				break;
			}
			else
			{
				printf("�������������");
				continue;
			}	

			break;	
		}
		//��ӹ���Ա�ĵ绰���� 
			while(1)
		{
			long long n=0;
			int isEleven=0;
			printf("������Ҫ��ӹ���Ա�ĵ绰���룺\n");
			printf("?") ;
			scanf("%lld",&telNum);
			printf("\n������ĵ绰������:%lld\n",telNum);
			n=telNum;
			while(n!=0)//�ж������Ƿ�Ϊʮһλ���� 
			{
				n/=10;
				isEleven++;
			}
			if(isEleven!=11)
			{
				int is=-1; 
				printf("�������������\n");
				printf("�˳��밴0,������1\n");
				scanf("%d",&is);
				if(is==1)
				{
					continue;
				}
				else if(is!=1) 
				{
					break;
				}
			}
			isFull++;			
			break;	
		}
		//��ӹ���Ա��нˮ 
			while(1)
		{
			printf("������Ҫ��ӹ���Ա��нˮ\n");
			printf("?") ;
			scanf("%lf",&salary);
			printf("\n�������нˮ��:%lf\n",salary);
			if(salary<=3000)
			{
				int is;
				printf("����нˮ���٣�������\n");
				printf("�˳��밴0,������1\n");
				scanf("%d",&is);
				if(is==1)
				{
					continue;
				}
				else if (is!=1) 
				{
					break;
				}
			}
			isFull++;			
			break;
		}
		if(isFull==6)
		{
			break;
		}
		else
		{
			printf("������Ϣ����Ϊ�գ�������\n");		
		}	
	}
	//Ϊ����ĸ��������ֵ 
	node->account=account;
	node->password=password;
	node->gender=gender;
	strcpy(node->name,name);
	node->salary=salary;				
	node->telNum=telNum;
	node->next=NULL;	
	return node;						
	
}
/********************************************************
������changeAdiministratorInfo()   ���ܣ���������Ա��¼���棬�޸Ĺ���Ա����Ϣ 
*********************************************************/ 
void changeAdiministratorInfo(Administrator* head)
{
	readFile_Administrator(head,"D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\����Ա����.txt");
	FILE *fp;
	int account=0;
	int choice=0;
	int isContinue=0;
	fp=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\����Ա����.txt","w+");
	if(fp==NULL)
	{
		printf("�ļ���ʧ��\n");
		exit(0); 
	}
	while(1)
	{
		Administrator* p=head->next;
		printf("����������Ҫ�޸���Ϣ�Ĺ���Ա�˻�\n?");
		scanf("%d",&account);
		if(account<1000000&&account>99999)
		{
			printf("����Ҫ�޸��˻�Ϊ%d�Ĺ���Ա��Ϣ\n",account);
		}
		else
		{
			printf("������������������\n");
			continue;
		}
		if(head->next==NULL)//�ж������Ƿ�Ϊ�� 
		{
			printf("����Ϊ��\n");
		}
		while(p)
		{
			if(p->account==account)
			{
				int gender=0;
				long long telNum;
				double salary;
				while(1)
				{
					int wrongEnter=0; 
					printf("����������ѡ��\n");
					printf("1>�Ա�\n");	
					printf("2>�绰\n");	
					printf("3>нˮ\n");
					printf("4>�˳�\n?");
					scanf("%d",&choice);
					switch(choice)
					{
						case 1:
						{
							printf("�������µĹ���Ա�Ա�");
							scanf("%d",&gender);
							if(gender==1&&gender==2)
							{
								p->gender=gender;
								printf("�޸ĳɹ��������ص�������\n");
							}
							else
							{
								printf("������������������");
								wrongEnter=1; 
							}
							break;							
						}
						case 2:
						{
							printf("�������µĹ���Ա�绰");
							scanf("%lld",&telNum);
							if(telNum<100000000000&&telNum>9999999999)
							{
								p->telNum=telNum;
								printf("�޸ĳɹ��������ص�������\n");								
							}
							else
							{
								printf("������������������");
								wrongEnter=1; 								 
							}
							break;							
						}
						case 3:
						{
							printf("�������µĹ���Աнˮ");
							printf("�޸ĳɹ��������ص�������\n");							
							scanf("%lf",&salary);
							if(salary>=3000.0)
							{
								p->salary=salary;
							}
							else
							{
								printf("�������нˮ���٣�������"); 
								wrongEnter=1; 								
							}
							break;							
						}
						default : break;													
					}
					if(choice==4)
					{
						break;
					}
					if(wrongEnter==0)	
					{
						break;
					}
					else if (wrongEnter==1)
					{
						continue;
					}				
				}																						
				break;
			}
			p=p->next;	
		}
		if(p==NULL)
			{
				printf("����Ҫ�޸��˻�Ϊ%d�Ĺ���Ա������\n",account);
				printf("�Ƿ�����\n1>����  2>�˳�\n?");
				scanf("%d",&isContinue);
				if(isContinue==1)
				{
					continue;
				}
				else if(isContinue==2)
				{
					break;
				}
				if(isContinue!=1&&isContinue!=2)
				{
					printf("�����������󣬽��˳�\n");
					break;
				}
			}
		p=head->next;
		while(p)
		{
			fwrite(p,sizeof(p),1,fp);
			p=p->next;
		 }
		 break;	 													
	}
	fclose(fp);
}
/******************************************
���� addAdministrator()   ���ܣ���ӹ���Ա������λ����������Ա��Ϣ�����ļ� 
*******************************************/ 
void  addAdministrator(Administrator*headAdministrator)//��ӹ���Ա���� 
{
	readFile_Administrator(headAdministrator,"D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\����Ա����.txt");
	FILE *fp;
	fp=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\����Ա����.txt","a+") ;
	if(fp==NULL)
	{
		printf("�ļ���ʧ��\n");
		exit(0); 
	}
	Administrator* newNode;
	int isContinue=-1; 
	//�жϹ���Ա����Ƿ���� 
	while(1)
	{
			int isRepeated=0;
		
			printf("���ڿ�ʼ����Ա�����\n");
			newNode=createAdministrator();	
			Administrator* p=headAdministrator->next;
			//���������鿴�Ƿ�����ͬ����Ա
			while(p)
			{

				if(p->account==newNode->account)
				{
					isRepeated++;
				}
				if(p->password==newNode->password)
				{
					isRepeated++;
				}
				if(p->telNum==newNode->telNum)
				{
					isRepeated++;
				}
				if(isRepeated!=0)
				{
					printf("������Ĺ���Ա��Ϣ�ظ��ˣ�\n1>����2>�˳�  ����������������\n?");
					scanf("%d",&isContinue);
//					printf("%d",isRepeated);
					break;	
				}
				p=p->next;					
			}
			if(isContinue==2)
			{
				break;
			}
			if(isRepeated!=0)
			{
				continue;
			}
			isContinue=-1;			

		//���µ�����λ�������� 
//		while(p->next!=NULL)
//		{
//			p = p->next;
//		}
//		p->next=newNode;
//		fseek(fp,0,SEEK_END); 
//		fwrite(newNode,sizeof(newNode.account),1,fp);
//		fwrite(newNode,sizeof(newNode.password),1,fp);
//		fwrite(newNode,sizeof(newNode.name),1,fp);
//		fwrite(newNode,sizeof(newNode.gender),1,fp);
//		fwrite(newNode,sizeof(newNode.telNum),1,fp);
//		fwrite(newNode,sizeof(newNode.salary),1,fp);
		fwrite(newNode,sizeof(newNode),1,fp);
		printf("�����ɣ��Ƿ������ӹ���Ա\n");
		printf("1>����  2>�˳�\n?");
		scanf("%d",&isContinue);
		if(isContinue==1)
		{
			continue;
		}
		else if(isContinue==2)
		{
			break;
		}
		else if(isContinue!=1&&isContinue!=2)
		{
			break;
		} 
	}
	fclose(fp);	
}
/**********************************************************
removeAdministrator()  ���ܣ���������Աɾ������Ա��Ϣ 
************************************************************/
void  removeAdministrator(Administrator*headAdministrator)
{
	readFile_Administrator(headAdministrator,"D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\����Ա����.txt");
	FILE *fp;
	fp=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\����Ա����.txt","w+") ;
	int account=0;
	int account1=-1;
	int isContinue=0;
	int isContinue1=0;	
	if(fp==NULL)
	{
		printf("�ļ���ʧ��\n");
		exit(0); 
	}
	while(1)
	{
		Administrator* p=headAdministrator->next;
		Administrator*t=headAdministrator;
		printf("����������Ҫɾ���Ĺ���Ա���˻�\n?");
		scanf("%d",&account);
		printf("���ٴ���������Ҫɾ���Ĺ���Ա���˻�\n?");
		scanf("%d",&account1);
		if(account==account1&&(account<1000000&&account>99999))
		{
			printf("����Ҫɾ���Ĺ���Ա�˻�Ϊ%d\n",account);
		}
		else
		{
			printf("������������1>�˳�  ���������������\n��");
			scanf("%d",&isContinue1);
			if(isContinue1==1)
			{
				break;
			}
			else
			{
				continue;
			}			
		}
		if(headAdministrator->next==NULL)//�ж������Ƿ�Ϊ�� 
		{
			printf("����Ϊ��\n");
		}
		while(p)
		{
			if(p->account==account)
			{
				t->next=p->next;
				printf("���ɹ�ɾ���˻�Ϊ%d�Ĺ���Ա\n",p->account);
				free(p);
				p=NULL;
				break;
			}
			t=p;
			p=p->next;
		}
		
		if(p==NULL&&t==NULL)
		{
			printf("�����꣬����Ҫɾ���Ĺ���Ա�˻�������\n");
			printf("�Ƿ�����\n1>����  2>�˳�   ���������������\n?");
			scanf("%d",&isContinue);
			if(isContinue==1)
			{
				continue;
			}
			else if(isContinue==2)
			{
				break;
			}
			if(isContinue!=1&&isContinue!=2)
			{
				printf("�����������󣬽��˳�\n");
				break;
			}
		}
		p=headAdministrator->next;
		while(p)
		{
			fwrite(p,sizeof(p),1,fp);
			p=p->next;
		 }
		break; 		
	}

	 fclose(fp);
			
}
/*****************************************************
showAdministrator()      ���ܣ���������Ա�鿴����Ա��Ϣ 
*******************************************************/
void showAdministrator()
{
	FILE *fp;
	fp=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\����Ա����.txt", "r+");
	Administrator *Admin;
	if(fp==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
     printf("www\n"); 
    //fread(&PL,sizeof(ProductList),1,test1); 
    if(fgetc(fp)!=EOF)   
    { 
   	  fseek(fp,0,SEEK_SET);
   	  fread(&Admin,sizeof(Administrator),1,fp); 
   	  printf("%d",Admin.account)
   	  while (feof(fp)==0)//�ж��Ƿ���� 
   	  {
   	  	printf("�˻���%d\n���룺%d\n������%s\n�Ա�%d\n�绰��%lld\nнˮ��%lf\n",Admin->account,Admin->password,Admin->name,Admin->gender,Admin->telNum,Admin->salary);
   	  	printf("***************************************************************************\n");
   	  	fread(&Admin,sizeof(Administrator),1,fp); 
	  }
	  printf("\n..........��ѯ���...............\n");	  
    }
    else
    {
    	printf("����Ա����Ϊ�գ�����\n\n");
	}
	
}

/***********************************************************************************************************



��������Ա�����������������˿Ͳ��ֺ��� 



*************************************************************************************************************/
void printList(CustomerList* headCustomer)
{
	CustomerList* curPtr=headCustomer;
		puts("The list is");
		curPtr=curPtr->next;
		while(curPtr!=NULL)
		{
			
			printf("%d-->",curPtr->customer.ID);
			curPtr=curPtr->next;
		}
		puts("NULL\n");
}
/***************************************************
CustomerList* creatHeadCustomer()     ����:Ϊ�˿� ���� ����ͷ�ڵ� 
*******************************************************/
CustomerList* creatHeadCustomer()//ͷ�ڵ� ָ�� 
{
	CustomerList* headCustomer=(CustomerList*)malloc(sizeof(CustomerList));
	headCustomer->customer.ID=0;
	headCustomer->next=NULL;
	return headCustomer;
}
CustomerList* createNode(Customer newCustomer)
{
	CustomerList* newPtr=(CustomerList*)malloc(sizeof(CustomerList));
	newPtr->customer=newCustomer;
	return newPtr;
}
/*****************************************
��������void readFile_customer(CustomerList* headCustomer,char *fileName)  ���ܣ����ļ��ж�ȡ���˿���Ϣ 
********************************************/
void readFile_customer(CustomerList* headCustomer,char *fileName)
{
	Customer newCustomer;
	FILE *fp;char ch;
	if((fp=fopen(fileName,"r"))==NULL)
	{
		printf("Error\n");
		exit(0);
	}
	ch=fgetc(fp);
		if(ch==EOF)
		{
			return;
		}
		while(!feof(fp))
		{
			fread(&newCustomer,sizeof(Customer),1,fp);
			wand(headCustomer,newCustomer);
		}	
		fclose(fp);
		printList(headCustomer);
}
/*****************************************
��������void wand(CustomerList *headCustomer,Customer newCustomer)  ���ܣ����ļ��ж�ȡ���Ĺ˿���Ϣ�������� 
********************************************/
void wand(CustomerList *headCustomer,Customer newCustomer)
{
	printf("����wand\n");
	
	CustomerList* newPtr=createNode(newCustomer);
	printf("wand_get: %6d\n",newPtr->customer.ID);//ok
	CustomerList* curPtr=headCustomer;
	CustomerList* previousPtr=NULL;
	while(curPtr!=NULL)
	{
		printf("����ѭ��\n");
		
		previousPtr=curPtr;	
		printf("echo:1\n");
		curPtr=curPtr->next;	
		printf("echo:2\n");
	}

				previousPtr->next=newPtr;//ע�� ���ӵķ���ͬ 
				printf("echo:3\n");
			newPtr->next=curPtr;
			printf("echo:4\n");	
			printf("%6d\n",newPtr->customer.ID);
			printf("%6d\n",previousPtr->next->customer.ID);

	printf("Done_wand\n");	
}
/********************************
��������setVIPDiscount ����  ���ܣ���������Ա��¼��������Ա���棬�޸Ļ�Ա���е��ۿ� 
*********************************/ 
void setVIPDiscount(CustomerList*headCustomer)
{
	 readFile_customer( headCustomer,"D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\customerList.txt");
	 CustomerList *p=headCustomer->next;
	 int choice=-1;
	 double disCount=1.0;
	 FILE *fp;
	 fp=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\customerList.txt","w+");
	 if(fp==NULL)
	 {
	 	printf("�ļ���ʧ��");
	 	exit(0);
	 }
	 while(1)
	 {
	 	printf("�Ƿ��޸Ļ�Ա���е��ۿ�");
		printf("1>ȷ��  2>�˳�  ���������������\n?");
		scanf("%d",&choice);
		if(choice==1)
		{
			printf("�������Ա�ۿ�\n?");
			scanf("%lf",&disCount);
			if(disCount<=0&&disCount>1)
			{
				printf("������������������");
				continue;
			}			
		 	while(p)	
		 	{
		 		if(p->customer.isVIP==2)
		 		{
		 			p->customer.vipDiscount=disCount;
				 }
				 p=p->next;
			 }
		 	 printf("���ѳɹ�����޸�,������������\n");
		}
		else if(choice==2)
		{
			break;
		}
		else if(choice!=1&&choice!=2)
		{
			printf("����\n");
			continue; 
		}
		break;
	 }
 	p=headCustomer->next;
	 while(p)
	 {
	 	fwrite(p,sizeof(p),1,fp);
	 	p->next;
	 }

	 fclose(fp);
} 

/********************************
��������setCouponDiscount ����  ���ܣ���������Ա��¼��������Ա���棬�޸Ĺ˿�ʹ���Ż�ȯ���е��ۿ� 
*********************************/ 
void setCouponDiscount(CustomerList*curCustomer)
{
	 readFile_customer( curCustomer,"D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\customerList.txt");
	 CustomerList *p=curCustomer->next;
	 int choice=-1;
	 float couponDiscount=1;
	 int kind=0;
	 FILE *fp;
	 fp=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\customerList.txt","w+");
	 if(fp==NULL)
	 {
	 	printf("�ļ���ʧ��");
	 	exit(0);
	 }
	 while(1)
	 {
	 	printf("�Ƿ��޸��Ż�ȯ���е��ۿ�");
		printf("1>ȷ��  2>�˳�\n ����������������?");
		scanf("%d",&choice);
		if(choice==1)
		{
			printf("��������Ҫ�޸��ۿ۵��Ż�ȯ����");
			scanf("%d",&kind);
			if(kind!=1&&kind!=2&&kind!=3)
			{
				printf("������������������");
				continue;
			}			
			printf("�������Ż�ȯ�ۿ�\n?");
			scanf("%f",&couponDiscount);
			if(couponDiscount<=0&&couponDiscount>1)
			{
				printf("������������������");
				continue;
			}
		 	while(p)	
		 	{
		 		int i=0;
		 		int hasdiscountCoupon=0;
		 		for(i;i<10;i++)
		 		{
		 			if(p->customer.discountCoupon[i].kind!=0)
		 			{
		 				hasdiscountCoupon++;
					 }
				 }
		 		if(hasdiscountCoupon!=0)
		 		{
			 		for(i;i<10;i++)
			 		{
			 			if(p->customer.discountCoupon[i].kind=kind)
			 			{
			 				p->customer.discountCoupon[i].discount=couponDiscount;
						 }
					 }		 			
		 			
				 }
				 p=p->next;
			 }
			 printf("���ѳɹ�����޸�,������������\n");
		}
		else if(choice==2)
		{
			break;
		}
		else if(choice!=1&&choice!=2)
		{
			printf("����\n");
			continue; 
		}
		break;
	 }
 	p=curCustomer->next;
	 while(p)
	 {
	 	fwrite(p,sizeof(p),1,fp);
	 	p->next;
	 }
	 fclose(fp);
	
}
/**************************************
showCustomerList()       ���ܣ���ѯ�˿���Ϣ 
******************************************/
void showCustomerList()
{
	FILE *fp;
	fp=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\customerList.txt", "r+");
	CustomerList curCustomer;
	if(fp==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
    //fread(&PL,sizeof(ProductList),1,test1); 
    if(fgetc(fp)!=EOF)   
    { 
   	  fseek(fp,0,SEEK_SET);
   	  fread(&curCustomer,sizeof(CustomerList),1,fp); 
   	  while (feof(fp)==0)//�ж��Ƿ���� 
   	  {
   	  	int i=0;
   	  	int a=0;//������¼�˿��Ż�ȯ���� 
   	  	int b=0;
   	  	int c=0;   	  	
   	  	printf("ID��%d\n������%s\n�Ա�%d\n�绰��%lld\nнˮ��%lf\n�Ƿ�VIP��%d\n",curCustomer.customer.ID,curCustomer.customer.name,curCustomer.customer.gender,curCustomer.customer.telNum,curCustomer.customer.salary,curCustomer.customer.isVIP,curCustomer.customer.vipDiscount);
   	  	for(i=0;i<10;i++)
   	  	{

   	  		if(curCustomer.customer.discountCoupon[i].kind==1)
   	  		{
   	  			a++;
			 }
			 if(curCustomer.customer.discountCoupon[i].kind==2)
			 {
			 	b++;
			 }
			 if(curCustomer.customer.discountCoupon[i].kind==3)
			 {
			 	c++;
			 }			 	  		
		 }
   	  		printf("���˿ͳ��е��Ż�ȯΪ\n");
   	  		printf("1...........%d��",a);
   	  		printf("2...........%d��",b); 
   	  		printf("3...........%d��",c); 				 				  		 
   	  	printf("***************************************************************************\n");
   	  	fread(&curCustomer,sizeof(CustomerList),1,fp); 
	  }
	  printf("\n..........��ѯ���...............\n");
    }
    else
    {
    	printf("�˿�����Ϊ�գ�����\n\n");
	}
	
}



/*****************************************************************************************************************



��������Ա����������Ʒ���溯�� 



*****************************************************************************************************************/
/****************************
ProductList  suCreatProduct()  ���ܣ���������Ա������Ʒ 
**************************************/
ProductList  suCreatProduct()
{
	int i=0;
	int k=0;
	int u=0;
	ProductList  creatProduct;
	char name[15];
	int code,kind,stock;
	double price,weight,cost,profit;
	do 
	{
	  u=0,k=0;
	  printf("���Կո�ָ�������������Ʒ��ţ�4λ���ͣ�����Ʒ���ࣨ1�������2�����߹���3������ʳ������Ʒ��棨���ͣ�\n");
	 // fflush(stdin);
	  i=scanf("%d%d%d",&code,&kind,&stock);   //�������� 
	  //fflush(stdin);
	  setbuf(stdin, NULL);
	  if((i!=3)||(code<=999)||(code>9999)||(kind!=1&&kind!=2&&kind!=3))//�ж������Ƿ���ȷ 
	  {
	  	
	  	do    
	  	{
	  	  setbuf(stdin, NULL);
		  if(u==0)
		  {	
		  printf("�����������1�������룬����2�˳�\n");
		  u++;	  
		  }   

		  //printf("%d\n",k);
		  //fflush(stdin);
          scanf("%d",&k);
          //setbuf(stdin, NULL);
          //printf("%d\n",i);

	  	  if(k==1||k==2)    //ֱ���û�������ȷΪֹ 
	  	  {
	  	  	break;	
		  }
	  	}while(1);     //ֱ���û�������ȷΪֹ 
	  	if(k==2)
	  	{
	  		creatProduct.productInfo.description.code=0;
	  		return creatProduct ;     //�˳�����������NULL 
		}
      }
    }while(k==1);
    do 
	{
		k=0,u=0;
	 printf("���Կո�ָ�����������۸�˫���ȸ���������������˫���ȸ������� ����(˫���ȸ�����)\n");
	  i=scanf("%lf%lf%lf",&price,&weight,&cost);   //�������� 
	  setbuf(stdin, NULL);
	  if((i!=3)||price<0||weight<0||(cost<0||price<cost))//�ж������Ƿ���ȷ 
	  {
	  	do    
	  	{
		  if(u==0)
		  {	
		  printf("�������(ԭ��1.�����ʽ����\n 2.���۴����ۼ�)��\n����1�������룬����2�˳�\n");
		  u++;	  
		  }   
		  //printf("%d\n",i);
		  //setbuf(stdin, NULL);
          scanf("%d",&k);
          setbuf(stdin, NULL);
	  	  if(k==1||k==2)    //ֱ���û�������ȷΪֹ 
	  	  {
	  	  	break;	
		  }
	  	}while(1);     //ֱ���û�������ȷΪֹ 
	  	if(k==2)
	  	{
	  		creatProduct.productInfo.description.code=0;
	  		return creatProduct ;     //�˳�����������NULL 
		}
      }
    }while(k==1);
    printf("��������Ʒ����\n");
    fgets( creatProduct.productInfo.description.name, 15, stdin);
    setbuf(stdin, NULL);
    //profit=price-cost;����Ա��Ȩ�޸ĳɱ� 
    creatProduct.productInfo.description.code=code;
    creatProduct.productInfo.stock=stock;
    creatProduct.productInfo.description.kind=kind;
   creatProduct.productInfo.description.price=price;
    creatProduct.productInfo.description.weight=weight;
    creatProduct.productInfo.cost=cost;          //����Ա��Ȩ�޸ĳɱ� 
    creatProduct.productInfo.profit=price-cost;   //����Ա��Ȩ�޸ĳɱ� 
    creatProduct.productInfo.sales=0;
	return creatProduct;
}
/********************************************
wandProduct()    ���ܣ���������Ա����������Ʒ��ӵ��ļ��� 
************************************************/ 
void wandProduct()
{
	ProductList PL;
//	ProductList * S;
//	S=head;
//	ProductList * M=(ProductList *)malloc(sizeof(ProductList));
//	S=M;
    //printf("%d",head->productInfo.description.code);
	PL=suCreatProduct();
//	PL.next=NULL;0.
//	//FILE * Pr=fopen();//���ļ�
//	fread(M,sizeof(ProductList),1,Pr); //���ļ��ж�ȡ�ṹ��; 
	if(PL.productInfo.description.code!=0)
	{
//	  for(;head!=NULL;)
//	  {
//	  	   printf("%d\n",head->productInfo.description.code);
//	       head=head->next;   
//	  }
//	  head->next=&PL;   //����������ĩβ�� 
//	  for(;S!=NULL;S=S->next)
//	  {
		  FILE * test1=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��Ʒ����.txt","a+");
		  fwrite(&PL,sizeof(ProductList),1,test1);
		  fclose(test1);
//	  }
	      printf("��ӳɹ�\n");
    }
    else
    {
    	printf("���ʧ�ܣ�����\n");
	}
	
		 
}
/****************************************************
showsProduct()    ���ܣ���������Ա�鿴��Ʒ��Ϣ 
****************************************************/
void showsProduct()
{
	printf("aaa\n");
	ProductList PL;
	FILE * test1=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��Ʒ����.txt", "r+");
	if(test1==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
    //fread(&PL,sizeof(ProductList),1,test1); 
    if(fgetc(test1)!=EOF)   
    { 
   	  fseek(test1,0,SEEK_SET);
   	  fread(&PL,sizeof(ProductList),1,test1); 
   	  while (feof(test1)==0)//�ж��Ƿ���� 
   	  {
   	  	printf("��Ʒ��ţ�%d\n��Ʒ���ƣ�%s\n��Ʒ���ͣ�%d\n��Ʒ������%lf\n��Ʒ�ۼۣ�%lf\n��Ʒ�ɱ���%lf\n��Ʒ����%lf\n��Ʒ��棺%d\n",PL.productInfo.description.code,PL.productInfo.description.name,PL.productInfo.description.kind,PL.productInfo.description.weight,PL.productInfo.description.price,PL.productInfo.cost,PL.productInfo.profit,PL.productInfo.stock);
   	  	printf("***************************************************************************\n");
   	  	fread(&PL,sizeof(ProductList),1,test1); 
	  }
	  printf("\n..........��ѯ���...............\n");	  
    }
    else
    {
    	printf("��Ʒ���Ϊ�գ�����\n\n");
	}
	
}
/******************************************
suSetProduct()     ���ܣ���������Ա�޸���Ʒ��Ϣ 
************************************************/ 
void suSetProduct()
{
	ProductList PL,new1;
	int code,j=0;
	printf("��������Ҫ�޸ĵ���Ʒ���\n");
	scanf("%d",&code);
	FILE * test1;
	test1=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��Ʒ����.txt","r+");//�򿪴������Ա��Ϣ���ļ�
	if(test1==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
    fread(&PL,sizeof(ProductList),1,test1); //���ļ��ж�ȡ�ṹ��; 
    printf("%d\n",PL.productInfo.description.code);
   
	for(;feof(test1)==0;)
	{
		if(PL.productInfo.description.code==code)
		{
			new1=suCreatProduct();
			if(new1.productInfo.description.code!=0)
			{
				fseek(test1,-sizeof(ProductList),SEEK_CUR);
				fwrite(&new1,sizeof(ProductList),1,test1);
				fclose(test1);
				printf("�޸ĳɹ�������\n");
			}
			else
			{
				printf("�޸�ʧ�ܣ�����\n");
			}
			j++;
		}
		fread(&PL,sizeof(ProductList),1,test1);
	}
	if(PL.productInfo.description.code==code)
		{
			new1=suCreatProduct();
			if(new1.productInfo.description.code!=0)
			{
				fseek(test1,-sizeof(ProductList),SEEK_CUR);
				fwrite(&new1,sizeof(ProductList),1,test1);
				fclose(test1);
				printf("�޸ĳɹ�������\n");
			}
			else
			{
				printf("�޸�ʧ�ܣ�����\n");
			}
			j++;
		}
	if(j==0)
	{
	  printf("����Ʒ�����ڣ�����\n");
    }
}
/***********************************************************
deleteProduct()     ���ܣ���������Աɾ����Ʒ 
***********************************************************/
void deleteProduct()
{
  ProductList p1;
  int code,i=0;
  FILE * fp = fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��Ʒ����.txt", "r+");
  FILE * fp1 = fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\linshi.txt", "w+");//��д�½�һ����ʱ�ļ�
  if(fp==NULL||fp1==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
  if(fgetc(fp)!=EOF)   
   {
   	fseek(fp,0,SEEK_SET);
	fread(&p1,sizeof(ProductList),1,fp);
    printf("��������Ҫɾ����Ʒ�ı��\n");	
    scanf("%d",&code);
    while (feof(fp)==0)//�ж��Ƿ���� 
    {
        if (p1.productInfo.description.code==code)//����Ҫɾ��������,��д�롣
        {
      	    printf("ɾ���ɹ�������\n");
            i++;
        }
        else
        {
      	  fwrite(&p1, sizeof(ProductList), 1, fp1);
	    }
        fread(&p1,sizeof(ProductList),1,fp);
    }
//      if (p1.productInfo.description.code==code)//����Ҫɾ��������,��д�롣��ֹ©�����һ�� 
//      {
//        printf("ɾ���ɹ�������\n");
//        i++;
//      }
//      else
//      {
//         fwrite(&p1, sizeof(ProductList), 1, fp1);
//	  }
    if(i==0)
   {
  	 printf("����Ʒ�����ڣ�����\n");
   }
  }
  else
  {
  	printf("��ǰ��Ʒ���Ϊ��!!!\n");
  }
    fclose(fp);
    fclose(fp1);
    remove("��Ʒ����.txt");                
    rename("linshi.txt", "test1.txt");
}
/**********************************************************



---------------------------��¼�������沿�� 



**************************************************************/
/***************************************
showInfo()    ���ܣ���ѯ�û�������Ա����Ʒ��Ϣ 
****************************************/ 
void  showInfo()
{
	while(1)
	{
		int choice=-1;
		printf("����������ѡ��\n");
		printf("1>��ѯ����Ա��Ϣ\n2>��ѯ�˿���Ϣ\n3>��ѯ��Ʒ��Ϣ\n4>�˳�\n��������������\n");
		printf("******************************\n?");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			{
				showAdministrator();
				break;
			}
			case 2:
			{
				showCustomerList();
				break;
			}
			case 3:
			{
				showsProduct();
				break;
			}
			default: 
			printf("��������������������\n");
			break;			
		}
		if(choice==4)
		{
			break;
		}
		
	}
}
/***************************************************
�������� LoginSuperAdministrator  ���ܣ���������Ա��¼ 
*******************************************************/
int LoginSuperAdministrator()
{
	FILE * ad; 
	int a=0;   //�����ж����� 
	int account;
	int password;
//	char string[Max];    //�����û����� 
//	char suAccount[Max];
//	char suPassword[Max];
//	int view1,view2;//�洢�ַ���ת�����int 
	SuperAdministrator admini;
	int i=0,j=0;
	printf("�����볬������Ա�˺�\n");
	scanf("%d",&account);
	setbuf(stdin, NULL);
	ad=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��������Ա����.txt","r+");//�򿪴������Ա��Ϣ���ļ�
	if(ad==NULL)
     {
      printf("���ļ�ʧ��\n");
      exit(0);
     }
     fread(&admini,sizeof(SuperAdministrator),1,ad);
	for(;feof(ad)==0;)
	{
//	    fgets(string,sizeof(string),ad);
//	    for(i=0;i<Max;i++)//���ַ����е���Ϣ��� 
//	    {
//	    	suAccount[i]='\0';
//	    	suPassword[i]='\0';
//		 }
//		 for(i=0,j=0;string[i]!='_';i++,j++)//��ʼ�ָ��ַ��� 
//		 {
//		 	suAccount[i]=string[i];
//		 }
//		 i++;
//		 for(j=0;string[i]!='_';i++,j++)
//		 {
//		 	suPassword[j]=string[i];
//		 }
//		 view1=atoi(suAccount);
//		 view2=atoi(suPassword);
		//printf("!!!\n");
		while(admini.account==account)
		{
			fclose(ad);     //�ҵ���Ӧ����Ա���ر��ļ� 
			printf("����������\n");
			scanf("%d",&password);
			setbuf(stdin, NULL);
			int i=0,k=0;    //���ڴ����ж���Ϣ 
			char c;
			if(admini.password==password)
			{
				printf("��ӭ���ĳ�������Ա��¼\n");
				
				while(1)
				{
					printf("******************************************************************\n");
					printf("1>��ӹ���Ա\n2>�޸Ĺ���Ա��Ϣ\n3>ɾ������Ա\n4>��ѯ��Ϣ\n5>�޸ĳ�������Ա����\n") ;//֮���ٲ��� 
					printf("6>�����Ʒ\n7>ɾ����Ʒ\n8>�޸���Ʒ��Ϣ\n") ;
					printf("9>�޸��Ż�ȯ�ۿ�\n10>�޸Ļ�Ա�ۿ�\n11>ͳ����Ʒ\n12>�˳�\n");
					printf("*************************************************************\n?");
					scanf("%d",&i);
					setbuf(stdin, NULL);
					switch (i)
                  {
                    case 1:
                    {
                    	Administrator *head1= administratorCreateList();
				   		addAdministrator(head1);
                    break;
                    }
                    case 2:
                    	{
	                      	Administrator *head2= administratorCreateList();
	                      	changeAdiministratorInfo(head2);
	                   		break;                   		
						}
                    case 3:
                    	{
	                      	Administrator *head3= administratorCreateList();                    		
		                    removeAdministrator(head3);
							break;	                    		
						}
					case 4:
						{
							showInfo();
							break;
						}
					case 5:
						{
							SuperAdministrator *head4= superAdministratorCreateList();
							changeSuAdminPassword(head4);
							break;	
						}
					case 6:
						{
							wandProduct();
							break;
						}
					case 7:
						{
							deleteProduct();
							break;
						}
					case 8:
						{
							suSetProduct();
							break;
						}
					case 9:
						{
							CustomerList* head5=creatHeadCustomer();
							setCouponDiscount(head5);
							break;
						}						
					case 10:
						{
							CustomerList* head6=creatHeadCustomer();
							setVIPDiscount(head6);
							break;
						}
					case 11:
						{
							printf("�˴�����ͳ����Ʒ\n");
							break;
						}
                    case 12:
                    printf("12�㿪!\n");
                    return 2;             //����4��������¼���������ش�����ͨ������ֵ�ж��Ƿ��¼�ɹ��� 
                    break;
                    default:
                    printf("�ò㲻����, ����������\n");
				  }
				}
			}
			else
			{
				printf("���������������2�˳�����������������������\n");
				scanf("%d",&k);
				setbuf(stdin, NULL);
				if(k==2)
				{
					return 1;    //��һ��int���ܷ��ص�ֵ���ж��Ƿ��¼�ɹ� 
				}
			} 
			
			
		}
     fread(&admini,sizeof(SuperAdministrator),1,ad);  //��ȡ��һ�� 	
	}
	printf("�˺Ŵ���\n");
	fclose(ad);
	return 2;
	
//	while(admini.account==account&&a==0)
//		{
//			fclose(ad);     //�ҵ���Ӧ����Ա���ر��ļ� 
//			printf("����������\n");
//			scanf("%d",&password);
//			setbuf(stdin, NULL);
//			int i=0,k=0;     //���ڴ����ж���Ϣ 
//			if(password==admini.password)
//			{
//				printf("��ӭ���ĳ�������Ա��¼\n");
//				FILE*test1=fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test1.txt","a+");  	
//				ProductList PL;
//				fread(&PL,sizeof(ProductList),1,test1);
//				fclose(test1);
//				while(1)
//				{
//					printf("����1�����Ʒ\n����2�޸���Ʒ\n����3ɾ����Ʒ\n����4�˳�\n") ;//֮���ٲ��� 
//					scanf("%d",&i);
//					setbuf(stdin, NULL);
//					switch (i)
//                  {
//                    case 1:
//                    {
//				    wandProduct();
//                    break;
//                    }
//                    case 2:
//                    setProduct();
//                    break;
//                    case 3:
//                    deleteProduct();
//					break;	
//                    case 4:
//                    printf("4�㿪!\n");
//                    return 2;             //����4��������¼���������ش�����ͨ������ֵ�ж��Ƿ��¼�ɹ��� 
//                    break;
//                    default:
//                    printf("�ò㲻����, ����������\n");
//				  }
//				}
//			}
//			else
//			{
//				printf("���������������2�˳�����������������������\n");
//				scanf("%d",&k);
//				setbuf(stdin, NULL);
//				if(k==2)
//				{
//					return 1;    //��һ��int���ܷ��ص�ֵ���ж��Ƿ��¼�ɹ� 
//				}
//			} 
//	   }
//	fclose(ad);    //�Ҳ������ر��ļ� 
//	printf("�ù���Ա�˺Ų����ڣ�����\n"); 
}

/***************************************************
�������� LoginAdministrator  ���ܣ�����Ա��¼ 
*******************************************************/
//int LoginAdministrator()
//{
//	FILE * ad; 
//	int a=0;   //�����ж����� 
//	int account;
//	int password;    //�����û����� 
//	Administrator admini;
//	printf("���������Ա�˺�\n");
//	scanf("%d",&account);
//	setbuf(stdin, NULL);
//	ad=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\����Ա����.txt","r+");//�򿪴������Ա��Ϣ���ļ�
//	if(ad==NULL)
//     {
//      printf("���ļ�ʧ��.\n");
//      exit(0);
//     }
//    fread(&admini,sizeof(Administrator),1,ad); //���ļ��ж�ȡ�ṹ��; 
//   
//	for(;feof(ad)==0;)
//	{
//		//printf("%d\n",admini.account);
//		//printf("!!!\n");
//		while(admini.account==account)
//		{
//			fclose(ad);     //�ҵ���Ӧ����Ա���ر��ļ� 
//			printf("����������\n");
//			scanf("%d",&password);
//			setbuf(stdin, NULL);
//			int i=0,k=0;    //���ڴ����ж���Ϣ 
//			char c;
//			if(password==admini.password)
//			{
//				printf("��ӭ���Ĺ���Ա%s��¼\n",admini.name);
//				
//				while(1)
//				{
//					printf("����1�����Ʒ\n����2�޸���Ʒ\n����3ɾ����Ʒ\n����4�˳�\n") ;//֮���ٲ��� 
//					scanf("%d",&i);
//					setbuf(stdin, NULL);
//					switch (i)
//                  {
//                    case 1:
//                    {
//				    wandProduct();
//                    break;
//                    }
//                    case 2:
//                    setProduct();
//                    break;
//                    case 3:
//                    deleteProduct();
//					break;	
//                    case 4:
//                    printf("4�㿪!\n");
//                    return 2;             //����4��������¼���������ش�����ͨ������ֵ�ж��Ƿ��¼�ɹ��� 
//                    break;
//                    default:
//                    printf("�ò㲻����, ����������\n");
//				  }
//				}
//			}
//			else
//			{
//				printf("���������������2�˳�����������������������\n");
//				scanf("%d",&k);
//				setbuf(stdin, NULL);
//				if(k==2)
//				{
//					return 1;    //��һ��int���ܷ��ص�ֵ���ж��Ƿ��¼�ɹ� 
//				}
//			} 
//			
//			
//		}
//		fread(&admini,sizeof(Administrator),1,ad);    //��ȡ��һ�� 
//		
//	}
//	while(admini.account==account&&a==0)
//		{
//			fclose(ad);     //�ҵ���Ӧ����Ա���ر��ļ� 
//			printf("����������\n");
//			scanf("%d",&password);
//			setbuf(stdin, NULL);
//			int i=0,k=0;     //���ڴ����ж���Ϣ 
//			if(password==admini.password)
//			{
//				printf("��ӭ���Ĺ���Ա%s��¼\n",admini.name);
////				FILE*test1=fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test1.txt","a+");  	
////				ProductList PL;
////				fread(&PL,sizeof(ProductList),1,test1);
////				fclose(test1);
//				while(1)
//				{
//					printf("����1�����Ʒ\n����2�޸���Ʒ\n����3ɾ����Ʒ\n����4�˳�\n") ;//֮���ٲ��� 
//					scanf("%d",&i);
//					setbuf(stdin, NULL);
//					switch (i)
//                  {
//                    case 1:
//                    {
//				    wandProduct();
//                    break;
//                    }
//                    case 2:
//                    setProduct();
//                    break;
//                    case 3:
//                    deleteProduct();
//					break;	
//                    case 4:
//                    printf("4�㿪!\n");
//                    return 2;             //����4��������¼���������ش�����ͨ������ֵ�ж��Ƿ��¼�ɹ��� 
//                    break;
//                    default:
//                    printf("�ò㲻����, ����������\n");
//				  }
//				}
//			}
//			else
//			{
//				printf("���������������2�˳�����������������������\n");
//				scanf("%d",&k);
//				setbuf(stdin, NULL);
//				if(k==2)
//				{
//					return 1;    //��һ��int���ܷ��ص�ֵ���ж��Ƿ��¼�ɹ� 
//				}
//			} 
//	   }
//	fclose(ad);    //�Ҳ������ر��ļ� 
//	printf("�ù���Ա�˺Ų����ڣ�����\n"); 
//}

//void loginUser()//�����û�����  ��¼ 
//{
//	int choice;
//	printf("0>�˳�\n");
//	printf("1>����Ա��¼\n");
//	printf("���룺");
//	scanf("%d\n",&choice);
//		while(choice>1||choice<0)
//	{
//		printf("�������������\n?");
//		scanf("%d\n",&choice);
//	}
//	switch(choice)
//	{
//		case 0:
//			exit(0) ;
//			break;
//		case 1:
//			userCheckIn();
//			break;
//		default:
//			break; 
//			
//			
//	}	
// } 
int main()
{
	while(1)
	{
		int choice=-1;
		int i; 
		int k;
		printf("��ѡ����Ҫ���еĲ���\n");
		printf("0>�˳�\n"); 	
		printf("1>��������Ա��¼\n"); 
		printf("2>����Ա��¼\n"); 
		printf("3>�û���¼\n");
		printf("?");
		scanf("%d",&choice) ;
		printf("�������ѡ����%d\n",choice);
		while(choice>3||choice<0)
		{
			printf("�������������\n?");
			scanf("%d\n",&choice);
		}
		switch(choice)
		{
			case 0:
				break;
			case 1:
				 i=LoginSuperAdministrator();
				break;
			case 2:
				printf("�˴�������¼����Ա����\n");
//				 k=loginAdmin();
				break;
			case 3:
				printf("�˴�����½�û�����\n");
				break;
			default: 
				 break;	
		}
		if(choice==0)
		{
			break;
		}
	 		
	}
	return 0;

	
}
