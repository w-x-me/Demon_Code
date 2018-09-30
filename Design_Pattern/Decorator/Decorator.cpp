#include "ISchoolReport.h"
#include "FouthGradeSchoolReport.h"

#include "HighScoreDecorator.h"
#include "SortDecorator.h"

void DoIt()
{
	ISchoolReport *psr = new CFouthGradeSchoolReport();
	psr->Report();//看成绩单
	psr->Sign("老三");//很开心，就签字了
	delete psr;
}
void DoNew()
{
	cout << "----------分部分进行装饰----------" << endl;
	ISchoolReport *psr = new CFouthGradeSchoolReport();//原装成绩单 psr指向CFouthGradeSchoolReport
	ISchoolReport *pssr = new CSortDecorator(psr);//又加了成绩排名的说明 pssr指向CSortDecorator，修改类父类CReportDecorator的指向
	ISchoolReport *phsr = new CHighScoreDecorator(pssr);//加了最高分说明的成绩单， phsr指向CHighScoreDecorator，修改父类CReportDecorator的指向
	//phsr指向CHighScoreDecorator
	phsr->Report();//看成绩单
	phsr->Sign("老三");//很开心，就签字了

	cout << "----------装饰顺序的影响----------" << endl;
	delete pssr;
	delete phsr;
	pssr = NULL;
	phsr = NULL;
	//先装饰哪个不重要，顺序已经在装饰内部确定好，但一定要调用最后一个装饰器的接口。
	phsr = new CHighScoreDecorator(psr);//加了最高分说明的成绩单
	pssr = new CSortDecorator(phsr);//又加了成绩排名的说明
	//pss指向CSortDecorator
	pssr->Report();//看成绩单
	pssr->Sign("老三");//很开心，就签字了

	delete pssr;
	delete phsr;
	delete psr;
}
int main()
{
	//在装饰之前，可以用继承的办法，来进行简单的修饰
	DoIt();

	//但如果需要修饰的项目太多呢？或者装饰的项目不是固定的，继承显然会变得更复杂
	DoNew();

	system("pause");

		return 0;
}