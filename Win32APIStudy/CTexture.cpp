#pragma once
#include "pch.h"
#include "CTexture.h"
#include "CCore.h"

void CTexture::Load(const wstring& _strFilePath)
{
	//파일로 부터 로딩한 데이터를 비트맵으로 생성
	SetWindowText(CCore::GetInst()->GetMainHwnd(), _strFilePath.c_str());
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	//assert(m_hBit);

	//비트맵과 연결할 DC
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	//비트맵과 DC연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	//가로 세로 길이
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
