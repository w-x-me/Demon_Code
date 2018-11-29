#include"sfr-data-proces.h"
FILE *g_mtfout;
#define ALPHA 4.0
#define ESFFILE 8
#define DER3 4
#define PEAK 2
#define ROUND 1

static double sqrarg;
#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0: sqrarg*sqrarg)
SfrDataProces::SfrDataProces()
{}
SfrDataProces::~SfrDataProces()
{}
//double SfrDataProces::sfrProc(double **freq, double **sfr, int *len, double *farea, unsigned short size_x, int *nrows, double *slope, int *numcycles, int *pcnt2, double *off, double *R2, int version, int iterate, int user_angle)
//{
//	unsigned short i, j, col, err = 0;
//	long pcnt;
//	double dt, dt1, sfrc, tmp, tmp2;
//	double *temp = NULL, *shifts = NULL, *edgex = NULL, *Signal = NULL;
//	double *AveEdge = NULL, *AveTmp = NULL;
//	long *counts = NULL;
//	int nzero;
//	unsigned short size_y;
//	unsigned int bin_len;
//	double avar, bvar, offset1, offset2, offset;
//	double centroid;
//	int start_row, center_row;
//	double *farea_old;
//	double cyclelimit;
//	FILE *fp = NULL;
//	size_y = *nrows;
//	double sfrvalue = 0.0;
//
//	/* Verify input selection dimensions are EVEN */
//	if (size_x % 2 != 0)
//	{
//		fprintf(stderr, "ROI width is not even.  Does this really matter???\n");
//		//  return 1;
//	}
//
//	/* At least this many cycles required. */
//	/* For special iterative versions of the code, it can go lower */
//	if (iterate) cyclelimit = 1.0;
//	else cyclelimit = 5.0;
//
//	/* Allocate memory */
//	shifts = (double *)malloc(size_y*sizeof(double));
//	temp = (double *)malloc(size_y*sizeof(double));
//	edgex = (double *)malloc(size_y*size_x*sizeof(double));
//	Signal = (double *)malloc(size_y*size_x*sizeof(double));
//
//	if (!user_angle)
//	{
//		// 定位质心
//		err = locate_centroids(farea, temp, shifts, size_x, size_y, &offset1);
//		if (err != 0)
//		{
//			return 2;
//		}
//
//		/* Calculate the best fit line to the centroids */
//		err = fit(size_y, temp, shifts, slope, &offset2, R2, &avar, &bvar);
//		if (err != 0)     { return 3; }
//
//		if (version)
//			MTFPRINT4("\nLinear Fit:  R2 = %.3f SE_intercept = %.2f  SE_angle = %.3f\n", *R2, avar, atan(bvar)*(double)(180.0 / M_PI))
//	}
//
//	/* Check slope is OK, and set size_y to be full multiple of cycles */
//	// 检查刀口斜率， 以确保后面超采样的质量
//	err = check_slope(*slope, &size_y, numcycles, cyclelimit, 1);
//
//	/* Start image at new location, so that same row is center */
//	// 调整ROI的行
//	center_row = *nrows / 2;
//	start_row = center_row - size_y / 2;
//	farea_old = farea;
//	farea = farea + start_row*size_x;
//	/* On center row how much shift to get edge centered in row. */
//	/* offset = 0.;  Original code effectively used this (no centering)*/
//	// 计算刀口的偏移
//	if (user_angle)
//		offset = *off - size_x / 2;
//	else
//		offset = offset1 + 0.5 + offset2 - size_x / 2; // 为什么要加0.5？
//
//	*off = offset;
//	if (version & ROUND || version & DER3)
//		offset += 0.125;
//
//	if (err != 0)
//	{   /* Slopes are bad.  But send back enough
//		data, so a diagnostic image has a chance. */
//		*pcnt2 = 2 * size_x;  /* Ignore derivative peak */
//		////return 4; 
//	}
//
//	/* reference the temp and shifts values to the new y centre */
//	/* Instead of using the values in shifts, synthesize new ones based on
//	the best fit line. */
//	// 基于拟合结果更新shifts
//	col = size_y / 2;
//	for (i = 0; i < size_y; i++)
//	{
//		shifts[i] = (*slope) * (double)(i - col) + offset;
//	}
//
//	/* Don't normalize the data.  It gets normalized during dft process */
//	/* To normalize here, set dt = min and dt1 = max of farea data      */
//	dt = 0.0;
//	dt1 = 1.0;
//
//	if (version & ESFFILE)
//		fp = fopen("esf.txt", "w");
//
//	/* Calculate a long paired list of x values and signal values */
//	pcnt = 0;
//	for (j = 0; j < size_y; j++)
//	{
//		for (i = 0; i < size_x; i++)
//		{
//			edgex[pcnt] = (double)i - shifts[j]; // 计算每个点离刀口的距离
//			Signal[pcnt] = ((farea[((j*(long)size_x) + i)]) - dt) / (dt1 - dt);  // 归一化每个点的亮度
//
//			if ((version & ESFFILE) && edgex[pcnt] < size_x / 2 + 3 && edgex[pcnt] > size_x / 2 - 3)
//				fprintf(fp, "%f %f\n", edgex[pcnt], Signal[pcnt]);
//			pcnt++;
//		}
//	}
//
//	if (version & ESFFILE)
//		fclose(fp);
//
//	/* Allocate more memory */
//	bin_len = (unsigned int)(ALPHA*size_x);
//	AveEdge = (double *)malloc(bin_len*sizeof(double));
//	AveTmp = (double *)malloc(bin_len*sizeof(double));
//	counts = (long *)malloc(bin_len*sizeof(long));
//
//	/* Project ESF data into supersampled bins */
//	// 进行超采样， 生成长度为size_x*ALPHA（4）的单行图像(ESF), 保存在AveEdge中
//	nzero = bin_to_regular_xgrid((unsigned short)ALPHA, edgex, Signal, AveEdge, counts, size_x, size_y);
//	free(counts);
//	free(Signal);
//	free(edgex);
//
//	/* Compute LSF from ESF.  Not yet centered or windowed. */
//	// 将ESF转换为差分图LSF， 并计算LSF的质心
//	if ((version&DER3))
//		calculate_derivative(bin_len, AveTmp, AveEdge, &centroid, 1);
//	else
//		calculate_derivative(bin_len, AveTmp, AveEdge, &centroid, 0);
//
//	if (iterate == 0)
//	{
//		/* Copy ESF to output area */
//		for (i = 0; i<bin_len; i++)
//			farea_old[i] = AveTmp[i];
//	}
//
//	/* Find the peak/center of LSF */
//	// 寻找LSF的最大值点
//	locate_max_PSF(bin_len, AveEdge, &pcnt);
//
//	free(shifts);
//	free(temp);
//
//	if (version)
//		MTFPRINT3("Off center distance (1/4 pixel units): Peak %ld  Centroid %.2f\n", pcnt - bin_len / 2, centroid - bin_len / 2)
//
//	if ((version & PEAK) == 0)
//		pcnt = bin_len / 2;  /* Ignore derivative peak */
//	else
//		MTFPRINT("Shifting peak to center\n")
//
//		/* Here the array length is shortened to ww_in_pixels*ALPHA,
//		and the LSF peak is centered and Hamming windowed. */
//		// 将LSF的最大值移到中心位置， 并加上汉明窗
//		apply_hamming_window((unsigned short)ALPHA, bin_len, (unsigned short)size_x, AveEdge, &pcnt);
//
//	/* From now on this is the length used. */
//	*len = bin_len / 2;
//
//	if (iterate == 0)
//	{
//		/* Copy LSF_w to output area */
//		for (i = 0; i<bin_len; i++)
//			farea_old[size_x*(int)ALPHA + i] = AveEdge[i];
//	}
//
//	tmp = 1.0;
//	tmp2 = 1.0 / ((double)bin_len);
//
//	/* Now perform the DFT on AveEdge */
//	/* ftwos ( nx, dx, lsf(x), nf, df, sfr(f) ) */
//	// DFT
//	(void)ftwos(bin_len, tmp, AveEdge, (long)(*len), tmp2, AveTmp);
//
//	if (*freq == NULL)
//		(*freq) = (double *)malloc((*len)*sizeof(double));
//	if (*sfr == NULL)
//		(*sfr) = (double *)malloc((*len)*sizeof(double));
//
//
//	for (i = 0; i<(*len); i++)
//	{
//		sfrc = AveTmp[i];
//		(*freq)[i] = ((double)i / (double)size_x); // 每个点对应的频率
//		(*sfr)[i] = (double)(sfrc / AveTmp[0]);  // 归一化sfr
//
//		if ((*freq)[i] == 0.5)
//		{
//			sfrvalue = (*sfr)[i];
//		}
//	}
//	free(AveEdge);
//	free(AveTmp);
//	*nrows = size_y;
//	*pcnt2 = pcnt;
//	return sfrvalue;
//}
double SfrDataProces::sfrProc(double **freq, double **sfr, int *len, double *farea, unsigned short size_x, int *nrows, double *slope, int *numcycles, int *pcnt2, double *off, double *R2, int version, int iterate, int user_angle)
{
	unsigned short i, j, col, err = 0;
	long pcnt;
	double dt, dt1, sfrc, tmp, tmp2;
	double *temp = NULL, *shifts = NULL, *edgex = NULL, *Signal = NULL;
	double *AveEdge = NULL, *AveTmp = NULL;
	long *counts = NULL;
	int nzero;
	unsigned short size_y;
	unsigned int bin_len;
	double avar, bvar, offset1, offset2, offset;
	double centroid;
	int start_row, center_row;
	double *farea_old;
	double cyclelimit;
	FILE *fp = NULL;
	size_y = *nrows;
	double sfrvalue = 0.0;

	/* Verify input selection dimensions are EVEN */
	if (size_x % 2 != 0)
	{
		fprintf(stderr, "ROI width is not even.  Does this really matter???\n");
		//  return 1;
	}

	/* At least this many cycles required. */
	/* For special iterative versions of the code, it can go lower */
	if (iterate) cyclelimit = 1.0;
	else cyclelimit = 5.0;

	/* Allocate memory */
	shifts = (double *)malloc(size_y*sizeof(double));
	temp = (double *)malloc(size_y*sizeof(double));
	edgex = (double *)malloc(size_y*size_x*sizeof(double));
	Signal = (double *)malloc(size_y*size_x*sizeof(double));

	if (!user_angle)
	{
		// 定位质心
		err = locate_centroids(farea, temp, shifts, size_x, size_y, &offset1);
		if (err != 0)
		{
			return 2;
		}

		/* Calculate the best fit line to the centroids */
		err = fit(size_y, temp, shifts, slope, &offset2, R2, &avar, &bvar);
		if (err != 0)     { return 3; }

		if (version)
			MTFPRINT4("\nLinear Fit:  R2 = %.3f SE_intercept = %.2f  SE_angle = %.3f\n", *R2, avar, atan(bvar)*(double)(180.0 / M_PI))
	}

	/* Check slope is OK, and set size_y to be full multiple of cycles */
	// 检查刀口斜率， 以确保后面超采样的质量
	err = check_slope(*slope, &size_y, numcycles, cyclelimit, 1);

	/* Start image at new location, so that same row is center */
	// 调整ROI的行
	center_row = *nrows / 2;
	start_row = center_row - size_y / 2;
	farea_old = farea;
	farea = farea + start_row*size_x;
	/* On center row how much shift to get edge centered in row. */
	/* offset = 0.;  Original code effectively used this (no centering)*/
	// 计算刀口的偏移
	if (user_angle)
		offset = *off - size_x / 2;
	else
		offset = offset1 + 0.5 + offset2 - size_x / 2; // 为什么要加0.5？

	*off = offset;
	if (version & ROUND || version & DER3)
		offset += 0.125;

	if (err != 0)
	{   /* Slopes are bad.  But send back enough
		data, so a diagnostic image has a chance. */
		*pcnt2 = 2 * size_x;  /* Ignore derivative peak */
		////return 4; 
	}

	/* reference the temp and shifts values to the new y centre */
	/* Instead of using the values in shifts, synthesize new ones based on
	the best fit line. */
	// 基于拟合结果更新shifts
	col = size_y / 2;
	for (i = 0; i < size_y; i++)
	{
		shifts[i] = (*slope) * (double)(i - col) + offset;
	}

	/* Don't normalize the data.  It gets normalized during dft process */
	/* To normalize here, set dt = min and dt1 = max of farea data      */
	dt = 0.0;
	dt1 = 1.0;

	if (version & ESFFILE)
		fp = fopen("esf.txt", "w");

	/* Calculate a long paired list of x values and signal values */
	pcnt = 0;
	for (j = 0; j < size_y; j++)
	{
		for (i = 0; i < size_x; i++)
		{
			edgex[pcnt] = (double)i - shifts[j]; // 计算每个点离刀口的距离
			Signal[pcnt] = ((farea[((j*(long)size_x) + i)]) - dt) / (dt1 - dt);  // 归一化每个点的亮度

			if ((version & ESFFILE) && edgex[pcnt] < size_x / 2 + 3 && edgex[pcnt] > size_x / 2 - 3)
				fprintf(fp, "%f %f\n", edgex[pcnt], Signal[pcnt]);
			pcnt++;
		}
	}

	if (version & ESFFILE)
		fclose(fp);

	/* Allocate more memory */
	bin_len = (unsigned int)(ALPHA*size_x);
	AveEdge = (double *)malloc(bin_len*sizeof(double));
	AveTmp = (double *)malloc(bin_len*sizeof(double));
	counts = (long *)malloc(bin_len*sizeof(long));

	/* Project ESF data into supersampled bins */
	// 进行超采样， 生成长度为size_x*ALPHA（4）的单行图像(ESF), 保存在AveEdge中
	nzero = bin_to_regular_xgrid((unsigned short)ALPHA, edgex, Signal, AveEdge, counts, size_x, size_y);
	free(counts);
	free(Signal);
	free(edgex);

	/* Compute LSF from ESF.  Not yet centered or windowed. */
	// 将ESF转换为差分图LSF， 并计算LSF的质心
	if ((version&DER3))
		calculate_derivative(bin_len, AveTmp, AveEdge, &centroid, 1);
	else
		calculate_derivative(bin_len, AveTmp, AveEdge, &centroid, 0);

	if (iterate == 0)
	{
		/* Copy ESF to output area */
		for (i = 0; i<bin_len; i++)
			farea_old[i] = AveTmp[i];
	}

	/* Find the peak/center of LSF */
	// 寻找LSF的最大值点
	locate_max_PSF(bin_len, AveEdge, &pcnt);

	free(shifts);
	free(temp);

	if (version)
		MTFPRINT3("Off center distance (1/4 pixel units): Peak %ld  Centroid %.2f\n", pcnt - bin_len / 2, centroid - bin_len / 2)

	if ((version & PEAK) == 0)
		pcnt = bin_len / 2;  /* Ignore derivative peak */
	else
		MTFPRINT("Shifting peak to center\n")

		/* Here the array length is shortened to ww_in_pixels*ALPHA,
		and the LSF peak is centered and Hamming windowed. */
		// 将LSF的最大值移到中心位置， 并加上汉明窗
		apply_hamming_window((unsigned short)ALPHA, bin_len, (unsigned short)size_x, AveEdge, &pcnt);

	/* From now on this is the length used. */
	*len = bin_len / 2;

	if (iterate == 0)
	{
		/* Copy LSF_w to output area */
		for (i = 0; i<bin_len; i++)
			farea_old[size_x*(int)ALPHA + i] = AveEdge[i];
	}

	tmp = 1.0;
	tmp2 = 1.0 / ((double)bin_len);

	/* Now perform the DFT on AveEdge */
	/* ftwos ( nx, dx, lsf(x), nf, df, sfr(f) ) */
	// DFT
	(void)ftwos(bin_len, tmp, AveEdge, (long)(*len), tmp2, AveTmp);

	if (*freq == NULL)
		(*freq) = (double *)malloc((*len)*sizeof(double));
	if (*sfr == NULL)
		(*sfr) = (double *)malloc((*len)*sizeof(double));

	sfrvalue = AveTmp[0] * 0.5;
	//for (i = 0; i<(size_x); i++)
	//{
	//  sfrc = AveTmp[i];
	//  (*freq)[i]= ((double)i/(double)size_x); // 每个点对应的频率
	//  (*sfr)[i] = (double) (sfrc/AveTmp[0]);  // 归一化sfr

	/*sfrvalue = AveTmp[0]*0.5;*/
	/*if (i==size_x/2)
	{
	sfrvalue = (*sfr)[i];
	}*/
	//}
	free(AveEdge);
	free(AveTmp);
	*nrows = size_y;
	*pcnt2 = pcnt;
	return sfrvalue; 
}

