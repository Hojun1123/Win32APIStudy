#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT, //LEFT,
	VK_RIGHT, //RIGHT,
	VK_UP, //UP,
	VK_DOWN, //DOWN,

	//Q,W,E,R,T,Y,U,I,O,P,
	//A,S,D,F,G,Z,X,C,V,B,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',


	VK_MENU,//ALT,
	VK_CONTROL,//CTRL,
	VK_LSHIFT,//LSHIFT,
	VK_SPACE,//SPACE,
	VK_RETURN,//ENTER,
	VK_ESCAPE,//ESC,

	VK_LBUTTON,
	VK_RBUTTON,

	//LAST
};


CKeyMgr::CKeyMgr()
{

}
CKeyMgr::~CKeyMgr()
{
}
void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}


void CKeyMgr::update()
{
	//윈도우 포커싱 알아내기
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus();	//윈도우에서 제공, 현재 포커싱되어있는 윈도우를 알려줌~.
	//
	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			//키 눌림~
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPush = true;
			}
			else
			{
				if (m_vecKey[i].bPrevPush)
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevPush = false;
			}
		}

		//마우스
		POINT ptPos = {};
		assert(GetCursorPos(&ptPos));

		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);
		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);


	}
	else
	{
		//윈도우가 포커싱이 해제되면, 키입력들을 순차적으로 해제해줌
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
				m_vecKey[i].eState = KEY_STATE::AWAY;
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
				m_vecKey[i].eState = KEY_STATE::NONE;
			m_vecKey[i].bPrevPush = false;
		}
	}
}
