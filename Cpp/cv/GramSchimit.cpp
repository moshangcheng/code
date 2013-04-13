// ***************************************************************
//  GramSchmit   version:  1.0   date: 05/24/2007
//  -------------------------------------------------------------
//  作者:luckdst
//  -------------------------------------------------------------
//  Copyright (C) 2007 
// ***************************************************************
// 
// ***************************************************************
#include "cv.h"
#include "cxcore.h"
#include "cvaux.h"
#include <iostream>
using namespace std;
//按行操作，要被正交化的向量以行的形式放在src里面，输出正交向量以行 
//的形式放dst里面，输出向量没有单位化． 
void GramSchmidt(const CvMat* src, CvMat* dst)
{
	int i,j;
	double param,param1,param2;
	assert(src!=NULL&&dst!=NULL);
	assert(src->cols==dst->cols&&src->rows==dst->rows);
	CvMat *VecSrc = cvCreateMat(1, src->cols, CV_64FC1);
	CvMat *VecDst = cvCreateMat(1, dst->cols, CV_64FC1);
	CvMat *VecTmp = cvCreateMat(1, dst->cols, CV_64FC1);
	cvZero(VecSrc);
	cvZero(VecDst);
	for(i=0;i<dst->rows;i++)
	{
		cvGetRow(src, VecDst, i);
		cvGetRow(src, VecSrc, i);
		for(j=0;j<i;j++)
		{
			cvGetRow(dst, VecTmp, j);
			param1=cvDotProduct(VecSrc,VecTmp);
			param2=cvDotProduct(VecTmp,VecTmp);
			param=param1/param2;
			cvAddWeighted(VecTmp,-param,VecDst,1.0,0,VecDst);
		}		
		memcpy(dst->data.db+i*dst->cols,VecDst->data.db,dst->cols*sizeof(double));
	}
	cvReleaseMat(&VecSrc);
	cvReleaseMat(&VecDst);
	cvReleaseMat(&VecTmp);
}
 
int main(int argc, char *argv[]) 
{
	int i,j;
	CvMat *Ma,*Mb;
	Ma= cvCreateMatHeader( 3, 4, CV_64FC1 );
	Mb=NULL;
 
	const double a[] = { 1, 0,1, 1, 
		             0,1, 1, 0, 0, 0,1,1,};
	cvInitMatHeader( Ma, 3, 4, CV_64FC1, (void *)a);
	Mb=cvCreateMat(Ma->rows,Ma->cols,CV_64FC1);
	GramSchmidt(Ma,Mb);
	//printf out
	for(i=0;i<Mb->rows;i++)
	{
		for(j=0;j<Mb->cols;j++)
		{
			cout<<CV_MAT_ELEM(*Mb,double,i,j)<<"  ";
		}
		cout<<endl;
	}
	cout<<endl;
	///////////////////////////////////
	//test
	CvMat *M1=cvCreateMat(1,Ma->cols,CV_64FC1);
	CvMat *M2=cvCreateMat(1,Ma->cols,CV_64FC1);
	double s;
	for(i=0;i<Mb->rows;i++)
	{
		cvGetRow(Mb, M1, i);
		for(j=0;j<Mb->rows;j++)
		{
			cvGetRow(Mb, M2, j);
			s=cvDotProduct(M2,M1);
			cout<<s<<"      ";
		}
		cout<<endl;
	}
	cvReleaseMat(&Ma);
	cvReleaseMat(&Mb);
	return 0;
}