#pragma once
class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI* GetTargetedUI(CUI* _pParentUI);	//�θ� UI������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�Ѵ�.
public:
	void update();

};

