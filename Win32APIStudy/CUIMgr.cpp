#include "pch.h"
#include "CUIMgr.h"
#include "CUI.h"
#include "CKeyMgr.h"

#include "CScene.h"
#include "CSceneMgr.h"

CUIMgr::CUIMgr()
	:m_pFocusedUI(nullptr)
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

CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	CUI* pFocusedUI = m_pFocusedUI;

	//클릭이 발생하지 않을 때는 x
	if (!bLbtnTap)
		return pFocusedUI;

	//왼쪽 클릭이 발생 했을 때., UI개 맨위에 위치한다는 것은 맨 마지막에 그려졌다는 의미로 벡터의 뒤쪽에 있다는 의미이다. > 나중에 그려졌다 > 우선순위 높음
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::reverse_iterator iter = vecUI.rbegin();
	for (; iter != vecUI.rend(); ++iter)
	{
		if(((CUI*)*iter)->IsMouseOn())
		{
			targetiter = --iter.base();
			break;
		}
	}

	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);
	return pFocusedUI;
}

void CUIMgr::update()
{
	//1. 포커스 UI 확인
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	//현재 포커스 된 실제 타겟팅 된 UI를 가져옴
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	if (pTargetUI != nullptr)
	{
		pTargetUI->MouseOn();

		//마우스가 올려져있고 누름
		if (bLbtnTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}

		//마우스가 올려져있는데, 눌렀다 때는중
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();
			if (pTargetUI->m_bLbtnDown)	//만약 이전에 누른 상태였다면 클릭 이벤트
			{
				pTargetUI->MouseLbtnClicked();
			}
			pTargetUI->m_bLbtnDown = false;
		}
	}
}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	if (m_pFocusedUI == _pUI || nullptr == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}
	m_pFocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();


	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}
