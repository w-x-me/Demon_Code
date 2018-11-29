#include"sfr-method.h"
SfrMethod::SfrMethod()
{}

double SfrMethod::FFC_Func(HTuple hv_HomMat2D, HTuple hv_offRow, HTuple hv_offCol, HTuple hv_hwidth, HTuple hv_hheight)
{
	HTuple  hv_ULRow, hv_ULCol, hv_weidth, hv_height;
	HObject  ho_ContoursAffineTrans, ho_Rectangle1;
	HTuple  hv_RowTrans, hv_ColTrans;


	g_ppi = 287;////
	g_scan_header = 17;
	g_scan_cols = 1600;
	g_scan_rows = 1200;


	AffineTransPixel(hv_HomMat2D, hv_offRow, hv_offCol, &hv_RowTrans, &hv_ColTrans);

	GenRectangle2(&ho_Rectangle1, hv_RowTrans, hv_ColTrans, 0, hv_hwidth, hv_hheight);
	//AffineTransContourXld(ho_ModelContours, &ho_ContoursAffineTrans, hv_HomMat2D);


	hv_ULRow = hv_RowTrans - hv_hheight;
	hv_ULCol = hv_ColTrans - hv_hwidth;
	hv_weidth = hv_hwidth * 2;
	hv_height = hv_hheight * 2;
	//****ROI宽度和高度
	centerx = hv_ULCol.D();//列
	centery = hv_ULRow.D();//行
	width = hv_weidth.D();//宽度
	height = hv_height.D();//高度

	const char*  src = "D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\ffc.tiff";
	const char*  src2 = "D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\oecf.txt";

	strcpy_s(image_filename, src);
	strcpy_s(data_filename, src2);

	char problem_string[82];
	unsigned char rotation;
	int i;
	double *farea;
	double slope, scale, b;
	int size_x, size_y;
	int len, err, bin_len;
	int rgt_side, left_side;
	int center;
	int numcycles = 0;
	double *Freq = NULL;
	double *disp = NULL;
	double *ref_lut;
	double off, R2;
	int center_x, center_y, new_x, new_y;
	int lowest_val, highest_val, grey_level, first, last;
	int piv_err;

	TIFF* tif = NULL;

	/* Once-only initializations */
	g_scan_image_file_id = 0;
	g_problem_count = 0;                /* # of problems in our problem report */
	g_IQS_problem_count = 0;

	get_switches(image_filename, data_filename);

	/* always append output to this file */
	//if ((g_mtfout = fopen(MTFOUTNAME, "a")) == NULL)
	//{

	//	return -1;
	//}

	/* command line args */
	get_args(image_filename, data_filename, &tif); // 获取源文件名并读取文件头， 获取ROI位置， 如果需要读取计算角度的两个点位

	g_target_res = 500;

	if (abs((int)g_ppi - g_target_res) > 10)
	{

	}

	// 从ROI 4个角落各读取4个像素点， 用于判断刀口方向， 并确认ROI区域的合法性
	input_area(tif, &rotation, g_test_pattern_yul, g_test_pattern_ylr, g_test_pattern_xul, g_test_pattern_xlr);

	/* read the image in - we store it internally in a standard way */
	// 读取ROI图像， 如果并将水平刀口转换为垂直刀口
	read_in_image(tif, rotation, image_filename, &size_x, &size_y);

	/* get reflectance */
	// 创建反射查找表， 将图像灰阶映射在0~1范围内
	ref_lut = read_in_ref_lut(data_filename, &lowest_val, &highest_val);
	if (g_scan_image_file_id != 0)
	{
		_close(g_scan_image_file_id);
		g_scan_image_file_id = 0;
	}
	// 将原图ROI映射到反射ROI
	len = size_x*size_y;
	farea = (double *)malloc(len*sizeof(double));
	for (i = 0; i < len; i++)
	{
		grey_level = g_image_array[i];
		if (grey_level < lowest_val || grey_level > highest_val)
		{
			// MTFPRINT("ERROR: OECF range does not cover the entire image\n")
			// MTFPRINT2("       Greylevel %d found in image, but not OECF\n", grey_level)
			//exit(-1);
			return -1;
		}
		farea[i] = (double)ref_lut[grey_level];
	}
	// 计算ROI中超出取值范围[0, 255]外的像素比例
	// 前面像素映射的时候已经逐点确认过是否所有像素在oecf范围内， 感觉这个函数没什么实际作用
	clipping(0, 255, 0.02, g_image_array, len);

	double param = sfr_data_proces.sfrProc(&Freq, &disp, &bin_len, farea, (unsigned short)size_x, &size_y, &slope, &numcycles, &center, &off, &R2, g_version, 0, g_userangle);

	return param;
}

