#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	//FPS
	//1프레임 당 시간 (delta Time)
	//1초에 100만큼 이동하고 싶으면 > 100 * delta Time
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double	m_dDT;	//프레임 간의 시간값
	double m_dAcc;	//1초 체크를 위한 누적시간
	UINT m_iCallCount;	//함수 호출 횟수 체크
	UINT m_iFPS;	//초당 호출 횟수
public:
	void init();
	void update();

public:
	double GetDT() { return m_dDT; }
	double GetfDT() { return (float)m_dDT; }
};

