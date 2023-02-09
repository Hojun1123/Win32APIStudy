#pragma once
#include "CObject.h"  

class CMonster:public CObject
{
private:
	float m_fSpeed;
	float m_fMaxDistance;
	Vec2 m_vCenterPos;
	int m_iDir; //1, -1  진행 방향

public:
	virtual void update();
	virtual void OnCollisionEnter(CCollider* _pOther);

public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _f) { m_fSpeed = _f; }
	void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
	void SetCenterPos(Vec2 _v) { m_vCenterPos = _v; }

public:
	CMonster();
	~CMonster();
};

