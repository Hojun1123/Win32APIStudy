#pragma once

//역슬래시 : 다음줄로 코드가 이어짐
//싱글톤 매크로
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



/* 자주 쓰는 것들 정의 */
#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()



