/********************************************************************
@created:	2011/04/28 11:05
@author:	moshangcheng
@version:	1.0
@tag:		OpenCV cvGet2D
@purpose:	����OpenCV��cvGet2D������Ч�ʣ����Խ����ʾʹ�ú��д���ݵ�Ч����ǰ�ߵ�10��20��
*********************************************************************/
#include <cv.h>
#include <highgui.h>
using namespace cv;

#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
using namespace std;

const int TEST_SIZE = 1000000;

int main()	{
	CvMat* testMat = cvCreateMat(3, 3, CV_32FC1);
	clock_t startTime, endTime;

	startTime = clock();
	for(int k = 0; k < TEST_SIZE; k++)	{
		for(int i = 0; i < testMat->rows; i++)	{
			for(int j = 0; j < testMat->cols; j++)	{
				*CV_MAT_ELEM_PTR(*testMat, i, j) = i+j;
			}
		}
	}
	endTime = clock();
	cout << "ʹ�ú�д������ʱ�� " << endTime-startTime << " ms" << endl;


	startTime = clock();
	for(int k = 0; k < TEST_SIZE; k++)	{
		for(int i = 0; i < testMat->rows; i++)	{
			for(int j = 0; j < testMat->cols; j++)	{
				int temp = *CV_MAT_ELEM_PTR(*testMat, i, j);
			}
		}
	}
	endTime = clock();
	cout << "ʹ�ú��������ʱ�� " << endTime-startTime << " ms" << endl;


	startTime = clock();
	for(int k = 0; k < TEST_SIZE; k++)	{
		for(int i = 0; i < testMat->rows; i++)	{
			for(int j = 0; j < testMat->cols; j++)	{
				cvSet2D(testMat, i, j, cvRealScalar(i+j));
			}
		}
	}
	endTime = clock();
	cout << "ʹ��cvSet2Dд������ʱ�� " << endTime-startTime << " ms" << endl;


	startTime = clock();
	for(int k = 0; k < TEST_SIZE; k++)	{
		for(int i = 0; i < testMat->rows; i++)	{
			for(int j = 0; j < testMat->cols; j++)	{
				CvScalar temp = cvGet2D(testMat, i, j);
			}
		}
	}
	endTime = clock();
	cout << "ʹ��cvGet2D��������ʱ�� " << endTime-startTime << " ms" << endl;
	cvReleaseMat(&testMat);
}