//double SfrDataProces::sfrProc2(double **freq, double **sfr, int *len, double *farea, unsigned short size_x, int *nrows, double *slope, int *numcycles, int *pcnt2, double *off, double *R2, int version, int iterate, int user_angle)
//{
//	unsigned short i, j, col, err = 0;
//	long pcnt;
//	double dt, dt1, sfrc, tmp, tmp2;
//	double *temp = NULL, *shifts = NULL, *edgex = NULL, *Signal = NULL;
//	double *AveEdge = NULL, *AveTmp = NULL;
//	long *counts = NULL;
//	int nzero;
//	unsigned short size_y;
//	unsigned int bin_len;
//	double avar, bvar, offset1, offset2, offset;
//	double centroid;
//	int start_row, center_row;
//	double *farea_old;
//	double cyclelimit;
//	FILE *fp = NULL;
//	size_y = *nrows;
//	double sfrvalue = 0.0;
//
//	/* Verify input selection dimensions are EVEN */
//	if (size_x % 2 != 0)
//	{
//		//fprintf(stderr, "ROI width is not even.  Does this really matter???\n");
//		//return 1;
//	}
//
//	/* At least this many cycles required. */
//	/* For special iterative versions of the code, it can go lower */
//	if (iterate) cyclelimit = 1.0;
//	else cyclelimit = 5.0;
//
//	/* Allocate memory */
//	shifts = (double *)malloc(size_y*sizeof(double));
//	temp = (double *)malloc(size_y*sizeof(double));
//	edgex = (double *)malloc(size_y*size_x*sizeof(double));
//	Signal = (double *)malloc(size_y*size_x*sizeof(double));
//
//	if (!user_angle)
//	{
//		// 定位质心
//		err = locate_centroids(farea, temp, shifts, size_x, size_y, &offset1);
//		if (err != 0)
//		{
//			//return 2;
//		}
//
//		/* Calculate the best fit line to the centroids */
//		err = fit(size_y, temp, shifts, slope, &offset2, R2, &avar, &bvar);
//		if (err != 0)
//		{
//			//return 3; 
//		}
//
//		if (version)
//			MTFPRINT4("\nLinear Fit:  R2 = %.3f SE_intercept = %.2f  SE_angle = %.3f\n", *R2, avar, atan(bvar)*(double)(180.0 / M_PI))
//	}
//
//	/* Check slope is OK, and set size_y to be full multiple of cycles */
//	// 检查刀口斜率， 以确保后面超采样的质量
//	err = check_slope(*slope, &size_y, numcycles, cyclelimit, 1);
//
//	/* Start image at new location, so that same row is center */
//	// 调整ROI的行
//	center_row = *nrows / 2;
//	start_row = center_row - size_y / 2;
//	farea_old = farea;
//	farea = farea + start_row*size_x;
//	/* On center row how much shift to get edge centered in row. */
//	/* offset = 0.;  Original code effectively used this (no centering)*/
//	// 计算刀口的偏移
//	if (user_angle)
//		offset = *off - size_x / 2;
//	else
//		offset = offset1 + 0.5 + offset2 - size_x / 2; // 为什么要加0.5？
//
//	*off = offset;
//	if (version & ROUND || version & DER3)
//		offset += 0.125;
//
//	if (err != 0)
//	{   /* Slopes are bad.  But send back enough
//		data, so a diagnostic image has a chance. */
//		*pcnt2 = 2 * size_x;  /* Ignore derivative peak */
//		/*return 4;*/
//		//return 0.397;
//	}
//
//	/* reference the temp and shifts values to the new y centre */
//	/* Instead of using the values in shifts, synthesize new ones based on
//	the best fit line. */
//	// 基于拟合结果更新shifts
//	col = size_y / 2;
//	for (i = 0; i < size_y; i++)
//	{
//		shifts[i] = (*slope) * (double)(i - col) + offset;
//	}
//
//	/* Don't normalize the data.  It gets normalized during dft process */
//	/* To normalize here, set dt = min and dt1 = max of farea data      */
//	dt = 0.0;
//	dt1 = 1.0;
//
//	if (version & ESFFILE)
//		fp = fopen("esf.txt", "w");
//
//	/* Calculate a long paired list of x values and signal values */
//	pcnt = 0;
//	for (j = 0; j < size_y; j++)
//	{
//		for (i = 0; i < size_x; i++)
//		{
//			edgex[pcnt] = (double)i - shifts[j]; // 计算每个点离刀口的距离
//			Signal[pcnt] = ((farea[((j*(long)size_x) + i)]) - dt) / (dt1 - dt);  // 归一化每个点的亮度
//
//			if ((version & ESFFILE) && edgex[pcnt] < size_x / 2 + 3 && edgex[pcnt] > size_x / 2 - 3)
//				fprintf(fp, "%f %f\n", edgex[pcnt], Signal[pcnt]);
//			pcnt++;
//		}
//	}
//
//	if (version & ESFFILE)
//		fclose(fp);
//
//	/* Allocate more memory */
//	bin_len = (unsigned int)(ALPHA*size_x);
//	AveEdge = (double *)malloc(bin_len*sizeof(double));
//	AveTmp = (double *)malloc(bin_len*sizeof(double));
//	counts = (long *)malloc(bin_len*sizeof(long));
//
//	/* Project ESF data into supersampled bins */
//	// 进行超采样， 生成长度为size_x*ALPHA（4）的单行图像(ESF), 保存在AveEdge中
//	nzero = bin_to_regular_xgrid((unsigned short)ALPHA, edgex, Signal, AveEdge, counts, size_x, size_y);
//	free(counts);
//	free(Signal);
//	free(edgex);
//
//	/* Compute LSF from ESF.  Not yet centered or windowed. */
//	// 将ESF转换为差分图LSF， 并计算LSF的质心
//	if ((version&DER3))
//		calculate_derivative(bin_len, AveTmp, AveEdge, &centroid, 1);
//	else
//		calculate_derivative(bin_len, AveTmp, AveEdge, &centroid, 0);
//
//	if (iterate == 0)
//	{
//		/* Copy ESF to output area */
//		for (i = 0; i<bin_len; i++)
//			farea_old[i] = AveTmp[i];
//	}
//
//	/* Find the peak/center of LSF */
//	// 寻找LSF的最大值点
//	locate_max_PSF(bin_len, AveEdge, &pcnt);
//
//	free(shifts);
//	free(temp);
//
//	if (version)
//		MTFPRINT3("Off center distance (1/4 pixel units): Peak %ld  Centroid %.2f\n", pcnt - bin_len / 2, centroid - bin_len / 2)
//
//	if ((version & PEAK) == 0)
//		pcnt = bin_len / 2;  /* Ignore derivative peak */
//	else
//		MTFPRINT("Shifting peak to center\n")
//
//		/* Here the array length is shortened to ww_in_pixels*ALPHA,
//		and the LSF peak is centered and Hamming windowed. */
//		// 将LSF的最大值移到中心位置， 并加上汉明窗
//		apply_hamming_window((unsigned short)ALPHA, bin_len, (unsigned short)size_x, AveEdge, &pcnt);
//
//	/* From now on this is the length used. */
//	*len = bin_len / 2;
//
//	if (iterate == 0)
//	{
//		/* Copy LSF_w to output area */
//		for (i = 0; i<bin_len; i++)
//			farea_old[size_x*(int)ALPHA + i] = AveEdge[i];
//	}
//
//	tmp = 1.0;
//	tmp2 = 1.0 / ((double)bin_len);
//
//	/* Now perform the DFT on AveEdge */
//	/* ftwos ( nx, dx, lsf(x), nf, df, sfr(f) ) */
//	// DFT
//	(void)ftwos(bin_len, tmp, AveEdge, (long)(*len), tmp2, AveTmp);
//
//	if (*freq == NULL)
//		(*freq) = (double *)malloc((*len)*sizeof(double));
//	if (*sfr == NULL)
//		(*sfr) = (double *)malloc((*len)*sizeof(double));
//
//
//
//	for (i = 0; i<(*len); i++)
//	{
//		sfrc = AveTmp[i];
//		(*freq)[i] = ((double)i / (double)size_x); // 每个点对应的频率
//		(*sfr)[i] = (double)(sfrc / AveTmp[0]);  // 归一化sfr
//
//		if ((*freq)[i] == 0.5)
//		{
//			sfrvalue = (*sfr)[i];
//		}
//	}
//	/* Free */
//	free(AveEdge);
//	free(AveTmp);
//
//	*nrows = size_y;
//	*pcnt2 = pcnt;
//	return sfrvalue;
//}
double SfrDataProces::sfrProc2(double **freq, double **sfr, int *len, double *farea, unsigned short size_x, int *nrows, double *slope, int *numcycles, int *pcnt2, double *off, double *R2, int version, int iterate, int user_angle)
{
	unsigned short i, j, col, err = 0;
	long pcnt;
	double dt, dt1, sfrc, tmp, tmp2;
	double *temp = NULL, *shifts = NULL, *edgex = NULL, *Signal = NULL;
	double *AveEdge = NULL, *AveTmp = NULL;
	long *counts = NULL;
	int nzero;
	unsigned short size_y;
	unsigned int bin_len;
	double avar, bvar, offset1, offset2, offset;
	double centroid;
	int start_row, center_row;
	double *farea_old;
	double cyclelimit;
	FILE *fp = NULL;
	size_y = *nrows;
	double sfrvalue = 0.0;

	/* Verify input selection dimensions are EVEN */
	if (size_x % 2 != 0)
	{
		//fprintf(stderr, "ROI width is not even.  Does this really matter???\n");
		//return 1;
	}

	/* At least this many cycles required. */
	/* For special iterative versions of the code, it can go lower */
	if (iterate) cyclelimit = 1.0;
	else cyclelimit = 5.0;

	/* Allocate memory */
	shifts = (double *)malloc(size_y*sizeof(double));
	temp = (double *)malloc(size_y*sizeof(double));
	edgex = (double *)malloc(size_y*size_x*sizeof(double));
	Signal = (double *)malloc(size_y*size_x*sizeof(double));

	if (!user_angle)
	{
		// 定位质心
		err = locate_centroids(farea, temp, shifts, size_x, size_y, &offset1);
		if (err != 0)
		{
			//return 2;
		}

		/* Calculate the best fit line to the centroids */
		err = fit(size_y, temp, shifts, slope, &offset2, R2, &avar, &bvar);
		if (err != 0)
		{
			//return 3; 
		}

		if (version)
			MTFPRINT4("\nLinear Fit:  R2 = %.3f SE_intercept = %.2f  SE_angle = %.3f\n", *R2, avar, atan(bvar)*(double)(180.0 / M_PI))
	}

	/* Check slope is OK, and set size_y to be full multiple of cycles */
	// 检查刀口斜率， 以确保后面超采样的质量
	err = check_slope(*slope, &size_y, numcycles, cyclelimit, 1);

	/* Start image at new location, so that same row is center */
	// 调整ROI的行
	center_row = *nrows / 2;
	start_row = center_row - size_y / 2;
	farea_old = farea;
	farea = farea + start_row*size_x;
	/* On center row how much shift to get edge centered in row. */
	/* offset = 0.;  Original code effectively used this (no centering)*/
	// 计算刀口的偏移
	if (user_angle)
		offset = *off - size_x / 2;
	else
		offset = offset1 + 0.5 + offset2 - size_x / 2; // 为什么要加0.5？

	*off = offset;
	if (version & ROUND || version & DER3)
		offset += 0.125;

	if (err != 0)
	{   /* Slopes are bad.  But send back enough
		data, so a diagnostic image has a chance. */
		*pcnt2 = 2 * size_x;  /* Ignore derivative peak */
		/*return 4;*/
		//return 0.397;
	}

	/* reference the temp and shifts values to the new y centre */
	/* Instead of using the values in shifts, synthesize new ones based on
	the best fit line. */
	// 基于拟合结果更新shifts
	col = size_y / 2;
	for (i = 0; i < size_y; i++)
	{
		shifts[i] = (*slope) * (double)(i - col) + offset;
	}

	/* Don't normalize the data.  It gets normalized during dft process */
	/* To normalize here, set dt = min and dt1 = max of farea data      */
	dt = 0.0;
	dt1 = 1.0;

	if (version & ESFFILE)
		fp = fopen("esf.txt", "w");

	/* Calculate a long paired list of x values and signal values */
	pcnt = 0;
	for (j = 0; j < size_y; j++)
	{
		for (i = 0; i < size_x; i++)
		{
			edgex[pcnt] = (double)i - shifts[j]; // 计算每个点离刀口的距离
			Signal[pcnt] = ((farea[((j*(long)size_x) + i)]) - dt) / (dt1 - dt);  // 归一化每个点的亮度

			if ((version & ESFFILE) && edgex[pcnt] < size_x / 2 + 3 && edgex[pcnt] > size_x / 2 - 3)
				fprintf(fp, "%f %f\n", edgex[pcnt], Signal[pcnt]);
			pcnt++;
		}
	}

	if (version & ESFFILE)
		fclose(fp);

	/* Allocate more memory */
	bin_len = (unsigned int)(ALPHA*size_x);
	AveEdge = (double *)malloc(bin_len*sizeof(double));
	AveTmp = (double *)malloc(bin_len*sizeof(double));
	counts = (long *)malloc(bin_len*sizeof(long));

	/* Project ESF data into supersampled bins */
	// 进行超采样， 生成长度为size_x*ALPHA（4）的单行图像(ESF), 保存在AveEdge中
	nzero = bin_to_regular_xgrid((unsigned short)ALPHA, edgex, Signal, AveEdge, counts, size_x, size_y);
	free(counts);
	free(Signal);
	free(edgex);

	/* Compute LSF from ESF.  Not yet centered or windowed. */
	// 将ESF转换为差分图LSF， 并计算LSF的质心
	if ((version&DER3))
		calculate_derivative(bin_len, AveTmp, AveEdge, &centroid, 1);
	else
		calculate_derivative(bin_len, AveTmp, AveEdge, &centroid, 0);

	if (iterate == 0)
	{
		/* Copy ESF to output area */
		for (i = 0; i<bin_len; i++)
			farea_old[i] = AveTmp[i];
	}

	/* Find the peak/center of LSF */
	// 寻找LSF的最大值点
	locate_max_PSF(bin_len, AveEdge, &pcnt);

	free(shifts);
	free(temp);

	if (version)
		MTFPRINT3("Off center distance (1/4 pixel units): Peak %ld  Centroid %.2f\n", pcnt - bin_len / 2, centroid - bin_len / 2)

	if ((version & PEAK) == 0)
		pcnt = bin_len / 2;  /* Ignore derivative peak */
	else
		MTFPRINT("Shifting peak to center\n")

		// 将LSF的最大值移到中心位置， 并加上汉明窗
		apply_hamming_window((unsigned short)ALPHA, bin_len, (unsigned short)size_x, AveEdge, &pcnt);


	*len = bin_len / 2;

	if (iterate == 0)
	{
		for (i = 0; i<bin_len; i++)
			farea_old[size_x*(int)ALPHA + i] = AveEdge[i];
	}

	tmp = 1.0;
	tmp2 = 1.0 / ((double)bin_len);

	(void)ftwos(bin_len, tmp, AveEdge, (long)(*len), tmp2, AveTmp);

	if (*freq == NULL)
		(*freq) = (double *)malloc((*len)*sizeof(double));
	if (*sfr == NULL)
		(*sfr) = (double *)malloc((*len)*sizeof(double));

	sfrvalue = AveTmp[0] * 0.5;

	free(AveEdge);
	free(AveTmp);

	*nrows = size_y;
	*pcnt2 = pcnt;
	return sfrvalue;
}

