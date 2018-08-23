#include "template_macth.h"
#include<qdebug>
#pragma execution_character_set("utf-8") 
Template_Macth::Template_Macth(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.Image_Show_label->setScaledContents(true);
	//ui.Image_Show_label_2->setScaledContents(true);
	connect(this, SIGNAL(ho_Image_show_signal(int)), this, SLOT(ho_Image_show(int)));
	connect(this, SIGNAL(init_windows_signal(QString)), this, SLOT(init_windows(QString)));
	connect(this, SIGNAL(circle_Image_show_signal(int, QString)), this, SLOT(circle_Image_show(int, QString)));


}
void Template_Macth::Template_Macth_Method()
{
	HalconCpp::HObject  ho_ModelImage, ho_ROIPart1, ho_ROIPart2;
	HalconCpp::HObject  ho_ModelROI, ho_ImageROI, ho_ShapeModelImage, ho_ShapeModelRegion;
	HalconCpp::HObject  ho_ShapeModel, ho_MeasureROI1, ho_MeasureROI2, ho_MeasureROI1Ref;
	HalconCpp::HObject  ho_MeasureROI2Ref, ho_SearchImage, ho_ModelAtNewPosition;
	HalconCpp::HObject  ho_MeasureROI1AtNewPosition, ho_MeasureROI2AtNewPosition;

	HalconCpp::HTuple  hv_USING_TRANSLATE_MEASURE, hv_Pointer;
	HalconCpp::HTuple  hv_Type, hv_Width, hv_Height, hv_WindowHandle, hv_Row1;
	HalconCpp::HTuple  hv_Column1, hv_Row2, hv_Column2, hv_Area, hv_CenterROIRow;
	HalconCpp::HTuple  hv_CenterROIColumn, hv_ModelID, hv_Rect1Row, hv_Rect1Col;
	HalconCpp::HTuple  hv_DistColRect1Rect2, hv_Rect2Row, hv_Rect2Col;
	HalconCpp::HTuple  hv_RectPhi, hv_RectLength1, hv_RectLength2, hv_OriginalClipRegion;
	HalconCpp::HTuple  hv_DistRect1CenterRow, hv_DistRect1CenterCol, hv_DistRect2CenterRow;
	HalconCpp::HTuple  hv_DistRect2CenterCol, hv_MeasureHandle1, hv_MeasureHandle2;
	HalconCpp::HTuple  hv_RowCheck, hv_ColumnCheck, hv_AngleCheck, hv_Score;
	HalconCpp::HTuple  hv_i, hv_MovementOfObject, hv_Rect1RowCheck, hv_Rect1ColCheck;
	HalconCpp::HTuple  hv_Rect2RowCheck, hv_Rect2ColCheck, hv_RowEdge11;
	HalconCpp::HTuple  hv_ColEdge11, hv_Amp11, hv_RowEdge21, hv_ColEdge21;
	HalconCpp::HTuple  hv_Amp21, hv_Width1, hv_Distance1, hv_RowEdge12;
	HalconCpp::HTuple  hv_ColEdge12, hv_Amp12, hv_RowEdge22, hv_ColEdge22;
	HalconCpp::HTuple  hv_Amp22, hv_Width2, hv_Distance2, hv_RectPhiCheck;
	HalconCpp::HTuple  hv_NumberTeeth1, hv_NumberTeeth2, hv_j, hv_RowFault;
	HalconCpp::HTuple  hv_ColFault, hv_WindowHandleZoom;

	hv_USING_TRANSLATE_MEASURE = 0;

	Hlong winId=(Hlong)ui.Image_Show_label->winId();
	ReadImage(&ho_ModelImage, "razors1");
	GetImagePointer1(ho_ModelImage, &hv_Pointer, &hv_Type, &hv_Width, &hv_Height);
	if (HalconCpp::HDevWindowStack::IsOpen())
		CloseWindow(HalconCpp::HDevWindowStack::Pop());
	HalconCpp::SetWindowAttr("background_color", "white");
	OpenWindow(0, 0, hv_Width, hv_Height, winId, "visible", "", &hv_WindowHandle);
	HalconCpp::HDevWindowStack::Push(hv_WindowHandle);
	if (HalconCpp::HDevWindowStack::IsOpen())
		SetPart(HalconCpp::HDevWindowStack::GetActive(), 0, 0, hv_Height - 1, hv_Width - 1);
	if (HalconCpp::HDevWindowStack::IsOpen())
		DispObj(ho_ModelImage, HalconCpp::HDevWindowStack::GetActive());

	if (HalconCpp::HDevWindowStack::IsOpen())
		HalconCpp::SetColor(HalconCpp::HDevWindowStack::GetActive(), "cyan");
	if (HalconCpp::HDevWindowStack::IsOpen())
		HalconCpp::SetDraw(HalconCpp::HDevWindowStack::GetActive(), "margin");
	if (HalconCpp::HDevWindowStack::IsOpen())
		HalconCpp::SetLineWidth(HalconCpp::HDevWindowStack::GetActive(), 2);

	hv_Row1 = 46;
	hv_Column1 = 57;
	hv_Row2 = 79;
	hv_Column2 = 94;
	GenRectangle1(&ho_ROIPart1, hv_Row1, hv_Column1, hv_Row2, hv_Column2);
	GenRectangle1(&ho_ROIPart2, hv_Row1 + 364, hv_Column1 + 13, hv_Row2 + 364, hv_Column2 + 13);
	Union2(ho_ROIPart1, ho_ROIPart2, &ho_ModelROI);
	AreaCenter(ho_ModelROI, &hv_Area, &hv_CenterROIRow, &hv_CenterROIColumn);
	if (HalconCpp::HDevWindowStack::IsOpen())
		DispObj(ho_ModelImage, HalconCpp::HDevWindowStack::GetActive());
	if (HalconCpp::HDevWindowStack::IsOpen())
		DispObj(ho_ModelROI, HalconCpp::HDevWindowStack::GetActive());
	// stop(...); only in hdevelop
	//-> create the model
	ReduceDomain(ho_ModelImage, ho_ModelROI, &ho_ImageROI);
	CreateShapeModel(ho_ImageROI, 4, 0, 0, "auto", "none", "use_polarity", 30, 10,
		&hv_ModelID);
	InspectShapeModel(ho_ImageROI, &ho_ShapeModelImage, &ho_ShapeModelRegion, 1, 30);
	GetShapeModelContours(&ho_ShapeModel, hv_ModelID, 1);
	if (HalconCpp::HDevWindowStack::IsOpen())
		HalconCpp::ClearWindow(HalconCpp::HDevWindowStack::GetActive());
	if (HalconCpp::HDevWindowStack::IsOpen())
		HalconCpp::SetColor(HalconCpp::HDevWindowStack::GetActive(), "blue");
	if (HalconCpp::HDevWindowStack::IsOpen())
		DispObj(ho_ShapeModelRegion, HalconCpp::HDevWindowStack::GetActive());
	// stop(...); only in hdevelop
	//step 1: create variables describing  the measurement ROIs and display them
	hv_Rect1Row = 244;
	hv_Rect1Col = 73;
	hv_DistColRect1Rect2 = 17;
	hv_Rect2Row = hv_Rect1Row;
	hv_Rect2Col = hv_Rect1Col + hv_DistColRect1Rect2;
	hv_RectPhi = HalconCpp::HTuple(90).TupleRad();
	hv_RectLength1 = 122;
	hv_RectLength2 = 2;
	GenRectangle2(&ho_MeasureROI1, hv_Rect1Row, hv_Rect1Col, hv_RectPhi, hv_RectLength1,
		hv_RectLength2);
	GenRectangle2(&ho_MeasureROI2, hv_Rect2Row, hv_Rect2Col, hv_RectPhi, hv_RectLength1,
		hv_RectLength2);
	if (HalconCpp::HDevWindowStack::IsOpen())
		DispObj(ho_ModelImage, HalconCpp::HDevWindowStack::GetActive());
	if (HalconCpp::HDevWindowStack::IsOpen())
		HalconCpp::SetColor(HalconCpp::HDevWindowStack::GetActive(), "yellow");
	if (HalconCpp::HDevWindowStack::IsOpen())
		DispObj(ho_MeasureROI1, HalconCpp::HDevWindowStack::GetActive());
	if (HalconCpp::HDevWindowStack::IsOpen())
		DispObj(ho_MeasureROI2, HalconCpp::HDevWindowStack::GetActive());
	//translate measurement ROIs to lie on XLD model (without clipping!)
	GetSystem("clip_region", &hv_OriginalClipRegion);
	HalconCpp::SetSystem("clip_region", "false");
	MoveRegion(ho_MeasureROI1, &ho_MeasureROI1Ref, -hv_CenterROIRow, -hv_CenterROIColumn);
	MoveRegion(ho_MeasureROI2, &ho_MeasureROI2Ref, -hv_CenterROIRow, -hv_CenterROIColumn);
	SetSystem("clip_region", hv_OriginalClipRegion);
	hv_DistRect1CenterRow = hv_Rect1Row - hv_CenterROIRow;
	hv_DistRect1CenterCol = hv_Rect1Col - hv_CenterROIColumn;
	hv_DistRect2CenterRow = hv_Rect2Row - hv_CenterROIRow;
	hv_DistRect2CenterCol = hv_Rect2Col - hv_CenterROIColumn;
	if (0 != (hv_USING_TRANSLATE_MEASURE != 0))
	{
		//-> measure objects are created only once in advance and then translated later
		GenMeasureRectangle2(hv_Rect1Row, hv_Rect1Col, hv_RectPhi, hv_RectLength1, hv_RectLength2,
			hv_Width, hv_Height, "bilinear", &hv_MeasureHandle1);
		GenMeasureRectangle2(hv_Rect2Row, hv_Rect2Col, hv_RectPhi, hv_RectLength1, hv_RectLength2,
			hv_Width, hv_Height, "bilinear", &hv_MeasureHandle2);
	}
	// stop(...); only in hdevelop
	//step 2: find the objects in another image
	ReadImage(&ho_SearchImage, "razors2");
	if (HalconCpp::HDevWindowStack::IsOpen())
		DispObj(ho_SearchImage, HalconCpp::HDevWindowStack::GetActive());
	FindShapeModel(ho_SearchImage, hv_ModelID, 0, 0, 0.8, 0, 0.5, "least_squares",
		0, 0.7, &hv_RowCheck, &hv_ColumnCheck, &hv_AngleCheck, &hv_Score);
	if (0 != ((hv_Score.TupleLength())>0))
	{
		{
			HalconCpp::HTuple end_val80 = (hv_Score.TupleLength()) - 1;
			HalconCpp::HTuple step_val80 = 1;
			for (hv_i = 0; hv_i.Continue(end_val80, step_val80); hv_i += step_val80)
			{
				//step 3: determine the affine transformation
				VectorAngleToRigid(0, 0, 0, HalconCpp::HTuple(hv_RowCheck[hv_i]), HalconCpp::HTuple(hv_ColumnCheck[hv_i]),
					HalconCpp::HTuple(hv_AngleCheck[hv_i]), &hv_MovementOfObject);
				AffineTransContourXld(ho_ShapeModel, &ho_ModelAtNewPosition, hv_MovementOfObject);
				if (HalconCpp::HDevWindowStack::IsOpen())
					DispObj(ho_ModelAtNewPosition, HalconCpp::HDevWindowStack::GetActive());
				//step 4: measure width and distance of the teeth
				//-> display the moved ROIs
				AffineTransRegion(ho_MeasureROI1Ref, &ho_MeasureROI1AtNewPosition, hv_MovementOfObject,
					"constant");
				AffineTransRegion(ho_MeasureROI2Ref, &ho_MeasureROI2AtNewPosition, hv_MovementOfObject,
					"constant");
				if (HalconCpp::HDevWindowStack::IsOpen())
					DispObj(ho_MeasureROI1AtNewPosition, HalconCpp::HDevWindowStack::GetActive());
				if (HalconCpp::HDevWindowStack::IsOpen())
					DispObj(ho_MeasureROI2AtNewPosition, HalconCpp::HDevWindowStack::GetActive());
				AffineTransPixel(hv_MovementOfObject, hv_DistRect1CenterRow, hv_DistRect1CenterCol,
					&hv_Rect1RowCheck, &hv_Rect1ColCheck);
				AffineTransPixel(hv_MovementOfObject, hv_DistRect2CenterRow, hv_DistRect2CenterCol,
					&hv_Rect2RowCheck, &hv_Rect2ColCheck);
				if (0 != (hv_USING_TRANSLATE_MEASURE != 0))
				{
					//-> translate the already created measure objects
					TranslateMeasure(hv_MeasureHandle1, hv_Rect1RowCheck, hv_Rect1ColCheck);
					TranslateMeasure(hv_MeasureHandle2, hv_Rect2RowCheck, hv_Rect2ColCheck);
					MeasurePairs(ho_SearchImage, hv_MeasureHandle1, 2, 25, "negative", "all",
						&hv_RowEdge11, &hv_ColEdge11, &hv_Amp11, &hv_RowEdge21, &hv_ColEdge21,
						&hv_Amp21, &hv_Width1, &hv_Distance1);
					MeasurePairs(ho_SearchImage, hv_MeasureHandle2, 2, 25, "negative", "all",
						&hv_RowEdge12, &hv_ColEdge12, &hv_Amp12, &hv_RowEdge22, &hv_ColEdge22,
						&hv_Amp22, &hv_Width2, &hv_Distance2);
				}
				else
				{
					//-> create new measure objects and destroy them after the measurement
					hv_RectPhiCheck = hv_RectPhi + HalconCpp::HTuple(hv_AngleCheck[hv_i]);
					GenMeasureRectangle2(hv_Rect1RowCheck, hv_Rect1ColCheck, hv_RectPhiCheck,
						hv_RectLength1, hv_RectLength2, hv_Width, hv_Height, "bilinear", &hv_MeasureHandle1);
					GenMeasureRectangle2(hv_Rect2RowCheck, hv_Rect2ColCheck, hv_RectPhiCheck,
						hv_RectLength1, hv_RectLength2, hv_Width, hv_Height, "bilinear", &hv_MeasureHandle2);
					//step 5: perform the measurement
					MeasurePairs(ho_SearchImage, hv_MeasureHandle1, 2, 25, "negative", "all",
						&hv_RowEdge11, &hv_ColEdge11, &hv_Amp11, &hv_RowEdge21, &hv_ColEdge21,
						&hv_Amp21, &hv_Width1, &hv_Distance1);
					MeasurePairs(ho_SearchImage, hv_MeasureHandle2, 2, 25, "negative", "all",
						&hv_RowEdge12, &hv_ColEdge12, &hv_Amp12, &hv_RowEdge22, &hv_ColEdge22,
						&hv_Amp22, &hv_Width2, &hv_Distance2);
					CloseMeasure(hv_MeasureHandle1);
					CloseMeasure(hv_MeasureHandle2);
				}
				//step 6: check for too short or missing teeth
				hv_NumberTeeth1 = hv_Width1.TupleLength();
				hv_NumberTeeth2 = hv_Width2.TupleLength();
				if (HalconCpp::HDevWindowStack::IsOpen())
					HalconCpp::SetColor(HalconCpp::HDevWindowStack::GetActive(), "red");
				if (0 != (hv_NumberTeeth1<37))
				{
					{
						HalconCpp::HTuple end_val115 = hv_NumberTeeth1 - 2;
						HalconCpp::HTuple step_val115 = 1;
						for (hv_j = 0; hv_j.Continue(end_val115, step_val115); hv_j += step_val115)
						{
							if (0 != (HalconCpp::HTuple(hv_Distance1[hv_j])>4.0))
							{
								hv_RowFault = (0.5*(HalconCpp::HTuple(hv_RowEdge11[hv_j + 1]) + HalconCpp::HTuple(hv_RowEdge21[hv_j]))).TupleRound();
								hv_ColFault = (0.5*(HalconCpp::HTuple(hv_ColEdge11[hv_j + 1]) + HalconCpp::HTuple(hv_ColEdge21[hv_j]))).TupleRound();
								DispRectangle2(hv_WindowHandle, hv_RowFault, hv_ColFault, 0, 4, 4);
								HalconCpp::SetWindowAttr("background_color", "black");
								OpenWindow(0, hv_Width + 20, 80, 80, 0, "visible", "", &hv_WindowHandleZoom);
								HalconCpp::HDevWindowStack::Push(hv_WindowHandleZoom);
								if (HalconCpp::HDevWindowStack::IsOpen())
									SetPart(HalconCpp::HDevWindowStack::GetActive(), hv_RowFault - 10, hv_ColFault - 10,
									hv_RowFault + 10, hv_ColFault + 10);
								if (HalconCpp::HDevWindowStack::IsOpen())
									DispObj(ho_SearchImage, HalconCpp::HDevWindowStack::GetActive());
								DispRectangle2(hv_WindowHandleZoom, hv_RowFault, hv_ColFault, 0, 4, 4);
								// stop(...); only in hdevelop
								if (HalconCpp::HDevWindowStack::IsOpen())
									CloseWindow(HalconCpp::HDevWindowStack::Pop());
								if (HalconCpp::HDevWindowStack::IsOpen())
									SetPart(HalconCpp::HDevWindowStack::GetActive(), 0, 0, hv_Height - 1, hv_Width - 1);
							}
						}
					}
				}
				if (0 != (hv_NumberTeeth2<37))
				{
					{
						HalconCpp::HTuple end_val131 = hv_NumberTeeth2 - 2;
						HalconCpp::HTuple step_val131 = 1;
						for (hv_j = 0; hv_j.Continue(end_val131, step_val131); hv_j += step_val131)
						{
							if (0 != (HalconCpp::HTuple(hv_Distance2[hv_j])>4.0))
							{
								hv_RowFault = (0.5*(HalconCpp::HTuple(hv_RowEdge12[hv_j + 1]) + HalconCpp::HTuple(hv_RowEdge22[hv_j]))).TupleRound();
								hv_ColFault = (0.5*(HalconCpp::HTuple(hv_ColEdge12[hv_j + 1]) + HalconCpp::HTuple(hv_ColEdge22[hv_j]))).TupleRound();
								DispRectangle2(hv_WindowHandle, hv_RowFault, hv_ColFault, 0, 4, 4);
								HalconCpp::SetWindowAttr("background_color", "black");
								OpenWindow(0, hv_Width + 20, 80, 80, 0, "visible", "", &hv_WindowHandleZoom);
								HalconCpp::HDevWindowStack::Push(hv_WindowHandleZoom);
								if (HalconCpp::HDevWindowStack::IsOpen())
									SetPart(HalconCpp::HDevWindowStack::GetActive(), hv_RowFault - 10, hv_ColFault - 10,
									hv_RowFault + 10, hv_ColFault + 10);
								if (HalconCpp::HDevWindowStack::IsOpen())
									DispObj(ho_SearchImage, HalconCpp::HDevWindowStack::GetActive());
								DispRectangle2(hv_WindowHandleZoom, hv_RowFault, hv_ColFault, 0, 4, 4);
								// stop(...); only in hdevelop
								if (HalconCpp::HDevWindowStack::IsOpen())
									CloseWindow(HalconCpp::HDevWindowStack::Pop());
								if (HalconCpp::HDevWindowStack::IsOpen())
									SetPart(HalconCpp::HDevWindowStack::GetActive(), 0, 0, hv_Height - 1, hv_Width - 1);
							}
						}
					}
				}
				if (HalconCpp::HDevWindowStack::IsOpen())
					HalconCpp::SetColor(HalconCpp::HDevWindowStack::GetActive(), "yellow");
				// stop(...); only in hdevelop
			}
		}
	}
	//-------------------  end of the application  -----------------
	//clean up
	if (0 != (hv_USING_TRANSLATE_MEASURE != 0))
	{
		CloseMeasure(hv_MeasureHandle1);
		CloseMeasure(hv_MeasureHandle2);
	}
	// dev_update_window(...); only in hdevelop
	ClearShapeModel(hv_ModelID);
}

