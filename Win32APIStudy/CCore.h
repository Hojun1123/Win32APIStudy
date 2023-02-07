#pragma once

//�̱���, ��ü�� ������ 1���� ����
/*
class CCore
{
private:
	static CCore* g_pInst;

public:

	//���� ����Լ�
	static CCore* GetInstance()
	{
		//
		g_pInst = nullptr;
		if (nullptr == g_pInst)
		{
			g_pInst = new CCore;
		}
		//���� ȣ��
		return g_pInst;
	}
	static void Release(CCore c)
	{
		if (nullptr != g_pInst)
		{
			delete g_pInst;
			g_pInst = nullptr;
		}
	}





//�����ڸ� private���� ����, Ư���Լ����� ���� ������ �� �ְ� ����
//�ٵ� �ش� �Լ��� ������ ��ü�� �־���ϴµ� ������ ���� -> staticŰ���带 �ٿ��� ���
//ȣ���� ��ü ���� ȣ���ϰ� �Ǵ� ���, this�� ����x, ������� ���� �Ұ���
//������ static����� ���ؼ��� ���ٰ���
private:
	CCore();
	~CCore();
};

*/




// 2. ������ ������ Ŭ������ �ø��� ���

#include "pch.h"
#include "define.h"

class CCore
{
	SINGLE(CCore);

private:
	HWND	m_hWnd;	//���� ������ �ڵ�
	POINT	m_ptResolution;	//���� ������ �ػ�
	HDC		m_hDC;	//���� �����쿡 Draw�� DC

	HBITMAP m_hBit;
	HDC m_memDC;
	// ���� ����ϴ� GID Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];
	

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void CreateBrushPen();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }

	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};