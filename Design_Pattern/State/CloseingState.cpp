#include "CloseingState.h"
#include "Context.h"
CCloseingState::CCloseingState(void)
{
	cout << "CCloseingState" << endl;
}

CCloseingState::~CCloseingState(void)
{
	cout << "~CCloseingState" << endl;
}

void CCloseingState::Open()
{
	//调用CContext中的SetLiftState;
	this->CLiftState::m_pContext->SetLiftState(CContext::pOpenningState);
	
	this->CLiftState::m_pContext->GetLiftState()->Open();
}

void CCloseingState::Close()
{
	cout << "电梯门关闭..." << endl;
}

void CCloseingState::Run()
{
	this->CLiftState::m_pContext->SetLiftState(CContext::pRunningState);
	this->CLiftState::m_pContext->GetLiftState()->Run();
}

void CCloseingState::Stop()
{
	this->CLiftState::m_pContext->SetLiftState(CContext::pStoppingState);
	this->CLiftState::m_pContext->GetLiftState()->Stop();
}