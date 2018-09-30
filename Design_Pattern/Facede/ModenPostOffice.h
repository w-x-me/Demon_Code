#pragma once
#include "ILetterProcess.h"
#include "LetterProcessImpl.h"
#include "LetterPolice.h"

class CModenPostOffice
{
public:
	CModenPostOffice(void);
	~CModenPostOffice(void);
	void SendLetter(string context, string address);
private:
	ILetterProcess *m_pLetterProcess;
	CLetterPolice *m_pLetterPolice;
};