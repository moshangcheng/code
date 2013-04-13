/**************************************************
* cvLoadImage, cvSaveImage, cvCreateImage, cvCopy以及图像显示的例子
**************************************************/

/***********************************************************************
* OpenCV example
* By Shiqi Yu 2006
***********************************************************************/

#include "cv.h"
#include "highgui.h"

int main( int argc, char** argv )
{
	IplImage* pImg; //声明IplImage指针
	pImg = cvLoadImage("lena.jpg", 0);
	IplImage* pImg2 = cvCreateImage(cvGetSize(pImg),
		pImg->depth,
		pImg->nChannels);
	cvCopy(pImg, pImg2, NULL);

	cvSaveImage("copyLena.jpg", pImg2);//把图像写入文件

	cvNamedWindow( "Image", 1 );//创建窗口
	
	cvShowImage( "Image", pImg );//显示图像

	cvWaitKey(0); //等待按键

	cvDestroyWindow( "Image" );//销毁窗口
	cvReleaseImage( &pImg ); //释放图像
	cvReleaseImage( &pImg2 ); //释放图像
	return 0;
}