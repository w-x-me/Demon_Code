#pragma once
#include "icommand.h"
class CDeletePageCommand :
	public ICommand
{
public:
	CDeletePageCommand(void);
	~CDeletePageCommand(void);
	void Execute();
};