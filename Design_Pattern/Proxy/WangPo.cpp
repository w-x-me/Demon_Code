#include "WangPo.h"
WangPo::WangPo(IKindWomen *pIKindWomen)
{
	this->m_kindwomen = pIKindWomen;
}
WangPo::~WangPo(void)
{
	delete this->m_kindwomen;
}
void WangPo::HappyWithMan()
{
	this->m_kindwomen->HappyWithMan();
}
void WangPo::MakeEyesWithMan()
{
	this->m_kindwomen->MakeEyesWithMan();
}