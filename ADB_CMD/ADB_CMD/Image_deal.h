#pragma once
#include "HalconCpp.h"
#include "HDevThread.h"
using namespace HalconCpp;
class image_deal
{

public:
	image_deal();
	~image_deal();
	HObject  ho_Image, ho_Regions;
	HTuple  hv_Width, hv_Height, hv_Row1, hv_Column1;
	HTuple  hv_Row2, hv_Column2, hv_ScaleRatio, hv_WD, hv_Length;
	HTuple  hv_centerX, hv_centerY, hv_Len, hv_ATan, hv_ang;
	void disp_message(HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem,
		HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box);
	int image_Analysis(char post);
};

