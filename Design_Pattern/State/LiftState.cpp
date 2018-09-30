#include "LiftState.h"
#include<iostream>
using namespace std;
CLiftState::CLiftState(void)
{
	cout << "CLiftState" << endl;
}

CLiftState::~CLiftState(void)
{
	cout << "~CLiftState" << endl;
}

void CLiftState::SetContext(CContext *pContext)
{
	m_pContext = pContext;
}