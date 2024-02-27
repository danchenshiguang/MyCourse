#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main()
{
	char a[12][12]={"############", //定义双下标数组 
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
	mazeTraverse(a,&a[2][0]);//使用函数 
 	return 0;
		}
void mazeTraverse(char a[][12],char*m) //定义函数 
{
	char*p1,*p2,*mid; //p1是起始地指针，p2是目的地指针，mid是中间指针 
	int i1=0,i2=0;//i1，i2是用来打印迷宫的坐标 
	int x=2,y=1;//x，y是用来确定下一个目的地的坐标 
	int counter=0 ;//counter用来数步数 
	p1=m;//初始坐标 
	*p1='x';
	while(p2!=&a[4][11])//当未走到目的地时进行循环 
	{
		counter++; 
		p2=&a[x][y];
		*p2='x';
		*p1='.' ;
		while(i2<=11)//打印迷宫的循环 
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
				printf("\n(%d,%d)  这是第%d步\n\n",x+1,y+1,counter);
				i1=0;
				break;
			}//成功打印一次迷宫，显示迷宫此时状态
		}
		system ("cls"); 
		if(p2-p1==1)//由初始地和目的地确定方向，1为向东走，if中判定此时相对于人的前后左右 ，都是先判断右边有无墙，再判断前面有无墙，最后判断左边有无墙 
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
		if(p2-p1==-1)//由初始地和目的地确定方向，-1为向西走 
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
		if(p2-p1==-12)//由初始地和目的地确定方向，-12为向北走 
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
		if(p2-p1==12)//由初始地和目的地确定方向，12为向南走 
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
