#pragma once
#include "CObject.h"

void CreateObject(CObject* _pobj, GROUP_TYPE _eGroup);

void DeleteObject(CObject* _pobj);

void ChangeScene(SCENE_TYPE _eNext);


template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		delete _vec[i];
	}
	_vec.clear();
}