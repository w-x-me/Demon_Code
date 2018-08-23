/*****************************************************************************
* bottle2.cpp
*****************************************************************************
*
* Project:      HALCON/C++
* Description:  Example program for HALCON/C++
*
* (c) 2002      by MVTec Software GmbH
*               www.mvtec.com
*****************************************************************************
*
* Segmentation and OCR of numbers on a beer bottle
* (see also ../../hdevelop/Applications/OCR/bottle2.dev)
*
****************************************************************************/

#include "HalconCpp.h"
using namespace HalconCpp;

// There are three ways for calling the OCR operator:
//   first, calling the method of the HOCR instance
//   second, calling the appropriate method of the HImage(Array)
//   third, calling the global methods
// Uncomment the following #define statement to use the first method,
// comment it to run the second way
#define USE_TOOL_CLASS

HBool singleStep = H_FALSE;
HBool useDisplay = H_TRUE;


void action()
{
	HOCRMlp    hOCRMlp;
	hOCRMlp.ReadOcrClassMlp("bottle");

	HImage  hImBottle("bottle2");
	int     width = hImBottle.Width();
	int     height = hImBottle.Height();
	HWindow hWindow("");
	if (useDisplay)
	{
		HTuple OpSys;
		::get_system("operating_system", &OpSys);
		hWindow.OpenWindow(0, 0, width, height);
		hWindow.SetPart(0, 0, height - 1, width - 1);
		hWindow.SetFont(OpSys.Substring(0, 2) == "Win" ?
			"-Arial-26-*-*-*-*-*-" :
			"-*-courier-*-*-*-*-26-*-*-*-*-*-*-*");
		hWindow.Display(hImBottle);
		if (singleStep) hWindow.Click();
	}

	HRegion hRegRawSegmentation = hImBottle <= 95; // Threshold(0,95)
	HRegion hRegRemovedNoise = hRegRawSegmentation.FillUpShape("area", 1, 5);
	HRegion hRegThickStructures = hRegRemovedNoise.OpeningCircle(2.5);
	HRegion hRegSolid = hRegThickStructures.FillUp();
	HRegion hRegCut = hRegSolid.OpeningRectangle1(1, 7);
	HRegionArray hRegArrConnectedPatterns = hRegCut.Connection();
	HRegionArray hRegArrNumberCandidates =
		hRegArrConnectedPatterns & hRegThickStructures; // Intersection(..)
	HRegionArray hRegArrNumbers =
		hRegArrNumberCandidates.SelectShape("area", "and", 300, 9999);
	HRegionArray hRegArrFinalNumbers =
		hRegArrNumbers.SortRegion("first_point", "true", "column");

	if (useDisplay)
	{
		hWindow.SetColor("green");
		hWindow.Display(hRegThickStructures);
		if (singleStep) hWindow.Click();
		hWindow.SetDraw("margin");
		hWindow.SetLineWidth(3);
		hWindow.Display(hImBottle);
		hWindow.Display(hRegThickStructures);
		if (singleStep) hWindow.Click();
		hWindow.Display(hImBottle);
		hWindow.Display(hRegSolid);
		if (singleStep) hWindow.Click();
		hWindow.Display(hImBottle);
		hWindow.Display(hRegCut);
		if (singleStep) hWindow.Click();
		hWindow.SetColored(12);
		hWindow.Display(hImBottle);
		hWindow.Display(hRegArrNumberCandidates);
		if (singleStep) hWindow.Click();
		hWindow.SetColor("red");
		hWindow.Display(hImBottle);
		hWindow.Display(hRegArrNumbers);
		hWindow.SetShape("rectangle1");
		hWindow.SetColor("green");
		hWindow.Display(hRegArrFinalNumbers);
		if (singleStep) hWindow.Click();
	}

	HTuple tupRecNum, tupConfidence, tupColNum;
#ifdef USE_TOOL_CLASS  // two alternative methods for using the ocr
	tupRecNum = hOCRMlp.DoOcrMultiClassMlp(hRegArrFinalNumbers, hImBottle, &tupConfidence);
#else
	tupRecNum = hRegArrFinalNumbers.DoOcrMultiClassMlp(hImBottle, hOCRMlp.GetHandle(),
		&tupConfidence);
#endif
	hRegArrFinalNumbers.AreaCenter(NULL, &tupColNum);
	cout << " " << tupRecNum << endl;
	if (useDisplay)
	{
		for (int i = 0; i<tupRecNum.Num(); i++)
		{
			hWindow.SetTposition(75, tupColNum[i]);
			hWindow.WriteString(tupRecNum[i]);
		}
	}
	if (useDisplay)
		hWindow.Click();
}


int main(int argc, char *argv[])
{
	long i, numRuns = 1;
	for (i = 1; i<argc; i++)
	{
		switch (*argv[i])
		{
		case '-':
		case '/':
			switch (argv[i][1])
			{
			case 's':
				singleStep = H_TRUE;
				break;
			case 'd':
				useDisplay = H_FALSE;
				break;
			case 'i':
				if (argv[i][2])
					numRuns = atoi(argv[i] + 2);
				else if (i + 1 < argc && *argv[i + 1] != '-')
					numRuns = atoi(argv[++i]);
				break;
			}
			break;
		}
	}
	for (i = 0; i<numRuns; i++)
		action();
	return 0;
}