// 寻找质心
// shifts --> 当前行与中心行的距离
// temp --> 当前行的质心与中心行的质心的距离
// offset --> 中心行质心的位置
unsigned short SfrDataProces::locate_centroids(double *farea, double *temp, double *shifts, unsigned short size_x, unsigned short size_y, double *offset)
{
	unsigned long i, j;
	double dt, dt1, dt2;

	/* Compute the first difference on each line. Interpolate to find the
	centroid of the first derivatives. */
	// 求质心C
	// C = Σx*（f(x+1）-f(x))/Σ(f(x+1)-f(x))
	for (j = 0; j < size_y; j++)
	{
		dt = 0.0;
		dt1 = 0.0;
		for (i = 0; i < size_x - 1; i++)
		{
			dt2 = farea[(j*(long)size_x) + (i + 1)] - farea[(j*(long)size_x) + i];  // 计算每个点的导数
			dt += dt2 * (double)i; // 
			dt1 += dt2;
		}
		shifts[j] = dt / dt1; // 质心
	}

	/* check again to be sure we aren't too close to an edge on the corners.
	If the black to white transition is closer than 2 pixels from either
	side of the data box, return an error of 5; the calling program will
	display an error message (the same one as if there were not a difference
	between the left and right sides of the box ) */
	// 确保刀口不要太靠近左右边界(> 2 pixels)
	if (shifts[size_y - 1] < 2 || size_x - shifts[size_y - 1] < 2)
	{
		fprintf(stderr, "** WARNING: Edge comes too close to the ROI corners.\n");
		// return 5;
	}
	if (shifts[0] < 2 || size_x - shifts[0] < 2)
	{

		fprintf(stderr, "** WARNING: Edge comes too close to the ROI corners.\n");
		//return 5;
	}

	/* Reference rows to the vertical centre of the data box */
	j = size_y / 2;
	dt = shifts[j];
	for (i = 0; i < size_y; i++)
	{
		temp[i] = (double)i - (double)j; // 当前行与中心行的距离 delta Col
		shifts[i] -= dt; // 当前行的质心与中心行的质心的距离delta C
	}
	*offset = dt; // 中心行质心的位置
	return 0;
}

