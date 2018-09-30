#include "ILift.h"
#include "Lift.h"
#include"Context.h"
#include "OpenningState.h"
#include "CloseingState.h"
#include "RunningState.h"
#include "StoppingState.h"
#include <iostream>
using std::cout;
using std::endl;

void DoIt()
{
	//ILift.h, Lift.h, Lift.cpp
	ILift *pLift = new CLift();
	pLift->SetState(ILift::STOPPING_STATE);//电梯的初始条件是停止状态。
	pLift->Open();//首先是电梯门开启，人进去
	pLift->Close();//然后电梯门关闭
	pLift->Run();//再然后，电梯跑起来，向上或者向下
	pLift->Stop();//最后到达目的地，电梯停下来
	delete pLift;
}


void DoNew()
{
	CContext context;
	CCloseingState closeingState;
	context.SetLiftState(&closeingState);
	context.Close();
	context.Open();
	context.Run();
	context.Stop();
}

int main()
{
	cout << "----------使用模式之前----------" << endl;
	DoIt();
	cout << "----------使用模式之后----------" << endl;
	DoNew();

	system("pause");

		return 0;
}