
#include "camera-detection.h"
using namespace std;

//构造函数
CameraDetection::CameraDetection()
{
	camera_number = 0;
}

///注意如果筛选面积为空 时发生异常 catch 返回0 表示没有污点
void CameraDetection::Blemish(double& param)
{
	try
	{

		HObject  ho_Image, ho_GrayImage, ho_ROI_0, ho_ImageReduced;
		HObject  ho_Region, ho_ConnectedRegions, ho_SelectedRegions;

		// Local control variables
		HTuple  hv_Area, hv_Row, hv_Column, hv_Max;
	
		HalconCpp::ReadImage(&ho_Image, img_file.c_str());
		HalconCpp::Rgb1ToGray(ho_Image, &ho_GrayImage);

		GenRectangle1(&ho_ROI_0, 3, 3, 1200, 1600);
		ReduceDomain(ho_GrayImage, ho_ROI_0, &ho_ImageReduced);
		Threshold(ho_ImageReduced, &ho_Region, 0, 135);
		Connection(ho_Region, &ho_ConnectedRegions);
		SelectShape(ho_ConnectedRegions, &ho_SelectedRegions, "area", "and", 2, 9999999);
		AreaCenter(ho_SelectedRegions, &hv_Area, &hv_Row, &hv_Column);
		TupleMax(hv_Area, &hv_Max);

		param = hv_Max.D();
	}
	catch (HException &HDevDxpDefaultException)
	{
		param = 0;

	}
}

//RG检测  选取中心及图像四个边缘的点，判断RG色彩通道是否分布均匀
void CameraDetection::RG(double& param)
{
	try
	{

		// Local iconic variables
		HObject  ho_Image, ho_Rectangle, ho_Rectangle1;
		HObject  ho_Rectangle2, ho_Rectangle3, ho_Rectangle4, ho_Rectangle5;
		HObject  ho_Rectangle6, ho_Rectangle7, ho_Rectangle8, ho_ImageR;
		HObject  ho_ImageG, ho_ImageB, ho_ImageReducedR, ho_ImageReducedB;
		HObject  ho_ImageReducedUpCenter, ho_ImageReducedTopCenter1;
		HObject  ho_ImageReduced_Right_UP, ho_ImageReduced_Right_Up1;
		HObject  ho_ImageReduced_Right_Center, ho_ImageReduced_Right_Cener1;
		HObject  ho_ImageReduced_Center, ho_ImageReduced_Center1;
		HObject  ho_ImageReduced_Left_center, ho_ImageReduced_Left_center2;
		HObject  ho_ImageReducedLeftLow, ho_ImageReducedLeftLow2;
		HObject  ho_ImageReducedLowCenter, ho_ImageReducedLowCenter2;
		HObject  ho_ImageReduced, ho_ImageReduced1;

		// Local control variables
		HTuple  hv_Width, hv_Height, hv_Mean, hv_Deviation;
		HTuple  hv_Mean1, hv_Deviation1, hv_b_Left_up, hv_Mean2;
		HTuple  hv_Deviation2, hv_Mean3, hv_Deviation3, hv_b_Top_Center;
		HTuple  hv_Mean4, hv_Deviation4, hv_Mean5, hv_Deviation5;
		HTuple  hv_b_Top_Right, hv_Mean6, hv_Deviation6, hv_Mean7;
		HTuple  hv_Deviation7, hv_b_Center_Right, hv_Mean8, hv_Deviation8;
		HTuple  hv_Mean9, hv_Deviation9, hv_b_center_Center, hv_Mean10;
		HTuple  hv_Deviation10, hv_Mean11, hv_Deviation11, hv_b_Center_left;
		HTuple  hv_Mean12, hv_Deviation12, hv_Mean13, hv_Deviation13;
		HTuple  hv_b_Left_Low, hv_Mean14, hv_Deviation14, hv_Mean15;
		HTuple  hv_Deviation15, hv_b_low_Center, hv_Mean16, hv_Deviation16;
		HTuple  hv_Mean17, hv_Deviation17, hv_b_low_right, hv_tup;
		HTuple  hv_Min, hv_ratio;

		ReadImage(&ho_Image, img_file.c_str());
		GetImageSize(ho_Image, &hv_Width, &hv_Height);
		//**左上
		GenRectangle1(&ho_Rectangle, 10, 10, 80, 80);
		//***上中
		GenRectangle1(&ho_Rectangle1, 10, 780, 80, 850);

		//***右上
		GenRectangle1(&ho_Rectangle2, 10, 1520, 80, 1590);

		//**右中
		GenRectangle1(&ho_Rectangle3, 565, 1520, 635, 1590);
		//***中
		GenRectangle1(&ho_Rectangle4, 565, 780, 635, 850);
		//**中左
		GenRectangle1(&ho_Rectangle5, 565, 10, 635, 80);
		//***左下
		GenRectangle1(&ho_Rectangle6, 1120, 10, 1190, 80);
		//***下中
		GenRectangle1(&ho_Rectangle7, 1120, 780, 1190, 850);
		//**右下
		GenRectangle1(&ho_Rectangle8, 1120, 1520, 1190, 1590);

		//***通道分解
		HalconCpp::Decompose3(ho_Image, &ho_ImageR, &ho_ImageG, &ho_ImageB);
		//***左上
		HalconCpp::ReduceDomain(ho_ImageR, ho_Rectangle, &ho_ImageReducedR);
		HalconCpp::Intensity(ho_Rectangle, ho_ImageReducedR, &hv_Mean, &hv_Deviation);

		HalconCpp::ReduceDomain(ho_ImageG, ho_Rectangle, &ho_ImageReducedB);
		HalconCpp::Intensity(ho_Rectangle, ho_ImageReducedB, &hv_Mean1, &hv_Deviation1);

		hv_b_Left_up = hv_Mean / hv_Mean1;

		//**上中
		HalconCpp::ReduceDomain(ho_ImageR, ho_Rectangle1, &ho_ImageReducedUpCenter);
		HalconCpp::Intensity(ho_Rectangle1, ho_ImageReducedUpCenter, &hv_Mean2, &hv_Deviation2);

		HalconCpp::ReduceDomain(ho_ImageG, ho_Rectangle1, &ho_ImageReducedTopCenter1);
		HalconCpp::Intensity(ho_Rectangle1, ho_ImageReducedTopCenter1, &hv_Mean3, &hv_Deviation3);

		hv_b_Top_Center = hv_Mean2 / hv_Mean3;

		//**右上
		HalconCpp::ReduceDomain(ho_ImageR, ho_Rectangle2, &ho_ImageReduced_Right_UP);
		HalconCpp::Intensity(ho_Rectangle2, ho_ImageReduced_Right_UP, &hv_Mean4, &hv_Deviation4);

		HalconCpp::ReduceDomain(ho_ImageG, ho_Rectangle2, &ho_ImageReduced_Right_Up1);
		HalconCpp::Intensity(ho_Rectangle2, ho_ImageReduced_Right_Up1, &hv_Mean5, &hv_Deviation5);

		hv_b_Top_Right = hv_Mean4 / hv_Mean5;

		//**中右

		HalconCpp::ReduceDomain(ho_ImageR, ho_Rectangle3, &ho_ImageReduced_Right_Center);
		HalconCpp::Intensity(ho_Rectangle3, ho_ImageReduced_Right_Center, &hv_Mean6, &hv_Deviation6);

		HalconCpp::ReduceDomain(ho_ImageG, ho_Rectangle3, &ho_ImageReduced_Right_Cener1);
		HalconCpp::Intensity(ho_Rectangle3, ho_ImageReduced_Right_Cener1, &hv_Mean7, &hv_Deviation7);

		hv_b_Center_Right = hv_Mean6 / hv_Mean7;

		//***中中
		HalconCpp::ReduceDomain(ho_ImageR, ho_Rectangle4, &ho_ImageReduced_Center);
		Intensity(ho_Rectangle4, ho_ImageReduced_Center, &hv_Mean8, &hv_Deviation8);

		ReduceDomain(ho_ImageG, ho_Rectangle4, &ho_ImageReduced_Center1);
		Intensity(ho_Rectangle4, ho_ImageReduced_Center1, &hv_Mean9, &hv_Deviation9);

		hv_b_center_Center = hv_Mean8 / hv_Mean9;

		//***左中

		ReduceDomain(ho_ImageR, ho_Rectangle5, &ho_ImageReduced_Left_center);
		Intensity(ho_Rectangle5, ho_ImageReduced_Left_center, &hv_Mean10, &hv_Deviation10);

		ReduceDomain(ho_ImageG, ho_Rectangle5, &ho_ImageReduced_Left_center2);
		Intensity(ho_Rectangle5, ho_ImageReduced_Left_center2, &hv_Mean11, &hv_Deviation11);

		hv_b_Center_left = hv_Mean10 / hv_Mean11;
		//***z左下
		ReduceDomain(ho_ImageR, ho_Rectangle6, &ho_ImageReducedLeftLow);
		Intensity(ho_Rectangle6, ho_ImageReducedLeftLow, &hv_Mean12, &hv_Deviation12);

		ReduceDomain(ho_ImageG, ho_Rectangle6, &ho_ImageReducedLeftLow2);
		Intensity(ho_Rectangle6, ho_ImageReducedLeftLow2, &hv_Mean13, &hv_Deviation13);

		hv_b_Left_Low = hv_Mean12 / hv_Mean13;

		//***LowCenter
		ReduceDomain(ho_ImageR, ho_Rectangle7, &ho_ImageReducedLowCenter);
		Intensity(ho_Rectangle7, ho_ImageReducedLowCenter, &hv_Mean14, &hv_Deviation14);

		ReduceDomain(ho_ImageG, ho_Rectangle7, &ho_ImageReducedLowCenter2);
		Intensity(ho_Rectangle7, ho_ImageReducedLowCenter2, &hv_Mean15, &hv_Deviation15);

		hv_b_low_Center = hv_Mean14 / hv_Mean15;

		//**lowRight
		ReduceDomain(ho_ImageR, ho_Rectangle8, &ho_ImageReduced);
		Intensity(ho_Rectangle8, ho_ImageReduced, &hv_Mean16, &hv_Deviation16);

		ReduceDomain(ho_ImageG, ho_Rectangle8, &ho_ImageReduced1);
		Intensity(ho_Rectangle8, ho_ImageReduced1, &hv_Mean17, &hv_Deviation17);

		hv_b_low_right = hv_Mean16 / hv_Mean17;

		hv_tup.Clear();
		hv_tup.Append(hv_b_Left_up);
		hv_tup.Append(hv_b_Top_Center);
		hv_tup.Append(hv_b_Top_Right);
		hv_tup.Append(hv_b_Center_Right);
		hv_tup.Append(hv_b_Center_left);
		hv_tup.Append(hv_b_Left_Low);
		hv_tup.Append(hv_b_low_Center);
		hv_tup.Append(hv_b_low_right);

		TupleMin(hv_tup, &hv_Min);

		hv_ratio = hv_Min / hv_b_center_Center;

		hv_ratio = hv_Min / hv_b_center_Center;

		param = hv_ratio.D();
	}

	catch (HException&HDevDxpDefaultException)
	{
		param = -1.0;
	}
}