double  SfrMethod::RFC_Func(HTuple hv_HomMat2D, HTuple hv_offRow, HTuple hv_offCol, HTuple hv_hwidth, HTuple hv_hheight)
{



	HObject ho_Rectangle;
	HTuple  hv_RowTrans, hv_ColTrans;
	HTuple  hv_ULRow, hv_ULCol, hv_weidth, hv_height;

	g_ppi = 287;////
	g_scan_header = 17;
	g_scan_cols = 1600;
	g_scan_rows = 1200;

	centerx = 0;
	centery = 0;
	width = 0;
	height = 0;


	AffineTransPixel(hv_HomMat2D, hv_offRow, hv_offCol, &hv_RowTrans, &hv_ColTrans);
	GenRectangle2(&ho_Rectangle, hv_RowTrans, hv_ColTrans, 0, hv_hwidth, hv_hheight);

	hv_ULRow = hv_RowTrans - hv_hheight;
	hv_ULCol = hv_ColTrans - hv_hwidth;
	hv_weidth = hv_hwidth * 2;
	hv_height = hv_hheight * 2;

	centerx = hv_ULCol.D();//列
	centery = hv_ULRow.D();//行
	width = hv_weidth.D();//宽度
	height = hv_height.D();//高度


	const char*  src = "D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\rfc.tiff";
	const char*  src2 = "D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\oecf.txt";

	strcpy_s(image_filename, src);
	strcpy_s(data_filename, src2);


	char problem_string[82];
	unsigned char rotation;
	int i;
	double *farea;
	double slope, scale, b;
	int size_x, size_y;
	int len, err, bin_len;
	int rgt_side, left_side;
	int center;
	int numcycles = 0;
	double *Freq = NULL;
	double *disp = NULL;
	double *ref_lut;
	double off, R2;
	int center_x, center_y, new_x, new_y;
	int lowest_val, highest_val, grey_level, first, last;
	int piv_err;

	TIFF* tif = NULL;
	/* Once-only initializations */
	g_scan_image_file_id = 0;
	g_problem_count = 0;                /* # of problems in our problem report */
	g_IQS_problem_count = 0;

	get_switches(image_filename, data_filename);

	/* always append output to this file */
	//if ((g_mtfout = fopen(MTFOUTNAME, "a")) == NULL)
	//{

	//return -1;
	//}

	/* command line args */
	get_args(image_filename, data_filename, &tif); // 获取源文件名并读取文件头， 获取ROI位置， 如果需要读取计算角度的两个点位

	g_target_res = 500;

	if (abs((int)g_ppi - g_target_res) > 10)
	{

	}

	// 从ROI 4个角落各读取4个像素点， 用于判断刀口方向， 并确认ROI区域的合法性
	input_area(tif, &rotation, g_test_pattern_yul, g_test_pattern_ylr, g_test_pattern_xul, g_test_pattern_xlr);

	/* read the image in - we store it internally in a standard way */
	// 读取ROI图像， 如果并将水平刀口转换为垂直刀口
	read_in_image(tif, rotation, image_filename, &size_x, &size_y);

	/* get reflectance */
	// 创建反射查找表， 将图像灰阶映射在0~1范围内
	ref_lut = read_in_ref_lut(data_filename, &lowest_val, &highest_val);

	// 将原图ROI映射到反射ROI
	len = size_x*size_y;
	farea = (double *)malloc(len*sizeof(double));
	for (i = 0; i < len; i++)
	{
		grey_level = g_image_array[i];
		if (grey_level < lowest_val || grey_level > highest_val)
		{
			// MTFPRINT("ERROR: OECF range does not cover the entire image\n")
			// MTFPRINT2("       Greylevel %d found in image, but not OECF\n", grey_level)
			//exit(-1);
			return -1;
		}
		farea[i] = (double)ref_lut[grey_level];
	}

	// 计算ROI中超出取值范围[0, 255]外的像素比例
	// 前面像素映射的时候已经逐点确认过是否所有像素在oecf范围内， 感觉这个函数没什么实际作用
	clipping(0, 255, 0.02, g_image_array, len);
	/* calculate the sfr on this area */
	double	param = 0.0;
	param = sfr_data_proces.sfrProc2(&Freq, &disp, &bin_len, farea, (unsigned short)size_x, &size_y, &slope, &numcycles, &center, &off, &R2, g_version, 0, g_userangle);

	return  param;
}

void SfrMethod::get_switches(char *image_filename, char *data_filename)
{
	int centerx = 0, centery = 0, width = 0, height = 0;
	char switch_entry = ' ';
	int count = 0;
	int read_value = 0;

	g_streamline_args = g_reversepolarity = g_extended = g_debug = g_autorefine = 0;
	g_nocompare = 0;
	g_userangle = 0;
	g_version = 0;
	g_center = 0;



	g_debug = 0;

	if (g_streamline_args)
	{
		if (g_center)
		{
			g_test_pattern_xul = centerx - width / 2;
			g_test_pattern_yul = centery - height / 2;
		}
		else
		{
			g_test_pattern_xul = centerx;
			g_test_pattern_yul = centery;
		}
		g_test_pattern_xlr = g_test_pattern_xul + width;
		g_test_pattern_ylr = g_test_pattern_yul + height;
	}

}

