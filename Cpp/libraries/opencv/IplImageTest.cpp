/********************************************************************
@created:	2011/04/28 10:14
@author:	moshangcheng
@version:	1.0
@tag:		OpenCV IplImage
@purpose:	测试Opencv的IplImage结构	
*********************************************************************/
#include <cv.h>
#include <highgui.h>
using namespace cv;

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()	{
	IplImage* testImage = cvCreateImage(cvSize(3, 3), IPL_DEPTH_8U , 3);
	//图像为3*3
	cout << testImage->width << " " << testImage->height << endl;
	//每一行按照aligh个字节对齐
	cout << testImage->align << endl;
	//每一行占据的字节数widhtStep
	cout << testImage->widthStep << endl;
	//图像的数据占据的存储空间
	cout << testImage->imageSize << endl;
	for(int i = 0; i < testImage->height; i++)	{
		for(int j = 0; j < testImage->width; j++)	{					
			for(int k = 0; k < testImage->nChannels; k++)	{
				//也可以使用cvGet2D函数访问，但很慢
				//IplImage把图像的每个通道看作不同的元素
				cout << (int)&CV_IMAGE_ELEM(testImage, uchar, i, j*testImage->nChannels + k) << "-";				
			}
			cout << " ";
		}
		cout << endl;
	}
	cvReleaseImage(&testImage);
}