void CameraDetection::BG(double& param)
{
	try
	{

		// Local iconic variables
		HObject  ho_Image, ho_Rectangle, ho_Rectangle1;
		HObject  ho_Rectangle2, ho_Rectangle3, ho_Rectangle4, ho_Rectangle5;
		HObject  ho_Rectangle6, ho_Rectangle7, ho_Rectangle8, ho_ImageR;
		HObject  ho_ImageG, ho_ImageB, ho_ImageReducedR, ho_ImageReducedB;
		HObject  ho_ImageReducedUpCenter, ho_ImageReducedTopCenter1;
		HObject  ho_ImageReduced_Right_UP, ho_ImageReduced_Right_Up1;
		HObject  ho_ImageReduced_Right_Center, ho_ImageReduced_Right_Cener1;
		HObject  ho_ImageReduced_Center, ho_ImageReduced_Center1;
		HObject  ho_ImageReduced_Left_center, ho_ImageReduced_Left_center2;
		HObject  ho_ImageReducedLeftLow, ho_ImageReducedLeftLow2;
		HObject  ho_ImageReducedLowCenter, ho_ImageReducedLowCenter2;
		HObject  ho_ImageReduced, ho_ImageReduced1;

		// Local control variables
		HTuple  hv_Width, hv_Height, hv_Mean, hv_Deviation;
		HTuple  hv_Mean1, hv_Deviation1, hv_b_Left_up, hv_Mean2;
		HTuple  hv_Deviation2, hv_Mean3, hv_Deviation3, hv_b_Top_Center;
		HTuple  hv_Mean4, hv_Deviation4, hv_Mean5, hv_Deviation5;
		HTuple  hv_b_Top_Right, hv_Mean6, hv_Deviation6, hv_Mean7;
		HTuple  hv_Deviation7, hv_b_Center_Right, hv_Mean8, hv_Deviation8;
		HTuple  hv_Mean9, hv_Deviation9, hv_b_center_Center, hv_Mean10;
		HTuple  hv_Deviation10, hv_Mean11, hv_Deviation11, hv_b_Center_left;
		HTuple  hv_Mean12, hv_Deviation12, hv_Mean13, hv_Deviation13;
		HTuple  hv_b_Left_Low, hv_Mean14, hv_Deviation14, hv_Mean15;
		HTuple  hv_Deviation15, hv_b_low_Center, hv_Mean16, hv_Deviation16;
		HTuple  hv_Mean17, hv_Deviation17, hv_b_low_right, hv_tup;
		HTuple  hv_Min, hv_ratio;

		//前置

		ReadImage(&ho_Image, img_file.c_str());
		GetImageSize(ho_Image, &hv_Width, &hv_Height);

		//**左上
		GenRectangle1(&ho_Rectangle, 10, 10, 80, 80);
		//***上中
		GenRectangle1(&ho_Rectangle1, 10, 780, 80, 850);

		//***右上
		GenRectangle1(&ho_Rectangle2, 10, 1520, 80, 1590);

		//**右中
		GenRectangle1(&ho_Rectangle3, 565, 1520, 635, 1590);
		//***中
		GenRectangle1(&ho_Rectangle4, 565, 780, 635, 850);
		//**中左
		GenRectangle1(&ho_Rectangle5, 565, 10, 635, 80);
		//***左下
		GenRectangle1(&ho_Rectangle6, 1120, 10, 1190, 80);
		//***下中
		GenRectangle1(&ho_Rectangle7, 1120, 780, 1190, 850);
		//**右下
		GenRectangle1(&ho_Rectangle8, 1120, 1520, 1190, 1590);


		//***通道分解
		Decompose3(ho_Image, &ho_ImageR, &ho_ImageG, &ho_ImageB);
		//***左上
		ReduceDomain(ho_ImageR, ho_Rectangle, &ho_ImageReducedR);
		Intensity(ho_Rectangle, ho_ImageReducedR, &hv_Mean, &hv_Deviation);

		ReduceDomain(ho_ImageG, ho_Rectangle, &ho_ImageReducedB);
		Intensity(ho_Rectangle, ho_ImageReducedB, &hv_Mean1, &hv_Deviation1);

		hv_b_Left_up = hv_Mean / hv_Mean1;

		//**上中
		ReduceDomain(ho_ImageR, ho_Rectangle1, &ho_ImageReducedUpCenter);
		Intensity(ho_Rectangle1, ho_ImageReducedUpCenter, &hv_Mean2, &hv_Deviation2);

		ReduceDomain(ho_ImageG, ho_Rectangle1, &ho_ImageReducedTopCenter1);
		Intensity(ho_Rectangle1, ho_ImageReducedTopCenter1, &hv_Mean3, &hv_Deviation3);

		hv_b_Top_Center = hv_Mean2 / hv_Mean3;

		//**右上
		ReduceDomain(ho_ImageB, ho_Rectangle2, &ho_ImageReduced_Right_UP);
		Intensity(ho_Rectangle2, ho_ImageReduced_Right_UP, &hv_Mean4, &hv_Deviation4);

		ReduceDomain(ho_ImageG, ho_Rectangle2, &ho_ImageReduced_Right_Up1);
		Intensity(ho_Rectangle2, ho_ImageReduced_Right_Up1, &hv_Mean5, &hv_Deviation5);

		hv_b_Top_Right = hv_Mean4 / hv_Mean5;

		//**中右

		ReduceDomain(ho_ImageB, ho_Rectangle3, &ho_ImageReduced_Right_Center);
		Intensity(ho_Rectangle3, ho_ImageReduced_Right_Center, &hv_Mean6, &hv_Deviation6);

		ReduceDomain(ho_ImageG, ho_Rectangle3, &ho_ImageReduced_Right_Cener1);
		Intensity(ho_Rectangle3, ho_ImageReduced_Right_Cener1, &hv_Mean7, &hv_Deviation7);

		hv_b_Center_Right = hv_Mean6 / hv_Mean7;

		//***中中
		ReduceDomain(ho_ImageB, ho_Rectangle4, &ho_ImageReduced_Center);
		Intensity(ho_Rectangle4, ho_ImageReduced_Center, &hv_Mean8, &hv_Deviation8);

		ReduceDomain(ho_ImageG, ho_Rectangle4, &ho_ImageReduced_Center1);
		Intensity(ho_Rectangle4, ho_ImageReduced_Center1, &hv_Mean9, &hv_Deviation9);

		hv_b_center_Center = hv_Mean8 / hv_Mean9;

		//***左中

		ReduceDomain(ho_ImageB, ho_Rectangle5, &ho_ImageReduced_Left_center);
		Intensity(ho_Rectangle5, ho_ImageReduced_Left_center, &hv_Mean10, &hv_Deviation10);

		ReduceDomain(ho_ImageG, ho_Rectangle5, &ho_ImageReduced_Left_center2);
		Intensity(ho_Rectangle5, ho_ImageReduced_Left_center2, &hv_Mean11, &hv_Deviation11);

		hv_b_Center_left = hv_Mean10 / hv_Mean11;
		//***z左下
		ReduceDomain(ho_ImageB, ho_Rectangle6, &ho_ImageReducedLeftLow);
		Intensity(ho_Rectangle6, ho_ImageReducedLeftLow, &hv_Mean12, &hv_Deviation12);

		ReduceDomain(ho_ImageG, ho_Rectangle6, &ho_ImageReducedLeftLow2);
		Intensity(ho_Rectangle6, ho_ImageReducedLeftLow2, &hv_Mean13, &hv_Deviation13);

		hv_b_Left_Low = hv_Mean12 / hv_Mean13;

		//***LowCenter
		ReduceDomain(ho_ImageB, ho_Rectangle7, &ho_ImageReducedLowCenter);
		Intensity(ho_Rectangle7, ho_ImageReducedLowCenter, &hv_Mean14, &hv_Deviation14);

		ReduceDomain(ho_ImageG, ho_Rectangle7, &ho_ImageReducedLowCenter2);
		Intensity(ho_Rectangle7, ho_ImageReducedLowCenter2, &hv_Mean15, &hv_Deviation15);

		hv_b_low_Center = hv_Mean14 / hv_Mean15;

		//**lowRight
		ReduceDomain(ho_ImageB, ho_Rectangle8, &ho_ImageReduced);
		Intensity(ho_Rectangle8, ho_ImageReduced, &hv_Mean16, &hv_Deviation16);

		ReduceDomain(ho_ImageG, ho_Rectangle8, &ho_ImageReduced1);
		Intensity(ho_Rectangle8, ho_ImageReduced1, &hv_Mean17, &hv_Deviation17);

		hv_b_low_right = hv_Mean16 / hv_Mean17;

		hv_tup.Clear();
		hv_tup.Append(hv_b_Left_up);
		hv_tup.Append(hv_b_Top_Center);
		hv_tup.Append(hv_b_Top_Right);
		hv_tup.Append(hv_b_Center_Right);
		hv_tup.Append(hv_b_Center_left);
		hv_tup.Append(hv_b_Left_Low);
		hv_tup.Append(hv_b_low_Center);
		hv_tup.Append(hv_b_low_right);

		TupleMin(hv_tup, &hv_Min);

		hv_ratio = hv_Min / hv_b_center_Center;

		param = hv_ratio.D();
	}

	catch (HException&HDevDxpDefaultException)
	{
		param = -1;
	}
}

