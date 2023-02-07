#pragma once
#include "CObject.h"
#include "CTexture.h"

class CPlayer
	:public CObject
{
private:
	CTexture* m_pTex;

public:
	CPlayer();
	~CPlayer();

public:	
	virtual void update();
	virtual void render(HDC _dc);


private:
	void CreateMissile();
};

