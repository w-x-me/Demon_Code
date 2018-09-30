#include "Husband.h"
#include <iostream>
CHusband::CHusband(void) : CHandler(2)
{
}
CHusband::~CHusband(void)
{
}
void CHusband::Response(IWomen *pwomen)
{
	cout << "妻子向丈夫请示：" << endl;
	cout << pwomen->GetRequest().c_str() << endl;
	cout << "丈夫的答复是：同意" << endl;
}