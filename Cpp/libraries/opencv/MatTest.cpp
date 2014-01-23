/********************************************************************
@created:	2011/04/28 11:35
@author:	moshangcheng
@version:	1.0
@tag:		OpenCV Mat
@purpose:	测试OpenCV的Mat结构，测试结果显示cv::Mat的读写效率远低于CvMat，
			使用指针访问和使用cv::Mat::at访问Mat，效率差别不大
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
	Mat testMat(3, 3, CV_32FC1);
	clock_t startTime, endTime;

	startTime = clock();
	for(int k = 0; k < TEST_SIZE; k++)	{
		for(int i = 0; i < testMat.rows; i++)	{
			for(int j = 0; j < testMat.cols; j++)	{
				testMat.at<float>(i, j) = i+j;
			}
		}
	}
	endTime = clock();
	cout << "使用cv::Mat::at写数据用时： " << endTime-startTime << " ms" << endl;


	startTime = clock();
	for(int k = 0; k < TEST_SIZE; k++)	{
		for(int i = 0; i < testMat.rows; i++)	{
			for(int j = 0; j < testMat.cols; j++)	{
				int temp = testMat.at<float>(i, j);
			}
		}
	}
	endTime = clock();
	cout << "使用cv::Mat::at读数据用时： " << endTime-startTime << " ms" << endl;


	startTime = clock();
	for(int k = 0; k < TEST_SIZE; k++)	{
		for(int i = 0; i < testMat.rows; i++)	{
			for(int j = 0; j < testMat.cols; j++)	{
				*((float*)testMat.data + i*testMat.step1(0) + j*testMat.step1(1)) = i+j;
			}
		}
	}
	endTime = clock();
	cout << "使用指针写数据用时： " << endTime-startTime << " ms" << endl;

	for(int i = 0; i < testMat.rows; i++)	{
		for(int j = 0; j < testMat.cols; j++)	{
			int temp = *((float*)testMat.data + i*testMat.step1(0) + j*testMat.step1(1));
			cout << temp << " ";
		}
		cout << endl;
	}


	startTime = clock();
	for(int k = 0; k < TEST_SIZE; k++)	{
		for(int i = 0; i < testMat.rows; i++)	{
			for(int j = 0; j < testMat.cols; j++)	{
				int temp = *((float*)testMat.data + i*testMat.step1(0) + j*testMat.step1(1));				
			}
		}
	}
	endTime = clock();
	cout << "使用指针读数据用时： " << endTime-startTime << " ms" << endl;
}