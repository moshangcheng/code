/********************************************************************
	@created:	2011/05/03 15:42
	@author:	moshagncheng
	@version:	1.0
	@tag:		OpenCV DFT IDFT
	@purpose:	ѧϰOpenCV������DFT	
*********************************************************************/
#include <cv.h>
#include <highgui.h>
using namespace cv;

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()	{
	string fileName = "������.png";
	Mat srcImage, dftImage, idftImage;
	srcImage = imread(fileName, CV_LOAD_IMAGE_GRAYSCALE);
	if(srcImage.empty())	{
		cout << "��ȡͼ��ʧ��\n";
		return -1;
	}
	//��ͼ��ĻҶ�ת��Ϊ�������������޷�����DFT
	srcImage.convertTo(srcImage, CV_32FC1);
	normalize(srcImage, srcImage, 0, 1, CV_MINMAX);
	//��ʾԴͼ��
	imshow("source-image", srcImage);
	dft(srcImage, dftImage, DFT_SCALE);
	idft(dftImage, idftImage, DFT_REAL_OUTPUT);
	//��ʾ��Ƶ�׽����渵��Ҷ�任���ͼ��
	//���srcImageû�й�һ������ô���뽫idftImageת����CV_8UC1���͵�ͼ�����������ʾ
	//��Ϊ���ڸ��������󣬱����һ��������Ϊͼ����ʾ�������������󣬱���Ϊ0-255������ʾ
	imshow("idft-image", idftImage);
	imshow("defference-iamge", abs(idftImage-srcImage));
	waitKey();
	return 0;
}
