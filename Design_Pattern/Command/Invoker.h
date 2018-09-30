#pragma once
#include "ICommand.h"
class CInvoker
{
public:
	CInvoker(void);
	~CInvoker(void);
	void SetCommand(ICommand *pcommand);
	void Action();
private:
	ICommand *m_pCommand;
};