//实点检测
void CameraDetection::DeadPixel(double& param)
{
	try
	{
		HObject  ho_Image, ho_GrayImage, ho_ROI_0, ho_ImageReduced;
		HObject  ho_Region, ho_ConnectedRegions, ho_SelectedRegions;

		// Local control variables
		HTuple  hv_Area, hv_Row, hv_Column, hv_Max, hv_Number;

		ReadImage(&ho_Image, img_file.c_str());
		Rgb1ToGray(ho_Image, &ho_GrayImage);

		GenRectangle1(&ho_ROI_0, 3, 3, 1200, 1600);
		ReduceDomain(ho_GrayImage, ho_ROI_0, &ho_ImageReduced);
		Threshold(ho_ImageReduced, &ho_Region, 0, 135);
		Connection(ho_Region, &ho_ConnectedRegions);
		SelectShape(ho_ConnectedRegions, &ho_SelectedRegions, "area", "and", 2, 5);

		AreaCenter(ho_SelectedRegions, &hv_Area, &hv_Row, &hv_Column);
		TupleMax(hv_Area, &hv_Max);

		CountObj(ho_SelectedRegions, &hv_Number);
		param = hv_Max.D();

	}
	catch (HException &HDevDxpDefaultException)
	{
		param = 0;
	}
}

