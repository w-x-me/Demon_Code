#include "Context.h"
Context::Context(IStrategy1 *mStrategy)
{
	this->m_strategy = mStrategy;
}
Context::~Context()
{
	delete this->m_strategy;
}
void Context::Operator()
{
	this->m_strategy->Operator();
}
