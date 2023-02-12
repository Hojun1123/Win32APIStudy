#pragma once
class CAnimation;
class CObject;
class CTexture;

class CAnimator
{
private:
	CObject* m_pOwner;	//소유 오브젝트	cobject > animator > animation
	map<wstring, CAnimation*> m_mapAnim;	//모든 애니메이션
	CAnimation* m_pCurAnim; //현재 재생중인 애니메이션
	bool m_bRepeat;

public:
	CAnimator();
	~CAnimator();

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);
	CAnimation* FindAnimation(const wstring & _strName);
	void Play(const wstring& _strName, bool _bRepeat);
	
	void update();
	void render(HDC _dc);

	CObject* GetObj() { return m_pOwner; }

	friend class CObject;
};

