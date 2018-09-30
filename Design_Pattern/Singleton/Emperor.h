#pragma once
#include <Windows.h>
#include <winnt.h>
#include <iostream>
using namespace std;
class Emperor
{
public:
	static Emperor* getInstance();
	static void releaseInstance();
	void emperorInfo(void);
	void setEmperorTag(string tag);
	
	
private:
	Emperor(void);
	virtual ~Emperor(void);
	Emperor(const Emperor&);
	Emperor& operator=(const Emperor&);
	static Emperor *m_emperor;
	static HANDLE m_mutex;
	string m_emperor_tag;
	class Garbo
	{
	public:
		Garbo()
		{
			cout << "create garbo" << endl;
		}
		~Garbo()
		{
			cout << "destrory garbo" << endl;
			getchar();
			if (NULL != m_emperor)
			{
				WaitForSingleObject(m_mutex, INFINITE);
				if (NULL != m_emperor)
				{
					cout << "remove instance" << endl;
					delete m_emperor;
					m_emperor = NULL;
				}
				ReleaseMutex(m_mutex);
			}
			if (NULL != m_mutex)
			{
				cout << "delete mutex" << endl;
				CloseHandle(m_mutex);
				m_mutex = NULL;
			}
		}
	};
	static Garbo m_garbo;
};