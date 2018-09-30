#pragma once
#include "corpnode.h"
class CLeafNode :
	public CCorpNode
{
public:
	CLeafNode(void);
	CLeafNode(string name, string pos, int salary);
	~CLeafNode(void);
	bool IsLeaf();
};