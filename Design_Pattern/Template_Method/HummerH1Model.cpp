#include "HummerH1Model.h"

CHummerH1Model::CHummerH1Model(void)
{
	m_isAlarm = true;
}
CHummerH1Model::~CHummerH1Model(void)
{
}
void CHummerH1Model::Start()
{
	cout << "悍马H1发动..." << endl;
}
void CHummerH1Model::Stop()
{
	cout << "悍马H1停车..." << endl;
}
void CHummerH1Model::Alarm()
{
	cout << "悍马H1鸣笛" << endl;
}
void CHummerH1Model::EngineBoom()
{
	cout << "悍马H1引擎声音是这样...." << endl;
}
bool CHummerH1Model::IsAlarm()
{
	return this->m_isAlarm;
}
void CHummerH1Model::SetAlarm(bool tag)
{
	this->m_isAlarm = tag;
}