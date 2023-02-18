#include "pch.h"
#include "CUI.h"
#include "CCamera.h"
#include "CKeyMgr.h"

// 부모 > 자식 순 업데이트, 랜더

CUI::CUI(bool _bCamAff)
	:m_pParentUI(nullptr)
	,m_bCamAffected(_bCamAff)
	,m_bMouseOn(false)
	,m_bLbtnDown(false)
{

}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}

void CUI::update()
{
	update_child();
}


void CUI::finalupdate()
{
	CObject::finalupdate();

	//ui의 최종 좌표를 구함
	//부모가 있다면 부모 위치에 본인 위치를 더하고, 없다면 최상위 UI이므로 그대로.
	m_vFinalPos = GetPos();
	if (GetParent())
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}
	//UI Mouse체크
	MouseOnCheck();

	finalupdate_child();
}

void CUI::MouseOn()
{

}

void CUI::MouseLbtnDown()
{

}

void CUI::MouseLbtnUp()
{

}

void CUI::MouseLbtnClicked()
{

}



void CUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	Rectangle(_dc
		,	int(vPos.x)
		,   int(vPos.y)
		,	int(vPos.x + vScale.x)
		,	int(vPos.y + vScale.y)
		);

	render_child(_dc);
}

void CUI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalupdate();
	}
}


void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::MouseOnCheck()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();
	if (m_bCamAffected)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}

	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= (m_vFinalPos.x + vScale.x)
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= (m_vFinalPos.y + vScale.y))
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}
