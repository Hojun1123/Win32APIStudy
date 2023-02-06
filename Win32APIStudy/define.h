#pragma once

//�������� : �����ٷ� �ڵ尡 �̾���
//�̱��� ��ũ��
#define SINGLE(type) public:\
						static type* GetInst()\
						 {\
							static type mgr;\
							return &mgr;\
						 }\
					private:\
						type(); \
						~type();

enum class GROUP_TYPE
{

	DEFUALT,		//0
	PLAYER,			//1
	MISSILE,		//2
	MOSTER,			//3

	END = 32,
};


enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,
	END,
};



/* ���� ���� �͵� ���� */
#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()



