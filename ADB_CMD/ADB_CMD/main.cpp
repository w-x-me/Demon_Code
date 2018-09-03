#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS 
#include <SDKDDKVer.h>
#include<cstring>
#include <dos.h> 
#include <afx.h>
#include"Image_deal.h"
using namespace std;
//C++调用ADB函数
bool ExecuteADBShellCmd(char* cmdline, char* response)
{
	int ShellRetryCT = 0;

ShellRetry:


	CString FilePath;
	char appPath[267];
	char buffer[4096] = { 0 };
	DWORD bytesRead;
	bool readflag = true;

	FilePath.Format(".\\adb\\adb.exe %s", cmdline);
	
	strcpy(appPath, FilePath);
	cout << appPath << endl;

	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	if (!CreatePipe(&hRead, &hWrite, &sa, 0))   //???¨????????
	{
		//cout << "打开文件失败" << endl;
		return false;
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite; 
	si.wShowWindow = SW_HIDE;  
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;


	if (!CreateProcess(NULL, appPath, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		CString sMsg;
		sMsg.Format("Unable to open program: \"%s\"", "adb.exe");
		//cout << "Unable to open program" << endl;
		return false;
	}
	/*int a;
	 a=WaitForSingleObject(pi.hProcess, 200000);
	if (0x00000102 == a)
	{
		return false;
	}
	*/
	CloseHandle(hWrite);



	while (true)
	{
		if (ReadFile(hRead, buffer, 4095, &bytesRead, NULL) == NULL)
			break;
		if (readflag)
		{
			readflag = false;
			strcpy(response, buffer);
		}
		else
			sprintf(response, "%s%s", response, buffer);
		Sleep(100);
	}
	CloseHandle(hRead);

	//remove the enter key
	if (strlen(response) != 0)
	{
		if (0x0a == response[strlen(response) - 1])		response[strlen(response) - 1] = 0x00;
		if (0x0d == response[strlen(response) - 1])		response[strlen(response) - 1] = 0x00;
		if (0x0d == response[strlen(response) - 1])		response[strlen(response) - 1] = 0x00;
	}
	//end

	ShellRetryCT++;

	//这里处理下device not found的情况，如果出现则做几次retry device not found
	if (strstr(response, "device not found") != NULL)
	{
		if (ShellRetryCT <= 5)
		{
			Sleep(2000);
			goto ShellRetry;
		}

	}

	return true;
}
int take_image_ffc()//前置摄像头
{
	image_deal halcon_deal;
	char cmdline[50];
	char response[20480];
	strcpy(cmdline, "shell dtest display_f_turn_off");
	bool ok = ExecuteADBShellCmd(cmdline, response);
	if (response[12] != 'P' || ok == false)
	{
		cout << "关闭屏幕执行失败" << endl;
		return -1;
	}

	strcpy(cmdline, "shell rm  /data/image_ffc.jpeg");
	ok = ExecuteADBShellCmd(cmdline, response);
	if (ok == false)
	{
		cout << "删除照片失败" << endl;
		return -1;
	}

	strcpy(cmdline, "shell dtest camera_FFC_f_capture 30 90");//F前置摄像头
	ok = ExecuteADBShellCmd(cmdline, response);
	if (ok == false)
	{
		cout << "获取图片失败" << endl;
		return -1;
	}

	strcpy(cmdline, "pull  /data/image_ffc.jpeg");
	ok = ExecuteADBShellCmd(cmdline, response);
	if (ok == false)
	{
		cout << "取出图片失败" << endl;
		return -1;
	}

	strcpy(cmdline, "shell dtest display_f_turn_on");
	ok = ExecuteADBShellCmd(cmdline, response);
	int hav_angle;
	try{
			hav_angle = halcon_deal.image_Analysis('f');

	}
	catch (exception& e){
		cout << e.what() << endl;
		return -1;
	}
	return 0;
}
int take_image_rf()
{
	image_deal halcon_deal;
	char cmdline[50];
	char response[20480];
	strcpy(cmdline, "shell dtest display_f_turn_off");
	bool ok = ExecuteADBShellCmd(cmdline, response);
	if (response[12] != 'P' || ok == false)
	{
		cout << "关闭屏幕执行失败" << endl;
		return -1;
	}

	strcpy(cmdline, "shell rm  /data/image_rfc.jpeg");
	ok = ExecuteADBShellCmd(cmdline, response);
	if (ok == false)
	{
		cout << "删除照片失败" << endl;
		return -1;
	}

	strcpy(cmdline, "shell dtest camera_RFC_f_capture 30 90");//R后置摄像头
	ok = ExecuteADBShellCmd(cmdline, response);
	if (ok == false)
	{
		cout << "获取图片失败" << endl;
		return -1;
	}

	strcpy(cmdline, "pull  /data/image_rfc.jpeg");
	ok = ExecuteADBShellCmd(cmdline, response);
	if (ok == false)
	{
		cout << "取出图片失败" << endl;
		return -1;
	}

	strcpy(cmdline, "shell dtest display_f_turn_on");
	ok = ExecuteADBShellCmd(cmdline, response);
	int hav_angle;
	try{
		hav_angle = halcon_deal.image_Analysis('r');

	}
	catch (exception& e){
		cout << e.what() << endl;
		return -1;
	}
	return 0;
}
int main()
{
	take_image_ffc();
	
	
	system("pause");
	return 0;

}