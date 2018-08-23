#include"Find_ncc_model_exposure.h"
#include<qdebug>
void find_ncc_model_exposure::dev_display_ncc_matching_results(HTuple hv_ModelID, HTuple hv_Color, HTuple hv_Row,
	HTuple hv_Column, HTuple hv_Angle, HTuple hv_Model)
{

	HObject  ho_ModelRegion, ho_ModelContours, ho_ContoursAffinTrans;
	HObject  ho_Cross;

	HTuple  hv_NumMatches, hv_Index, hv_Match, hv_HomMat2DIdentity;
	HTuple  hv_HomMat2DRotate, hv_HomMat2DTranslate, hv_RowTrans;
	HTuple  hv_ColTrans;

	hv_NumMatches = hv_Row.TupleLength();
	if (0 != (hv_NumMatches>0))
	{
		if (0 != ((hv_Model.TupleLength()) == 0))
		{
			TupleGenConst(hv_NumMatches, 0, &hv_Model);
		}
		else if (0 != ((hv_Model.TupleLength()) == 1))
		{
			TupleGenConst(hv_NumMatches, hv_Model, &hv_Model);
		}
		{
			HTuple end_val9 = (hv_ModelID.TupleLength()) - 1;
			HTuple step_val9 = 1;
			for (hv_Index = 0; hv_Index.Continue(end_val9, step_val9); hv_Index += step_val9)
			{
				GetNccModelRegion(&ho_ModelRegion, HTuple(hv_ModelID[hv_Index]));
				GenContourRegionXld(ho_ModelRegion, &ho_ModelContours, "border_holes");
				if (HDevWindowStack::IsOpen())
					SetColor(HDevWindowStack::GetActive(), HTuple(hv_Color[hv_Index % (hv_Color.TupleLength())]));
				{
					HTuple end_val13 = hv_NumMatches - 1;
					HTuple step_val13 = 1;
					for (hv_Match = 0; hv_Match.Continue(end_val13, step_val13); hv_Match += step_val13)
					{
						if (0 != (hv_Index == HTuple(hv_Model[hv_Match])))
						{
							HomMat2dIdentity(&hv_HomMat2DIdentity);
							HomMat2dRotate(hv_HomMat2DIdentity, HTuple(hv_Angle[hv_Match]), 0, 0, &hv_HomMat2DRotate);
							HomMat2dTranslate(hv_HomMat2DRotate, HTuple(hv_Row[hv_Match]), HTuple(hv_Column[hv_Match]),
								&hv_HomMat2DTranslate);
							AffineTransContourXld(ho_ModelContours, &ho_ContoursAffinTrans, hv_HomMat2DTranslate);
							if (HDevWindowStack::IsOpen())
								DispObj(ho_ContoursAffinTrans, HDevWindowStack::GetActive());
							AffineTransPixel(hv_HomMat2DTranslate, 0, 0, &hv_RowTrans, &hv_ColTrans);
							GenCrossContourXld(&ho_Cross, hv_RowTrans, hv_ColTrans, 6, HTuple(hv_Angle[hv_Match]));
							if (HDevWindowStack::IsOpen())
								DispObj(ho_Cross, HDevWindowStack::GetActive());
						}
					}
				}
			}
		}
	}
	return;
}

