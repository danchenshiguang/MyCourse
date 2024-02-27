#include <stdio.h>
#include<stdlib.h>
//�ڵ�
//typedef struct monster
//{
//	//����
//	int data;
//	char *name;
//	struct monster * pNext; 
//}Monster; 
typedef struct Node//�ڵ� 
{
	int data;
	struct Node *next;
}Node;//���� �µĽṹ�����ʱ������struct�ͱ�����������û�ӾͿ��ñ��� 


/******************************************
	����ͷ�ڵ�ĺ���
	*****************************/ 
 Node * creatList()//ͷ�ڵ� 
{
	//�ռ� mallc����������Ϊ�ڵ�����ڴ�� 
	Node * headNode =(Node*) malloc(sizeof(Node));
	//��������
	headNode->data =0; 
	//����ͷ�ڵ��ָ��
	headNode->next=NULL;
	return headNode;
}
/************************************
�����ڵ�
**********************************/
Node *createNode(int data) 
{
	//�����ڵ����ռ�
	Node *node=(Node*) malloc(sizeof (node));
	//���ýڵ�����
	node->data=data;
	//ָ��
	node->next=NULL;
	//���ش����Ľڵ�
	return node; 
}


//��ӽڵ�
void want(Node* headNode,int data) 
{
	//�����ڵ�
	Node* newNode =createNode(data);
	//�ṹ��ָ��
	Node* p=headNode;
	//�жϣ���ǰ�ڵ��ָ���Ƿ�Ϊ��
	while (p->next!=NULL) 
	{
		p=p->next;
	}
	//��ǰpΪ��������һ���ڵ�
	//�����½ڵ�Ϊp����һ���ڵ�
	p->next = newNode;
}
void show(Node* headNode)//Monster * Node
{
	//����ṹ��ָ��
	Node *node =headNode->next;
	//��Ϊ�վ�������ȥ
	 
	while (node) 
	{
//		printf("%d........%s\n",node->data,node->name);
		printf("%d........\n",node->data);
		node=node->next;
	}
	printf("\n");
}
/************************
����  ͷ�ڵ�   �½ڵ��ֵ       Ҫ�ҵ��ڵ��ֵ
************************/
void insert(Node* headNode, int data, int index) 
{
	Node* newNode =createNode(data);
	//ָ��ڵ�
	Node * t= headNode->next;
	//t ��������ݲ�����index������
	while (t->data!=index) 
	{
		t=t->next;
	}
	//�½ڵ����һ���ڵ�Ϊt����һ���ڵ� 
	 newNode->next=t->next;
	 //t�ڵ����һ���ڵ�Ϊ�½ڵ� 
	 t->next=newNode;
	 
}
/*************************
�޸Ķ�Ӧ������
***********************/ 
void rewrite(Node*headNode,int data,int index) 
{
	Node* newNode =createNode(data);
	//ָ��ڵ�	
	Node * t= headNode->next;
	//t ��������ݲ�����index������
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
	Node *t=headNode;//��������ָ�����ж�Ҫɾ������ 
	Node*p =headNode->next;
	if(headNode->next==NULL)//�ж������Ƿ�Ϊ�� 
	{
		printf("����Ϊ��\n");
	}
	else{
		while (p->data!=data)
		{
			t=p;
			p=p->next;
			if(p==NULL)
			{
				printf("�����꣬û��Ҫ�ҵ�ֵ\n"); 
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
//	//��ֵ
//	Monster m1={1,"С��"} ;
//	Monster m2={2,"С��"};
//	Monster m3={3,"С��"};
//	Monster m4={4,"С��"} ;//?????
////���ýڵ�
//	 m1.pNext =&m2;
//	 m2.pNext= &m3;
//	 m3.pNext= &m4;
//	 m4.pNext= NULL; 
//	 show(&m1);
	//��������
	struct  Node *headNode = creatList();
	want(headNode,39);
	want(headNode,32);
	want(headNode,342);
	want(headNode,392);
	want(headNode,20);
	show(headNode);	
	printf("\n==========����===========\n")	;
	insert(headNode,38,32);
	show(headNode);
	printf("\n==========�޸�===========\n")	;
	rewrite(headNode,55,392) ; 
	show(headNode);
	printf("\n==========ɾ��===========\n")	;
	reMove(headNode,39) ; 
	show(headNode);	
	return 0;
}

