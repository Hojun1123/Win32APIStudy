#pragma once

class CCollider;

class CObject
{
private:
	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;
public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	virtual void update() = 0;
	virtual void finalupdate() final; //final : 자식들이 오버라이딩하지 못하게 제한함
	virtual void render(HDC _dc);

	CCollider* GetCollider() { return m_pCollider; }
	void CreateCollider();
	void component_render(HDC _dc);


public:
	CObject();
	virtual ~CObject();
};