void find_ncc_model_exposure::dev_open_window_fit_image(HObject ho_Image, HTuple hv_Row, HTuple hv_Column,
	HTuple hv_WidthLimit, HTuple hv_HeightLimit, HTuple *hv_WindowHandle)
{

	HTuple  hv_MinWidth, hv_MaxWidth, hv_MinHeight;
	HTuple  hv_MaxHeight, hv_ResizeFactor, hv_ImageWidth, hv_ImageHeight;
	HTuple  hv_TempWidth, hv_TempHeight, hv_WindowWidth, hv_WindowHeight;

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

	hv_ResizeFactor = 1;
	GetImageSize(ho_Image, &hv_ImageWidth, &hv_ImageHeight);
	if (0 != (HTuple(hv_MinWidth>hv_ImageWidth).TupleOr(hv_MinHeight>hv_ImageHeight)))
	{
		hv_ResizeFactor = (((hv_MinWidth.TupleReal()) / hv_ImageWidth).TupleConcat((hv_MinHeight.TupleReal()) / hv_ImageHeight)).TupleMax();
	}
	hv_TempWidth = hv_ImageWidth*hv_ResizeFactor;
	hv_TempHeight = hv_ImageHeight*hv_ResizeFactor;

	if (0 != (HTuple(hv_MaxWidth<hv_TempWidth).TupleOr(hv_MaxHeight<hv_TempHeight)))
	{
		hv_ResizeFactor = hv_ResizeFactor*((((hv_MaxWidth.TupleReal()) / hv_TempWidth).TupleConcat((hv_MaxHeight.TupleReal()) / hv_TempHeight)).TupleMin());
	}
	hv_WindowWidth = hv_ImageWidth*hv_ResizeFactor;
	hv_WindowHeight = hv_ImageHeight*hv_ResizeFactor;
	SetWindowAttr("background_color", "black");
	OpenWindow(hv_Row, hv_Column, hv_WindowWidth, hv_WindowHeight,winId, "visible", "", &(*hv_WindowHandle));
	HDevWindowStack::Push((*hv_WindowHandle));
	if (HDevWindowStack::IsOpen())
		SetPart(HDevWindowStack::GetActive(), 0, 0, hv_ImageHeight - 1, hv_ImageWidth - 1);
	return;
}

void find_ncc_model_exposure::dev_update_off()
{
	return;
}

void find_ncc_model_exposure::disp_continue_message(HTuple hv_WindowHandle, HTuple hv_Color, HTuple hv_Box)
{

	HTuple  hv_GenParamName, hv_GenParamValue, hv_ContinueMessage;

	hv_GenParamName = HTuple();
	hv_GenParamValue = HTuple();
	if (0 != ((hv_Box.TupleLength())>0))
	{
		if (0 != (HTuple(hv_Box[0]) == HTuple("false")))
		{
			hv_GenParamName = hv_GenParamName.TupleConcat("box");
			hv_GenParamValue = hv_GenParamValue.TupleConcat("false");
		}
		else if (0 != (HTuple(hv_Box[0]) != HTuple("true")))
		{
			hv_GenParamName = hv_GenParamName.TupleConcat("box_color");
			hv_GenParamValue = hv_GenParamValue.TupleConcat(HTuple(hv_Box[0]));
		}
	}
	if (0 != ((hv_Box.TupleLength())>1))
	{
		if (0 != (HTuple(hv_Box[1]) == HTuple("false")))
		{
			hv_GenParamName = hv_GenParamName.TupleConcat("shadow");
			hv_GenParamValue = hv_GenParamValue.TupleConcat("false");
		}
		else if (0 != (HTuple(hv_Box[1]) != HTuple("true")))
		{
			hv_GenParamName = hv_GenParamName.TupleConcat("shadow_color");
			hv_GenParamValue = hv_GenParamValue.TupleConcat(HTuple(hv_Box[1]));
		}
	}
	if (0 != (hv_Color == HTuple("")))
	{
		hv_Color = HTuple();
	}

	hv_ContinueMessage = "Press Run (F5) to continue";
	DispText(hv_WindowHandle, hv_ContinueMessage, "window", "bottom", "right", hv_Color,
		hv_GenParamName, hv_GenParamValue);
	return;
}

