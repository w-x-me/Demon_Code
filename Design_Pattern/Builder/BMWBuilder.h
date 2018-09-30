#pragma once
#include "icarbuilder.h"
#include "CarModel.h"
using std::string;
using std::vector;
class CBMWBuilder :
	public ICarBuilder
{
public:
	CBMWBuilder(void);
	~CBMWBuilder(void);
	void SetSequence(vector<string> *pSeq);
	CCarModel * GetCarModel();
private:
	CCarModel *m_pBMW;
};