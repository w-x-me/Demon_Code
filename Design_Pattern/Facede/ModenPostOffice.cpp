#include "ModenPostOffice.h"
CModenPostOffice::CModenPostOffice(void)
{
	this->m_pLetterProcess = new CLetterProcessImpl();
	this->m_pLetterPolice = new CLetterPolice();
}
CModenPostOffice::~CModenPostOffice(void)
{
	delete m_pLetterProcess;
	delete m_pLetterPolice;
}
void CModenPostOffice::SendLetter(string context, string address)
{
	//帮忙写信
	m_pLetterProcess->WriteContext(context);
	//写好信封
	m_pLetterProcess->FillEnvelope(address);
	//警察要检查信件了
	m_pLetterPolice->CheckLetter(m_pLetterProcess);
	//把信放到信封中
	m_pLetterProcess->LetterIntoEnvelope();
	//邮递信件
	m_pLetterProcess->SendLetter();
}