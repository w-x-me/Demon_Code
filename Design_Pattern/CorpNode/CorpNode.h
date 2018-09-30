#pragma once
#include <iostream>
#include<vector>
using namespace std;
class CCorpNode
{
public:
	CCorpNode();
	CCorpNode(string _name, string _pos, int _salary);
	virtual ~CCorpNode(void);
	virtual string GetInfo();
	void SetParent(CCorpNode *_pParent);
	CCorpNode * GetParent();
	virtual bool IsLeaf() = 0;
private:
	string m_name;
	string m_position;
	int m_salary;
protected:
	bool m_isLeaf;
	CCorpNode *m_pParent;
};