#define _CRT_SECURE_NO_WARNINGS
#define _AFXDLL
#include<iostream>
#include <fstream>
#include <afx.h>
using namespace std;
int MyCopyFile(char *SourceFile, char *NewFile)
{
	ifstream in;
	ofstream out;
	in.open(SourceFile, ios::binary);//打开源文件
	if (in.fail())//打开源文件失败
	{
		in.close();
		out.close();
		return 0;
	}
	out.open(NewFile, ios::binary);//创建目标文件 
	if (out.fail())//创建文件失败
	{
		out.close();
		in.close();
		return 0;
	}
	else//复制文件
	{
		out << in.rdbuf();
		out.close();
		in.close();
		return 1;
	}
}
int main()
{
	CTime currTime;
	currTime = CTime::GetCurrentTime();
	CString strTime;
	CString strDate;
	strTime.Format(_T("%.4d%.2d%.2d%.2d%.2d%.2d"),
		currTime.GetYear(), currTime.GetMonth(), currTime.GetDay(),
		currTime.GetHour(), currTime.GetMinute(), currTime.GetSecond() + 1);
	strDate.Format(_T("%.4d%.2d%.2d"),
		currTime.GetYear(), currTime.GetMonth(), currTime.GetDay());

	CString strPath;
	strPath = _T(".\\Image\\") + strDate + "\\" + "SNS" + "\\SN";
	DWORD ftyp = GetFileAttributesA(strPath.GetBuffer());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
	{
		char *fileName = strPath.GetBuffer(), *tag, path[1000];
		strcpy(path, fileName);
		char filePath[1000];
		CString RW = strPath + "\\" + strTime + "rb.jpeg";
		sprintf(filePath, "md %s", path);
		system(filePath);
		MyCopyFile("1.jpeg", (LPSTR)(LPCTSTR)RW);
	}
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return 0;
	
}