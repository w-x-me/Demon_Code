#include "Emperor.h"
#include <iostream>
Emperor *Emperor::m_emperor = NULL;
HANDLE Emperor::m_mutex = CreateMutex(NULL, FALSE, NULL);
Emperor::Garbo Emperor::m_garbo;
Emperor::Emperor(void)
{
	cout << "create emperor instance" << endl;
}
Emperor::~Emperor(void)
{
	cout << "destroy emperor instance and release its resources" << endl;
}
void Emperor::emperorInfo(void)
{
	char msg_buf[50] = { 0 };
	sprintf_s(msg_buf, 50, "the emperor's name is (%s)", m_emperor_tag.c_str());
	string msg(msg_buf);
	cout << msg.c_str() << endl;
}
Emperor *Emperor::getInstance()
{
	if (NULL == m_emperor)
	{
		WaitForSingleObject(m_mutex, INFINITE);
		if (NULL == m_emperor)
			m_emperor = new Emperor();
		ReleaseMutex(m_mutex);
	}
	return m_emperor;
}
void Emperor::releaseInstance()
{
	if (NULL != m_emperor)
	{
		WaitForSingleObject(m_mutex, INFINITE);
		if (NULL != m_emperor)
		{
			delete m_emperor;
			m_emperor = NULL;
		}
		ReleaseMutex(m_mutex);
	}
}
void Emperor::setEmperorTag(string tag)
{
	m_emperor_tag = tag;
}