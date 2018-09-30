#include "BackDoor.h"
#include"GivenGreenLight.h"
#include "Context.h"
int main()
{
	Context *p_context;
	p_context = new Context(new CBackDoor());
	p_context->Operator();
	delete p_context;
	p_context = new Context(new GivenGreenLight());
	p_context->Operator();
	delete p_context;
	system("pause");
	return 0;
}