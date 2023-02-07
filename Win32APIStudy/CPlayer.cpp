
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

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	//텍스쳐 로딩
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"content\\texture\\player_image.bmp");

}

CPlayer::~CPlayer()
{
}

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
	pMissile->SetDir(Vec2(1.f, -7.f));
	
	CScene* pCurScene =  CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFUALT);
}


void CPlayer::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();
	Vec2 vPos = GetPos();
	BitBlt(_dc, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, SRCCOPY);
}