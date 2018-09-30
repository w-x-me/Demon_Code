#pragma once
#include "icarbuilder.h"
#include "CarModel.h"

class CBenzBuilder :
	public ICarBuilder
{
public:
	CBenzBuilder(void);
	~CBenzBuilder(void);
	void SetSequence(vector<string> *pSeq);
	CCarModel * GetCarModel();
private:
	CCarModel *m_pBenz;
};