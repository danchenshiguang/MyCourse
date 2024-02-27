#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  Max   100
#include <errno.h>
#include<windows.h>
#include<mmsystem.h>
#include<conio.h>
#pragma comment(lib,"Winmm.lib")
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

struct customer
{
	ItemList *shoppingCart;
	char name[10];
	int ID;//6λ�� 
	int password;// 6λ�� 
	int gender;//1:female  2:male
	int isVIP;//1:no  2:yes
	double vipDiscount;
	long long telNum; 
	double balance;
	int package;//1:yes 0:no
	double packageFee;
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
/*********************************************************/
struct record
{
	int customerID;
	int customerSalary;//1-5
	Item item;
};typedef struct record Record;
struct recordList
{
	Record record;
	struct recordList *next;
};typedef struct recordList RecordList;
struct countID
{
	int code;
	long long countTotal; //������Ʒ���� 
};typedef struct countID CountID;
struct countRecord
{
	CountID  countID[Max];//��Ʒ���ࣨID)
	int countCustomerSalary;//��¼�˿����� 
};typedef struct countRecord CountRecord;
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
 /*****/
 void wand_Product();
 void wandProduct();
 void statisticsProduct();
 ProductList  CreatProduct();
ProductList * maopao(ProductList * head);
void searchProduct();
void searchCustomer();
void showsCustomer();
void showsVip();
void showsProduct();
void showsRecord();
void CsearchRecord(int ID);
void PsearchRecord(int code);
void ranking();
ProductList * Smaopao(ProductList * head);
void setProduct(int code);
void deleteProduct(int code);
int LoginAdministrator();
/******/
void wand_record(RecordList* headRecord,RecordList* curRecord);

void registering(CustomerList* headCustomer);
CustomerList* login_verify(CustomerList* headCustomer);
Customer createCustomer(CustomerList* headCustomer);
CustomerList* createNode(Customer newCustomer);
void printList(CustomerList* headCustomer);
void wand_product(ProductList* headProduct,struct productInfo newProduct);
void writeFile_customer(CustomerList* headCustomer); 
void ShoppingRecommend(RecordList* head,CustomerList* curCustomer,ProductList* headProduct);
int setAdministrator(int account);
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
	Administrator *node=(Administrator *)malloc(sizeof(Administrator));
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
			fread(node,sizeof(Administrator),1,fp);											
			wandAdministrator(headAdministrator,node->account,node->password,node->name,node->gender,node->telNum,node->salary);
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
			fwrite(p,sizeof(Administrator),1,fp);
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
		fwrite(newNode,sizeof(Administrator),1,fp);
		printf("�����ɣ��Ƿ������ӹ���Ա\n");
		printf("1>����  2>�˳�\n?");
		scanf("%d",&isContinue);
		if(isContinue==1)
		{
			fclose(fp);
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
			system("cls");
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
				system("cls");
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
			fwrite(p,sizeof(Administrator),1,fp);
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
	Administrator *Admin=(Administrator*)malloc(sizeof(Administrator));
	if(fp==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
    //fread(&PL,sizeof(ProductList),1,test1); 
    if(fgetc(fp)!=EOF)   
    { 
   	  fseek(fp,0,SEEK_SET);
   	  fread(Admin,sizeof(Administrator),1,fp); 
//   	  printf("%d\n",feof(fp));
//   	  	printf("�˻���%d\n���룺%d\n������%s\n�Ա�%d\n�绰��%lld\nнˮ��%lf\n",Admin->account,Admin->password,Admin->name,Admin->gender,Admin->telNum,Admin->salary);
//   	  printf("%d",Admin->account);
   	  
   	  while (feof(fp)==0)//�ж��Ƿ���� 
   	  {
   	  	printf("�˻���%d\n���룺%d\n������%s\n�Ա�%d\n�绰��%lld\nнˮ��%.2lf\n",Admin->account,Admin->password,Admin->name,Admin->gender,Admin->telNum,Admin->salary);
   	  	printf("***************************************************************************\n");
   	  	fread(&Admin,sizeof(Administrator),1,fp); 
	  }
	  printf("\n..........��ѯ���...............\n");	  
    }
    else
    {
    	printf("����Ա����Ϊ�գ�����\n\n");
	}
	fclose(fp);
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
	rewind(fp);
		if(ch==EOF)
		{
			return;
		}
			fread(&newCustomer,sizeof(Customer),1,fp);
			while (feof(fp)==0)
//		while(!feof(fp)) 
		{
			wand(headCustomer,newCustomer);
			fread(&newCustomer,sizeof(Customer),1,fp);

		}
//		deletedLast(headCustomer);
		fclose(fp);
//		printList(headCustomer);
}

/*****************************************
��������void wand(CustomerList *headCustomer,Customer newCustomer)  ���ܣ����ļ��ж�ȡ���Ĺ˿���Ϣ�������� 
********************************************/
void wand(CustomerList *headCustomer,Customer newCustomer)
{
//	printf("����wand\n");
	
	CustomerList* newPtr=createNode(newCustomer);
//	printf("wand_get: %6d\n",newPtr->customer.ID);//ok
	CustomerList* curPtr=headCustomer;
	CustomerList* previousPtr=NULL;
	while(curPtr!=NULL)
	{
//		printf("����ѭ��\n");
		
		previousPtr=curPtr;	
//		printf("echo:1\n");
		curPtr=curPtr->next;	
//		printf("echo:2\n");
	}

				previousPtr->next=newPtr;//ע�� ���ӵķ���ͬ 
//				printf("echo:3\n");
			newPtr->next=curPtr;
//			printf("echo:4\n");	
//			printf("%6d\n",newPtr->customer.ID);
//			printf("%6d\n",previousPtr->next->customer.ID);

//	printf("Done_wand\n");	
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
	 	fwrite(p,sizeof(Customer),1,fp);
	 	p=p->next;
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
			printf("��������Ҫ�޸��ۿ۵��Ż�ȯ����:����1-3��");
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
	 	fwrite(p,sizeof(Customer),1,fp);
	 	p=p->next;
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
	Customer curCustomer;
	if(fp==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
    //fread(&PL,sizeof(ProductList),1,test1); 
    if(fgetc(fp)!=EOF)   
    { 
   	  fseek(fp,0,SEEK_SET);
   	  fread(&curCustomer,sizeof(Customer),1,fp); 
   	  while (feof(fp)==0)//�ж��Ƿ���� 
   	  {
   	  	int i=0;
   	  	int a=0;//������¼�˿��Ż�ȯ���� 
   	  	int b=0;
   	  	int c=0;   	  	
   	  	printf("ID��%d\n������%s\n�Ա�%d\n�绰��%lld\nнˮ��%lf\n�Ƿ�VIP��%d\n",curCustomer.ID,curCustomer.name,curCustomer.gender,curCustomer.telNum,curCustomer.salary,curCustomer.isVIP,curCustomer.vipDiscount);
   	  	for(i=0;i<10;i++)
   	  	{

   	  		if(curCustomer.discountCoupon[i].kind==1)
   	  		{
   	  			a++;
			 }
			 if(curCustomer.discountCoupon[i].kind==2)
			 {
			 	b++;
			 }
			 if(curCustomer.discountCoupon[i].kind==3)
			 {
			 	c++;
			 }			 	  		
		 }
   	  		printf("���˿ͳ��е��Ż�ȯΪ\n");
   	  		printf("1...........%d��\n",a);
   	  		printf("2...........%d��\n",b); 
   	  		printf("3...........%d��\n",c); 				 				  		 
   	  	printf("\n***************************************************************************\n");
   	  	fread(&curCustomer,sizeof(CustomerList),1,fp); 
	  }
	  printf("\n..........��ѯ���...............\n");
    }
    else
    {
    	printf("�˿�����Ϊ�գ�����\n\n");
	}
	fclose(fp);
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
void wand_Product()
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
   	  	printf("��Ʒ��ţ�%d\n��Ʒ���ƣ�%s\n��Ʒ���ͣ�%.2d\n��Ʒ������%.2lf\n��Ʒ�ۼۣ�%.2lf\n��Ʒ�ɱ���%.2lf\n��Ʒ����%.2lf\n��Ʒ��棺%d\n",PL.productInfo.description.code,PL.productInfo.description.name,PL.productInfo.description.kind,PL.productInfo.description.weight,PL.productInfo.description.price,PL.productInfo.cost,PL.productInfo.profit,PL.productInfo.stock);
   	  	printf("***************************************************************************\n");
   	  	fread(&PL,sizeof(ProductList),1,test1); 
	  }
	  printf("\n..........��ѯ���...............\n");	  
    }
    else
    {
    	printf("��Ʒ���Ϊ�գ�����\n\n");
	}
	fclose(test1);
}
/******************************************
suSetProduct()     ���ܣ���������Ա�޸���Ʒ��Ϣ 
************************************************/ 
void suSetProduct()
{
	printf("��������Ҫ�޸���Ʒ�ı��\n");
	int code;
	scanf("%d",&code);
	deleteProduct(code);
	printf("\n����������µ���Ʒ��Ϣ����\n\n");
	wand_Product();
}
/***********************************************************
deleteProduct()     ���ܣ���������Աɾ����Ʒ 
***********************************************************/
//void suDeleteProduct()
//{
//  ProductList p1;
//  int code,i=0;
//  FILE * fp = fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��Ʒ����.txt", "r+");
//  FILE * fp1 = fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\linshi.txt", "w+");//��д�½�һ����ʱ�ļ�
//  if(fp==NULL||fp1==NULL)
//     {
//      printf("���ļ�ʧ��.\n");
//      exit(0);
//     }
//  if(fgetc(fp)!=EOF)   
//   {
//   	fseek(fp,0,SEEK_SET);
//	fread(&p1,sizeof(ProductList),1,fp);
//    printf("��������Ҫɾ����Ʒ�ı��\n");	
//    scanf("%d",&code);
//    while (feof(fp)==0)//�ж��Ƿ���� 
//    {
//        if (p1.productInfo.description.code==code)//����Ҫɾ��������,��д�롣
//        {
//      	    printf("ɾ���ɹ�������\n");
//            i++;
//        }
//        else
//        {
//      	  fwrite(&p1, sizeof(ProductList), 1, fp1);
//	    }
//        fread(&p1,sizeof(ProductList),1,fp);
//    }
////      if (p1.productInfo.description.code==code)//����Ҫɾ��������,��д�롣��ֹ©�����һ�� 
////      {
////        printf("ɾ���ɹ�������\n");
////        i++;
////      }
////      else
////      {
////         fwrite(&p1, sizeof(ProductList), 1, fp1);
////	  }
//    if(i==0)
//   {
//  	 printf("����Ʒ�����ڣ�����\n");
//   }
//  }
//  else
//  {
//  	printf("��ǰ��Ʒ���Ϊ��!!!\n");
//  }
//    fclose(fp);
//    fclose(fp1);
//    remove("��Ʒ����.txt");                
//    rename("linshi.txt", "test1.txt");
//}
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
				system("cls");				
				printf("��ӭ���ĳ�������Ա��¼\n");
				int code=0;				
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
							wand_Product();
							break;
						}
					case 7:
						{
							printf("��������Ҫɾ����Ʒ�ı��\n");

							scanf("%d",&code);
							deleteProduct(code);
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
							statisticsProduct();
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
}
void wandProduct()
{
	ProductList PL;
	PL=CreatProduct();
	if(PL.productInfo.description.code!=0)
	{

		  FILE * test1=fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test1.txt","a+");
		  fwrite(&PL,sizeof(ProductList),1,test1);
		  fclose(test1);
	      printf("��ӳɹ�\n");
    }
    else
    {
    	printf("���ʧ�ܣ�����\n");
	}
	
		 
}
/************************************************************************************************/ 
ProductList CreatProduct()
{
	int a=0,b=0,i=0;
	int j=0;   //������int���ڴ����ж���Ϣ�����ں����ж� 
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
	  i=scanf("%d%d%d",&code,&kind,&stock);   //�������� 
	  if((i!=3)||(code<=999)||(code>9999))//||(kind!=1&&kind!=2&&kind!=3))//�ж������Ƿ���ȷ 
	  {
	  	
	  	do    
	  	{
	  	  setbuf(stdin, NULL);
		  if(u==0)
		  {	
		  printf("�����������1�������룬����2�˳�\n");
		  u++;	  
		  }   
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
    do 
	{
	  k=0,u=0;
	  printf("���Կո�ָ�����������۸�˫���ȸ���������������˫���ȸ�������\n");
	  i=scanf("%lf%lf",&price,&weight);   //�������� 
	  if((i!=2)||price<0||weight<0)//�ж������Ƿ���ȷ 
	  {
	  	do    
	  	{
	  	  setbuf(stdin, NULL);
		  if(u==0)
		  {	
		  printf("�����������1�������룬����2�˳�\n");
		  u++;	  
		  }   
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
    setbuf(stdin, NULL);
    fgets(creatProduct.productInfo.description.name, 15, stdin);
    creatProduct.productInfo.description.code=code;
    creatProduct.productInfo.stock=stock;
    creatProduct.productInfo.description.kind=kind;
    creatProduct.productInfo.description.price=price;
    creatProduct.productInfo.description.weight=weight;
    creatProduct.productInfo.cost=0;            //����Ա��Ȩ�޸ĳɱ� 
    creatProduct.productInfo.profit=0;   //����Ա��Ȩ�޸ĳɱ� 
    creatProduct.productInfo.sales=0;
    creatProduct.next=NULL;
	return creatProduct;
}

void setProduct(int code)
{
	deleteProduct(code);
	printf("\n����������µ���Ʒ��Ϣ����\n\n");
	wandProduct();
}
void deleteProduct(int code)
{
  ProductList p1;
  int i=0;
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
    int p=remove("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��Ʒ����.txt");       
    rename("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\linshi.txt","D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��Ʒ����.txt");
}
void statisticsProduct()
{
	ProductList * D;
	ProductList * A=(ProductList *)malloc(sizeof(ProductList));
	ProductList * B=(ProductList *)malloc(sizeof(ProductList));
	//ProductList * D,C;
	double sum;
	FILE * test1=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��Ʒ����.txt", "r+");
	if(test1==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
	if(fgetc(test1)!=EOF)
	{
	
		fseek(test1,0,SEEK_SET);
		fread(A,sizeof(ProductList),1,test1);	
		D=A;	
		sum=A->productInfo.description.price;
		if(fgetc(test1)!=EOF)
	  {
		  fseek(test1,-1,SEEK_CUR);
		  fread(B,sizeof(ProductList),1,test1);
		  //printf("%d\n",B.productInfo.description.code)
		  while(feof(test1)==0)
		  {	
			  A->next=B;
			  A=B;
			  sum=sum+B->productInfo.description.price;
			  //printf("%lf\n",sum);
			  B=(ProductList *)malloc(sizeof(ProductList));
		      fread(B,sizeof(ProductList),1,test1);			
		  }
      }
		fseek(test1,0,SEEK_SET);
		
		D=maopao(D);
		printf("%lf\n",sum);
		while(D!=NULL)
		{
			fwrite(D,sizeof(ProductList),1,test1);
			D=D->next;
		}
		printf("\n\n��Ʒ�ܼ�Ϊ:%lf\n\n",sum);
		showsProduct();
		
	}
	else
	{
		printf("��Ʒ���Ϊ�գ�����\n");
	}
	fclose(test1);
}
void ranking()
{
	int i=0;
	ProductList * D;
	ProductList * A=(ProductList *)malloc(sizeof(ProductList));
	ProductList * B=(ProductList *)malloc(sizeof(ProductList));
	//ProductList * D,C;
	FILE * test1=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��Ʒ����.txt", "r+");
	if(test1==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
	if(fgetc(test1)!=EOF)
	{
	
		fseek(test1,0,SEEK_SET);
		fread(A,sizeof(ProductList),1,test1);	
		D=A;	
		if(fgetc(test1)!=EOF)
	  {
		  fseek(test1,-1,SEEK_CUR);
		  fread(B,sizeof(ProductList),1,test1);
		  //printf("%d\n",B.productInfo.description.code)
		  while(feof(test1)==0)
		  {	
			  A->next=B;
			  A=B;
			  //printf("%lf\n",sum);
			  B=(ProductList *)malloc(sizeof(ProductList));
		      fread(B,sizeof(ProductList),1,test1);			
		  }
      }
		D=Smaopao(D);
		printf("                                                 �������а�                                         \n");
		while(D!=NULL)
		{
			i++;
			printf("NO.%d:\n",i);
			printf("��Ʒ���ƣ�%s\n��Ʒ��ţ�%d\n��Ʒ�۸�%lf\n��Ʒ����%d\n",D->productInfo.description.name,D->productInfo.description.code,D->productInfo.description.price,D->productInfo.sales);
			printf("************************************************************************************************************\n");
			D=D->next;
		}
		
		
	
	}
	else
	{
		printf("��Ʒ���Ϊ�գ�����\n");
	}
	fclose(test1);
}

void PsearchRecord(int code)
{
	Record R;
	int i=0;
	FILE * test3=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\record.txt", "r+");
	if(test3==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
     if(fgetc(test3)!=EOF)   
    { 
   	  fseek(test3,0,SEEK_SET);
   	  fread(&R,sizeof(Record),1,test3); 
   	  while (feof(test3)==0)//�ж��Ƿ���� 
   	  {
   	  	if(R.item.description.code==code)
   	  	{
   	  	  printf("��Ʒ����:%s\n��Ʒ���:%d\n��������:%d\n",R.item.description.name,R.item.description.code,R.item.quantity);
   	  	  printf("������ID��%d\n������нˮ���%d\n",R.customerID,R.customerSalary);
   	  	  printf("***************************************************************************\n");
   	  	  i++;
		}
		fread(&R,sizeof(Record),1,test3); 
	  }
	  if(i==0)
	  {
	  	printf("�����ڸ���Ʒ��������Ϣ������\n");
	  }

    }
    else
    {
    	printf("��ǰ�浵�˿�Ϊ�գ�����\n");
	}
	fclose(test3);
}
void CsearchRecord(int ID)
{
	Record R;
	int i=0;
	FILE * test3=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\record.txt", "r+");
	if(test3==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
     if(fgetc(test3)!=EOF)   
    { 
   	  fseek(test3,0,SEEK_SET);
   	  fread(&R,sizeof(Record),1,test3); 
   	  while (feof(test3)==0)//�ж��Ƿ���� 
   	  {
   	  	if(R.customerID==ID)
   	  	{
   	  	  printf("��Ʒ����:%s\n��Ʒ���:%d\n��������:%d\n",R.item.description.name,R.item.description.code,R.item.quantity);
   	  	  printf("������ID��%d\n������нˮ���%d\n",R.customerID,R.customerSalary);
   	  	  printf("***************************************************************************\n");
   	  	  i++;
		}
		fread(&R,sizeof(Record),1,test3); 
	  }
      if(i==0)
      {
      	printf("�����ڸù˿͵Ĺ�����Ϣ������\n");
	  }
    }
    else
    {
    	printf("��ǰ�浵�˿�Ϊ�գ�����\n");
	}
	fclose(test3);
}
void showsRecord()
{
	Record R;
	FILE * test3=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\record.txt", "r+");
	if(test3==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
     if(fgetc(test3)!=EOF)   
    { 
   	  fseek(test3,0,SEEK_SET);
   	  fread(&R,sizeof(Record),1,test3); 
   	  while (feof(test3)==0)//�ж��Ƿ���� 
   	  {
   	  	printf("��Ʒ����:%s\n��Ʒ���:%d\n��������:%d\n",R.item.description.name,R.item.description.code,R.item.quantity);
   	  	printf("������ID��%d\n������нˮ���%d\n",R.customerID,R.customerSalary);
   	  	printf("***************************************************************************\n");
   	  	fread(&R,sizeof(Record),1,test3); 
	  }

    }
    else
    {
    	printf("��ǰ�浵�˿�Ϊ�գ�����\n");
	}
	fclose(test3);
	
}
void showsVip()
{
	Customer C;
	int i=0;
	FILE * test2=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\customerList.txt", "r+");
	if(test2==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
     if(fgetc(test2)!=EOF)   
    { 
   	  fseek(test2,0,SEEK_SET);
   	  fread(&C,sizeof(Customer),1,test2); 
   	  while (feof(test2)==0)//�ж��Ƿ���� 
   	  {
   	  	if(C.isVIP==2)
   	  	{
   	  	  printf("�˿�ID��%d\n�˿����ƣ�%s\n",C.ID,C.name);
   	  	  if(C.gender==1)
   	  	  {
   	  		  printf("�˿��Ա�Ů\n"); 
		  }
		  if(C.gender==2)
		  {
			  printf("�˿��Ա���\n");
		  }
		  if(C.isVIP==1)
		  {
			  printf("�Ƿ�VIP����\n");
		  }
		  if(C.isVIP==2)
		  {
			  printf("�Ƿ�VIP����\n");
	 	  }
		  printf("�˿����:%lf\n�˿���н����:%d\n�˿͵绰���룺%lld\n",C.balance,C.salary,C.telNum);
   	  	  printf("***************************************************************************\n"); 
   	  	  i++;
		}
		fread(&C,sizeof(Customer),1,test2); 
	  }
	  if(i==0)
	  {
	  	printf("������Vip�˿ͣ�����\n");
	  }
    }
    else
    {
    	printf("��ǰ�浵�˿�Ϊ�գ�����\n");
	}
	fclose(test2);
	
}
void showsCustomer()
{
	Customer C;
	FILE * test2=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\customerList.txt", "r+");
	if(test2==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
     if(fgetc(test2)!=EOF)   
    { 
   	  fseek(test2,0,SEEK_SET);
   	  fread(&C,sizeof(Customer),1,test2); 
   	  while (feof(test2)==0)//�ж��Ƿ���� 
   	  {
   	  	//printf("!!!\n");
   	  	printf("�˿�ID��%d\n�˿����ƣ�%s\n",C.ID,C.name);
   	  	if(C.gender==1)
   	  	{
   	  		printf("�˿��Ա�Ů\n"); 
		}
		if(C.gender==2)
		{
			printf("�˿��Ա���\n");
		}
		if(C.isVIP==1)
		{
			printf("�Ƿ�VIP����\n");
		}
		if(C.isVIP==2)
		{
			printf("�Ƿ�VIP����\n");
		}
		printf("�˿����:%lf\n�˿���н����:%d\n�˿͵绰���룺%lld\n",C.balance,C.salary,C.telNum);
   	  	printf("***************************************************************************\n");
   	  	fread(&C,sizeof(Customer),1,test2); 
	  }

    }
    else
    {
    	printf("��ǰ�浵�˿�Ϊ�գ�����\n");
	}
	fclose(test2);
	
}
void searchCustomer(int ID)
{
	Customer C;
	int i=0;
	FILE * test2=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\customerList.txt", "r+");
	if(test2==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
     if(fgetc(test2)!=EOF)   
    { 
   	  fseek(test2,0,SEEK_SET);
   	  fread(&C,sizeof(Customer),1,test2); 
   	  while (feof(test2)==0)//�ж��Ƿ���� 
   	  {
   	  	if(C.ID==ID)
   	  	{
   	  	  printf("�˿�ID��%d\n�˿����ƣ�%s\n",C.ID,C.name);
   	  	  if(C.gender==1)
   	  	  {
   	  		  printf("�˿��Ա�Ů\n"); 
		  }
		  if(C.gender==2)
		  {
			  printf("�˿��Ա���\n");
		  }
		  if(C.isVIP==1)
		  {
			  printf("�Ƿ�VIP����\n");
		  }
		  if(C.isVIP==2)
		  {
			  printf("�Ƿ�VIP����\n");
	 	  }
		  printf("�˿����:%lf\n�˿���н����:%d\n�˿͵绰���룺%lld\n",C.balance,C.salary,C.telNum);
   	  	  printf("***************************************************************************\n"); 
   	  	  i++;
		}
		fread(&C,sizeof(Customer),1,test2); 
	  }
	  if(i==0)
	  {
	  	printf("�ù˿Ͳ����ڣ�����\n");
	  }
    }
    else
    {
    	printf("��ǰ�浵�˿�Ϊ�գ�����\n");
	}
	fclose(test2);
	
}
void searchProduct()
{
	int code,i=0;
	printf("��������Ʒ���\n");
	scanf("%d",&code);
	setbuf(stdin,NULL);
	ProductList PL;
	FILE * test1=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\customerList.txt", "r+");
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
   	  	if(PL.productInfo.description.code==code)
   	  	{
			 printf("��Ʒ��ţ�%d\n��Ʒ���ƣ�%s\n��Ʒ���ͣ�%d\n��Ʒ������%lf\n��Ʒ�ۼۣ�%lf\n��Ʒ�ɱ���%lf\n��Ʒ����%lf\n��Ʒ��棺%d\n",PL.productInfo.description.code,PL.productInfo.description.name,PL.productInfo.description.kind,PL.productInfo.description.weight,PL.productInfo.description.price,PL.productInfo.cost,PL.productInfo.profit,PL.productInfo.stock);
   	  	     printf("***************************************************************************\n");
   	  	     i++;
   	    }
   	    fread(&PL,sizeof(ProductList),1,test1); 
	  }
	  if(i==0)
	  {
	  	printf("����Ʒ�����ڣ�����\n");
	  }

    }
    else
    {
    	printf("��Ʒ���Ϊ�գ�����\n");
	}
	fclose(test1);
	
}
ProductList * maopao(ProductList * head)
{
	ProductList *p,*q;
	int num=0,j=0;
	q=head;
	//��ȡ����ĳ��� 
	while(q!=NULL){
		q=q->next;
		num++;
	}
	//ð������Ļ���˼· 
	int i;
	for(i=0;i<num-1;i++)
		{
			p=q=head; 
			j=num-i-1; //����ÿһ��ѭ���������ȽϵĴ��� 
			while(p->next!=NULL&&j!=0){
				j--;
				if(p->productInfo.stock<p->next->productInfo.stock){
					//�ڵ�Ľ��� 
					if(p==head) head=p->next;
					else q->next=p->next;
					q->next=p->next;
					q=q->next;
					p->next=q->next;
					q->next=p;
					//ִ��������Ĺ��̺�Ϊ���ܹ���p˳����ִ���ƶ������������һλ . 
					p=q; 
				}
				q=p; //Ϊ������q������p��ǰ�� 
				p=p->next; //pָ����ƣ���p�������q��ǰ�� 
			}
		}
	return head;
} 
ProductList * Smaopao(ProductList * head)
{
	ProductList *p,*q;
	int num=0,j=0;
	q=head;
	//��ȡ����ĳ��� 
	while(q!=NULL){
		q=q->next;
		num++;
	}
	//ð������Ļ���˼· 
	int i;
	for(i=0;i<num-1;i++)
		{
			p=q=head; 
			j=num-i-1; //����ÿһ��ѭ���������ȽϵĴ��� 
			while(p->next!=NULL&&j!=0){
				j--;
				if(p->productInfo.sales<p->next->productInfo.sales){
					//�ڵ�Ľ��� 
					if(p==head) head=p->next;
					else q->next=p->next;
					q->next=p->next;
					q=q->next;
					p->next=q->next;
					q->next=p;
					//ִ��������Ĺ��̺�Ϊ���ܹ���p˳����ִ���ƶ������������һλ . 
					p=q; 
				}
				q=p; //Ϊ������q������p��ǰ�� 
				p=p->next; //pָ����ƣ���p�������q��ǰ�� 
			}
		}
	return head;
} 

/***************************************************
�������� LoginAdministrator  ���ܣ�����Ա��¼ 
*******************************************************/
int LoginAdministrator()
{
	mciSendString("open D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\abc.mp3 alias bkmusic", 0, 0, 0);
	mciSendString("play bkmusic repeat", 0, 0, 0);        //ѭ����������
	FILE * ad; 
	int a=0;   //�����ж����� 
	int account;
	int password;    //�����û����� 
	Administrator admini;
	printf("���������Ա�˺�\n");
	scanf("%d",&account);
	setbuf(stdin, NULL);
	ad=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\����Ա����.txt","r+");//�򿪴������Ա��Ϣ���ļ�
	if(ad==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
    fread(&admini,sizeof(Administrator),1,ad);
//	printf("%d\n",admini.account) ;//���ļ��ж�ȡ�ṹ��;
//	printf("%d",feof(ad)) ;
	while(feof(ad)==0)
	{
		printf("%d",admini.account);
		//printf("%d\n",admini.account);
		//printf("!!!\n");
		while(admini.account==account)
		{
			fclose(ad);     //�ҵ���Ӧ����Ա���ر��ļ� 
			printf("����������\n");
			scanf("%d",&password);
			setbuf(stdin, NULL);
			int i=0,k=0,j=0,m=1;    //���ڴ����ж���Ϣ 
			int code=0,ID=0;
			char c;
			if(password==admini.password)
			{
				system("cls");
				printf("��ӭ���Ĺ���Ա%s��¼\n",admini.name);
				//printf("%d\n",sizeof(ProductList));
				
				while(1)
				{
					printf("����1�����Ʒ\n����2�޸���Ʒ\n����3ɾ����Ʒ\n");
					printf("����4��ʾ��Ʒ\n����5ͳ����Ʒ���������Ӷൽ��������Ʒ\n����6��ѯ��Ʒ\n����7��ʾ�˿���Ϣ\n����8��ʾvip�˿���Ϣ\n����9��ѯ�˿���Ϣ\n����10��ʾ������Ϣ\n����11��ѯ������Ϣ\n����12������������Ʒ\n����13�ر�/������\n����14�޸�����\n����15����Ļ\n����16�˳�\n") ;//֮���ٲ��� 
					scanf("%d",&i);
					setbuf(stdin, NULL);
					switch (i)
                  {
                    case 1:
                    {
				    wandProduct();
                    break;
                    }
                    case 2:
                    printf("��������Ҫ�޸ĵ���Ʒ���\n");
	                scanf("%d",&code);
                    setProduct(code);
                    break;
                    case 3:
                    printf("��������Ҫɾ����Ʒ�ı��\n");	
                    scanf("%d",&code);
                    deleteProduct(code);
					break;	
					case 4:
					showsProduct(); 
					break;
					case 5:
					statisticsProduct();
					break;
					case 6:
					searchProduct();
					break;
					case 7:
					showsCustomer();
					break;
					case 8:
					showsVip();
					break;
					case 9:
					printf("��������Ҫ��ѯ�Ĺ˿�ID\n");
					scanf("%d",&ID);	
					searchCustomer(ID);
					break;	
					case 10:
					showsRecord();
					break;	
					case 11:
					{
					printf("����1���չ�����ID��ѯ������2������Ʒ��Ų�ѯ\n");
					scanf("%d",&j);
					if(j==1)
					{
						printf("������˿�ID\n");
						scanf("%d",&ID);
						CsearchRecord(ID);
					}
					if(j==2)
					{
						printf("��������Ʒ���\n");
						scanf("%d",&code);
						PsearchRecord(code);
					}
					if(j!=1&&j!=2)
					{
						printf("����ȷ���룡����\n");
					}
					break;
				    }
				    case 12:
				    ranking();
				    break;
				    case 13:
				    {
						
				      if(m%2==1)
				      {
				    	  mciSendString("stop bkmusic", 0, 0, 0);
					  }
					  else
					  {
						  mciSendString("play bkmusic repeat", 0, 0, 0);
					  }
					  m++;
					  break;
				    }
				    case 14:
				    setAdministrator(admini.account);
				    break;
				    case 15:
				    system("cls");
				    break;
                    case 16:
                    printf("16�㿪!\n");
                    return 2;            //����13��������¼���������ش�����ͨ������ֵ�ж��Ƿ��¼�ɹ��� 
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
		fread(&admini,sizeof(Administrator),1,ad);    //��ȡ��һ�� 
		
	}

	fclose(ad);    //�Ҳ������ر��ļ� 
	printf("�ù���Ա�˻�������\n"); 
}


/************************************************************************/
void wand_product(ProductList* headProduct,struct productInfo newProduct)
{
	ProductList* newPtr=(ProductList*)malloc(sizeof(ProductList));
	newPtr->productInfo=newProduct;
	newPtr->next=NULL;
	ProductList* curPtr=headProduct;
	ProductList* previousPtr=NULL;
	while(curPtr!=NULL)
	{
		previousPtr=curPtr;
		curPtr=curPtr->next;
	}
	previousPtr->next=newPtr;//ע�� ���ӵķ���ͬ 
	newPtr->next=curPtr;
//	printf("Done_wand_product\n");

}

void printList_product(ProductList* headProduct)
{
	ProductList* curPtr=headProduct;
		puts("The list is");
		curPtr=curPtr->next;
		while(curPtr!=NULL)
		{
			
			printf("%s-->",curPtr->productInfo.description.name);
			curPtr=curPtr->next;
		}
		puts("NULL\n");
} 


void writeFile_record(RecordList* headRecord)
{
	RecordList* curPtr=headRecord->next;
	FILE *fp;
		if((fp=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\record.txt","w"))!=NULL)
	{
		printf("error");
	}
	
		while(curPtr!=NULL)
	{
//		printf("����д�ļ�ѭ��\n");
		fwrite(&(curPtr->record), sizeof(struct record), 1, fp);
		curPtr=curPtr->next;
	}
//	printf("Done_write\n");
	fclose(fp);
	
	
}

void readFile_product(ProductList *headProduct)
{
//	printf("aaa\n");
	ProductList PL;
	struct productInfo plf;
	FILE * fp=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��Ʒ����.txt", "r+");
	if(fp==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
     
    if(fgetc(fp)!=EOF)   
    { 
   	  	fseek(fp,0,SEEK_SET);
   	  	fread(&PL,sizeof(ProductList),1,fp); 
   	  	while (feof(fp)==0)/*�ж��Ƿ����*/ 
   	  	{
   	  		plf=PL.productInfo;
   	  		wand_product(headProduct,plf);
   	  		fread(&PL,sizeof(ProductList),1,fp); 
	  	}
    }
    	else
   	 {
    	printf("��Ʒ���Ϊ�գ�����\n");
		}
//	printList_product(headProduct);
	
}

void readFile_record(RecordList* headRecord)
{
	
	Record newRecord;
	FILE *fp;char ch;

	if((fp=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\record.txt","r"))==NULL)
	{
		printf("Error\n");
		return;
	}
	ch=fgetc(fp);
	rewind(fp);
		if(ch==EOF)
		{
			return;
		}
			fread(&newRecord,sizeof(Record),1,fp);
			while (feof(fp)==0)

		{
			RecordList* newRecordList=(RecordList*)malloc(sizeof(RecordList));
			newRecordList->record=newRecord;
			wand_record(headRecord,newRecordList);
			fread(&newRecord,sizeof(Record),1,fp);

		}

		fclose(fp);
		printf("Done_read_Record\n");
//		printList();
}

void writeFile_product(ProductList* headProduct)
{
//	printf("����д�ļ�\n");
	ProductList* curPtr=headProduct->next;
	if(headProduct!=NULL)
	{
//		printf("Notempty\n");
	}//ok 
	FILE * rt;
	
	if((rt=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��Ʒ����.txt","w"))!=NULL)
	{
//		printf("error");
	}
	
//	printf("openFile\n");
	while(curPtr!=NULL)
	{
//		printf("����д�ļ�ѭ��\n");
		fwrite(curPtr, sizeof(ProductList), 1, rt);
		curPtr=curPtr->next;
	}
//	printf("Done_write\n");
	fclose(rt);
}


ProductList* createHeadProduct()
{
	ProductList* headProduct=(ProductList*)malloc(sizeof(ProductList));
	headProduct->next=NULL;
	return headProduct;
}
void writeFile_customer(CustomerList* headCustomer)
{
//	printf("����д�ļ�\n");
	CustomerList* curPtr=headCustomer->next;
	if(headCustomer!=NULL)
	{
//		printf("Notempty\n");
	}//ok 
	FILE * rt;
	
	if((rt=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\customerList.txt","w"))!=NULL)
	{
//		printf("error");
	}
	
//	printf("openFile\n");
	while(curPtr!=NULL)
	{
//		printf("����д�ļ�ѭ��\n");
		fwrite(&(curPtr->customer), sizeof(Customer), 1, rt);
		curPtr=curPtr->next;
	}
//	printf("Done_write\n");
	fclose(rt);
}
//************************** *******************************************************************

//ע���¼************************************************************ 
void registering(CustomerList* headCustomer)
{
	Customer newCustomer=createCustomer(headCustomer);
	printf("registering: %s\n",newCustomer.name);//ok
	wand(headCustomer,newCustomer);
//	printf("�߳�wand\n"); 
}

//void printList(CustomerList* headCustomer)//��ӡ�˿� ID�б� 
//{
//	CustomerList* curPtr=headCustomer;
//		puts("The list is");
//		curPtr=curPtr->next;
//		while(curPtr!=NULL)
//		{
//			
//			printf("%d-->",curPtr->customer.ID);
//			curPtr=curPtr->next;
//		}
//		puts("NULL\n");
//} 

int checkCustomer(CustomerList* headCustomer,int ID)
{
	CustomerList* curPtr=headCustomer;
	while(curPtr!=NULL)
	{
		if(curPtr->customer.ID==ID)
		{
			return 1;
		}
		curPtr=curPtr->next;
	}
	return 0;
}

Customer createCustomer(CustomerList* headCustomer)
{
	int ID;int gender,password,salary;
	long long telNum; char name[15];
	
	printf("Enter your gender \n 1 means female\n2means male: ");
	do{
		printf("Enter:");
		scanf("%1d",&gender);
	}while(gender<1||gender>2);
	setbuf(stdin, NULL);
	
	
	printf("Enter the 6 numbers as your id\n");
	do{
			do{
			scanf("%6d",&ID);
		
			}while(ID<99999 || ID>999999);
			
	}while(checkCustomer(headCustomer,ID));

	setbuf(stdin, NULL);
	printf("Enter your name\n");
	printf("Enter( No More Than 15 characters):");
		scanf("%s",name);
setbuf(stdin, NULL);
	printf("Enter the password: ");
	do{
		printf("Enter:");
		scanf("%6d",&password);
	}while(password<99999 || password>999999);
	
	printf("Enter your salary\n \n1:<3000\n2:3000-6000\n3:6000-10000\n4:10000-20000\n5:>20000:");
	do{
		printf("Enter:");
		scanf("%1d",&salary);
	}while(salary<1||salary>5);
	
	printf("Enter your telephone number\n");
	do{
		printf("Enter:");
		scanf("%11lld",&telNum);
	}while(telNum<9999999999 || telNum>99999999999);
	
	
	Customer newCustomer;
	newCustomer.ID=ID;
	newCustomer.gender=gender;
	newCustomer.password=password;
	newCustomer.salary=salary;
	newCustomer.telNum=telNum;
	newCustomer.isVIP=1;
	newCustomer.vipDiscount=0.8;
	newCustomer.packageFee=15.0;
	newCustomer.balance=0.0;
	strcpy(newCustomer.name,name);
	newCustomer.shoppingCart=(ItemList*)malloc(sizeof(ItemList));
	newCustomer.shoppingCart->next=NULL;
//	printf("%6d",newCustomer.ID);
//	printf("Done Input\n");
	return newCustomer;
}


CustomerList* login_verify(CustomerList* headCustomer)//��֤ 
{
	int id;int password;
	CustomerList* curCustomer=headCustomer;
	printf("***************************Login***********************\n");
	printf("Enter your ID:");
	scanf("%6d",&id);
	printf("Enter your password:");
	scanf("%6d",&password);
	while(curCustomer!=NULL)
	{
		
		if(curCustomer->customer.ID==id && curCustomer->customer.password==password)
		{
			return curCustomer;
		}
		curCustomer=curCustomer->next;
	}
	return NULL;
	
	
}

CustomerList* login_user(CustomerList *headCustomer)//��½ҳ�� 
{
	
	int choice_login;
	CustomerList* curCustomer;
	printf("***********************WELCOME**********************************\n **Input 1 to register\n");
	printf("**Input 2 to login\n");
	printf("****************************************************************\n\n\n");
	printf("Choice: ");
	scanf("%1d",&choice_login);
	system("cls");
	while(choice_login!=0)
	{
		switch(choice_login)
		{
			case 1:
				registering(headCustomer);
				writeFile_customer(headCustomer);
				choice_login=2;
				system("cls");
				break;
			case 2:
				if( (curCustomer=login_verify(headCustomer))!=NULL)
				{
					choice_login=0;
					return curCustomer;
				}else
				{
					printf("===============Customer Not Found======================\n");
					printf("======input 1 to register\ninput 2 to login again========\n\n");
					printf("===Enter your choice:");
					scanf("%d",&choice_login);
					system("cls");
				}
				break;
			default:
				printf("Invalid Input\n");
				system("cls");
				break;			
		}
	}
}
//***********************************************************************
//*****************�����ﳵ+���� 



/**********************************************************
�������� void sortProduct; void wand_record; void buildRecordList
����: ��ǰ�˿� ��ǰ���ﳵ���� 
����: ��
���ܣ� �������ۼ�¼���� 
**********************************************************/
RecordList* createRecord(CustomerList* curCustomer,ItemList* curItem)
{
	RecordList* newRecord=(RecordList*)malloc(sizeof(RecordList));
	newRecord->record.item=curItem->item;
	newRecord->record.customerID=curCustomer->customer.ID;
	newRecord->record.customerSalary=curCustomer->customer.salary;
	return newRecord;
	
}
void wand_record(RecordList* headRecord,RecordList* curRecord)
{
	RecordList* curPtr=headRecord;
	RecordList* prePtr=NULL;
	while(curPtr!=NULL)
	{
		prePtr=curPtr;
		curPtr=curPtr->next;
	}
	prePtr->next=curRecord;
	curRecord->next=curPtr;
	
//	printf("Done_wand_record");
}

RecordList* createHeadRecord()// HEAD_RECORD
{
	RecordList* headRecord=(RecordList*)malloc(sizeof(RecordList));
	headRecord->next=NULL;
	return headRecord;
}

void buildRecordList(CustomerList* curCustomer,RecordList* headRecord)
{
	ItemList* curItem=curCustomer->customer.shoppingCart->next;//�ܿ�ͷ�ڵ�ı�����ȡ��Ϣ 
	while(curItem!=NULL)
	{
		RecordList* curRecord=createRecord(curCustomer,curItem);
		wand_record(headRecord,curRecord);
		curItem=curItem->next;
	}
//	printf("Done_build_Record_list\n");
	
}





ItemList* getItem(CustomerList* curCustomer,int code)
{
	ItemList* curPtr=curCustomer->customer.shoppingCart;
	while(curPtr!=NULL)
	{
		if(curPtr->item.description.code==code)
		{
			return curPtr;
		}
		curPtr=curPtr->next;
	}
	return NULL;
}

void setQuantity(CustomerList* curCustomer)
{
	int quantity;int code;
	printf("Enter the code:");
	printf("Enter:");
	scanf("%4d",&code);
	ItemList *curItem=getItem(curCustomer,code);
	if(curItem!=NULL)
	{
		printf("Enter the new quantity: ");
		printf("Enter:");
		scanf("%1d",&quantity);
		curItem->item.quantity=quantity;
		printf("*******************Done!!***********************\n");
		
	}else
	{
		printf("Item Not Found");
	}
}
void instruction_2()
{
	printf("++++++++++++++++++++++++++++\n");
	printf("Enter 1 to set your cart\n");
	printf("Enter 2 to pay\n");
	printf("Enter 0 to back\n");
	printf("++++++++++++++++++++++++++++\n");
}

void showCart(CustomerList* curCustomer)
{
	ItemList* curPtr=curCustomer->customer.shoppingCart->next;
	while(curPtr!=NULL)
	{
		printf("=========================================\n");
		printf("============%s================\n",curPtr->item.description.name);
		printf("============code: %4d===============\n",curPtr->item.description.code);
		printf("============kind :%1d===============\n",curPtr->item.description.kind);
		printf("============quantity: %d===============\n",curPtr->item.quantity);
		printf("============price: %lf===============\n",curPtr->item.description.price);	
		printf("============weight:%lf===============\n",curPtr->item.description.weight);
		printf("========================================\n\n");
		curPtr=curPtr->next;
	}
}

/**********************************************************
�������� void addCoupon 
����: ��ǰ�ܼ� �˿���Ϣ 
����: ��
���ܣ� ���ݼ۸��Զ��ṩ����ȯ 
**********************************************************/
void addCoupon(double totalPrice, CustomerList* curCustomer)
{
	int i;
	if(totalPrice>500)
	{
		for(i=0;i<10;i++)
		{
			if(curCustomer->customer.discountCoupon[i].kind==0)
			{
				curCustomer->customer.discountCoupon[i].kind=3;
			}
		}
		
					
	}else if(totalPrice>300)
		{
		
		for(i=0;i<10;i++)
		{
			if(curCustomer->customer.discountCoupon[i].kind==0)
			{
				curCustomer->customer.discountCoupon[i].kind=2;
			}
		}
			
		}else if(totalPrice>100)
		{
			for(i=0;i<10;i++)
		{
			if(curCustomer->customer.discountCoupon[i].kind==0)
			{
				curCustomer->customer.discountCoupon[i].kind=1;
			}
		}
		}
			
}

/**********************************************************
�������� Double getTotalPrice 
����: ��ǰ�˿���Ϣ 
����: �ܼ� 
���ܣ� �����ܼ� 
**********************************************************/
double getTotalPrice(CustomerList* curCustomer)
{
	double totalPrice=0;int i;double tempPrice;int choice_2_1,choice_2_2;
	
	ItemList* curItem=curCustomer->customer.shoppingCart;
	curItem=curItem->next;
	printf("***********************\n");
	printf("Enter 1 to package\nEnter 0 not to\nEnter: ");
	scanf("%1d",&choice_2_1);
	if(choice_2_1)
	{
		totalPrice+=curCustomer->customer.packageFee;
	}
	
	while(curItem!=NULL)
	{
		tempPrice=curItem->item.description.price;
		printf("Enter 1 to use the discount coupon\n Enter 0 not to use\n Enter:");
		scanf("%1d",&choice_2_2);
		if(choice_2_2)
		{
				for(i=0;i<10;i++)
			{
				if((curCustomer->customer.discountCoupon[i].kind)==curItem->item.description.kind)
				{
					tempPrice=tempPrice*curCustomer->customer.discountCoupon[i].discount;
					tempPrice=tempPrice*curItem->item.quantity;
					curCustomer->customer.discountCoupon[i].kind=0;
					
					break;
				}
				if(i==9)
				{
					printf("����Ӧ�Ż�ȯ����\n");
					tempPrice=tempPrice*curItem->item.quantity;
					totalPrice+=tempPrice;
				}
				
			}	
			
		}else
		{
			tempPrice=tempPrice*curItem->item.quantity; 
			totalPrice+=tempPrice;	
		}	
		curItem=curItem->next;
	}
	
	if(curCustomer->customer.isVIP==2)
	{
		totalPrice=totalPrice*curCustomer->customer.vipDiscount;
	}
	
	return totalPrice;
	
}


/**********************************************************
�������� void pay
����: ��ǰ�˿� 
����: ��
���ܣ� ���� 
**********************************************************/
void pay(CustomerList* curCustomer)
{
	int choice,confirm;
	double totalPrice;
	totalPrice=getTotalPrice(curCustomer);
	addCoupon(totalPrice,curCustomer);
	if(totalPrice>curCustomer->customer.balance)
	{
		printf("���㣡��\n�뷵�ظ�����Ϣ���ó�ֵ����\n");
		return;
	}
	
	printf("------------------------------------------\n");
	printf("???????CONFIRM to BUY?????\nEnter 1 to confirm\nEnter 0 to exit\nEnter:");
	scanf("%1d",&confirm);
	if(!confirm)
	{
		return;
	}
	printf("Enter 1 to get receipt\nEnter 0 not to\n");
	printf("Enter:");
	scanf("%1d",&choice);
	
	printf("**********�ܼۣ�%lf**************\n",totalPrice);
	curCustomer->customer.balance-=totalPrice;
	
}
/**********************************************************
�������� void setStock 
����: ��Ʒ����  ��ǰ���ﳵ 
����: ��
���ܣ� �������������Ʒ�Ķ�Ӧ�Ŀ�������� 
**********************************************************/
void setStock(ProductList* headProduct,ItemList *shoppingCart)
{
	ProductList* curProduct=headProduct->next;
	ItemList* curItem=shoppingCart->next;
	while(curItem!=NULL)
	{
		while(curProduct!=NULL)
		{
			if(curItem->item.description.code==curProduct->productInfo.description.code)
			{
				printf("����\n");
				curProduct->productInfo.stock-=curItem->item.quantity;
				curProduct->productInfo.sales+=curItem->item.quantity;
			}
			curProduct=curProduct->next;
		}
		curItem=curItem->next;
	}
//	ProductList* curPtr=headProduct->next;
//	while(curPtr!=NULL)
//	{
//		printf("%s:%d\n",curPtr->productInfo.description.name,curPtr->productInfo.stock);
//		curPtr=curPtr->next;
//	}
	
}
/**********************************************************
�������� void resetCart
����: ��ǰ�˿� 
����: ��
���ܣ� ��ֵ���ﳵ �൱����� 
**********************************************************/
void resetCart(CustomerList* curCustomer)
{
	curCustomer->customer.shoppingCart=(ItemList*)malloc(sizeof(ItemList));
	curCustomer->customer.shoppingCart->next=NULL;
	
}
/**********************************************************
�������� void setCart 
����: ��Ʒ���� ��ǰ�˿� ���ۼ�¼���� 
����: ��
���ܣ� ���ù��ﳵ ����������Ʒ����������ȹ��� 
**********************************************************/
void setCart(CustomerList *curCustomer,ProductList* headProduct,RecordList* headRecord)
{
	int  choice_2; 
	printf("Your Cart contains the follows:\n");
	showCart(curCustomer);
	instruction_2();
	scanf("%1d",&choice_2);
	system("cls");
	while(choice_2)
	{
		switch(choice_2)
		{
			case 1:
				setQuantity(curCustomer);
				showCart(curCustomer);
				instruction_2();
				scanf("%1d",&choice_2);
				system("cls");
				break;
			case 2:
				if(curCustomer->customer.shoppingCart->next!=NULL)
				{
					pay(curCustomer);
					setStock(headProduct,curCustomer->customer.shoppingCart);
					buildRecordList(curCustomer,headRecord);
					writeFile_record(headRecord);					
					resetCart(curCustomer);
				
				}else
				{
					printf("Empty Cart!!\n");
				}
				instruction_2();
				scanf("%1d",&choice_2);
				system("cls");
				break;
			default:
				printf("Invalid Input\n");
				showCart(curCustomer);
				instruction_2();
				scanf("%1d",&choice_2);
				system("cls");
				break;	
		}
	}
 } 


//********************************************************************************
 //������Ʒ �����빺�ﳵ�� 
void showProductInfo(ProductList* curPtr)
{
			printf("*******************************\n");
			printf("******code:%d******\n",curPtr->productInfo.description.code);
			printf("******name:%s******\n",curPtr->productInfo.description.name);
			printf("******kind:%d******\n",curPtr->productInfo.description.kind);
			printf("******weight:%lf******\n",curPtr->productInfo.description.weight);
			printf("******price:%lf******\n",curPtr->productInfo.description.price);
			printf("*******************************\n\n");
}



/**********************************************************
�������� void elect
����: ��Ʒ���� �ؼ��� 
����: ��
���ܣ� ���ݹؼ�����ʾ�����Ʒ 
**********************************************************/
void electProduct(ProductList* headProduct,char* keyWord)//������ʾ�ض���Ʒ 
{
//	printf("echo:1_electProduct\n");
	char* str;
	ProductList* curPtr=headProduct;
	while(curPtr!=NULL)
	{
//		printf("echo:2_electProduct\n");
		str=strstr(curPtr->productInfo.description.name,keyWord);
		if(str!=NULL)
		{
//			printf("echo:3_electProduct\n");
			showProductInfo(curPtr);
		}
		curPtr=curPtr->next;
	}
}
void instruction_1_1()
{
	printf("**********************************************\n");
		printf("Enter 1 to show goods\n Enter 2 to show in Price\n Enter 3 to show in Weight Order\nEnter 0 to exit.\n");
	printf("**********************************************\n");
		printf("Enter:");

}

ProductList* getProduct(ProductList* headProduct,int code)
{
	ProductList* curPtr=headProduct;
//	printf("in_getProduct\n");
	while(curPtr!=NULL)
	{
		if(code==curPtr->productInfo.description.code)
		{
//			printf("Found");
			return curPtr;
		}
		curPtr=curPtr->next;
	}
		printf("Not Found\n");
		return NULL;
}



ItemList* createItem(Description newDescription,int quantity)
{
	ItemList* newItem=(ItemList*)malloc(sizeof(ItemList));
	newItem->item.description=newDescription;
	newItem->item.quantity=quantity;
	newItem->next=NULL;
	return newItem;
}

void addCart(CustomerList* curCustomer,ItemList* item)
{
	ItemList* newItem=item;
	ItemList* curPtr=curCustomer->customer.shoppingCart;
	ItemList* previousPtr=NULL;
	
	
		while(curPtr!=NULL)
	{
//		printf("����ѭ��\n");
		
		previousPtr=curPtr;	
//		printf("echo:1\n");
		curPtr=curPtr->next;	
//		printf("echo:2\n");
	}

		previousPtr->next=newItem;//ע�� ���ӵķ���ͬ 
//		printf("echo:3\n");
		newItem->next=curPtr;
}


/**********************************************************
�������� void buyGoods
����: ��Ʒ���� ����ǰ�˿� 
����: ��
���ܣ� �ҵ��ض���Ʒ�����빺�ﳵ�� 
**********************************************************/
void buyGood(CustomerList *curCustomer,ProductList *headProduct)
{
	int curCode,quantity;ProductList* curPtr;Description newDescription;
	printf("Enter the code you want to buy:");
	scanf("%d",&curCode);  
	printf("Enter the quantity you want to buy:");
	scanf("%d",&quantity);
	curPtr=getProduct(headProduct,curCode);
	if(curPtr!=NULL)
	{
//		printf("�ҵ�\n");
		newDescription=curPtr->productInfo.description;
		ItemList* newItem=createItem(newDescription,quantity);
		addCart(curCustomer,newItem);
		printf("*****************You have put it in Cart !!****************** !!\n");
		
	}else
	{
		printf("Product Not Found !!\n");
	}
	
}

/**********************************************************
�������� void purchase() 
����: ��Ʒ���� ��ǰ�˿� 
����: ��
���ܣ� ���빺��ҳ�� 
**********************************************************/
void purchase(CustomerList *curCustomer,ProductList *headProduct)
{
	int choice_1_1_1;
	
	printf("************\nEnter 1 to buy\nEnter 0 to exit\nEnter:");
				scanf("%d",&choice_1_1_1);
				
					while(choice_1_1_1)
					{
						if(choice_1_1_1)
							{
									buyGood(curCustomer,headProduct);
								}
							printf("******Enter 1 to buy\n******Enter 0 to exit\nEnter:");
						scanf("%d",&choice_1_1_1);
					
					}
}

/**********************************************************
�������� void sortProduct 
����: ��Ʒ���� 
����: ��
���ܣ� ���ݼ۸���������� 
**********************************************************/
void sortProduct_price(ProductList* headProduct)
{
	ProductList* pb=NULL;
	ProductList* pf;
    struct productInfo temp;
    pf = headProduct->next;

    while(pf->next != NULL) {//��pfָ��Ľڵ�Ϊ��׼�ڵ�
        pb = pf->next;//pb�ӻ�׼�����һ���ڵ㿪ʼ
        while(pb != NULL) {
            if(pf->productInfo.description.price > pb->productInfo.description.price) 
			{
				
                temp = pf->productInfo;
                pf->productInfo = pb->productInfo;
                pb->productInfo = temp;
            }
            pb = pb->next;
        }
        pf = pf->next;
    }
}


void sortProduct_weight(ProductList* headProduct)
{
	ProductList* pb=NULL;
	ProductList* pf;
    struct productInfo temp;
    pf = headProduct->next;

    while(pf->next != NULL) {//��pfָ��Ľڵ�Ϊ��׼�ڵ�
        pb = pf->next;//pb�ӻ�׼�����һ���ڵ㿪ʼ
        while(pb != NULL) {
            if(pf->productInfo.description.weight > pb->productInfo.description.weight) 
			{
				
                temp = pf->productInfo;
                pf->productInfo = pb->productInfo;
                pb->productInfo = temp;
            }
            pb = pb->next;
        }
        pf = pf->next;
    }
}

/**********************************************************
�������� void searchGoods()
����: ��ǰ�˿� ��Ʒ���� 
����: ��
���ܣ� ��ѯ��Ʒ��Ϣ 
**********************************************************/
void searchGoods(CustomerList *curCustomer,ProductList *headProduct)
{
	int choice_1_1;
	char keyWord[15];
	printf("Enter the key word you want to search:");
	scanf("%s",keyWord);
//	printf("echo:4\n");
	electProduct(headProduct,keyWord);
	printf("All related goods shown !!\n");
	//�ж��Ƿ����� while 
	printf("Do you want to show in order?\n");
	instruction_1_1();
	scanf("%d",&choice_1_1);
	while(choice_1_1)
	{
		switch(choice_1_1)
		{
			case 1:
				electProduct(headProduct,keyWord);
				purchase(curCustomer,headProduct);
				instruction_1_1();
				scanf("%d",&choice_1_1);
				system("cls");
				break;
			case 2:
				sortProduct_price(headProduct);
				electProduct(headProduct,keyWord);
				purchase(curCustomer,headProduct);
				instruction_1_1();
				scanf("%d",&choice_1_1);
				system("cls");
				break;
			case 3:
				sortProduct_weight(headProduct);
				electProduct(headProduct,keyWord);
				purchase(curCustomer,headProduct);
				instruction_1_1();
				scanf("%d",&choice_1_1);
				system("cls");
				break;	
			default:
				printf("Invalid Input\n");
				instruction_1_1();
				scanf("%d",&choice_1_1);
				system("cls");
				break;		
		}
	}
	
	
}
//********************************************************************************************
/**********************************************************
�������� CustomerList* createCustomer()
����: ��
����: ��
���ܣ�����ͷ�ڵ� 
**********************************************************/
//�޸ĸ�����Ϣ************************************ 
void instruction_1()
{
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("++++++Enter 1 to Search the goods++++++++\n");
		printf("++++++Enter 2 to Check the Shopping Cart++++++++\n");
		printf("++++++Enter 3 to Set your personal infomation++++++++\n");
		printf("++++++Enter 4 to glance the recommended product+++++++\n");
		printf("++++++Enter 0 to exit the user version++++++++\n");	
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}
void instruction_1_3()
{
	printf("===============================================\n");
	printf("=================Set Your Infomation================\n");
	printf("========Enter 1 to become a VIP===========\n");
	printf("========Enter 2 to set your password===========\n");
	printf("========Enter 3 to check your balance===========\n");
	printf("========Enter 0 to back================\n");
	printf("===============================================\n");	
}
void instruction_1_3_2()
{
	printf("*************************************************\n");
	printf("***********Check Your Balance**************\n");
	printf("*******Enter 1 to show your balance**************\n");
	printf("*******Enter 2 to top up ***********************\n");
	printf("*******Enter 0 to back************************\n");
	printf("*************************************************\n");
}
void setVIP(CustomerList* curCustomer)
{
	if(curCustomer->customer.isVIP==2)
	{
		printf("You have already been a VIP\n");
	}else
	{
		if(curCustomer->customer.balance>=500)
		{
			curCustomer->customer.balance-=500;
			curCustomer->customer.isVIP=2;
			printf("*************************\n");
			printf("You Have Become a VIP !!! \n");
			printf("*************************\n");
		}	else
			{
				printf("Not enough balance, Please top up\n");
			}
	}
}
void setPwd(CustomerList* curCustomer)
{
	
	printf("Enter the new password\n");
	int pwd;
	
	scanf("%6d",&pwd);	
	while(pwd<99999 || pwd>999999);
	{
		printf("invalid input\n");
		scanf("%6d",&pwd);
	}
	curCustomer->customer.password=pwd;
	printf("****************************************\n"); 
	printf("You have set your new password: %d\nPlease keep remind\n",curCustomer->customer.password);
	printf("****************************************\n");
}

void checkBalance(CustomerList* curCustomer)
{
	int choice_1_3_2;
	printf("You balance is %lf",curCustomer->customer.balance);
	printf("Do you want to top up?\n");
	printf("Enter 0 for no\t Enter 1 for yes\n");
	scanf("%1d",&choice_1_3_2);
	if(choice_1_3_2)
	{
		printf("Enter the amount you want to top up:");
		double amount;
		scanf("%lf",&amount);
		while(amount<=0)
		{
			printf("Invalid Input\n");
			scanf("%lf",&amount);
		}
		curCustomer->customer.balance+=amount;
	}
}

/**********************************************************
�������� void setUserInfo 
����: ��ǰ�˿� 
����: �� 
���ܣ� �޸ĵ�ǰ�˿���Ϣ 
**********************************************************/
void setUserInfo(CustomerList* curCustomer)
{
	int choice_1_3;
	instruction_1_3();
	scanf("%d",&choice_1_3);
	system("cls");
	while(choice_1_3!=0)
	{
		switch(choice_1_3)
		{
			case 1:
				setVIP(curCustomer);
	instruction_1_3();
	scanf("%d",&choice_1_3);
	system("cls");
				break;
			case 2:
			setPwd(curCustomer); 
	instruction_1_3();
	scanf("%d",&choice_1_3);
	system("cls");
				break;
			case 3:
			checkBalance(curCustomer);
	instruction_1_3();
	scanf("%d",&choice_1_3);
	system("cls");
				break;	
			default: 
			printf("Invalid Input\n");break;		
				
		}	
	}
}

/**********************************************************
�������� user_hall
����: �˿�����  ��ǰ�˿�  ��Ʒ����  ���ۼ�¼���� 
����: �� 
���ܣ� �����û�ҳ�� 
**********************************************************/
void user_hall(CustomerList* headCustomer,CustomerList* curCustomer,ProductList* headProduct,RecordList* headRecord)
{
	int choice_1;
	instruction_1();

	curCustomer->customer.shoppingCart=(ItemList*)malloc(sizeof(ItemList));
	curCustomer->customer.shoppingCart->next=NULL;
	
	scanf("%1d",&choice_1);	
	system("cls");
	while(choice_1!=0)
	{
		switch(choice_1)
		{
			case 1:
					searchGoods(curCustomer,headProduct);
					instruction_1();
				scanf("%1d",&choice_1);	
				system("cls");
				break;
			case 2:
				setCart(curCustomer,headProduct,headRecord);
				instruction_1();
				scanf("%1d",&choice_1);	
				system("cls");
				break;
			case 3:
				
				setUserInfo(curCustomer);
				instruction_1();
				scanf("%1d",&choice_1);	
				system("cls");
				break;
			case 4:
				ShoppingRecommend(headRecord,curCustomer,headProduct);
				instruction_1();
				scanf("%1d",&choice_1);	
				system("cls");
			default:
				printf("Invalid Input\n");
				instruction_1();
				scanf("%1d",&choice_1);	
				system("cls");
				break;			
		}
	}
	writeFile_customer(headCustomer);
	writeFile_product(headProduct);

}


/**********************************************************
�������� void recomend
����: ��ǰ�˿�  ���ۼ�¼ͷ�ڵ� 
����: ��
���ܣ� ��ǰ�˿��Ƽ���Ʒ������ʵʩΪ�ṩ��ͬ���͹˿��������ϸߵ���Ʒ 
**********************************************************/
void ShoppingRecommend(RecordList* head,CustomerList* curCustomer,ProductList* headProduct)
{
	int i=0;
	int j=0;//����ð������ 
	int m=0;//����ð������	
	int mid1;
	int mid2;
	int zhonglei=0; //���ڼ�¼��Ʒ�������� 
	FILE *fp;
	fp=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\��Ʒ����.txt","r");
	ProductList PL;
	readFile_record(head);
	RecordList*p=head->next;
	CountRecord curCount[5];
	CountRecord mid[5];
//	int choice[Max]	;
//	for(i=0;i<Max;i++)
//	{
//		choice[i]=0;
//	}
	if(fp==NULL)
	{
		printf("Error\n");
		return;
	}
	for(i=0;i<5;i++)
	{
		curCount[i].countCustomerSalary=i;

	}
    if(fgetc(fp)!=EOF)   
    { 
 		i=0;
 		for(i;i<5;i++)
 		{
			for(j=0;j<Max;j++)
			{
				curCount[i].countID[j].code=0;
				curCount[i].countID[j].countTotal=0;			
			} 			
		 }
    
   	  fseek(fp,0,SEEK_SET);
   	  fread(&PL,sizeof(ProductList),1,fp); 
   	  
   	  while (feof(fp)==0)//�ж��Ƿ���� 
   	  {
   	  	fread(&PL,sizeof(ProductList),1,fp);
   	  		for(i=0;i<5;i++)
   	  		{
   		  			curCount[i].countID[zhonglei].code=PL.productInfo.description.code;			
			 }
		zhonglei++;	 			
		}
	} fclose(fp);

	while(p)
	{
		for(i=0;i<5;i++)
		{
			if(p->record.customerSalary==curCount[i].countCustomerSalary)
			{
				for(m=0;m<Max;m++)
				{
					if(curCount[i].countID[m].code==p->record.item.description.code)
					{
						curCount[i].countID[m].countTotal+=p->record.item.quantity;
//						printf("%d\n",m);
					}
				}
			}
		}
		p=p->next;
	}
	for(i=0;i<5;i++)
	{
		j=0;
		for(j;j<Max-1;j++)
		{
			for(m=j+1;m<Max;m++)
			{
				if(curCount[i].countID[j].countTotal<curCount[i].countID[m].countTotal)
				{
					mid1=curCount[i].countID[j].countTotal;
					mid2=curCount[i].countID[j].code;
					curCount[i].countID[j].countTotal=curCount[i].countID[m].countTotal;
					curCount[i].countID[j].code=curCount[i].countID[m].code;
					curCount[i].countID[m].countTotal=mid1;
					curCount[i].countID[m].code=mid2;					
				}
			}
		} 	
	}

//	printf("%d",curCount[3].countID[3].countTotal);
	int counter;
	printf("%d",curCount[curCustomer->customer.salary].countID[3].code);
	for(counter=0;counter<5;counter++)
	{
		ProductList* curProduct=getProduct(headProduct,curCount[curCustomer->customer.salary].countID[counter].code);
		showProductInfo(curProduct);
	}
	
}
int setAdministrator(int account)
{
	Administrator p1;
  int i=0,mima=0,u=0,k=0;
  FILE * fp = fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test.txt", "r+");
  FILE * fp1 = fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\lingshi.txt", "w+");//��д�½�һ����ʱ�ļ�
  if(fp==NULL||fp1==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
  if(fgetc(fp)!=EOF)   
   {
   	fseek(fp,0,SEEK_SET);
	fread(&p1,sizeof(Administrator),1,fp);
    while (feof(fp)==0)//�ж��Ƿ���� 
    {
        if (p1.account==account)//����Ҫɾ��������,��д�롣
        {
	      do 
	     {
	        u=0,k=0;
	        printf("������������(6λ����)����\n");
	        i=scanf("%d",&mima);   //�������� 
	        if((i!=1)||(mima<=99999)||(mima>999999))//||(kind!=1&&kind!=2&&kind!=3))//�ж������Ƿ���ȷ 
	      {
	  	     do    
	  	    {
	  	      setbuf(stdin, NULL);
		      if(u==0)
		      {	
		      printf("�����������1�������룬����2�˳�\n");
		      u++;	  
		      }   
              scanf("%d",&k);
              setbuf(stdin, NULL);
	  	      if(k==1||k==2)    //ֱ���û�������ȷΪֹ 
	  	      {
	  	  	    break;	
		       }
	  	    }while(1);     //ֱ���û�������ȷΪֹ 
	  	    if(k==2)
	  	    {
	  		    return 0 ;     //�˳�����������NULL 
		    }
          }
         }while(k==1);
      	    
      	    printf("�����������%d\n",mima);
      	    p1.password=mima;
      	    fwrite(&p1,sizeof(Administrator),1,fp1);
      	    printf("�޸ĳɹ�������\n");
            i++;
        }
        else
        {
      	  fwrite(&p1, sizeof(Administrator), 1, fp1);
	    }
        fread(&p1,sizeof(Administrator),1,fp);
    }

    if(i==0)
   {
  	 printf("�޸�ʧ�ܣ�����\n");
   }
  }
  else
  {
  	printf("����Ա�浵������!!!\n");
  }
    fclose(fp);
    fclose(fp1);
    int p=remove("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\����Ա����.txt");       
    rename("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\lingshi.txt","D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\����Ա����.txt");
}

void loginUser()
{
	int choice_login;
	CustomerList* headCustomer=creatHeadCustomer();
	CustomerList* curCustomer;
	ProductList* headProduct=createHeadProduct();
	RecordList* headRecord=createHeadRecord();
	readFile_record(headRecord);
	readFile_product(headProduct);	
	readFile_customer(headCustomer,"D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\customerList.txt");
	curCustomer= login_user(headCustomer);
	user_hall(headCustomer,curCustomer,headProduct,headRecord);
}

/********************************************************************************/


void Login()
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
			scanf("%d",&choice);
		}
		setbuf(stdin,NULL);
		switch(choice)
		{
			case 0:
				break;
			case 1:
				 i=LoginSuperAdministrator();
				break;
			case 2:
				{
				 	k=LoginAdministrator();
//				 	k=loginAdmin();
					break;					
				}

			case 3:
				loginUser();
				break;
			default: 
				 break;	
		}
		if(choice==0)
		{
			break;
		}
	 		
	}	
}
int main()
{
//	Administrator * AD;
//	AD=createAdministrator();
//	FILE * test=fopen("D:\\ѧϰ����\\���ʵѵ\\���̹���ϵͳ\\����Ա����.txt","a+");
//	fwrite(AD,sizeof(Administrator),1,test);
//	fclose(test);
	Login();
	return 0;
}
