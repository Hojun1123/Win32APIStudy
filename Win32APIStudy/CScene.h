#pragma once

class CObject;

class CScene
{
private:
	//32그룹을 관리
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];	//오브젝트 벡터
	wstring m_strName;	//씬 이름

	UINT m_iTileX;	//가로
	UINT m_iTileY;	//세로

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName(){ return m_strName; }

	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	//순수 가상 함수
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); }
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelativePath);

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }
public:
	CScene();
	virtual ~CScene();
};