//获取灰度值
void CameraDetection::RI(double& param)
{
	try
	{
		// Local iconic variables
		HObject  ho_Image, ho_GrayImage, ho_Rectangle1;
		HObject  ho_Rectangle2, ho_Rectangle3, ho_Rectangle4, ho_RectangleCenter;
		HObject  ho_ImageReducedCenter, ho_ImageReduced1, ho_ImageReduced2;
		HObject  ho_ImageReduced3, ho_ImageReduced4;

		// Local control variables
		HTuple  hv_WindowHandle, hv_Width, hv_Height;
		HTuple  hv_MeanCenter, hv_DeviationCenter, hv_Mean1, hv_Deviation1;
		HTuple  hv_Mean2, hv_Deviation2, hv_Mean3, hv_Deviation3;
		HTuple  hv_Mean4, hv_Deviation4, hv_ratio_up_Left, hv_ratio_up_Right;
		HTuple  hv_ratio_LRight, hv_ratio_LLeft, hv_ratio, hv_Min;
		
		ReadImage(&ho_Image, img_file.c_str());
		GetImageSize(ho_Image, &hv_Width, &hv_Height);
		Rgb1ToGray(ho_Image, &ho_GrayImage);
		
		//****获取左上角第一个点灰度值
		GenRectangle1(&ho_Rectangle1, 10, 10, 250, 330);
		//**右上角
		GenRectangle1(&ho_Rectangle2, 10, 1270, 250, 1590);
		//****获取右下
		GenRectangle1(&ho_Rectangle3, 950, 1270, 1190, 1590);
		//****获取左下
		GenRectangle1(&ho_Rectangle4, 950, 10, 1190, 330);
		//****获取中间
		GenRectangle1(&ho_RectangleCenter, 480, 640, 720, 960);

		//***中间平均灰度
		HalconCpp::ReduceDomain(ho_GrayImage, ho_RectangleCenter, &ho_ImageReducedCenter);
		HalconCpp::Intensity(ho_RectangleCenter, ho_ImageReducedCenter, &hv_MeanCenter, &hv_DeviationCenter);

		HalconCpp::ReduceDomain(ho_GrayImage, ho_Rectangle1, &ho_ImageReduced1);
		HalconCpp::Intensity(ho_Rectangle1, ho_ImageReduced1, &hv_Mean1, &hv_Deviation1);

		HalconCpp::ReduceDomain(ho_GrayImage, ho_Rectangle2, &ho_ImageReduced2);
		HalconCpp::Intensity(ho_Rectangle2, ho_ImageReduced2, &hv_Mean2, &hv_Deviation2);

		HalconCpp::ReduceDomain(ho_GrayImage, ho_Rectangle3, &ho_ImageReduced3);
		HalconCpp::Intensity(ho_Rectangle3, ho_ImageReduced3, &hv_Mean3, &hv_Deviation3);

		HalconCpp::ReduceDomain(ho_GrayImage, ho_Rectangle4, &ho_ImageReduced4);
		HalconCpp::Intensity(ho_Rectangle4, ho_ImageReduced4, &hv_Mean4, &hv_Deviation4);


		hv_ratio_up_Left = hv_Mean1 / hv_MeanCenter;
		hv_ratio_up_Right = hv_Mean2 / hv_MeanCenter;
		hv_ratio_LRight = hv_Mean3 / hv_MeanCenter;
		hv_ratio_LLeft = hv_Mean4 / hv_MeanCenter;

		hv_ratio.Clear();
		hv_ratio.Append(hv_ratio_up_Left);
		hv_ratio.Append(hv_ratio_up_Right);
		hv_ratio.Append(hv_ratio_LRight);
		hv_ratio.Append(hv_ratio_LLeft);

		HalconCpp::TupleMin(hv_ratio, &hv_Min);
		param = hv_Min.D();

	}
	catch (HException&HDevDxpDefaultException)
	{
		param = -1;
		//AfxMessageBox(HDevDxpDefaultException.ErrorMessage());
	}

}

