#include "HalconCpp.h"
using namespace HalconCpp;
class find_ncc_model_exposure
{
	public:
		HObject  ho_Image, ho_Circle, ho_ImageReduced;
		HTuple  hv_WindowHandle, hv_Area, hv_RowRef, hv_ColumnRef;
		HTuple  hv_ModelID, hv_Rows, hv_Cols, hv_J, hv_Row, hv_Column;
		HTuple  hv_Angle, hv_Score, hv_StdDevRows, hv_StdDevCols;
		Hlong winId;
	
	public:
		void dev_display_ncc_matching_results(HTuple hv_ModelID, HTuple hv_Color, HTuple hv_Row,
			HTuple hv_Column, HTuple hv_Angle, HTuple hv_Model);

		void dev_open_window_fit_image(HObject ho_Image, HTuple hv_Row, HTuple hv_Column,
			HTuple hv_WidthLimit, HTuple hv_HeightLimit, HTuple *hv_WindowHandle);
 
		void dev_update_off();

		void disp_continue_message(HTuple hv_WindowHandle, HTuple hv_Color, HTuple hv_Box);

		void disp_message(HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem,
			HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box);

		void set_display_font(HTuple hv_WindowHandle, HTuple hv_Size, HTuple hv_Font, HTuple hv_Bold,
			HTuple hv_Slant);

		int read_image();

		void init_windows();

		void ho_Image_show();
		
		void ho_Image1_show();

		void circle_Image_show();
};