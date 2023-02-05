#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	//FPS
	//1프레임 당 시간 (delta Time)
	//1초에 100만큼 이동하고 싶으면 > 100 * delta Time
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;

public:
	void init();
};

