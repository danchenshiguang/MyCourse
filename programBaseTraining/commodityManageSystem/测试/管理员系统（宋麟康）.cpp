#include <stdio.h>
#include "stdio.h"
#include<stdlib.h>
#include<string.h>
#include <errno.h>
#include<windows.h>
#include<mmsystem.h>
#include<conio.h>
#pragma comment(lib,"Winmm.lib")

struct description
{
	char name[15];
	int code;//4位 
	double price;	
	double weight;
	int kind;//1-3
};typedef struct description Description;
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
struct administrator
{
	int account;//6位数 
	int password;//6位数 
	char name[10];
	int gender;//1表示男，2表示女 
	double telNum;//11位 
	double salary;//3000起步
	struct Administator * next;	
};typedef struct administrator  Administrator;
struct productInfo
{
	Description description;
	int stock;//库存数量 
	double cost;
	double profit;
	int sales;
};typedef struct productInfo ProductInfo;
struct productList
{
	struct productInfo productInfo;
	struct productList* next;	
};typedef struct productList ProductList;
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
Administrator   *createAdministrator();
int LoginAdministrator();
void wandProduct();
ProductList  CreatProduct();
void setProduct(int code);
void deleteProduct(int code);
void showsProduct();
void statisticsProduct();
ProductList * maopao(ProductList * head);
void searchProduct();
void searchCustomer();
void showsCustomer();
void showsVip();
void showsRecord();
void CsearchRecord(int ID);
void PsearchRecord(int code);
void ranking();
ProductList * Smaopao(ProductList * head);
void ranking()
{
	int i=0;
	ProductList * D;
	ProductList * A=(ProductList *)malloc(sizeof(ProductList));
	ProductList * B=(ProductList *)malloc(sizeof(ProductList));
	//ProductList * D,C;
	FILE * test1=fopen("C:\\Users\\SSS\\Desktop\\实训\\test1.txt", "r+");
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
	FILE * test3=fopen("C:\\Users\\SSS\\Desktop\\实训\\test3.txt", "r+");
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
	FILE * test3=fopen("C:\\Users\\SSS\\Desktop\\实训\\test3.txt", "r+");
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
   	  	  printf("购买人ID：%d\n购买人薪水类别：%\n",R.customerID,R.customerSalary);
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
	FILE * test3=fopen("C:\\Users\\SSS\\Desktop\\实训\\test3.txt", "r+");
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
   	  	printf("购买人ID：%d\n购买人薪水类别：%\n",R.customerID,R.customerSalary);
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
	FILE * test2=fopen("C:\\Users\\SSS\\Desktop\\实训\\test2.txt", "r+");
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
	FILE * test2=fopen("C:\\Users\\SSS\\Desktop\\实训\\test2.txt", "r+");
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
	FILE * test2=fopen("C:\\Users\\SSS\\Desktop\\实训\\test2.txt", "r+");
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
	FILE * test1=fopen("C:\\Users\\SSS\\Desktop\\实训\\test1.txt", "r+");
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
void statisticsProduct()
{
	ProductList * D;
	ProductList * A=(ProductList *)malloc(sizeof(ProductList));
	ProductList * B=(ProductList *)malloc(sizeof(ProductList));
	//ProductList * D,C;
	double sum;
	FILE * test1=fopen("C:\\Users\\SSS\\Desktop\\实训\\test1.txt", "r+");
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
		while(D!=NULL)
		{
			fwrite(D,sizeof(ProductList),1,test1);
			D=D->next;
		}
		fclose(test1);
		printf("\n\n商品总价为:%lf\n\n",sum);
		showsProduct();
		
	}
	else
	{
		printf("商品库存为空！！！\n");
	}
}
void showsProduct()
{
	ProductList PL;
	FILE * test1=fopen("C:\\Users\\SSS\\Desktop\\实训\\test1.txt", "r+");
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
   	  	//printf("!!!\n");
   	  	printf("商品编号：%d\n商品名称：%s\n商品类型：%d\n商品重量：%lf\n商品售价：%lf\n商品成本：%lf\n商品利润：%lf\n商品库存：%d\n",PL.productInfo.description.code,PL.productInfo.description.name,PL.productInfo.description.kind,PL.productInfo.description.weight,PL.productInfo.description.price,PL.productInfo.cost,PL.productInfo.profit,PL.productInfo.stock);
   	  	printf("***************************************************************************\n");
   	  	fread(&PL,sizeof(ProductList),1,test1); 
	  }

    }
    else
    {
    	printf("商品库存为空！！！\n");
	}
	fclose(test1);
	
}
void deleteProduct(int code)
{
  ProductList p1;
  int i=0;
  FILE * fp = fopen("C:\\Users\\SSS\\Desktop\\实训\\test1.txt", "r+");
  FILE * fp1 = fopen("C:\\Users\\SSS\\Desktop\\实训\\linshi.txt", "w+");//读写新建一个临时文件
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
    int p=remove("C:\\Users\\SSS\\Desktop\\实训\\test1.txt");       
    rename("C:\\Users\\SSS\\Desktop\\实训\\linshi.txt","C:\\Users\\SSS\\Desktop\\实训\\test1.txt");
}
void setProduct(int code)
{
	deleteProduct(code);
	printf("\n接下来添加新的商品信息！！\n\n");
	wandProduct();
}
ProductList  CreatProduct()
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
void wandProduct()
{
	ProductList PL;
//	ProductList * S;
//	S=head;
//	ProductList * M=(ProductList *)malloc(sizeof(ProductList));
//	S=M;
    //printf("%d",head->productInfo.description.code);
	PL=CreatProduct();
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
		  FILE * test1=fopen("C:\\Users\\SSS\\Desktop\\实训\\test1.txt","a+");
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
int LoginAdministrator()
{
	mciSendString("open C:\\Users\\SSS\\Desktop\\实训\\abc.mp3 alias bkmusic", 0, 0, 0);
	mciSendString("play bkmusic repeat", 0, 0, 0);        //循环播放音乐
	FILE * ad; 
	int a=0;   //保存判断条件 
	int account;
	int password;    //接受用户输入 
	Administrator admini;
	printf("请输入管理员账号\n");
	scanf("%d",&account);
	setbuf(stdin, NULL);
	ad=fopen("C:\\Users\\SSS\\Desktop\\实训\\test.txt","r+");//打开储存管理员信息的文件
	if(ad==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
    fread(&admini,sizeof(Administrator),1,ad); //从文件中读取结构体; 
   
	for(;feof(ad)==0;)
	{
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
					printf("输入1添加商品\n输入2修改商品\n输入3删除商品\n输入4显示商品\n输入5统计商品，并按库存从多到少排序商品\n输入6查询商品\n输入7显示顾客信息\n输入8显示vip顾客信息\n输入9查询顾客信息\n输入10显示销售信息\n输入11查询销售信息\n输入12按销量排序商品\n输入13关闭\打开音乐\n输入14清屏幕\n输入15退出\n") ;//之后再补充 
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
				    system("cls");
				    break;
                    case 15:
                    printf("15层开!\n");
                    return 2;             //输入13，结束登录函数，返回大厅，通过返回值判断是否登录成功。 
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
	printf("该管理员账号不存在！！！\n"); 
}

/*******************************
函数名： createAdministrator()   功能： 创建一个管理员的链表单位 
************************************/
Administrator  * createAdministrator()
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
			printf("\n您输入的是:%d",account);
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
			printf("\n您输入的密码是:%d",password);
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
			setbuf(stdin, NULL);
			printf("\n您输入的名字是:%s",name);
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
			printf("\n?");
			scanf("%d",&gender);
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
			int n=0;
			int isEleven=0;
			printf("请输入要添加管理员的电话号码：\n");
			printf("?") ;
			scanf("%lld",&telNum);
			printf("\n您输入的电话号码是:%lld",telNum);
			n=telNum;
//			while(n!=0)//判断输入是否为十一位整数 
//			{
//				n/=10;
//				isEleven++;
//			}
			if(telNum<10000000000&&telNum>99999999999)
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
			printf("\n您输入的薪水是:%lf",salary);
			if(salary<=3000.0)
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
		//printf("%d",isFull);
		if(isFull==6)
		{
			break;
		}
		else
		{
			printf("必填信息不能为空，请重试");		
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

int main(void)
{
	//Administrator * AD;
	//AD=createAdministrator();
	//FILE * test=fopen("C:\\Users\\SSS\\Desktop\\实训\\test.txt","a+");
	//fwrite(AD,sizeof(Administrator),1,test);
	//fclose(test);
	int i=LoginAdministrator();		
}
