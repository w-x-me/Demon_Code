#include "AddRequirementCommand.h"
CAddRequirementCommand::CAddRequirementCommand(void)
{
}
CAddRequirementCommand::~CAddRequirementCommand(void)
{
}
void CAddRequirementCommand::Execute()
{
	//执行增另一项需求的命令
	this->ICommand::m_prg->Find();

	//增加一份需求
	this->ICommand::m_prg->Add();

	//给出计划
	this->ICommand::m_prg->Plan();
}