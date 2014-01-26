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
	namedWindow("loveLena", CV_WINDOW_AUTOSIZE); //创建窗口,并确定其为大小不可变类型窗口

	imshow("loveLena", img); //显示图片。如果你不介意窗口大小可变，可以直接注释掉上一句。因为imshow可以直接创建窗口

	waitKey(); //等待按键
	return 0;
}