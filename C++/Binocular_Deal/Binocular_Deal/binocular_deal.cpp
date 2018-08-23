#include<iostream>
#include "HalconCpp.h"  
#include"string.h"
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
using namespace HalconCpp;
void get_grayval_range(HObject ho_Image, HObject ho_RegionROI, HObject *ho_RegionForeground,
	HObject *ho_RegionBackground, HTuple *hv_BackgroundGVal, HTuple *hv_ForegroundGVal)
{

	HObject  ho_ImageReduced;

	HTuple  hv_UsedThreshold, hv_DeviationFG, hv_DeviationBG;

	ReduceDomain(ho_Image, ho_RegionROI, &ho_ImageReduced);
	BinaryThreshold(ho_ImageReduced, &(*ho_RegionBackground), "max_separability", "dark",
		&hv_UsedThreshold);
	Difference(ho_RegionROI, (*ho_RegionBackground), &(*ho_RegionForeground));
	Intensity((*ho_RegionForeground), ho_Image, &(*hv_ForegroundGVal), &hv_DeviationFG);
	Intensity((*ho_RegionBackground), ho_Image, &(*hv_BackgroundGVal), &hv_DeviationBG);
	return;
}
void dev_open_window_fit_size(HTuple hv_Row, HTuple hv_Column, HTuple hv_Width,
	HTuple hv_Height, HTuple hv_WidthLimit, HTuple hv_HeightLimit, HTuple *hv_WindowHandle)
{
	/*hv_Row=0, 
	hv_Column=0, 
	hv_Width=hv_Width, 
	hv_Height=hv_Height, 
	hv_WidthLimit=600, 
	hv_HeightLimit=600, 
	hv_WindowHandle=&hv_WindowHandle*/
	HTuple  hv_MinWidth, hv_MaxWidth, hv_MinHeight;
	HTuple  hv_MaxHeight, hv_ResizeFactor, hv_TempWidth, hv_TempHeight;
	HTuple  hv_WindowWidth, hv_WindowHeight;

	//hv_WidthLimit.TupleLength()  获取元祖个数
	//HTuple TupleOr(const HTuple& T2) const;计算一个元组的逻辑"或"
	
	//初始化 hv_MinWidth, hv_MaxWidth
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

	//初始化hv_MinHeight，hv_MaxHeight,
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

	//此处定义hv_ResizeFactor值得作用？
	hv_ResizeFactor = 1;
	if (0 != (HTuple(hv_MinWidth>hv_Width).TupleOr(hv_MinHeight>hv_Height)))
	{
		hv_ResizeFactor = (((hv_MinWidth.TupleReal()) / hv_Width).TupleConcat((hv_MinHeight.TupleReal()) / hv_Height)).TupleMax();
	}
	hv_TempWidth = hv_Width*hv_ResizeFactor;
	hv_TempHeight = hv_Height*hv_ResizeFactor;

	if (0 != (HTuple(hv_MaxWidth<hv_TempWidth).TupleOr(hv_MaxHeight<hv_TempHeight)))
	{
		hv_ResizeFactor = hv_ResizeFactor*((((hv_MaxWidth.TupleReal()) / hv_TempWidth).TupleConcat((hv_MaxHeight.TupleReal()) / hv_TempHeight)).TupleMin());
	}
	hv_WindowWidth = hv_Width*hv_ResizeFactor;
	hv_WindowHeight = hv_Height*hv_ResizeFactor;

	SetWindowAttr("background_color", "black");
	//参数作用？
	OpenWindow(hv_Row, hv_Column, hv_WindowWidth, hv_WindowHeight, 0, "visible", "", &(*hv_WindowHandle));
	HDevWindowStack::Push((*hv_WindowHandle));

	if (HDevWindowStack::IsOpen())
		SetPart(HDevWindowStack::GetActive(), 0, 0, hv_Height - 1, hv_Width - 1);
	return;
}
int LeftImage_Deal()
{
	HObject  ho_ModelImage, ho_ROI_0, ho_ImageReduced1;
	HObject  ho_ImageReduced, ho_Regions1, ho_Contours, ho_RegionROI;
	HObject  ho_ModelContours, ho_ModelContoursAffineTrans, ho_VarImage;
	HObject  ho_RegionForeground, ho_RegionBackground, ho_BinImage, ho_rImage;
	HObject  ho_ImageAffineTrans, ho_RegionForegroundImage, ho_RegionBackgroundImage;
	HObject  ho_ModelContoursTrans, ho_ImageScaled, ho_RegionDiff;
	HObject  ho_RegionDiffSelected, ho_RegionOpening, ho_ConnectedRegions;
	HObject  ho_DefectRegions, ho_DefectRegionsTrans, ho_DefectRegionsClosing;
	HObject  ho_RegionUnion, ho_RegionClosing, ho_DefectRegionEnlarged;
	HObject  ho_Ellipse, ho_ImageLeftCheckNG, ho_ImageLeftCheckOK;


	HTuple  hv_Width, hv_Height, hv_WindowHandle;
	HTuple  hv_Area, hv_RowModel, hv_ColumnModel, hv_ModelID;
	HTuple  hv_HomMat2DIdentity, hv_HomMat2DTranslate, hv_VariationID;
	HTuple  hv_BackgroundGVModel, hv_ForegroundGVModel, hv_Row;
	HTuple  hv_Column, hv_Angle, hv_Scale, hv_Score, hv_HomMat2DImage;
	HTuple  hv_BackgroundImage, hv_ForegroundImage, hv_Mult;
	HTuple  hv_Add, hv_HomMat2DContour, hv_NumberRegionDiff;
	HTuple  hv_Area2, hv_Row2, hv_Column2, hv_HomMat2DInvert;
	HTuple  hv_Area1, hv_Row1, hv_Column1, hv_Ra, hv_Rb, hv_i, hv_Phi;
	HTuple  hv_RowEllipse, hv_ColumnEllipse;
	ReadImage(&ho_rImage, "D:/work/C++/Binocular_Deal/Image/LeftCAM.bmp");
	GetImageSize(ho_rImage, &hv_Width, &hv_Height);

	WriteImage(ho_rImage, "bmp", 0, "LeftCAM.bmp");
	ReadImage(&ho_ModelImage, "LeftCAM.bmp");
	GetImageSize(ho_ModelImage, &hv_Width, &hv_Height);

	//if (HDevWindowStack::IsOpen())
	//  CloseWindow(HDevWindowStack::Pop());
	dev_open_window_fit_size(0, 0, hv_Width, hv_Height, 600, 600, &hv_WindowHandle);
	
	
	
	//if (HDevWindowStack::IsOpen())
	//DispObj(ho_ModelImage, HDevWindowStack::GetActive());
	GenRectangle1(&ho_ROI_0, 537.34, 338.62, 1608.7, 1660.54);
	ReduceDomain(ho_ModelImage, ho_ROI_0, &ho_ImageReduced1);
	ReduceDomain(ho_ModelImage, ho_ROI_0, &ho_ImageReduced);
	Threshold(ho_ImageReduced, &ho_Regions1, 96, 233);
	GenContourRegionXld(ho_ROI_0, &ho_Contours, "border");
	GenRegionContourXld(ho_Contours, &ho_RegionROI, "filled");
	AreaCenter(ho_RegionROI, &hv_Area, &hv_RowModel, &hv_ColumnModel);
	ReadShapeModel("LeftCheck.shm", &hv_ModelID);
	GetShapeModelContours(&ho_ModelContours, hv_ModelID, 1);
	HomMat2dIdentity(&hv_HomMat2DIdentity);
	HomMat2dTranslate(hv_HomMat2DIdentity, hv_RowModel, hv_ColumnModel, &hv_HomMat2DTranslate);
	AffineTransContourXld(ho_ModelContours, &ho_ModelContoursAffineTrans, hv_HomMat2DTranslate);
	CreateVariationModel(hv_Width, hv_Height, "byte", "direct", &hv_VariationID);
	SobelAmp(ho_ModelImage, &ho_VarImage, "sum_abs", 5);
	PrepareDirectVariationModel(ho_ModelImage, ho_VarImage, hv_VariationID, (HTuple(20).Append(25)),
		(HTuple(1.6).Append(1.6)));
	get_grayval_range(ho_ModelImage, ho_Regions1, &ho_RegionForeground, &ho_RegionBackground,
		&hv_BackgroundGVModel, &hv_ForegroundGVModel);
	//

	//************************这一整套也只是找出一个区域，找出目标区域************
	FindScaledShapeModel(ho_rImage, hv_ModelID, 0, HTuple(360).TupleRad(), 0.98, 1.02,
		0.4, 1, 1, "least_squares_high", (HTuple(5).Append(3)), 0.9, &hv_Row, &hv_Column,
		&hv_Angle, &hv_Scale, &hv_Score);

	GetShapeModelContours(&ho_ModelContours, hv_ModelID, 1);
	VectorAngleToRigid(HTuple(hv_Row[0]), HTuple(hv_Column[0]), hv_Angle, HTuple(hv_RowModel[0]),
		HTuple(hv_ColumnModel[0]), 0, &hv_HomMat2DImage);
	AffineTransImage(ho_rImage, &ho_ImageAffineTrans, hv_HomMat2DImage, "constant",
		"false");
	get_grayval_range(ho_ImageAffineTrans, ho_Regions1, &ho_RegionForegroundImage,
		&ho_RegionBackgroundImage, &hv_BackgroundImage, &hv_ForegroundImage);

	hv_Mult = (hv_ForegroundGVModel - hv_BackgroundGVModel) / (hv_ForegroundImage - hv_BackgroundImage);
	hv_Add = hv_ForegroundGVModel - (hv_Mult*hv_ForegroundImage);
	VectorAngleToRigid(0, 0, 0, HTuple(hv_Row[0]), HTuple(hv_Column[0]), hv_Angle,
		&hv_HomMat2DContour);
	AffineTransContourXld(ho_ModelContours, &ho_ModelContoursTrans, hv_HomMat2DContour);
	ReduceDomain(ho_ImageAffineTrans, ho_RegionROI, &ho_ImageReduced);
	ScaleImage(ho_ImageReduced, &ho_ImageScaled, hv_Mult, hv_Add);


	//************主要是下面的这个算子，将一幅图像与一个变化模型相比较
	CompareExtVariationModel(ho_ImageReduced, &ho_RegionDiff, hv_VariationID, "light_dark");
	/*if (HDevWindowStack::IsOpen())
	DispObj(ho_rImage, HDevWindowStack::GetActive());*/
	CountObj(ho_RegionDiff, &hv_NumberRegionDiff);
	{
		HTuple end_val52 = hv_NumberRegionDiff;
		HTuple step_val52 = 1;
		for (hv_i = 1; hv_i.Continue(end_val52, step_val52); hv_i += step_val52)
		{
			SelectObj(ho_RegionDiff, &ho_RegionDiffSelected, hv_i);
			OpeningCircle(ho_RegionDiffSelected, &ho_RegionOpening, 2.5);

			AreaCenter(ho_RegionOpening, &hv_Area2, &hv_Row2, &hv_Column2);
			// wight=(int)hv_Area2;
			// hight=(double)hv_Column2;
			if (0 != (hv_Area2.TupleLess(185498)))
			{
				Connection(ho_RegionOpening, &ho_ConnectedRegions);
				SelectShape(ho_ConnectedRegions, &ho_DefectRegions, "height", "and", 20, 99999);
				HomMat2dInvert(hv_HomMat2DImage, &hv_HomMat2DInvert);
				AffineTransRegion(ho_DefectRegions, &ho_DefectRegionsTrans, hv_HomMat2DInvert,
					"nearest_neighbor");
				ClosingCircle(ho_DefectRegionsTrans, &ho_DefectRegionsClosing, 1.5);
				dev_open_window_fit_size(0, 0, hv_Width, hv_Height, 600, 600, &hv_WindowHandle);
				//if (HDevWindowStack::IsOpen())
					SetLineWidth(HDevWindowStack::GetActive(), 2);
				//if (HDevWindowStack::IsOpen())
					SetDraw(HDevWindowStack::GetActive(), "fill");
				//if (HDevWindowStack::IsOpen())
					SetColor(HDevWindowStack::GetActive(), "red");
				//if (HDevWindowStack::IsOpen())
					SetColor(HDevWindowStack::GetActive(), "orange");
				//if (HDevWindowStack::IsOpen())
				// DispObj(ho_DefectRegionsClosing, HDevWindowStack::GetActive());
				//if (HDevWindowStack::IsOpen())
					SetColor(HDevWindowStack::GetActive(), "magenta");
				//if (HDevWindowStack::IsOpen())
					SetDraw(HDevWindowStack::GetActive(), "margin");
				Union1(ho_DefectRegionsClosing, &ho_RegionUnion);
				AreaCenter(ho_RegionUnion, &hv_Area1, &hv_Row1, &hv_Column1);
				if (0 != ((hv_Area1.TupleLength()) != 0))
				{
					ClosingCircle(ho_RegionUnion, &ho_RegionClosing, 10);
					Connection(ho_RegionClosing, &ho_DefectRegionEnlarged);
					EllipticAxis(ho_DefectRegionEnlarged, &hv_Ra, &hv_Rb, &hv_Phi);

					if (0 != (hv_Phi.TupleLength()))
					{
						AreaCenter(ho_DefectRegionEnlarged, &hv_Area, &hv_RowEllipse, &hv_ColumnEllipse);
						GenEllipse(&ho_Ellipse, hv_RowEllipse, hv_ColumnEllipse, hv_Phi, hv_Ra * 2,
							hv_Rb * 2);

						//if (HDevWindowStack::IsOpen())
						// DispObj(ho_Ellipse, HDevWindowStack::GetActive());
					}

					if (HDevWindowStack::IsOpen())
						SetLineWidth(HDevWindowStack::GetActive(), 1);
					if (HDevWindowStack::IsOpen())
						SetColor(HDevWindowStack::GetActive(), "green");
					if (HDevWindowStack::IsOpen())
						DispObj(ho_rImage, HDevWindowStack::GetActive());
					if (HDevWindowStack::IsOpen())
						DispObj(ho_Ellipse, HDevWindowStack::GetActive());
					//set_display_font(hv_WindowHandle, 66, "mono", "true", "false");
					//disp_message(hv_WindowHandle, " NG", "window", 12, 12, "red", "false");
					DumpWindowImage(&ho_ImageLeftCheckNG, hv_WindowHandle);
					WriteImage(ho_ImageLeftCheckNG, "bmp", 0, "ho_ImageLeftCheckNG.bmp");
					//WriteImage(ho_rImage, "bmp", 0, m_StrImagePathTemp.GetBuffer());
					//m_StrImagePathTemp.ReleaseBuffer();
					//WriteImage(ho_ImageLeftCheckNG, "bmp", 0, "ImageLeftCheckFinal.bmp");

					WriteImage(ho_rImage, "bmp", 0, "ho_rImage.bmp");
					return false;

				}
				else
				{
					//if (HDevWindowStack::IsOpen())
					//  DispObj(ho_rImage, HDevWindowStack::GetActive());
					///*set_display_font(hv_WindowHandle, 66, "mono", "true", "false");*/
					//disp_message(hv_WindowHandle, "  OK", "window", 12, 12, "green", "false");
					//DumpWindowImage(&ho_ImageLeftCheckOK, hv_WindowHandle);
					//WriteImage(ho_ImageLeftCheckOK, "bmp", 0, "ImageLeftCheckFinal.bmp");
					return true;
				}

			}
			else
			{
				//   if (HDevWindowStack::IsOpen())
				//     DispObj(ho_rImage, HDevWindowStack::GetActive());
				///*   set_display_font(hv_WindowHandle, 66, "mono", "true", "false");*/
				//   disp_message(hv_WindowHandle, "  OK", "window", 12, 12, "green", "false");
				//   DumpWindowImage(&ho_ImageLeftCheckOK, hv_WindowHandle);
				//   WriteImage(ho_ImageLeftCheckOK, "bmp", 0, "ImageLeftCheckFinal.bmp");
				return true;
			}
		}
		return 0;
	}
}
int main()
{
	LeftImage_Deal();
	return 0;
}