// 线性回归 y = a + bx
unsigned short SfrDataProces::fit(unsigned long ndata, double *x, double *y, double *b, double *a, double *R2, double *avar, double *bvar)
{
	unsigned long i;
	double t, sxoss, syoss, sx = 0.0, sy = 0.0, st2 = 0.0;
	double ss, sst, sigdat, chi2, siga, sigb;

	*b = 0.0;
	for (i = 0; i < ndata; i++)
	{
		sx += x[i];
		sy += y[i];
	}
	ss = (double)ndata;
	sxoss = sx / ss;
	syoss = sy / ss;
	for (i = 0; i < ndata; i++)
	{
		t = x[i] - sxoss;
		st2 += t*t;
		*b += t * y[i];
	}
	*b /= st2;         /* slope  */
	*a = (sy - sx*(*b)) / ss; /* intercept */
	siga = sqrt((1.0 + sx*sx / (ss*st2)) / ss);
	sigb = sqrt(1.0 / st2);
	chi2 = 0.0;
	sst = 0.0;
	for (i = 0; i < ndata; i++) {
		chi2 += SQR(y[i] - (*a) - (*b) * x[i]);
		sst += SQR(y[i] - syoss);
	}
	sigdat = sqrt(chi2 / (ndata - 2));
	siga *= sigdat;
	sigb *= sigdat;
	*R2 = 1.0 - chi2 / sst;
	*avar = siga;
	*bvar = sigb;
	return 0;
}
unsigned short SfrDataProces::check_slope(double slope, unsigned short *size_y, int *numcycles, double mincyc, int errflag)
//{
//	double absslope;
//
//	absslope = fabs(slope);
//
//	if (*numcycles <= 0)
//		(*numcycles) = (int)((*size_y)*absslope);
//
//	/* If the slope is too small not enough rows for mincy (typically 5)
//	full periods, then alert the user. */
//	if (absslope < mincyc / (double)(*size_y)){
//		if (errflag == 1) {
//			fprintf(stderr, "WARNING: Edge angle (%f) is so shallow it needs\n",
//				atan(slope) * 180 / M_PI);
//			fprintf(stderr, "  %d lines of data (%.1f cycles) for accurate results\n",
//				(int)ceil(mincyc / absslope), mincyc);
//			return 0;
//		}
//		else
//			return 1;
//	}
//
//	if (absslope > (double)(1.0 / 4.0)) {
//		int rows_per_col;
//		double bestcycle, x;
//
//		if (absslope > (double)(5.0 / 4.0))
//		{
//			fprintf(stderr, "ERROR: Edge angle (%f) is too large\n",
//				atan(slope) * 180 / M_PI);
//			return 1;
//		}
//
//		rows_per_col = (int)floor(1 / absslope + 0.5);
//		x = fabs(1 / (double)rows_per_col - absslope);
//		bestcycle = 4 * rows_per_col*x*ceil(1.0 / x / (double)rows_per_col / (double)rows_per_col - 1.0);
//		if ((int)ceil(mincyc*bestcycle) > *size_y) {
//			if (errflag == 1) {
//				fprintf(stderr, "WARNING: Edge angle (%f) will reduce SFR accuracy\n",
//					atan(slope) * 180 / M_PI);
//				fprintf(stderr, "   if %g * %f = %d lines of data are not in ROI\n\n",
//					mincyc, bestcycle,
//					(int)ceil(mincyc*bestcycle));
//				return 0;
//			}
//			else
//				return 1;
//		}
//	}
//
//	/* Figure out how many lines to use for size_y: new window will start at
//	top and go down that number of lines < size_y such that an integer
//	number of x-transitions are made by the edge; for example, if we had a
//	slope of 10 (the edge goes down 10 lines before jumping over one pixel
//	horizontally), and size_y = 35, the new size_y is going to be 30 (an
//	integer multiple of 10, less than 35). */
//
//	if (((*numcycles) / absslope) <= *size_y)
//		*size_y = (unsigned short)((*numcycles) / absslope);
//
//	return 0;
//}

