#include <cv.h>
#include <highgui.h>

using namespace cv;

int
	main (int argc, char **argv)
{
	// (1)load a specified file as a grayscale image
	const char *imagename = argc > 1 ? argv[1] : "lena.jpg";
	Mat src_img = imread(imagename, 0);
	if(!src_img.data)
		return -1;

	// (2)calculate the first image derivatives using an Sobel operator
	Mat tmp_img;
	Mat sobel_img;
	Sobel(src_img, tmp_img, CV_32F, 1, 1);
	convertScaleAbs(tmp_img, sobel_img, 1, 0);

	// (3)calculate the Laplacian of an image  
	Mat laplacian_img;
	Laplacian(src_img, tmp_img, CV_32F, 3);
	convertScaleAbs(tmp_img, laplacian_img, 1, 0);

	// (4)implement the Canny algorithm for edge detection
	Mat canny_img;
	Canny(src_img, canny_img, 50, 200);

	// (5)show original gray and their edge images respectively, 
	//    and quit when any key pressed
	namedWindow("Original(Grayscale)", CV_WINDOW_AUTOSIZE);
	namedWindow("Sobel", CV_WINDOW_AUTOSIZE);
	namedWindow("Laplacian", CV_WINDOW_AUTOSIZE);
	namedWindow("Canny", CV_WINDOW_AUTOSIZE);
	imshow("Original(Grayscale)", src_img);
	imshow("Sobel", sobel_img);
	imshow("Laplacian", laplacian_img);
	imshow("Canny", canny_img);
	waitKey(0);

	return 0;
}
