#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define _TOTAL_PERSONS_ 100
#define _FILE_NAME_ "d:\\score.dat"
typedef struct tagSTUDENT
{
	char szStuName[30];//学生姓名
	int nStuID;//学号
	float fMathScore;//数学成绩
	float fProgScore;//程序设计成绩
	float fEnglishScore;//英语设计成绩
	float fAverScore;//平均成绩
}STUDENT;
/**********************************************************
函数名： void flushStdin()
参数: 无
返回: 无
功能： 采用逆向字符集清除键盘缓冲
**********************************************************/
void flushStdin()
{
	scanf("%*[^\n]%*c");
}
/**********************************************************
函数名： int ReadData(STUDENT* pStuBuf, int nBufSize)
参数: pStuBuf - 学生信息结构体指针（数组）
	 nBufSize - 缓冲区大小（数组元素数目）
返回:  读取或输入的数据记录条数
功能： 在函数中打开已存在文件，如果打开文件成功，读入文件中的数据；
	   如果打开文件失败，则创建文件，录入数据，并把录入的数据写如文件中
**********************************************************/
int ReadData(STUDENT* pStuBuf, int nBufSize)
{
	int nTotalPersons = 0, i;
	FILE* pFile = fopen(_FILE_NAME_, "rb");//打开已存在的文件，以只读方式打开
	if (pFile)
	{//文件存在
		fseek(pFile, 0, SEEK_END);//文件位置指针移动到文件末尾
		int nFileLen = ftell(pFile);//调用ftell获取当前位置的偏移量，由于在文件末尾，因此获得文件长度
		nTotalPersons = nFileLen / sizeof(STUDENT);//学生人数 = 文件长度/每个结构大小
		if (nTotalPersons > nBufSize)
			nTotalPersons = nBufSize;//如果文件中存入的数据条数（人数）大于缓冲区大小，修改其值为缓冲区大小，避免内存溢出
		fseek(pFile, 0, SEEK_SET);//文件指针移动到文件开始位置
		fread(pStuBuf, sizeof(STUDENT), nTotalPersons, pFile);//从文件开始位置开始读入数据
		fclose(pFile);//关闭文件
		return nTotalPersons;//返回读取的数据记录条数
	}

	pFile = fopen(_FILE_NAME_, "wb+");//文件不存在,创建文件
	int bExitInput = 0;//结束输入标记
	do
	{
		printf("请输入第%d个学生信息:\n", nTotalPersons + 1);

		//第一次循环时，nTotalPersons为零，pStudent指向第一条记录，以后每次循环指向需要输入数据的记录
		STUDENT* pStudent = pStuBuf + nTotalPersons;

		int bValid = 1;//学号输入合法标记
		//循环输入，保证学号输入正确
		do
		{
			bValid = 1; //每次循环，置输入学号合法标记为1
			printf("学号:");
			if (0 == scanf("%d", &pStudent->nStuID))
			{//没有成功录入数据 
				flushStdin();//清空键盘缓冲
				bValid = 0;
			}

			if (pStudent->nStuID < 0)
			{//按照题目要求，输入的学号小于0退出数据录入
				bExitInput = 1;//学号小于0，置结束输入标记为1
				break;//退出输入学号的循环
			}
			//检查学号有效性，即输入学号不能和以往的学号重复
			for (i = 0; i < nTotalPersons; i++)
			{
				if (pStuBuf[i].nStuID == pStudent->nStuID)
				{//重复
					bValid = 0;//置有效标记为假
					break;
				}
			}
			if (!bValid)
				printf("输入学号错误!\n");

		} while (!bValid);//输入学号有效性为假时继续循环

		if (bExitInput)
			break;//结束输入标记为真，结束数据录入循环
		//输入姓名
		pStudent->szStuName[0] = '\0';
		do
		{
			printf("姓名:");
			if (0 == scanf("%30s", pStudent->szStuName))
			{
				flushStdin();
				pStudent->szStuName[0] = '\0';
			}
		} while ('\0' == pStudent->szStuName[0]);
		//输入数学
		pStudent->fMathScore = -1.0f;
		do
		{
			printf("数学成绩:");
			if (0 == scanf("%f", &pStudent->fMathScore))
			{
				flushStdin();
				pStudent->fMathScore = -1.0f;
			}

		} while (pStudent->fMathScore < 0.0f || pStudent->fMathScore>100.0f);

		//输入程序成绩
		pStudent->fProgScore = -1.0f;
		do
		{
			printf("程序成绩:");
			if (0 == scanf("%f", &pStudent->fProgScore))
			{
				flushStdin();
				pStudent->fProgScore = -1.0f;
			}

		} while (pStudent->fProgScore < 0.0f || pStudent->fProgScore>100.0f);
		//输入英语成绩
		pStudent->fEnglishScore = -1.0f;
		do
		{
			printf("英语成绩:");
			if (0 == scanf("%f", &pStudent->fEnglishScore))
			{
				flushStdin();
				pStudent->fEnglishScore = -1.0f;
			}

		} while (pStudent->fEnglishScore < 0.0f || pStudent->fEnglishScore>100.0f);
		pStudent->fAverScore = 0.0f;
		nTotalPersons++;//输入人数加1

	} while (nTotalPersons < nBufSize);
	if (pFile)
	{
		fwrite(pStuBuf, sizeof(STUDENT), nTotalPersons, pFile);//把数据写入到文件中
		fclose(pFile);//关闭文件
	}
	return nTotalPersons;
}
/**********************************************************
函数名： CalcuAverageScore(STUDENT* pStuBuf, int nTotalPerons)
参数: pStuBuf - 学生信息结构体指针（数组）
	 nTotalPerons - 记录条数
返回: 无
功能： 计算平均成绩
**********************************************************/
void CalcuAverageScore(STUDENT* pStuBuf, int nTotalPerons)
{
	int i;
	for (i = 0; i < nTotalPerons; i++)
	{
		pStuBuf[i].fAverScore = (pStuBuf[i].fMathScore + pStuBuf[i].fProgScore + pStuBuf[i].fEnglishScore) / 3;
	}
}
/**********************************************************
函数名：void SortAverageScore(STUDENT* pStuBuf, int nTotalPerons)
参数: pStuBuf - 学生信息结构体指针（数组）
	  nTotalPerons - 记录条数
返回: 无
功能： 以平均成绩从大到小的顺序排序数据记录，并打印数据信息
	   排序方法为冒泡排序
**********************************************************/
void SortAverageScore(STUDENT* pStuBuf, int nTotalPerons)
{
	int i;
	for (i = 0; i < nTotalPerons - 1; i++)
	{
		if (pStuBuf[i].fAverScore < pStuBuf[i + 1].fAverScore)
		{// 后一条记录的平均成绩大于当前记录的平均成绩，不符合排序要求
			//把当前记录和后一条记录交换
			STUDENT stu = pStuBuf[i];
			pStuBuf[i] = pStuBuf[i + 1];
			pStuBuf[i + 1] = stu;
			//循环变量赋值 -1，继续循环，由于依次循环后循环变量i++,执行后i变为0，即从头开始再排序
			i = -1;
			continue;
		}
	}
	//按格式打印报表头
	printf("%-12s%-20s%-12s%-12s%-12s%-12s:\n",
		"学号", "姓名", "高数", "程序设计", "英语", "平均成绩");


	//pStudent 再初始时指向缓冲首地址，以后每次循环完成进行自增1运算，指向下一条数据记录
	STUDENT* pStudent = pStuBuf;

	for (i = 0; i < nTotalPerons; i++, pStudent++)
	{

		printf("%-12d%-20s%-12.1f%-12.1f%-12.1f%-12.1f\n",
			pStudent->nStuID, pStudent->szStuName, pStudent->fMathScore,
			pStudent->fProgScore, pStudent->fEnglishScore, pStudent->fAverScore);
	}
}
/**********************************************************
函数名：void StatAverageScore(STUDENT* pStuBuf, int nTotalPerons)
参数: pStuBuf - 学生信息结构体指针（数组）
	  nTotalPerons - 记录条数
返回: 无
功能： 统计平均成绩的优、良、中、差 比例
**********************************************************/
void StatAverageScore(STUDENT* pStuBuf, int nTotalPerons)
{
	if (nTotalPerons <= 0)
		return;
	int nExcellentCnts = 0;//优秀计数器
	int nGoodCnts = 0;//良好计数器
	int nMediumCnts = 0;//中等计数器
	int nBadCnts = 0;//差等计数器
	int i;
	// pStudent 再初始时指向缓冲首地址，以后每次循环完成进行自增1运算，指向下一条数据记录
	STUDENT* pStudent = pStuBuf;
	for (i = 0; i < nTotalPerons; i++, pStudent++)
	{//用 if .. else 语句完成数据的统计
		if (pStudent->fAverScore >= 90.0f)
			nExcellentCnts++;
		else if (pStudent->fAverScore >= 80.0f)
			nGoodCnts++;
		else if (pStudent->fAverScore >= 60.0f)
			nMediumCnts++;
		else
			nBadCnts++;

	}
	float fRatio = 100.0f / nTotalPerons;
	//打印比例
	printf("优秀比率: %5.1f %%\n良好比率 : %5.1f%%\n中比率: %5.1f%%\n差比率: %5.1f%%\n",
		nExcellentCnts * fRatio, nGoodCnts * fRatio, nMediumCnts * fRatio, nBadCnts * fRatio);
}
int main()
{
	//定义学生信息结构体数组，并对每个元素赋0初值
	STUDENT arrayStu[_TOTAL_PERSONS_] = { {"",0,0.0f,0.0f,0.0f,0.0f} };
	int nTotalPerons = ReadData(arrayStu, _TOTAL_PERSONS_);
	CalcuAverageScore(arrayStu, nTotalPerons);
	SortAverageScore(arrayStu, nTotalPerons);
	StatAverageScore(arrayStu, nTotalPerons);

	return 1;
}
