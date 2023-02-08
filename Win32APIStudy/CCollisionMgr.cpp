#include "pch.h"
#include "CCollisionMgr.h"
#include "CCollider.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CObject.h"







CCollisionMgr::CCollisionMgr()
	:m_arrCheck{}
{
}


CCollisionMgr::~CCollisionMgr()
{
}


void CCollisionMgr::init()
{
}

void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();
	Vec2 vRightScale = _pRightCol->GetScale();

	if ((abs(vRightPos.x - vLeftPos.x) < (vRightScale.x + vLeftScale.x) / 2.f)
		&& (abs(vRightPos.y - vLeftPos.y) < (vRightScale.y + vLeftScale.y) / 2.f))
	{
		return true;
	}
	return false;
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	//충돌체를 가지지않는 물체들에 대해는 continue
	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			//자기자신에 대한 경우도 continue
			if (vecRight[j]->GetCollider() == nullptr || vecLeft[i] == vecRight[j])
				continue;


			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();
			iter = m_mapColInfo.find(ID.ID);

			// 충돌 정보가 등록되어있지 않은 경우, 등록하고 false
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			if (IsCollision(pLeftCol, pRightCol))
			{
				//현재 충돌
				if (iter->second)
				{
					//이전에 충돌이었음 > 계속 충돌 중
					pLeftCol->OnCollision(pRightCol);
					pRightCol->OnCollision(pLeftCol);
				}
				else
				{
					//처음 충돌 시작
					pLeftCol->OnCollisionEnter(pRightCol);
					pRightCol->OnCollisionEnter(pLeftCol);
					iter->second = true;
				}
			}
			else
			{
				//현재 충돌x
				if (iter->second)
				{
					//이전에 충돌이었음 > 충돌 종료
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
				/*
				else
				{
					//이전 현재 모두 충돌x
				}
				*/
			}
		}
	}
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	//더 작은 값의 그룹 타입을 행, 큰 값을 열
	/*
	3, 0
	arr[0] = 3	> 0000 0000 0000 0000 0000 0000 0000 1000
	12, 4
	arr[4] = 12 > 0000 0000 0000 0000 0001 0000 0000 0000
	*/
	
	UINT iRow = (UINT)_eLeft;;
	UINT iCol = (UINT)_eRight;;
	if (_eLeft > _eRight)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	//만약 다시 체크를 시도할 경우 체크 해제
	if (m_arrCheck[iRow] & (1 << iCol))
		m_arrCheck[iRow] &= ~(1 << iCol);
	else
		m_arrCheck[iRow] |= (1 << iCol);
}
void CCollisionMgr::Reset()
{
	memset(m_arrCheck, 0, sizeof(m_arrCheck));
}