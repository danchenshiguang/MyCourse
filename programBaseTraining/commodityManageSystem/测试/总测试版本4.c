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
商品变量 
********************************************************************************************/ 
struct description
{
	char name[15];
	int code;//4位 
	double price;//售价	
	double weight;
	int kind;//1-3
};typedef struct description Description;
struct productInfo
{
	Description description;
	int stock;//库存数量 
	double cost;//成本
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
	int quantity;//购买的数量 
};typedef struct item Item;
struct discountCoupon//优惠券结构体 
{
	int kind;
	float discount;//折扣 
};typedef  struct discountCoupon DiscountCoupon;
struct itemList
{
	Item item;
	struct itemList *next;
};typedef struct itemList ItemList;

/*****************************************************************************************
顾客变量 
*****************************************************************************************/ 

struct customer
{
	ItemList *shoppingCart;
	char name[10];
	int ID;//6位数 
	int password;// 6位数 
	int gender;//1:female  2:male
	int isVIP;//1:no  2:yes
	double vipDiscount;
	long long telNum; 
	double balance;
	int package;//1:yes 0:no
	double packageFee;
	int salary;//1:<3000   2:3000-6000 3:6000-10000 4:10000-20000 5:>20000
	DiscountCoupon discountCoupon[10];//优惠卷数量有限制 
};typedef struct customer Customer;

 

struct customerList		//	创建顾客名单  链表 
{
	Customer customer;
	struct customerList  *next;	
};typedef  struct customerList CustomerList;

/************************************************************************************************
超级管理员变量 
***********************************************************************************************/ 

struct superAdministrator//超级管理员的结构体 
{
	int account;//超级管理员的账户 	int 6位数 
	int password;//超级管理员的密码    int 6位数 
	struct superAdministrator *next;//指向下一个超级管理员的指针 
};typedef  struct superAdministrator  SuperAdministrator;

/*******************************************************************************************
管理员变量
***********************************************************************************************/ 
struct administrator//管理员的结构体 
{
	int account;//6位数 
	int password;//6位数 
	char name[10];
	int gender;//1表示男，2表示女 
	long long  telNum;//11位 
	double salary;//3000起步
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
	long long countTotal; //购买商品总数 
};typedef struct countID CountID;
struct countRecord
{
	CountID  countID[Max];//商品种类（ID)
	int countCustomerSalary;//记录顾客种类 
};typedef struct countRecord CountRecord;
/********函数声明********************************/ 

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

超级管理员————————超级管理员部分函数 

*************************************************************************************************************/


/***************************
函数名： superAdministratorCreateList() 功能：创建超级管理员名单链表   头节点 
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
 函数名： createSuperAdministrator()   功能：创建一个超级管理员的链表单位 
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
函数名   wandSuperAdministrator()    功能：将文件中的超级管理员的信息存入一个链表单位 
*****************************/
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

