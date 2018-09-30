#include "SimpleHumanFactory.h"
#include "YellowHuman.h"
#include "WhiteHuman.h"
#include "BlackHuman.h"

CSimpleHumanFactory::CSimpleHumanFactory(void)
{
}

CSimpleHumanFactory::~CSimpleHumanFactory(void)
{
}

IHuman * CSimpleHumanFactory::CreateHuman(string classType)
{
	if (classType.compare("CYellowHuman") == 0)
	{
		return new CYellowHuman();
	}
	else if (classType.compare("CWhiteHuman") == 0)
	{
		return new CWhiteHuman();
	}
	else if (classType.compare("CBlackHuman") == 0)
	{
		return new CBlackHuman();
	}
}