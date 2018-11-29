#pragma once
#define MTFOUTNAME "SFROUT.txt"
#define MAX_PROBLEMS 60
#define MAX_LINE_LENGTH 132
#define RIGHT 3
#define BOTTOM 2
#define MTFPRINT(a)                                                     \
{                                                                       \
        fprintf(stdout,a);                                              \
        fprintf(g_mtfout,a);                                            \
}
#include "HalconCpp.h"
#include"sfr-data-proces.h"
#include<io.h>
#include<fcntl.h>
#include<sfr.h>
using namespace HalconCpp;
static int too_many_problems;


typedef struct Grey_Reflectance_Pair
{
	double grey;
	double reflectance;
} grey_reflectance_pair;


class SfrMethod
{
public:
	SfrMethod();
	~SfrMethod();
	double FFC_Func(HTuple hv_HomMat2D, HTuple hv_offRow, HTuple hv_offCol, HTuple hv_hwidth, HTuple hv_hheight);
	double  RFC_Func(HTuple hv_HomMat2D, HTuple hv_offRow, HTuple hv_offCol, HTuple hv_hwidth, HTuple hv_hheight);
protected:
	void get_switches(char *image_filename, char *data_filename);
	void get_args(char *image_filename, char *data_filename, TIFF** tif);

	// 从ROI 4个角落各读取4个像素点， 用于判断刀口方向， 并确认ROI区域的合法性
	void input_area(TIFF *tif, unsigned char *rotation, int rstart, int rend, int cstart, int cend);
	
	// 读取ROI图像， 如果并将水平刀口转换为垂直刀口
	void read_in_image(TIFF *tif, unsigned char rotation, char *image_name, int *size_x, int *size_y);

	// 读取由line_num指定的行
	void read_scan_line(TIFF *tif, unsigned char *buf, short line_num);

	// 创建反射查找表， 将图像灰阶映射在0~1范围内
	// 之前指定了线性映射， 则直接将图像0到最大灰阶线性地映射在0~1
	// 否则读取oecf文件， 并采用线性插值地方式建立反射查找表
	double* read_in_ref_lut(char *data_filename, int *lowest_value, int *highest_value);

	int clipping(int low, int high, double thresh, unsigned char *img, int len);

	int read_pgm_header(char *image_filename);

	unsigned char* make_debug_image(TIFF *tif, unsigned char *buf, unsigned char rotation);

	short raw_readscanline(unsigned char *buf, short i);

	static int compare_grey_reflectance_pairs(const void *first, const void *second);

public:
	FILE *g_mtfout;
	char g_debug_file_name[80];
	char image_filename[80];
	char data_filename[80];
	int g_scan_image_file_id;
	int g_ofd;

	unsigned char *g_image_array;

	short g_input_column_start;
	short g_input_last_column;
	short g_input_row_start;
	short g_input_last_row;
	short g_input_width;
	short g_input_height;

	unsigned int g_total_image_width;
	unsigned int g_total_image_height;
	unsigned int g_bytes_per_pixel;
	unsigned int g_max_pixel_value;

	int g_test_pattern_xul;
	int g_test_pattern_yul;
	int g_test_pattern_xlr;
	int g_test_pattern_ylr;
	int g_target_res;

	double g_target_width_in_mm;
	double g_target_height_in_mm;

	double g_target_width;
	double g_target_height;

	char g_problems[MAX_PROBLEMS][MAX_LINE_LENGTH];
	short g_problem_count;
	char g_problem_type[MAX_PROBLEMS];
	short g_IQS_problem_count;

	unsigned int g_scan_rows;
	unsigned int g_scan_cols;
	unsigned int g_scan_header;
	unsigned short g_bps;
	unsigned short g_photometric;

	double g_ppi;

	int g_version;
	unsigned char g_center;
	unsigned char g_debug;
	unsigned char g_streamline_args;
	unsigned char g_reversepolarity;
	unsigned char g_extended;
	unsigned char g_pgm;
	unsigned char g_autorefine;
	unsigned char g_nocompare;

	int centerx = 0;
	int centery = 0;
	int width = 0;
	int height = 0;

	unsigned char *g_debug_array;
	unsigned char *g_start_ptr;
	int g_debug_fullwidth;
	int g_debug_fullheight;
	int g_userangle;
	float g_pt1x, g_pt1y, g_pt2x, g_pt2y;

	SfrDataProces sfr_data_proces;
	
};