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
	 //标记下标五；
	 int index =5;
	int i;
	for(i=0;i<(length+1);i++)
	  {
	  	if(i<index)
	  	{
	  		m2[i]=m[i];
		  }
		  else if(i==index)
		  {
		  	m2[i]=num;
		  }
		  else if(i>index)
		  {
		  	m2[i]=m[i-1];
		  }
	  }
	  	 for(i=0;i<(length+1);i++)
	 {
	 	printf("%d\t",m2[i]);
	 
	 }
	
}
