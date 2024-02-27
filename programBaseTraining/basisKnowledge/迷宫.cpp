#include <stdio.h>
#include <stdlib.h>

#define SIZE 12

//以顺时针秩序定义方向秩序为 上、右、下、左,如果对应当前面的方向，则为前、右、后、左
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
//申明走迷宫函数
int mazeTraverse(char* pMazeAddr, char* pCurPos, int nWidthStep, int nMazeRows, int nOffset[], int nFace);
int main()
{
	char chMazeWithBorder[SIZE+2][SIZE+2] =
	{
		 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
		 0 ,'#','#','#','#','#','#','#','#','#','#','#','#', 0 ,
		 0 ,'#','.','.','.','#','.','.','.','.','.','.','#', 0 ,
		 0 ,'.','.','#','.','#','.','#','#','#','#','.','#', 0 ,
		 0 ,'#','#','#','.','#','.','.','.','.','#','.','#', 0 ,
		 0 ,'#','.','.','.','.','#','#','#','.','#','.','.', 0 ,
		 0 ,'#','#','#','#','.','#','.','#','.','#','.','#', 0 ,
		 0 ,'#','.','.','#','.','#','.','#','.','#','.','#', 0 ,
		 0 ,'#','#','.','#','.','#','.','#','.','#','.','#', 0 ,
		 0 ,'#','.','.','.','.','.','.','.','.','#','.','#', 0 ,
		 0 ,'#','#','#','#','#','#','.','#','#','#','.','#', 0 ,
		 0 ,'#','.','.','.','.','.','.','#','.','.','.','#', 0 ,
		 0 ,'#','#','#','#','#','#','#','#','#','#','#','#', 0 ,
		 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 
	};//定义一个数组把迷宫用0字符为边界包裹起来，如果进入到0字符区域，表明已走出迷宫

	static int nOffset[4] = { -(SIZE + 2),1, (SIZE + 2), -1 };//定义数组，数组元素依次对应上、右、下、左 和当前位置的地址偏移量
	char* pchEntryPos = &chMazeWithBorder[3][1];//指明迷宫入口位置,因为有边界0字符包裹，所以在第3行，第1列
	chMazeWithBorder[3][0] = '#';//禁止从入口出来
	*pchEntryPos = 'X';//把当前位置字符变为X,打印时显示当前位置，看起来更直观
	char* pMazeAddr = &chMazeWithBorder[1][1];//迷宫首地址
	mazeTraverse(pMazeAddr, pchEntryPos, SIZE + 2, SIZE, nOffset, RIGHT);//调用走迷宫函数
	return 0;
}
/**************************************************************
函数名：mazeTraverse
功能： 走迷宫递归函数
参数： pMazeAddr - 迷宫首地址
	   pCurPos - 当前的位置指针
	   nMazeRows - 迷宫行数
       nWidthStep - 数组宽度
	   nOffset - 上、右、下、左 位置和当前位置的偏移量数组
	   nFaceDir - 当前面对方向（即上一次的行走方向） 0:上,1:右,2:下，3:左
返回:-2 - 出错 
     -1 - 走出迷宫
      0~3 : 本次走迷宫后的面对方向
***************************************************************/
int mazeTraverse(char* pMazeAddr,char * pCurPos,int nWidthStep,int nMazeRows,int nOffset[],int nFaceDir)
{
	if (0 == *pCurPos)
	{//已经进入包裹0的边界区域,表明已经走出迷宫
		return -1;
	}

	static int nPriority[4] = { RIGHT,UP,LEFT,DOWN };//根据摸墙原则，行走优先级为当前面对方向的  右、前、左、后
	bool bFlag = true;
	int nNextDirection = -2;//下一次的行走方向
	char* pNextPos;//前进位置指针
	int i, j;
	for (i = 0; i < 4; i++)//以右手边、前面、左边的顺序判断是否有墙
	{
		int nDirection = (nFaceDir + nPriority[i]) % 4;//行走方向 = 面对方向+行走优先级对应方向，由于以4为一个循环，所以取余数
		pNextPos = pCurPos + nOffset[nDirection];//pNextPos指向 当前位置+行走到新位置的偏移量,即指针指向新位置地址
		int bBreak = 0;//不循环标记赋初值为 0，表示默认情况下需要循环
		//检测该位置下的字符
		switch(*pNextPos )
		{
		case 'X': //回头路
		case  '.'://有路
			*pCurPos = '.';//上一次位置由'X'变成'.'
			*pNextPos = 'X';//前进的位置字符变成X
			system("cls");//清除屏幕
			//循环打印迷宫的每一行
			for (j = 0; j < nMazeRows; j++)
			{
				//每行迷宫地址 = 迷宫首地址 + 行号* 每行迷宫数组的列数
				printf("%s\n", pMazeAddr + j * nWidthStep);//由于迷宫有0字符包裹，因此每行迷宫字符都是一个字符串
			}
			 nNextDirection = mazeTraverse(pMazeAddr,pNextPos, nWidthStep, nMazeRows, nOffset,nDirection);//递归调用
			 
			 bBreak = 1;//走到新位置，不需要再循环，置不循环标记
			 break;
		case '#'://是墙,还需要循环
			break;
		case '\0'://是出口
			nNextDirection = -1;
			bBreak = 1; //结束循环,置不循环标记
			break;
		default://其他字符，说明出错
			bBreak = 1;//置不循环标记
			break;
		}
		if (bBreak)
			break;//不循环标记为真，跳出循环体

		
	}
	return nNextDirection;
}
