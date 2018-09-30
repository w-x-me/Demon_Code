#pragma once
#include "icommand.h"
class CAddRequirementCommand :
	public ICommand
{
public:
	CAddRequirementCommand(void);
	~CAddRequirementCommand(void);
	void Execute();
};