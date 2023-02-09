#include "pch.h"
#include "func.h"

#include "CEventMgr.h"
void CreateObject(CObject* _pobj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pobj;
	evn.wParam = (DWORD_PTR)_eGroup;

	CEventMgr::GetInst()->AddEvent(evn);

}

void DeleteObject(CObject* _pobj)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pobj;
	CEventMgr::GetInst()->AddEvent(evn);
}