void SfrMethod::get_args(char *image_filename, char *data_filename, TIFF** tif)
{


	while ((*tif == NULL) && (g_scan_image_file_id <= 0))
	{
		/*if (!g_streamline_args)
		{
		fprintf(stderr,"\n\n Enter image filename:   \t");
		scanf("%s",image_filename);
		}*/

#ifdef USE_TIFF
		{
			char *tmp;
			if (((tmp = strstr(image_filename, ".pgm")) == NULL || tmp != strrchr(image_filename, '.')) &&
				((tmp = strstr(image_filename, ".PGM")) == NULL || tmp != strrchr(image_filename, '.')))
				*tif = TIFFOpen((char *)image_filename, "r");
		}
#endif
		if (*tif == NULL)
		{

			g_pgm = 0;
			read_pgm_header(image_filename); // 读pgm文件头信息

			g_scan_image_file_id = _open(image_filename, (O_RDONLY | O_BINARY));
			if (g_scan_image_file_id < 0)
			{
				//fprintf(stderr, "\nCould not open %s\n", image_filename);
				//fprintf(stderr, "%s\n\n", strerror(errno));
				return;
			}
			//_close(g_scan_image_file_id);
		}
	}

	if (*tif == NULL)
	{
		if (!g_pgm)
		{
			//输入图像 头字节  图像宽度 高度
			// fprintf(stderr,"Image file is not in TIFF or PGM format\n");
			//  fprintf(stderr," Enter image header bytes, pixel width, pixel height:\t");
			// GET_COORD_PAIR(&g_scan_header,&g_scan_cols,&g_scan_rows);
			//前置ffc


			//g_scan_header = 17;
			//g_scan_cols = 1600;
			//g_scan_rows = 1200;//图像大小

			g_bps = 8;
			g_photometric = 1;

		}
	}
#ifdef USE_TIFF
	else
	{
		unsigned short sampleformat;
		unsigned short samplesperpixel;
		g_bps = 8;
		sampleformat = 1;
		samplesperpixel = 1;
		TIFFGetField(*tif, TIFFTAG_IMAGEWIDTH, &g_scan_cols);
		(void)TIFFGetField(*tif, TIFFTAG_IMAGELENGTH, &g_scan_rows);
		(void)TIFFGetField(*tif, TIFFTAG_BITSPERSAMPLE, &g_bps);

		/* Check to make sure it's a 1 band image */
		(void)TIFFGetField(*tif, TIFFTAG_SAMPLESPERPIXEL, &samplesperpixel);
		if (samplesperpixel != 1)
		{
			//	MTFPRINT2("ERROR: Cannot read more than one sample per pixel (%d).\n", samplesperpixel)
			//exit(-1);
			return -1;
		}

		/* reading in the tag on photometric interpretation - 7/22/94 - gtk */
		(void)TIFFGetField(*tif, TIFFTAG_PHOTOMETRIC, &g_photometric);
		/*    MTFPRINT2("G_photometric = %d\n", g_photometric); */
		(void)TIFFGetField(*tif, TIFFTAG_SAMPLEFORMAT, &sampleformat);
		if (sampleformat != 1)
		{
			// MTFPRINT2("ERROR: Signed or float imagery. SampleFormat = %d\n", sampleformat);
			return -1;
		}
		if (g_bps != 8)
		{
			//MTFPRINT2("ERROR: Cannot handle %d BitsPerPixel TIFF format. Try 8.\n",g_bps);
			// exit(-1);
			return -1;
		}
	}
#endif

	g_bytes_per_pixel = (g_bps + 7) / 8; // 计算每像素字节数
	g_max_pixel_value = (1 << g_bps) - 1; // 计算灰阶最大值


	if (!g_streamline_args)
	{
		/*  int c;

		while ( getchar() != (int)'\n');
		fprintf(stderr, " OECF: if nonlinear enter filename, if linear press RETURN ");
		while ((c = getchar()) == EOF);
		if((char)c == '\r' || (char)c == '\n')
		strcpy(data_filename, "linear");
		else {
		ungetc((int)c,stdin);
		scanf("%s",data_filename);
		}

		fprintf(stderr, " Enter pixels per inch (PPI):   ");
		scanf("%lf", &g_ppi);

		fprintf(stderr,"\n     (ref: col,row = 0,0 at upper left corner of ENTIRE image,\n");
		fprintf(stderr,"     cols increase left to right, rows increase top to bottom.)\n");*/
		// 下面开始获取ROI位置
		/* if (g_center)
		fprintf(stderr,"\n Enter Col, Row for center pixel (~ on edge):\t");
		else
		fprintf(stderr,"\n Enter Col, Row for UL pixel of ROI:\t");
		GET_INT_PAIR(&centerx,&centery)

		fprintf(stderr," Enter Width, Height for region of interest:\t");
		GET_INT_PAIR(&width,&height)*/

		if (g_center)
		{
			g_test_pattern_xul = centerx - width / 2;
			g_test_pattern_yul = centery - height / 2;
		}
		else
		{
			g_test_pattern_xul = centerx;
			g_test_pattern_yul = centery;
		}
		g_test_pattern_xlr = g_test_pattern_xul + width;
		g_test_pattern_ylr = g_test_pattern_yul + height;

		/* if( g_userangle )
		{
		do
		{
		fprintf(stderr, "\nEnter edge endpoints to define edge tilt");
		fprintf(stderr, "\n(left/right for HorzEdge, top/bot for VertEdge)");
		fprintf(stderr, "\n Enter Col, Row for 1st Edge Point:\t");
		GET_FLOAT_PAIR(&g_pt1x, &g_pt1y)
		fprintf(stderr, " Enter Col, Row for 2nd Edge Point:\t");
		GET_FLOAT_PAIR(&g_pt2x, &g_pt2y)
		if (g_pt2x == g_pt1x || g_pt2y == g_pt1y)
		fprintf(stderr, "*** Edge points cannot have the same row or col value. Try again. *** \n");
		} while (g_pt2x == g_pt1x || g_pt2y == g_pt1y);
		}*/
	}

}

