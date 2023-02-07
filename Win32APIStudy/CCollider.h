#pragma once
class CObject;

class CCollider
{
private:
	CObject* m_pOwner;
	Vec2 m_vOffsetPos;	//중심점(오브젝트의 위치) 로 부터 오프셋만큼 이동한 곳이 충돌체의 위치
	Vec2 m_vFinalPos;	//최종적으로 계산되는 충돌체의 위치

	Vec2 m_vScale;	//충돌체의 크기

public:
	void finalupdate();
	void render(HDC _dc);

	CCollider();
	~CCollider();

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }


	friend class CObject;
};

