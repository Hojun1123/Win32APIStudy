#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	//FPS
	//1������ �� �ð� (delta Time)
	//1�ʿ� 100��ŭ �̵��ϰ� ������ > 100 * delta Time
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;

public:
	void init();
};

