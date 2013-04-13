#include "cv.h"
#include "highgui.h"
using namespace std;
using namespace cv;

int main() {
	// allocates IplImages and wraps it into shared pointer class.
	Ptr<IplImage> iplimg = cvLoadImage("lena.jpg");
	// constructs Mat header for IplImage data;
	// does not copy the data;
	// the reference counter will be NULL
	Mat img(iplimg);
	// in the end of the block img destructor is called,
	// which does not try to deallocate the data because
	// of NULL pointer to the reference counter.
	//
	// Then Ptr<IplImage> destructor is called that decrements
	// the reference counter and, as the counter becomes 0 in this case,
	// the destructor calls cvReleaseImage().
	namedWindow("loveLena", CV_WINDOW_AUTOSIZE); //��������,��ȷ����Ϊ��С���ɱ����ʹ���

	imshow("loveLena", img); //��ʾͼƬ������㲻���ⴰ�ڴ�С�ɱ䣬����ֱ��ע�͵���һ�䡣��Ϊimshow����ֱ�Ӵ�������

	waitKey(); //�ȴ�����
	return 0;
}