void SfrMethod::input_area(TIFF *tif, unsigned char *rotation, int rstart, int rend, int cstart, int cend)
{
	short j;
	unsigned char *buf;
	double ave[4];
	double topdiff, botdiff, lftdiff, rgtdiff;
	int extra_height;
	int flag = 0;

	// 如果ROI边角越界， 调整ROI四角坐标和边角对其
	if (g_test_pattern_xul < 0) { g_test_pattern_xul = 0; flag = 1; }
	if (g_test_pattern_yul < 0) { g_test_pattern_yul = 0; flag = 1; }
	if (g_test_pattern_xlr > g_scan_cols) { g_test_pattern_xlr = g_scan_cols; flag = 1; }
	if (g_test_pattern_ylr > g_scan_rows) { g_test_pattern_ylr = g_scan_rows; flag = 1; }

	// 将ROI尺寸限定在300*300以内， 任何一个坐标超出范围都只取改坐标的中心300pixel
	extra_height = g_test_pattern_ylr - g_test_pattern_yul - 300;

	if (extra_height > 0)
	{
		flag = 2;
		g_test_pattern_yul += (extra_height + 1) / 2;
		g_test_pattern_ylr = g_test_pattern_yul + 300;
	}

	extra_height = g_test_pattern_xlr - g_test_pattern_xul - 300;

	if (extra_height > 0)
	{
		flag = 2;
		g_test_pattern_xul += (extra_height + 1) / 2;
		g_test_pattern_xlr = g_test_pattern_xul + 300;
	}

	if (flag)
	{
		rstart = g_test_pattern_yul;
		rend = g_test_pattern_ylr;
		cstart = g_test_pattern_xul;
		cend = g_test_pattern_xlr;
	}

	// 估计是历史遗留代码， 当前代码不存在flag==1的情况.(重新定位ROI中心)
	if (flag == 1)
	{
		//fprintf(stderr, "ROI center/dims changed to stay within the image.\n");
		//fprintf(stderr, "  New center (%d,%d)  dims %d x %d\n",(g_test_pattern_xlr+g_test_pattern_xul)/2,
		// (g_test_pattern_ylr+g_test_pattern_yul)/2,(g_test_pattern_xlr-g_test_pattern_xul), (g_test_pattern_ylr-g_test_pattern_yul));
	}
	if (flag == 2)
	{
		// fprintf(stderr, "ROI dimension reduced to 300.\n");
	}



	/* enough to hold a single scan line */
	buf = NULL;
	if (g_scan_image_file_id)
	{
		buf = (unsigned char*)calloc((unsigned int)g_scan_cols, sizeof(unsigned char));
	}
#ifdef USE_TIFF
	else
	{
		buf = (unsigned char*)calloc((unsigned int)TIFFScanlineSize(tif), sizeof(unsigned char));
	}
#endif
	if (buf == NULL)
	{
		// fprintf(stderr, "\nCan't allocate memory for scanline buffer\n\n");
		//exit(-1);
		return;
	}

	for (j = 0; j<4; j++)
		ave[j] = 0.0;

	for (j = 0; j<2; j++)
	{
		read_scan_line(tif, buf, rstart + j); // 读取ROI顶部两行中的一行
		switch (g_bytes_per_pixel)
		{
		case 1:
			ave[0] += (double)(buf[cstart] + buf[cstart + 1]); // 累加ROI左上4个pixels的灰阶
			ave[1] += (double)(buf[cend - 1] + buf[cend - 2]); // 累加ROI右上4个pixels的灰阶
			break;
		default:
			// fprintf(stderr,"\nCannot handle more than 1 byte per pixel!!\n\n");
			//exit(-1);
			return;
		}
		read_scan_line(tif, buf, rend - j - 1); // 读取ROI底部两行中的一行
		switch (g_bytes_per_pixel)
		{
		case 1:
			ave[2] += (double)(buf[cstart] + buf[cstart + 1]); // 累加ROI左下4个pixels的灰阶
			ave[3] += (double)(buf[cend - 1] + buf[cend - 2]); // 累加ROI右下4个pixels的灰阶
			break;
		default:
			//  fprintf(stderr,"\nCannot handle more than 1 byte per pixel!!\n\n");
			return;
		}
	}

	free(buf);

	// 求ROI四个角的灰阶均值
	for (j = 0; j<4; j++)
		ave[j] /= 4.0;

	// ave[0] --> 左上
	// ave[1] --> 右上
	// ave[2] --> 左下
	// ave[3] --> 右下
	// 计算ROI各方向两个极点的对比度（MTF）
	// 对比度越大， 表示灰阶差异越大
	topdiff = (ave[1] - ave[0]) / (ave[1] + ave[0]);
	botdiff = (ave[3] - ave[2]) / (ave[3] + ave[2]);
	lftdiff = (ave[2] - ave[0]) / (ave[2] + ave[0]);
	rgtdiff = (ave[3] - ave[1]) / (ave[3] + ave[1]);

	// 1. 判断ROI的长边是否和刀口方向对应
	// 2. 黑白极点的MTF是否大于0.2
	// 3. 确定黑白变化的方向没有错误
	// 4. 确定黑白变化方向上的像素点数为偶数， 如果不是则从高位减去一个像素使其变成偶数（估计和后面fft有关）
	if (cend - cstart <= rend - rstart)
	{
		/* Should be a vertical edge */
		if (fabs(topdiff + botdiff) < fabs(lftdiff + rgtdiff))
		{ // 1. 判断ROI的长边是否和刀口方向对应
			MTFPRINT("** ERROR:  Edge does not appear to be 'vertical'.\n")
				MTFPRINT("           Rerun with ROI where width > height\n")
				return;
		}
		if (fabs(topdiff) < 0.2 || fabs(botdiff) < 0.2) // 2. 黑白极点的MTF是否大于0.2
			MTFPRINT("Warning: Low edge contrast (< 20%% modulation)\n")
		if (topdiff*botdiff > 0)
		{ // 3. 确定黑白变化的方向没有错误
			*rotation = RIGHT;
			if ((g_test_pattern_xlr - g_test_pattern_xul) % 2 != 0)
			{ // 4. 确定黑白变化方向上的像素点数为偶数， 如果不是则从高位减去一个像素使其变成偶数（估计和后面fft有关）
				MTFPRINT("** Pixels across edge reduced to an even number **\n")
					g_test_pattern_xlr--;
			}
		}
		else
		{
			MTFPRINT("** ERROR: Can't determine edge orientation\n")
				return;
		}
	}
	else
	{
		/* rotate 90 for horizontal edge */
		if (fabs(topdiff + botdiff) > fabs(lftdiff + rgtdiff))
		{
			// MTFPRINT("** ERROR:  Edge does not appear to be 'horizontal'.\n")
			// MTFPRINT("           Rerun with ROI where width < height\n")
			exit(-1);
		}
		if (fabs(lftdiff) < 0.2 || fabs(rgtdiff) < 0.2)
			// MTFPRINT("Warning: Low edge contrast (< 20%% modulation)\n")
		if (lftdiff*rgtdiff > 0)
		{
			*rotation = BOTTOM;
			if (extra_height % 2 != 0)
			{
				//MTFPRINT("** Pixels across edge reduced to an even number **\n")
				g_test_pattern_ylr--;
			}
		}
		else
		{
			//  MTFPRINT("** ERROR: Can't determine edge orientation\n")
			return;
		}
	}
}

