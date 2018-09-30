#include "HummerModel.h"
CHummerModel::CHummerModel(void)
{
}
CHummerModel::~CHummerModel(void)
{
}
void CHummerModel::Run()
{
	//先发动汽车
	Start();
	//引擎开始轰鸣
	EngineBoom();
	//然后就开始跑了，跑的过程中遇到一条狗挡路，就按喇叭
	if (IsAlarm())
		Alarm();

	//到达目的地就停车
	Stop();
}
bool CHummerModel::IsAlarm()
{
	//钩子方法，默认喇叭是会响的
	return true;
}