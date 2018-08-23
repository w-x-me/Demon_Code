#include "HalconCpp.h"  
using namespace HalconCpp;

int main()
{
	HImage img;
	ReadImage(&img, "C:/Users/DELL/Desktop/1.jpg");
	Hlong width, height;
	img.GetImageSize(&width, &height);
	HWindow w(0, 0, int(5.5*width), int(5.5*height));
	img.DispImage(w);
	w.Click();
	w.ClearWindow();
	return 0;
}