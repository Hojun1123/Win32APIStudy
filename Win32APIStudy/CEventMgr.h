#pragma once

struct tEvent
{
	EVENT_TYPE eEven;
	DWORD_PTR lParam;
	DWORD_PTR wParam;
};

class CEventMgr
{
	SINGLE(CEventMgr)


private:
	vector<tEvent> m_vecEvent;
	vector<CObject*> m_vecDead;

public:
	void update();
 	void AddEvent(const tEvent& _e) { m_vecEvent.push_back(_e); }
	void Excute(const tEvent& _e);
};

