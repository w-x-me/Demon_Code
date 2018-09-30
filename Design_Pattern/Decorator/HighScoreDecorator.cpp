#include "HighScoreDecorator.h"

CHighScoreDecorator::CHighScoreDecorator(ISchoolReport *psr) : CReportDecorator(psr)
{
	cout << "CHighScoreDecorator" << endl;
}
CHighScoreDecorator::~CHighScoreDecorator(void)
{
	cout << "~CHighScoreDecorator" << endl;
}
void CHighScoreDecorator::Report()
{
	this->ReportHighScore();
	this->CReportDecorator::Report();
}
void CHighScoreDecorator::ReportHighScore()
{
	cout << "这次考试语文最高是75， 数学是78， 自然是80" << endl;
}