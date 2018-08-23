#include "qt_halcon_image_deal.h"
#include"string.h"
#include <QFileDialog>
Qt_Halcon_Image_Deal::Qt_Halcon_Image_Deal(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
}

void get_grayval_range(HalconCpp::HObject ho_Image, HalconCpp::HObject ho_RegionROI, HalconCpp::HObject *ho_RegionForeground,
	HalconCpp::HObject *ho_RegionBackground, HalconCpp::HTuple *hv_BackgroundGVal, HalconCpp::HTuple *hv_ForegroundGVal)
{

	// Local iconic variables
	HalconCpp::HObject  ho_ImageReduced;

	// Local control variables
	HalconCpp::HTuple  hv_UsedThreshold, hv_DeviationFG, hv_DeviationBG;

	ReduceDomain(ho_Image, ho_RegionROI, &ho_ImageReduced);
	BinaryThreshold(ho_ImageReduced, &(*ho_RegionBackground), "max_separability", "dark",
		&hv_UsedThreshold);
	Difference(ho_RegionROI, (*ho_RegionBackground), &(*ho_RegionForeground));
	Intensity((*ho_RegionForeground), ho_Image, &(*hv_ForegroundGVal), &hv_DeviationFG);
	Intensity((*ho_RegionBackground), ho_Image, &(*hv_BackgroundGVal), &hv_DeviationBG);
	return;
}

void set_display_font(HalconCpp::HTuple hv_WindowHandle, HalconCpp::HTuple hv_Size, HalconCpp::HTuple hv_Font, HalconCpp::HTuple hv_Bold,
	HalconCpp::HTuple hv_Slant)
{

	// Local iconic variables

	// Local control variables
	HalconCpp::HTuple  hv_OS, hv_Fonts, hv_Style, hv_Exception;
	HalconCpp::HTuple  hv_AvailableFonts, hv_Fdx, hv_Indices;

	//This procedure sets the text font of the current window with
	//the specified attributes.
	//
	//Input parameters:
	//WindowHandle: The graphics window for which the font will be set
	//Size: The font size. If Size=-1, the default of 16 is used.
	//Bold: If set to 'true', a bold font is used
	//Slant: If set to 'true', a slanted font is used
	//
	GetSystem("operating_system", &hv_OS);
	if (0 != (HalconCpp::HTuple(hv_Size == HalconCpp::HTuple()).TupleOr(hv_Size == -1)))
	{
		hv_Size = 16;
	}
	if (0 != ((hv_OS.TupleSubstr(0, 2)) == HalconCpp::HTuple("Win")))
	{
		//Restore previous behaviour
		hv_Size = (1.13677*hv_Size).TupleInt();
	}
	else
	{
		hv_Size = hv_Size.TupleInt();
	}
	if (0 != (hv_Font == HalconCpp::HTuple("Courier")))
	{
		hv_Fonts.Clear();
		hv_Fonts[0] = "Courier";
		hv_Fonts[1] = "Courier 10 Pitch";
		hv_Fonts[2] = "Courier New";
		hv_Fonts[3] = "CourierNew";
		hv_Fonts[4] = "Liberation Mono";
	}
	else if (0 != (hv_Font == HalconCpp::HTuple("mono")))
	{
		hv_Fonts.Clear();
		hv_Fonts[0] = "Consolas";
		hv_Fonts[1] = "Menlo";
		hv_Fonts[2] = "Courier";
		hv_Fonts[3] = "Courier 10 Pitch";
		hv_Fonts[4] = "FreeMono";
		hv_Fonts[5] = "Liberation Mono";
	}
	else if (0 != (hv_Font == HalconCpp::HTuple("sans")))
	{
		hv_Fonts.Clear();
		hv_Fonts[0] = "Luxi Sans";
		hv_Fonts[1] = "DejaVu Sans";
		hv_Fonts[2] = "FreeSans";
		hv_Fonts[3] = "Arial";
		hv_Fonts[4] = "Liberation Sans";
	}
	else if (0 != (hv_Font == HalconCpp::HTuple("serif")))
	{
		hv_Fonts.Clear();
		hv_Fonts[0] = "Times New Roman";
		hv_Fonts[1] = "Luxi Serif";
		hv_Fonts[2] = "DejaVu Serif";
		hv_Fonts[3] = "FreeSerif";
		hv_Fonts[4] = "Utopia";
		hv_Fonts[5] = "Liberation Serif";
	}
	else
	{
		hv_Fonts = hv_Font;
	}
	hv_Style = "";
	if (0 != (hv_Bold == HalconCpp::HTuple("true")))
	{
		hv_Style += HalconCpp::HTuple("Bold");
	}
	else if (0 != (hv_Bold != HalconCpp::HTuple("false")))
	{
		hv_Exception = "Wrong value of control parameter Bold";
		throw HalconCpp::HException(hv_Exception);
	}
	if (0 != (hv_Slant == HalconCpp::HTuple("true")))
	{
		hv_Style += HalconCpp::HTuple("Italic");
	}
	else if (0 != (hv_Slant != HalconCpp::HTuple("false")))
	{
		hv_Exception = "Wrong value of control parameter Slant";
		throw HalconCpp::HException(hv_Exception);
	}
	if (0 != (hv_Style == HalconCpp::HTuple("")))
	{
		hv_Style = "Normal";
	}
	QueryFont(hv_WindowHandle, &hv_AvailableFonts);
	hv_Font = "";
	{
		HalconCpp::HTuple end_val48 = (hv_Fonts.TupleLength()) - 1;
		HalconCpp::HTuple step_val48 = 1;
		for (hv_Fdx = 0; hv_Fdx.Continue(end_val48, step_val48); hv_Fdx += step_val48)
		{
			hv_Indices = hv_AvailableFonts.TupleFind(HalconCpp::HTuple(hv_Fonts[hv_Fdx]));
			if (0 != ((hv_Indices.TupleLength())>0))
			{
				if (0 != (HalconCpp::HTuple(hv_Indices[0]) >= 0))
				{
					hv_Font = HalconCpp::HTuple(hv_Fonts[hv_Fdx]);
					break;
				}
			}
		}
	}
	if (0 != (hv_Font == HalconCpp::HTuple("")))
	{
		throw HalconCpp::HException("Wrong value of control parameter Font");
	}
	hv_Font = (((hv_Font + "-") + hv_Style) + "-") + hv_Size;
	SetFont(hv_WindowHandle, hv_Font);
	return;
}


