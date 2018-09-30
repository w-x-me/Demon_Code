#pragma once
#include "iobserver.h"
class CZhouSiObserver :
	public IObserver
{
public:
	CZhouSiObserver(void);
	~CZhouSiObserver(void);
	void Update(string context);
	string GetName();
private:
	void Cry(string report);
};