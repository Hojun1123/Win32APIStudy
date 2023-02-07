#pragma once
class CObject;

class CCollider
{
private:
	CObject* m_pOwner;
	Vec2 m_vOffsetPos;	//�߽���(������Ʈ�� ��ġ) �� ���� �����¸�ŭ �̵��� ���� �浹ü�� ��ġ
	Vec2 m_vFinalPos;	//���������� ���Ǵ� �浹ü�� ��ġ

	Vec2 m_vScale;	//�浹ü�� ũ��

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

