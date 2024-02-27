#include <stdio.h>
#include<stdlib.h>
//节点
//typedef struct monster
//{
//	//数据
//	int data;
//	char *name;
//	struct monster * pNext; 
//}Monster; 
typedef struct Node//节点 
{
	int data;
	struct Node *next;
}Node;//定义 新的结构体变量时，加了struct就必须用真名，没加就可用别名 


/******************************************
	创建头节点的函数
	*****************************/ 
 Node * creatList()//头节点 
{
	//空间 mallc函数是用来为节点分配内存的 
	Node * headNode =(Node*) malloc(sizeof(Node));
	//设置数据
	headNode->data =0; 
	//设置头节点的指针
	headNode->next=NULL;
	return headNode;
}
/************************************
创建节点
**********************************/
Node *createNode(int data) 
{
	//创建节点分配空间
	Node *node=(Node*) malloc(sizeof (node));
	//设置节点数据
	node->data=data;
	//指针
	node->next=NULL;
	//返回创建的节点
	return node; 
}


//添加节点
void want(Node* headNode,int data) 
{
	//创建节点
	Node* newNode =createNode(data);
	//结构体指针
	Node* p=headNode;
	//判断，当前节点的指针是否为空
	while (p->next!=NULL) 
	{
		p=p->next;
	}
	//当前p为链表的最后一个节点
	//设置新节点为p的下一个节点
	p->next = newNode;
}
void show(Node* headNode)//Monster * Node
{
	//定义结构体指针
	Node *node =headNode->next;
	//不为空就运行下去
	 
	while (node) 
	{
//		printf("%d........%s\n",node->data,node->name);
		printf("%d........\n",node->data);
		node=node->next;
	}
	printf("\n");
}
/************************
插入  头节点   新节点的值       要找到节点的值
************************/
void insert(Node* headNode, int data, int index) 
{
	Node* newNode =createNode(data);
	//指针节点
	Node * t= headNode->next;
	//t 里面的数据不等于index就运行
	while (t->data!=index) 
	{
		t=t->next;
	}
	//新节点的下一个节点为t的下一个节点 
	 newNode->next=t->next;
	 //t节点的下一个节点为新节点 
	 t->next=newNode;
	 
}
/*************************
修改对应的数据
***********************/ 
void rewrite(Node*headNode,int data,int index) 
{
	Node* newNode =createNode(data);
	//指针节点	
	Node * t= headNode->next;
	//t 里面的数据不等于index就运行
	while (t->data!=index) 
	{
		t=t->next;
	}
	if(t->data==index)
	{
		t->data=data;
	}
		
}
void reMove(Node*headNode,int data) 
{
	Node *t=headNode;//定义两个指针来判断要删的数据 
	Node*p =headNode->next;
	if(headNode->next==NULL)//判断链表是否为空 
	{
		printf("链表为空\n");
	}
	else{
		while (p->data!=data)
		{
			t=p;
			p=p->next;
			if(p==NULL)
			{
				printf("遍历完，没有要找的值\n"); 
				break;
			}
		}
		t->next=p->next;
		free(p);
		p=NULL; 
	}
}

int main()
{
//	//赋值
//	Monster m1={1,"小明"} ;
//	Monster m2={2,"小红"};
//	Monster m3={3,"小马"};
//	Monster m4={4,"小赵"} ;//?????
////设置节点
//	 m1.pNext =&m2;
//	 m2.pNext= &m3;
//	 m3.pNext= &m4;
//	 m4.pNext= NULL; 
//	 show(&m1);
	//创建链表
	struct  Node *headNode = creatList();
	want(headNode,39);
	want(headNode,32);
	want(headNode,342);
	want(headNode,392);
	want(headNode,20);
	show(headNode);	
	printf("\n==========插入===========\n")	;
	insert(headNode,38,32);
	show(headNode);
	printf("\n==========修改===========\n")	;
	rewrite(headNode,55,392) ; 
	show(headNode);
	printf("\n==========删除===========\n")	;
	reMove(headNode,39) ; 
	show(headNode);	
	return 0;
}

