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
		char element ;		//��Ҷ�ڵ����ķ���
		int weight;			//Ȩ��
	public:
	leafNode(char & e,int wgt);
	int getWeight();
	char getElement();
	 bool isLeaf();
};
class inNode : public HuffNode
{
	private:
		HuffNode *lc;       		//���ӣ�ָ�룩 
		HuffNode *rc;				//�Һ��ӣ�ָ�룩 
		int weight;					//Ȩ�� 
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
