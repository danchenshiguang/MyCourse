#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  Max   100

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

struct customer//顾客结构体 
{
	ItemList shoppingCart;//
	char name[10];
	int ID;//6位数 
	int password;// 6位数 
	int gender;//1:female  2:male
	int isVIP;//1:no  2:yes
	double vipDiscount;
	long long telNum; 
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
 void wandProduct();
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
	Administrator node;
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
			fread(&node,sizeof(Administrator),1,fp);											
			wandAdministrator(headAdministrator,node.account,node.password,node.name,node.gender,node.telNum,node.salary);
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
			fwrite(p,sizeof(p),1,fp);
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
		fwrite(newNode,sizeof(newNode),1,fp);
		printf("添加完成，是否继续添加管理员\n");
		printf("1>继续  2>退出\n?");
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
			fwrite(p,sizeof(p),1,fp);
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
	Administrator *Admin;
	if(fp==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
     printf("www\n"); 
    //fread(&PL,sizeof(ProductList),1,test1); 
    if(fgetc(fp)!=EOF)   
    { 
   	  fseek(fp,0,SEEK_SET);
   	  fread(&Admin,sizeof(Administrator),1,fp); 
   	  printf("%d",Admin.account)
   	  while (feof(fp)==0)//判断是否读完 
   	  {
   	  	printf("账户：%d\n密码：%d\n姓名：%s\n性别：%d\n电话：%lld\n薪水：%lf\n",Admin->account,Admin->password,Admin->name,Admin->gender,Admin->telNum,Admin->salary);
   	  	printf("***************************************************************************\n");
   	  	fread(&Admin,sizeof(Administrator),1,fp); 
	  }
	  printf("\n..........查询完毕...............\n");	  
    }
    else
    {
    	printf("管理员名单为空！！！\n\n");
	}
	
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
函数名：void wand(CustomerList *headCustomer,Customer newCustomer)  功能：将文件中读取出的顾客信息存入链表 
********************************************/
void wand(CustomerList *headCustomer,Customer newCustomer)
{
	printf("进入wand\n");
	
	CustomerList* newPtr=createNode(newCustomer);
	printf("wand_get: %6d\n",newPtr->customer.ID);//ok
	CustomerList* curPtr=headCustomer;
	CustomerList* previousPtr=NULL;
	while(curPtr!=NULL)
	{
		printf("进入循环\n");
		
		previousPtr=curPtr;	
		printf("echo:1\n");
		curPtr=curPtr->next;	
		printf("echo:2\n");
	}

				previousPtr->next=newPtr;//注意 连接的方向不同 
				printf("echo:3\n");
			newPtr->next=curPtr;
			printf("echo:4\n");	
			printf("%6d\n",newPtr->customer.ID);
			printf("%6d\n",previousPtr->next->customer.ID);

	printf("Done_wand\n");	
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
	 	fwrite(p,sizeof(p),1,fp);
	 	p->next;
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
			printf("请输入想要修改折扣的优惠券种类");
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
	 	fwrite(p,sizeof(p),1,fp);
	 	p->next;
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
	CustomerList curCustomer;
	if(fp==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
    //fread(&PL,sizeof(ProductList),1,test1); 
    if(fgetc(fp)!=EOF)   
    { 
   	  fseek(fp,0,SEEK_SET);
   	  fread(&curCustomer,sizeof(CustomerList),1,fp); 
   	  while (feof(fp)==0)//判断是否读完 
   	  {
   	  	int i=0;
   	  	int a=0;//用来记录顾客优惠券数量 
   	  	int b=0;
   	  	int c=0;   	  	
   	  	printf("ID：%d\n姓名：%s\n性别：%d\n电话：%lld\n薪水：%lf\n是否VIP：%d\n",curCustomer.customer.ID,curCustomer.customer.name,curCustomer.customer.gender,curCustomer.customer.telNum,curCustomer.customer.salary,curCustomer.customer.isVIP,curCustomer.customer.vipDiscount);
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
   	  		printf("本顾客持有的优惠券为\n");
   	  		printf("1...........%d张",a);
   	  		printf("2...........%d张",b); 
   	  		printf("3...........%d张",c); 				 				  		 
   	  	printf("***************************************************************************\n");
   	  	fread(&curCustomer,sizeof(CustomerList),1,fp); 
	  }
	  printf("\n..........查询完毕...............\n");
    }
    else
    {
    	printf("顾客名单为空！！！\n\n");
	}
	
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
   	  	printf("商品编号：%d\n商品名称：%s\n商品类型：%d\n商品重量：%lf\n商品售价：%lf\n商品成本：%lf\n商品利润：%lf\n商品库存：%d\n",PL.productInfo.description.code,PL.productInfo.description.name,PL.productInfo.description.kind,PL.productInfo.description.weight,PL.productInfo.description.price,PL.productInfo.cost,PL.productInfo.profit,PL.productInfo.stock);
   	  	printf("***************************************************************************\n");
   	  	fread(&PL,sizeof(ProductList),1,test1); 
	  }
	  printf("\n..........查询完毕...............\n");	  
    }
    else
    {
    	printf("商品库存为空！！！\n\n");
	}
	
}
/******************************************
suSetProduct()     功能：超级管理员修改商品信息 
************************************************/ 
void suSetProduct()
{
	ProductList PL,new1;
	int code,j=0;
	printf("请输入需要修改的商品编号\n");
	scanf("%d",&code);
	FILE * test1;
	test1=fopen("D:\\学习材料\\软件实训\\电商管理系统\\商品名单.txt","r+");//打开储存管理员信息的文件
	if(test1==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
    fread(&PL,sizeof(ProductList),1,test1); //从文件中读取结构体; 
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
				printf("修改成功！！！\n");
			}
			else
			{
				printf("修改失败！！！\n");
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
				printf("修改成功！！！\n");
			}
			else
			{
				printf("修改失败！！！\n");
			}
			j++;
		}
	if(j==0)
	{
	  printf("该商品不存在！！！\n");
    }
}
/***********************************************************
deleteProduct()     功能：超级管理员删除商品 
***********************************************************/
void deleteProduct()
{
  ProductList p1;
  int code,i=0;
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
    printf("请输入需要删除商品的编号\n");	
    scanf("%d",&code);
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
    remove("商品名单.txt");                
    rename("linshi.txt", "test1.txt");
}
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
				printf("欢迎尊贵的超级管理员登录\n");
				
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
							printf("此处用来统计商品\n");
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
	
