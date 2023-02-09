#pragma once
class CObject;

class CCollider
{
private:
	static UINT g_iNextID;	//���� ���.

	CObject* m_pOwner;
	Vec2 m_vOffsetPos;	//�߽���(������Ʈ�� ��ġ) �� ���� �����¸�ŭ �̵��� ���� �浹ü�� ��ġ
	Vec2 m_vFinalPos;	//���������� ���Ǵ� �浹ü�� ��ġ

	Vec2 m_vScale;	//�浹ü�� ũ��

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
	virtual void OnCollision(CCollider* _pOther);	//�浹 ���� ���
	virtual void OnCollisionEnter(CCollider* _pOther);	//�浹 ����
	virtual void OnCollisionExit(CCollider* _pOther);	//�浹 ����

};

