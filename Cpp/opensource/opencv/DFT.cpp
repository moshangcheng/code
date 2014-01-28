/********************************************************************
@created:	2011/04/21 16:38
@author:	moshangcheng
@version:	1.1
@tag:		DFT opencv
@purpose:	练习使用OPENCV，熟悉DFT
*********************************************************************/
#include <cv.h>
#include <highgui.h>
using namespace cv;

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main(int argc, char ** argv)	{
	const char* filename = argc >=2 ? argv[1] : "腰果花.png";
	//从文件读取图像，同时转换为灰度图
	Mat img = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
	if( img.empty() )	{
		return -1;
	}
	//改变图像大小，使之能更快的进行FFT
	//计算最优尺寸
	int M = getOptimalDFTSize( img.rows );
	int N = getOptimalDFTSize( img.cols );
	Mat padded;
	//创建最优尺寸的图像，原图与新图左上对齐，其余补0
	copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, BORDER_CONSTANT, Scalar::all(0));
	imshow("ORIGIN-IMAGE", padded);
	//将图像灰度由8位整数转换为32位浮点数，为DFT做准备
	Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
	Mat complexImg;
	merge(planes, 2, complexImg);
	//输入图像是双频道复数矩阵，计算得到的频谱也用双频道复数矩阵表示，因此不会将频谱压缩成一个实数矩阵表示（参考API）
	dft(complexImg, complexImg);

	// compute log(1 + sqrt(Re(DFT(img))**2 + Im(DFT(img))**2))
	split(complexImg, planes);
	//*(planes[0].refcount) = 1
	magnitude(planes[0], planes[1], planes[0]);
	//*(planes[0].refcount) = 2
	Mat mag = planes[0];
	mag += Scalar::all(1);
	log(mag, mag);//如果不取对数，归一化之后频谱只有一个白点，说明频谱低频分量强度高。

	// crop the spectrum, if it has an odd number of rows or columns
	mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));

	int cx = mag.cols/2;
	int cy = mag.rows/2;
	//将低频分量平移到原点
	Mat tmp;
	//*(planes[0].refcount) = 3
	Mat q0(mag, Rect(0, 0, cx, cy));
	//*(planes[0].refcount) = 4
	Mat q1(mag, Rect(cx, 0, cx, cy));
	//*(planes[0].refcount) = 5
	Mat q2(mag, Rect(0, cy, cx, cy));
	//*(planes[0].refcount) = 6
	Mat q3(mag, Rect(cx, cy, cx, cy));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(mag, mag, 0, 1, CV_MINMAX);//归一化是为了使浮点数精度的图像能正确显示

	imshow("FREQUENCY-IMAGE", mag);
	waitKey();
	return 0;
}

