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

//新增方法，保证adb.exe进程每次调用后被杀死，同时保证完全获取adb指令执行后，把返回值获取全
#include<Tlhelp32.h>
void KillProcessFromName(CString strProcessName)
{
	try
	{
		HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (!Process32First(hSnapShot, &pe))
			return;
		strProcessName.MakeLower();
		while (Process32Next(hSnapShot, &pe))
		{
			CString scTemp = pe.szExeFile;
			scTemp.MakeLower();
			if (!scTemp.Compare(strProcessName))
			{
				DWORD dwProcessID = pe.th32ProcessID;
				HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessID);
				::TerminateProcess(hProcess, 0);
				CloseHandle(hProcess);
			}
			scTemp.ReleaseBuffer();
		}
		strProcessName.ReleaseBuffer();
	}
	catch (...)
	{

	}
};

bool ExecuteADBCmdWithSerial(char* cmdline,  char* response)
{
	int RetryCT = 0;
Retry:

	//char szADBCmdLine[1024] = { 0 };
	char szTmp[4096] = { 0 };
	char szBuffer[4096] = { 0 };
	DWORD dwRet = 0;
	DWORD dwBytesRead = 0;
	DWORD dwMilliseconds = 15000;//HRH 30000->15000
	bool bRet = false;
	int totalRetryTime = 3;
	int retryCount = 0;
	CString strFilePath;

	char appPath[267];
	strFilePath.Format(".\\adb\\adb.exe %s", cmdline);
	strcpy(appPath, strFilePath);
	
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead = NULL, hWrite = NULL;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
		return false;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	for (; retryCount <= totalRetryTime; retryCount++)
	{
		if (!CreateProcess(NULL, appPath, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
			break;
		dwRet = WaitForSingleObject(pi.hProcess, dwMilliseconds);
		if (dwRet == WAIT_TIMEOUT || dwRet == WAIT_FAILED)
		{
			TerminateProcess(pi.hProcess, 0);
			Sleep(200);
			continue;   //HRH,强制结束后重新创建
		}

		if (true)
		{
			CloseHandle(hWrite);
			hWrite = NULL;
			bool bReadOk = false;
			for (int i = 0; i < 5; i++)
			{
				memset(szBuffer, 0, sizeof(szBuffer));
				ReadFile(hRead, szBuffer, sizeof(szBuffer)-1, &dwBytesRead, NULL);
				if (strstr(szBuffer, "daemon not running") != NULL)
				{
					Sleep(100);
					continue;
				}
				if (strstr(szBuffer, "device not found") != NULL)
				{
					Sleep(100);
					continue;
				}
				CString str = szBuffer;
				if (str.IsEmpty())
				{
					Sleep(100);
					continue;
				}
				bReadOk = true;
				break;
			}
			if (!bReadOk)
			{
				TerminateProcess(pi.hProcess, 0);
				Sleep(200);
				continue;
			}
			else
			{
				strncpy(response, szBuffer, sizeof(szBuffer)-1);
				bRet = true;
				CloseHandle(hRead);
				hRead = NULL;
				break;
			}
		}
		else
			bRet = true;

		break;
	}

	if (hRead)
	{
		CloseHandle(hRead);
		hRead = NULL;
	}
	if (hWrite)
	{
		CloseHandle(hWrite);
		hWrite = NULL;
	}

	RetryCT++;
	if (strstr(response, "device not found") != NULL)
	{
		if (RetryCT <= 5)
		{
			Sleep(2000);
			goto Retry;
		}
	}
	KillProcessFromName(".\\adb\\adb.exe");//每次执行完后将adb.exe杀死。
	KillProcessFromName("conhost.exe");
	return bRet;
}
/*--------------------------------------------------------------------------------------------*/



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
