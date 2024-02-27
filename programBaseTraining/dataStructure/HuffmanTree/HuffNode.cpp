#include<string>
#include<iostream>
#include<stdio.h>
#include<HuffNode.h>
/*****************
����HuffNode 
******************/
class HuffNode
{
	public:
		virtual ~HuffNode()
		{
		}
		virtual int weight()=0;
		virtual bool isLeaf()=0;
};
/***************** 
//�����ڻ���HuffNode�ϵ�Ҷ�ڵ���leafNode 
**************/
class leafNode : public HuffNode
{
	private:
		char element ;		//��Ҷ�ڵ����ķ���
		int weight;			//Ȩ�� 
	public:
		leafNode(char  e,int wgt)	//���캯�� 
		{
			element =e;
			weight=wgt;
		 } 
		 int getWeight()
		 {
		 	return weight;
		 }
		 char getElement()
		 {
		 	return element;
		 }
		 bool isLeaf()
		 {
		 	return true;
		 }
};
/***************** 
//�����ڻ���HuffNode�ϵ��ڲ��ڵ���inNode 
**************/
class inNode : public HuffNode
{
	private:
		HuffNode *lc;       		//���ӣ�ָ�룩 
		HuffNode *rc;				//�Һ��ӣ�ָ�룩 
		int weight;					//Ȩ�� 
	public:
		inNode(HuffNode *l, HuffNode *r)
		{
			weight=l->weight()+r->weight();
			lc=l;
			rc=r;
		}
		 int getWeight()
		{
		 	return weight;
		}
		 bool isLeaf()
		 {
		 	return false;
		 }
		void setRight(HuffNode *t)
		{
			rc=t;
		}
		HuffNode *right()
		{
			return rc;
		}
		void setLeft(HuffNode *t)
		{
			lc=t;
		} 
		HuffNode *left()
		{
			return lc;
		}
};