unsigned char *SfrMethod::make_debug_image(TIFF *tif, unsigned char *buf, unsigned char rotation)
{
	int i, j, k, jj, cnt;
	int height, width, full_height, full_width;
	int offset_x, offset_y;
	unsigned char *debug_array, *ptr;

	width = g_scan_cols;
	height = g_scan_rows;
	if (width > g_ppi*1.6) width = g_ppi*1.6;
	if (height > g_ppi*1.5) height = g_ppi*1.5;

	full_width = width;
	full_height = height;
	if (rotation == RIGHT)
		full_width += 10 + 4 * (g_test_pattern_xlr - g_test_pattern_xul);
	else
		full_height += 10 + 4 * (g_test_pattern_ylr - g_test_pattern_yul + 1);

	debug_array = (unsigned char *)calloc(full_height*full_width,
		sizeof(unsigned char));

	offset_x = offset_y = 0;
	if (g_test_pattern_xlr > width) offset_x = g_test_pattern_xlr - width;
	if (g_test_pattern_ylr > height) offset_y = g_test_pattern_ylr - height;

	if (rotation == RIGHT)
		g_start_ptr = debug_array + (g_test_pattern_yul - offset_y)*full_width
		+ width + 10;
	else
		g_start_ptr = debug_array + (height + 10)*full_width + (g_test_pattern_xul - offset_x);

	cnt = 0;
	for (i = offset_y, k = 0; k<height; i++, k++) {

		read_scan_line(tif, buf, i);

		if (i >= g_test_pattern_yul && i <= g_test_pattern_ylr) {
			if (rotation == RIGHT) {
				ptr = g_start_ptr + cnt*full_width;
				for (jj = 0, j = g_test_pattern_xul; j<g_test_pattern_xlr; j++, jj += 4)
					memset(ptr + jj, (int)(buf[j]), 4);
				cnt++;
			}
			else
			for (j = 0; j<4; j++, cnt++) {
				memcpy((g_start_ptr + cnt*full_width),
					(buf + g_test_pattern_xul),
					g_test_pattern_xlr - g_test_pattern_xul);
			}
		}
		/* Modify with box if needed */
		if (i == g_test_pattern_yul || i == (g_test_pattern_ylr - 1)) {
			for (j = g_test_pattern_xul; j<g_test_pattern_xlr; j++)
				buf[j] += 128;
		}
		else if (i>g_test_pattern_yul && i<g_test_pattern_ylr) {
			buf[g_test_pattern_xul] += 128;
			buf[g_test_pattern_xlr - 1] += 128;
		}

		if (g_userangle) {

			if (fabs(i - g_pt1y) < .6) buf[(int)rint(g_pt1x)] += 128;
			if (fabs(i - g_pt2y) < .6) buf[(int)rint(g_pt2x)] += 128;
		}

		memcpy((debug_array + k*full_width), (buf + offset_x), width);
	}

	g_debug_fullwidth = full_width;
	g_debug_fullheight = full_height;

	if (rotation != RIGHT)
		g_start_ptr += g_test_pattern_xlr - g_test_pattern_xul - 1;


	return debug_array;
}

