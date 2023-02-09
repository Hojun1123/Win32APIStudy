#pragma once

class CCollider;

class CObject
{
private:
	wstring m_strName;

	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;

	bool m_bAlive;
	void SetDead() { m_bAlive = false; }
public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }
	bool IsDead() { return !m_bAlive; }

public:
	virtual void update() = 0;
	virtual void finalupdate() final; //final : 자식들이 오버라이딩하지 못하게 제한함
	virtual void render(HDC _dc);

	CCollider* GetCollider() { return m_pCollider; }
	void CreateCollider();
	void component_render(HDC _dc);

	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};

	friend class CEventMgr;
public:
	CObject();
	virtual ~CObject();
};

