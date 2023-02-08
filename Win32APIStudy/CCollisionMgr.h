#pragma once
/*
32개의 그룹끼리의 충돌의 경우의 수는 32*32
충동케이스 상태를 32x32의 행렬로 표현가능
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
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];	//충돌 체크 행렬

	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);

public:
	void init();
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset();
};