void SfrMethod::read_in_image(TIFF *tif, unsigned char rotation, char *image_name, int *size_x, int *size_y)
{
	short input_row;
	short array_column_start = 0;
	short array_row_index;
	short array_column_index;
	short array_column_delta = 1;
	short array_row_delta = 1;
	short array_row_start = 0;
	unsigned short actual_rows, actual_cols;

	unsigned char *buf;
	short i;

	/* enough to hold a single scan line */
	buf = NULL;
	if (g_scan_image_file_id)
	{
		buf = (unsigned char*)calloc((unsigned int)g_scan_cols, sizeof(unsigned char));
	}
#ifdef USE_TIFF
	else {
		buf = (unsigned char*)calloc((unsigned int)TIFFScanlineSize(tif), sizeof(unsigned char));
	}
#endif
	if (buf == NULL)
	{
		fprintf(stderr,
			"\nCan't allocate memory for scanline buffer\n\n");
		return;
	}

	if (g_debug)
	{
		int j, k;

		/* given an input image file name of the form "base.ext", here we create
		an output file with the form "base8_box", where "base8" was taken from
		the first 8 characters of the input file name - the first 8 characters
		of "base".  If "base" has less than 8 characters, then all characters
		before the "." are used. 9/2/94 - gtk */

		i = strlen(image_name);
		j = i;
		while ((image_name[i] != '/') && (i >= 0))
		{
			if (image_name[i] == '.') j = i;
			i--;
		}
		i++;
		j = j - i;
		if (j > 20) j = 20;		/* no more than 8 characters */
		for (k = 0; k<j; k++)
			g_debug_file_name[k] = image_name[i + k];
		g_debug_file_name[j] = '\0';

#ifdef USE_TIFF
		strncat(g_debug_file_name, "_box.tif", 8);
#else
		strncat(g_debug_file_name, "_box.pgm", 8);
#endif
		fprintf(stderr, "\n\nDiagnostic output image:  %s\n\n", g_debug_file_name);

		g_debug_array = make_debug_image(tif, buf, rotation);
	}

	actual_cols = g_test_pattern_xlr - g_test_pattern_xul;
	actual_rows = g_test_pattern_ylr - g_test_pattern_yul;


	/* enough to hold the whole image */
	g_image_array = (unsigned char*)calloc((int)(actual_rows*actual_cols)*g_bytes_per_pixel, sizeof(char));
	if (g_image_array == NULL) {
		fprintf(stderr, "\nCan't allocate memory for image array\n\n");
		return;
	}

	/* As we read-in the test pattern area, we rotate it to a standard
	format, with a vertical edge;
	The variables below are set to cause the rotation to occur. These
	variables are used to index into the storage array as we process each
	scan line of the input image. */
	switch (rotation) {
	case BOTTOM:
		/* Horizontal - make top rows left cols */
		/* The first pixel of the input image becomes the bottom
		pixel of the first column in the output array. */
		/* For each input row we fill in a storage column from
		bottom to top; working our way from left to right. */
		array_column_start = 0;	/* left to right */
		array_column_delta = 1;	/* ditto */
		/* bottom to top */
		array_row_delta = -1;
		/* bottom most row */
		array_row_start = actual_cols - 1;
		break;
	case RIGHT:
		/* normal case - white patch at top - read in straight*/
		array_column_start = 0;
		array_column_delta = 1;
		array_row_delta = 1;
		array_row_start = 0;
		break;
	default:
		fprintf(stderr, "\nUnknown rotation!!\n\n");
		return;
	}

	// 读取ROI区域， 同时将水平的刀口转换为垂直刀口
	switch (rotation)
	{
	case BOTTOM:
		array_column_index = array_column_start;
		switch (g_bytes_per_pixel) {
		case 1:
			for (input_row = g_test_pattern_yul; input_row < g_test_pattern_ylr; input_row++)
			{
				read_scan_line(tif, buf, input_row);
				array_row_index = array_row_start;
				for (i = g_test_pattern_xul; i<g_test_pattern_xlr; i++)
				{
					g_image_array[array_column_index + array_row_index * actual_rows] = buf[i];
					array_row_index += array_row_delta;
				}
				array_column_index += array_column_delta;
			}
			break;
		default:
			fprintf(stderr, "\nCannot handle more than 1 byte per pixel!!\n\n");
			return;
		}
		break;
	case RIGHT:
		array_row_index = array_row_start;
		switch (g_bytes_per_pixel)
		{
		case 1:
			for (input_row = g_test_pattern_yul; input_row < g_test_pattern_ylr; input_row++)
			{
				read_scan_line(tif, buf, input_row);
				array_column_index = array_column_start;
				for (i = g_test_pattern_xul; i<g_test_pattern_xlr; i++)
				{
					g_image_array[array_row_index * actual_cols + array_column_index] = buf[i];
					array_column_index += array_column_delta;
				}
				array_row_index += array_row_delta;
			}
			break;
		default:
			fprintf(stderr, "\nCannot handle more than 1 byte per pixel!!\n\n");
			return;
		}
		break;
	default:
		fprintf(stderr, "\nUnknown rotation!!\n\n");
		return;
	}

	/* switch the dimensions to match the now rotated image chip */
	// 转换水平刀口的ROI尺寸为对应的垂直尺寸
	switch (rotation) {
	case BOTTOM:
		*size_x = actual_rows;
		*size_y = actual_cols;
		break;
	case RIGHT:
		*size_x = actual_cols;
		*size_y = actual_rows;
		break;
	}

	free(buf);

}

