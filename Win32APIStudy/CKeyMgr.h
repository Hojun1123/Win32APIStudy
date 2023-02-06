#pragma once
// 1. 프레임 동기화, 동일한 키에 대해 동일한 상태를 받을 수 있게 하기 위함
// 즉 한 프레임 시작전에 입력된 키 상태들을 갱신하여 해당 프레임에서의모든 오브젝트들에게 동일한 이벤트를 적용시켜줌
// 2. 키 입력에 대해 이전상태를 고려하게 해준다. 최초로 눌렸는지, 몇번 눌렸는지 등
// tab, hold, away 등

//키 상태
enum class KEY_STATE
{
	NONE, // 눌리지 않고, 이전에도 눌리지 않음
	TAP, // 막 누른 시점
	HOLD, // 누르고 있는
	AWAY, // 막 땐 시점, 이전 프레임에 눌려있었음
};


//지원해 줄 수 있는 키
enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,
	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,
	LAST,	//LAST는 enum의 끝을 나타냄
};

struct tKeyInfo
{
	KEY_STATE eState;	//키의 상태값
	bool bPrevPush;	//이전 프레임에 눌렸는지의 상태
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;	//인덱스 값이 곧 해당 키를 의미


public:
	void init();
	void update();


public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }

};

