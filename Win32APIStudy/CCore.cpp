#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTexture.h"

#include "CSceneMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"

//CCore* CCore::g_pInst = nullptr;

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{


}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	//���� ������� �ٸ��� Delete�� �������� , > ���۷���
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
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

	CreateBrushPen();

	//Manager �ʱ�ȭ
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();
	CPathMgr::GetInst()->init();


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

	//Manager update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();

	//Scene update
	CSceneMgr::GetInst()->update();
	//�浹üũ
	CCollisionMgr::GetInst()->update();

	//������~ ~~~~~~~~~~~//////////////////////////////
	//ȭ�� clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	CSceneMgr::GetInst()->render(m_memDC);
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
	
	//Fps, ������ ����
	CTimeMgr::GetInst()->render();

	//�̺�Ʈ ����ó��
	CEventMgr::GetInst()->update();
}

//���� ��� �� �� �귯�� ����
void CCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH) GetStockObject(HOLLOW_BRUSH);

	//red blue green pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
