#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	//FPS
	//1������ �� �ð� (delta Time)
	//1�ʿ� 100��ŭ �̵��ϰ� ������ > 100 * delta Time
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double	m_dDT;	//������ ���� �ð���
	double m_dAcc;	//1�� üũ�� ���� �����ð�
	UINT m_iCallCount;	//�Լ� ȣ�� Ƚ�� üũ
	UINT m_iFPS;	//�ʴ� ȣ�� Ƚ��
public:
	void init();
	void update();

public:
	double GetDT() { return m_dDT; }
	double GetfDT() { return (float)m_dDT; }
};

