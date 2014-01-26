/********************************************************************
@created:	2011/05/06 16:15
@author:	moshangcheng
@version:	1.0
@tag:		OpenCV edge
@purpose:	ѧϰOpenCV����Ե��ȡ	
*********************************************************************/

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;
using namespace std;


int edgeThresh = 1;
Mat image, gray, edge, cedge;

void onTrackbar(int, void*)	{
	//ƽ��
	blur(gray, edge, Size(3,3));
	//��ȡ��Ե
	Canny(edge, edge, edgeThresh, edgeThresh*3, 3);
	cedge = Scalar::all(0);
	//edge�Ƕ�ά�������
	image.copyTo(cedge, edge);
	imshow("Edge map", cedge);
}

int main( int argc, char** argv )	{
	char* filename = argc == 2 ? argv[1] : (char*)"����.png";

	image = imread(filename, 1);
	if(image.empty())	{
		cout << "��ȡͼ��ʧ��\n";
		return -1;
	}
	cedge.create(image.size(), image.type());
	cvtColor(image, gray, CV_BGR2GRAY);

	namedWindow("Edge map", 1);

	createTrackbar("Canny threshold", "Edge map", &edgeThresh, 100, onTrackbar);
	onTrackbar(0, 0);
	waitKey(0);
	return 0;
}
