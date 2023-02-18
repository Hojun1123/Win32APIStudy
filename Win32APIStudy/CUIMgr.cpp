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

			//���콺�� �÷����ְ� ����
			if (bLbtnTap)
			{
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}

			//���콺�� �÷����ִµ�, ������ ������
			else if (bLbtnAway)
			{
				pUI->MouseLbtnUp();
				if (pUI->m_bLbtnDown)	//���� ������ ���� ���¿��ٸ� Ŭ�� �̺�Ʈ
				{
					pUI->MouseLbtnClicked();
				}
				pUI->m_bLbtnDown = false;
			}
		}
	}
}