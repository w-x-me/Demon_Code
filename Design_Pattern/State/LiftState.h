#pragma once
class CContext;
class CLiftState
{
public:
	CLiftState(void);
	virtual ~CLiftState(void);
	void SetContext(CContext *pContext);
	virtual void Open() = 0;
	virtual void Close() = 0;
	virtual void Run() = 0;
	virtual void Stop() = 0;
protected:
	CContext *m_pContext;
};