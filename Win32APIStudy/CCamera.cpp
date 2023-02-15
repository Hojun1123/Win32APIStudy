#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(1.f)
	, m_fSpeed(0.f)
	, m_fAccTime(1.f)
{
}

CCamera::~CCamera()
{
}

void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
			m_pTargetObj = nullptr;
		else
			m_vLookAt = m_pTargetObj->GetPos();
	}

	if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 500.f * (float)fDT;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 500.f * (float)fDT;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 500.f * (float)fDT;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 500.f * (float)fDT;
	//화면 중앙좌표와 카메라 LookAt 좌표간의 차이 값 계산
	CalDiff();
}

void CCamera::CalDiff()
{
	// 이전 lookat과 현재 lookat의 차이값을 보정하여 현재의 lookat을 구함
	m_fAccTime += (float)fDT;
	if (m_fAccTime >= m_fTime)
	{
		m_vCurLookAt = m_vLookAt;

	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;
		m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * (float) fDT;
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;
	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;
}