void Template_Macth::Template_Macth1_Method()
{
	qDebug() << "调用相关性匹配方法" << endl;
	FNCME.winId = (Hlong)ui.Image_Show_label->winId();
	FNCME.read_image();
	int a = 200;
	emit init_windows_signal("init");
	Sleep(2000);
	//FNCME.winId = (Hlong)ui.Image_Show_label_2->winId();
	emit ho_Image_show_signal(200);
	Sleep(2000);
	emit circle_Image_show_signal(300,"bbb");
	/*if (HDevWindowStack::IsOpen())
		CloseWindow(HDevWindowStack::Pop());*/

	//png = QPixmap('D:/codeWorkSpace/Edgin_machine/1.jpg').scaled(self.Pic_Val.width(), self.Pic_Val.height())
		//self.Pic_Val.setPixmap(png)
	/*ui.Image_Show_label->setPixmap(QPixmap("1.bmp").scaled(ui.Image_Show_label->width(), ui.Image_Show_label->height()));
	Sleep(5000);
	ui.centralWidget->update();
	ui.Image_Show_label_2->setPixmap(QPixmap("9.bmp").scaled(ui.Image_Show_label->width(), ui.Image_Show_label->height()));
	Sleep(1000);
	ui.Image_Show_label->setPixmap(QPixmap("2.bmp").scaled(ui.Image_Show_label->width(), ui.Image_Show_label->height()));*/
}

