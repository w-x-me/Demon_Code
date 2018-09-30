#include "RunningState.h"
#include"Context.h"
CRunningState::CRunningState(void)
{
	cout << "CRunningState" << endl;
}

CRunningState::~CRunningState(void)
{
	cout << "~CRunningState" << endl;
}

void CRunningState::Open()
{
	//do nothing
}

void CRunningState::Close()
{
	//do nothing
}

void CRunningState::Run()
{
	cout << "µçÌÝÉÏÏÂÅÜ..." << endl;
}

void CRunningState::Stop()
{
	this->CLiftState::m_pContext->SetLiftState(CContext::pStoppingState);
	this->CLiftState::m_pContext->GetLiftState()->Stop();
}