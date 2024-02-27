#include<string>
#include<iostream>
#include<stdio.h>
#include<HuffNode.h>
/*****************
基类HuffNode 
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
//建立在基类HuffNode上的叶节点类leafNode 
**************/
class leafNode : public HuffNode
{
	private:
		char element ;		//树叶节点代表的符号
		int weight;			//权重 
	public:
		leafNode(char  e,int wgt)	//构造函数 
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
//建立在基类HuffNode上的内部节点类inNode 
**************/
class inNode : public HuffNode
{
	private:
		HuffNode *lc;       		//左孩子（指针） 
		HuffNode *rc;				//右孩子（指针） 
		int weight;					//权重 
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


