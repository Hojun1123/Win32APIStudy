#pragma once
#include "CScene.h"


class CScene_Start :
	public CScene
{	
public:
	//명시적으로 virtual를 붙여줌.
	virtual void Enter();
	virtual void Exit();

public:
	CScene_Start();
	~CScene_Start();
};

