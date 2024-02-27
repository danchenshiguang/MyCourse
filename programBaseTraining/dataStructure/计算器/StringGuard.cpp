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
		预处理：（1）删除所有空格
				（2）开头遇到”-“，加0
				（3）结尾没有”=“，补”=“
				（4）删除空括号
		*/
		void preProcess(std::string &data) {
			trimSpace(data);
			addZero(data);
			addEqual(data);
			trimInvalidBracket(data);
		}

		//删除空格（完成）
		void trimSpace(std::string &data) {
			std::string delem = " ";   //空字符: 空格或者tab键
			std::string::size_type pos = data.find_first_of(delem, 0);
			while (pos != std::string::npos) {
				data.erase(pos, 1);
				pos = data.find_first_of(delem, 0);
			}
		}
 
		//在开头为"-"前加0（完成）
		void addZero(std::string &data) {
			if (data[0] == '-') {
				data = "0" + data;
			}
		}
		//结尾没有等号则添加之（完成）
		void addEqual(std::string &data) {
			if (data[data.size() - 1] != '=') {
				data = data + '=';
			}
		}
		//删除空括号（完成）
		void trimInvalidBracket(std::string &data) {
			for (int i = 0; i < data.size() - 2; i++) {
				if (data[i] == '(' && data[i + 1] == ')') {
					data.erase(i, 2);
				}
			}
		}
		//错误类型1 括号问题（3）（3*2-9））（完成）
		/*
			方案一：
				设置一个栈
				遇到左括号push();
				右括号pop();
				最终若栈内还有元素【即左括号多了】
				pop()操作失败【即右括号多了】

			方案二：
				设置整型变量flag=0;
				见到左括号flag++;
				右括号flag--;
				在整个遍历过程中，一旦flag<0返回错误
				在结束遍历过程中，flag>0则返回错误
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
		//错误类型2 无效字符（@S&￥等）（完成）
		/*
				遍历字符串利用ASCLL码逐个判断
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
		//错误类型3 错误操作（3+*8等）
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
		//错误类型4 小数点错误（3*.4等）
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
			examDividingZero(data, errorInfo);//不确定归不归我们管
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
