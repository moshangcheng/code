/********************************************************************
@created:	2011/04/28 9:50
@author:	moshangcheng
@version:	1.0
@tag:		OpenCV CvMat
@purpose:	����OpenCV��CvMat�ṹ
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
	//CvMat�е�refcountû������
	//CvMat anotherCvMat = *testMat;
	for(int i = 0; i < testMat->rows; i++)	{
		for(int j = 0; j < testMat->cols; j++)	{
			//��ͨ������ķ��ʷ�ʽ
			//cvSet2D(testMat, i, j, cvRealScalar(i+j));
			//CV_MAT_ELEM(*testMat, uchar, i, j) = i+j;
			//��ͨ��������ʷ�ʽ��Ҳ����˵CvMat�Ѷ��ͨ����Ԫ�ؿ���һ��Ԫ��
			float* temp = (float*)CV_MAT_ELEM_PTR(*testMat, i, j);
			for(int k = 0; k < 3; k++)	{				
				//*((float*)CV_MAT_ELEM_PTR(*testMat, i, j) + k) = i+j+k;
				temp[k] = i + j + k;
			}			
		}
	}
	//��ȻOpenCV���ĵ�ָ��CvMat���д洢��ÿ�а�4�ֽڶ��롣���ǴӲ��Խ��������ÿ�в�û�ж��롣
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