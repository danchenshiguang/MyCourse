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
	 //�������37�����±� 
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
