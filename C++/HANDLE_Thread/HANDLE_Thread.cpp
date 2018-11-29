#include<iostream>
#include<windows.h>
#include<afxwin.h>
using namespace std;
DWORD WINAPI myThread(LPVOID lpParameter);
DWORD WINAPI myThread1(LPVOID lpParameter);
typedef struct{
	int paraInt;
	float paraFloat;
}Param;
void WaitForFinish(HANDLE handle)
{
	try
	{
		while (true)
		{
			if (handle == NULL)
				return;
			DWORD result = MsgWaitForMultipleObjects(1, &handle, FALSE, INFINITE, QS_ALLINPUT);
			if (result == (WAIT_OBJECT_0))
			{
				CloseHandle(handle);
				handle = NULL;
				break;
			}
			else
			{
				MSG msg;
				PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
				DispatchMessage(&msg);
			}
		}
	}
	catch (...)
	{
	}
}
int main()
{
	HANDLE h;
	HANDLE h1;
	Param lap;
	int a = 10;
	CWinThread* threadProc1 = NULL;
	threadProc1 = AfxBeginThread((AFX_THREADPROC)myThread, &a);
	threadProc1->m_bAutoDelete = false;
	threadProc1->ResumeThread();
	WaitForFinish(threadProc1->m_hThread);
	lap.paraFloat = 0.5;
	lap.paraInt = 5;
	

	//h = CreateThread(NULL, 0, myThread, (void*)&a, 0, NULL);
	h1 = CreateThread(NULL, 0, myThread1, (void*)&lap, 0, NULL);
	system("pause");
	//关闭线程句柄对象
	CloseHandle(h);
	CloseHandle(h1);
	
	return 0;
}
DWORD WINAPI myThread(LPVOID lpParameter)
{
	cout << "线程1正在运行" << endl;
	cout << lpParameter << endl;
	return 0;
}

DWORD WINAPI myThread1(LPVOID lpParameter)
{
	cout << "线程2正在运行" << endl;
	Param *p = (Param *)lpParameter;
	cout << p->paraFloat << endl;
	cout << p->paraInt << endl;
	return 0;
}