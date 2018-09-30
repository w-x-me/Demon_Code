#pragma once
#include "iletterprocess.h"
class CLetterProcessImpl :
	public ILetterProcess
{
public:
	CLetterProcessImpl(void);
	~CLetterProcessImpl(void);

	void WriteContext(string context);
	void FillEnvelope(string address);
	void LetterIntoEnvelope();
	void SendLetter();
};