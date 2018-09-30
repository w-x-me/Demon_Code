#pragma once
#include "igroup.h"
class CPageGroup :
	public IGroup
{
public:
	CPageGroup(void);
	~CPageGroup(void);
	void Find();
	void Add();
	void Delete();
	void Change();
	void Plan();
};