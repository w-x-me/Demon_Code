#pragma once
#include "corpnode.h"
#include "CorpNode.h"

class CBranchNode :
	public CCorpNode
{
public:
	CBranchNode(void);
	CBranchNode(string name, string pos, int salary);
	~CBranchNode(void);
	void Add(CCorpNode *pcorpNode);
	vector<CCorpNode*> GetSubordinateInfo();
	bool IsLeaf();
private:
	vector<CCorpNode*> m_subordinateList;
};