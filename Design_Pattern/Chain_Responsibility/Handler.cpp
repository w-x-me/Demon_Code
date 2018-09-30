#include "Handler.h"
CHandler::CHandler(int _level) : m_level(_level)
{
	m_pNextHandler = NULL;
}
CHandler::~CHandler(void)
{
}
void CHandler::HandleMessage(IWomen *pwomen)
{
	if (pwomen->GetType() == this->m_level)
	{
		this->Response(pwomen);
	}
	else
	{
		if (this->m_pNextHandler != NULL)
			this->m_pNextHandler->HandleMessage(pwomen);
		else
			cout << "----------没地方请示了，不做处理！----------" << endl;
	}
}
void CHandler::SetNext(CHandler *phandler)
{
	m_pNextHandler = phandler;
}