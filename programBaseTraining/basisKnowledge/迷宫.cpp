#include <stdio.h>
#include <stdlib.h>

#define SIZE 12

//��˳ʱ�������巽������Ϊ �ϡ��ҡ��¡���,�����Ӧ��ǰ��ķ�����Ϊǰ���ҡ�����
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
//�������Թ�����
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
	};//����һ��������Թ���0�ַ�Ϊ�߽����������������뵽0�ַ����򣬱������߳��Թ�

	static int nOffset[4] = { -(SIZE + 2),1, (SIZE + 2), -1 };//�������飬����Ԫ�����ζ�Ӧ�ϡ��ҡ��¡��� �͵�ǰλ�õĵ�ַƫ����
	char* pchEntryPos = &chMazeWithBorder[3][1];//ָ���Թ����λ��,��Ϊ�б߽�0�ַ������������ڵ�3�У���1��
	chMazeWithBorder[3][0] = '#';//��ֹ����ڳ���
	*pchEntryPos = 'X';//�ѵ�ǰλ���ַ���ΪX,��ӡʱ��ʾ��ǰλ�ã���������ֱ��
	char* pMazeAddr = &chMazeWithBorder[1][1];//�Թ��׵�ַ
	mazeTraverse(pMazeAddr, pchEntryPos, SIZE + 2, SIZE, nOffset, RIGHT);//�������Թ�����
	return 0;
}
/**************************************************************
��������mazeTraverse
���ܣ� ���Թ��ݹ麯��
������ pMazeAddr - �Թ��׵�ַ
	   pCurPos - ��ǰ��λ��ָ��
	   nMazeRows - �Թ�����
       nWidthStep - ������
	   nOffset - �ϡ��ҡ��¡��� λ�ú͵�ǰλ�õ�ƫ��������
	   nFaceDir - ��ǰ��Է��򣨼���һ�ε����߷��� 0:��,1:��,2:�£�3:��
����:-2 - ���� 
     -1 - �߳��Թ�
      0~3 : �������Թ������Է���
***************************************************************/
int mazeTraverse(char* pMazeAddr,char * pCurPos,int nWidthStep,int nMazeRows,int nOffset[],int nFaceDir)
{
	if (0 == *pCurPos)
	{//�Ѿ��������0�ı߽�����,�����Ѿ��߳��Թ�
		return -1;
	}

	static int nPriority[4] = { RIGHT,UP,LEFT,DOWN };//������ǽԭ���������ȼ�Ϊ��ǰ��Է����  �ҡ�ǰ���󡢺�
	bool bFlag = true;
	int nNextDirection = -2;//��һ�ε����߷���
	char* pNextPos;//ǰ��λ��ָ��
	int i, j;
	for (i = 0; i < 4; i++)//�����ֱߡ�ǰ�桢��ߵ�˳���ж��Ƿ���ǽ
	{
		int nDirection = (nFaceDir + nPriority[i]) % 4;//���߷��� = ��Է���+�������ȼ���Ӧ����������4Ϊһ��ѭ��������ȡ����
		pNextPos = pCurPos + nOffset[nDirection];//pNextPosָ�� ��ǰλ��+���ߵ���λ�õ�ƫ����,��ָ��ָ����λ�õ�ַ
		int bBreak = 0;//��ѭ����Ǹ���ֵΪ 0����ʾĬ���������Ҫѭ��
		//����λ���µ��ַ�
		switch(*pNextPos )
		{
		case 'X': //��ͷ·
		case  '.'://��·
			*pCurPos = '.';//��һ��λ����'X'���'.'
			*pNextPos = 'X';//ǰ����λ���ַ����X
			system("cls");//�����Ļ
			//ѭ����ӡ�Թ���ÿһ��
			for (j = 0; j < nMazeRows; j++)
			{
				//ÿ���Թ���ַ = �Թ��׵�ַ + �к�* ÿ���Թ����������
				printf("%s\n", pMazeAddr + j * nWidthStep);//�����Թ���0�ַ����������ÿ���Թ��ַ�����һ���ַ���
			}
			 nNextDirection = mazeTraverse(pMazeAddr,pNextPos, nWidthStep, nMazeRows, nOffset,nDirection);//�ݹ����
			 
			 bBreak = 1;//�ߵ���λ�ã�����Ҫ��ѭ�����ò�ѭ�����
			 break;
		case '#'://��ǽ,����Ҫѭ��
			break;
		case '\0'://�ǳ���
			nNextDirection = -1;
			bBreak = 1; //����ѭ��,�ò�ѭ�����
			break;
		default://�����ַ���˵������
			bBreak = 1;//�ò�ѭ�����
			break;
		}
		if (bBreak)
			break;//��ѭ�����Ϊ�棬����ѭ����

		
	}
	return nNextDirection;
}
