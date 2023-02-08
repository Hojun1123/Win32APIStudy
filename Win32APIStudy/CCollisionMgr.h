#pragma once
/*
32���� �׷쳢���� �浹�� ����� ���� 32*32
�浿���̽� ���¸� 32x32�� ��ķ� ǥ������
*/
class CCollider;
union COLLIDER_ID
{
	struct {
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};


class CCollisionMgr
{
	SINGLE(CCollisionMgr)
public:

private:
	map<ULONGLONG, bool> m_mapColInfo;
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];	//�浹 üũ ���

	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);

public:
	void init();
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset();
};

