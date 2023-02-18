#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "CCamera.h"
#include "CCore.h"
#include "CResMgr.h"
#include "resource.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{
	//鸥老 积己
	CreateTile(5, 5);

	//UI积己
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CUI* pUI = new CUI(false);
	pUI->SetName(L"ParentUI");
	pUI->SetScale(Vec2(500.f, 400.f));
	pUI->SetPos(Vec2(vResolution.x - pUI->GetScale().x, 0.f));

	
	CUI* pChildUI = new CUI(false);
	pChildUI->SetName(L"ChildUI");
	pChildUI->SetScale(Vec2(100.f, 40.f));
	pChildUI->SetPos(Vec2(0.f, 0.f));

	pUI->AddChild(pChildUI);
	//AddObject(pChildUI, GROUP_TYPE::UI);
	AddObject(pUI, GROUP_TYPE::UI);


	//墨皋扼
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Tool::Exit()
{
}


void CScene_Tool::update()
{
	CScene::update();
	SetTileIdx();
}

void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		UINT iTileX = GetTileX();
		UINT iTileY = GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (vMousePos.x < 0.f || (int)iTileX <= iCol || vMousePos.y < 0.f || (int)iTileY <= iRow)
		{
			return;
		}

		int iIdx = int(iRow * iTileX + iCol);
		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();

	}
}




///////////////////################

INT_PTR __stdcall  TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT3, nullptr, false);
			
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
