#include<stdio.h>
int main()
{
	//ԭ���� 
	int m[8]={23,14,28,65,72,37,96,21};
	//��ȡ����ĳ���
	int length=sizeof(m)/sizeof(m[0]);
	 //���������� 
	 int m2[length+1];
	 //Ҫ��ӵ���
	 int num =77;
	 //����±��壻
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
