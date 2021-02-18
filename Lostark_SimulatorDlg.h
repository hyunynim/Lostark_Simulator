
// Lostark_SimulatorDlg.h: 헤더 파일
//

#pragma once

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
	void UpdateCurrentValue();
	char msg[1010];
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
	// 명예의 돌파석 가격
	ll stone1Price;
	// 위대한 명예의 돌파석 가격
	ll stone2Price;
	// 중급 오레하 결정 가격
	ll orehaPrice;

	//보조재료 슬라이더
	CSliderCtrl additional1Slider;
	CSliderCtrl additional2Slider;
	CSliderCtrl additional3Slider;

	//보조재료 현재 개수
	int additional1Value;
	int additional2Value;
	int additional3Value;

	//보조재료 출력값
	CString additional1String;
	CString additional2String;
	CString additional3String;

	BOOL additionalMax;
	afx_msg void OnNMCustomdrawAdditional1Slider(NMHDR* pNMHDR, LRESULT* pResult);
	//강화 확률
	vector<ll> probability = { 10000, 10000, 10000, 10000, 10000, 10000, 6000, 4500, 3000, 3000, 3000, 1500, 1500, 1500, 1000, 1000, 1000, 500, 500, 300, 300, 100, 100, 50, 50 };
	
	//무기 재료
	vector<ll> weaponReinforcePrice = { 0, 0, 0, 0, 0, 0, 640, 640, 640, 640, 660, 660, 660, 660, 660, 680, 680, 680, 710, 730, 750, 780, 810, 840, 870 };
	vector<ll> weaponNum = { 0, 0, 0, 0, 0, 0, 672, 672, 672, 830, 830, 830, 986, 986, 986, 1144, 1144, 1144, 1300, 1300, 1300, 1458, 1458, 1458, 1614 };
	vector<ll> weaponStoneNum = { 0, 0, 0, 0, 0, 0, 12, 14, 14, 16, 16, 18, 18, 20, 20, 22, 24, 28, 30, 32, 34, 38, 42, 44, 48 };
	vector<ll> weaponOrehaNum = { 0, 0, 0, 0, 0, 0, 6, 6, 8, 8, 8, 8, 10, 10, 10, 12, 14, 16, 18, 20, 22, 26, 28, 32, 36 };
	vector<ll> weaponFragment = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


	//방어구 재료
	vector<ll> armorReinforcePrice = { 0, 0, 0, 0, 0, 0, 330, 330, 330, 330, 330, 330, 330, 330, 350, 350, 350, 350, 350, 350, 360, 380, 390, 400, 420 };
	vector<ll> armorNum = { 0, 0, 0, 0, 0, 0, 404, 404, 404, 498, 498, 498, 592, 592, 592, 686, 686, 686, 780, 780, 780, 874, 874, 874, 968 };
	vector<ll> armorStoneNum = { 0, 0, 0, 0, 0, 0, 8, 10, 10, 10, 10, 12, 12, 12, 12, 14, 16, 16, 18, 20, 22, 24, 26, 28, 30 };
	vector<ll> armorOrehaNum = { 0, 0, 0, 0, 0, 0, 6, 6, 6, 8, 8, 8, 8, 8, 8, 10, 10, 12, 14, 14, 16, 18, 20, 22, 24 };
	vector<ll> armorFragment = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//현재 강화 확률 출력값
	CString currentProbability;
	ll curProb;	//현재 강화 확률

	//장인의 기운 출력값
	CString currentComulative;
	ll curCom = 0;	//현재 장인의 기운

	afx_msg void OnBnClickedReinforce();
	
	int currentLevel;
	// 누적 소모 골드
	ll comulativeGold;
	ll comulativeCount;
	ll currentCount;
	ll meetMrJang;
	afx_msg void OnBnClickedInitializing();
	// 명예의 파편 가격
	ll fragmentPrice;
	BOOL weapon;
	BOOL armor;
	CComboBox selectEquipControl;
	afx_msg void OnCbnSelchangeSelectEquip();
	CEdit reinforcementLogControl;
	CString reinforcementLog;
};
