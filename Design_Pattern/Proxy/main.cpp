#include "WangPo.h"
#include "PanJinLian.h"
#include "JiaShi.h"

void doPanJinLian()
{
	WangPo *pWangPo;
	pWangPo = new WangPo(new PanJinLian());
	pWangPo->MakeEyesWithMan();
	pWangPo->HappyWithMan();
	delete pWangPo;
}
void doJiaShi()
{
	WangPo *pWangPo;
	pWangPo = new WangPo(new JiaShi());
	pWangPo->MakeEyesWithMan();
	pWangPo->HappyWithMan();
	delete pWangPo;
}
int main()
{
	doPanJinLian();

	doJiaShi();
	system("pause");

	return 0;
}