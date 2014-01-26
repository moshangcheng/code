/********************************************************************
	@created:	2011/05/03 15:42
	@author:	moshagncheng
	@version:	1.0
	@tag:		OpenCV DFT IDFT
	@purpose:	学习OpenCV，测试DFT	
*********************************************************************/
#include <cv.h>
#include <highgui.h>
using namespace cv;

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()	{
	string fileName = "腰果花.png";
	Mat srcImage, dftImage, idftImage;
	srcImage = imread(fileName, CV_LOAD_IMAGE_GRAYSCALE);
	if(srcImage.empty())	{
		cout << "读取图像失败\n";
		return -1;
	}
	//将图像的灰度转换为浮点数，否则无法进行DFT
	srcImage.convertTo(srcImage, CV_32FC1);
	normalize(srcImage, srcImage, 0, 1, CV_MINMAX);
	//显示源图像
	imshow("source-image", srcImage);
	dft(srcImage, dftImage, DFT_SCALE);
	idft(dftImage, idftImage, DFT_REAL_OUTPUT);
	//显示对频谱进行逆傅立叶变换后的图像
	//如果srcImage没有归一化，那么必须将idftImage转换成CV_8UC1类型的图像才能正常显示
	//因为对于浮点数矩阵，必须归一化才能作为图像显示；对于整数矩阵，必须为0-255才能显示
	imshow("idft-image", idftImage);
	imshow("defference-iamge", abs(idftImage-srcImage));
	waitKey();
	return 0;
}