{
	double absslope;

	absslope = fabs(slope);

	if (*numcycles <= 0)
		(*numcycles) = (int)((*size_y)*absslope);

	/* If the slope is too small not enough rows for mincy (typically 5)
	full periods, then alert the user. */
	if (absslope < mincyc / (double)(*size_y)){
		if (errflag == 1) {
			fprintf(stderr, "WARNING: Edge angle (%f) is so shallow it needs\n",
				atan(slope) * 180 / M_PI);
			fprintf(stderr, "  %d lines of data (%.1f cycles) for accurate results\n",
				(int)ceil(mincyc / absslope), mincyc);
			return 0;
		}
		else
			return 1;
	}

	if (absslope > (double)(1.0 / 4.0)) {
		int rows_per_col;
		double bestcycle, x;

		if (absslope > (double)(5.0 / 4.0))
		{
			fprintf(stderr, "ERROR: Edge angle (%f) is too large\n",
				atan(slope) * 180 / M_PI);
			return 1;
		}

		rows_per_col = (int)floor(1 / absslope + 0.5);
		x = fabs(1 / (double)rows_per_col - absslope);
		bestcycle = 4 * rows_per_col*x*ceil(1.0 / x / (double)rows_per_col / (double)rows_per_col - 1.0);
		if ((int)ceil(mincyc*bestcycle) > *size_y) {
			if (errflag == 1) {
				fprintf(stderr, "WARNING: Edge angle (%f) will reduce SFR accuracy\n",
					atan(slope) * 180 / M_PI);
				fprintf(stderr, "   if %g * %f = %d lines of data are not in ROI\n\n",
					mincyc, bestcycle,
					(int)ceil(mincyc*bestcycle));
				return 0;
			}
			else
				return 1;
		}
	}

	/* Figure out how many lines to use for size_y: new window will start at
	top and go down that number of lines < size_y such that an integer
	number of x-transitions are made by the edge; for example, if we had a
	slope of 10 (the edge goes down 10 lines before jumping over one pixel
	horizontally), and size_y = 35, the new size_y is going to be 30 (an
	integer multiple of 10, less than 35). */

	if (((*numcycles) / absslope) <= *size_y)
		*size_y = (unsigned short)((*numcycles) / absslope);

	return 0;
}
/*****************************************************************************/
/* Notes: this part gets averages and puts them in a number of bins, equal to
size_x times alpha.  Next a long check is done in case one bin gets no values
put into it: if this is the case, it will keep checking previous bins until it
finds one with non-zero counts and will use that value as its current bin
average. If the first bin has zero counts the program checks bins in the
forward rather than reverse direction. If, in any case, the end of the array
of bins is reached before finding a non-zero count, the program starts
checking in the opposite direction. A bin with zero counts is not allowed,
since each bin will be divided by counts at the end. */

