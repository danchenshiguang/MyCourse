#include <iostream>
#include <string>
#include <ctype.h>

class StringGuard {
	private:
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
			return true;
		}
		/*
		Ԥ������1��ɾ�����пո�
				��2����ͷ������-������0
				��3����βû�С�=��������=��
				��4��ɾ��������
		*/
		void preProcess(std::string &data) {
			trimSpace(data);
			addZero(data);
			addEqual(data);
			trimInvalidBracket(data);
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
 
		//�ڿ�ͷΪ"-"ǰ��0����ɣ�
		void addZero(std::string &data) {
			if (data[0] == '-') {
				data = "0" + data;
			}
		}
		//��βû�еȺ������֮����ɣ�
		void addEqual(std::string &data) {
			if (data[data.size() - 1] != '=') {
				data = data + '=';
			}
		}
		//ɾ�������ţ���ɣ�
		void trimInvalidBracket(std::string &data) {
			for (int i = 0; i < data.size() - 2; i++) {
				if (data[i] == '(' && data[i + 1] == ')') {
					data.erase(i, 2);
				}
			}
		}
		//��������1 �������⣨3����3*2-9��������ɣ�
		/*
			����һ��
				����һ��ջ
				����������push();
				������pop();
				������ջ�ڻ���Ԫ�ء��������Ŷ��ˡ�
				pop()����ʧ�ܡ��������Ŷ��ˡ�

			��������
				�������ͱ���flag=0;
				����������flag++;
				������flag--;
				���������������У�һ��flag<0���ش���
				�ڽ������������У�flag>0�򷵻ش���
		*/
		void examBracket(std::string data, int errInfo[]) {
			int flag = 0;
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
			if (flag > 0) {
				append(errInfo, 1);
			}
		}
		//��������2 ��Ч�ַ���@S&���ȣ�����ɣ�
		/*
				�����ַ�������ASCLL������ж�
		*/
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
		//��������3 ���������3+*8�ȣ�
		void examWrongOperate(std::string data, int errInfo[]) 
		{
				deleteBracket(data);
		if (isOperate(data[0])) {
			return false;
		} else if (isOperate(data[data.size() - 2])) {
			return false;
		} else {
			for (int i = 1; i < data.size() - 2; i++) {
				if (isOperate(data[i])) {
					if (isdigit(data[i - 1]) && isdigit(data[i + 1])) {
	
					} else {
						return false;
					}
				}
			}
		}
	return true;
		}
		//��������4 С�������3*.4�ȣ�
		void examWrongPoint(std::string data, int errInfo[]) {
			if (data[0] == '.') {
				append(errInfo, 4);
			} else if (data[data.size() - 1] == '.') {
				append(errInfo, 4);
			} else {
				for (int i = 1; i < data.size() - 1; i++) {
					if (data[i] == '.') {
						if (isdigit(data[i - 1]) && isdigit(data[i + 1])) {

						} else {
							append(errInfo, 4);
						}
					}
				}
			}
		}
		bool isEmpty(int[])
		{
 			int i=0;
 			int count=0;
 			for(i=0;i<10;i++);
 			{
 				if(string[i]!=0) 
 				{
 					count++;
				 }
	 		}
	 		return count==0;
		}
		void append(int errType, int errorInfo[]) 
		{
			errorInfo[errType]=errType;
		}
		void examString(std::string data, int errorInfo[]) {
			examBracket(data, errorInfo);
			examInvalidInput(data, errorInfo);
			examWrongOperate(data, errorInfo);
			examWrongPoint(data, errInfo);
			examDividingZero(data, errorInfo);//��ȷ���鲻�����ǹ�
		}
		//
	public:
		std::string process(std::string rawData, int errorInfo[]) {
			preProcess(rawData);
			examString(rawData, errorInfo);
			if (isEmpty(errInfo)) {
				return rawData;
			} else {
				return NULL;
			}
		}
};
