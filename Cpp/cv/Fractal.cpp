#include "cv.h"
#include "highgui.h"
 
const int image_w = 100;
const double a =0.0;
const double b =0.0;
const long Nmax = 255;  //Z值衰减（趋向于零) 的临界
const double Rmax = 20; // Z值没有界限地增加（趋向无穷）的临界
 
IplImage* image =0;
int c_r_value = 60;
int c_i_value = 40;
 
//返回迭代的次数
int getnum(int i,int j)
{
	double C_RealPart = (double)(c_r_value-50)/100*2*2;  //-2 到 +2  //Julia 集合 常数C
	double C_ImagPart = (double)(c_i_value-50)/100*2*2;  // -2 到 +2 //Julia 集合 常数C
	double RealPart = (double)i/image_w+a; 
	double ImagPart = (double)j/image_w+b;
	int n=0;
	while(n<Nmax)
	{
		//Z=Z*Z+C;
		double ZM =  RealPart*RealPart + ImagPart*ImagPart;
		if(ZM>Rmax) break;
		double temp_RealPart = RealPart*RealPart - ImagPart*ImagPart+C_RealPart;
		double temp_ImagPart = 2*ImagPart*RealPart+C_ImagPart;
		RealPart= temp_RealPart;
		ImagPart= temp_ImagPart;  
		n++;
	}
	return n;
}
void onChangeimg(int pos)
{
	cvZero(image);
	for(int i =0;i<image_w;i++)
		for(int j =0;j<image_w;j++)
		{
			int n1 = getnum(i,j);
			int n2 = getnum(j,i);
			int n3 = getnum(j,i/2);
			//printf("%d,",n);
 
			CvScalar sc1;
			if(n1>Nmax-2) n1=0;
			if(n2>Nmax-2) n2=0;
			if(n3>Nmax-2) n3=0;
 
			sc1.val[0] = (int)abs(255*(float)n1/Nmax);
			sc1.val[1] = (int)abs(255*(float)n2/Nmax);
			sc1.val[2] = (int)abs(255*(float)n3/Nmax);
			cvSet2D(image,i,j,sc1);
 
		}
 
		double nvalue = cvNorm(image,0,CV_C);
 
		for(int i =0;i<image_w;i++)
		for(int j =0;j<image_w;j++)
		{
			CvScalar sc1;
			CvScalar sc2 =cvGet2D(image,i,j);
			sc1.val[0] = (int)abs(255*sc2.val[0]/nvalue);
			sc1.val[1] = (int)abs(255*sc2.val[1]/nvalue);;
			sc1.val[2] = (int)abs(255*sc2.val[2]/nvalue);;
			cvSet2D(image,i,j,sc1);
		}
 
}
int main( int argc, char** argv )
{
 
 
	cvNamedWindow( "WIN", 0 );
	cvCreateTrackbar( "C real", "WIN", &c_r_value, 100, onChangeimg );
	cvCreateTrackbar( "C imag", "WIN", &c_i_value, 100, onChangeimg );
 
	image = cvCreateImage( cvSize(image_w,image_w), 8, 3 );
	onChangeimg(0);
 
 
		for(;;)
		{
 
			cvShowImage("WIN",image);
			if(cvWaitKey(40)==27) break;
		}
		return 0;
 
}