#ifndef HuffNode.h
#define HuffNode.h
class HuffNode
{
	public:
		virtual ~HuffNode()
		{
		}
		virtual int weight()=0;
		virtual bool isLeaf()=0;
};		
class leafNode : public HuffNode
{
	private:
		char element ;		//树叶节点代表的符号
		int weight;			//权重
	public:
	leafNode(char & e,int wgt);
	int getWeight();
	char getElement();
	 bool isLeaf();
};
class inNode : public HuffNode
{
	private:
		HuffNode *lc;       		//左孩子（指针） 
		HuffNode *rc;				//右孩子（指针） 
		int weight;					//权重 
	public:
		inNode(HuffNode *l, HuffNode *r);
		 int getWeight();
		 bool isLeaf();
		void setRight(HuffNode *t);
		HuffNode *right();
		void setLeft(HuffNode *t);
		HuffNode *left();	
 } ;
#endif
