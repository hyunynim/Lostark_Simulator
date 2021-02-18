
// Lostark_SimulatorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Lostark_Simulator.h"
#include "Lostark_SimulatorDlg.h"
#include "afxdialogex.h"
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

random_device rd;
mt19937 gen(rd());
typedef uniform_int_distribution<ll> ud;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLostarkSimulatorDlg 대화 상자



CLostarkSimulatorDlg::CLostarkSimulatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOSTARK_SIMULATOR_DIALOG, pParent)
	, armorPrice(0)
	, weaponPrice(0)
	, additional1Price(0)
	, additional2Price(0)
	, additional3Price(0)
	, weaponAdditionalPrice(0)
	, armorAdditionalPrice(0)
	, additional1Value(0)
	, additional2Value(0)
	, additional3Value(0)
	, additionalMax(FALSE)
	, additional1String(_T("0/0"))
	, additional2String(_T("0/0"))
	, additional3String(_T("0/0"))
	, currentProbability(_T("100%"))
	, currentComulative(_T("100%"))
	, stone1Price(0)
	, stone2Price(0)
	, orehaPrice(0)
	, currentLevel(6)
	, comulativeGold(0)
	, comulativeCount(0)
	, currentCount(0)
	, meetMrJang(0)
	, fragmentPrice(0)
	, reinforcementLog(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLostarkSimulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ARMOR_PRICE, armorPrice);
	DDX_Text(pDX, IDC_WEAPON_PRICE, weaponPrice);
	DDX_Text(pDX, IDC_ADDITIONAL1_PRICE, additional1Price);
	DDX_Text(pDX, IDC_ADDITIONAL2_PRICE, additional2Price);
	DDX_Text(pDX, IDC_ADDITIONAL3_PRICE, additional3Price);
	DDX_Text(pDX, IDC_WEAPON_ADDITIONAL_PRICE, weaponAdditionalPrice);
	DDX_Text(pDX, IDC_ARMOR_ADDITIONAL_PRICE, armorAdditionalPrice);
	DDX_Control(pDX, IDC_ADDITIONAL1_SLIDER, additional1Slider);
	DDX_Control(pDX, IDC_ADDITIONAL2_SLIDER, additional2Slider);
	DDX_Control(pDX, IDC_ADDITIONAL3_SLIDER, additional3Slider);
	DDX_Slider(pDX, IDC_ADDITIONAL1_SLIDER, additional1Value);
	DDX_Slider(pDX, IDC_ADDITIONAL2_SLIDER, additional2Value);
	DDX_Slider(pDX, IDC_ADDITIONAL3_SLIDER, additional3Value);
	DDX_Check(pDX, IDC_SET_ADDITIONAL_MAX, additionalMax);
	DDX_Text(pDX, IDC_ADDITIONAL1_STRING, additional1String);
	DDX_Text(pDX, IDC_ADDITIONAL2_STRING, additional2String);
	DDX_Text(pDX, IDC_ADDITIONAL3_STRING, additional3String);
	DDX_Text(pDX, IDC_CURRENT_PROBABILITY, currentProbability);
	DDX_Text(pDX, IDC_CURRENT_COMULATIVE, currentComulative);
	DDX_Text(pDX, IDC_STONE1, stone1Price);
	DDX_Text(pDX, IDC_STONE2, stone2Price);
	DDX_Text(pDX, IDC_OREHA_PRICE, orehaPrice);
	DDX_Text(pDX, IDC_CURRENT_LEVEL, currentLevel);
	DDX_Text(pDX, IDC_COMULATIVE_GOLD, comulativeGold);
	DDX_Text(pDX, IDC_COMULATIVE_COUNT, comulativeCount);
	DDX_Text(pDX, IDC_CURRENT_COUNT, currentCount);
	DDX_Text(pDX, IDC_MEET_MR_JANG, meetMrJang);
	DDX_Text(pDX, IDC_FRAGMENT_PRICE, fragmentPrice);
	DDX_Control(pDX, IDC_SELECT_EQUIP, selectEquipControl);
	DDX_Control(pDX, IDC_REINFORCEMENT_LOG, reinforcementLogControl);
	DDX_Text(pDX, IDC_REINFORCEMENT_LOG, reinforcementLog);
}

