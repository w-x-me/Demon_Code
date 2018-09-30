#pragma once
#include "igroup.h"
class CRequirementGroup :
	public IGroup
{
public:
	CRequirementGroup(void);
	~CRequirementGroup(void);
	void Find();
	void Add();
	void Delete();
	void Change();
	void Plan();
};