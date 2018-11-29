#pragma once
#include<iostream>
#include"sfr.h"
using namespace std;
/*传递给该函数的数据假设为辐射校正，*/
/*垂直方向，左边为黑色，右边为白色。黑色的到*/
/*白色方向在这段代码中并不是特别重要。*/
class SfrDataProces
{
public:
	SfrDataProces();
	~SfrDataProces();
public:
	double sfrProc(double **freq, double **sfr, int *len, double *farea, 
		unsigned short size_x, int *nrows, double *slope, int *numcycles, 
		int *pcnt2, double *off, double *R2, int version, int iterate, int user_angle);

	double sfrProc2(double **freq, double **sfr, int *len, double *farea, 
		unsigned short size_x, int *nrows, double *slope, int *numcycles, int *pcnt2, 
		double *off, double *R2, int version, int iterate, int user_angle);

	unsigned short locate_centroids(double *farea, double *temp, double *shifts, unsigned short size_x, 
		unsigned short size_y, double *offset);

	unsigned short ftwos(long number, double dx, double *lsf, long ns, double ds, double *sfr);

	void apply_hamming_window(unsigned short alpha, unsigned int oldlen, unsigned short newxwidth,
		double *AveEdge, long *pcnt2);

	void locate_max_PSF(unsigned int len, double *AveEdge, long *pcnt2);

	void calculate_derivative(unsigned int len, double *AveTmp, double *AveEdge, double *centroid, int separation);

	unsigned short bin_to_regular_xgrid(unsigned short alpha,double *edgex, double *Signal,double *AveEdge, 
		long *counts,unsigned short size_x,unsigned short size_y);

	unsigned short check_slope(double slope, unsigned short *size_y, int *numcycles, double mincyc, int errflag);

	unsigned short fit(unsigned long ndata, double *x, double *y, double *b, double *a, double *R2, double *avar, double *bvar);
};