short SfrMethod::raw_readscanline(unsigned char *buf, short i)
{
	int pos;

	if ((unsigned)i > g_scan_rows - 1) return(-1);
	if (g_bytes_per_pixel != 1) return(-1);
	pos = g_scan_header + i*g_scan_cols;
	if (_lseek(g_scan_image_file_id, pos, 0) < 0) return(-1);
	if (_read(g_scan_image_file_id, buf, (int)g_scan_cols) != (int)g_scan_cols)
		return(-1);
	else
		return(0);
}

void SfrMethod::read_scan_line(TIFF *tif, unsigned char *buf, short line_num)
{
	int j;

	if (g_scan_image_file_id)
	{
		if (raw_readscanline(buf, line_num) < 0)
		{
			fprintf(stderr,
				"\nBad data read on imageline %d\n\n", line_num);
			return;
		}
	}
#ifdef USE_TIFF
	else {
		if (TIFFReadScanline(tif, buf, line_num, 0L) < 0) {
			fprintf(stderr,
				"\nBad data read on imageline %d\n\n", line_num);
			return ;
		}
	}
#endif

	/* IF the tif tag: PHOTOMETRICINTERPRETATION was read as 'white is zero';
	Then the polarity needs to be reversed.  Also, the user may have
	requested a forced polarity reversal.  This can be useful when reading
	RAW images on little-endian or big-endian systems, or when a TIFF
	image has an incorrectly marked photometric interpretation.
	Two polarity reversals (tiff photometric=0 + user request) results in
	no reversal required.
	*/


	// g_reversepolarity 和（g_photometric==0）有且只有一个成立的时候， 灰阶翻转
	if ((g_reversepolarity || (g_photometric == 0)) &&
		!(g_reversepolarity && (g_photometric == 0))) {

		switch (g_bytes_per_pixel) {
		case 1:
			for (j = 0; j<(int)g_scan_cols; j++)
				buf[j] = g_max_pixel_value - buf[j];
			break;
		default:
			fprintf(stderr, "\nCannot handle more than 1 byte per pixel!!\n\n");
			return;
		}
	}
}

int SfrMethod::compare_grey_reflectance_pairs(const void *first, const void *second)
{

	if (((grey_reflectance_pair *)first)->grey < ((grey_reflectance_pair *)second)
		->grey)
		return -1;

	if (((grey_reflectance_pair *)first)->grey >((grey_reflectance_pair *)second)
		->grey)
		return 1;

	return 0;

}

