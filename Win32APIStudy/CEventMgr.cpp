#include "pch.h"
#include "CEventMgr.h"
#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"
CEventMgr::CEventMgr()
{


}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{

	//���� �����ӿ��� ����ص� Dead_Object�� ����
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	//������Ʈ ���� �̺�Ʈ ������Ʈ
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _e)
{
	switch (_e.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{	//lParam : ������Ʈ �ּ�
		//rParam : ������Ʈ Ÿ��
		CObject* pNewObj = (CObject*)_e.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_e.wParam;
		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
		break;

	case EVENT_TYPE::DELETE_OBJECT:
	{
		//lParam : ������ ������Ʈ �ּ�
		CObject* pDeadObj = (CObject*)_e.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;

	case EVENT_TYPE::SCENE_CHANGE:
	{
		//lParam : Next Scene Type
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_e.lParam);
	}
		break;

	default:
		break;

	}
}