void disp_message(HalconCpp::HTuple hv_WindowHandle, HalconCpp::HTuple hv_String, HalconCpp::HTuple hv_CoordSystem,
	HalconCpp::HTuple hv_Row, HalconCpp::HTuple hv_Column, HalconCpp::HTuple hv_Color, HalconCpp::HTuple hv_Box)
{

	// Local iconic variables

	// Local control variables
	HalconCpp::HTuple  hv_GenParamName, hv_GenParamValue;

	
	if (0 != (HalconCpp::HTuple(hv_Row == HalconCpp::HTuple()).TupleOr(hv_Column == HalconCpp::HTuple())))
	{
		return;
	}
	if (0 != (hv_Row == -1))
	{
		hv_Row = 12;
	}
	if (0 != (hv_Column == -1))
	{
		hv_Column = 12;
	}
	//
	//Convert the parameter Box to generic parameters.
	hv_GenParamName = HalconCpp::HTuple();
	hv_GenParamValue = HalconCpp::HTuple();
	if (0 != ((hv_Box.TupleLength())>0))
	{
		if (0 != (HalconCpp::HTuple(hv_Box[0]) == HalconCpp::HTuple("false")))
		{
			//Display no box
			hv_GenParamName = hv_GenParamName.TupleConcat("box");
			hv_GenParamValue = hv_GenParamValue.TupleConcat("false");
		}
		else if (0 != (HalconCpp::HTuple(hv_Box[0]) != HalconCpp::HTuple("true")))
		{
			//Set a color other than the default.
			hv_GenParamName = hv_GenParamName.TupleConcat("box_color");
			hv_GenParamValue = hv_GenParamValue.TupleConcat(HalconCpp::HTuple(hv_Box[0]));
		}
	}
	if (0 != ((hv_Box.TupleLength())>1))
	{
		if (0 != (HalconCpp::HTuple(hv_Box[1]) == HalconCpp::HTuple("false")))
		{
			//Display no shadow.
			hv_GenParamName = hv_GenParamName.TupleConcat("shadow");
			hv_GenParamValue = hv_GenParamValue.TupleConcat("false");
		}
		else if (0 != (HalconCpp::HTuple(hv_Box[1]) != HalconCpp::HTuple("true")))
		{
			//Set a shadow color other than the default.
			hv_GenParamName = hv_GenParamName.TupleConcat("shadow_color");
			hv_GenParamValue = hv_GenParamValue.TupleConcat(HalconCpp::HTuple(hv_Box[1]));
		}
	}
	//Restore default CoordSystem behavior.
	if (0 != (hv_CoordSystem != HalconCpp::HTuple("window")))
	{
		hv_CoordSystem = "image";
	}
	//
	if (0 != (hv_Color == HalconCpp::HTuple("")))
	{
		//disp_text does not accept an empty string for Color.
		hv_Color = HalconCpp::HTuple();
	}
	//
	DispText(hv_WindowHandle, hv_String, hv_CoordSystem, hv_Row, hv_Column, hv_Color,
		hv_GenParamName, hv_GenParamValue);
	return;
}

