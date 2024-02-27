#include<stdio.h>
int main()
{
	//原数组 
	int m[8]={23,14,28,65,72,37,96,21};
	//获取数组的长度
	int length=sizeof(m)/sizeof(m[0]);
	 //创建新数组 
	 int m2[length+1];
	 //要添加的量
	 int num =77;
	 //标记数据37所在下标 
	 int index=0; 
	int i;
	for(i=0;i<length;i++)
	{
		if(m[i]==37)
		{
			index=i;
		}
	}
	for(i=0;i<(length+1);i++)
	  {
	  	if(i<index+1)
	  	{
	  		m2[i]=m[i];
		  }
		  else if(i==index+1)
		  {
		  	m2[i]=num;
		  }
		  else if(i>index+1)
		  {
		  	m2[i]=m[i-1];
		  }
	  }
	  	 for(i=0;i<(length+1);i++)
	 {
	 	printf("%d\t",m2[i]);
	 
	 }
	
}
