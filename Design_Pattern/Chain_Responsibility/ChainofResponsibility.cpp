#include "IWomen.h"
#include "Women.h"
#include "Handler.h"
#include "Father.h"
#include "Husband.h"
#include "Son.h"
void DoNew()
{
	cout << "----------使用模式后的处理方式----------" << endl;
	//Handler.h, Handler.cpp, IWomen.h, Women.h, Women.cpp, Father.h, Father,cpp, Husband.h, Husband.cpp, Son.h, Son.cpp
	IWomen *pwomen1 = new CWomen(1, "我要出去逛街");//女儿
	IWomen *pwomen2 = new CWomen(2, "我要出去吃饭");//妻子
	IWomen *pwomen3 = new CWomen(3, "我也要出去吃饭");//母亲
	IWomen *pwomen4 = new CWomen(4, "我也要出去逛街");

	CHandler *pfather = new CFather();//指向子类对象CFather
	CHandler *phusband = new CHusband();//指向子类对象CHusband
	CHandler *pson = new CSon();//指向子类对象CSon

	pfather->SetNext(phusband);//调用CHandler的SetNext，让m_pNextHandler指向CHusband
	phusband->SetNext(pson);//调用CHandler的SetNext，让m_pNextHandler指向CSon

	pfather->HandleMessage(pwomen1);
	pfather->HandleMessage(pwomen2);
	pfather->HandleMessage(pwomen3);
	pfather->HandleMessage(pwomen4);

	delete pfather;
	delete phusband;
	delete pson;
	delete pwomen1;
	delete pwomen2;
	delete pwomen3;
	delete pwomen4;
}
int main()
{
	//要实现逻辑判断，即女性的请求先发送到父亲类，父亲类一看是自己要处理的，就回应进行处理。如果女儿已经出嫁了，那就把这个请求转发到女婿（CHusband）类来处理。依此类推，形成了一个责任链。
	DoNew();
	system("pause");
	return 0;
}