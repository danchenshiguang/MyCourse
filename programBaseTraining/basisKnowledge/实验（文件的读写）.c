#include<stdio.h>
int main()
{
	FILE *p;
	int a[]={1,2,3,4,5,6};int i=0,x; 
	if((p=fopen("D:\\test.txt","rw"))==NULL)
	{
		printf("fell to open the file");
	}
	else
	{
		while(i<=5)
		{
			fprintf(p,"%d",a[i]);
			i++;
		}
	}
	fscanf(p,"%d",&x);
	printf("%d",x);
	fclose(p);
}
