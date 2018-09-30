#include "CarModel.h"
CCarModel::CCarModel(void)
{
}
CCarModel::~CCarModel(void)
{
}
void CCarModel::SetSequence(vector<string> *pSeq)
{
	m_pSequence = pSeq;
}
void CCarModel::Run()
{
	vector<string>::const_iterator it = m_pSequence->begin();
	for (; it < m_pSequence->end(); ++it)
	{
		string actionName = *it;
		if (actionName.compare("start") == 0)
		{
			Start();//哪个子类调用此方法，就指向哪个子类的方法，下同
		}
		else if (actionName.compare("stop") == 0)
		{
			Stop();
		}
		else if (actionName.compare("alarm") == 0)
		{
			Alarm();
		}
		else if (actionName.compare("engine boom") == 0)
		{
			EngineBoom();
		}
	}
}