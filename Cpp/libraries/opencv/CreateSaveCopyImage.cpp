/**************************************************
* cvLoadImage, cvSaveImage, cvCreateImage, cvCopy�Լ�ͼ����ʾ������
**************************************************/

/***********************************************************************
* OpenCV example
* By Shiqi Yu 2006
***********************************************************************/

#include "cv.h"
#include "highgui.h"

int main( int argc, char** argv )
{
	IplImage* pImg; //����IplImageָ��
	pImg = cvLoadImage("lena.jpg", 0);
	IplImage* pImg2 = cvCreateImage(cvGetSize(pImg),
		pImg->depth,
		pImg->nChannels);
	cvCopy(pImg, pImg2, NULL);

	cvSaveImage("copyLena.jpg", pImg2);//��ͼ��д���ļ�

	cvNamedWindow( "Image", 1 );//��������
	
	cvShowImage( "Image", pImg );//��ʾͼ��

	cvWaitKey(0); //�ȴ�����

	cvDestroyWindow( "Image" );//���ٴ���
	cvReleaseImage( &pImg ); //�ͷ�ͼ��
	cvReleaseImage( &pImg2 ); //�ͷ�ͼ��
	return 0;
}