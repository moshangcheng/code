/********************************************************************
	@created:	2011/04/28 16:07
	@author:	moshangcheng
	@version:	1.0
	@tag:		OpenCV Ptr
	@purpose:	测试OpenCV的Ptr模板类	
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

template<> inline void Ptr<CvMat>::delete_obj()	{
	cvReleaseMat(&obj);
}

template<> inline void Ptr<IplImage>::delete_obj()	{
	cvReleaseImage(&obj);
}

int main()	{
	CvMat* testMat = cvCreateMat(3, 3, CV_32FC3);
	Ptr<CvMat> testPtrCvMat = cvCreateMat(3, 3, CV_32FC3);
	//*anotherPtr.refcount = 2，在拷贝构造函数中调用了addref()
	Ptr<CvMat> anotherPtr = testPtrCvMat;

	clock_t startTime, endTime;

	startTime = clock();
	for(int k = 0; k < TEST_SIZE; k++)	{
		for(int i = 0; i < testPtrCvMat->rows; i++)	{
			for(int j = 0; j < testPtrCvMat->cols; j++)	{
				*CV_MAT_ELEM_PTR(*testPtrCvMat, i, j) = i+j;
			}
		}
	}
	endTime = clock();
	cout << "使用Ptr封装CvMat写数据用时： " << endTime-startTime << " ms" << endl;

	//进行大规模计算前强制转换testPtrCvMat，否则效率会很低
	//在进行大规模计算时强制转换为CvMat，在各个程序块之间传递参数时使用Ptr
	CvMat* tempCvMat = testPtrCvMat;
	startTime = clock();
	for(int k = 0; k < TEST_SIZE; k++)	{
		for(int i = 0; i < tempCvMat->rows; i++)	{
			for(int j = 0; j < tempCvMat->cols; j++)	{
				*CV_MAT_ELEM_PTR(*tempCvMat, i, j) = i+j;
			}
		}
	}
	endTime = clock();
	cout << "使用CvMat写数据用时： " << endTime-startTime << " ms" << endl;

	cvReleaseMat(&testMat);
	return 0;
}