//旋转偏移量检测
void CameraDetection::Rotation(double& param)
{
	try
	{

		HObject  ho_Image, ho_GrayImage, ho_ROI_0, ho_ImageReduced;
		HObject  ho_Edges, ho_ContoursSplit, ho_UnionContours, ho_SelectedContours1;
		HObject  ho_SelectedContours2, ho_Cross1, ho_Cross2;

		// Local control variables
		HTuple  hv_Row1, hv_Column1, hv_Row2, hv_Column2;
		HTuple  hv_Area, hv_Row3, hv_Column3, hv_PointOrder, hv_Row4;
		HTuple  hv_Column4, hv_Angle, hv_ang, hv_Abs;


		//建立模板坐标（557.349,343.984）（557.349,1230）
		hv_Row1 = 557.349;
		hv_Column1 = 343.984;

		hv_Row2 = 557.349;
		hv_Column2 = 1230;

		ReadImage(&ho_Image, img_file.c_str());
		Rgb1ToGray(ho_Image, &ho_GrayImage);

		//左圆
		GenRectangle1(&ho_ROI_0, 452.105, 94.3905, 895.778, 538.186);
		ReduceDomain(ho_GrayImage, ho_ROI_0, &ho_ImageReduced);
		EdgesSubPix(ho_ImageReduced, &ho_Edges, "canny", 1, 20, 40);
		SegmentContoursXld(ho_Edges, &ho_ContoursSplit, "lines_circles", 5, 4, 2);
		UnionCocircularContoursXld(ho_ContoursSplit, &ho_UnionContours, 0.5, 0.1, 0.2,
			30, 10, 10, "true", 1);
		SelectContoursXld(ho_UnionContours, &ho_SelectedContours1, "contour_length", 170,
			250, -0.5, 0.5);
		AreaCenterXld(ho_SelectedContours1, &hv_Area, &hv_Row3, &hv_Column3, &hv_PointOrder);

		//右圆
		GenRectangle1(&ho_ROI_0, 466.994, 958.624, 910.666, 1402.42);
		ReduceDomain(ho_GrayImage, ho_ROI_0, &ho_ImageReduced);
		EdgesSubPix(ho_ImageReduced, &ho_Edges, "canny", 1, 20, 40);
		SegmentContoursXld(ho_Edges, &ho_ContoursSplit, "lines_circles", 5, 4, 2);
		UnionCocircularContoursXld(ho_ContoursSplit, &ho_UnionContours, 0.5, 0.1, 0.2,
			30, 10, 10, "true", 1);
		SelectContoursXld(ho_UnionContours, &ho_SelectedContours2, "contour_length", 170,
			250, -0.5, 0.5);
		AreaCenterXld(ho_SelectedContours2, &hv_Area, &hv_Row4, &hv_Column4, &hv_PointOrder);

		AngleLl(hv_Row1, hv_Column1, hv_Row2, hv_Column2, hv_Row3, hv_Column3, hv_Row4,
			hv_Column4, &hv_Angle);

		hv_ang = (hv_Angle.TupleDeg());

		if (0 != (hv_ang>90))
		{
			hv_ang = -(180 - hv_ang);
		}

		else if (0 != (hv_ang<-90))
		{
			hv_ang = -(-180 - hv_ang);
		}

		TupleAbs(hv_ang, &hv_Abs);
		param = hv_Abs.D();

	}
	catch (HException &HDevDxpDefaultException)
	{
		param = -1;
	}
}
//视场角检测
void CameraDetection::FOV(double& param)
{
	try
	{
		// Local iconic variables
		HObject  ho_Image, ho_GrayImage, ho_ROI_0, ho_Region;
		HObject  ho_Edges, ho_ContoursSplit, ho_SelectedContours;
		HObject  ho_SortedContours, ho_ObjectSelected, ho_UnionContours;

		// Local control variables
		HTuple  hv_Row, hv_Column, hv_Radius1, hv_StartPhi;
		HTuple  hv_EndPhi, hv_PointOrder, hv_D1, hv_Pi, hv_Distance;
		HTuple  hv_Length, hv_hight, hv_ATan, hv_ang;

		ReadImage(&ho_Image, img_file.c_str());
		Rgb1ToGray(ho_Image, &ho_GrayImage);
		GenRectangle1(&ho_ROI_0, 139.885, 408.111, 882.192, 1159.58);
		ReduceDomain(ho_GrayImage, ho_ROI_0, &ho_Region);
		EdgesSubPix(ho_Region, &ho_Edges, "canny", 1, 20, 40);
		SegmentContoursXld(ho_Edges, &ho_ContoursSplit, "lines_circles", 5, 4, 2);
		//UnionCocircularContoursXld(ho_ContoursSplit, &ho_UnionContours, 0.5, 0.1, 0.2, 30, 10, 10, 'true', 1);
		SelectContoursXld(ho_ContoursSplit, &ho_SelectedContours, "contour_length", 205, 305, -0.5, 0.5);
		SortContoursXld(ho_SelectedContours, &ho_SortedContours, "character", "true", "row");

		//大圆直径15mm
		SelectObj(ho_SortedContours, &ho_ObjectSelected, 1);
		FitCircleContourXld(ho_ObjectSelected, "algebraic", -1, 0, 0, 3, 2, &hv_Row, &hv_Column,
			&hv_Radius1, &hv_StartPhi, &hv_EndPhi, &hv_PointOrder);

		hv_D1 = hv_Radius1 * 2;
		hv_Pi = 15 / hv_D1;

		DistancePp(0, 0, 1200, 1600, &hv_Distance);
		hv_Length = (hv_Distance / 2)*hv_Pi;
		hv_hight = 350;

		TupleAtan(hv_Length / hv_hight, &hv_ATan);
		hv_ang = (hv_ATan.TupleDeg()) * 2;
		param = hv_ang.D();
	}
	catch (HException &HDevDxpDefaultException)
	{
		param = -1;
	}
}
//水平偏移角度计算
void CameraDetection::Tilt(double& param)
{
	try
	{
		// Local iconic variables
		HObject  ho_Image, ho_GrayImage, ho_ImageReduced;

		HObject  ho_ROI_0, ho_Region;
		HObject  ho_Edges, ho_ContoursSplit, ho_SelectedContours;
		HObject  ho_SortedContours, ho_ObjectSelected, ho_UnionContours;

		// Local control variables
		HTuple  hv_WindowHandle, hv_WD, hv_Ratio, hv_Width;
		HTuple  hv_Height, hv_ModelID, hv_Row, hv_Column, hv_Angle;
		HTuple  hv_Score, hv_ImageCenterRow, hv_ImageCenterCol;
		HTuple  hv_D1, hv_L, hv_ATan1, hv_AD1, hv_Abs;

		HTuple  hv_Row11, hv_Column11, hv_Radius11, hv_StartPhi11;
		HTuple  hv_EndPhi11, hv_PointOrder11, hv_D11;

		//***物距
		hv_WD = 350;

		//**物象比
		//hv_Ratio = 0.209;

		//**物象比-------------------------------------------------------------------------

		ReadImage(&ho_Image, img_file.c_str());
		GetImageSize(ho_Image, &hv_Width, &hv_Height);
		Rgb1ToGray(ho_Image, &ho_GrayImage);
		GenRectangle1(&ho_ROI_0, 139.885, 408.111, 882.192, 1159.58);
		ReduceDomain(ho_GrayImage, ho_ROI_0, &ho_Region);
		EdgesSubPix(ho_Region, &ho_Edges, "canny", 1, 20, 40);
		SegmentContoursXld(ho_Edges, &ho_ContoursSplit, "lines_circles", 5, 4, 2);
		//UnionCocircularContoursXld(ho_ContoursSplit, &ho_UnionContours, 0.5, 0.1, 0.2, 30, 10, 10, 'true', 1);
		SelectContoursXld(ho_ContoursSplit, &ho_SelectedContours, "contour_length", 205, 305, -0.5, 0.5);
		SortContoursXld(ho_SelectedContours, &ho_SortedContours, "character", "true", "row");

		//大圆直径15mm
		SelectObj(ho_SortedContours, &ho_ObjectSelected, 1);
		FitCircleContourXld(ho_ObjectSelected, "algebraic", -1, 0, 0, 3, 2, &hv_Row11, &hv_Column11,
			&hv_Radius11, &hv_StartPhi11, &hv_EndPhi11, &hv_PointOrder11);

		hv_D11 = hv_Radius11 * 2;
		hv_Ratio = 15 / hv_D11;

		//-----------------------------------------------------------------------------------

		if (g_IsFFCInited == false && camera_number == 0)
		{
			ReadShapeModel("D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\ffc.shm", &g_ffc_hv_ModelID);
			ReadRegion(&g_ffc_ho_Region, "D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\ffcRegion.reg");
			g_IsFFCInited = true;
		}

		if (g_IsRFCInited == false && camera_number == 1)
		{
			ReadShapeModel("D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\rfc.shm", &g_rfc_hv_ModelID);
			ReadRegion(&g_rfc_ho_Region, "D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\rfcRegion.reg");
			g_IsRFCInited = true;
		}
		if (camera_number == 0)
		{
			ReadImage(&ho_Image, img_file.c_str());
			GetImageSize(ho_Image, &hv_Width, &hv_Height);
			Rgb1ToGray(ho_Image, &ho_GrayImage);
			ReduceDomain(ho_GrayImage, g_ffc_ho_Region, &ho_ImageReduced);
			FindShapeModel(ho_ImageReduced, g_ffc_hv_ModelID, HTuple(-20).TupleRad(), HTuple(40).TupleRad(), 0.5, 1, 0.5, "least_squares", 0, 0.9, &hv_Row, &hv_Column, &hv_Angle, &hv_Score);
		}
		if (camera_number == 1)
		{
			ReadImage(&ho_Image, img_file.c_str());
			GetImageSize(ho_Image, &hv_Width, &hv_Height);
			Rgb1ToGray(ho_Image, &ho_GrayImage);
			ReduceDomain(ho_GrayImage, g_rfc_ho_Region, &ho_ImageReduced);
			FindShapeModel(ho_ImageReduced, g_rfc_hv_ModelID, HTuple(-20).TupleRad(), HTuple(40).TupleRad(), 0.5, 1, 0.5, "least_squares", 0, 0.9, &hv_Row, &hv_Column, &hv_Angle, &hv_Score);
		}
		hv_ImageCenterRow = hv_Height / 2;
		hv_ImageCenterCol = hv_Width / 2;
		DistancePp(hv_ImageCenterRow, hv_ImageCenterCol, hv_Row, hv_Column, &hv_D1);
		hv_L = hv_D1*hv_Ratio;
		TupleAtan(hv_L / hv_WD, &hv_ATan1);
		hv_AD1 = hv_ATan1.TupleDeg();
		TupleAbs(hv_AD1, &hv_Abs);

		param = hv_Abs.D();
	}
	catch (HException &HDevDxpDefaultException)
	{
		param = -1;
	}
}

