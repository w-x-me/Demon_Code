#include "HalconCpp.h"  
#include"string.h"
using namespace HalconCpp;

//运用此方法定义窗口图片显示有什么好处？
void dev_open_window_fit_size(HTuple hv_Row, HTuple hv_Column, HTuple hv_Width,
	HTuple hv_Height, HTuple hv_WidthLimit, HTuple hv_HeightLimit, HTuple *hv_WindowHandle)
{


	HTuple  hv_MinWidth, hv_MaxWidth, hv_MinHeight;
	HTuple  hv_MaxHeight, hv_ResizeFactor, hv_TempWidth, hv_TempHeight;
	HTuple  hv_WindowWidth, hv_WindowHeight;


	if (0 != (HTuple((hv_WidthLimit.TupleLength()) == 0).TupleOr(hv_WidthLimit<0)))
	{
		hv_MinWidth = 500;
		hv_MaxWidth = 800;
	}
	else if (0 != ((hv_WidthLimit.TupleLength()) == 1))
	{
		hv_MinWidth = 0;
		hv_MaxWidth = hv_WidthLimit;
	}
	else
	{
		hv_MinWidth = ((const HTuple&)hv_WidthLimit)[0];
		hv_MaxWidth = ((const HTuple&)hv_WidthLimit)[1];
	}
	//Parse input tuple HeightLimit
	if (0 != (HTuple((hv_HeightLimit.TupleLength()) == 0).TupleOr(hv_HeightLimit<0)))
	{
		hv_MinHeight = 400;
		hv_MaxHeight = 600;
	}
	else if (0 != ((hv_HeightLimit.TupleLength()) == 1))
	{
		hv_MinHeight = 0;
		hv_MaxHeight = hv_HeightLimit;
	}
	else
	{
		hv_MinHeight = ((const HTuple&)hv_HeightLimit)[0];
		hv_MaxHeight = ((const HTuple&)hv_HeightLimit)[1];
	}
	//
	//Test, if window size has to be changed.
	hv_ResizeFactor = 1;
	//First, expand window to the minimum extents (if necessary).
	if (0 != (HTuple(hv_MinWidth>hv_Width).TupleOr(hv_MinHeight>hv_Height)))
	{
		hv_ResizeFactor = (((hv_MinWidth.TupleReal()) / hv_Width).TupleConcat((hv_MinHeight.TupleReal()) / hv_Height)).TupleMax();
	}
	hv_TempWidth = hv_Width*hv_ResizeFactor;
	hv_TempHeight = hv_Height*hv_ResizeFactor;
	//Then, shrink window to maximum extents (if necessary).
	if (0 != (HTuple(hv_MaxWidth<hv_TempWidth).TupleOr(hv_MaxHeight<hv_TempHeight)))
	{
		hv_ResizeFactor = hv_ResizeFactor*((((hv_MaxWidth.TupleReal()) / hv_TempWidth).TupleConcat((hv_MaxHeight.TupleReal()) / hv_TempHeight)).TupleMin());
	}
	hv_WindowWidth = hv_Width*hv_ResizeFactor;
	hv_WindowHeight = hv_Height*hv_ResizeFactor;
	//Resize window
	SetWindowAttr("background_color", "black");
	OpenWindow(hv_Row, hv_Column, hv_WindowWidth, hv_WindowHeight, 0, "visible", "", &(*hv_WindowHandle));
	HDevWindowStack::Push((*hv_WindowHandle));
	if (HDevWindowStack::IsOpen())
		SetPart(HDevWindowStack::GetActive(), 0, 0, hv_Height - 1, hv_Width - 1);
	return;
}

