#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;
class StringGuard {
	private:
		int errorInfo[10]={0,0,0,0,0,0,0,0,0,0};
		bool isOperate(char ch) {
			if (ch != '+') {
				if (ch != '-') {
					if (ch != '*') {
						if (ch != '/') {
							if (ch != '(') {
								if (ch != ')') {
									if (ch != '%') {
										if (ch != '^') {
											if (ch != '&') {
												if (ch != '.') {
													if (ch != '=') {
														return false;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			return true;
		}
		/*
		Ԥ������1��ɾ�����пո�
				��2����ͷ������-������0
				��3����βû�С�=��������=��
				��4��ɾ��������
				(5)��Ϊ����ʱ���ж�ǰ����û������ 
		*/
		void preProcess(std::string &data) {
			trimSpace(data);
//			addZero(data);
			addEqual(data);
			trimInvalidBracket(data);
			addBracket(data);
		}
		//�������
void addBracket(std::string &data)
{
	for(int j=0;j<100;j++)
	{
		if(data[j]=='-'&&(j==0||isOperate(data[j-1])))
		{
			data.insert(j,"(");
			j++;
		}
		if(j==data.size()-1)
		{
			break;
		}
	}
	for(int j=0;j<100;j++)
	{
		if(data[j]=='-'&&data[j-1]=='(')
		{
			data.insert(j,"0");
			j++;	
		}

		if(j==data.size()-1)
		{
			break;
		}		
	}
	int hastrim=0;
	for(int j=0;j<100;j++)
	{
		if(data[j]=='(')
		hastrim=1;
		if(data[j]=='-'||data[j]=='.')
		{
			continue;
		}
		if(isOperate(data[j])&&hastrim==1&&isdigit(data[j-1]))
		{
			data.insert(j,")");
			hastrim=0;
			j++;
		}
		if(j==data.size()-1)
		{
			break;
		}		
		
	}
}

		//ɾ���ո���ɣ�
		void trimSpace(std::string &data) {
			std::string delem = " ";   //���ַ�: �ո����tab��
			std::string::size_type pos = data.find_first_of(delem, 0);
			while (pos != std::string::npos) {
				data.erase(pos, 1);
				pos = data.find_first_of(delem, 0);
			}
		}
				//��βû�еȺ������֮����ɣ�
		void addEqual(std::string &data) {
			if (data[data.size() - 1] != '=') {
				data = data + '=';
			}
		}

//		��"-"ʱ�ж��Ƿ�ǰ�������Ų���ӣ���ɣ�
		//ɾ�������ţ���ɣ�
		void trimInvalidBracket(std::string &data) {
			for (int i = 0; i < data.size() - 2; i++) {
				if (data[i] == '(' && data[i + 1] == ')') {
					data.erase(i, 2);
				}
			}
		}
//		//��������1 �������⣨3����3*2-9��������ɣ�
//		/*
//			����һ��
//				����һ��ջ
//				����������push();
//				������pop();
//				������ջ�ڻ���Ԫ�ء��������Ŷ��ˡ�
//				pop()����ʧ�ܡ��������Ŷ��ˡ�
//
//			��������
//				�������ͱ���flag=0;
//				����������flag++;
//				������flag--;
//				���������������У�һ��flag<0���ش���
//				�ڽ������������У�flag>0�򷵻ش���
//		*/
		void examBracket(std::string data, int errInfo[]) {
			int flag = 0;
//			printf("flag:%d\n",flag);
			for (int i = 0; i < data.size(); i++) {
				if (data[i] == '(')
					flag++;
				if (data[i] == ')')
					flag--;
				if (flag < 0) {
					append(errInfo, 1);
					//
					return ;
				}
			}
			if (flag > 0) 
			{
				append(errInfo, 1);
			}
		}
//		//��������2 ��Ч�ַ���@S&���ȣ�����ɣ�
//		/*
//				�����ַ�������ASCLL������ж�
//		*/
		void examInvalidInput(std::string data, int errInfo[]) {
			int flag = 1;
			for (int i = 0; i < data.size(); i++) {
				if (!isdigit(data[i])) {
					if (!isOperate(data[i])) {
						append(errInfo, 2);
						return;
					}
				}
			}
		}
		//��������3 ���������3+*8�ȣ������ǵ���Ϊ��Ԫ����������������ɾ��֮�󣬵õ��ı��ʽ�У�������������ߣ����Ⱥ��⣩��Ϊ��,����ʽ��ȷ��
		//С�������Ҳ��������
		void deleteBracket(std::string &data) {
			for (int i = 0; i < data.size() - 1; i++) {
				if (data[i] == '(' || data[i] == ')') {
					data.erase(i, 1);
				}
			}
		}

		void examWrongOperate(std::string data, int errInfo[]) {
			deleteBracket(data);
			if (isOperate(data[0])) {
				append(errInfo,3);
			} else if (isOperate(data[data.size() - 2])) {
				append(errInfo,3);
			} else {
				for (int i = 1; i < data.size() - 2; i++) {
					if (isOperate(data[i])) {
						if (isdigit(data[i - 1]) && isdigit(data[i + 1])) {
		
						} else {
							append(errInfo,3);
						}
					}
				}
			}
			return ;
		}
		//��������4 �Ⱥ�ʹ�ô���(8=4+8
		void examWrongEqual(std::string data,int errInfo[])
		{
			for(int i=0;i<data.size()-1;i++)
			{
				if(data[i]=='=')
				{
					append(errInfo,4);
				}
			}
		}
//		//��������4 С�������3*.4�ȣ�(���)
//		void examWrongPoint(std::string data, errInfo) {
//			if (data[0] == '.') {
//				append(errInfo, 4);
//			} else if (data[data.size() - 1] == '.') {
//				append(errInfo, 4);
//			} else {
//				for (int i = 1; i < data.size() - 1; i++) {
//					if (data[i] == '.') {
//						if (isdigit(data[i - 1]) && isdigit(data[i + 1])) {
//
//						} else {
//							append(errInfo, 4);
//						}
//					}
//				}
//			}
//		}
//		//��������5 ��0
//		void examDividingZero(std::string data, int errorInfo[]) {
//
//		}

		void append(int errorInfo[], int errType) { //��������Ӵ�������
			errorInfo[errType] = errType;

		}


		bool isEmpty(int string[]) { //�ж������Ƿ�Ϊ��
			int i = 0;
			int count = 0;
			for (i = 0; i < 10; i++)
			{
				if (string[i] != 0) {
					count++;
				}
			}
			return count == 0;
		}


		//�����ʽ�Ƿ���ȷ
		void examString(std::string data, int errorInfo[]) {
			examBracket(data, errorInfo);
			examInvalidInput(data, errorInfo);
			examWrongOperate(data, errorInfo);
//			examWrongPoint(data, errorInfo);
			//examDividingZero(data, errorInfo);//��ȷ���鲻�����ǹ�
		}
		//
	public:
		StringGuard() 
		{
//			errInfo[10]={0,0,0,0,0,0,0,0,0,0}

		}
		std::string process(std::string rawData) {
			preProcess(rawData);
			examString(rawData, errorInfo);
			if (isEmpty(errorInfo)) {
				return rawData;
			} else {
				return "error";
			}
		}
		
		void getErrorInfo()
		{

			if(errorInfo[1]==1)
				std::cout<<"��������1������ʹ�ô���"<<endl;
			if(errorInfo[2]==2)
				std::cout<<"��������2����Ч�ַ�"<<endl;
			if(errorInfo[3]==3)
			{
				std::cout<<"��������3:���������󣨺�С�������"<<endl; 
			}
			if(errorInfo[4]==4)
				std::cout<<"��������4���Ⱥ�ʹ�ô���"<<endl;
		}
		
};

int main(void) {
	std::string data = "3*-8.8=";
	StringGuard guard = StringGuard();
	std::string newData = guard.process(data);
	guard.getErrorInfo();
	
	std::cout << newData << std::endl;
	return 0;
}
