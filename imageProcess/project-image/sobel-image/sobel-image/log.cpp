#include "iostream"
#include "math.h"
#include "opencv.hpp"
using namespace std;
using namespace cv;
const double π = 3.14;
bool ImageBlockData(uchar* lpData, long Width, long Height, int Temx, int Temy, long WindWidth, long WindHeight, uchar* TempData) {
	int Temi, Temj, Temu, Temv;
	for (Temi = 0; Temi < WindHeight; Temi++)
	{
		for (Temj = 0; Temj < WindWidth; Temj++)
		{
			Temu = Temy + Temi - WindHeight / 2;
			Temv = Temx + Temj - WindWidth / 2;
			if (Temu < 0)   Temu = -Temu - 1;
			if (Temv < 0)   Temv = -Temv - 1;
			if (Temu >= Height) Temu = 2 * Height - Temu - 1;
			if (Temv >= Width)  Temv = 2 * Width - Temv - 1;
			TempData[Temi * WindWidth + Temj] = lpData[Temu * Width + Temv];
		}	
	}return true;
	
}
int main()
{
	Mat Image, grayImage, out_Image, l_out_Image;   //out_Image为结果图像
	Image = imread("花(高斯2).png");
	namedWindow("原图", 1);
	imshow("原图", Image);
	long width = Image.cols; //图片的宽
	long height = Image.rows;//图片的高
	//const int length = Image.cols * Image.rows;
	cvtColor(Image, grayImage, COLOR_RGB2GRAY);
	out_Image = grayImage.clone();
	l_out_Image = grayImage.clone();
	uchar* start_image;
	uchar* end_image;
	uchar* l_end_image;

	start_image = (uchar*)calloc((grayImage.cols) * (grayImage.rows), sizeof(uchar));
	end_image = (uchar*)calloc((grayImage.cols) * (grayImage.rows), sizeof(uchar));
	l_end_image = (uchar*)calloc((grayImage.cols) * (grayImage.rows), sizeof(uchar));
	for (int i = 0; i < height; i++)
	{
		uchar* a = grayImage.ptr<uchar>(i);
		for (int j = 0; j < width; j++)
		{
			//printf("%u\t", a[i]);
			start_image[i * width + j] = a[j];
			end_image[i * width + j] = 0;
			l_end_image[i * width + j] = 0;
			//printf("%u\t", start_image[i * width + j]);
		}
	}



	int  loG_kernel[5][5] = {
	{0, 0, -1, 0, 0},
	{0, -1, -2, -1, 0},
	{-1, -2, 16, -2, -1},
	{0, -1, -2, -1, 0},
	{0, 0, -1, 0, 0}
	};
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			double loG_value = 0;
			uchar* temp_block = (uchar*)calloc(25, sizeof(uchar));
			bool is_true = ImageBlockData(start_image, width, height, j, i, 5, 5, temp_block);
			for (int m = -2; m <= 2; m++) {
				for (int n = -2; n <= 2; n++) {
					loG_value += loG_kernel[m + 2][n + 2] * temp_block[(m + 2) * 5 + (n + 2)];
				}
			}
			end_image[i * width + j] = loG_value;
		}
	}

	for (int i = 0; i < height; i++)
	{
		uchar* result = out_Image.ptr<uchar>(i);
		for (int j = 0; j < width; j++)
		{
			result[j] = end_image[i * width + j];
			//printf("%d\t", end_image[i * width + j]);
		}
	}

	//laplacian-----------------------
	int  laplacian_kernel[3][3] = { {0, 1, 0}, {1, -4, 1}, {0, 1, 0} };
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			double laplacian_value = 0;
			uchar* laplacian_block = (uchar*)calloc(9, sizeof(uchar));
			bool is_true = ImageBlockData(start_image, width, height, j, i, 3, 3, laplacian_block);
			for (int m = -1; m <= 1; m++) {
				for (int n = -1; n <= 1; n++) {
					laplacian_value += laplacian_kernel[m + 1][n + 1] * laplacian_block[(m + 1) * 3 + (n + 1)];
				}
			}
			l_end_image[i * width + j] = laplacian_value;
		}
	}
	for (int i = 0; i < height; i++)
	{
		uchar* result = l_out_Image.ptr<uchar>(i);
		for (int j = 0; j < width; j++)
		{
			result[j] = l_end_image[i * width + j];
			//printf("%d\t", end_image[i * width + j]);
		}
	}

	namedWindow("loG算子结果", 1);
	imshow("loG算子结果", out_Image);
	namedWindow("laplacian算子结果", 1);
	imshow("laplacian算子结果", l_out_Image);
	waitKey(0);
	return 0;
}