void find_ncc_model_exposure::disp_message(HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem,
	HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box)
{
	HTuple  hv_GenParamName, hv_GenParamValue;

	if (0 != (HTuple(hv_Row == HTuple()).TupleOr(hv_Column == HTuple())))
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
	hv_GenParamName = HTuple();
	hv_GenParamValue = HTuple();
	if (0 != ((hv_Box.TupleLength())>0))
	{
		if (0 != (HTuple(hv_Box[0]) == HTuple("false")))
		{
			//Display no box
			hv_GenParamName = hv_GenParamName.TupleConcat("box");
			hv_GenParamValue = hv_GenParamValue.TupleConcat("false");
		}
		else if (0 != (HTuple(hv_Box[0]) != HTuple("true")))
		{
			//Set a color other than the default.
			hv_GenParamName = hv_GenParamName.TupleConcat("box_color");
			hv_GenParamValue = hv_GenParamValue.TupleConcat(HTuple(hv_Box[0]));
		}
	}
	if (0 != ((hv_Box.TupleLength())>1))
	{
		if (0 != (HTuple(hv_Box[1]) == HTuple("false")))
		{
			//Display no shadow.
			hv_GenParamName = hv_GenParamName.TupleConcat("shadow");
			hv_GenParamValue = hv_GenParamValue.TupleConcat("false");
		}
		else if (0 != (HTuple(hv_Box[1]) != HTuple("true")))
		{
			//Set a shadow color other than the default.
			hv_GenParamName = hv_GenParamName.TupleConcat("shadow_color");
			hv_GenParamValue = hv_GenParamValue.TupleConcat(HTuple(hv_Box[1]));
		}
	}
	//Restore default CoordSystem behavior.
	if (0 != (hv_CoordSystem != HTuple("window")))
	{
		hv_CoordSystem = "image";
	}
	//
	if (0 != (hv_Color == HTuple("")))
	{
		//disp_text does not accept an empty string for Color.
		hv_Color = HTuple();
	}
	//
	DispText(hv_WindowHandle, hv_String, hv_CoordSystem, hv_Row, hv_Column, hv_Color,
		hv_GenParamName, hv_GenParamValue);
	return;
}

void find_ncc_model_exposure::set_display_font(HTuple hv_WindowHandle, HTuple hv_Size, HTuple hv_Font, HTuple hv_Bold,
	HTuple hv_Slant)
{

	// Local iconic variables

	// Local control variables
	HTuple  hv_OS, hv_Fonts, hv_Style, hv_Exception;
	HTuple  hv_AvailableFonts, hv_Fdx, hv_Indices;

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
	if (0 != (HTuple(hv_Size == HTuple()).TupleOr(hv_Size == -1)))
	{
		hv_Size = 16;
	}
	if (0 != ((hv_OS.TupleSubstr(0, 2)) == HTuple("Win")))
	{
		//Restore previous behaviour
		hv_Size = (1.13677*hv_Size).TupleInt();
	}
	else
	{
		hv_Size = hv_Size.TupleInt();
	}
	if (0 != (hv_Font == HTuple("Courier")))
	{
		hv_Fonts.Clear();
		hv_Fonts[0] = "Courier";
		hv_Fonts[1] = "Courier 10 Pitch";
		hv_Fonts[2] = "Courier New";
		hv_Fonts[3] = "CourierNew";
		hv_Fonts[4] = "Liberation Mono";
	}
	else if (0 != (hv_Font == HTuple("mono")))
	{
		hv_Fonts.Clear();
		hv_Fonts[0] = "Consolas";
		hv_Fonts[1] = "Menlo";
		hv_Fonts[2] = "Courier";
		hv_Fonts[3] = "Courier 10 Pitch";
		hv_Fonts[4] = "FreeMono";
		hv_Fonts[5] = "Liberation Mono";
	}
	else if (0 != (hv_Font == HTuple("sans")))
	{
		hv_Fonts.Clear();
		hv_Fonts[0] = "Luxi Sans";
		hv_Fonts[1] = "DejaVu Sans";
		hv_Fonts[2] = "FreeSans";
		hv_Fonts[3] = "Arial";
		hv_Fonts[4] = "Liberation Sans";
	}
	else if (0 != (hv_Font == HTuple("serif")))
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
	if (0 != (hv_Bold == HTuple("true")))
	{
		hv_Style += HTuple("Bold");
	}
	else if (0 != (hv_Bold != HTuple("false")))
	{
		hv_Exception = "Wrong value of control parameter Bold";
		throw HException(hv_Exception);
	}
	if (0 != (hv_Slant == HTuple("true")))
	{
		hv_Style += HTuple("Italic");
	}
	else if (0 != (hv_Slant != HTuple("false")))
	{
		hv_Exception = "Wrong value of control parameter Slant";
		throw HException(hv_Exception);
	}
	if (0 != (hv_Style == HTuple("")))
	{
		hv_Style = "Normal";
	}
	QueryFont(hv_WindowHandle, &hv_AvailableFonts);
	hv_Font = "";
	{
		HTuple end_val48 = (hv_Fonts.TupleLength()) - 1;
		HTuple step_val48 = 1;
		for (hv_Fdx = 0; hv_Fdx.Continue(end_val48, step_val48); hv_Fdx += step_val48)
		{
			hv_Indices = hv_AvailableFonts.TupleFind(HTuple(hv_Fonts[hv_Fdx]));
			if (0 != ((hv_Indices.TupleLength())>0))
			{
				if (0 != (HTuple(hv_Indices[0]) >= 0))
				{
					hv_Font = HTuple(hv_Fonts[hv_Fdx]);
					break;
				}
			}
		}
	}
	if (0 != (hv_Font == HTuple("")))
	{
		throw HException("Wrong value of control parameter Font");
	}
	hv_Font = (((hv_Font + "-") + hv_Style) + "-") + hv_Size;
	SetFont(hv_WindowHandle, hv_Font);
	return;
}

