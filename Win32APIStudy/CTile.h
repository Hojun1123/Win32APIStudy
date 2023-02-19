#pragma once
#include "CObject.h"
class CTexture;

class CTile
	:public CObject
{
private:
	CTexture* m_pTileTex;
	int m_iImgIdx;

private:
	virtual void update();
	virtual void render(HDC _dc);
	
	CLONE(CTile);

public:
	void SetTexture(CTexture* _pTex) { m_pTileTex = _pTex; }
	void AddImgIdx() { ++m_iImgIdx; }

	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _PFile);

public:
	CTile();
	~CTile();
};

