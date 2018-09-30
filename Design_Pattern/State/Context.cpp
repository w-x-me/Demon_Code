#include"Context.h"
#include<iostream>
using namespace std;
COpenningState* CContext::pOpenningState = NULL;
CCloseingState* CContext::pCloseingState = NULL;
CRunningState* CContext::pRunningState = NULL;
CStoppingState* CContext::pStoppingState = NULL;

CContext::CContext(void)
{
	m_pLiftState = NULL;
	pOpenningState = new COpenningState();
	pCloseingState = new CCloseingState();
	pRunningState = new CRunningState();
	pStoppingState = new CStoppingState();
	cout << "CContext" << endl;
}

CContext::~CContext(void)
{
	delete pOpenningState;
	pOpenningState = NULL;
	delete pCloseingState;
	pCloseingState = NULL;
	delete pRunningState;
	pRunningState = NULL;
	delete pStoppingState;
	pStoppingState = NULL;
	cout << "~CContext" << endl;
}

CLiftState * CContext::GetLiftState()
{
	return m_pLiftState;
}

//依据传入的指针，改变基类指针的指向，从而判断具体调用方法。
void CContext::SetLiftState(CLiftState *pLiftState)
{
	//第一次传入进来的的CCloseingState，基类CLiftStateat的m_pLiftState指针指向CCloseingState
	this->m_pLiftState = pLiftState;//让基类指针指向子类对象，调用子类的方法
	this->m_pLiftState->SetContext(this); //调用基类CLiftStateat的SetContext方法，初始化m_pContext；
}

void CContext::Open()
{
	//m_pLiftState指针指向CCloseingState
	this->m_pLiftState->Open();
	//执行完后m_pLiftState指针指向COpenningState
}

void CContext::Close()
{
	//m_pLiftState指针指向CCloseingState
	this->m_pLiftState->Close();//调用CloseingState的Close方法
	//执行完后m_pLiftState指针指向COpenningState
}

void CContext::Run()
{
	//m_pLiftState指针指向COpenningState
	this->m_pLiftState->Run();
	//执行完后m_pLiftState指针指向CRunningState
}

void CContext::Stop()
{
	//m_pLiftState指针指向CRunningState
	this->m_pLiftState->Stop();
	//执行完后m_pLiftState指针指向CStoppingState
}