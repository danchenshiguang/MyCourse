#include<stdio.h> 
int main()
{
	//ԭ���� 
	int m[8]={23,14,28,65,72,37,96,21};
	//��ȡ����ĳ���
	int length=sizeof(m)/sizeof(m[0]);
		 //���������� 
	 int m2[length-1];
	 	 //Ҫɾ������
	 int num =65;
	 //���Ҫɾ�����±�
	 int index=100 ; 
	int i;
	//�ж���������65 
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
 	//�޸���֪���� 
 	//Ҫ�޸ĵ���28��Ϊ33
 	int num2=33;
 	//���������� 
 	printf("\n");
	 int m3[length] ;
	 // ����Ҫ�޸ĵ�ֵ
	 	for(i=0;i<length;i++)
	{
		if(m[i]==28)
		{
			index=i;
		}
	}
	//¼��������
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
