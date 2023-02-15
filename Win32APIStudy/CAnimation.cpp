#include "pch.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CCamera.h"

CAnimation::CAnimation()
	:m_pAnimator(nullptr)
	,m_pTex(nullptr)
	,m_iCurFrm(0)
	,m_fAccTime(0.f)
{

}

CAnimation::~CAnimation()
{

}

void CAnimation::update()
{
	if (m_bFinish)
		return;

	m_fAccTime += (float)fDT;	//시간누적

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)	//Duration만큼 쌓이면 프레임교체
	{
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
		++m_iCurFrm;
		if (m_vecFrm.size() <= m_iCurFrm)	//애니메이션 한바퀴를 다 돌면
		{
			m_iCurFrm = -1;			
			m_bFinish = true;
		}
	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;

	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	vPos += m_vecFrm[m_iCurFrm].vOffset;
	//랜더링 좌표로 변환
	vPos = CCamera::GetInst()->GetRenderPos(vPos);
	TransparentBlt(_dc
		, (int) (vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
		, (int) (vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
		, (int) m_vecFrm[m_iCurFrm].vSlice.x
		, (int) m_vecFrm[m_iCurFrm].vSlice.y
		, m_pTex->GetDC()
		, (int) m_vecFrm[m_iCurFrm].vLT.x
		, (int) m_vecFrm[m_iCurFrm].vLT.y
		, (int) m_vecFrm[m_iCurFrm].vSlice.x
		, (int) m_vecFrm[m_iCurFrm].vSlice.y
		, RGB(255, 255, 255)
	);
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;
	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + (_vStep * (float)i);
		m_vecFrm.push_back(frm);
	}
}
