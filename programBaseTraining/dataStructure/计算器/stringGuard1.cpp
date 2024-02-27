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
		预处理：（1）删除所有空格
				（2）开头遇到”-“，加0
				（3）结尾没有”=“，补”=“
				（4）删除空括号
				(5)当为负数时，判断前后有没有括号 
		*/
		void preProcess(std::string &data) {
			trimSpace(data);
//			addZero(data);
			addEqual(data);
			trimInvalidBracket(data);
			addBracket(data);
		}
		//添加括号
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

		//删除空格（完成）
		void trimSpace(std::string &data) {
			std::string delem = " ";   //空字符: 空格或者tab键
			std::string::size_type pos = data.find_first_of(delem, 0);
			while (pos != std::string::npos) {
				data.erase(pos, 1);
				pos = data.find_first_of(delem, 0);
			}
		}
				//结尾没有等号则添加之（完成）
		void addEqual(std::string &data) {
			if (data[data.size() - 1] != '=') {
				data = data + '=';
			}
		}

//		在"-"时判断是否前后有括号并添加（完成）
		//删除空括号（完成）
		void trimInvalidBracket(std::string &data) {
			for (int i = 0; i < data.size() - 2; i++) {
				if (data[i] == '(' && data[i + 1] == ')') {
					data.erase(i, 2);
				}
			}
		}
//		//错误类型1 括号问题（3）（3*2-9））（完成）
//		/*
//			方案一：
//				设置一个栈
//				遇到左括号push();
//				右括号pop();
//				最终若栈内还有元素【即左括号多了】
//				pop()操作失败【即右括号多了】
//
//			方案二：
//				设置整型变量flag=0;
//				见到左括号flag++;
//				右括号flag--;
//				在整个遍历过程中，一旦flag<0返回错误
//				在结束遍历过程中，flag>0则返回错误
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
//		//错误类型2 无效字符（@S&￥等）（完成）
//		/*
//				遍历字符串利用ASCLL码逐个判断
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
		//错误类型3 错误操作（3+*8等）（考虑到均为二元操作符，若将括号删除之后，得到的表达式中，运算符左右两边（除等号外）均为数,则表达式正确）
		//小数点错误也包含在内
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
		//错误类型4 等号使用错误(8=4+8
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
//		//错误类型4 小数点错误（3*.4等）(完成)
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
//		//错误类型5 除0
//		void examDividingZero(std::string data, int errorInfo[]) {
//
//		}

		void append(int errorInfo[], int errType) { //向数组添加错误类型
			errorInfo[errType] = errType;

		}


		bool isEmpty(int string[]) { //判断数组是否为空
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


		//检测表达式是否正确
		void examString(std::string data, int errorInfo[]) {
			examBracket(data, errorInfo);
			examInvalidInput(data, errorInfo);
			examWrongOperate(data, errorInfo);
//			examWrongPoint(data, errorInfo);
			//examDividingZero(data, errorInfo);//不确定归不归我们管
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
				std::cout<<"错误类型1：括号使用错误"<<endl;
			if(errorInfo[2]==2)
				std::cout<<"错误类型2：无效字符"<<endl;
			if(errorInfo[3]==3)
			{
				std::cout<<"错误类型3:操作符错误（含小数点错误）"<<endl; 
			}
			if(errorInfo[4]==4)
				std::cout<<"错误类型4：等号使用错误"<<endl;
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
