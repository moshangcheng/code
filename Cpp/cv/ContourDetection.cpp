/**************************************************
 * �������
 * ��Ҫ������
 *      cvFindContours
 *      cvDrawContours
 **************************************************/
 
/***********************************************************************
 * OpenCV example
 * By Shiqi Yu 2006
 ***********************************************************************/
 
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
 
int main( int argc, char** argv )
{
  //����IplImageָ��
  IplImage* pImg = NULL; 
  IplImage* pContourImg = NULL;
 
 
  CvMemStorage * storage = cvCreateMemStorage(0);
  CvSeq * contour = 0;
  int mode = CV_RETR_EXTERNAL;
 
  if( argc == 3)
      if(strcmp(argv[2], "all") == 0)
	mode = CV_RETR_CCOMP; //�������������
 
 
  //��������
  cvNamedWindow("src", 1);
  cvNamedWindow("contour",1);
 
 
  //����ͼ��ǿ��ת��ΪGray
  if( argc >= 2 && 
      (pImg = cvLoadImage( argv[1], 0)) != 0 )
    {
 
      cvShowImage( "src", pImg );
 
      //Ϊ������ʾͼ������ռ�
      //3ͨ��ͼ���Ա��ò�ɫ��ʾ
      pContourImg = cvCreateImage(cvGetSize(pImg),
					  IPL_DEPTH_8U,
					  3);
      //copy source image and convert it to BGR image
      cvCvtColor(pImg, pContourImg, CV_GRAY2BGR);
 
 
      //����contour
      cvFindContours( pImg, storage, &contour, sizeof(CvContour), 
		  mode, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
 
    }
  else
    {
      //���ٴ���
      cvDestroyWindow( "src" );
	  cvDestroyWindow( "contour" );
      cvReleaseMemStorage(&storage);
 
      return -1;
    }
 
 
 
 
  //����������    
  cvDrawContours(pContourImg, contour, 
		 CV_RGB(0,0,255), CV_RGB(255, 0, 0), 
		 2, 2, 8, cvPoint(0,0));
  //��ʾͼ��
  cvShowImage( "contour", pContourImg );
 
  cvWaitKey(0);
 
 
  //���ٴ���
  cvDestroyWindow( "src" );
  cvDestroyWindow( "contour" );
  //�ͷ�ͼ��
  cvReleaseImage( &pImg ); 
  cvReleaseImage( &pContourImg ); 
 
  cvReleaseMemStorage(&storage);
 
  return 0;
}