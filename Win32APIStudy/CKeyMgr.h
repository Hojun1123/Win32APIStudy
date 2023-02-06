#pragma once
// 1. ������ ����ȭ, ������ Ű�� ���� ������ ���¸� ���� �� �ְ� �ϱ� ����
// �� �� ������ �������� �Էµ� Ű ���µ��� �����Ͽ� �ش� �����ӿ����Ǹ�� ������Ʈ�鿡�� ������ �̺�Ʈ�� ���������
// 2. Ű �Է¿� ���� �������¸� ����ϰ� ���ش�. ���ʷ� ���ȴ���, ��� ���ȴ��� ��
// tab, hold, away ��

//Ű ����
enum class KEY_STATE
{
	NONE, // ������ �ʰ�, �������� ������ ����
	TAP, // �� ���� ����
	HOLD, // ������ �ִ�
	AWAY, // �� �� ����, ���� �����ӿ� �����־���
};


//������ �� �� �ִ� Ű
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
	LAST,	//LAST�� enum�� ���� ��Ÿ��
};

struct tKeyInfo
{
	KEY_STATE eState;	//Ű�� ���°�
	bool bPrevPush;	//���� �����ӿ� ���ȴ����� ����
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;	//�ε��� ���� �� �ش� Ű�� �ǹ�


public:
	void init();
	void update();


public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }

};

