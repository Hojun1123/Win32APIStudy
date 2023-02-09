#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "CEventMgr.h"

void CMonster::update()
{
	Vec2 vCurPos = GetPos();
	vCurPos.x += fDT * m_fSpeed * m_iDir;

	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;
	if (0.f < fDist)
	{
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj =  _pOther->GetObj();
	if (pOtherObj->GetName() == L"Missile_Player")
	{

		DeleteObject(this);
	}
}

CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(45.f, 45.f));
}

CMonster::~CMonster()
{
}
