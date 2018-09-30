#include "OpenningState.h"
#include "Context.h"


COpenningState::COpenningState(void)
{
	cout << "COpenningState" << endl;
}

COpenningState::~COpenningState(void)
{
	cout << "~COpenningState" << endl;
}

void COpenningState::Open()
{
	cout << "µçÌÝÃÅ¿ªÆô..." << endl;
}

void COpenningState::Close()
{
	this->CLiftState::m_pContext->SetLiftState(CContext::pCloseingState);
	this->CLiftState::m_pContext->GetLiftState()->Close();
}

void COpenningState::Run()
{
	this->CLiftState::m_pContext->SetLiftState(CContext::pRunningState);
	this->CLiftState::m_pContext->GetLiftState()->Run();
}

void COpenningState::Stop()
{
	this->CLiftState::m_pContext->SetLiftState(CContext::pStoppingState);
	this->CLiftState::m_pContext->GetLiftState()->Close();
}