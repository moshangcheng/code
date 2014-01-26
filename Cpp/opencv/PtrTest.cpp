/********************************************************************
	@created:	2011/04/28 16:07
	@author:	moshangcheng
	@version:	1.0
	@tag:		OpenCV Ptr
	@purpose:	����OpenCV��Ptrģ����	
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
	//*anotherPtr.refcount = 2���ڿ������캯���е�����addref()
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
	cout << "ʹ��Ptr��װCvMatд������ʱ�� " << endTime-startTime << " ms" << endl;

	//���д��ģ����ǰǿ��ת��testPtrCvMat������Ч�ʻ�ܵ�
	//�ڽ��д��ģ����ʱǿ��ת��ΪCvMat���ڸ��������֮�䴫�ݲ���ʱʹ��Ptr
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
	cout << "ʹ��CvMatд������ʱ�� " << endTime-startTime << " ms" << endl;

	cvReleaseMat(&testMat);
	return 0;
}
