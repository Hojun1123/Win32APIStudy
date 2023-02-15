#include "pch.h"
#include "CScene_Start.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"
#include "CCamera.h"

#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

CScene_Start::CScene_Start()
{

}
CScene_Start::~CScene_Start()
{

}
void CScene_Start::update()
{
	CScene::update();
	//+추가적인 할일
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}
}

void CScene_Start::Enter()
{
	//오브젝트 추가
	CObject* pObj = new CPlayer();
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	//CObject* pOtherPlayer = pObj->Clone();
	//pObj->SetPos(Vec2(660.f, 384.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);


	//카메라가 플레이어 쫓아다니기
	//CCamera::GetInst()->SetTarget(pObj);

	int iMonsterCount = 10;
	float fMoveDist = 25.f;
	float fObjectScale = 50.f;
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CMonster* pMonsterObj = nullptr;
	float fTerm = (vResolution.x - ((fMoveDist+fObjectScale/2)* 2)) / (iMonsterCount-1);

	for (int i = 0; i < iMonsterCount; i++)
	{
		//몬스터 추가
		pMonsterObj = new CMonster();
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjectScale / 2.f) + (float)fTerm * i, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());

		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetScale(Vec2(fObjectScale, fObjectScale));
		AddObject(pMonsterObj, GROUP_TYPE::MOSTER);
	}
	
	//이번 씬에서의 충돌지정 : 플레이어그룹과 몬스터 그룹간의 충돌체크.
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MOSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MOSTER, GROUP_TYPE::PROJ_PLAYER);

	// Camera Look 
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInst()->Reset();
}