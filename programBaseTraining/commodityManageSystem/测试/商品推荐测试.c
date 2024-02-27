#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define   Max    100


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
struct record
{
	int customerID;
	int customerSalary;
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
struct itemList
{
	Item item;
	struct itemList *next;
};typedef struct itemList ItemList;
struct discountCoupon//�Ż�ȯ�ṹ�� 
{
	int kind;
	float discount;//�ۿ� 
};typedef  struct discountCoupon DiscountCoupon;
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
void wand_record(RecordList* headRecord,RecordList* curRecord);
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
//		printf("Done_read_Record\n");
//		printList();
}

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
void ShoppingRecommend(RecordList*head,)
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

	printf("%d",curCount[3].countID[3].countTotal);
	
	printf("%d",curCount[curCustomer->customer.salary].countID.code);
	
}


int main()
{
	RecordList *head=createHeadRecord();
	ShoppingRecommend(head);
	return 0;
}
