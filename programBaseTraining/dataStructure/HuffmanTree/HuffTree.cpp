#include<iostream> 
#include<stdio.h>
#include<string>
#define INF 0x3f3f3f3f
using 
//#include<HuffNode.h>
/*****************
基类HuffNode 
******************/
class HuffNode
{
	public:
		virtual ~HuffNode()
		{
		}
		virtual int getWeight()=0;
		virtual bool isLeaf()=0;
		virtual HuffNode *right()=0;
		virtual HuffNode *left()=0;
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
		leafNode(char e,int wgt)	//构造函数 
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
		 HuffNode *right()
		 {
		 	return NULL;
		 }
		 HuffNode *left()
		 {
		 	return NULL;
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
			weight=l->getWeight()+r->getWeight();
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


class HuffTree
{
	private:
		HuffNode *root;
//		inNode *root1;
//		leafNode *root2;

	public:
		HuffTree(char  value,int wgt)
		{
			root=new leafNode(value,wgt);
		}
		HuffTree(HuffTree *l,HuffTree *r)
		{
			root= new inNode(l->getRoot(),r->getRoot());
		}
		~HuffTree()
		{
		}
		HuffNode *getRoot()
		{
			return root;
		}
		int getWeight()
		{
			return root->getWeight(); 
		}
		
};
//合并两颗最小的树 
void combineMinTwo(HuffTree **ttree,int treeNum,HuffTree *temp1,HuffTree *temp2)
{
	int s1=-1;
	int s2=-1; 
	double min1;
	double min2;
	min1=min2=INF;
	for(int i=0;i<treeNum;i++)
	{
//		printf("%d",ttree[i]->getWeight());
		if(ttree[i]->getWeight()<min1)
		{
			min2=min1;
			s2=s1;
			min1=ttree[i]->getWeight();
			s1=i;	
		} 
		else if(ttree[i]->getWeight()>=min1&&ttree[i]->getWeight()<min2)
		{
			min2=ttree[i]->getWeight();
			s2=i;
		}
	}
	
	temp1=new HuffTree(ttree[s1],ttree[s2]);
	ttree[s1]=temp1;
	temp2=ttree[s2];
	ttree[s2]=ttree[treeNum-1];
	ttree[treeNum-1]=temp2;
}
HuffTree *HuffmanBuild(char *s,int *w,int num)
{
	HuffTree *ttree[num], *temp1,*temp2;
	for(int i=0;i<num;i++)
	{
		ttree[i]= new HuffTree(s[i],w[i]);
	}
	for(int i=num;i>1;--i)
	{
		combineMinTwo(ttree,i,temp1,temp2);		
	}
//	printf("jj");
//	printf("%d",ttree[0]->getWeight());
	for(int i=1;i<num;i++)
	{
		delete ttree[i];
	}
	return ttree[0];
}
int main()
{
	char f[5]={'a','b','c','d','e'};
	int weight[5]={1,2,3,4,5};
	HuffTree *temp;
	temp=HuffmanBuild(f,weight,5);
	
	
}