void Template_Macth::ho_Image_show(int a)
{
	qDebug() << "a：" << a << endl;
	FNCME.init_windows();
	FNCME.ho_Image_show();
	
}
void Template_Macth::init_windows(QString str)
{
	qDebug() << "str：" << str << endl;
	FNCME.init_windows();
	
	
}
void Template_Macth::circle_Image_show(int b, QString bstr)
{
	qDebug() << "bstr：" << bstr << endl;
	qDebug() << "b：" << b << endl;
	FNCME.circle_Image_show();
}

void Template_Macth::Template_Macth2_Method()
{
	qDebug() << "调用相关性匹配方法2" << endl;
	ui.Image_Show_label->setScaledContents(true);
	FNCME.winId = (Hlong)ui.Image_Show_label->winId();
	Timer = startTimer(500);
	index = 0;
}
void Template_Macth::timerEvent(QTimerEvent*)
{
	Start();
}

void Template_Macth::Start()
{
	if (index == 0)
	{
		FNCME.read_image();
		
	}
	if (index == 1)
	{
		FNCME.init_windows();
	}
	if (index == 2)
	{
		FNCME.ho_Image1_show();
	}
	if (index == 3)
	{
		FNCME.ho_Image_show();
	}
	if (index == 4)
	{
		FNCME.circle_Image_show();
	}
	if (index == 5)
	{
		if (Timer != -1)
		{
			killTimer(Timer);
			Timer = -1;
		}
	}
	index += 1;
}

Template_Macth::~Template_Macth()
{
	
}
