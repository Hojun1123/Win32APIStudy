#pragma once
class CObject;

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2	m_vLookAt;	//ī�޶� ���� �ִ� ��
	CObject* m_pTargetObj;	//ī�޶� �Ѿƴٴ� ������Ʈ

	Vec2	m_vDiff  ;	//�ػ� �߽���ġ�� ī�޶� LookAt ���� ���� ��

	void CalDiff();

public:
	void SetLookAt(Vec2 _vLook) { m_vLookAt = _vLook; }
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }

	void update();
	Vec2 GetRenderPos(Vec2 _vObject){ return _vObject - m_vDiff; }
};

