/********************************************************************
@created:	2011/05/07 16:38
@author:	moshangcheng
@version:	1.0
@tag:		OpenCV Histogram
@purpose:	学习OpenCV，计算图像的直方图
http://code.google.com/p/opencvjp-sample/
*********************************************************************/


#include <cv.h>
#include <highgui.h>
#include <iostream>
using namespace cv;
using namespace std;

int	main (int argc, char **argv)	{
	string imagePath;
	std::cout << "请输入图像路径：\n";
	std::getline(std::cin, imagePath, '\n');
	if(imagePath[0] == '"') {
		imagePath = imagePath.substr(1, imagePath.length()-2);
	}
	Mat srcImage = imread(imagePath, -1);
	if(srcImage.empty())	{
		cout << "读取图像失败\n";
		return -1;
	}

	//allocate Mat to draw a histogram image
	const int ch_width = 260;//一共有256个箱子，每个直方图宽度必须大于256
	const int sch = srcImage.channels();
	Mat hist_img(Size(ch_width * sch, 200), CV_8UC3, Scalar::all(255));

	vector<Mat> hist(3);
	const int hist_size = 256;
	const int hdims[] = {hist_size};
	const float hranges[] = {0,256};
	const float* ranges[] = {hranges};
	double max_val = .0;

	if(sch==1) {
		//if the source image has single-channel, calculate its histogram
		//计算一幅图像的直方图，使用其第0个通道；Mat()表示空矩阵，因此无掩码矩阵；
		//直方图有1个维度，此维度有256个箱子，统计[0,256)之间的值，每个箱子大小相同
		calcHist(&srcImage, 1, 0, Mat(), hist[0], 1, hdims, ranges, true, false);
		minMaxLoc(hist[0], 0, &max_val);
	} else {
		//if the souce image has multi-channel, calculate histogram of each plane
		for(int i=0; i<sch; ++i) {
			calcHist(&srcImage, 1, &i, Mat(), hist[i], 1, hdims, ranges, true, false);
			double tmp_val;
			minMaxLoc(hist[i], 0, &tmp_val);
			max_val = max_val < tmp_val ? tmp_val : max_val;
		}
	}

	//scale and draw the histogram(s)
	Scalar color = Scalar::all(100);
	for(int i = 0; i < sch; i++) {
		if(sch == 3)	{
			color = Scalar((0xaa<<i*8)&0x0000ff,(0xaa<<i*8)&0x00ff00,(0xaa<<i*8)&0xff0000, 0);
		}
		//对hist[i]的每个箱子的统计值归一化，最大为200
		hist[i].convertTo(hist[i], hist[i].type(), max_val?200./max_val:0.,0);
		for(int j = 0; j < hist_size; ++j) {
			int bin_w = saturate_cast<int>((double)ch_width/ hist_size);
			//画出直方图的每个箱子
			rectangle(hist_img,	Point( j * bin_w + (i*ch_width), hist_img.rows),
				Point((j+1)* bin_w+(i*ch_width), hist_img.rows-saturate_cast<int>(hist[i].at<float>(j))),
				color, -1);//-1表示实心矩阵
		}
	}

	imshow("Image", srcImage);
	imshow("Histogram", hist_img);
	waitKey(0);

	return 0;
}
