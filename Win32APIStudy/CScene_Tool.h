#pragma once

#include "CScene.h"
class CUI;

class CScene_Tool : public CScene
{
private:
	CUI* m_pUI;

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	void SetTileIdx();
	
	void SaveTile(const wstring& _strRelativePath);


public:
	CScene_Tool();
	~CScene_Tool();
};