double* SfrMethod::read_in_ref_lut(char *data_filename, int *lowest_value, int *highest_value)
{
	FILE *fd;
	int i, j, tot;
	double *ref_lut;
	double ref, grey, m;
	char str[502];
	grey_reflectance_pair *grey_ref_pairs;
	int ncflag, comment_lines;

	ref_lut = (double *)malloc((g_max_pixel_value + 1)*sizeof(double));

	if (strcmp(data_filename, "linear") == 0)
	{
		
		*lowest_value = 0;
		*highest_value = 255;
		for (i = 0; i <= g_max_pixel_value; i++)
			ref_lut[i] = (double)i / (double)g_max_pixel_value;
	}
	else
	{
		fd = fopen(data_filename, "r");
		if (fd == NULL)
		{
			fprintf(stderr, "\nCould not open %s\n", data_filename);
			fprintf(stderr, "%s\n\n", strerror(errno));
			return(0);
		}

		i = 0; comment_lines = 0; ncflag = 0;
		while (fgets(str, 500, fd) != NULL)
		{
			if (ncflag == 0 && str[0] == '#')
			{
				comment_lines++;
			}
			else
			{
				ncflag = 1;
				i++;
			}
		}
		tot = i;
		fseek(fd, 0, SEEK_SET);

		grey_ref_pairs = (grey_reflectance_pair *)calloc(tot, sizeof(grey_reflectance_pair));

		for (i = 0; i<comment_lines; i++) fgets(str, 500, fd);
		i = 0;
		while (fscanf(fd, "%lf %lf", &ref, &grey) == 2 && i<tot)
		{
			grey_ref_pairs[i].reflectance = ref;
			grey_ref_pairs[i].grey = grey;
			i++;
		}
		tot = i;

		/* 根据灰度值(从低到高)对grey_reflectance_pair进行排序 */
		qsort(grey_ref_pairs, tot, sizeof(grey_reflectance_pair), compare_grey_reflectance_pairs);

		j = 0;
		i = ceil(grey_ref_pairs[0].grey);
		if (i<0) i = 0;
		if (i>g_max_pixel_value) i = g_max_pixel_value + 1;
		*lowest_value = i;
		/* 如果需要，可以在低端进行推断 */
		// oecf项的最小灰阶大于0且不为整的情况下， 采用前两个oecf项线性插值的方法估算小于最小oecf的第一个整数灰阶的ref
		if (i>0 && ceil(grey_ref_pairs[0].grey) != floor(grey_ref_pairs[0].grey))
		{
			*lowest_value -= 1;
			m = (grey_ref_pairs[1].reflectance - grey_ref_pairs[0].reflectance) / (grey_ref_pairs[1].grey - grey_ref_pairs[0].grey);
			ref_lut[i - 1] = ((double)i - 1 - grey_ref_pairs[0].grey)*m + grey_ref_pairs[0].reflectance;
		}
		for (; i<grey_ref_pairs[tot - 1].grey && i <= g_max_pixel_value; i++)
		{
			while ((double)i > grey_ref_pairs[j].grey && j<tot) j++; // 找到第一个不小于当前灰阶的oecf项
			if (j >= tot) break;
			if ((double)i == grey_ref_pairs[j].grey)				// oecf的灰阶恰巧是整数， 则直接将ref直接复制
				ref_lut[i] = grey_ref_pairs[j].reflectance;
			else
			{												// 否则采用线性插值的方法估算对应的ref
				m = (grey_ref_pairs[j].reflectance - grey_ref_pairs[j - 1].reflectance)
					/ (grey_ref_pairs[j].grey - grey_ref_pairs[j - 1].grey);
				ref_lut[i] = ((double)i - grey_ref_pairs[j - 1].grey)*m
					+ grey_ref_pairs[j - 1].reflectance;
			}
		}
		// oecf项的最大灰阶小于图片最大灰阶且不为整的情况下， 采用最后两个oecf项线性插值的方法估算大于最大oecf的第一个整数灰阶的ref
		if ((i <= g_max_pixel_value))
		{
			if ((double)i == grey_ref_pairs[tot - 1].grey)
			{
				ref_lut[i] = grey_ref_pairs[tot - 1].reflectance;
			}
			else
			{
				m = (grey_ref_pairs[tot - 1].reflectance - grey_ref_pairs[tot - 2].reflectance) / (grey_ref_pairs[tot - 1].grey - grey_ref_pairs[tot - 2].grey);
				ref_lut[i] = ((double)i - grey_ref_pairs[tot - 1].grey)*m + grey_ref_pairs[tot - 1].reflectance;
			}
			i++;
		}
		*highest_value = i - 1;
		fclose(fd);
	}

	return (ref_lut);
}

int SfrMethod::clipping(int low, int high, double thresh, unsigned char *img, int len)
{
	int i;
	unsigned char *buf;
	int nlow = 0;
	int nhigh = 0;
	int status = 0;

	switch (g_bytes_per_pixel)
	{
	case 1:
		buf = img;
		for (i = 0; i<len; i++, buf++)
		{
			if ((int)(*buf) <= low)
				nlow++;
			else if ((int)(*buf) >= high)
				nhigh++;
		}
		break;
	default:
		return -1;
	}

	if (nlow / (double)len > thresh)
	{
		
		status = 1;
	}
	if (nhigh / (double)len > thresh)
	{
		
		status = 1;
	}

	return(status);
}

int SfrMethod::read_pgm_header(char *image_filename)
{
	FILE *fp;
	int val, rows, cols;
	char header[256];
	int numread;

	fp = fopen(image_filename, "rb");
	if (fp == NULL) return (-2);

	do {
		if (fgets(header, 255, fp) == NULL)
		{
			fclose(fp);
			return (-1);
		}
	} while (header[0] == '#');

	if (strncmp(header, "P5", 2) != 0)
	{
		fclose(fp);
		return (-1);
	}

	do {
		if (fgets(header, 255, fp) == NULL)
		{
			fclose(fp);
			return (-1);
		}
	} while (header[0] == '#');

	numread = sscanf(header, "%d %d", &cols, &rows);
	g_scan_cols = cols;
	/*一行只有一个数字，读下一行得到高度 */
	if (numread != 2) {
		
		fgets(header, 255, fp);
		sscanf(header, "%d", &rows);
	}
	g_scan_rows = rows;

	fgets(header, 255, fp);
	sscanf(header, "%d", &val);
	if (val <= 255)
		g_bps = 8;

	g_scan_header = ftell(fp);

	fclose(fp);
	g_pgm = 1;
	g_photometric = 1;

	return(0);
}
SfrMethod::~SfrMethod()
{}