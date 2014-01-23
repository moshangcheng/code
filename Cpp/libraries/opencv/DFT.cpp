/********************************************************************
@created:	2011/04/21 16:38
@author:	moshangcheng
@version:	1.1
@tag:		DFT opencv
@purpose:	��ϰʹ��OPENCV����ϤDFT
*********************************************************************/
#include <cv.h>
#include <highgui.h>
using namespace cv;

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main(int argc, char ** argv)	{
	const char* filename = argc >=2 ? argv[1] : "������.png";
	//���ļ���ȡͼ��ͬʱת��Ϊ�Ҷ�ͼ
	Mat img = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
	if( img.empty() )	{
		return -1;
	}
	//�ı�ͼ���С��ʹ֮�ܸ���Ľ���FFT
	//�������ųߴ�
	int M = getOptimalDFTSize( img.rows );
	int N = getOptimalDFTSize( img.cols );
	Mat padded;
	//�������ųߴ��ͼ��ԭͼ����ͼ���϶��룬���ಹ0
	copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, BORDER_CONSTANT, Scalar::all(0));
	imshow("ORIGIN-IMAGE", padded);
	//��ͼ��Ҷ���8λ����ת��Ϊ32λ��������ΪDFT��׼��
	Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
	Mat complexImg;
	merge(planes, 2, complexImg);
	//����ͼ����˫Ƶ���������󣬼���õ���Ƶ��Ҳ��˫Ƶ�����������ʾ����˲��ὫƵ��ѹ����һ��ʵ�������ʾ���ο�API��
	dft(complexImg, complexImg);

	// compute log(1 + sqrt(Re(DFT(img))**2 + Im(DFT(img))**2))
	split(complexImg, planes);
	//*(planes[0].refcount) = 1
	magnitude(planes[0], planes[1], planes[0]);
	//*(planes[0].refcount) = 2
	Mat mag = planes[0];
	mag += Scalar::all(1);
	log(mag, mag);//�����ȡ��������һ��֮��Ƶ��ֻ��һ���׵㣬˵��Ƶ�׵�Ƶ����ǿ�ȸߡ�

	// crop the spectrum, if it has an odd number of rows or columns
	mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));

	int cx = mag.cols/2;
	int cy = mag.rows/2;
	//����Ƶ����ƽ�Ƶ�ԭ��
	Mat tmp;
	//*(planes[0].refcount) = 3
	Mat q0(mag, Rect(0, 0, cx, cy));
	//*(planes[0].refcount) = 4
	Mat q1(mag, Rect(cx, 0, cx, cy));
	//*(planes[0].refcount) = 5
	Mat q2(mag, Rect(0, cy, cx, cy));
	//*(planes[0].refcount) = 6
	Mat q3(mag, Rect(cx, cy, cx, cy));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(mag, mag, 0, 1, CV_MINMAX);//��һ����Ϊ��ʹ���������ȵ�ͼ������ȷ��ʾ

	imshow("FREQUENCY-IMAGE", mag);
	waitKey();
	return 0;
}