int find_ncc_model_exposure::read_image()
{
	ReadImage(&ho_Image, "cap_exposure/cap_exposure_03");
	return 0;
}
void find_ncc_model_exposure::init_windows()
{
	if (HDevWindowStack::IsOpen())
		CloseWindow(HDevWindowStack::Pop());
	dev_open_window_fit_image(ho_Image, 0, 0, -1, -1, &hv_WindowHandle);
	set_display_font(hv_WindowHandle, 16, "mono", "true", "false");
}
void find_ncc_model_exposure::ho_Image1_show()
{
	GenCircle(&ho_Circle, 246, 336, 150);
	if (HDevWindowStack::IsOpen())
		DispObj(ho_Circle, HDevWindowStack::GetActive());
}

void find_ncc_model_exposure::ho_Image_show()
{
	ho_Image1_show();
	//DumpWindowImage(&ho_Circle, hv_WindowHandle);
	//WriteImage(ho_Circle, "bmp", 0, "Circle.bmp");
	AreaCenter(ho_Circle, &hv_Area, &hv_RowRef, &hv_ColumnRef);
	ReduceDomain(ho_Image, ho_Circle, &ho_ImageReduced);
	//WriteImage(ho_ImageReduced, "bmp", 0, "ImageReduced.bmp");
	CreateNccModel(ho_ImageReduced, "auto", 0, 0, "auto", "use_polarity", &hv_ModelID);
	
	if (HDevWindowStack::IsOpen())
		SetDraw(HDevWindowStack::GetActive(), "margin");
	//DumpWindowImage(&ho_Circle, hv_WindowHandle);
	//WriteImage(ho_Circle, "bmp", 0, "Circle1.bmp");
	qDebug() << "ho_Image_show1" << endl;
	if (HDevWindowStack::IsOpen())
		DispObj(ho_Image, HDevWindowStack::GetActive());
	//DumpWindowImage(&ho_Circle, hv_WindowHandle);
	//WriteImage(ho_Circle, "bmp", 0, "Circle2.bmp");
	//WriteImage(ho_Image, "bmp", 0, "ho_Image.bmp");
}

void find_ncc_model_exposure::circle_Image_show()
{
	if (HDevWindowStack::IsOpen())
		SetColor(HDevWindowStack::GetActive(), "yellow");
	//DumpWindowImage(&ho_Circle, hv_WindowHandle);
	//WriteImage(ho_Circle, "bmp", 0, "Circle3.bmp");
	qDebug() << "circle_Image_show" << endl;
	if (HDevWindowStack::IsOpen())
		DispObj(ho_Circle, HDevWindowStack::GetActive());
	//DumpWindowImage(&ho_Circle, hv_WindowHandle);
	//WriteImage(ho_Circle, "bmp", 0, "Circle4.bmp");

	disp_message(hv_WindowHandle, "Trained NCC model", "window", 12, 12, "black", "true");
	disp_continue_message(hv_WindowHandle, "black", "true");
	//DumpWindowImage(&ho_Circle, hv_WindowHandle);
	//WriteImage(ho_Circle, "bmp", 0, "Circle5.bmp");
}