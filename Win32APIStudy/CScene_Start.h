#pragma once
#include "CScene.h"


class CScene_Start :
	public CScene
{	
public:
	//���������� virtual�� �ٿ���.
	virtual void Enter();
	virtual void Exit();

public:
	CScene_Start();
	~CScene_Start();
};
