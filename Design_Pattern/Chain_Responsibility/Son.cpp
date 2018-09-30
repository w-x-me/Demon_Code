#include "Son.h"
#include <iostream>
using std::cout;
using std::endl;
CSon::CSon(void) : CHandler(3)
{
}
CSon::~CSon(void)
{
}
void CSon::Response(IWomen *pwomen)
{
	cout << "母亲向儿子请示：" << endl;
	cout << pwomen->GetRequest().c_str() << endl;
	cout << "儿子的答复是：同意" << endl;
}