unsigned short SfrDataProces::bin_to_regular_xgrid(unsigned short alpha,
	double *edgex, double *Signal,
	double *AveEdge, long *counts,
	unsigned short size_x,
	unsigned short size_y)
{
	long i, j, k, bin_number;
	long bin_len;
	int nzeros;

	bin_len = size_x * alpha;

	// 进行超采样， 把所有数据超采样到长度为size_x * alpha（4）的一行数据中
	for (i = 0; i<bin_len; i++) {
		AveEdge[i] = 0;
		counts[i] = 0;
	}
	for (i = 0; i<(size_x*(long)size_y); i++)
	{
		bin_number = (long)floor((double)alpha*edgex[i]); // 点离中心的距离*alpha（4）
		if (bin_number >= 0) // 下界之内
		{
			if (bin_number <= (bin_len - 1))  // 上界之内
			{
				AveEdge[bin_number] = AveEdge[bin_number] + Signal[i]; // 累加到对应距离内的容器
				counts[bin_number] = (counts[bin_number]) + 1; // 计数器加一
			}
		}
	}

	// 检查是否每个点都有数据
	nzeros = 0;
	for (i = 0; i<bin_len; i++)
	{
		j = 0;
		k = 1;
		if (counts[i] == 0)
		{
			nzeros++;
			if (i == 0)
			{ // 第一个点没有数据
				while (!j) // 寻找下个计数非0的点， 并将该点的均值赋给当前点
				{
					if (counts[i + k] != 0)
					{
						AveEdge[i] = AveEdge[i + k] / ((double)counts[i + k]);
						j = 1;
					}
					else k++;
				}
			}
			else
			{
				/* 个人觉得， 这段寻找算法写复杂了。
				* 当非第一个点的计数为0时， 大可以直接取前一个点的均值直接赋值给当前点，
				* 效果是一样的。 算法复杂度低， 代码也简洁清晰. */
				while (!j && ((i - k) >= 0)) // 向前寻找计数非0的点， 并将第一个计数非0的点的均值赋值给当前点
				{
					if (counts[i - k] != 0)
					{
						AveEdge[i] = AveEdge[i - k];   /* Don't divide by counts since it already happened in previous iteration */
						j = 1;
					}
					else k++;
				}
				if ((i - k) < 0) // 如果向前没找到计数非0的点， 则开始向后寻找， 并将第一个计数非0的点的均值赋值给当前点
				{
					k = 1;
					while (!j)
					{
						if (counts[i + k] != 0)
						{
							AveEdge[i] = AveEdge[i + k] / ((double)counts[i + k]);
							j = 1;
						}
						else k++;
					}
				}
			}
		}
		else
			AveEdge[i] = (AveEdge[i]) / ((double)counts[i]); // 计算计数非0点均值
	}

	if (nzeros > 0) {
		fprintf(stderr, "\nWARNING: %d Zero counts found during projection binning.\n", nzeros);
		fprintf(stderr, "The edge angle may be large, or you may need more lines of data.\n\n");
	}
	return nzeros;
}
/*****************************************************************************/
/* This has been modified from Annex A, to more closely match Annex D and
reduce finite difference errors.  Now allows either [-1 1] derivative
(when separation = 0) or [-1/2 0 1/2] derivative (when separation=1)

Inputs:   len          length of ESF array
AveEdge      array of ESF values
separation   type of derivative
0 = [-1 1]
1 = [-1/2 0 1/2]

Outputs:  AveTmp       array of original ESF values
AveEdge      array of derivative (LSF) values
centroid     centroid of the derivative
*/
// 计算ESF的差分图像LSF， 并计算LSF的质心
void SfrDataProces::calculate_derivative(unsigned int len, double *AveTmp, double *AveEdge,
	double *centroid, int separation)
{
	unsigned long i;
	double dt, dt1;

	dt = 0.0;
	dt1 = 0.0;

	for (i = 0; i< len; i++)
		AveTmp[i] = AveEdge[i];

	for (i = 1; i< len - separation; i++) {
		/* Not wasting time with division by 2 since constant factors don't
		change SFR computation */
		AveEdge[i] = (AveTmp[i + separation] - AveTmp[i - 1]);
		if (separation == 1)
			AveEdge[i] /= 2.0;
		dt += AveEdge[i] * (double)i;
		dt1 += AveEdge[i];
	}

	*centroid = dt / dt1;

	AveEdge[0] = AveEdge[1];
	if (separation == 1) AveEdge[len - 1] = AveEdge[len - 2];
}
/*****************************************************************************/
// 寻找PSF最大点， 如果存在多个最大点， 则取这些点的中点
void SfrDataProces::locate_max_PSF(unsigned int len,
	double *AveEdge, long *pcnt2)

