#pragma once
#include "iobserver.h"

class CLiSiObserver :
	public IObserver
{
public:
	CLiSiObserver(void);
	~CLiSiObserver(void);
	void Update(string context);
	string GetName();
private:
	void ReportToQinShiHuang(string report);
};