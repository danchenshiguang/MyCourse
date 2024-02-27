#include "iostream"
#include "math.h"
#include "opencv.hpp"

using namespace std;
using namespace cv;

const double π = 3.14;
int main()
{
	Mat Image, grayImage, out_Image, Gx_Image, Gy_Image;   //out_Image为结果图像
	Image = imread("花(高斯2).png");
	namedWindow("原图", 1);
	imshow("原图", Image);

	cvtColor(Image, grayImage, COLOR_RGB2GRAY);
	out_Image = grayImage.clone();
	Gx_Image = grayImage.clone();
	Gy_Image = grayImage.clone();
	int width = Image.cols - 2; //图片的宽
	int height = Image.rows - 2;//图片的高
	double Gx = 0;   //横向梯度值
	double Gy = 0;   //纵向梯度值
	int px = 0;
	int py = 0;
	int G = 0;

	for (int i = 1; i < height; i++)
	{
		uchar* a = grayImage.ptr<uchar>(i - 1);  //获取第i-1行的指针
		uchar* b = grayImage.ptr<uchar>(i);
		uchar* c = grayImage.ptr<uchar>(i + 1);

		uchar* d = out_Image.ptr<uchar>(i); //获取结果图第i行指针
		uchar* e = Gx_Image.ptr<uchar>(i);
		uchar* f = Gy_Image.ptr<uchar>(i);
		for (int j = 1; j < width; j++)
		{
			//Gx = (a[j - 1] + 2 * b[j - 1] + c[j - 1]) - (a[j + 1] + 2 * b[j + 1] + c[j + 1]);//计算横向梯度值
			//Gy = (a[j - 1] + 2 * a[j] + a[j + 1]) - (c[j - 1] + 2 * c[j] + c[j + 1]);     //计算纵向梯度值
			//G = sqrt(abs(Gx)*abs(Gx) + abs(Gy)*abs(Gy));   //计算该像素点上的梯度值

			G = a[j - 1] + b[j - 1] - 4 * b[j] + b[j + 1] + c[j];
			d[j] = G;//将梯度近似值作为灰度写入结果图像中
		}
	}

	for (int i = 2; i < height-1; i++)
	{
		uchar* a = grayImage.ptr<uchar>(i-2);
		uchar* b = grayImage.ptr<uchar>(i - 1);  //获取第i-1行的指针
		uchar* c = grayImage.ptr<uchar>(i);
		uchar* d = grayImage.ptr<uchar>(i + 1);
		uchar* e = grayImage.ptr<uchar>(i+2);

		uchar* f = Gx_Image.ptr<uchar>(i);

		for (int j = 2; j < width-1; j++)
		{
			//G = sqrt(abs(Gx)*abs(Gx) + abs(Gy)*abs(Gy));   //计算该像素点上的梯度值
			//将梯度近似值作为灰度写入结果图像中
			Gx = 16 * c[j] - a[j] - b[j - 1] - 2 * b[j] - b[j + 1] - c[j - 2] - 2 * c[j - 1] - 2 * c[j + 1] - c[j + 2] - d[j - 1] - 2 * d[j] - d[j + 1] - e[j];
			f[j] = Gx;
		}
	}
	//namedWindow("横向梯度显示", 1);
	//imshow("横向梯度显示", Gx_Image);
	namedWindow("loG显示", 1);
	imshow("loG显示", Gx_Image);
	namedWindow("sobel算子边缘检测", 1);
	imshow("sobel算子边缘检测", out_Image);
	waitKey(0);
	return 0;
}