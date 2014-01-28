/********************************************************************
@created:	2011/04/28 9:50
@author:	moshangcheng
@version:	1.0
@tag:		OpenCV CvMat
@purpose:	测试OpenCV的CvMat结构
*********************************************************************/
#include <cv.h>
#include <highgui.h>
using namespace cv;

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()	{
	CvMat* testMat = cvCreateMat(3, 3, CV_32FC3);
	//CvMat中的refcount没有作用
	//CvMat anotherCvMat = *testMat;
	for(int i = 0; i < testMat->rows; i++)	{
		for(int j = 0; j < testMat->cols; j++)	{
			//单通道矩阵的访问方式
			//cvSet2D(testMat, i, j, cvRealScalar(i+j));
			//CV_MAT_ELEM(*testMat, uchar, i, j) = i+j;
			//多通道矩阵访问方式，也就是说CvMat把多个通道的元素看作一个元素
			float* temp = (float*)CV_MAT_ELEM_PTR(*testMat, i, j);
			for(int k = 0; k < 3; k++)	{				
				//*((float*)CV_MAT_ELEM_PTR(*testMat, i, j) + k) = i+j+k;
				temp[k] = i + j + k;
			}			
		}
	}
	//虽然OpenCV的文档指出CvMat按行存储，每行按4字节对齐。但是从测试结果来看，每行并没有对齐。
	//Ref: http://www.opencv.org.cn/forum/viewtopic.php?f=1&t=3725&start=0
	cout << (int)(CV_MAT_ELEM_PTR(*testMat, 2, 2) - testMat->data.ptr)/CV_ELEM_SIZE(testMat->type) + 1 << endl;
	for(int i = 0; i < testMat->rows; i++)	{
		for(int j = 0; j < testMat->cols; j++)	{
			//cout << (int)(&CV_MAT_ELEM(*testMat, uchar, i, j)) << "-" << (int)CV_MAT_ELEM(*testMat, uchar, i, j) << " ";
			cout << (int)CV_MAT_ELEM_PTR(*testMat, i, j) << "-" << (float)CV_MAT_ELEM(*testMat, float, i, j) << " ";			
		}
		cout << endl;
	}
	cvReleaseMat(&testMat);
	return 0;
}