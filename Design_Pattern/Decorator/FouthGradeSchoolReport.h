#pragma once
#include "ischoolreport.h"
class CFouthGradeSchoolReport :
	public ISchoolReport
{
public:
	CFouthGradeSchoolReport(void);
	~CFouthGradeSchoolReport(void);
	void Report();
	void Sign(string name);
};