int main()
{
	HObject  ho_ModelImage, ho_ROI_0, ho_ImageReduced1;
	HObject  ho_ImageReduced, ho_Regions1, ho_Contours, ho_RegionROI;
	HObject  ho_ModelContours, ho_ModelContoursAffineTrans, ho_VarImage;
	HObject  ho_RegionForeground, ho_RegionBackground, ho_rImage;
	HObject  ho_ImageAffineTrans, ho_RegionForegroundImage, ho_RegionBackgroundImage;
	HObject  ho_ModelContoursTrans, ho_ImageScaled, ho_RegionDiff;
	HObject  ho_RegionDiffSelected, ho_RegionOpening, ho_ConnectedRegions;
	HObject  ho_DefectRegions, ho_DefectRegionsTrans, ho_DefectRegionsClosing;
	HObject  ho_RegionUnion, ho_RegionClosing, ho_DefectRegionEnlarged;
	HObject  ho_Ellipse, ho_ImageLeftCheckNG, ho_ImageLeftCheckOK;

	HTuple  hv_Width, hv_Height, hv_WindowHandle;
	HTuple  ho_Width, ho_Height, ho_WindowHandle;
	HTuple  hv_Area, hv_RowModel, hv_ColumnModel, hv_ModelID;
	HTuple  hv_HomMat2DIdentity, hv_HomMat2DTranslate, hv_VariationID;
	HTuple  hv_BackgroundGVModel, hv_ForegroundGVModel, hv_Row;
	HTuple  hv_Column, hv_Angle, hv_Scale, hv_Score, hv_HomMat2DImage;
	HTuple  hv_BackgroundImage, hv_ForegroundImage, hv_Mult;
	HTuple  hv_Add, hv_HomMat2DContour, hv_NumberRegionDiff;
	HTuple  hv_Area2, hv_Row2, hv_Column2, hv_HomMat2DInvert;
	HTuple  hv_Area1, hv_Row1, hv_Column1, hv_Ra, hv_Rb, hv_Phi;
	HTuple  hv_RowEllipse, hv_ColumnEllipse;
	
	HImage image;
	HObject hobject;

	//HImage img;
	ReadImage(&ho_ModelImage, "D:/work/C++/halcon_test/halcon_test/1.jpg");
	//Hlong width, height;
	HTuple width, height;
	//img.GetImageSize(&width, &height);
	GetImageSize(ho_ModelImage, &hv_Width, &hv_Height);
	//HWindow w(0, 0, int(int(hv_Width)*0.25), int(int(hv_Height)*0.25));
	//DispObj(ho_ModelImage, w);
	//w.Click();
	//w.ClearWindow();
	/*if (HDevWindowStack::IsOpen())
	CloseWindow(HDevWindowStack::Pop());
	dev_open_window_fit_size(0, 0, hv_Width, hv_Height, 800, 800, &hv_WindowHandle);//关于此函数的具体实现思路？
	if (HDevWindowStack::IsOpen())
	DispObj(ho_ModelImage, HDevWindowStack::GetActive());*/

	GenRectangle1(&ho_ROI_0, 537.34, 338.62, 1608.7, 1660.54);//定义一个矩阵
	
	ReduceDomain(ho_ModelImage, ho_ROI_0, &ho_ImageReduced1);//参数1：源图像；参数2：截取的矩阵位置；参数3：目标图像
	ReduceDomain(ho_ModelImage, ho_ROI_0, &ho_ImageReduced);
	//如何查看阈值处理后的图片,阈值处理后图片效果
	Threshold(ho_ImageReduced, &ho_Regions1, 96, 233);//阈值的处理;参数1：输入图像；参数2：被分割后的图像；参数3：阈值分割像素的最小值，参数4：阈值分割像素的最大值  被分割后的图像如何显示出来？
	GenContourRegionXld(ho_ROI_0, &ho_Contours, "border");//此处函数的作用

	//WriteImage(ho_ModelImage, "bmp", 0, "threshold.bmp");
	//GetImageSize(ho_ROI_0, &ho_Width, &ho_Height);
	//HWindow w(0, 0, int(int(ho_Width)*0.25), int(int(ho_Height)*0.25));
	//DispObj(ho_ROI_0, w);
	//w.Click();
	//w.ClearWindow();

	
	//img.DispImage(w);
	//img.DispObj(w);

	//system("pause");
	return 0;
}