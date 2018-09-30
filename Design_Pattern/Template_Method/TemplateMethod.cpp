#include "HummerModel.h"
#include "HummerH1Model.h"
#include "HummerH2Model.h"
#include <crtdbg.h>
int main()
{
	//客户开着H1型号，出去遛弯了gan
	CHummerModel *ph1 = new CHummerH1Model();
	ph1->Run();
	delete ph1;

	//客户开H2型号，出去玩耍了
	CHummerModel *ph2 = new CHummerH2Model();
	ph2->Run();
	delete ph2;

	//客户开着H1型号，出去遛弯了，并且不让喇叭响
	CHummerH1Model *ph11 = new CHummerH1Model();
	ph11->SetAlarm(false);
	ph11->Run();
	delete ph11;

	system("pause");

	return 0;
}