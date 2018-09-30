#pragma once
#include "ILetterProcess.h"
class CLetterPolice
{
public:
	CLetterPolice(void);
	~CLetterPolice(void);
	void CheckLetter(ILetterProcess *pLetterProcess);
};