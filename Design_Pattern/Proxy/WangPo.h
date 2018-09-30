#pragma once
#include "IKindWomen.h"
class WangPo : public IKindWomen
{
public:
	WangPo(IKindWomen *pKindWomen);
	~WangPo(void);
	void HappyWithMan(void);
	void MakeEyesWithMan(void);
private:
	IKindWomen *m_kindwomen;
};