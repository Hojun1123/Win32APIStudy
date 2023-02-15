#pragma comment(lib, "msimg32.lib")

#include "pch.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CScene.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	//텍스쳐 로딩
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"content\\texture\\rusid.bmp");
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0, 0));
	GetCollider()->SetScale(Vec2(36.f, 60.f));

	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"content\\texture\\helena.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 0.f), Vec2(80.f, 60.f), Vec2(80.f, 0.f), 0.15f, 4);
	GetAnimator()->Play(L"WALK_LEFT", true);
	
	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_LEFT");
	for (int i = 0; i < pAnim->GetMaxFrame(); ++i)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}
}	

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
		vPos.y -= 200.f * (float)fDT;
	if (KEY_HOLD(KEY::S))
		vPos.y += 200.f * (float)fDT;
	if (KEY_HOLD(KEY::A))
		vPos.x -= 200.f * (float)fDT;
	if (KEY_HOLD(KEY::D))
		vPos.x += 200.f * (float)fDT;

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}
	SetPos(vPos);

	GetAnimator()->update();
}

void CPlayer::CreateMissile()
{
	CMissile* pMissile = new CMissile;
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -7.f));
	
	//CScene* pCurScene =  CSceneMgr::GetInst()->GetCurScene();
	//pCurScene->AddObject(pMissile, GROUP_TYPE::PROJ_PLAYER);

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}


void CPlayer::render(HDC _dc)
{
	/*
	BitBlt(_dc, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, SRCCOPY);
		*/

	/*
	TransparentBlt(_dc
		, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight, RGB(255, 255, 255));


	//충돌체가 있는 경우 렌더링
	*/
	component_render(_dc);
}