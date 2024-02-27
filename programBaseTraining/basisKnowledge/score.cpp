#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define _TOTAL_PERSONS_ 100
#define _FILE_NAME_ "d:\\score.dat"
typedef struct tagSTUDENT
{
	char szStuName[30];//ѧ������
	int nStuID;//ѧ��
	float fMathScore;//��ѧ�ɼ�
	float fProgScore;//������Ƴɼ�
	float fEnglishScore;//Ӣ����Ƴɼ�
	float fAverScore;//ƽ���ɼ�
}STUDENT;
/**********************************************************
�������� void flushStdin()
����: ��
����: ��
���ܣ� ���������ַ���������̻���
**********************************************************/
void flushStdin()
{
	scanf("%*[^\n]%*c");
}
/**********************************************************
�������� int ReadData(STUDENT* pStuBuf, int nBufSize)
����: pStuBuf - ѧ����Ϣ�ṹ��ָ�루���飩
	 nBufSize - ��������С������Ԫ����Ŀ��
����:  ��ȡ����������ݼ�¼����
���ܣ� �ں����д��Ѵ����ļ���������ļ��ɹ��������ļ��е����ݣ�
	   ������ļ�ʧ�ܣ��򴴽��ļ���¼�����ݣ�����¼�������д���ļ���
**********************************************************/
int ReadData(STUDENT* pStuBuf, int nBufSize)
{
	int nTotalPersons = 0, i;
	FILE* pFile = fopen(_FILE_NAME_, "rb");//���Ѵ��ڵ��ļ�����ֻ����ʽ��
	if (pFile)
	{//�ļ�����
		fseek(pFile, 0, SEEK_END);//�ļ�λ��ָ���ƶ����ļ�ĩβ
		int nFileLen = ftell(pFile);//����ftell��ȡ��ǰλ�õ�ƫ�������������ļ�ĩβ����˻���ļ�����
		nTotalPersons = nFileLen / sizeof(STUDENT);//ѧ������ = �ļ�����/ÿ���ṹ��С
		if (nTotalPersons > nBufSize)
			nTotalPersons = nBufSize;//����ļ��д�����������������������ڻ�������С���޸���ֵΪ��������С�������ڴ����
		fseek(pFile, 0, SEEK_SET);//�ļ�ָ���ƶ����ļ���ʼλ��
		fread(pStuBuf, sizeof(STUDENT), nTotalPersons, pFile);//���ļ���ʼλ�ÿ�ʼ��������
		fclose(pFile);//�ر��ļ�
		return nTotalPersons;//���ض�ȡ�����ݼ�¼����
	}

	pFile = fopen(_FILE_NAME_, "wb+");//�ļ�������,�����ļ�
	int bExitInput = 0;//����������
	do
	{
		printf("�������%d��ѧ����Ϣ:\n", nTotalPersons + 1);

		//��һ��ѭ��ʱ��nTotalPersonsΪ�㣬pStudentָ���һ����¼���Ժ�ÿ��ѭ��ָ����Ҫ�������ݵļ�¼
		STUDENT* pStudent = pStuBuf + nTotalPersons;

		int bValid = 1;//ѧ������Ϸ����
		//ѭ�����룬��֤ѧ��������ȷ
		do
		{
			bValid = 1; //ÿ��ѭ����������ѧ�źϷ����Ϊ1
			printf("ѧ��:");
			if (0 == scanf("%d", &pStudent->nStuID))
			{//û�гɹ�¼������ 
				flushStdin();//��ռ��̻���
				bValid = 0;
			}

			if (pStudent->nStuID < 0)
			{//������ĿҪ�������ѧ��С��0�˳�����¼��
				bExitInput = 1;//ѧ��С��0���ý���������Ϊ1
				break;//�˳�����ѧ�ŵ�ѭ��
			}
			//���ѧ����Ч�ԣ�������ѧ�Ų��ܺ�������ѧ���ظ�
			for (i = 0; i < nTotalPersons; i++)
			{
				if (pStuBuf[i].nStuID == pStudent->nStuID)
				{//�ظ�
					bValid = 0;//����Ч���Ϊ��
					break;
				}
			}
			if (!bValid)
				printf("����ѧ�Ŵ���!\n");

		} while (!bValid);//����ѧ����Ч��Ϊ��ʱ����ѭ��

		if (bExitInput)
			break;//����������Ϊ�棬��������¼��ѭ��
		//��������
		pStudent->szStuName[0] = '\0';
		do
		{
			printf("����:");
			if (0 == scanf("%30s", pStudent->szStuName))
			{
				flushStdin();
				pStudent->szStuName[0] = '\0';
			}
		} while ('\0' == pStudent->szStuName[0]);
		//������ѧ
		pStudent->fMathScore = -1.0f;
		do
		{
			printf("��ѧ�ɼ�:");
			if (0 == scanf("%f", &pStudent->fMathScore))
			{
				flushStdin();
				pStudent->fMathScore = -1.0f;
			}

		} while (pStudent->fMathScore < 0.0f || pStudent->fMathScore>100.0f);

		//�������ɼ�
		pStudent->fProgScore = -1.0f;
		do
		{
			printf("����ɼ�:");
			if (0 == scanf("%f", &pStudent->fProgScore))
			{
				flushStdin();
				pStudent->fProgScore = -1.0f;
			}

		} while (pStudent->fProgScore < 0.0f || pStudent->fProgScore>100.0f);
		//����Ӣ��ɼ�
		pStudent->fEnglishScore = -1.0f;
		do
		{
			printf("Ӣ��ɼ�:");
			if (0 == scanf("%f", &pStudent->fEnglishScore))
			{
				flushStdin();
				pStudent->fEnglishScore = -1.0f;
			}

		} while (pStudent->fEnglishScore < 0.0f || pStudent->fEnglishScore>100.0f);
		pStudent->fAverScore = 0.0f;
		nTotalPersons++;//����������1

	} while (nTotalPersons < nBufSize);
	if (pFile)
	{
		fwrite(pStuBuf, sizeof(STUDENT), nTotalPersons, pFile);//������д�뵽�ļ���
		fclose(pFile);//�ر��ļ�
	}
	return nTotalPersons;
}
/**********************************************************
�������� CalcuAverageScore(STUDENT* pStuBuf, int nTotalPerons)
����: pStuBuf - ѧ����Ϣ�ṹ��ָ�루���飩
	 nTotalPerons - ��¼����
����: ��
���ܣ� ����ƽ���ɼ�
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
��������void SortAverageScore(STUDENT* pStuBuf, int nTotalPerons)
����: pStuBuf - ѧ����Ϣ�ṹ��ָ�루���飩
	  nTotalPerons - ��¼����
����: ��
���ܣ� ��ƽ���ɼ��Ӵ�С��˳���������ݼ�¼������ӡ������Ϣ
	   ���򷽷�Ϊð������
**********************************************************/
void SortAverageScore(STUDENT* pStuBuf, int nTotalPerons)
{
	int i;
	for (i = 0; i < nTotalPerons - 1; i++)
	{
		if (pStuBuf[i].fAverScore < pStuBuf[i + 1].fAverScore)
		{// ��һ����¼��ƽ���ɼ����ڵ�ǰ��¼��ƽ���ɼ�������������Ҫ��
			//�ѵ�ǰ��¼�ͺ�һ����¼����
			STUDENT stu = pStuBuf[i];
			pStuBuf[i] = pStuBuf[i + 1];
			pStuBuf[i + 1] = stu;
			//ѭ��������ֵ -1������ѭ������������ѭ����ѭ������i++,ִ�к�i��Ϊ0������ͷ��ʼ������
			i = -1;
			continue;
		}
	}
	//����ʽ��ӡ����ͷ
	printf("%-12s%-20s%-12s%-12s%-12s%-12s:\n",
		"ѧ��", "����", "����", "�������", "Ӣ��", "ƽ���ɼ�");


	//pStudent �ٳ�ʼʱָ�򻺳��׵�ַ���Ժ�ÿ��ѭ����ɽ�������1���㣬ָ����һ�����ݼ�¼
	STUDENT* pStudent = pStuBuf;

	for (i = 0; i < nTotalPerons; i++, pStudent++)
	{

		printf("%-12d%-20s%-12.1f%-12.1f%-12.1f%-12.1f\n",
			pStudent->nStuID, pStudent->szStuName, pStudent->fMathScore,
			pStudent->fProgScore, pStudent->fEnglishScore, pStudent->fAverScore);
	}
}
/**********************************************************
��������void StatAverageScore(STUDENT* pStuBuf, int nTotalPerons)
����: pStuBuf - ѧ����Ϣ�ṹ��ָ�루���飩
	  nTotalPerons - ��¼����
����: ��
���ܣ� ͳ��ƽ���ɼ����š������С��� ����
**********************************************************/
void StatAverageScore(STUDENT* pStuBuf, int nTotalPerons)
{
	if (nTotalPerons <= 0)
		return;
	int nExcellentCnts = 0;//���������
	int nGoodCnts = 0;//���ü�����
	int nMediumCnts = 0;//�еȼ�����
	int nBadCnts = 0;//��ȼ�����
	int i;
	// pStudent �ٳ�ʼʱָ�򻺳��׵�ַ���Ժ�ÿ��ѭ����ɽ�������1���㣬ָ����һ�����ݼ�¼
	STUDENT* pStudent = pStuBuf;
	for (i = 0; i < nTotalPerons; i++, pStudent++)
	{//�� if .. else ���������ݵ�ͳ��
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
	//��ӡ����
	printf("�������: %5.1f %%\n���ñ��� : %5.1f%%\n�б���: %5.1f%%\n�����: %5.1f%%\n",
		nExcellentCnts * fRatio, nGoodCnts * fRatio, nMediumCnts * fRatio, nBadCnts * fRatio);
}
int main()
{
	//����ѧ����Ϣ�ṹ�����飬����ÿ��Ԫ�ظ�0��ֵ
	STUDENT arrayStu[_TOTAL_PERSONS_] = { {"",0,0.0f,0.0f,0.0f,0.0f} };
	int nTotalPerons = ReadData(arrayStu, _TOTAL_PERSONS_);
	CalcuAverageScore(arrayStu, nTotalPerons);
	SortAverageScore(arrayStu, nTotalPerons);
	StatAverageScore(arrayStu, nTotalPerons);

	return 1;
}
