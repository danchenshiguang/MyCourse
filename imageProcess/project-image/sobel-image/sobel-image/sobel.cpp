#include "iostream"
#include "math.h"
#include "opencv.hpp"

using namespace std;
using namespace cv;

const double �� = 3.14;
int main()
{
	Mat Image, grayImage, out_Image, Gx_Image, Gy_Image;   //out_ImageΪ���ͼ��
	Image = imread("��(��˹2).png");
	namedWindow("ԭͼ", 1);
	imshow("ԭͼ", Image);

	cvtColor(Image, grayImage, COLOR_RGB2GRAY);
	out_Image = grayImage.clone();
	Gx_Image = grayImage.clone();
	Gy_Image = grayImage.clone();
	int width = Image.cols - 2; //ͼƬ�Ŀ�
	int height = Image.rows - 2;//ͼƬ�ĸ�
	double Gx = 0;   //�����ݶ�ֵ
	double Gy = 0;   //�����ݶ�ֵ
	int px = 0;
	int py = 0;
	int G = 0;

	for (int i = 1; i < height; i++)
	{
		uchar* a = grayImage.ptr<uchar>(i - 1);  //��ȡ��i-1�е�ָ��
		uchar* b = grayImage.ptr<uchar>(i);
		uchar* c = grayImage.ptr<uchar>(i + 1);

		uchar* d = out_Image.ptr<uchar>(i); //��ȡ���ͼ��i��ָ��
		uchar* e = Gx_Image.ptr<uchar>(i);
		uchar* f = Gy_Image.ptr<uchar>(i);
		for (int j = 1; j < width; j++)
		{
			//Gx = (a[j - 1] + 2 * b[j - 1] + c[j - 1]) - (a[j + 1] + 2 * b[j + 1] + c[j + 1]);//��������ݶ�ֵ
			//Gy = (a[j - 1] + 2 * a[j] + a[j + 1]) - (c[j - 1] + 2 * c[j] + c[j + 1]);     //���������ݶ�ֵ
			//G = sqrt(abs(Gx)*abs(Gx) + abs(Gy)*abs(Gy));   //��������ص��ϵ��ݶ�ֵ

			G = a[j - 1] + b[j - 1] - 4 * b[j] + b[j + 1] + c[j];
			d[j] = G;//���ݶȽ���ֵ��Ϊ�Ҷ�д����ͼ����
		}
	}

	for (int i = 2; i < height-1; i++)
	{
		uchar* a = grayImage.ptr<uchar>(i-2);
		uchar* b = grayImage.ptr<uchar>(i - 1);  //��ȡ��i-1�е�ָ��
		uchar* c = grayImage.ptr<uchar>(i);
		uchar* d = grayImage.ptr<uchar>(i + 1);
		uchar* e = grayImage.ptr<uchar>(i+2);

		uchar* f = Gx_Image.ptr<uchar>(i);

		for (int j = 2; j < width-1; j++)
		{
			//G = sqrt(abs(Gx)*abs(Gx) + abs(Gy)*abs(Gy));   //��������ص��ϵ��ݶ�ֵ
			//���ݶȽ���ֵ��Ϊ�Ҷ�д����ͼ����
			Gx = 16 * c[j] - a[j] - b[j - 1] - 2 * b[j] - b[j + 1] - c[j - 2] - 2 * c[j - 1] - 2 * c[j + 1] - c[j + 2] - d[j - 1] - 2 * d[j] - d[j + 1] - e[j];
			f[j] = Gx;
		}
	}
	//namedWindow("�����ݶ���ʾ", 1);
	//imshow("�����ݶ���ʾ", Gx_Image);
	namedWindow("loG��ʾ", 1);
	imshow("loG��ʾ", Gx_Image);
	namedWindow("sobel���ӱ�Ե���", 1);
	imshow("sobel���ӱ�Ե���", out_Image);
	waitKey(0);
	return 0;
}