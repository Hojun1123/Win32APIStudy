#pragma once

//싱글톤, 객체의 생성을 1개로 제한
/*
class CCore
{
private:
	static CCore* g_pInst;

public:

	//정적 멤버함수
	static CCore* GetInstance()
	{
		//
		g_pInst = nullptr;
		if (nullptr == g_pInst)
		{
			g_pInst = new CCore;
		}
		//최초 호출
		return g_pInst;
	}
	static void Release(CCore c)
	{
		if (nullptr != g_pInst)
		{
			delete g_pInst;
			g_pInst = nullptr;
		}
	}





//생성자를 private으로 제한, 특정함수만을 통해 생성할 수 있게 제한
//근데 해당 함수를 쓰려면 객체가 있어야하는데 생성을 못함 -> static키워드를 붙여서 사용
//호출한 객체 없이 호출하게 되는 경우, this는 존재x, 멤버에도 접근 불가능
//하지만 static멤버에 대해서는 접근가능
private:
	CCore();
	~CCore();
};

*/




// 2. 데이터 영역에 클래스를 올리는 방법

#include "pch.h"
#include "define.h"

class CCore
{
	SINGLE(CCore);

private:
	HWND	m_hWnd;	//메인 윈도우 핸들
	POINT	m_ptResolution;	//메인 윈도우 해상도
	HDC		m_hDC;	//메인 윈도우에 Draw할 DC

	HBITMAP m_hBit;
	HDC m_memDC;

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }
};