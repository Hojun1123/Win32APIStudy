#pragma once
#include "CObject.h"
class CMissile :
    public CObject
{


private:
    float m_fTheta; //πÊ«‚
    Vec2 m_vDir;



public:
    CMissile();
    ~CMissile();

public:
    virtual void update();
    virtual void render(HDC _dc);
    void SetTheta(bool _bTheta) { m_fTheta = _bTheta; }
    void SetDir(Vec2 _vDir) { m_vDir = _vDir; m_vDir.Normalize(); }

};

