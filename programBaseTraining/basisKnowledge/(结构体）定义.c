#include<stdio.h>
#include<stdlib.h> 
struct Student//ѧ���ṹ�� 
{
	char name[20];
	int num;
	float score;
}; 
struct Class
{
	int room ;
	struct Student student;
};
int main ()
{
	struct Student a={"����",202,95.5};
	printf("%g\n",a.score);
	struct Student b;
	printf ("bѧ�������֣�\n");
	scanf("%s",b.name);
	printf ("bѧ����ѧ�ţ�\n");
	scanf("%d",&b.num);
	printf ("bѧ���ĳɼ���\n");
	scanf("%f",&b.score);
	printf("\n*********************\n");
	printf("bѧ�������֣�%s\n",b.name);
	printf ("bѧ����ѧ�ţ�%d\n",b.num);
	printf("bѧ���ĳɼ���%.2f\n",b.score);
	struct Class c ={		203,	{	"����",133,28.5}	};
	printf("%s",c.student.name);
}
