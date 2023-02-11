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

	//이전 프레임에서 등록해둔 Dead_Object들 삭제
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	//오브젝트 생성 이벤트 업데이트
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
	{	//lParam : 오브젝트 주소
		//rParam : 오브젝트 타입
		CObject* pNewObj = (CObject*)_e.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_e.wParam;
		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
		break;

	case EVENT_TYPE::DELETE_OBJECT:
	{
		//lParam : 삭제할 오브젝트 주소
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
