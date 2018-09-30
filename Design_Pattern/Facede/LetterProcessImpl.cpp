#include "LetterProcessImpl.h"
CLetterProcessImpl::CLetterProcessImpl(void)
{
}
CLetterProcessImpl::~CLetterProcessImpl(void)
{
}
void CLetterProcessImpl::WriteContext(string context)
{
	cout << "填写信的内容... ..." << endl;
}
void CLetterProcessImpl::FillEnvelope(string address)
{
	cout << "填写收件人地址及姓名... ..." << endl;
}
void CLetterProcessImpl::LetterIntoEnvelope()
{
	cout << "把信放到信封中..." << endl;
}
void CLetterProcessImpl::SendLetter()
{
	cout << "邮递信件..." << endl;
}