#pragma once
class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2 vLT;
	Vec2 vSlice;
	Vec2 vOffset;
	float fDuration;
};

class CAnimation
{

private:
	wstring m_strName;
	CAnimator* m_pAnimator;
	CTexture* m_pTex;
	vector<tAnimFrm> m_vecFrm;	//모든 프레임 정보
	int m_iCurFrm;	//현재 프레임
	float m_fAccTime; //시간 누적
	bool m_bFinish;

	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	void update();
	void render(HDC _dc);

	size_t GetMaxFrame() { return m_vecFrm.size(); }
	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }
	void SetFrame(int _iFrameIdx) {
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}
	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }

	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

