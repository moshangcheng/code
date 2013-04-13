/***********************************************************************
 * OpenCV 2.1 example
 * By Pebbler Chung 2010
 ***********************************************************************/
 
#include "cv.h"
#include "highgui.h"
 
using namespace cv; //���������cv������Ͳ��ü���ǰ׺��
 
int main(int argc, char* argv[])
{
    Mat img = imread("lena.jpg"); //����Mat����������lenaС椣���������ڣ�������Ƭ
 
    if(!img.data) //�ж�ͼƬ�����Ƿ�ɹ�
		return -1; //����ͼƬʧ�����˳�
 
    namedWindow("loveLena", CV_WINDOW_AUTOSIZE); //��������,��ȷ����Ϊ��С���ɱ����ʹ���
 
    imshow("loveLena", img); //��ʾͼƬ������㲻���ⴰ�ڴ�С�ɱ䣬����ֱ��ע�͵���һ�䡣��Ϊimshow����ֱ�Ӵ�������
 
    waitKey(); //�ȴ�����
 
    return 0;
}