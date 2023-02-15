#pragma once
class CObject;

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2	m_vLookAt;	//카메라가 보고 있는 곳
	Vec2	m_vCurLookAt;	//이전과 현재 보정위치
	Vec2	m_vPrevLookAt;	//카메라가 보는 이젠 프레임 위치
	
	CObject* m_pTargetObj;	//카메라가 쫓아다닐 오브젝트
	Vec2	m_vDiff  ;	//해상도 중심위치와 카메라 LookAt 간의 차이 값

	float m_fTime;	//타겟을 따라가는데 걸리는 시간
	float m_fSpeed;
	float m_fAccTime;

	void CalDiff();

public:
	void SetLookAt(Vec2 _vLook) 
	{ 
		m_vLookAt = _vLook;
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }

	void update();
	Vec2 GetRenderPos(Vec2 _vObject){ return _vObject - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }
};

