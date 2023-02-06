#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
//CCore* CCore::g_pInst = nullptr;


CObject g_obj;


CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{


}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	//���� ������� �ٸ��� Delete�� �������� , > ���۷���
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	//���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� ����
	//���� �ػ��� ��Ʈ���� ���� �����쿡	�����Ͽ� �ѱ�
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);


	//Manager �ʱ�ȭ
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();



	Vec2 vPos = Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2));
	g_obj.SetPos(vPos);
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}


void CCore::progress()
{
	////Ƚ�� ����
	//static int callcount = 0;
	//++callcount;

	//
	//static int iPrevCount = GetTickCount64();
	//int iCurCount = GetTickCount64();
	//if (iCurCount - iPrevCount > 1000)
	//{
	//	iPrevCount = iCurCount;
	//	callcount = 0;
	//}


	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CSceneMgr::GetInst()->update();
	

	//������~ ~~~~~~~~~~~//////////////////////////////
	//ȭ�� clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	//�ð� ����ȭ�� �ʿ� > ���ɿ� ���� �̵��ӵ��� �޶����� ���� �ذ�
	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
	{
		vPos.x -= 200.f * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		vPos.x += 200.f * fDT;
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	//ȭ�� clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y+1);

	//�׸���
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_memDC, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f)
	);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
}