/********************************************************************
@created:	2011/05/03 16:35
@author:	moshangcheng
@version:	1.0
@tag:		OpenCV DFT IDFT
@purpose:	http://opencvjp-sample.googlecode.com/svn/trunk/	
*********************************************************************/

#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

// class declaration
class DftIdftApp {
private:
	Mat src_img, mag_img;
	Mat Re_img, Im_img, Complex_img;
	Mat zero, dft_src, dft_dst, dft_dst_p;
	Mat idft_img;
	vector<Mat> mv;
	string org_win, mag_win, idft_win;
	int src_cols, src_rows, dft_cols, dft_rows;
public:
	DftIdftApp(const string filename);
	~DftIdftApp(){};
	void calcMagImage();
	void showOrgImage(){imshow(org_win, src_img);}
	void showMagImage(){imshow(mag_win, mag_img);}
	void showIDFTImage(){imshow(idft_win, idft_img);}
	void shiftDFT(Mat &src, Mat &dst);
	void calcIDFT(bool all=false);
	void clear(){idft_img.setTo(0);}
	static void onMouse(int event, int x, int y, int flags, void* param);
};

// constructor
DftIdftApp::DftIdftApp(const string filename)
	:org_win("Original"), mag_win("Magnitude"), idft_win("IDTF")
{
	src_img = imread(filename, 0);
	if(!src_img.data) return;

	Size s_size = src_img.size();
	src_cols = s_size.width;
	src_rows = s_size.height;
	Re_img = Mat(s_size, CV_64F);
	Im_img = Mat::zeros(s_size, CV_64F);
	Complex_img = Mat(s_size, CV_64FC2);

	src_img.convertTo(Re_img, CV_64F);
	mv.push_back(Re_img);
	mv.push_back(Im_img);
	merge(mv, Complex_img);
	idft_img = zero = Mat::zeros(s_size, CV_64F);

	namedWindow(org_win, CV_WINDOW_AUTOSIZE);
	namedWindow(mag_win, CV_WINDOW_AUTOSIZE);
	namedWindow(idft_win, CV_WINDOW_AUTOSIZE);
	cvSetMouseCallback(mag_win.c_str(), DftIdftApp::onMouse, this);
}

// calc magnitude image
void
	DftIdftApp::calcMagImage()
{
	dft_rows = getOptimalDFTSize(src_rows-1);
	dft_cols = getOptimalDFTSize(src_cols-1);
	dft_src = Mat::zeros(dft_rows, dft_cols, CV_64FC2);

	Mat roi(dft_src, Rect(0, 0, src_cols, src_rows));
	Complex_img.copyTo(roi);

	dft(dft_src, dft_dst);
	dft_dst_p = Mat::zeros(dft_dst.size(), dft_dst.type());

	split(dft_dst.mul(dft_dst), mv);
	sqrt(mv[0]+mv[1], mv[0]);
	log(mv[0]+1, mv[0]);

	shiftDFT(mv[0], mv[0]);

	//归一化
	double min, max;
	minMaxLoc(mv[0], &min, &max);
	//min=>0, max=>1
	mag_img = mv[0]*1.0/(max-min) - 1.0*min/(max-min);
}

// swap 1,3 and 2,4 quadrants respectively
void
	DftIdftApp::shiftDFT(Mat &src, Mat& dst)
{
	Mat tmp;
	int cx = src.cols/2;
	int cy = src.rows/2;

	for(int i=0; i<=cx; i+=cx) {
		Mat qs(src, Rect(i^cx,0,cx,cy));
		Mat qd(dst, Rect(i,cy,cx,cy));
		qs.copyTo(tmp);
		qd.copyTo(qs);
		tmp.copyTo(qd);
	}
}

// mouse event callback
void
	DftIdftApp::onMouse(int event, int x, int y, int flags, void* param)
{
	DftIdftApp *app = static_cast<DftIdftApp*>(param);
	Mat &dft_dst = app->dft_dst;
	Mat &dft_dst_p = app->dft_dst_p;
	Mat &mag_img = app->mag_img;
	int cx = app->src_cols/2;
	int cy = app->src_rows/2;
	int mx=x, my=y;
	int w = app->dft_cols;
	int h = app->dft_rows;

	switch(event) {
	case CV_EVENT_MOUSEMOVE:
		if((flags&CV_EVENT_FLAG_LBUTTON)==0) return;
	case CV_EVENT_LBUTTONUP:
		if(flags&CV_EVENT_FLAG_CTRLKEY) { // LeftButton+CTRL
			int step = 5;
			for(int j=-step; j<=step; j++) {
				my = y+j + ((y+j)<cy ? cy:-cy);
				if(y+j<0 || y+j>=h) continue;
				double *from = dft_dst.ptr<double>(my);
				double *to = dft_dst_p.ptr<double>(my);
				double *mag = mag_img.ptr<double>(y+j);
				for(int i=-step; i<=step; i++) {
					mx = x+i + ((x+i)<cx ? cx:-cx);
					if(x+i<0 || x+i>=w) break;
					to[(mx)*2+0] = from[(mx)*2+0];
					to[(mx)*2+1] = from[(mx)*2+1];
					mag[x+i] = 0;
				}
			}
		} else {  // LeftButton
			mx += x<cx ? cx:-cx;
			my += y<cy ? cy:-cy;
			double *from = dft_dst.ptr<double>(my);
			double *to = dft_dst_p.ptr<double>(my);
			double *mag = mag_img.ptr<double>(y);
			to[(mx)*2+0] = from[(mx)*2+0];
			to[(mx)*2+1] = from[(mx)*2+1];
			mag[x] = 0;
		}
		break;
	default:
		return;
	}
	app->calcIDFT();  
}

// Inverse Discrete Fourier Transforma
void
	DftIdftApp::calcIDFT(bool all)
{
	if(all) {
		dft_dst.copyTo(dft_dst_p);
		mag_img.setTo(0);
	}

	double min, max;
	idft(dft_dst_p, dft_src);
	split(dft_src, mv);
	minMaxLoc(mv[0], &min, &max);
	idft_img = Mat(mv[0]*1.0/max, Rect(0, 0, src_cols, src_rows));
}

int
	main(int argc, char *argv[])
{
	const string filename = argc > 1 ? argv[1] : "格子.png";
	DftIdftApp app(filename);

	cout << "Usage: click and drag on Magnitude Image.\n" <<
		"Hot keys: \n"
		"\tESC - quit the program\n"
		"\ta - select all pixels\n"
		"\tr - restore original images\n"
		"\tleft mouse button - select one pixel\n"
		"\tCTRL+left mouse button - select a pixel and neighbors\n";

	app.showOrgImage();
	app.calcMagImage();
	while(1) {
		int c = waitKey(10);
		switch((char)c) {
		case '\x1b': // exit
			return 0;
		case 'a': // IDFT all
			app.calcIDFT(true);
			break;
		case 'r': // reset
			app.clear();
			app.calcMagImage();
			break;
		}
		app.showIDFTImage();
		app.showMagImage();
	}

	return 0;
}
