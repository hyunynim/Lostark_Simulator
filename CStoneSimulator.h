#pragma once


// CStoneSimulator 대화 상자

class CStoneSimulator : public CDialogEx
{
	DECLARE_DYNAMIC(CStoneSimulator)

public:
	CStoneSimulator(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CStoneSimulator();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STONE_SIMULATOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	char msg[1010];

	CEdit activityControl;
	int activity;
	afx_msg void OnBnClickedApplyActivity();
	int option1Activity;
	CButton reinforce1Control;
	CButton reinforce2Control;
	CButton reinforce3Control;
	int option1Remain;
	int option2Remain;
	int option3Remain;
	int option2Activity;
	int option3Activity;
	CButton applyControl;
	CString probabilityString;

	void UpdateProbability();
	ll probability;
	afx_msg void OnBnClickedReinforce1();
	afx_msg void OnBnClickedReinforce2();
	afx_msg void OnBnClickedReinforce3();
	CString stoneLog;
	CEdit stoneLogControl;
	afx_msg void OnBnClickedInitialize();

	ll currentGold;
};
