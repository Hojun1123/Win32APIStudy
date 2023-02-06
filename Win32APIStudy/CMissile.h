#pragma once
#include "CObject.h"
class CMissile :
    public CObject
{


private:
    float m_fDir; //위 아래 방향


public:
    CMissile();
    ~CMissile();

public:
    virtual void update();
    virtual void render(HDC _dc);
    void SetDir(bool _bUp) { if(_bUp) m_fDir = -1.f;else m_fDir = 1.f; }

};