void Qt_Halcon_Image_Deal::My_deal_image()
{
	//HalconCpp::HDevWindowStack::Pop();
	QPixmap image = QPixmap("my_ho_rImage.bmp");
	//image.scaled(ui.Image_lb_2->width(),ui.Image_lb_2->height());
	ui.Image_lb_2->setScaledContents(true);
	ui.Image_lb_2->setPixmap(image);
	HalconCpp::HObject  ho_ModelImage, ho_ROI_0, ho_ImageReduced1;
	HalconCpp::HObject  ho_ImageReduced, ho_Regions1, ho_Contours, ho_RegionROI;
	HalconCpp::HObject  ho_ModelContours, ho_ModelContoursAffineTrans, ho_VarImage;
	HalconCpp::HObject  ho_RegionForeground, ho_RegionBackground, ho_BinImage, ho_rImage;
	HalconCpp::HObject  ho_ImageAffineTrans, ho_RegionForegroundImage, ho_RegionBackgroundImage;
	HalconCpp::HObject  ho_ModelContoursTrans, ho_ImageScaled, ho_RegionDiff;
	HalconCpp::HObject  ho_RegionDiffSelected, ho_RegionOpening, ho_ConnectedRegions;
	HalconCpp::HObject  ho_DefectRegions, ho_DefectRegionsTrans, ho_DefectRegionsClosing;
	HalconCpp::HObject  ho_RegionUnion, ho_RegionClosing, ho_DefectRegionEnlarged;
	HalconCpp::HObject  ho_Ellipse, ho_ImageLeftCheckNG, ho_ImageLeftCheckOK;

	// Local control variables
	HalconCpp::HTuple  hv_Width, hv_Height, hv_WindowHandle;
	HalconCpp::HTuple  hv_Area, hv_RowModel, hv_ColumnModel, hv_ModelID;
	HalconCpp::HTuple  hv_HomMat2DIdentity, hv_HomMat2DTranslate, hv_VariationID;
	HalconCpp::HTuple  hv_BackgroundGVModel, hv_ForegroundGVModel, hv_Row;
	HalconCpp::HTuple  hv_Column, hv_Angle, hv_Scale, hv_Score, hv_HomMat2DImage;
	HalconCpp::HTuple  hv_BackgroundImage, hv_ForegroundImage, hv_Mult;
	HalconCpp::HTuple  hv_Add, hv_HomMat2DContour, hv_NumberRegionDiff;
	HalconCpp::HTuple  hv_Area2, hv_Row2, hv_Column2, hv_HomMat2DInvert;
	HalconCpp::HTuple  hv_Area1, hv_Row1, hv_Column1, hv_Ra, hv_Rb, hv_i, hv_Phi;
	HalconCpp::HTuple  hv_RowEllipse, hv_ColumnEllipse;

	ReadImage(&ho_ModelImage, "ModelImageLeft.bmp");
	GetImageSize(ho_ModelImage, &hv_Width, &hv_Height);

	ui.Image_lb->setText("读取图片");
	HalconCpp::ReadImage(&ho_rImage, "LeftCAM.bmp");
	HalconCpp::GetImageSize(ho_rImage, &hv_Width, &hv_Height);
	HalconCpp::SetWindowAttr("background_color", "black");
	Hlong winID = (Hlong)ui.Image_lb->winId();
	HalconCpp::HDevWindowStack::IsOpen();
	HalconCpp::OpenWindow(0, 0, ui.Image_lb->width(), ui.Image_lb->height(), winID, "visible", "", &hv_WindowHandle);
	HalconCpp::HDevWindowStack::Push((hv_WindowHandle));
	if (HalconCpp::HDevWindowStack::IsOpen())
		HalconCpp::DispObj(ho_rImage, HalconCpp::HDevWindowStack::GetActive());

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
	PrepareDirectVariationModel(ho_ModelImage, ho_VarImage, hv_VariationID, (HalconCpp::HTuple(20).Append(25)),
		(HalconCpp::HTuple(1.6).Append(1.6)));

	get_grayval_range(ho_ModelImage, ho_Regions1, &ho_RegionForeground, &ho_RegionBackground,
		&hv_BackgroundGVModel, &hv_ForegroundGVModel);
	//

	//************************这一整套也只是找出一个区域，找出目标区域************
	FindScaledShapeModel(ho_rImage, hv_ModelID, 0, HalconCpp::HTuple(360).TupleRad(), 0.98, 1.02,
		0.4, 1, 1, "least_squares_high", (HalconCpp::HTuple(5).Append(3)), 0.9, &hv_Row, &hv_Column,
		&hv_Angle, &hv_Scale, &hv_Score);

	GetShapeModelContours(&ho_ModelContours, hv_ModelID, 1);
	VectorAngleToRigid(HalconCpp::HTuple(hv_Row[0]), HalconCpp::HTuple(hv_Column[0]), hv_Angle, HalconCpp::HTuple(hv_RowModel[0]),
		HalconCpp::HTuple(hv_ColumnModel[0]), 0, &hv_HomMat2DImage);
	AffineTransImage(ho_rImage, &ho_ImageAffineTrans, hv_HomMat2DImage, "constant",
		"false");
	get_grayval_range(ho_ImageAffineTrans, ho_Regions1, &ho_RegionForegroundImage,
		&ho_RegionBackgroundImage, &hv_BackgroundImage, &hv_ForegroundImage);

	hv_Mult = (hv_ForegroundGVModel - hv_BackgroundGVModel) / (hv_ForegroundImage - hv_BackgroundImage);
	hv_Add = hv_ForegroundGVModel - (hv_Mult*hv_ForegroundImage);
	VectorAngleToRigid(0, 0, 0, HalconCpp::HTuple(hv_Row[0]), HalconCpp::HTuple(hv_Column[0]), hv_Angle,
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
		HalconCpp::HTuple end_val52 = hv_NumberRegionDiff;
		HalconCpp::HTuple step_val52 = 1;
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
				if (HalconCpp::HDevWindowStack::IsOpen())
					HalconCpp::SetLineWidth(HalconCpp::HDevWindowStack::GetActive(), 2);
				if (HalconCpp::HDevWindowStack::IsOpen())
					HalconCpp::SetDraw(HalconCpp::HDevWindowStack::GetActive(), "fill");
				if (HalconCpp::HDevWindowStack::IsOpen())
					HalconCpp::SetColor(HalconCpp::HDevWindowStack::GetActive(), "red");
				if (HalconCpp::HDevWindowStack::IsOpen())
					HalconCpp::SetColor(HalconCpp::HDevWindowStack::GetActive(), "orange");
				//if (HDevWindowStack::IsOpen())
				// DispObj(ho_DefectRegionsClosing, HDevWindowStack::GetActive());
				if (HalconCpp::HDevWindowStack::IsOpen())
					HalconCpp::SetColor(HalconCpp::HDevWindowStack::GetActive(), "magenta");
				if (HalconCpp::HDevWindowStack::IsOpen())
					HalconCpp::SetDraw(HalconCpp::HDevWindowStack::GetActive(), "margin");
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

					if (HalconCpp::HDevWindowStack::IsOpen())
						HalconCpp::SetLineWidth(HalconCpp::HDevWindowStack::GetActive(), 1);
					if (HalconCpp::HDevWindowStack::IsOpen())
						HalconCpp::SetColor(HalconCpp::HDevWindowStack::GetActive(), "green");
					if (HalconCpp::HDevWindowStack::IsOpen())
						DispObj(ho_rImage, HalconCpp::HDevWindowStack::GetActive());
					if (HalconCpp::HDevWindowStack::IsOpen())
						DispObj(ho_Ellipse, HalconCpp::HDevWindowStack::GetActive());
					set_display_font(hv_WindowHandle, 66, "mono", "true", "false");
					disp_message(hv_WindowHandle, " NG", "window", 12, 12, "red", "false");
					DumpWindowImage(&ho_ImageLeftCheckNG, hv_WindowHandle);
					WriteImage(ho_ImageLeftCheckNG, "bmp", 0, "ho_ImageLeftCheckNG.bmp");
					//WriteImage(ho_rImage, "bmp", 0, m_StrImagePathTemp.GetBuffer());
					//m_StrImagePathTemp.ReleaseBuffer();
					//WriteImage(ho_ImageLeftCheckNG, "bmp", 0, "ImageLeftCheckFinal.bmp");
					return ;

				}
				else
				{
					//if (HDevWindowStack::IsOpen())
					//  DispObj(ho_rImage, HDevWindowStack::GetActive());
					///*set_display_font(hv_WindowHandle, 66, "mono", "true", "false");*/
					//disp_message(hv_WindowHandle, "  OK", "window", 12, 12, "green", "false");
					//DumpWindowImage(&ho_ImageLeftCheckOK, hv_WindowHandle);
					//WriteImage(ho_ImageLeftCheckOK, "bmp", 0, "ImageLeftCheckFinal.bmp");
					return ;
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
				return ;
			}
		}
	}
}


