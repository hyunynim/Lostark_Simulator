
// Lostark_SimulatorDlg.h: 헤더 파일
//

#pragma once
typedef long long ll;

// CLostarkSimulatorDlg 대화 상자
class CLostarkSimulatorDlg : public CDialogEx
{
// 생성입니다.
public:
	CLostarkSimulatorDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOSTARK_SIMULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void Initialize();
public:
	afx_msg void OnEnChangeEdit5();
	// 수호석 결정 가격
	ll armorPrice;
	// 파괴석 결정 가격
	ll weaponPrice;
	// 태양의 은총 가격
	ll additional1Price;
	ll additional2Price;
	// 태양의 가호 가격
	ll additional3Price;
	// 야금술 가격
	ll weaponAdditionalPrice;
	// 재봉술 가격
	ll armorAdditionalPrice;
	CSliderCtrl additional1Slider;
	CSliderCtrl additional2Slider;
	CSliderCtrl additional3Slider;
	int additional1Value;
	int additional2Value;
	int additional3Value;
	BOOL additionalMax;
	afx_msg void OnNMCustomdrawAdditional1Slider(NMHDR* pNMHDR, LRESULT* pResult);
	CString additional1String;
	CString additional2String;
	CString additional3String;
};
