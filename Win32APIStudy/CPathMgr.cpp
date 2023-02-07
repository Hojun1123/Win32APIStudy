#include "pch.h"
#include "CPathMgr.h"
#include "CCore.h"

CPathMgr::CPathMgr()
	:m_szContentPath{}
{

}

CPathMgr::~CPathMgr()
{

}

void CPathMgr::init()
{
	GetCurrentDirectory(255, m_szContentPath);

	//���� �����ּ� + bin\\content\\//
	int iLen = wcslen(m_szContentPath);
	for (int i = iLen - 1; i >= 0; --i)
	{
		if ('\\' == m_szContentPath[i]) {
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");
}