/***************************************
readFile_SuperAdministrator()    功能：从文件中读取超级管理员数据 
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
 函数名：  changeSuAdminPassword()  功能： 修改超级管理员密码
************************************/
void changeSuAdminPassword(SuperAdministrator*head)
{
	readFile_SuperAdministrator(head,"D:\\学习材料\\软件实训\\电商管理系统\\超级管理员名单.txt");
	SuperAdministrator *p=head->next;
	
//	while(p)
//	{
//		printf("%d",p->account);
//		printf("%d",p->password);
//		p=p->next;
//	}
//	p=head->next;
	FILE * fp;
	fp=fopen("D:\\学习材料\\软件实训\\电商管理系统\\超级管理员名单.txt","w+");
	if(fp==NULL)
	{
		printf("文件打开失败\n");
		exit(0);
	}
	int account=0;
	int password=0;
	while(1)
	{
		int isRight1=0;
		int newPassword1=0;
		int newPassword2=-1;
		printf("请输入超级管理员账户\n?");
		scanf("%d",&account);
		printf("请输入超级管理员密码\n?");
		scanf("%d",&password);
		while(account!=p->account&&password!=p->password)
		{
			p=p->next;
			if(p==NULL)
			{
				printf("验证失败，请重试");
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
			printf("请输入新密码\n?");
			scanf("%d",&newPassword1);
			printf("请再次输入新密码\n?");
			scanf("%d",&newPassword2);
			if(newPassword1==newPassword2&&(newPassword1<1000000&&newPassword1>=100000))
			{
				p->password=newPassword1;
				printf("修改密码成功\n");
				break;
			}
			else
			{
				printf("输入错误请重试\n"); 
				printf("1>退出  2>重试\n?"); 
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



超级管理员————————管理员部分函数 



*************************************************************************************************************/

/*********************************
wandSuperAdministrator()     功能： 将文件中管理员的信息存入一个链表单位 
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
	 //判断，当前节点的指针是否为空
	while (p->next!=NULL) 
	{
		p=p->next;
	}
	p->next=newNode;
 } 
/*************************************
readFile_Administrator()	功能：从文件中读取管理员数据
**********************************/
 void readFile_Administrator(Administrator* headAdministrator,char *fileName)
{
	Administrator *node=(Administrator *)malloc(sizeof(Administrator));
	int account=0;
	int password=0;
	char name[10];
	int gender=0;
	long long  telNum=0;//11位 
	double salary;//3000起步
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
函数名：administratorCreateList() 功能：创建管理员名单链表    头节点 
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
函数名： createAdministrator()   功能： 创建一个管理员的链表单位 
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
		while(1)//添加账户 
		{
			int n=0;
			int isSix=0;
			printf("请输入要添加管理员的账户：\n");
			printf("?") ;
			scanf("%d",&account);
			printf("\n您输入的是:%d\n",account);
			n=account;
			while(n!=0)//判断输入是否为六位整数 
			{
				n/=10;
				isSix++;
			}
			if(isSix!=6)
			{
				int is=-1; 
				printf("输入错误，请重试\n");
				printf("退出请按0,继续按1\n");
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
		while(1)//添加密码 
		{
			int n=0;
			int isSix=0;	
			printf("请输入要添加管理员的密码：\n");
			printf("?") ;
			scanf("%d",&password);
			printf("\n您输入的密码是:%d\n",password);
			n=password;
			while(n!=0)//判断输入是否为六位整数 
			{
				n/=10;
				isSix++;
			}
			if(isSix!=6)
			{
				int is=-1; 
				printf("输入错误，请重试\n");
				printf("退出请按0,继续按1\n");
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
		while(1)//添加管理员的姓名 
		{	
			printf("请输入要添加管理员的姓名:\n");
			printf("?") ;
			scanf("%s",name);
			printf("\n您输入的名字是:%s\n",name);
			int length =strlen(name);
			//判断输入的名字是否合法 
			if(length<1)
			{
				int is=-1; 
				printf("名字输入错误，请重试\n");
				printf("退出请按0,继续按1\n");
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
		while(1)//添加管理员的性别 
		{	
			printf("请输入要添加管理员的性别\n1男2女");
			printf("?");
			scanf("%d",&gender);
			setbuf(stdin,NULL);
			//判断输入的性别是否合法 
			if(gender==1)
			{
				printf("您输入的管理员性别为男\n");
				isFull++;					
				break;
			}
			else if(gender==2)
			{
				printf("您输入的管理员性别为女\n");
				isFull++;				
				break;
			}
			else
			{
				printf("输入错误，请重试");
				continue;
			}	

			break;	
		}
		//添加管理员的电话号码 
			while(1)
		{
			long long n=0;
			int isEleven=0;
			printf("请输入要添加管理员的电话号码：\n");
			printf("?") ;
			scanf("%lld",&telNum);
			printf("\n您输入的电话号码是:%lld\n",telNum);
			n=telNum;
			while(n!=0)//判断输入是否为十一位整数 
			{
				n/=10;
				isEleven++;
			}
			if(isEleven!=11)
			{
				int is=-1; 
				printf("输入错误，请重试\n");
				printf("退出请按0,继续按1\n");
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
		//添加管理员的薪水 
			while(1)
		{
			printf("请输入要添加管理员的薪水\n");
			printf("?") ;
			scanf("%lf",&salary);
			printf("\n您输入的薪水是:%lf\n",salary);
			if(salary<=3000)
			{
				int is;
				printf("输入薪水过少，请重试\n");
				printf("退出请按0,继续按1\n");
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
			printf("必填信息不能为空，请重试\n");		
		}	
	}
	//为链表的各项参数赋值 
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
函数：changeAdiministratorInfo()   功能：超级管理员登录界面，修改管理员的信息 
*********************************************************/ 
void changeAdiministratorInfo(Administrator* head)
{
	readFile_Administrator(head,"D:\\学习材料\\软件实训\\电商管理系统\\管理员名单.txt");
	FILE *fp;
	int account=0;
	int choice=0;
	int isContinue=0;
	fp=fopen("D:\\学习材料\\软件实训\\电商管理系统\\管理员名单.txt","w+");
	if(fp==NULL)
	{
		printf("文件打开失败\n");
		exit(0); 
	}
	while(1)
	{
		Administrator* p=head->next;
		printf("请输入您想要修改信息的管理员账户\n?");
		scanf("%d",&account);
		if(account<1000000&&account>99999)
		{
			printf("您想要修改账户为%d的管理员信息\n",account);
		}
		else
		{
			printf("您的输入有误，请重试\n");
			continue;
		}
		if(head->next==NULL)//判断链表是否为空 
		{
			printf("链表为空\n");
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
					printf("请输入您的选择\n");
					printf("1>性别\n");	
					printf("2>电话\n");	
					printf("3>薪水\n");
					printf("4>退出\n?");
					scanf("%d",&choice);
					switch(choice)
					{
						case 1:
						{
							printf("请输入新的管理员性别");
							scanf("%d",&gender);
							if(gender==1&&gender==2)
							{
								p->gender=gender;
								printf("修改成功，即将回到主界面\n");
							}
							else
							{
								printf("您的输入有误，请重试");
								wrongEnter=1; 
							}
							break;							
						}
						case 2:
						{
							printf("请输入新的管理员电话");
							scanf("%lld",&telNum);
							if(telNum<100000000000&&telNum>9999999999)
							{
								p->telNum=telNum;
								printf("修改成功，即将回到主界面\n");								
							}
							else
							{
								printf("您的输入有误，请重试");
								wrongEnter=1; 								 
							}
							break;							
						}
						case 3:
						{
							printf("请输入新的管理员薪水");
							printf("修改成功，即将回到主界面\n");							
							scanf("%lf",&salary);
							if(salary>=3000.0)
							{
								p->salary=salary;
							}
							else
							{
								printf("您输入的薪水过少，请重试"); 
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
				printf("您想要修改账户为%d的管理员不存在\n",account);
				printf("是否重试\n1>继续  2>退出\n?");
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
					printf("您的输入有误，将退出\n");
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
函数 addAdministrator()   功能：添加管理员的链表单位，并将管理员信息存入文件 
*******************************************/ 
void  addAdministrator(Administrator*headAdministrator)//添加管理员函数 
{
	readFile_Administrator(headAdministrator,"D:\\学习材料\\软件实训\\电商管理系统\\管理员名单.txt");
	FILE *fp;
	fp=fopen("D:\\学习材料\\软件实训\\电商管理系统\\管理员名单.txt","a+") ;
	if(fp==NULL)
	{
		printf("文件打开失败\n");
		exit(0); 
	}
	Administrator* newNode;
	int isContinue=-1; 
	//判断管理员添加是否继续 
	while(1)
	{
			int isRepeated=0;
		
			printf("现在开始管理员的添加\n");
			newNode=createAdministrator();	
			Administrator* p=headAdministrator->next;
			//遍历链表，查看是否有相同管理员
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
					printf("您输入的管理员信息重复了，\n1>重试2>退出  按任意其他键重试\n?");
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

		//将新的链表单位加入链表 
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
		printf("添加完成，是否继续添加管理员\n");
		printf("1>继续  2>退出\n?");
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
removeAdministrator()  功能：超级管理员删除管理员信息 
************************************************************/
void  removeAdministrator(Administrator*headAdministrator)
{
	readFile_Administrator(headAdministrator,"D:\\学习材料\\软件实训\\电商管理系统\\管理员名单.txt");
	FILE *fp;
	fp=fopen("D:\\学习材料\\软件实训\\电商管理系统\\管理员名单.txt","w+") ;
	int account=0;
	int account1=-1;
	int isContinue=0;
	int isContinue1=0;	
	if(fp==NULL)
	{
		printf("文件打开失败\n");
		exit(0); 
	}
	while(1)
	{
		Administrator* p=headAdministrator->next;
		Administrator*t=headAdministrator;
		printf("请输入您想要删除的管理员的账户\n?");
		scanf("%d",&account);
		printf("请再次输入您想要删除的管理员的账户\n?");
		scanf("%d",&account1);
		if(account==account1&&(account<1000000&&account>99999))
		{
			printf("您想要删除的管理员账户为%d\n",account);
		}
		else
		{
			system("cls");
			printf("您的输入有误，1>退出  按其他任意键重试\n？");
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
		if(headAdministrator->next==NULL)//判断链表是否为空 
		{
			printf("链表为空\n");
		}
		while(p)
		{
			if(p->account==account)
			{
				t->next=p->next;
				system("cls");
				printf("您成功删除账户为%d的管理员\n",p->account);
				free(p);
				p=NULL;
				break;
			}
			t=p;
			p=p->next;
		}
		
		if(p==NULL&&t==NULL)
		{
			printf("遍历完，您想要删除的管理员账户不存在\n");
			printf("是否重试\n1>继续  2>退出   按其他任意键重试\n?");
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
				printf("您的输入有误，将退出\n");
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
showAdministrator()      功能：超级管理员查看管理员信息 
*******************************************************/
void showAdministrator()
{
	FILE *fp;
	fp=fopen("D:\\学习材料\\软件实训\\电商管理系统\\管理员名单.txt", "r+");
	Administrator *Admin=(Administrator*)malloc(sizeof(Administrator));
	if(fp==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
    //fread(&PL,sizeof(ProductList),1,test1); 
    if(fgetc(fp)!=EOF)   
    { 
   	  fseek(fp,0,SEEK_SET);
   	  fread(Admin,sizeof(Administrator),1,fp); 
//   	  printf("%d\n",feof(fp));
//   	  	printf("账户：%d\n密码：%d\n姓名：%s\n性别：%d\n电话：%lld\n薪水：%lf\n",Admin->account,Admin->password,Admin->name,Admin->gender,Admin->telNum,Admin->salary);
//   	  printf("%d",Admin->account);
   	  
   	  while (feof(fp)==0)//判断是否读完 
   	  {
   	  	printf("账户：%d\n密码：%d\n姓名：%s\n性别：%d\n电话：%lld\n薪水：%.2lf\n",Admin->account,Admin->password,Admin->name,Admin->gender,Admin->telNum,Admin->salary);
   	  	printf("***************************************************************************\n");
   	  	fread(&Admin,sizeof(Administrator),1,fp); 
	  }
	  printf("\n..........查询完毕...............\n");	  
    }
    else
    {
    	printf("管理员名单为空！！！\n\n");
	}
	fclose(fp);
}

/***********************************************************************************************************



超级管理员————————顾客部分函数 



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
CustomerList* creatHeadCustomer()     功能:为顾客 创建 链表头节点 
*******************************************************/
CustomerList* creatHeadCustomer()//头节点 指针 
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
函数名：void readFile_customer(CustomerList* headCustomer,char *fileName)  功能：从文件中读取出顾客信息 
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
函数名：void wand(CustomerList *headCustomer,Customer newCustomer)  功能：将文件中读取出的顾客信息存入链表 
********************************************/
void wand(CustomerList *headCustomer,Customer newCustomer)
{
//	printf("进入wand\n");
	
	CustomerList* newPtr=createNode(newCustomer);
//	printf("wand_get: %6d\n",newPtr->customer.ID);//ok
	CustomerList* curPtr=headCustomer;
	CustomerList* previousPtr=NULL;
	while(curPtr!=NULL)
	{
//		printf("进入循环\n");
		
		previousPtr=curPtr;	
//		printf("echo:1\n");
		curPtr=curPtr->next;	
//		printf("echo:2\n");
	}

				previousPtr->next=newPtr;//注意 连接的方向不同 
//				printf("echo:3\n");
			newPtr->next=curPtr;
//			printf("echo:4\n");	
//			printf("%6d\n",newPtr->customer.ID);
//			printf("%6d\n",previousPtr->next->customer.ID);

//	printf("Done_wand\n");	
}
/********************************
函数名：setVIPDiscount （）  功能：超级管理员登录超级管理员界面，修改会员享有的折扣 
*********************************/ 
void setVIPDiscount(CustomerList*headCustomer)
{
	 readFile_customer( headCustomer,"D:\\学习材料\\软件实训\\电商管理系统\\customerList.txt");
	 CustomerList *p=headCustomer->next;
	 int choice=-1;
	 double disCount=1.0;
	 FILE *fp;
	 fp=fopen("D:\\学习材料\\软件实训\\电商管理系统\\customerList.txt","w+");
	 if(fp==NULL)
	 {
	 	printf("文件打开失败");
	 	exit(0);
	 }
	 while(1)
	 {
	 	printf("是否修改会员享有的折扣");
		printf("1>确定  2>退出  按其他任意键重试\n?");
		scanf("%d",&choice);
		if(choice==1)
		{
			printf("请输入会员折扣\n?");
			scanf("%lf",&disCount);
			if(disCount<=0&&disCount>1)
			{
				printf("您的输入有误，请重试");
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
		 	 printf("您已成功完成修改,将返回主界面\n");
		}
		else if(choice==2)
		{
			break;
		}
		else if(choice!=1&&choice!=2)
		{
			printf("重试\n");
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
函数名：setCouponDiscount （）  功能：超级管理员登录超级管理员界面，修改顾客使用优惠券享有的折扣 
*********************************/ 
void setCouponDiscount(CustomerList*curCustomer)
{
	 readFile_customer( curCustomer,"D:\\学习材料\\软件实训\\电商管理系统\\customerList.txt");
	 CustomerList *p=curCustomer->next;
	 int choice=-1;
	 float couponDiscount=1;
	 int kind=0;
	 FILE *fp;
	 fp=fopen("D:\\学习材料\\软件实训\\电商管理系统\\customerList.txt","w+");
	 if(fp==NULL)
	 {
	 	printf("文件打开失败");
	 	exit(0);
	 }
	 while(1)
	 {
	 	printf("是否修改优惠券享有的折扣");
		printf("1>确定  2>退出\n 按任意其他键重试?");
		scanf("%d",&choice);
		if(choice==1)
		{
			printf("请输入想要修改折扣的优惠券种类:输入1-3：");
			scanf("%d",&kind);
			if(kind!=1&&kind!=2&&kind!=3)
			{
				printf("您的输入有误，请重试");
				continue;
			}			
			printf("请输入优惠券折扣\n?");
			scanf("%f",&couponDiscount);
			if(couponDiscount<=0&&couponDiscount>1)
			{
				printf("您的输入有误，请重试");
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
			 printf("您已成功完成修改,将返回主界面\n");
		}
		else if(choice==2)
		{
			break;
		}
		else if(choice!=1&&choice!=2)
		{
			printf("重试\n");
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
showCustomerList()       功能：查询顾客信息 
******************************************/
void showCustomerList()
{
	FILE *fp;
	fp=fopen("D:\\学习材料\\软件实训\\电商管理系统\\customerList.txt", "r+");
	Customer curCustomer;
	if(fp==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
    //fread(&PL,sizeof(ProductList),1,test1); 
    if(fgetc(fp)!=EOF)   
    { 
   	  fseek(fp,0,SEEK_SET);
   	  fread(&curCustomer,sizeof(Customer),1,fp); 
   	  while (feof(fp)==0)//判断是否读完 
   	  {
   	  	int i=0;
   	  	int a=0;//用来记录顾客优惠券数量 
   	  	int b=0;
   	  	int c=0;   	  	
   	  	printf("ID：%d\n姓名：%s\n性别：%d\n电话：%lld\n薪水：%lf\n是否VIP：%d\n",curCustomer.ID,curCustomer.name,curCustomer.gender,curCustomer.telNum,curCustomer.salary,curCustomer.isVIP,curCustomer.vipDiscount);
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
   	  		printf("本顾客持有的优惠券为\n");
   	  		printf("1...........%d张\n",a);
   	  		printf("2...........%d张\n",b); 
   	  		printf("3...........%d张\n",c); 				 				  		 
   	  	printf("\n***************************************************************************\n");
   	  	fread(&curCustomer,sizeof(CustomerList),1,fp); 
	  }
	  printf("\n..........查询完毕...............\n");
    }
    else
    {
    	printf("顾客名单为空！！！\n\n");
	}
	fclose(fp);
}



/*****************************************************************************************************************



超级管理员————商品方面函数 



*****************************************************************************************************************/
/****************************
ProductList  suCreatProduct()  功能：超级管理员创建商品 
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
	  printf("请以空格分隔，依次输入商品编号（4位整型），商品种类（1代表衣物，2代表蔬果，3代表零食），商品库存（整型）\n");
	 // fflush(stdin);
	  i=scanf("%d%d%d",&code,&kind,&stock);   //依次输入 
	  //fflush(stdin);
	  setbuf(stdin, NULL);
	  if((i!=3)||(code<=999)||(code>9999)||(kind!=1&&kind!=2&&kind!=3))//判断输入是否正确 
	  {
	  	
	  	do    
	  	{
	  	  setbuf(stdin, NULL);
		  if(u==0)
		  {	
		  printf("输入错误，输入1重新输入，输入2退出\n");
		  u++;	  
		  }   

		  //printf("%d\n",k);
		  //fflush(stdin);
          scanf("%d",&k);
          //setbuf(stdin, NULL);
          //printf("%d\n",i);

	  	  if(k==1||k==2)    //直到用户输入正确为止 
	  	  {
	  	  	break;	
		  }
	  	}while(1);     //直到用户输入正确为止 
	  	if(k==2)
	  	{
	  		creatProduct.productInfo.description.code=0;
	  		return creatProduct ;     //退出函数，返回NULL 
		}
      }
    }while(k==1);
    do 
	{
		k=0,u=0;
	 printf("请以空格分隔，依次输入价格（双精度浮点数），重量（双精度浮点数） 进价(双精度浮点数)\n");
	  i=scanf("%lf%lf%lf",&price,&weight,&cost);   //依次输入 
	  setbuf(stdin, NULL);
	  if((i!=3)||price<0||weight<0||(cost<0||price<cost))//判断输入是否正确 
	  {
	  	do    
	  	{
		  if(u==0)
		  {	
		  printf("输入错误(原因：1.输入格式不对\n 2.进价大于售价)，\n输入1重新输入，输入2退出\n");
		  u++;	  
		  }   
		  //printf("%d\n",i);
		  //setbuf(stdin, NULL);
          scanf("%d",&k);
          setbuf(stdin, NULL);
	  	  if(k==1||k==2)    //直到用户输入正确为止 
	  	  {
	  	  	break;	
		  }
	  	}while(1);     //直到用户输入正确为止 
	  	if(k==2)
	  	{
	  		creatProduct.productInfo.description.code=0;
	  		return creatProduct ;     //退出函数，返回NULL 
		}
      }
    }while(k==1);
    printf("请输入商品名称\n");
    fgets( creatProduct.productInfo.description.name, 15, stdin);
    setbuf(stdin, NULL);
    //profit=price-cost;管理员无权修改成本 
    creatProduct.productInfo.description.code=code;
    creatProduct.productInfo.stock=stock;
    creatProduct.productInfo.description.kind=kind;
   creatProduct.productInfo.description.price=price;
    creatProduct.productInfo.description.weight=weight;
    creatProduct.productInfo.cost=cost;          //管理员无权修改成本 
    creatProduct.productInfo.profit=price-cost;   //管理员无权修改成本 
    creatProduct.productInfo.sales=0;
	return creatProduct;
}
/********************************************
wandProduct()    功能：超级管理员将创建的商品添加到文件中 
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
//	//FILE * Pr=fopen();//打开文件
//	fread(M,sizeof(ProductList),1,Pr); //从文件中读取结构体; 
	if(PL.productInfo.description.code!=0)
	{
//	  for(;head!=NULL;)
//	  {
//	  	   printf("%d\n",head->productInfo.description.code);
//	       head=head->next;   
//	  }
//	  head->next=&PL;   //遍历到链表末尾； 
//	  for(;S!=NULL;S=S->next)
//	  {
		  FILE * test1=fopen("D:\\学习材料\\软件实训\\电商管理系统\\商品名单.txt","a+");
		  fwrite(&PL,sizeof(ProductList),1,test1);
		  fclose(test1);
//	  }
	      printf("添加成功\n");
    }
    else
    {
    	printf("添加失败！！！\n");
	}
	
		 
}
/****************************************************
showsProduct()    功能：超级管理员查看商品信息 
****************************************************/
void showsProduct()
{
	printf("aaa\n");
	ProductList PL;
	FILE * test1=fopen("D:\\学习材料\\软件实训\\电商管理系统\\商品名单.txt", "r+");
	if(test1==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
    //fread(&PL,sizeof(ProductList),1,test1); 
    if(fgetc(test1)!=EOF)   
    { 
   	  fseek(test1,0,SEEK_SET);
   	  fread(&PL,sizeof(ProductList),1,test1); 
   	  while (feof(test1)==0)//判断是否读完 
   	  {
   	  	printf("商品编号：%d\n商品名称：%s\n商品类型：%.2d\n商品重量：%.2lf\n商品售价：%.2lf\n商品成本：%.2lf\n商品利润：%.2lf\n商品库存：%d\n",PL.productInfo.description.code,PL.productInfo.description.name,PL.productInfo.description.kind,PL.productInfo.description.weight,PL.productInfo.description.price,PL.productInfo.cost,PL.productInfo.profit,PL.productInfo.stock);
   	  	printf("***************************************************************************\n");
   	  	fread(&PL,sizeof(ProductList),1,test1); 
	  }
	  printf("\n..........查询完毕...............\n");	  
    }
    else
    {
    	printf("商品库存为空！！！\n\n");
	}
	fclose(test1);
}
/******************************************
suSetProduct()     功能：超级管理员修改商品信息 
************************************************/ 
void suSetProduct()
{
	printf("请输入需要修改商品的编号\n");
	int code;
	scanf("%d",&code);
	deleteProduct(code);
	printf("\n接下来添加新的商品信息！！\n\n");
	wand_Product();
}
/***********************************************************
deleteProduct()     功能：超级管理员删除商品 
***********************************************************/
//void suDeleteProduct()
//{
//  ProductList p1;
//  int code,i=0;
//  FILE * fp = fopen("D:\\学习材料\\软件实训\\电商管理系统\\商品名单.txt", "r+");
//  FILE * fp1 = fopen("D:\\学习材料\\软件实训\\电商管理系统\\linshi.txt", "w+");//读写新建一个临时文件
//  if(fp==NULL||fp1==NULL)
//     {
//      printf("打开文件失败.\n");
//      exit(0);
//     }
//  if(fgetc(fp)!=EOF)   
//   {
//   	fseek(fp,0,SEEK_SET);
//	fread(&p1,sizeof(ProductList),1,fp);
//    printf("请输入需要删除商品的编号\n");	
//    scanf("%d",&code);
//    while (feof(fp)==0)//判断是否读完 
//    {
//        if (p1.productInfo.description.code==code)//遇到要删除的内容,则不写入。
//        {
//      	    printf("删除成功！！！\n");
//            i++;
//        }
//        else
//        {
//      	  fwrite(&p1, sizeof(ProductList), 1, fp1);
//	    }
//        fread(&p1,sizeof(ProductList),1,fp);
//    }
////      if (p1.productInfo.description.code==code)//遇到要删除的内容,则不写入。防止漏掉最后一个 
////      {
////        printf("删除成功！！！\n");
////        i++;
////      }
////      else
////      {
////         fwrite(&p1, sizeof(ProductList), 1, fp1);
////	  }
//    if(i==0)
//   {
//  	 printf("该商品不存在！！！\n");
//   }
//  }
//  else
//  {
//  	printf("当前商品库存为空!!!\n");
//  }
//    fclose(fp);
//    fclose(fp1);
//    remove("商品名单.txt");                
//    rename("linshi.txt", "test1.txt");
//}
/**********************************************************



---------------------------登录和主界面部分 



**************************************************************/
/***************************************
showInfo()    功能：查询用户，管理员，商品信息 
****************************************/ 
void  showInfo()
{
	while(1)
	{
		int choice=-1;
		printf("请输入您的选择\n");
		printf("1>查询管理员信息\n2>查询顾客信息\n3>查询商品信息\n4>退出\n输入其他键重试\n");
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
			printf("您输入了其他键将重试\n");
			break;			
		}
		if(choice==4)
		{
			break;
		}
		
	}
}
/***************************************************
函数名： LoginSuperAdministrator  功能：超级管理员登录 
*******************************************************/
int LoginSuperAdministrator()
{
	FILE * ad; 
	int a=0;   //保存判断条件 
	int account;
	int password;
//	char string[Max];    //接受用户输入 
//	char suAccount[Max];
//	char suPassword[Max];
//	int view1,view2;//存储字符串转换后的int 
	SuperAdministrator admini;
	int i=0,j=0;
	printf("请输入超级管理员账号\n");
	scanf("%d",&account);
	setbuf(stdin, NULL);
	ad=fopen("D:\\学习材料\\软件实训\\电商管理系统\\超级管理员名单.txt","r+");//打开储存管理员信息的文件
	if(ad==NULL)
     {
      printf("打开文件失败\n");
      exit(0);
     }
     fread(&admini,sizeof(SuperAdministrator),1,ad);
	for(;feof(ad)==0;)
	{
//	    fgets(string,sizeof(string),ad);
//	    for(i=0;i<Max;i++)//将字符串中的信息清空 
//	    {
//	    	suAccount[i]='\0';
//	    	suPassword[i]='\0';
//		 }
//		 for(i=0,j=0;string[i]!='_';i++,j++)//开始分割字符串 
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
			fclose(ad);     //找到对应管理员，关闭文件 
			printf("请输入密码\n");
			scanf("%d",&password);
			setbuf(stdin, NULL);
			int i=0,k=0;    //用于储存判断信息 
			char c;
			if(admini.password==password)
			{
				system("cls");				
				printf("欢迎尊贵的超级管理员登录\n");
				int code=0;				
				while(1)
				{
					printf("******************************************************************\n");
					printf("1>添加管理员\n2>修改管理员信息\n3>删除管理员\n4>查询信息\n5>修改超级管理员密码\n") ;//之后再补充 
					printf("6>添加商品\n7>删除商品\n8>修改商品信息\n") ;
					printf("9>修改优惠券折扣\n10>修改会员折扣\n11>统计商品\n12>退出\n");
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
							printf("请输入您要删除商品的编号\n");

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
                    printf("12层开!\n");
                    return 2;             //输入4，结束登录函数，返回大厅，通过返回值判断是否登录成功。 
                    break;
                    default:
                    printf("该层不存在, 请重新输入\n");
				  }
				}
			}
			else
			{
				printf("输入密码错误，输入2退出，输入任意数字重新输入\n");
				scanf("%d",&k);
				setbuf(stdin, NULL);
				if(k==2)
				{
					return 1;    //用一个int接受返回的值，判断是否登录成功 
				}
			} 
			
			
		}
     fread(&admini,sizeof(SuperAdministrator),1,ad);  //读取下一个 	
	}
	printf("账号错误\n");
	fclose(ad);
	return 2;
}
void wandProduct()
{
	ProductList PL;
	PL=CreatProduct();
	if(PL.productInfo.description.code!=0)
	{

		  FILE * test1=fopen("C:\\Users\\SSS\\Desktop\\实训\\test1.txt","a+");
		  fwrite(&PL,sizeof(ProductList),1,test1);
		  fclose(test1);
	      printf("添加成功\n");
    }
    else
    {
    	printf("添加失败！！！\n");
	}
	
		 
}
/************************************************************************************************/ 
ProductList CreatProduct()
{
	int a=0,b=0,i=0;
	int j=0;   //这两个int用于储存判断信息，用于后续判断 
	int k=0;
	int u=0;
	ProductList  creatProduct;
	char name[15];
	int code,kind,stock;
	double price,weight,cost,profit;
	do 
	{
	  u=0,k=0;
	  printf("请以空格分隔，依次输入商品编号（4位整型），商品种类（1代表衣物，2代表蔬果，3代表零食），商品库存（整型）\n");
	  i=scanf("%d%d%d",&code,&kind,&stock);   //依次输入 
	  if((i!=3)||(code<=999)||(code>9999))//||(kind!=1&&kind!=2&&kind!=3))//判断输入是否正确 
	  {
	  	
	  	do    
	  	{
	  	  setbuf(stdin, NULL);
		  if(u==0)
		  {	
		  printf("输入错误，输入1重新输入，输入2退出\n");
		  u++;	  
		  }   
          scanf("%d",&k);
          setbuf(stdin, NULL);
	  	  if(k==1||k==2)    //直到用户输入正确为止 
	  	  {
	  	  	break;	
		  }
	  	}while(1);     //直到用户输入正确为止 
	  	if(k==2)
	  	{
	  		creatProduct.productInfo.description.code=0;
	  		return creatProduct ;     //退出函数，返回NULL 
		}
      }
    }while(k==1);
    do 
	{
	  k=0,u=0;
	  printf("请以空格分隔，依次输入价格（双精度浮点数），重量（双精度浮点数）\n");
	  i=scanf("%lf%lf",&price,&weight);   //依次输入 
	  if((i!=2)||price<0||weight<0)//判断输入是否正确 
	  {
	  	do    
	  	{
	  	  setbuf(stdin, NULL);
		  if(u==0)
		  {	
		  printf("输入错误，输入1重新输入，输入2退出\n");
		  u++;	  
		  }   
          scanf("%d",&k);
          setbuf(stdin, NULL);
	  	  if(k==1||k==2)    //直到用户输入正确为止 
	  	  {
	  	  	break;	
		  }
	  	}while(1);     //直到用户输入正确为止 
	  	if(k==2)
	  	{
	  		creatProduct.productInfo.description.code=0;
	  		return creatProduct ;     //退出函数，返回NULL 
		}
      }
    }while(k==1);
    printf("请输入商品名称\n");
    setbuf(stdin, NULL);
    fgets(creatProduct.productInfo.description.name, 15, stdin);
    creatProduct.productInfo.description.code=code;
    creatProduct.productInfo.stock=stock;
    creatProduct.productInfo.description.kind=kind;
    creatProduct.productInfo.description.price=price;
    creatProduct.productInfo.description.weight=weight;
    creatProduct.productInfo.cost=0;            //管理员无权修改成本 
    creatProduct.productInfo.profit=0;   //管理员无权修改成本 
    creatProduct.productInfo.sales=0;
    creatProduct.next=NULL;
	return creatProduct;
}

void setProduct(int code)
{
	deleteProduct(code);
	printf("\n接下来添加新的商品信息！！\n\n");
	wandProduct();
}
void deleteProduct(int code)
{
  ProductList p1;
  int i=0;
  FILE * fp = fopen("D:\\学习材料\\软件实训\\电商管理系统\\商品名单.txt", "r+");
  FILE * fp1 = fopen("D:\\学习材料\\软件实训\\电商管理系统\\linshi.txt", "w+");//读写新建一个临时文件
  if(fp==NULL||fp1==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
  if(fgetc(fp)!=EOF)   
   {
   	fseek(fp,0,SEEK_SET);
	fread(&p1,sizeof(ProductList),1,fp);
    while (feof(fp)==0)//判断是否读完 
    {
        if (p1.productInfo.description.code==code)//遇到要删除的内容,则不写入。
        {
      	    printf("删除成功！！！\n");
            i++;
        }
        else
        {
      	  fwrite(&p1, sizeof(ProductList), 1, fp1);
	    }
        fread(&p1,sizeof(ProductList),1,fp);
    }
//      if (p1.productInfo.description.code==code)//遇到要删除的内容,则不写入。防止漏掉最后一个 
//      {
//        printf("删除成功！！！\n");
//        i++;
//      }
//      else
//      {
//         fwrite(&p1, sizeof(ProductList), 1, fp1);
//	  }
    if(i==0)
   {
  	 printf("该商品不存在！！！\n");
   }
  }
  else
  {
  	printf("当前商品库存为空!!!\n");
  }
    fclose(fp);
    fclose(fp1);
    int p=remove("D:\\学习材料\\软件实训\\电商管理系统\\商品名单.txt");       
    rename("D:\\学习材料\\软件实训\\电商管理系统\\linshi.txt","D:\\学习材料\\软件实训\\电商管理系统\\商品名单.txt");
}
void statisticsProduct()
{
	ProductList * D;
	ProductList * A=(ProductList *)malloc(sizeof(ProductList));
	ProductList * B=(ProductList *)malloc(sizeof(ProductList));
	//ProductList * D,C;
	double sum;
	FILE * test1=fopen("D:\\学习材料\\软件实训\\电商管理系统\\商品名单.txt", "r+");
	if(test1==NULL)
     {
      printf("打开文件失败.\n");
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
		printf("\n\n商品总价为:%lf\n\n",sum);
		showsProduct();
		
	}
	else
	{
		printf("商品库存为空！！！\n");
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
	FILE * test1=fopen("D:\\学习材料\\软件实训\\电商管理系统\\商品名单.txt", "r+");
	if(test1==NULL)
     {
      printf("打开文件失败.\n");
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
		printf("                                                 销量排行榜                                         \n");
		while(D!=NULL)
		{
			i++;
			printf("NO.%d:\n",i);
			printf("商品名称：%s\n商品编号：%d\n商品价格：%lf\n商品销量%d\n",D->productInfo.description.name,D->productInfo.description.code,D->productInfo.description.price,D->productInfo.sales);
			printf("************************************************************************************************************\n");
			D=D->next;
		}
		
		
	
	}
	else
	{
		printf("商品库存为空！！！\n");
	}
	fclose(test1);
}

void PsearchRecord(int code)
{
	Record R;
	int i=0;
	FILE * test3=fopen("D:\\学习材料\\软件实训\\电商管理系统\\record.txt", "r+");
	if(test3==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
     if(fgetc(test3)!=EOF)   
    { 
   	  fseek(test3,0,SEEK_SET);
   	  fread(&R,sizeof(Record),1,test3); 
   	  while (feof(test3)==0)//判断是否读完 
   	  {
   	  	if(R.item.description.code==code)
   	  	{
   	  	  printf("商品名称:%s\n商品编号:%d\n购买数量:%d\n",R.item.description.name,R.item.description.code,R.item.quantity);
   	  	  printf("购买人ID：%d\n购买人薪水类别：%d\n",R.customerID,R.customerSalary);
   	  	  printf("***************************************************************************\n");
   	  	  i++;
		}
		fread(&R,sizeof(Record),1,test3); 
	  }
	  if(i==0)
	  {
	  	printf("不存在该商品的销售信息！！！\n");
	  }

    }
    else
    {
    	printf("当前存档顾客为空！！！\n");
	}
	fclose(test3);
}
void CsearchRecord(int ID)
{
	Record R;
	int i=0;
	FILE * test3=fopen("D:\\学习材料\\软件实训\\电商管理系统\\record.txt", "r+");
	if(test3==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
     if(fgetc(test3)!=EOF)   
    { 
   	  fseek(test3,0,SEEK_SET);
   	  fread(&R,sizeof(Record),1,test3); 
   	  while (feof(test3)==0)//判断是否读完 
   	  {
   	  	if(R.customerID==ID)
   	  	{
   	  	  printf("商品名称:%s\n商品编号:%d\n购买数量:%d\n",R.item.description.name,R.item.description.code,R.item.quantity);
   	  	  printf("购买人ID：%d\n购买人薪水类别：%d\n",R.customerID,R.customerSalary);
   	  	  printf("***************************************************************************\n");
   	  	  i++;
		}
		fread(&R,sizeof(Record),1,test3); 
	  }
      if(i==0)
      {
      	printf("不存在该顾客的购买信息！！！\n");
	  }
    }
    else
    {
    	printf("当前存档顾客为空！！！\n");
	}
	fclose(test3);
}
void showsRecord()
{
	Record R;
	FILE * test3=fopen("D:\\学习材料\\软件实训\\电商管理系统\\record.txt", "r+");
	if(test3==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
     if(fgetc(test3)!=EOF)   
    { 
   	  fseek(test3,0,SEEK_SET);
   	  fread(&R,sizeof(Record),1,test3); 
   	  while (feof(test3)==0)//判断是否读完 
   	  {
   	  	printf("商品名称:%s\n商品编号:%d\n购买数量:%d\n",R.item.description.name,R.item.description.code,R.item.quantity);
   	  	printf("购买人ID：%d\n购买人薪水类别：%d\n",R.customerID,R.customerSalary);
   	  	printf("***************************************************************************\n");
   	  	fread(&R,sizeof(Record),1,test3); 
	  }

    }
    else
    {
    	printf("当前存档顾客为空！！！\n");
	}
	fclose(test3);
	
}
void showsVip()
{
	Customer C;
	int i=0;
	FILE * test2=fopen("D:\\学习材料\\软件实训\\电商管理系统\\customerList.txt", "r+");
	if(test2==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
     if(fgetc(test2)!=EOF)   
    { 
   	  fseek(test2,0,SEEK_SET);
   	  fread(&C,sizeof(Customer),1,test2); 
   	  while (feof(test2)==0)//判断是否读完 
   	  {
   	  	if(C.isVIP==2)
   	  	{
   	  	  printf("顾客ID：%d\n顾客名称：%s\n",C.ID,C.name);
   	  	  if(C.gender==1)
   	  	  {
   	  		  printf("顾客性别：女\n"); 
		  }
		  if(C.gender==2)
		  {
			  printf("顾客性别：男\n");
		  }
		  if(C.isVIP==1)
		  {
			  printf("是否VIP：否\n");
		  }
		  if(C.isVIP==2)
		  {
			  printf("是否VIP：是\n");
	 	  }
		  printf("顾客余额:%lf\n顾客月薪类型:%d\n顾客电话号码：%lld\n",C.balance,C.salary,C.telNum);
   	  	  printf("***************************************************************************\n"); 
   	  	  i++;
		}
		fread(&C,sizeof(Customer),1,test2); 
	  }
	  if(i==0)
	  {
	  	printf("不存在Vip顾客！！！\n");
	  }
    }
    else
    {
    	printf("当前存档顾客为空！！！\n");
	}
	fclose(test2);
	
}
void showsCustomer()
{
	Customer C;
	FILE * test2=fopen("D:\\学习材料\\软件实训\\电商管理系统\\customerList.txt", "r+");
	if(test2==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
     if(fgetc(test2)!=EOF)   
    { 
   	  fseek(test2,0,SEEK_SET);
   	  fread(&C,sizeof(Customer),1,test2); 
   	  while (feof(test2)==0)//判断是否读完 
   	  {
   	  	//printf("!!!\n");
   	  	printf("顾客ID：%d\n顾客名称：%s\n",C.ID,C.name);
   	  	if(C.gender==1)
   	  	{
   	  		printf("顾客性别：女\n"); 
		}
		if(C.gender==2)
		{
			printf("顾客性别：男\n");
		}
		if(C.isVIP==1)
		{
			printf("是否VIP：否\n");
		}
		if(C.isVIP==2)
		{
			printf("是否VIP：是\n");
		}
		printf("顾客余额:%lf\n顾客月薪类型:%d\n顾客电话号码：%lld\n",C.balance,C.salary,C.telNum);
   	  	printf("***************************************************************************\n");
   	  	fread(&C,sizeof(Customer),1,test2); 
	  }

    }
    else
    {
    	printf("当前存档顾客为空！！！\n");
	}
	fclose(test2);
	
}
void searchCustomer(int ID)
{
	Customer C;
	int i=0;
	FILE * test2=fopen("D:\\学习材料\\软件实训\\电商管理系统\\customerList.txt", "r+");
	if(test2==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
     if(fgetc(test2)!=EOF)   
    { 
   	  fseek(test2,0,SEEK_SET);
   	  fread(&C,sizeof(Customer),1,test2); 
   	  while (feof(test2)==0)//判断是否读完 
   	  {
   	  	if(C.ID==ID)
   	  	{
   	  	  printf("顾客ID：%d\n顾客名称：%s\n",C.ID,C.name);
   	  	  if(C.gender==1)
   	  	  {
   	  		  printf("顾客性别：女\n"); 
		  }
		  if(C.gender==2)
		  {
			  printf("顾客性别：男\n");
		  }
		  if(C.isVIP==1)
		  {
			  printf("是否VIP：否\n");
		  }
		  if(C.isVIP==2)
		  {
			  printf("是否VIP：是\n");
	 	  }
		  printf("顾客余额:%lf\n顾客月薪类型:%d\n顾客电话号码：%lld\n",C.balance,C.salary,C.telNum);
   	  	  printf("***************************************************************************\n"); 
   	  	  i++;
		}
		fread(&C,sizeof(Customer),1,test2); 
	  }
	  if(i==0)
	  {
	  	printf("该顾客不存在！！！\n");
	  }
    }
    else
    {
    	printf("当前存档顾客为空！！！\n");
	}
	fclose(test2);
	
}
void searchProduct()
{
	int code,i=0;
	printf("请输入商品编号\n");
	scanf("%d",&code);
	setbuf(stdin,NULL);
	ProductList PL;
	FILE * test1=fopen("D:\\学习材料\\软件实训\\电商管理系统\\customerList.txt", "r+");
	if(test1==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
    //fread(&PL,sizeof(ProductList),1,test1); 
    if(fgetc(test1)!=EOF)   
    { 
   	  fseek(test1,0,SEEK_SET);
   	  fread(&PL,sizeof(ProductList),1,test1); 
   	  while (feof(test1)==0)//判断是否读完 
   	  {
   	  	if(PL.productInfo.description.code==code)
   	  	{
			 printf("商品编号：%d\n商品名称：%s\n商品类型：%d\n商品重量：%lf\n商品售价：%lf\n商品成本：%lf\n商品利润：%lf\n商品库存：%d\n",PL.productInfo.description.code,PL.productInfo.description.name,PL.productInfo.description.kind,PL.productInfo.description.weight,PL.productInfo.description.price,PL.productInfo.cost,PL.productInfo.profit,PL.productInfo.stock);
   	  	     printf("***************************************************************************\n");
   	  	     i++;
   	    }
   	    fread(&PL,sizeof(ProductList),1,test1); 
	  }
	  if(i==0)
	  {
	  	printf("该商品不存在！！！\n");
	  }

    }
    else
    {
    	printf("商品库存为空！！！\n");
	}
	fclose(test1);
	
}
ProductList * maopao(ProductList * head)
{
	ProductList *p,*q;
	int num=0,j=0;
	q=head;
	//获取链表的长度 
	while(q!=NULL){
		q=q->next;
		num++;
	}
	//冒泡排序的基本思路 
	int i;
	for(i=0;i<num-1;i++)
		{
			p=q=head; 
			j=num-i-1; //减少每一趟循环中两两比较的次数 
			while(p->next!=NULL&&j!=0){
				j--;
				if(p->productInfo.stock<p->next->productInfo.stock){
					//节点的交换 
					if(p==head) head=p->next;
					else q->next=p->next;
					q->next=p->next;
					q=q->next;
					p->next=q->next;
					q->next=p;
					//执行完上面的过程后，为了能够让p顺利地执行移动到交换后的下一位 . 
					p=q; 
				}
				q=p; //为了能让q保持在p的前面 
				p=p->next; //p指针后移，即p变成了在q的前面 
			}
		}
	return head;
} 
ProductList * Smaopao(ProductList * head)
{
	ProductList *p,*q;
	int num=0,j=0;
	q=head;
	//获取链表的长度 
	while(q!=NULL){
		q=q->next;
		num++;
	}
	//冒泡排序的基本思路 
	int i;
	for(i=0;i<num-1;i++)
		{
			p=q=head; 
			j=num-i-1; //减少每一趟循环中两两比较的次数 
			while(p->next!=NULL&&j!=0){
				j--;
				if(p->productInfo.sales<p->next->productInfo.sales){
					//节点的交换 
					if(p==head) head=p->next;
					else q->next=p->next;
					q->next=p->next;
					q=q->next;
					p->next=q->next;
					q->next=p;
					//执行完上面的过程后，为了能够让p顺利地执行移动到交换后的下一位 . 
					p=q; 
				}
				q=p; //为了能让q保持在p的前面 
				p=p->next; //p指针后移，即p变成了在q的前面 
			}
		}
	return head;
} 

/***************************************************
函数名： LoginAdministrator  功能：管理员登录 
*******************************************************/
int LoginAdministrator()
{
	mciSendString("open D:\\学习材料\\软件实训\\电商管理系统\abc.mp3 alias bkmusic", 0, 0, 0);
	mciSendString("play bkmusic repeat", 0, 0, 0);        //循环播放音乐
	FILE * ad; 
	int a=0;   //保存判断条件 
	int account;
	int password;    //接受用户输入 
	Administrator admini;
	printf("请输入管理员账号\n");
	scanf("%d",&account);
	setbuf(stdin, NULL);
	ad=fopen("D:\\学习材料\\软件实训\\电商管理系统\\管理员名单.txt","r+");//打开储存管理员信息的文件
	if(ad==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
    fread(&admini,sizeof(Administrator),1,ad);
//	printf("%d\n",admini.account) ;//从文件中读取结构体;
//	printf("%d",feof(ad)) ;
	while(feof(ad)==0)
	{
		printf("%d",admini.account);
		//printf("%d\n",admini.account);
		//printf("!!!\n");
		while(admini.account==account)
		{
			fclose(ad);     //找到对应管理员，关闭文件 
			printf("请输入密码\n");
			scanf("%d",&password);
			setbuf(stdin, NULL);
			int i=0,k=0,j=0,m=1;    //用于储存判断信息 
			int code=0,ID=0;
			char c;
			if(password==admini.password)
			{
				system("cls");
				printf("欢迎尊贵的管理员%s登录\n",admini.name);
				//printf("%d\n",sizeof(ProductList));
				
				while(1)
				{
					printf("输入1添加商品\n输入2修改商品\n输入3删除商品\n");
					printf("输入4显示商品\n输入5统计商品，并按库存从多到少排序商品\n输入6查询商品\n输入7显示顾客信息\n输入8显示vip顾客信息\n输入9查询顾客信息\n输入10显示销售信息\n输入11查询销售信息\n输入12按销量排序商品\n输入13关闭/打开音乐\n输入14修改密码\n输入15清屏幕\n输入16退出\n") ;//之后再补充 
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
                    printf("请输入需要修改的商品编号\n");
	                scanf("%d",&code);
                    setProduct(code);
                    break;
                    case 3:
                    printf("请输入需要删除商品的编号\n");	
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
					printf("请输入需要查询的顾客ID\n");
					scanf("%d",&ID);	
					searchCustomer(ID);
					break;	
					case 10:
					showsRecord();
					break;	
					case 11:
					{
					printf("输入1按照购买人ID查询，输入2按照商品编号查询\n");
					scanf("%d",&j);
					if(j==1)
					{
						printf("请输入顾客ID\n");
						scanf("%d",&ID);
						CsearchRecord(ID);
					}
					if(j==2)
					{
						printf("请输入商品编号\n");
						scanf("%d",&code);
						PsearchRecord(code);
					}
					if(j!=1&&j!=2)
					{
						printf("请正确输入！！！\n");
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
                    printf("16层开!\n");
                    return 2;            //输入13，结束登录函数，返回大厅，通过返回值判断是否登录成功。 
                    break;
                    default:
                    printf("该层不存在, 请重新输入\n");
				  }
				}
			}
			else
			{
				printf("输入密码错误，输入2退出，输入任意数字重新输入\n");
				scanf("%d",&k);
				setbuf(stdin, NULL);
				if(k==2)
				{
					return 1;    //用一个int接受返回的值，判断是否登录成功 
				}
			} 
			
			
		}
		fread(&admini,sizeof(Administrator),1,ad);    //读取下一个 
		
	}

	fclose(ad);    //找不到，关闭文件 
	printf("该管理员账户不存在\n"); 
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
	previousPtr->next=newPtr;//注意 连接的方向不同 
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
		if((fp=fopen("D:\\学习材料\\软件实训\\电商管理系统\\record.txt","w"))!=NULL)
	{
		printf("error");
	}
	
		while(curPtr!=NULL)
	{
//		printf("进入写文件循环\n");
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
	FILE * fp=fopen("D:\\学习材料\\软件实训\\电商管理系统\\商品名单.txt", "r+");
	if(fp==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
     
    if(fgetc(fp)!=EOF)   
    { 
   	  	fseek(fp,0,SEEK_SET);
   	  	fread(&PL,sizeof(ProductList),1,fp); 
   	  	while (feof(fp)==0)/*判断是否读完*/ 
   	  	{
   	  		plf=PL.productInfo;
   	  		wand_product(headProduct,plf);
   	  		fread(&PL,sizeof(ProductList),1,fp); 
	  	}
    }
    	else
   	 {
    	printf("商品库存为空！！！\n");
		}
//	printList_product(headProduct);
	
}

void readFile_record(RecordList* headRecord)
{
	
	Record newRecord;
	FILE *fp;char ch;

	if((fp=fopen("D:\\学习材料\\软件实训\\电商管理系统\\record.txt","r"))==NULL)
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
//	printf("进入写文件\n");
	ProductList* curPtr=headProduct->next;
	if(headProduct!=NULL)
	{
//		printf("Notempty\n");
	}//ok 
	FILE * rt;
	
	if((rt=fopen("D:\\学习材料\\软件实训\\电商管理系统\\商品名单.txt","w"))!=NULL)
	{
//		printf("error");
	}
	
//	printf("openFile\n");
	while(curPtr!=NULL)
	{
//		printf("进入写文件循环\n");
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
//	printf("进入写文件\n");
	CustomerList* curPtr=headCustomer->next;
	if(headCustomer!=NULL)
	{
//		printf("Notempty\n");
	}//ok 
	FILE * rt;
	
	if((rt=fopen("D:\\学习材料\\软件实训\\电商管理系统\\customerList.txt","w"))!=NULL)
	{
//		printf("error");
	}
	
//	printf("openFile\n");
	while(curPtr!=NULL)
	{
//		printf("进入写文件循环\n");
		fwrite(&(curPtr->customer), sizeof(Customer), 1, rt);
		curPtr=curPtr->next;
	}
//	printf("Done_write\n");
	fclose(rt);
}
//************************** *******************************************************************

//注册登录************************************************************ 
void registering(CustomerList* headCustomer)
{
	Customer newCustomer=createCustomer(headCustomer);
	printf("registering: %s\n",newCustomer.name);//ok
	wand(headCustomer,newCustomer);
//	printf("走出wand\n"); 
}

//void printList(CustomerList* headCustomer)//打印顾客 ID列表 
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


CustomerList* login_verify(CustomerList* headCustomer)//验证 
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

CustomerList* login_user(CustomerList *headCustomer)//登陆页面 
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
//*****************管理购物车+结账 



/**********************************************************
函数名： void sortProduct; void wand_record; void buildRecordList
参数: 当前顾客 当前购物车链表 
返回: 无
功能： 构建销售记录链表 
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
	ItemList* curItem=curCustomer->customer.shoppingCart->next;//避开头节点的遍历提取信息 
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
函数名： void addCoupon 
参数: 当前总价 顾客信息 
返回: 无
功能： 根据价格自动提供购物券 
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
函数名： Double getTotalPrice 
参数: 当前顾客信息 
返回: 总价 
功能： 计算总价 
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
					printf("无相应优惠券！！\n");
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
函数名： void pay
参数: 当前顾客 
返回: 无
功能： 结算 
**********************************************************/
void pay(CustomerList* curCustomer)
{
	int choice,confirm;
	double totalPrice;
	totalPrice=getTotalPrice(curCustomer);
	addCoupon(totalPrice,curCustomer);
	if(totalPrice>curCustomer->customer.balance)
	{
		printf("余额不足！！\n请返回个人信息设置充值！！\n");
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
	
	printf("**********总价：%lf**************\n",totalPrice);
	curCustomer->customer.balance-=totalPrice;
	
}
/**********************************************************
函数名： void setStock 
参数: 商品链表  当前购物车 
返回: 无
功能： 设置所购买的商品的对应的库存与销量 
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
				printf("进入\n");
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
函数名： void resetCart
参数: 当前顾客 
返回: 无
功能： 充值购物车 相当于清空 
**********************************************************/
void resetCart(CustomerList* curCustomer)
{
	curCustomer->customer.shoppingCart=(ItemList*)malloc(sizeof(ItemList));
	curCustomer->customer.shoppingCart->next=NULL;
	
}
/**********************************************************
函数名： void setCart 
参数: 商品链表 当前顾客 销售记录链表 
返回: 无
功能： 设置购物车 包括设置商品数量、结算等功能 
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
 //搜索商品 并放入购物车中 
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
函数名： void elect
参数: 商品链表 关键词 
返回: 无
功能： 根据关键词显示相关商品 
**********************************************************/
void electProduct(ProductList* headProduct,char* keyWord)//单纯显示特定商品 
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
//		printf("进入循环\n");
		
		previousPtr=curPtr;	
//		printf("echo:1\n");
		curPtr=curPtr->next;	
//		printf("echo:2\n");
	}

		previousPtr->next=newItem;//注意 连接的方向不同 
//		printf("echo:3\n");
		newItem->next=curPtr;
}


/**********************************************************
函数名： void buyGoods
参数: 商品链表 ，当前顾客 
返回: 无
功能： 找到特定商品并放入购物车中 
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
//		printf("找到\n");
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
函数名： void purchase() 
参数: 商品链表 当前顾客 
返回: 无
功能： 进入购买页面 
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
函数名： void sortProduct 
参数: 商品链表 
返回: 无
功能： 根据价格或重量排序 
**********************************************************/
void sortProduct_price(ProductList* headProduct)
{
	ProductList* pb=NULL;
	ProductList* pf;
    struct productInfo temp;
    pf = headProduct->next;

    while(pf->next != NULL) {//以pf指向的节点为基准节点
        pb = pf->next;//pb从基准点的下一个节点开始
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

    while(pf->next != NULL) {//以pf指向的节点为基准节点
        pb = pf->next;//pb从基准点的下一个节点开始
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
函数名： void searchGoods()
参数: 当前顾客 商品链表 
返回: 无
功能： 查询商品信息 
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
	//判断是否买东西 while 
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
函数名： CustomerList* createCustomer()
参数: 无
返回: 无
功能：创建头节点 
**********************************************************/
//修改个人信息************************************ 
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
函数名： void setUserInfo 
参数: 当前顾客 
返回: 无 
功能： 修改当前顾客信息 
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
函数名： user_hall
参数: 顾客链表  当前顾客  产品链表  销售记录链表 
返回: 无 
功能： 进入用户页面 
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
函数名： void recomend
参数: 当前顾客  销售记录头节点 
返回: 无
功能： 向当前顾客推荐商品，具体实施为提供相同类型顾客中销量较高的商品 
**********************************************************/
void ShoppingRecommend(RecordList* head,CustomerList* curCustomer,ProductList* headProduct)
{
	int i=0;
	int j=0;//用于冒泡排序 
	int m=0;//用于冒泡排序	
	int mid1;
	int mid2;
	int zhonglei=0; //用于记录商品种类数量 
	FILE *fp;
	fp=fopen("D:\\学习材料\\软件实训\\电商管理系统\\商品名单.txt","r");
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
   	  
   	  while (feof(fp)==0)//判断是否读完 
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
  FILE * fp = fopen("C:\\Users\\SSS\\Desktop\\实训\\test.txt", "r+");
  FILE * fp1 = fopen("C:\\Users\\SSS\\Desktop\\实训\\lingshi.txt", "w+");//读写新建一个临时文件
  if(fp==NULL||fp1==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
  if(fgetc(fp)!=EOF)   
   {
   	fseek(fp,0,SEEK_SET);
	fread(&p1,sizeof(Administrator),1,fp);
    while (feof(fp)==0)//判断是否读完 
    {
        if (p1.account==account)//遇到要删除的内容,则不写入。
        {
	      do 
	     {
	        u=0,k=0;
	        printf("请输入新密码(6位整型)！！\n");
	        i=scanf("%d",&mima);   //依次输入 
	        if((i!=1)||(mima<=99999)||(mima>999999))//||(kind!=1&&kind!=2&&kind!=3))//判断输入是否正确 
	      {
	  	     do    
	  	    {
	  	      setbuf(stdin, NULL);
		      if(u==0)
		      {	
		      printf("输入错误，输入1重新输入，输入2退出\n");
		      u++;	  
		      }   
              scanf("%d",&k);
              setbuf(stdin, NULL);
	  	      if(k==1||k==2)    //直到用户输入正确为止 
	  	      {
	  	  	    break;	
		       }
	  	    }while(1);     //直到用户输入正确为止 
	  	    if(k==2)
	  	    {
	  		    return 0 ;     //退出函数，返回NULL 
		    }
          }
         }while(k==1);
      	    
      	    printf("您输入的密码%d\n",mima);
      	    p1.password=mima;
      	    fwrite(&p1,sizeof(Administrator),1,fp1);
      	    printf("修改成功！！！\n");
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
  	 printf("修改失败！！！\n");
   }
  }
  else
  {
  	printf("管理员存档出错了!!!\n");
  }
    fclose(fp);
    fclose(fp1);
    int p=remove("D:\\学习材料\\软件实训\\电商管理系统\\管理员名单.txt");       
    rename("D:\\学习材料\\软件实训\\电商管理系统\\lingshi.txt","D:\\学习材料\\软件实训\\电商管理系统\\管理员名单.txt");
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
	readFile_customer(headCustomer,"D:\\学习材料\\软件实训\\电商管理系统\\customerList.txt");
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
		printf("请选择您要进行的操作\n");
		printf("0>退出\n"); 	
		printf("1>超级管理员登录\n"); 
		printf("2>管理员登录\n"); 
		printf("3>用户登录\n");
		printf("?");
		scanf("%d",&choice) ;
		printf("您输入的选择是%d\n",choice);
		
		while(choice>3||choice<0)
		{
			printf("输入错误，请重试\n?");
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
//	FILE * test=fopen("D:\\学习材料\\软件实训\\电商管理系统\\管理员名单.txt","a+");
//	fwrite(AD,sizeof(Administrator),1,test);
//	fclose(test);
	Login();
	return 0;
}
