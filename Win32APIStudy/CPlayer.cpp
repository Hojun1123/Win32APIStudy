#include "pch.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CScene.h"

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
		vPos.y -= 200.f * fDT;
	if (KEY_HOLD(KEY::S))
		vPos.y += 200.f * fDT;
	if (KEY_HOLD(KEY::A))
		vPos.x -= 200.f * fDT;
	if (KEY_HOLD(KEY::D))
		vPos.x += 200.f * fDT;

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}
	SetPos(vPos);
}

void CPlayer::CreateMissile()
{
	CMissile* pMissile = new CMissile;
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(true);
	
	CScene* pCurScene =  CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFUALT);
}

CPlayer::CPlayer()
{

}

CPlayer::~CPlayer()
{

}