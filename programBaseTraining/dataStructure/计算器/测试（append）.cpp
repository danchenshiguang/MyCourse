#include<stdio.h>
#include<iostream>
#include<ctype.h>
#include<string>
using namespace std;
void append(int errorInfo[],int errType)//向数组添加错误类型 
{
	errorInfo[errType]=errType;
} 
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

 bool isEmpty(int string[])//判断数组是否为空 
 {
 	int i=0;
 	int count=0;
 	for(i;i<10;i++)
 	{	
 		if(string[i]!=0) 
 		{
 			count++;
		 }
	 }
	 return count==0;
 }
//错误类型4 小数点错误（3*.4等）
		void examWrongPoint(std::string data,int errInfo[]) 
		{
			if (data[0] == '.') 
			{
				append(errInfo, 4);
			} else if (data[data.size() - 1] == '.') 
			{
				append(errInfo, 4);
			} 
			else 
			{
				for (int i = 1; i < data.size() - 1; i++) 
				{
					if (data[i] == '.') 
					{
						if (isdigit(data[i - 1]) && isdigit(data[i + 1])) 
						{

						} else 
						{
							append(errInfo, 4);
						}
					}
				}
			}
		}
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
	int hasZero=0;
	for(int j=0;j<100;j++)
	{
		if(data[j]=='(')
		hastrim=1;
		if(data[j]=='-'||data[j]=='.')
		{
//			hastrim;
			continue;
		}
		if(data[j]=='0')
		{
			hasZero=1;
		}
		if(isOperate(data[j])&&hastrim==1&&hasZero==1&&isdigit(data[j-1]))
		{
			data.insert(j,")");
			hastrim=0;
			hasZero=0;
			j++;
		}
		if(j==data.size()-1)
		{
			break;
		}		
		
	}
}

//		void addBracket(std::string &data) 
//		{	
//			std::string data1="";
//			std::string data2="";
//			std::string temp="";
//			int isMid=0;
//			int isMid1=0;
//			int isRight=1;
//			for(int i=0;i<100;i++)
//			{
//				isMid=0;
//				isMid1=0;
//				isRight=1;
//				for(int j=0;j<data.size();j++)
//				{
//					if(data[j]=='-'&&(isOperate(data[j-1])||j==0))
//					{
//						isRight=0;
//						isMid=1;
//						isMid1=1;
//						if(data[j-2]=='('&&data[j+2]==')')
//						{
//							isRight=1;
//							isMid=0;
//							isMid1=0;
//							
//						}
//						continue;
//					}
//					if(isMid1==1&&isRight==0)
//					{
//						temp=data[j];
//						isMid1=0;
//						continue;
//					}
//					if(isMid==0)
//					{
//						data1+=data[j];
//					}
//					if(isMid==1)
//					{
//						data2+=data[j+1];
//					}				
//				}
//				if(isRight==0)
//				{
//					data=data1+"(0"+"-"+temp+")"+data2;
//				}
//				data1="";
//				data2="";
//				temp="";
//				isMid=0;
//				isMid1=0;
//				isRight=1;
//				
//			}
//	}
 int main(void)
 {
 	string data="(((2+1)))";
 	addBracket(data);
 	cout<<data<<endl;
// 	int errInfo[]={0,0,0,0,0,0,0,0,0,0};
// 	cout<<isEmpty(errInfo)<<endl;
// 	string data="3*.(4";
// 	bool m=0;
// 	examBracket(data,errInfo);
//// 	cout<<errInfo[1]<<endl;
// 	examWrongPoint(data,errInfo);
// 	cout<<errInfo[4]<<endl;
// 	m=isEmpty(errInfo);
// 	append(errInfo,1);
//
// 	cout<<m<<endl;
// 	
 	
 }
