#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max 100
struct description
{
	char name[15];
	int code;//4位 
	double price;	
	double weight;
	int kind;//1-3
};typedef struct description Description;

struct productInfo
{
	Description description;
	int stock;//库存数量 
	double cost;
	double profit;
	int sales;
};typedef struct product ProductInfo;

struct productList
{
	struct productInfo productInfo;
	struct productList* next;	
};typedef struct productList ProductList;


struct discountCoupon//优惠券 
{
	int kind;
	float discount;//折扣 
};typedef struct discountCoupon DiscountCoupon;

struct item
{
	Description description;
	int quantity;//购买的数量 
};typedef struct item Item;

struct itemList
{
	Item item;
	struct itemList *next;
};typedef struct itemList ItemList;

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
struct customerList
{
	Customer customer;
	struct customerList  *next;	
};typedef struct customerList CustomerList; 

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



void wand_record(RecordList* headRecord,RecordList* curRecord);

void registering(CustomerList* headCustomer);
CustomerList* login_verify(CustomerList* headCustomer);
Customer createCustomer(CustomerList* headCustomer);
CustomerList* createNode(Customer newCustomer);
void wand(CustomerList *headCustomer,Customer newCustomer);
void printList(CustomerList* headCustomer);
void wand_product(ProductList* headProduct,struct productInfo newProduct);
void writeFile_customer(CustomerList* headCustomer);  
//**********************************************************************************************
//***************文件读写 *****************


/****************
	读商品文件 
*****************/
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
		printf("error");
	}
	
	printf("openFile\n");
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
//**************************************************

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


void writeFile_customer(CustomerList* headCustomer)
{
//	printf("进入写文件\n");
	CustomerList* curPtr=headCustomer->next;
	if(headCustomer!=NULL)
	{
//		printf("Notempty\n");
	}//ok 
	FILE * rt;
	
	if((rt=fopen("C:\\Users\\liangyexi\\Documents\\University\\in\\se\\c\\ssss\\customerList.txt","w"))!=NULL)
	{
		printf("error");
	}
	
	printf("openFile\n");
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


void wand(CustomerList *headCustomer,Customer newCustomer) //连接顾客链表 
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
//	writeFile_customer(headCustomer);
//	printList(headCustomer);	
}
CustomerList* createNode(Customer newCustomer)
{
	CustomerList* newPtr=(CustomerList*)malloc(sizeof(CustomerList));
	newPtr->customer=newCustomer;
	return newPtr;
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
	ProductList* curProduct=headProduct;
	ItemList* curItem=shoppingCart;
	while(curItem!=NULL)
	{
		while(curProduct!=NULL)
		{
			if(curItem->item.description.code==curProduct->productInfo.description.code)
			{
				curProduct->productInfo.stock-=curItem->item.quantity;
				curProduct->productInfo.sales+=curItem->item.quantity;
			}
			curProduct=curProduct->next;
		}
		curItem=curItem->next;
	}
	
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
CustomerList* creatHeadCustomer()
{
	CustomerList* headCustomer=(CustomerList*)malloc(sizeof(CustomerList));
	headCustomer->customer.ID=0;
	headCustomer->next=NULL;
	return headCustomer;
}
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
//				recomend(curCustomer,headRecord);
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

int main(void)
{
	loginUser();
	
	
}
