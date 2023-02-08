#pragma once

class CObject;

class CScene
{
private:
	//32그룹을 관리
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];	//오브젝트 벡터
	wstring m_strName;	//씬 이름

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName(){ return m_strName; }

	void update();
	void finalupdate();
	void render(HDC _dc);

	//순수 가상 함수
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); }
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }

public:
	CScene();
	virtual ~CScene();
};

