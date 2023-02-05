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
