#ifndef SIFT_H
#define SIFT_H

#ifdef _CH_
#pragma package <opencv>
#endif

#ifndef _EiC
#include <stdio.h>

#include "stdlib.h"
#include "string.h" 
#include "malloc.h" 
#include "math.h" 
#include <assert.h>
#include <ctype.h>
#include <time.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <vector>

////////////////
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
//#include <stdio.h>
#include <ctype.h>
////////////////
#endif

using namespace std;

#ifdef _EiC
#define WIN32
#endif

#define NUMSIZE 2
#define GAUSSKERN 3.5
#define PI 3.14159265358979323846
/**
   Sigma of base image -- See D.L.'s paper.
*/
#define INITSIGMA 0.5
/**
   Sigma of each octave -- See D.L.'s paper.
*/
#define SIGMA sqrt(3)//1.6//
/**
   Number of scales per octave.  See D.L.'s paper.
*/
#define SCALESPEROCTAVE 2
#define MAXOCTAVES 4

/**
   Double image size before looking searching for keypoints
   Doubling finds more keypoints, but takes longer. See
   D.L.'s paper.
*/
#define CONTRAST_THRESHOLD   0.02
#define CURVATURE_THRESHOLD  10.0
#define DOUBLE_BASE_IMAGE_SIZE 1
#define peakRelThresh 0.8
#define LEN 128


//Gaussian�������о��ö�άָ��ϼ�
/* Data structure for a float image.
*/
typedef struct ImageSt {        /*������ÿһ��*/  
  float levelsigma;
  int levelsigmalength;
  float absolute_sigma;
  CvMat *Level;              
} ImageLevels;
typedef struct ImageSt1 {      /*������ÿһ����*/
  int row, col;          /* Dimensions of image. */
  float subsample;
  ImageLevels *Octave;              
} ImageOctaves;
typedef struct KeypointSt 
{
  float row, col; /* ������ԭͼ���С���������λ�� */
  float sx,sy;    /* ���������������λ��*/
  int octave,level;/*�������У����������ڵĽ��ݡ����*/

  float scale, ori,mag; /*���ڲ�ĳ߶�sigma,������orientation (range [-PI,PI])���Լ���ֵ*/
  float *descrip;       /*����������ָ�룺128ά��32ά��*/
  struct KeypointSt *next;/* Pointer to next keypoint in list. */
} *Keypoint;
//����������������


// The feature grid is has 4x4 cells - feat_grid describes the cell center positions   
#define GridSpacing 4

class MySIFT
{
	
public:
	MySIFT();
	int     numoctaves;
	CvMemStorage* storage; // temporary storage
	ImageOctaves *DOGoctaves;        //DOG pyr
	ImageOctaves *mag_thresh ;
	ImageOctaves *mag_pyr ;
	ImageOctaves *grad_pyr ;
	/* Data structure for a keypoint.  Lists of keypoints are linked
	   by the "next" field.*/

	Keypoint keypoints
		;      //������ʱ�洢�������λ�õ�
	Keypoint keyDescriptors; //��������ȷ���������Լ�����������

	/////////////////////////////
	Keypoint keypoints2;
	Keypoint keyDescriptors2;
	Keypoint Frame1Keys;// �洢��һ֡�Ĺؼ�������
	Keypoint Frame2Keys;
	int nMatch;
	//////////////////////////////////
    vector<CvPoint2D32f> MatchPoints[2];//�洢��֡�Ķ�Ӧ��λ����Ϣ
public:
	/////////////////////////////
	//ͼ���������������ʵ��ʵ������OPENCV�ĺ�������
	//void NormalizeImage(CvMat *src);
	CvMat * halfSizeImage(CvMat * im);     //��Сͼ���²���
	CvMat * doubleSizeImage(CvMat * im);   //����ͼ������ٷ���
	CvMat * doubleSizeImage2(CvMat * im);  //����ͼ�����Բ�ֵ
	float getPixelBI(CvMat * im, float col, float row);//˫���Բ�ֵ����
	void normalizeVec(float* vec, int dim);//������һ��  
	CvMat* GaussianKernel2D(float sigma);  //�õ�2ά��˹��
	float GetVecNorm( float* vec, int dim );
	void normalizeMat(CvMat* mat) ;        //�����һ��
	float* GaussianKernel1D(float sigma, int dim) ; //�õ�1ά��˹��
	float ConvolveLocWidth(float* kernel, int dim, CvMat * src, int x, int y) ;  //�ھ������ش���ȷ�����и�˹���
	void Convolve1DWidth(float* kern, int dim, CvMat * src, CvMat * dst) ;       //������ͼ���ȷ������1D��˹���
	float ConvolveLocHeight(float* kernel, int dim, CvMat * src, int x, int y) ; //�ھ������ش��߶ȷ�����и�˹���
	void Convolve1DHeight(float* kern, int dim, CvMat * src, CvMat * dst);       //������ͼ��߶ȷ������1D��˹���
	int BlurImage(CvMat * src, CvMat * dst, float sigma) ;                      //�ø�˹����ģ��ͼ��
	//����Ϊ�㷨���Ĳ���
	//SIFT�㷨��һ����ͼ��Ԥ����
	CvMat *ScaleInitImage(CvMat * im) ;                  //��������ʼ��
	//SIFT�㷨�ڶ�����������˹����������
	ImageOctaves* BuildGaussianOctaves(CvMat * image) ;  //������˹������
	//SIFT�㷨��������������λ�ü�⣬���ȷ���������λ��
	int DetectKeypoint(int numoctaves, ImageOctaves *GaussianPyr);
	void DisplayKeypointLocation(IplImage* image, ImageOctaves *GaussianPyr);
	//SIFT�㷨���Ĳ��������˹ͼ����ݶȷ���ͷ�ֵ����������������������
	void ComputeGrad_DirecandMag(int numoctaves, ImageOctaves *GaussianPyr);
	int FindClosestRotationBin (int binCount, float angle);  //���з���ֱ��ͼͳ��
	void AverageWeakBins (double* bins, int binCount);       //�Է���ֱ��ͼ�˲�
	//ȷ��������������
	bool InterpolateOrientation (double left, double middle,double right, double *degreeCorrection, double *peakValue);
	//ȷ�����������㴦����������
	void AssignTheMainOrientation(int numoctaves, ImageOctaves *GaussianPyr,ImageOctaves *mag_pyr,ImageOctaves *grad_pyr);
	//��ʾ������
	void DisplayOrientation (IplImage* image, ImageOctaves *GaussianPyr);
	//SIFT�㷨���岽����ȡ���������㴦������������
	void ExtractFeatureDescriptors(int numoctaves, ImageOctaves *GaussianPyr);
	
	//Ϊ����ʾͼ���������������ͼ��ˮƽ��ֱƴ��
	CvMat* MosaicHorizen( CvMat* im1, CvMat* im2 );
	CvMat* MosaicVertical( CvMat* im1, CvMat* im2 );
	int SiftMatch(IplImage* src,IplImage* src2);
};
#endif