#include "BenzBuilder.h"
#include "BenzModel.h"
CBenzBuilder::CBenzBuilder(void)
{
	m_pBenz = new CBenzModel();
}
CBenzBuilder::~CBenzBuilder(void)
{
	delete m_pBenz;
}
void CBenzBuilder::SetSequence(vector<string> *pSeq)
{
	m_pBenz->SetSequence(pSeq);
}
CCarModel * CBenzBuilder::GetCarModel()
{
	return m_pBenz;
}