BEGIN_MESSAGE_MAP(CLostarkSimulatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ADDITIONAL1_SLIDER, &CLostarkSimulatorDlg::OnNMCustomdrawAdditional1Slider)
	ON_BN_CLICKED(IDC_REINFORCE, &CLostarkSimulatorDlg::OnBnClickedReinforce)
	ON_BN_CLICKED(IDC_INITIALIZING, &CLostarkSimulatorDlg::OnBnClickedInitializing)
	ON_CBN_SELCHANGE(IDC_SELECT_EQUIP, &CLostarkSimulatorDlg::OnCbnSelchangeSelectEquip)
END_MESSAGE_MAP()


// CLostarkSimulatorDlg 메시지 처리기

BOOL CLostarkSimulatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	selectEquipControl.InsertString(0, "선택 무기");
	selectEquipControl.InsertString(1, "선택 방어구");
	selectEquipControl.SetItemHeight(0, 10);
	Initialize();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CLostarkSimulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CLostarkSimulatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CLostarkSimulatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLostarkSimulatorDlg::OnNMCustomdrawAdditional1Slider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	UpdateData(TRUE);
	sprintf(msg, "%d", additional1Value);
	//additional1String = msg;
	UpdateData(FALSE);
}

void CLostarkSimulatorDlg::Initialize() {
	additional1Slider.SetRangeMax(48);
	additional2Slider.SetRangeMax(24);
	additional3Slider.SetRangeMax(6);


	comulativeGold = 0;
	comulativeCount = 0;
	currentCount = 0;
	currentLevel = 6;

	curProb = probability[currentLevel];
	curCom = 0;

	meetMrJang = 0;

	additional1Value = 0;
	additional2Value = 0;
	additional3Value = 0;


	sprintf(msg, "%lld.%lld%%%", curProb / 100, curProb % 100);
	currentProbability = msg;

	sprintf(msg, "%lld.%lld%%%", curCom / 100, curCom % 100);
	currentComulative = msg;

	additional1String = "0/0";
	additional2String = "0/0";
	additional3String = "0/0";
	reinforcementLog = "";
	UpdateData(FALSE);
}

void CLostarkSimulatorDlg::OnBnClickedReinforce()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	int curSel = selectEquipControl.GetCurSel();
	if (~curSel) {
		if (currentLevel >= 25) {
			MessageBox("최고 수치 도달");
			return;
		}
		if (curSel == 0)
			comulativeGold += weaponReinforcePrice[currentLevel] + (weaponNum[currentLevel] * weaponPrice) / 10 + (weaponStoneNum[currentLevel] * stone2Price) + (weaponOrehaNum[currentLevel] * orehaPrice) + (weaponFragment[currentLevel] * fragmentPrice) / 50;
		else
			comulativeGold += armorReinforcePrice[currentLevel] + (armorNum[currentLevel] * armorPrice) / 10 + (armorStoneNum[currentLevel] * stone2Price) + (armorOrehaNum[currentLevel] * orehaPrice) + (armorFragment[currentLevel] * fragmentPrice) / 50;
		++comulativeCount;
		++currentCount;
		ll cur = probability[currentLevel];

		if (curCom >= 10000)
			curProb = 10000;

		ud d(0, 9999);
		if (d(gen) < curProb) {
			sprintf(msg, "%s +%d강화 성공(%d회)\r\n", curSel < 1 ? "무기" : "방어구", currentLevel, currentCount);
			reinforcementLog += msg;
			++currentLevel;
			curCom = 0;
			if (currentLevel < 25)
				curProb = probability[currentLevel];
			else
				curProb = 0;
			currentCount = 0;
		}
		else {
			sprintf(msg, "%s +%d강화 실패\r\n", curSel < 1 ? "무기" : "방어구", currentLevel, currentCount);
			reinforcementLog += msg;
			curCom = min({ 10000LL, curCom + (ll)(curProb * 0.465) });
			curProb = min({ curProb + cur / 10, cur * 2, 10000LL });
			if (curCom == 10000)
				++meetMrJang;
		}
		UpdateCurrentValue();
		reinforcementLogControl.SetScrollPos(1, 1e9);
		UpdateData(FALSE);
	}
	else {
		MessageBox("강화할 장비를 선택해주세요.");
	}
}

void CLostarkSimulatorDlg::UpdateCurrentValue() {
	sprintf(msg, "%lld.%lld%%", curCom / 100, curCom % 100);
	currentComulative = msg;
	sprintf(msg, "%lld.%lld%%", curProb / 100, curProb % 100);
	currentProbability = msg;
}


void CLostarkSimulatorDlg::OnBnClickedInitializing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Initialize();
}


void CLostarkSimulatorDlg::OnCbnSelchangeSelectEquip()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Initialize();
}
