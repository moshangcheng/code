/********************************************************************
@created:	2011/04/28 10:14
@author:	moshangcheng
@version:	1.0
@tag:		OpenCV IplImage
@purpose:	����Opencv��IplImage�ṹ	
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
	//ͼ��Ϊ3*3
	cout << testImage->width << " " << testImage->height << endl;
	//ÿһ�а���aligh���ֽڶ���
	cout << testImage->align << endl;
	//ÿһ��ռ�ݵ��ֽ���widhtStep
	cout << testImage->widthStep << endl;
	//ͼ�������ռ�ݵĴ洢�ռ�
	cout << testImage->imageSize << endl;
	for(int i = 0; i < testImage->height; i++)	{
		for(int j = 0; j < testImage->width; j++)	{					
			for(int k = 0; k < testImage->nChannels; k++)	{
				//Ҳ����ʹ��cvGet2D�������ʣ�������
				//IplImage��ͼ���ÿ��ͨ��������ͬ��Ԫ��
				cout << (int)&CV_IMAGE_ELEM(testImage, uchar, i, j*testImage->nChannels + k) << "-";				
			}
			cout << " ";
		}
		cout << endl;
	}
	cvReleaseImage(&testImage);
}