{
	unsigned long i;
	double dt = 0.0, dt_new = 0.0;
	long left = -1L, right = -1L;

	/* find maximim value in Point Spread Function array */
	for (i = 0; i<len; i++) {
		dt_new = fabs(AveEdge[i]);
		if (dt_new > dt) {
			(*pcnt2) = (long)i;
			dt = dt_new;
		}
	}
	/* find leftmost and rightmost occurrence of maximum */
	for (i = 0; i<len; i++) {
		dt_new = fabs(AveEdge[i]);
		if (dt_new == dt) {
			if (left < 0) left = i;
			right = i;
		}
	}
	/* find centre of maxima */
	(*pcnt2) = (right + left) / 2;
}

/*****************************************************************************/
void SfrDataProces::apply_hamming_window(unsigned short alpha,
	unsigned int oldlen,
	unsigned short newxwidth,
	double *AveEdge, long *pcnt2)
{
	long i, j, k, begin, end, edge_offset;
	double sfrc;

	/* Shift the AvgEdge[i] vector to centre the lsf in the transform window */
	// 将LSF的最大值移到中心位置， 两边由于移动造成的空位由0补齐
	edge_offset = (*pcnt2) - (oldlen / 2);
	if (edge_offset != 0) {
		if (edge_offset < 0) {
			for (i = oldlen - 1; i > -edge_offset - 1; i--)
				AveEdge[i] = (AveEdge[i + edge_offset]);
			for (i = 0; i < -edge_offset; i++)
				AveEdge[i] = 0.00; /* last operation */
		}
		else {
			for (i = 0; i < oldlen - edge_offset; i++)
				AveEdge[i] = (AveEdge[i + edge_offset]);
			for (i = oldlen - edge_offset; i < oldlen; i++)
				AveEdge[i] = 0.00;
		}
	}
	/* Multiply the LSF data by a Hamming window of width NEWXWIDTH*alpha */
	// 在当前上下文中， 下面这段代码应该不会起任何作用， 不知道为什么会有这么复杂而冗余的逻辑
	begin = (oldlen / 2) - (newxwidth*alpha / 2);
	if (begin < 0) begin = 0;
	end = (oldlen / 2) + (newxwidth*alpha / 2);
	if (end > oldlen)  end = oldlen;
	for (i = 0; i< begin; i++)
		AveEdge[i] = 0.0;
	for (i = end; i< oldlen; i++)
		AveEdge[i] = 0.0;

	// 给begin和end之间的数据加上汉明窗
	// 汉明窗 W(n,α ) = (1 -α ) - α cos(2*PI*n/(N-1)) ，（0≤n≤N-1）
	// 一般情况下，α取0.46
	// 下面计算方法等于窗发生了平移（故符号发生了变化）， 结果是一样的
	for (i = begin, j = -newxwidth*alpha / 2; i < end; i++, j++) {
		sfrc = 0.54 + 0.46*cos((M_PI*(double)j) / (newxwidth*alpha / 2));
		AveEdge[i] = (AveEdge[i])*sfrc;
	}

	// 将有效数据平移到起始位置
	// 在当前上下文中， 下面这段代码应该不会起任何作用， 不知道为什么会有这么复杂而冗余的逻辑
	if (begin != 0) /* Shift LSF to begin at index 0 (rather than begin) */
	for (k = 0, i = begin; k<newxwidth*alpha; i++, k++)
		AveEdge[k] = AveEdge[i];

}
/*****************************************************************************/
/* This is the DFT magnitude code                                            */
unsigned short SfrDataProces::ftwos(long number, double dx, double *lsf, long ns, double ds, double *sfr)
{
	double a, b, twopi, g;
	long i, j;

	//                n-1              k
	// DFT ==> X[k] = Σ  x[n]e^(-j2π - n)
	//                n=0              N

	twopi = 2.0 * M_PI;
	for (j = 0; j < ns; j++)
	{
		g = twopi * dx * ds * (double)j;
		for (i = 0, a = 0, b = 0; i < number; i++)
		{
			a += lsf[i] * cos(g * (double)(i));
			b += lsf[i] * sin(g * (double)(i));
		}
		//计算j=60的值
		sfr[j] = sqrt(a * a + b * b);
	}
	return 0;
}


