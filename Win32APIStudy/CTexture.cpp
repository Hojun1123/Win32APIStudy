#pragma once
#include "pch.h"
#include "CTexture.h"
#include "CCore.h"

void CTexture::Load(const wstring& _strFilePath)
{
	//���Ϸ� ���� �ε��� �����͸� ��Ʈ������ ����
	SetWindowText(CCore::GetInst()->GetMainHwnd(), _strFilePath.c_str());
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	//assert(m_hBit);

	//��Ʈ�ʰ� ������ DC
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	//��Ʈ�ʰ� DC����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	//���� ���� ����
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

CTexture::CTexture()
	:m_hBit(0)
	, m_dc(0)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}
