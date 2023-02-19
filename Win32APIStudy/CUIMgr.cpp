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

	//1. �θ� UI ���� , ��� �ڽĵ��� �˻��Ѵ�.
	list<CUI*> queue;
	vector<CUI*> vecNoneTarget;
	CUI* pTargetUI = nullptr;
	queue.push_back(_pParentUI);
	while (!queue.empty())
	{
		//ť���� UI �ϳ� ������
		CUI* pUI = queue.front();
		queue.pop_front();
		//ť���� ������ UI�� Ÿ��UI���� Ȯ��
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

		//��ư�� ����, ������ üũ�� �ٽ� ����
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

	//Ŭ���� �߻����� ���� ���� x
	if (!bLbtnTap)
		return pFocusedUI;

	//���� Ŭ���� �߻� ���� ��., UI�� ������ ��ġ�Ѵٴ� ���� �� �������� �׷����ٴ� �ǹ̷� ������ ���ʿ� �ִٴ� �ǹ��̴�. > ���߿� �׷����� > �켱���� ����
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
	//1. ��Ŀ�� UI Ȯ��
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	//���� ��Ŀ�� �� ���� Ÿ���� �� UI�� ������
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	if (pTargetUI != nullptr)
	{
		pTargetUI->MouseOn();

		//���콺�� �÷����ְ� ����
		if (bLbtnTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}

		//���콺�� �÷����ִµ�, ������ ������
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();
			if (pTargetUI->m_bLbtnDown)	//���� ������ ���� ���¿��ٸ� Ŭ�� �̺�Ʈ
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