void Qt_Halcon_Image_Deal::My_read_image()
{
	HalconCpp::HObject  ho_rImage;
	HalconCpp::HTuple hv_WindowHandle;
	HalconCpp::ReadImage(&ho_rImage, "LeftCAM.bmp");
	HalconCpp::GetImageSize(ho_rImage, &hv_Width, &hv_Height);
	HalconCpp::SetWindowAttr("background_color", "black");
	Hlong winID = (Hlong)ui.Image_lb_2->winId();

	HalconCpp::OpenWindow(0, 0, ui.Image_lb->width(), ui.Image_lb->height(), winID, "visible", "", &hv_WindowHandle);
	HalconCpp::HDevWindowStack::Push((hv_WindowHandle));
	if (HalconCpp::HDevWindowStack::IsOpen())
		HalconCpp::DispObj(ho_rImage, HalconCpp::HDevWindowStack::GetActive());
	WriteImage(ho_rImage, "bmp", 0, "my_ho_rImage.bmp");
	ui.Image_lb->update();
	Sleep(1000);
	if (HalconCpp::HDevWindowStack::IsOpen())
		CloseWindow(HalconCpp::HDevWindowStack::Pop());
	HalconCpp::ReadImage(&ho_rImage, "LeftCAM1.bmp");
	HalconCpp::GetImageSize(ho_rImage, &hv_Width, &hv_Height);
	HalconCpp::SetWindowAttr("background_color", "black");
	HalconCpp::OpenWindow(0, 0, ui.Image_lb->width(), ui.Image_lb->height(), winID, "visible", "", &hv_WindowHandle);
	HalconCpp::HDevWindowStack::Push((hv_WindowHandle));
	if (HalconCpp::HDevWindowStack::IsOpen())
		HalconCpp::DispObj(ho_rImage, HalconCpp::HDevWindowStack::GetActive());
	WriteImage(ho_rImage, "bmp", 0, "my_LeftCAM1.bmp");

	
	
}

Qt_Halcon_Image_Deal::~Qt_Halcon_Image_Deal()
{

}
