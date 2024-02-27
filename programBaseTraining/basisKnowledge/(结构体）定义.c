#include<stdio.h>
#include<stdlib.h> 
struct Student//学生结构体 
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
	struct Student a={"张三",202,95.5};
	printf("%g\n",a.score);
	struct Student b;
	printf ("b学生的名字：\n");
	scanf("%s",b.name);
	printf ("b学生的学号：\n");
	scanf("%d",&b.num);
	printf ("b学生的成绩：\n");
	scanf("%f",&b.score);
	printf("\n*********************\n");
	printf("b学生的名字：%s\n",b.name);
	printf ("b学生的学号：%d\n",b.num);
	printf("b学生的成绩：%.2f\n",b.score);
	struct Class c ={		203,	{	"李四",133,28.5}	};
	printf("%s",c.student.name);
}
