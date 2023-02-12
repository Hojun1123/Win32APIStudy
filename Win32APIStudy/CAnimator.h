#pragma once
class CAnimation;
class CObject;
class CTexture;

class CAnimator
{
private:
	CObject* m_pOwner;	//���� ������Ʈ	cobject > animator > animation
	map<wstring, CAnimation*> m_mapAnim;	//��� �ִϸ��̼�
	CAnimation* m_pCurAnim; //���� ������� �ִϸ��̼�
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