void CameraDetection::SFR(double& param)
{
	centerx = 0; centery = 0; width = 0; height = 0;

	// Local iconic variables
	HObject  ho_Image, ho_GrayImage, ho_img_ffc;
	HObject  ho_Rectangle, ho_ImageReduced, ho_Edges, ho_SelectedContours;
	HObject  ho_ObjectsConcat, ho_Region, ho_ImgPro, ho_ModelContours;
	HObject  ho_ContoursAffineTrans, ho_Rectangle1, ho_Rectangle2, ho_Rectangle3, ho_reduced, ho_ffc_img, ho_rfc_img, ho_searchRegion;

	// Local control variables
	HTuple  hv_WindowHandle, hv_offRow;
	HTuple  hv_offCol, hv_hwidth, hv_hheight, hv_Files, hv_i;
	HTuple  hv_Row, hv_Column, hv_Angle, hv_ScaleR, hv_ScaleC;
	HTuple  hv_Score, hv_HomMat2D, hv_ang, hv_RowTrans, hv_ColTrans;
	HTuple  hv_ULRow, hv_ULCol, hv_weidth, hv_height;
	HTuple  hv_ULRow2, hv_ULCol2, hv_weidth2, hv_height2;
	HTuple  hv_ULRow3, hv_ULCol3, hv_weidth3, hv_height3;

	HTuple  hv_offRow2, hv_offCol2, hv_hwidth2, hv_hheight2;
	HTuple  hv_offRow3, hv_offCol3, hv_hwidth3, hv_hheight3;
	HTuple  hv_RowTrans2, hv_ColTrans2;
	HTuple  hv_RowTrans3, hv_ColTrans3;
	HTuple  hv_offRow4, hv_offCol4, hv_hwidth4, hv_hheight4;

	//矩形跟踪
	HTuple  hv_onRow, hv_onCol, hv_PointStart_x, hv_PointStart_y, hv_PointEnd_x, hv_PointEnd_y;
	HTuple  hv_Cos, hv_Sin, hv_CircleCenter_x, hv_CircleCenter_y;
	HObject ho_ImageMean;

	if (camera_number == 0)
	{
		try
		{
			if (g_IsFFCInited == false)
			{
				ReadShapeModel("D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\ffc.shm", &g_ffc_hv_ModelID);
				g_IsFFCInited = true;
			}
			ReadImage(&ho_Image, img_file.c_str());
			Rgb1ToGray(ho_Image, &ho_GrayImage);
			//MeanImage(ho_GrayImage, &ho_ImageMean, 1, 1);
			WriteImage(ho_GrayImage, "tiff", 0, "D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\ffc.tiff");
			ReadImage(&ho_ffc_img, "D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\ffc.tiff");

			ReadRegion(&ho_searchRegion, "D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\ffcRegion.reg");
			GetShapeModelContours(&ho_ModelContours, g_ffc_hv_ModelID, 1);
			ReduceDomain(ho_ffc_img, ho_searchRegion, &ho_reduced);
			FindShapeModel(ho_reduced, g_ffc_hv_ModelID, -(HTuple(30).TupleRad()), HTuple(60).TupleRad(), 0.8, 1, 0.5, "least_squares", 0, 0.9, &hv_Row, &hv_Column, &hv_Angle, &hv_Score);


			//================================================================================
			hv_PointStart_x = HTuple();
			hv_PointStart_y = HTuple();
			hv_PointEnd_x = HTuple();
			hv_PointEnd_y = HTuple();
			hv_onRow = HTuple();
			hv_onCol = HTuple();

			hv_onRow[1] = -135;
			hv_onCol[1] = -70;

			hv_onRow[2] = -135;
			hv_onCol[2] = 213;

			hv_onRow[3] = 155;
			hv_onCol[3] = -70;

			hv_onRow[4] = 155;
			hv_onCol[4] = 213;

			hv_hwidth = 35;
			hv_hheight = 45;
			//hv_hwidth  = 28;
			//hv_hheight = 35;


			TupleCos(hv_Angle, &hv_Cos);
			TupleSin(hv_Angle, &hv_Sin);

			hv_CircleCenter_x = hv_Column;
			hv_CircleCenter_y = hv_Row;

			for (hv_i = 1; hv_i <= 4; hv_i += 1)
			{

				hv_PointStart_x[hv_i] = hv_Column + HTuple(hv_onCol[hv_i]);
				hv_PointStart_y[hv_i] = hv_Row + HTuple(hv_onRow[hv_i]);
				hv_PointEnd_x[hv_i] = (((HTuple(hv_PointStart_x[hv_i]) - hv_CircleCenter_x)*hv_Cos) - ((HTuple(hv_PointStart_y[hv_i]) - hv_CircleCenter_y)*hv_Sin)) + hv_CircleCenter_x;
				hv_PointEnd_y[hv_i] = (((HTuple(hv_PointStart_y[hv_i]) - hv_CircleCenter_y)*hv_Cos) + ((HTuple(hv_PointStart_x[hv_i]) - hv_CircleCenter_x)*hv_Sin)) + hv_CircleCenter_y;

			}

			hv_offRow = HTuple(hv_PointEnd_y[1]) - hv_Row;
			hv_offCol = HTuple(hv_PointEnd_x[1]) - hv_Column;

			hv_offRow2 = HTuple(hv_PointEnd_y[2]) - hv_Row;
			hv_offCol2 = HTuple(hv_PointEnd_x[2]) - hv_Column;

			hv_offRow3 = HTuple(hv_PointEnd_y[3]) - hv_Row;
			hv_offCol3 = HTuple(hv_PointEnd_x[3]) - hv_Column;

			hv_offRow4 = HTuple(hv_PointEnd_y[4]) - hv_Row;
			hv_offCol4 = HTuple(hv_PointEnd_x[4]) - hv_Column;

			//===========================================================================

			if (0 != ((hv_Score.TupleLength()) == 1))
			{

				VectorAngleToRigid(0, 0, 0, hv_Row, hv_Column, hv_Angle, &hv_HomMat2D);

				double sfr1 = sfr_method.FFC_Func(hv_HomMat2D, hv_offRow, hv_offCol, hv_hwidth, hv_hheight);
				double sfr2 = sfr_method.FFC_Func(hv_HomMat2D, hv_offRow2, hv_offCol2, hv_hwidth, hv_hheight);
				double sfr3 = sfr_method.FFC_Func(hv_HomMat2D, hv_offRow3, hv_offCol3, hv_hwidth, hv_hheight);
				double sfr4 = sfr_method.FFC_Func(hv_HomMat2D, hv_offRow4, hv_offCol4, hv_hwidth, hv_hheight);


				double sfr = (sfr1 + sfr2 + sfr3 + sfr4) / 4;

				param = sfr;
			}
			else
			{
				param = -1;
			}

		}

		catch (HException &HDevDxpDefaultException)
		{
			param = -1;
		}

	}

	if (camera_number == 1)
	{

		//矩形跟踪
		HTuple  hv_onRow, hv_onCol, hv_PointStart_x, hv_PointStart_y, hv_PointEnd_x, hv_PointEnd_y;
		HTuple  hv_Cos, hv_Sin, hv_CircleCenter_x, hv_CircleCenter_y;
		try
		{
			if (g_IsRFCInited == false)
			{
				ReadShapeModel("D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\rfc.shm", &g_rfc_hv_ModelID);
				g_IsRFCInited = true;
			}

			ReadImage(&ho_Image, img_file.c_str());
			Rgb1ToGray(ho_Image, &ho_GrayImage);
			WriteImage(ho_GrayImage, "tiff", 0, "D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\rfc.tiff");
			ReadImage(&ho_rfc_img, "D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\rfc.tiff");
			ReadRegion(&ho_searchRegion, "D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\rfcRegion.reg");

			ReduceDomain(ho_rfc_img, ho_searchRegion, &ho_reduced);
			FindShapeModel(ho_reduced, g_rfc_hv_ModelID, -(HTuple(20).TupleRad()), HTuple(40).TupleRad(), 0.7, 1, 0.5, "least_squares", 0, 0.9, &hv_Row, &hv_Column, &hv_Angle, &hv_Score);


			//================================================================================
			hv_PointStart_x = HTuple();
			hv_PointStart_y = HTuple();
			hv_PointEnd_x = HTuple();
			hv_PointEnd_y = HTuple();
			hv_onRow = HTuple();
			hv_onCol = HTuple();

			hv_onRow[1] = -114;
			hv_onCol[1] = -55;

			hv_onRow[2] = -112;
			hv_onCol[2] = 165;

			hv_onRow[3] = 110;
			hv_onCol[3] = -55;

			hv_onRow[4] = 108;
			hv_onCol[4] = 165;

			hv_hwidth = 28;
			hv_hheight = 35;


			TupleCos(hv_Angle, &hv_Cos);
			TupleSin(hv_Angle, &hv_Sin);

			hv_CircleCenter_x = hv_Column;
			hv_CircleCenter_y = hv_Row;

			for (hv_i = 1; hv_i <= 4; hv_i += 1)
			{

				hv_PointStart_x[hv_i] = hv_Column + HTuple(hv_onCol[hv_i]);
				hv_PointStart_y[hv_i] = hv_Row + HTuple(hv_onRow[hv_i]);
				hv_PointEnd_x[hv_i] = (((HTuple(hv_PointStart_x[hv_i]) - hv_CircleCenter_x)*hv_Cos) - ((HTuple(hv_PointStart_y[hv_i]) - hv_CircleCenter_y)*hv_Sin)) + hv_CircleCenter_x;
				hv_PointEnd_y[hv_i] = (((HTuple(hv_PointStart_y[hv_i]) - hv_CircleCenter_y)*hv_Cos) + ((HTuple(hv_PointStart_x[hv_i]) - hv_CircleCenter_x)*hv_Sin)) + hv_CircleCenter_y;

			}

			hv_offRow = HTuple(hv_PointEnd_y[1]) - hv_Row;
			hv_offCol = HTuple(hv_PointEnd_x[1]) - hv_Column;

			hv_offRow2 = HTuple(hv_PointEnd_y[2]) - hv_Row;
			hv_offCol2 = HTuple(hv_PointEnd_x[2]) - hv_Column;

			hv_offRow3 = HTuple(hv_PointEnd_y[3]) - hv_Row;
			hv_offCol3 = HTuple(hv_PointEnd_x[3]) - hv_Column;

			hv_offRow4 = HTuple(hv_PointEnd_y[4]) - hv_Row;
			hv_offCol4 = HTuple(hv_PointEnd_x[4]) - hv_Column;

			//===========================================================================



			if (0 != ((hv_Score.TupleLength()) == 1))
			{

				VectorAngleToRigid(0, 0, 0, hv_Row, hv_Column, hv_Angle, &hv_HomMat2D);

				double sfr1 = sfr_method.RFC_Func(hv_HomMat2D, hv_offRow, hv_offCol, hv_hwidth, hv_hheight);
				double sfr2 = sfr_method.RFC_Func(hv_HomMat2D, hv_offRow2, hv_offCol2, hv_hwidth, hv_hheight);
				double sfr3 = sfr_method.RFC_Func(hv_HomMat2D, hv_offRow3, hv_offCol3, hv_hwidth, hv_hheight);
				double sfr4 = sfr_method.RFC_Func(hv_HomMat2D, hv_offRow4, hv_offCol4, hv_hwidth, hv_hheight);
				double sfr = (sfr1 + sfr2 + sfr3 + sfr4) / 4;
				param = sfr;

			}
			else
			{
				param = 0;
			}

		}

		catch (HException &HDevDxpDefaultException)
		{
			param = 0;
		}
		//try
		//{

		//	ReadShapeModel("D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\rfc.shm", &hv_ModelID);
		//	ReadImage(&ho_Image, img_file.c_str());
		//	Rgb1ToGray(ho_Image, &ho_GrayImage);
		//	WriteImage(ho_GrayImage, "tiff", 0, "D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\rfc.tiff");
		//	ReadImage(&ho_rfc_img, "D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\rfc.tiff");
		//	ReadRegion(&ho_searchRegion, "D:\\work\\work_data\\HuaBeiCamera\\Kazam_Inin\\rfcRegion.reg");
		//	GetShapeModelContours(&ho_ModelContours, hv_ModelID, 1);


		//	////1
		//	hv_offRow = -113;
		//	hv_offCol = -50;
		//	hv_hwidth = 28;//矩形半宽度
		//	hv_hheight = 35;//矩形半高度


		//	///2白黑
		//	/*hv_offRow2 = -105;
		//	hv_offCol2 =55;
		//	hv_hwidth2 = 28;
		//	hv_hheight2 = 35;*/

		//	//黑白
		//	hv_offRow2 = -110;
		//	hv_offCol2 = 160;
		//	hv_hwidth2 = 28;
		//	hv_hheight2 = 35;


		//	///3
		//	/*hv_offRow3 = 105;
		//	hv_offCol3 = -55;
		//	hv_hwidth3 = 28;
		//	hv_hheight3 = 35;



		//	///4
		//	hv_offRow4 = 105;
		//	hv_offCol4 =55;
		//	hv_hwidth4 = 28;
		//	hv_hheight4 = 35;*/

		//	hv_offRow3 = -5;
		//	hv_offCol3 = -165;
		//	hv_hwidth3 = 28;
		//	hv_hheight3 = 35;



		//	///4
		//	/*hv_offRow4 = -5;
		//	hv_offCol4 = 165;
		//	hv_hwidth4 = 28;
		//	hv_hheight4 = 35;*/
		//	hv_offRow4 = 5;
		//	hv_offCol4 = 275;
		//	hv_hwidth4 = 28;
		//	hv_hheight4 = 35;



		//	ReduceDomain(ho_rfc_img, ho_searchRegion, &ho_reduced);

		//	FindShapeModel(ho_reduced, hv_ModelID, -(HTuple(20).TupleRad()), HTuple(40).TupleRad(), 0.7, 1, 0.5, "least_squares", 0, 0.9, &hv_Row, &hv_Column, &hv_Angle, &hv_Score);

		//	if (0 != ((hv_Score.TupleLength()) == 1))
		//	{
		//		VectorAngleToRigid(0, 0, 0, hv_Row, hv_Column, hv_Angle, &hv_HomMat2D);
		//		double sfr1 = sfr_method.RFC_Func(hv_HomMat2D, hv_offRow, hv_offCol, hv_hwidth, hv_hheight);
		//		double sfr2 = sfr_method.RFC_Func(hv_HomMat2D, hv_offRow2, hv_offCol2, hv_hwidth2, hv_hheight2);
		//		double sfr3 = sfr_method.RFC_Func(hv_HomMat2D, hv_offRow3, hv_offCol3, hv_hwidth3, hv_hheight3);
		//		double sfr4 = sfr_method.RFC_Func(hv_HomMat2D, hv_offRow4, hv_offCol4, hv_hwidth4, hv_hheight4);
		//		double sfr = (sfr1 + sfr2 + sfr3 + sfr4) / 4;
		//		param = sfr;

		//	}
		//	else
		//	{
		//		param = 0;
		//	}

		//}

		//catch (HException &HDevDxpDefaultException)
		//{
		//	param = 0;
		//}
	}

}

