#pragma once
#include "CObject.h"
class CUI	:	public CObject
{
private:
	vector<CUI*> m_vecChildUI;
	CUI* m_pParentUI;
	Vec2	m_vFinalPos;

	bool	m_bCamAffected;	//ī�޶� ������ ��/�ȹ޴� UI
	bool	m_bMouseOn;		//UI���� ���콺�� �ִ���
	bool	m_bLbtnDown;	//UI�� ���ʹ�ư�� �������� �ִ���

private:
	void update_child();
	void finalupdate_child();
	void render_child(HDC _dc);

	void MouseOnCheck();

public:

	virtual void update();
	virtual void render(HDC _dc);
	virtual void finalupdate();

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();
	
	Vec2 GetFinalPos() { return m_vFinalPos; }
	CUI* GetParent() { return m_pParentUI; }
	bool IsMouseOn() { return m_bMouseOn; }
	bool IsLbtnDown() { return m_bLbtnDown; }

 	void AddChild(CUI* _pUI) 
	{ 
		m_vecChildUI.push_back(_pUI);
		_pUI->m_pParentUI = this;
	}

	const vector<CUI*>& GetChildUI() { return m_vecChildUI; }


public:
	CUI(bool _bCamAff);
	CUI(const CUI& _origin);
	virtual ~CUI();
	virtual CUI* Clone() = 0;

	friend class CUIMgr;
};

