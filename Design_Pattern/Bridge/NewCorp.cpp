#include "NewCorp.h"
CNewCorp::CNewCorp(IProduct *pproduct)
{
	this->m_pProduct = pproduct;//根据传入的参数，确定基类指向的方向
}
CNewCorp::~CNewCorp(void)
{
}
void CNewCorp::MakeMoney()
{
	//每个公司都是一样，先生产
	this->m_pProduct->BeProducted();

	//然后销售
	this->m_pProduct->BeSelled();
}