//#pragma region MovePoint
//
//void ImgPro::FFC_Move(pStruct &p)
//{
//
//	HObject  ho_Image, ho_GrayImage, ho_img_ffc, ho_Rectangle1;
//	HObject  ho_Rectangle, ho_ImageReduced, ho_Edges, ho_SelectedContours;
//	HObject  ho_ObjectsConcat, ho_Region, ho_ImgPro, ho_ModelContours;
//	HObject  ho_ContoursAffineTrans, ho_Rectangle3, ho_reduced, ho_ffc_img, ho_searchRegion;
//
//	// Local control variables
//	HTuple  hv_WindowHandle, hv_ModelID, hv_offRow;
//	HTuple  hv_offCol, hv_hwidth, hv_hheight, hv_Files, hv_i;
//	HTuple  hv_Row, hv_Column, hv_Angle, hv_ScaleR, hv_ScaleC;
//	HTuple  hv_Score, hv_HomMat2D, hv_ang, hv_RowTrans, hv_ColTrans;
//	HTuple  hv_ULRow, hv_ULCol, hv_weidth, hv_height, hv_Width, hv_Height;
//
//
//
//	try
//	{
//		///图像基准
//		double XCenter = 0.0;
//		double YCenter = 0.0;
//
//		ReadShapeModel("D:\\Kazam\\ffcaniso.shm", &hv_ModelID);
//		ReadImage(&ho_Image, "D:\\Kazam\\camera_image_ffc.jpeg");
//		Rgb1ToGray(ho_Image, &ho_GrayImage);
//		GetImageSize(ho_GrayImage, &hv_Width, &hv_Height);
//
//		XCenter = hv_Width.D() / 2.0;
//		YCenter = hv_Height.D() / 2.0;
//
//		WriteImage(ho_GrayImage, "tiff", 0, "D:\\Kazam\\ffc.tiff");
//		ReadImage(&ho_ffc_img, "D:\\Kazam\\ffc.tiff");
//		ReadRegion(&ho_searchRegion, "D:\\Kazam\\ffcRegion.reg");
//		ReduceDomain(ho_ffc_img, ho_searchRegion, &ho_reduced);
//		FindAnisoShapeModel(ho_reduced, hv_ModelID, -(HTuple(30).TupleRad()), HTuple(60).TupleRad(), 0.8, 1.1, 0.8, 1.1, 0.8, 1, 0.5, "least_squares", 0, 0.9, &hv_Row, &hv_Column, &hv_Angle, &hv_ScaleR, &hv_ScaleC, &hv_Score);
//
//		if (0 != ((hv_Score.TupleLength()) == 1))
//		{
//
//			p.dx = (hv_Column.D() - XCenter)*0.209;//乘以物相比转换实际坐标 单位mm
//			p.dy = (hv_Row.D() - YCenter)*0.209;
//
//		}
//		else
//		{
//			//异常
//			p.dx = 100;
//			p.dy = 100;
//
//		}
//
//	}
//
//	catch (HException &HDevDxpDefaultException)
//	{
//		p.dx = 100;
//		p.dy = 100;
//	}
//}
//
//void ImgPro::RFC_Move(pStruct &p)
//{
//	HObject  ho_Image, ho_GrayImage, ho_img_ffc, ho_Rectangle1;
//	HObject  ho_Rectangle, ho_ImageReduced, ho_Edges, ho_SelectedContours;
//	HObject  ho_ObjectsConcat, ho_Region, ho_ImgPro, ho_ModelContours;
//	HObject  ho_ContoursAffineTrans, ho_Rectangle3, ho_reduced, ho_ffc_img, ho_searchRegion;
//
//	// Local control variables
//	HTuple  hv_WindowHandle, hv_ModelID, hv_offRow;
//	HTuple  hv_offCol, hv_hwidth, hv_hheight, hv_Files, hv_i;
//	HTuple  hv_Row, hv_Column, hv_Angle, hv_ScaleR, hv_ScaleC;
//	HTuple  hv_Score, hv_HomMat2D, hv_ang, hv_RowTrans, hv_ColTrans;
//	HTuple  hv_ULRow, hv_ULCol, hv_weidth, hv_height, hv_Width, hv_Height;
//
//
//
//	try
//	{
//		///图像基准
//		double XCenter = 0.0;
//		double YCenter = 0.0;
//
//		ReadShapeModel("D:\\Kazam\\rfcaniso.shm", &hv_ModelID);
//		ReadImage(&ho_Image, "D:\\Kazam\\camera_image_rfc.jpeg");
//		Rgb1ToGray(ho_Image, &ho_GrayImage);
//		GetImageSize(ho_GrayImage, &hv_Width, &hv_Height);
//
//		XCenter = hv_Width.D() / 2.0;
//		YCenter = hv_Height.D() / 2.0;
//
//
//		WriteImage(ho_GrayImage, "tiff", 0, "D:\\Kazam\\rfc.tiff");
//		ReadImage(&ho_ffc_img, "D:\\Kazam\\rfc.tiff");
//		ReadRegion(&ho_searchRegion, "D:\\Kazam\\rfcRegion.reg");
//		ReduceDomain(ho_ffc_img, ho_searchRegion, &ho_reduced);
//		FindAnisoShapeModel(ho_reduced, hv_ModelID, -(HTuple(30).TupleRad()), HTuple(60).TupleRad(), 0.8, 1.1, 0.8, 1.1, 0.8, 1, 0.5, "least_squares", 0, 0.9, &hv_Row, &hv_Column, &hv_Angle, &hv_ScaleR, &hv_ScaleC, &hv_Score);
//
//		if (0 != ((hv_Score.TupleLength()) == 1))
//		{
//
//			p.dx = (hv_Column.D() - XCenter)*0.41;//乘以物相比转换实际坐标 单位mm
//			p.dy = (hv_Row.D() - YCenter)*0.41;
//
//		}
//		else
//		{
//			//异常
//			p.dx = 100;
//			p.dy = 100;
//
//		}
//
//	}
//
//	catch (HException &HDevDxpDefaultException)
//	{
//		p.dx = 100;
//		p.dy = 100;
//	}
//}
//#pragma endregion MovePoint
//

CameraDetection::~CameraDetection()
{

	//_exit(1);
}

#pragma endregion 析构函数
