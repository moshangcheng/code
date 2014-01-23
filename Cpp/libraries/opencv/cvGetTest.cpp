/********************************************************************
@created:	2011/04/28 11:05
@author:	moshangcheng
@version:	1.0
@tag:		OpenCV cvGet2D
@purpose:	测试OpenCV的cvGet2D函数的效率，测试结果显示使用宏读写数据的效率是前者的10到20倍
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
	cout << "使用宏写数据用时： " << endTime-startTime << " ms" << endl;


	startTime = clock();
	for(int k = 0; k < TEST_SIZE; k++)	{
		for(int i = 0; i < testMat->rows; i++)	{
			for(int j = 0; j < testMat->cols; j++)	{
				int temp = *CV_MAT_ELEM_PTR(*testMat, i, j);
			}
		}
	}
	endTime = clock();
	cout << "使用宏读数据用时： " << endTime-startTime << " ms" << endl;


	startTime = clock();
	for(int k = 0; k < TEST_SIZE; k++)	{
		for(int i = 0; i < testMat->rows; i++)	{
			for(int j = 0; j < testMat->cols; j++)	{
				cvSet2D(testMat, i, j, cvRealScalar(i+j));
			}
		}
	}
	endTime = clock();
	cout << "使用cvSet2D写数据用时： " << endTime-startTime << " ms" << endl;


	startTime = clock();
	for(int k = 0; k < TEST_SIZE; k++)	{
		for(int i = 0; i < testMat->rows; i++)	{
			for(int j = 0; j < testMat->cols; j++)	{
				CvScalar temp = cvGet2D(testMat, i, j);
			}
		}
	}
	endTime = clock();
	cout << "使用cvGet2D读数据用时： " << endTime-startTime << " ms" << endl;
	cvReleaseMat(&testMat);
}