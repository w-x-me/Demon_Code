#pragma once
#include <string>
#include "HalconCpp.h"
#include<QString>
#include"sfr-method.h"
using namespace HalconCpp;

class CameraDetection
{
public:
	CameraDetection();
	~CameraDetection();
public:
	std::string img_file;
	SfrMethod sfr_method;
	int camera_number;
	int centerx = 0;
	int centery = 0;
	int width = 0;
	int height = 0;
	bool g_IsFFCInited = false;
	HTuple g_ffc_hv_ModelID;
	HObject g_ffc_ho_Region;

	bool g_IsRFCInited = false;
	HTuple g_rfc_hv_ModelID;
	HObject g_rfc_ho_Region;

public:
	
	QString Result_Show(QString file_name, double result);

	void Blemish(double& param);

	void RI(double& param);

	void DeadPixel(double& param);

	void FFC_SFR(double& param);

	void Rotation(double& param);

	void Tilt(double& param);

	void FOV(double& param);

	void BG(double& param);

	void RG(double& param);

	void SFR(double& param);


	/*typedef struct MyStruct
	{
		double dx;
		double dy;
	}pStruct;*/

	/*void FFC_Move(pStruct &p);
	void RFC_Move(pStruct &p);*/



};