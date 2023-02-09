#pragma once
class CObject;

class CCollider
{
private:
	static UINT g_iNextID;	//정적 멤버.

	CObject* m_pOwner;
	Vec2 m_vOffsetPos;	//중심점(오브젝트의 위치) 로 부터 오프셋만큼 이동한 곳이 충돌체의 위치
	Vec2 m_vFinalPos;	//최종적으로 계산되는 충돌체의 위치

	Vec2 m_vScale;	//충돌체의 크기

	UINT m_iID;
	UINT m_iCol;


public:
	void finalupdate();
	void render(HDC _dc);

	CCollider();
	~CCollider();
	CCollider(const CCollider& _origin);

	CCollider& operator = (CCollider& _origin) = delete;

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	Vec2 GetFinalPos() { return m_vFinalPos; }

	CObject* GetObj() { return m_pOwner; }

	UINT GetID(){ return m_iID; }

	friend class CObject;

public:
	virtual void OnCollision(CCollider* _pOther);	//충돌 중인 경우
	virtual void OnCollisionEnter(CCollider* _pOther);	//충돌 시작
	virtual void OnCollisionExit(CCollider* _pOther);	//충돌 종료

};

