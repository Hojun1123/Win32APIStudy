#pragma once
#include "CObject.h"
class CPlayer:public CObject
{
public:
	CPlayer();
	~CPlayer();

public:	
	virtual void update();


private:
	void CreateMissile();
};