//	while(admini.account==account&&a==0)
//		{
//			fclose(ad);     //找到对应管理员，关闭文件 
//			printf("请输入密码\n");
//			scanf("%d",&password);
//			setbuf(stdin, NULL);
//			int i=0,k=0;     //用于储存判断信息 
//			if(password==admini.password)
//			{
//				printf("欢迎尊贵的超级管理员登录\n");
//				FILE*test1=fopen("C:\\Users\\SSS\\Desktop\\实训\\test1.txt","a+");  	
//				ProductList PL;
//				fread(&PL,sizeof(ProductList),1,test1);
//				fclose(test1);
//				while(1)
//				{
//					printf("输入1添加商品\n输入2修改商品\n输入3删除商品\n输入4退出\n") ;//之后再补充 
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
//                    printf("4层开!\n");
//                    return 2;             //输入4，结束登录函数，返回大厅，通过返回值判断是否登录成功。 
//                    break;
//                    default:
//                    printf("该层不存在, 请重新输入\n");
//				  }
//				}
//			}
//			else
//			{
//				printf("输入密码错误，输入2退出，输入任意数字重新输入\n");
//				scanf("%d",&k);
//				setbuf(stdin, NULL);
//				if(k==2)
//				{
//					return 1;    //用一个int接受返回的值，判断是否登录成功 
//				}
//			} 
//	   }
//	fclose(ad);    //找不到，关闭文件 
//	printf("该管理员账号不存在！！！\n"); 
}

