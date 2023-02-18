#pragma once
class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI* GetTargetedUI(CUI* _pParentUI);	//부모 UI내에서 실제로 타겟팅 된 UI를 찾아서 변환한다.
public:
	void update();

};

