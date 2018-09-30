#include "HummerH2Model.h"

CHummerH2Model::CHummerH2Model(void)
{
}
CHummerH2Model::~CHummerH2Model(void)
{
}
void CHummerH2Model::Start()
{
	cout << "悍马H2发动..." << endl;
}
void CHummerH2Model::Stop()
{
	cout << "悍马H2停车..." << endl;
}
void CHummerH2Model::Alarm()
{
	cout << "悍马H2鸣笛" << endl;
}
void CHummerH2Model::EngineBoom()
{
	cout << "悍马H2引擎声音是这样...." << endl;
}
bool CHummerH2Model::IsAlarm()
{
	return false;
}