/***************************************************
函数名： LoginAdministrator  功能：管理员登录 
*******************************************************/
//int LoginAdministrator()
//{
//	FILE * ad; 
//	int a=0;   //保存判断条件 
//	int account;
//	int password;    //接受用户输入 
//	Administrator admini;
//	printf("请输入管理员账号\n");
//	scanf("%d",&account);
//	setbuf(stdin, NULL);
//	ad=fopen("D:\\学习材料\\软件实训\\电商管理系统\\管理员名单.txt","r+");//打开储存管理员信息的文件
//	if(ad==NULL)
//     {
//      printf("打开文件失败.\n");
//      exit(0);
//     }
//    fread(&admini,sizeof(Administrator),1,ad); //从文件中读取结构体; 
//   
//	for(;feof(ad)==0;)
//	{
//		//printf("%d\n",admini.account);
//		//printf("!!!\n");
//		while(admini.account==account)
//		{
//			fclose(ad);     //找到对应管理员，关闭文件 
//			printf("请输入密码\n");
//			scanf("%d",&password);
//			setbuf(stdin, NULL);
//			int i=0,k=0;    //用于储存判断信息 
//			char c;
//			if(password==admini.password)
//			{
//				printf("欢迎尊贵的管理员%s登录\n",admini.name);
//				
//				while(1)
//				{
//					printf("输入1添加商品\n输入2修改商品\n输入3删除商品\n输入4退出\n") ;//之后再补充 
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
//                    printf("4层开!\n");
//                    return 2;             //输入4，结束登录函数，返回大厅，通过返回值判断是否登录成功。 
//                    break;
//                    default:
//                    printf("该层不存在, 请重新输入\n");
//				  }
//				}
//			}
//			else
//			{
//				printf("输入密码错误，输入2退出，输入任意数字重新输入\n");
//				scanf("%d",&k);
//				setbuf(stdin, NULL);
//				if(k==2)
//				{
//					return 1;    //用一个int接受返回的值，判断是否登录成功 
//				}
//			} 
//			
//			
//		}
//		fread(&admini,sizeof(Administrator),1,ad);    //读取下一个 
//		
//	}
//	while(admini.account==account&&a==0)
//		{
//			fclose(ad);     //找到对应管理员，关闭文件 
//			printf("请输入密码\n");
//			scanf("%d",&password);
//			setbuf(stdin, NULL);
//			int i=0,k=0;     //用于储存判断信息 
//			if(password==admini.password)
//			{
//				printf("欢迎尊贵的管理员%s登录\n",admini.name);
////				FILE*test1=fopen("C:\\Users\\SSS\\Desktop\\实训\\test1.txt","a+");  	
////				ProductList PL;
////				fread(&PL,sizeof(ProductList),1,test1);
////				fclose(test1);
//				while(1)
//				{
//					printf("输入1添加商品\n输入2修改商品\n输入3删除商品\n输入4退出\n") ;//之后再补充 
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
//                    printf("4层开!\n");
//                    return 2;             //输入4，结束登录函数，返回大厅，通过返回值判断是否登录成功。 
//                    break;
//                    default:
//                    printf("该层不存在, 请重新输入\n");
//				  }
//				}
//			}
//			else
//			{
//				printf("输入密码错误，输入2退出，输入任意数字重新输入\n");
//				scanf("%d",&k);
//				setbuf(stdin, NULL);
//				if(k==2)
//				{
//					return 1;    //用一个int接受返回的值，判断是否登录成功 
//				}
//			} 
//	   }
//	fclose(ad);    //找不到，关闭文件 
//	printf("该管理员账号不存在！！！\n"); 
//}

//void loginUser()//进入用户界面  登录 
//{
//	int choice;
//	printf("0>退出\n");
//	printf("1>管理员登录\n");
//	printf("输入：");
//	scanf("%d\n",&choice);
//		while(choice>1||choice<0)
//	{
//		printf("输入错误，请重试\n?");
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
				printf("此处用来登录管理员界面\n");
//				 k=loginAdmin();
				break;
			case 3:
				printf("此处将登陆用户界面\n");
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
