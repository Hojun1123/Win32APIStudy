#include "pch.h"
#include "CPanelUI.h"
#include "CKeyMgr.h"

CPanelUI::CPanelUI()
	:CUI(false)

{

}

CPanelUI::~CPanelUI()
{

}


void CPanelUI::MouseOn()
{
	if(IsLbtnDown())
	{
		 Vec2 vDiff = MOUSE_POS - m_vDragStart;
		 SetPos(GetPos() + vDiff);
		 m_vDragStart = MOUSE_POS;
	}
}

void CPanelUI::MouseLbtnDown()
{
	m_vDragStart = MOUSE_POS;
}

void CPanelUI::MouseLbtnUp()
{
}

/*
void CPanelUI::update()
{
}

void CPanelUI::render(HDC _dc)
{
}
*/
