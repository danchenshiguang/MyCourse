#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<malloc.h>
#include<stdlib.h>
int dat1[]={1,2,3,4,5,6,7,8,9,10};
int dat2[]={-1,-2,-3,-4,-5,-6,-7,-8,-9,-10};
int buf1;
int buf2;
int count1=0;
int count2=0;
pthread_rwlock_t rwlock;
//pthread_rwlock_t rwlock2;
//pthread_rwlock_t rwlock2;
void* thread1(void*arg)
{
	int i=*(int*)arg;
	free(arg);
	for(count1;count1<10;count1++)
	{	pthread_rwlock_wrlock(&rwlock);
		buf1=dat1[count1];
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}
}
void* thread2(void*arg)
{
	int i=*(int*)arg;
	free(arg);
	for(count2;count2<10;count2++)
	{
	//	pthread_rwlock_rdlock(&rwlock1);	
		pthread_rwlock_wrlock(&rwlock);
		buf2=dat2[count2];
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}

}
void* thread3(void*arg)
{
	int i =*(int*)arg;
	free(arg);
	int m=0;
	int n=0;
	int i1=0;
	for(i1;i1<10;i++)
	{
		pthread_rwlock_rdlock(&rwlock);
		m=buf1+buf2;
		n=buf1*buf2;
		printf("两数乘积：%d*%d=%d\n",buf1,buf2,n);
		printf("两数加和：%d+%d=%d\n",buf1,buf2,m);
		printf("\n");
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
		
	}	
}
int main(void)
{
		pthread_rwlock_init(&rwlock,NULL);
		pthread_t tip[3];
		int *p[3];
		int i;
		for(i=0;i<3;i++)
		{
			p[i]=(int*)malloc(sizeof(int));
			*p[i]=i;
		}
		pthread_create(&tip[0],NULL,thread1,(void*)p[0]);
		pthread_create(&tip[1],NULL,thread2,(void*)p[1]);
		pthread_create(&tip[2],NULL,thread3,(void*)p[2]);
		for(i=0;i<2;i++)
		{
			pthread_join(tip[i],NULL);
		}
	pthread_rwlock_destroy(&rwlock);
	return 0;	
}

