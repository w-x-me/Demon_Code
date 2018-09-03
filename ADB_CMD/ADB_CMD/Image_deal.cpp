#include"Image_deal.h"
image_deal::image_deal()
{

}

void image_deal::disp_message(HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem,
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
int image_deal::image_Analysis(char post)
{
	if (post == 'f')
	{
		ReadImage(&ho_Image, "image_ffc.jpeg");
	}
	if (post == 'r')
	{
		ReadImage(&ho_Image, "image_rfc.jpeg");
	}
	GetImageSize(ho_Image, &hv_Width, &hv_Height);
	Threshold(ho_Image, &ho_Regions, 103, 255);

	SmallestRectangle1(ho_Regions, &hv_Row1, &hv_Column1, &hv_Row2, &hv_Column2);
	//*****假如物象比0.3
	hv_ScaleRatio = 0.3;
	//***镜头到物体表面高度200mmm
	hv_WD = 200;
	//**compute 对角线的Length

	DistancePp(hv_Row1, hv_Column1, hv_Row2, hv_Column2, &hv_Length);
	hv_centerX = (hv_Row1 + hv_Row2) / 2;
	hv_centerY = (hv_Column1 + hv_Column2) / 2;
	if (HDevWindowStack::IsOpen())
		DispObj(ho_Image, HDevWindowStack::GetActive());
	//***像素距离转化机械距离 单位mm
	//**转化底边一半
	hv_Len = (hv_Length*hv_ScaleRatio) / 2;
	try
	{
		
		DispLine(200000, hv_Row1, hv_Column1, hv_Row2, hv_Column2);
		DispCross(200000, hv_centerX, hv_centerY, 66, 0);
	}
	catch(int)
	{
		return -1;
	}
	
	//**求出视场角度

	TupleAtan(hv_Len / 200, &hv_ATan);
	//**弧度转角度
	hv_ang = hv_ATan.TupleDeg();
	return hv_ang;
	
}

image_deal::~image_deal()
{

}