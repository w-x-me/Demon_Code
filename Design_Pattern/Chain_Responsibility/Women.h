#pragma once
#include "iwomen.h"
class CWomen :
	public IWomen
{
public:
	CWomen(int _type, string _request);
	~CWomen(void);
	int GetType();
	string GetRequest();
private:
	int m_type;
	string m_request;
};