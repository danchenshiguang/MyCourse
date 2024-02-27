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
	int code;//4λ 
	double price;	
	double weight;
	int kind;//1-3
};typedef struct description Description;
struct discountCoupon//�Ż�ȯ 
{
	int kind;
	float discount;//�ۿ� 
};typedef struct discountCoupon DiscountCoupon;
struct item
{
	Description description;
	int quantity;//��������� 
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
struct administrator
{
	int account;//6λ�� 
	int password;//6λ�� 
	char name[10];
	int gender;//1��ʾ�У�2��ʾŮ 
	double telNum;//11λ 
	double salary;//3000��
	struct Administator * next;	
};typedef struct administrator  Administrator;
struct productInfo
{
	Description description;
	int stock;//������� 
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
	FILE * test1=fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test1.txt", "r+");
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
	FILE * test3=fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test3.txt", "r+");
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
	FILE * test3=fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test3.txt", "r+");
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
   	  	  printf("������ID��%d\n������нˮ���%\n",R.customerID,R.customerSalary);
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
	FILE * test3=fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test3.txt", "r+");
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
   	  	printf("������ID��%d\n������нˮ���%\n",R.customerID,R.customerSalary);
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
	FILE * test2=fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test2.txt", "r+");
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
	FILE * test2=fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test2.txt", "r+");
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
	FILE * test2=fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test2.txt", "r+");
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
	FILE * test1=fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test1.txt", "r+");
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
void statisticsProduct()
{
	ProductList * D;
	ProductList * A=(ProductList *)malloc(sizeof(ProductList));
	ProductList * B=(ProductList *)malloc(sizeof(ProductList));
	//ProductList * D,C;
	double sum;
	FILE * test1=fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test1.txt", "r+");
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
		while(D!=NULL)
		{
			fwrite(D,sizeof(ProductList),1,test1);
			D=D->next;
		}
		fclose(test1);
		printf("\n\n��Ʒ�ܼ�Ϊ:%lf\n\n",sum);
		showsProduct();
		
	}
	else
	{
		printf("��Ʒ���Ϊ�գ�����\n");
	}
}
void showsProduct()
{
	ProductList PL;
	FILE * test1=fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test1.txt", "r+");
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
   	  	//printf("!!!\n");
   	  	printf("��Ʒ��ţ�%d\n��Ʒ���ƣ�%s\n��Ʒ���ͣ�%d\n��Ʒ������%lf\n��Ʒ�ۼۣ�%lf\n��Ʒ�ɱ���%lf\n��Ʒ����%lf\n��Ʒ��棺%d\n",PL.productInfo.description.code,PL.productInfo.description.name,PL.productInfo.description.kind,PL.productInfo.description.weight,PL.productInfo.description.price,PL.productInfo.cost,PL.productInfo.profit,PL.productInfo.stock);
   	  	printf("***************************************************************************\n");
   	  	fread(&PL,sizeof(ProductList),1,test1); 
	  }

    }
    else
    {
    	printf("��Ʒ���Ϊ�գ�����\n");
	}
	fclose(test1);
	
}
void deleteProduct(int code)
{
  ProductList p1;
  int i=0;
  FILE * fp = fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test1.txt", "r+");
  FILE * fp1 = fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\linshi.txt", "w+");//��д�½�һ����ʱ�ļ�
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
    int p=remove("C:\\Users\\SSS\\Desktop\\ʵѵ\\test1.txt");       
    rename("C:\\Users\\SSS\\Desktop\\ʵѵ\\linshi.txt","C:\\Users\\SSS\\Desktop\\ʵѵ\\test1.txt");
}
void setProduct(int code)
{
	deleteProduct(code);
	printf("\n����������µ���Ʒ��Ϣ����\n\n");
	wandProduct();
}
ProductList  CreatProduct()
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
		  FILE * test1=fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test1.txt","a+");
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
int LoginAdministrator()
{
	mciSendString("open C:\\Users\\SSS\\Desktop\\ʵѵ\\abc.mp3 alias bkmusic", 0, 0, 0);
	mciSendString("play bkmusic repeat", 0, 0, 0);        //ѭ����������
	FILE * ad; 
	int a=0;   //�����ж����� 
	int account;
	int password;    //�����û����� 
	Administrator admini;
	printf("���������Ա�˺�\n");
	scanf("%d",&account);
	setbuf(stdin, NULL);
	ad=fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test.txt","r+");//�򿪴������Ա��Ϣ���ļ�
	if(ad==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
    fread(&admini,sizeof(Administrator),1,ad); //���ļ��ж�ȡ�ṹ��; 
   
	for(;feof(ad)==0;)
	{
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
					printf("����1�����Ʒ\n����2�޸���Ʒ\n����3ɾ����Ʒ\n����4��ʾ��Ʒ\n����5ͳ����Ʒ���������Ӷൽ��������Ʒ\n����6��ѯ��Ʒ\n����7��ʾ�˿���Ϣ\n����8��ʾvip�˿���Ϣ\n����9��ѯ�˿���Ϣ\n����10��ʾ������Ϣ\n����11��ѯ������Ϣ\n����12������������Ʒ\n����13�ر�\������\n����14����Ļ\n����15�˳�\n") ;//֮���ٲ��� 
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
				    system("cls");
				    break;
                    case 15:
                    printf("15�㿪!\n");
                    return 2;             //����13��������¼���������ش�����ͨ������ֵ�ж��Ƿ��¼�ɹ��� 
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
	printf("�ù���Ա�˺Ų����ڣ�����\n"); 
}

/*******************************
�������� createAdministrator()   ���ܣ� ����һ������Ա������λ 
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
		while(1)//����˻� 
		{
			int n=0;
			int isSix=0;
			printf("������Ҫ��ӹ���Ա���˻���\n");
			printf("?") ;
			scanf("%d",&account);
			printf("\n���������:%d",account);
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
			printf("\n�������������:%d",password);
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
			setbuf(stdin, NULL);
			printf("\n�������������:%s",name);
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
			printf("\n?");
			scanf("%d",&gender);
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
			int n=0;
			int isEleven=0;
			printf("������Ҫ��ӹ���Ա�ĵ绰���룺\n");
			printf("?") ;
			scanf("%lld",&telNum);
			printf("\n������ĵ绰������:%lld",telNum);
			n=telNum;
//			while(n!=0)//�ж������Ƿ�Ϊʮһλ���� 
//			{
//				n/=10;
//				isEleven++;
//			}
			if(telNum<10000000000&&telNum>99999999999)
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
			printf("\n�������нˮ��:%lf",salary);
			if(salary<=3000.0)
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
		//printf("%d",isFull);
		if(isFull==6)
		{
			break;
		}
		else
		{
			printf("������Ϣ����Ϊ�գ�������");		
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

int main(void)
{
	//Administrator * AD;
	//AD=createAdministrator();
	//FILE * test=fopen("C:\\Users\\SSS\\Desktop\\ʵѵ\\test.txt","a+");
	//fwrite(AD,sizeof(Administrator),1,test);
	//fclose(test);
	int i=LoginAdministrator();		
}
