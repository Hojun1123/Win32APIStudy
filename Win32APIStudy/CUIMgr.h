#pragma once
class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:
	CUI* m_pFocusedUI;

private:
	CUI* GetTargetedUI(CUI* _pParentUI);	//�θ� UI������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�Ѵ�.
	CUI* GetFocusedUI();


public:
	void update();
	void SetFocusedUI(CUI* _pUI);
};

