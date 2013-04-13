/***********************************************************************
 * OpenCV 2.1 example
 * By Pebbler Chung 2010
 ***********************************************************************/
 
#include "cv.h"
#include "highgui.h"
 
using namespace cv; //下面的所有cv相关类型不用加上前缀了
 
int main(int argc, char* argv[])
{
    Mat img = imread("lena.jpg"); //声明Mat变量并调入lena小妞（老妞了现在？）的照片
 
    if(!img.data) //判断图片调入是否成功
		return -1; //调入图片失败则退出
 
    namedWindow("loveLena", CV_WINDOW_AUTOSIZE); //创建窗口,并确定其为大小不可变类型窗口
 
    imshow("loveLena", img); //显示图片。如果你不介意窗口大小可变，可以直接注释掉上一句。因为imshow可以直接创建窗口
 
    waitKey(); //等待按键
 
    return 0;
}