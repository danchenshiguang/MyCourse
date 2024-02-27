#include<stdio.h> 
int main()
{
	//原数组 
	int m[8]={23,14,28,65,72,37,96,21};
	//获取数组的长度
	int length=sizeof(m)/sizeof(m[0]);
		 //创建新数组 
	 int m2[length-1];
	 	 //要删除的量
	 int num =65;
	 //标记要删除的下标
	 int index=100 ; 
	int i;
	//判断数组中有65 
	for(i=0;i<length;i++)
	{
		if(m[i]==37)
		{
			index=i;
		}
	}
	for(i=0;i<(length+1);i++)
	{
 		if(i<index)
  		{
  			m2[i]=m[i];
	  	}
	  else if(i>=index)
	  {
	  	m2[i]=m[i+1];
	  }
	 }
 	for(i=0;i<(length-1);i++)
 	{
 	printf("%d\t",m2[i]);
 	}
 	//修改已知数组 
 	//要修改的量28改为33
 	int num2=33;
 	//创建新数组 
 	printf("\n");
	 int m3[length] ;
	 // 查找要修改的值
	 	for(i=0;i<length;i++)
	{
		if(m[i]==28)
		{
			index=i;
		}
	}
	//录入新数组
	 	for(i=0;i<length+1;i++)
	{
 		if(i!=index)
  		{
  			m3[i]=m[i];
	  	}
	  else if(i==index)
	  {
	  	m3[i]=num2;
	  }
	 }
 	for(i=0;i<length;i++)
 	{
 	printf("%d\t",m3[i]);
 	}

	  
	 
}
