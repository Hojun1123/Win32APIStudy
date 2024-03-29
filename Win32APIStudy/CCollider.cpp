#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "CCamera.h"
#include "SelectGDI.h"
UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	:m_pOwner(nullptr)
	,m_iID(g_iNextID++)	//정적변수를 통한 아이디 값 부여
	,m_iCol(0)
{
}

CCollider::~CCollider()
{
}


// 아이디 값은 해당 객체가 복사되더라도 고유해야하기 때문에,
CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)
{

}

void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	++m_iCol;
	m_pOwner->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--m_iCol;
	m_pOwner->OnCollisionExit(_pOther);
}


void CCollider::finalupdate()
{
	//오브젝트(Owner)의 위치를 따라감
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
	
	assert(0 <= m_iCol);
}

void CCollider::render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;
	if (m_iCol)
		ePen = PEN_TYPE::RED;

	SelectGDI p(_dc, ePen);
	SelectGDI q(_dc, BRUSH_TYPE::HOLLOW);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

	Rectangle(_dc, int(vRenderPos.x - m_vScale.x / 2.f)
		, int(vRenderPos.y - m_vScale.y / 2.f)
		, int(vRenderPos.x + m_vScale.x / 2.f)
		, int(vRenderPos.y + m_vScale.y / 2.f));
}
