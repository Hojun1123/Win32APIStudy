#include "pch.h"
#include "CUIMgr.h"
#include "CUI.h"
#include "CKeyMgr.h"

#include "CScene.h"
#include "CSceneMgr.h"

CUIMgr::CUIMgr()
{}

CUIMgr::~CUIMgr()
{

}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	//1. 부모 UI 포함 , 모든 자식들을 검사한다.
	list<CUI*> queue;
	vector<CUI*> vecNoneTarget;
	CUI* pTargetUI = nullptr;
	queue.push_back(_pParentUI);
	while (!queue.empty())
	{
		//큐에서 UI 하나 꺼내기
		CUI* pUI = queue.front();
		queue.pop_front();
		//큐에서 꺼내온 UI가 타겟UI인지 확인
		if(pUI->IsMouseOn())
		{
			if(nullptr != pTargetUI)
				vecNoneTarget.push_back(pTargetUI);
			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}


		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i) 
		{
			queue.push_back(vecChild[i]);
		}

		//버튼을 때면, 눌렀던 체크를 다시 해제
		if (bLbtnAway)
		{
			for (size_t i = 0; i < vecNoneTarget.size(); ++i)
			{
				vecNoneTarget[i]->m_bLbtnDown = false;
			}
		}


	}
	return pTargetUI;
}

void CUIMgr::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];
		pUI = GetTargetedUI(pUI);
		if (pUI != nullptr)
		{
			pUI->MouseOn();

			//마우스가 올려져있고 누름
			if (bLbtnTap)
			{
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}

			//마우스가 올려져있는데, 눌렀다 때는중
			else if (bLbtnAway)
			{
				pUI->MouseLbtnUp();
				if (pUI->m_bLbtnDown)	//만약 이전에 누른 상태였다면 클릭 이벤트
				{
					pUI->MouseLbtnClicked();
				}
				pUI->m_bLbtnDown = false;
			}
		}
	}
}