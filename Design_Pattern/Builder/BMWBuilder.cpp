#include "BMWBuilder.h"
#include "BMWModel.h"
CBMWBuilder::CBMWBuilder(void)
{
	m_pBMW = new CBMWModel();
}
CBMWBuilder::~CBMWBuilder(void)
{
	delete m_pBMW;
}
void CBMWBuilder::SetSequence(vector<string> *pSeq)
{
	m_pBMW->SetSequence(pSeq);
}
CCarModel * CBMWBuilder::GetCarModel()
{
	return m_pBMW;
}