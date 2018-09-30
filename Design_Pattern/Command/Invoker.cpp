#include "Invoker.h"
CInvoker::CInvoker(void)
{
}
CInvoker::~CInvoker(void)
{
}
void CInvoker::SetCommand(ICommand *pcommand)
{
	this->m_pCommand = pcommand;
}
void CInvoker::Action()
{
	this->m_pCommand->Execute();
}