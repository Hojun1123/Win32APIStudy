#include "pch.h"
#include "CScene.h"
#include "CObject.h"

CScene::CScene()
{


}

CScene::~CScene()
{
	for (int i = 0; i < (int)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); ++j)
		{
			//m_arrObj[i] : 그룹 벡터의 j물체 삭제
			delete m_arrObj[i][j];
		}
	}
}

void CScene::update()
{
	for (int i = 0; i < (int)GROUP_TYPE::END; ++i)
	{
		for (int j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->update();
		}
	}
}

void CScene::finalupdate()
{
	for (int i = 0; i < (int)GROUP_TYPE::END; ++i)
	{
		for (int j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finalupdate();
		}
	}
}


void CScene::render(HDC _dc)
{
	for (int i = 0; i < (int)GROUP_TYPE::END; ++i)
	{
		for (int j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->render(_dc);
		}
	}
}

