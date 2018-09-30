#include "ILetterProcess.h"
#include "LetterProcessImpl.h"
#include "ModenPostOffice.h"

void DoItByPostOffice()
{
	CModenPostOffice modenPostOffice;
	string context = "Hello, It's me, do you know who I am? I'm your old lover. I'd like to ... ...";
	string address = "Happy Road No. 666, Beijing City, China";
	modenPostOffice.SendLetter(context, address);
}
void DoItYourself()
{
	ILetterProcess *pLetterProcess = new CLetterProcessImpl();
	pLetterProcess->WriteContext("Hello, It's me, do you know who I am? I'm your old lover. I'd like to ... ...");
	pLetterProcess->FillEnvelope("Happy Road No. 666, Beijing City, China");
	pLetterProcess->LetterIntoEnvelope();
	pLetterProcess->SendLetter();
	delete pLetterProcess;
}
int main()
{
	//现在的调用方式。对于客户来说确实简单多了。
	//如需要增加逻辑，例如让警察来检查邮件。可以在邮局里完成这项工作。
	DoItByPostOffice();

	//原来的调用方式。
	DoItYourself();

	system("pause");

	return 0;
}