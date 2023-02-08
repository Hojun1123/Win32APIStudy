#include "pch.h"
#include "CScene_Start.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"

CScene_Start::CScene_Start()
{

}
CScene_Start::~CScene_Start()
{

}
void CScene_Start::Enter()
{
	//������Ʈ �߰�
	CObject* pObj = new CPlayer();
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	int iMonsterCount = 10;
	float fMoveDist = 25.f;
	float fObjectScale = 50.f;
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CMonster* pMonsterObj = nullptr;
	float fTerm = (vResolution.x - ((fMoveDist+fObjectScale/2)* 2)) / (iMonsterCount-1);

	for (int i = 0; i < iMonsterCount; i++)
	{
		//���� �߰�
		pMonsterObj = new CMonster();
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjectScale / 2.f) + (float)fTerm * i, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetScale(Vec2(fObjectScale, fObjectScale));
		AddObject(pMonsterObj, GROUP_TYPE::MOSTER);
	}
	
	//�̹� �������� �浹���� : �÷��̾�׷�� ���� �׷찣�� �浹üũ.
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MOSTER);
}

void CScene_Start::Exit()
{
	CCollisionMgr::GetInst()->Reset();
}