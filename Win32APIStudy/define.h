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
	TILE,			//1
	PLAYER,			
	MOSTER,			
	PROJ_PLAYER,	
	PROJ_MOSTER,	


	UI = 31,
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

enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	END,
};


/* ���� ���� �͵� ���� */
#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()

#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define CLONE(type) type* Clone(){return new type(*this);}

#define PI 3.1415926535f

#define TILE_SIZE 64	//�ݺ�	//64