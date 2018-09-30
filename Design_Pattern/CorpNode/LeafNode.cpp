#include "LeafNode.h"
CLeafNode::CLeafNode(void)
{
	m_isLeaf = true;
}
CLeafNode::CLeafNode(string name, string pos, int salary) : CCorpNode(name, pos, salary)
{
	m_isLeaf = true;
}
CLeafNode::~CLeafNode(void)
{
}
bool CLeafNode::IsLeaf()
{
	return m_isLeaf;
}