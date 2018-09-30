
#include "MaleHumanFactory.h"
template<class T>
CMaleHumanFactory<T>::CMaleHumanFactory(void)
{
}
template<class T>
CMaleHumanFactory<T>::~CMaleHumanFactory(void)
{
}
template<class T>
IHuman * CMaleHumanFactory<T>::CreateYellowHuman()
{
	return CreateHuman();
}
template<class T>
IHuman * CMaleHumanFactory<T>::CreateWhiteHuman()
{
	return CreateHuman();
}

