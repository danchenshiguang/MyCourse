#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main()
{
	char a[12][12]={"############", //����˫�±����� 
				    "#...#......#",
				    "..#.#.####.#",
				    "###.#....#.#",
					"#....###.#..",
					"####.#.#.#.#",
					"#..#.#.#.#.#",
				    "##.#.#.#.#.#",
				    "#........#.#",
				    "######.###.#",
					"#......#...#",
					"############"};
	mazeTraverse(a,&a[2][0]);//ʹ�ú��� 
 	return 0;
		}
void mazeTraverse(char a[][12],char*m) //���庯�� 
{
	char*p1,*p2,*mid; //p1����ʼ��ָ�룬p2��Ŀ�ĵ�ָ�룬mid���м�ָ�� 
	int i1=0,i2=0;//i1��i2��������ӡ�Թ������� 
	int x=2,y=1;//x��y������ȷ����һ��Ŀ�ĵص����� 
	int counter=0 ;//counter���������� 
	p1=m;//��ʼ���� 
	*p1='x';
	while(p2!=&a[4][11])//��δ�ߵ�Ŀ�ĵ�ʱ����ѭ�� 
	{
		counter++; 
		p2=&a[x][y];
		*p2='x';
		*p1='.' ;
		while(i2<=11)//��ӡ�Թ���ѭ�� 
		{
			printf("%c ",a[i1][i2]);
			i2++;
			if(i2==12)
			{
				i1++;
				i2=0;
				printf("\n");
			}
			if(i1==12)
			{
				printf("\n(%d,%d)  ���ǵ�%d��\n\n",x+1,y+1,counter);
				i1=0;
				break;
			}//�ɹ���ӡһ���Թ�����ʾ�Թ���ʱ״̬
		}
		system ("cls"); 
		if(p2-p1==1)//�ɳ�ʼ�غ�Ŀ�ĵ�ȷ������1Ϊ���ߣ�if���ж���ʱ������˵�ǰ������ ���������ж��ұ�����ǽ�����ж�ǰ������ǽ������ж��������ǽ 
		{
			if(a[x+1][y]=='#')  
			{
				if(a[x][y+1]=='#')
				{
					if(a[x-1][y]=='#')
					{
						mid=p2;
						y--;
						p1=mid;	
						continue;
					}
					else if(a[x-1][y]=='.'||a[x-1][y]=='x')
					{
						mid=p2;
						x--;
						p1=mid;
						continue;
					}
				}
				else if(a[x][y+1]=='.'||a[x][y+1]=='x')
				{
					mid=p2;
					y++;
					p1=mid;
					continue;
				}
			}
			else if(a[x+1][y]=='.'||a[x+1][y]=='x')
			{
				mid=p2;
				x++;
				p1=mid;
				continue;
			}
		}
		if(p2-p1==-1)//�ɳ�ʼ�غ�Ŀ�ĵ�ȷ������-1Ϊ������ 
		{
			if(a[x-1][y]=='#')
			{
				if(a[x][y-1]=='#')
				{
					if(a[x+1][y]=='#')
					{
						mid=p2;
						y++;
						p1=mid;	
						continue;
					}
					else if(a[x+1][y]=='.'||a[x+1][y]=='x')
					{
						mid=p2;
						x++;
						p1=mid;
						continue;
					}
				}
				else if(a[x][y-1]=='.'||a[x][y-1]=='x')
				{
					mid=p2;
					y--;
					p1=mid;
					continue;
				}
			}
			else if(a[x-1][y]=='.'||a[x-1][y]=='x')
			{
				mid=p2;
				x--;
				p1=mid;
				continue;
			}
		}
		if(p2-p1==-12)//�ɳ�ʼ�غ�Ŀ�ĵ�ȷ������-12Ϊ���� 
		{
			if(a[x][y+1]=='#')
			{
				if(a[x-1][y]=='#')
				{
					if(a[x][y-1]=='#')
					{
						mid=p2;
						x++;
						p1=mid;
						continue;
					}
					else if(a[x][y-1]=='.'||a[x][y-1]=='x')
					{
						mid=p2;
						y--;
						p1=mid;
						continue;
					}
				}
				else if(a[x-1][y]=='.'||a[x-1][y]=='x')
				{
					mid=p2;
					x--;
					p1=mid;
					continue;
				}
			}
			else if(a[x][y+1]=='.'||a[x][y+1]=='x')
			{
				mid=p2;
				y++;
				p1=mid;
				continue;
			}
		}
		if(p2-p1==12)//�ɳ�ʼ�غ�Ŀ�ĵ�ȷ������12Ϊ������ 
		{
			if(a[x][y-1]=='#')
			{
				if(a[x+1][y]=='#')
				{
					if(a[x][y+1]=='#')
					{
						mid=p2;
						x--;
						p1=mid;
						continue;
					}
					else if(a[x][y+1]=='.'||a[x][y+1]=='x')
					{
						mid=p2;
						y++;
						p1=mid;
						continue;
					}
				}
				else if(a[x+1][y]=='.'||a[x+1][y]=='x')
				{
					mid=p2;
					x++;
					p1=mid;
					continue;
				}
			}
			else if(a[x][y-1]=='.'||a[x][y-1]=='x')
			{
				mid=p2;
				y--;
				p1=mid;
				continue;
			}
		}
	}
}
