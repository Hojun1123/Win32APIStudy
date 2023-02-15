#pragma once
class CObject;

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2	m_vLookAt;	//ī�޶� ���� �ִ� ��
	Vec2	m_vCurLookAt;	//������ ���� ������ġ
	Vec2	m_vPrevLookAt;	//ī�޶� ���� ���� ������ ��ġ
	
	CObject* m_pTargetObj;	//ī�޶� �Ѿƴٴ� ������Ʈ
	Vec2	m_vDiff  ;	//�ػ� �߽���ġ�� ī�޶� LookAt ���� ���� ��

	float m_fTime;	//Ÿ���� ���󰡴µ� �ɸ��� �ð�
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

