// CReinforceSimulator.cpp: 구현 파일
//

#include "pch.h"
#include "Lostark_Simulator.h"
#include "CReinforceSimulator.h"
#include "afxdialogex.h"
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

// CReinforceSimulator 대화 상자

IMPLEMENT_DYNAMIC(CReinforceSimulator, CDialogEx)

CReinforceSimulator::CReinforceSimulator(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REINFORCE_SIMULATOR, pParent)
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
	, printFailLog(FALSE)
	, setAdditional4(FALSE)
{

}

CReinforceSimulator::~CReinforceSimulator()
{
}

void CReinforceSimulator::DoDataExchange(CDataExchange* pDX)
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
	DDX_Check(pDX, IDC_PRINT_FAIL_LOG, printFailLog);
	DDX_Check(pDX, IDC_SET_ADDITIONAL4, setAdditional4);
	DDX_Control(pDX, IDC_SET_ADDITIONAL4, setAdditional4Control);
	DDX_Control(pDX, IDC_CURRENT_LEVEL, currentLevelControl);
}


BEGIN_MESSAGE_MAP(CReinforceSimulator, CDialogEx)
	ON_BN_CLICKED(IDC_REINFORCE, &CReinforceSimulator::OnBnClickedReinforce)
	ON_BN_CLICKED(IDC_INITIALIZING, &CReinforceSimulator::OnBnClickedInitializing)
	ON_CBN_SELCHANGE(IDC_SELECT_EQUIP, &CReinforceSimulator::OnCbnSelchangeSelectEquip)
	ON_BN_CLICKED(IDC_SET_ADDITIONAL4, &CReinforceSimulator::OnBnClickedSetAdditional4)
	ON_BN_CLICKED(IDC_CHANGE_CURRENT_LEVEL, &CReinforceSimulator::OnBnClickedChangeCurrentLevel)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ADDITIONAL1_SLIDER, &CReinforceSimulator::OnNMCustomdrawAdditional1Slider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ADDITIONAL2_SLIDER, &CReinforceSimulator::OnNMCustomdrawAdditional2Slider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ADDITIONAL3_SLIDER, &CReinforceSimulator::OnNMCustomdrawAdditional3Slider)
END_MESSAGE_MAP()


// CReinforceSimulator 메시지 처리기


BOOL CReinforceSimulator::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	selectEquipControl.InsertString(0, "선택 무기");
	selectEquipControl.InsertString(1, "선택 방어구");
	selectEquipControl.SetItemHeight(0, 15);
	selectEquipControl.SetItemHeight(1, 15);

	tabControl.InsertItem(0, "강화");


	Initialize();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void CReinforceSimulator::Initialize(int lvl) {
	Initialize();
	currentLevel = lvl;
	curProb = probability[currentLevel];

	UpdateProbability();

	sprintf(msg, "%lld.%lld%%%", curCom / 100, curCom % 100);
	currentComulative = msg;

	if (currentLevel > 15)
		setAdditional4Control.EnableWindow(0);
	UpdateData(FALSE);
}
void CReinforceSimulator::Initialize() {
	UpdateData(TRUE);
	UpdateSlider();

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

	reinforcementLog = "";
	setAdditional4Control.EnableWindow(1);
	setAdditional4 = FALSE;

	additionalProb = 0;

	UpdateData(FALSE);

}

void CReinforceSimulator::OnBnClickedReinforce()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	int curSel = selectEquipControl.GetCurSel();
	if (~curSel) {
		if (currentLevel >= 25) {
			MessageBox("최고 수치 도달");
			return;
		}

		if (curSel == 0) {
			comulativeGold += weaponReinforcePrice[currentLevel] + (weaponNum[currentLevel] * weaponPrice) / 10 + (weaponStoneNum[currentLevel] * stone2Price) + (weaponOrehaNum[currentLevel] * orehaPrice) + (weaponFragment[currentLevel] * fragmentPrice) / 50;
			if (setAdditional4)
				comulativeGold += weaponAdditionalPrice;
		}
		else {
			comulativeGold += armorReinforcePrice[currentLevel] + (armorNum[currentLevel] * armorPrice) / 10 + (armorStoneNum[currentLevel] * stone2Price) + (armorOrehaNum[currentLevel] * orehaPrice) + (armorFragment[currentLevel] * fragmentPrice) / 50;
			if (setAdditional4)
				comulativeGold += armorAdditionalPrice;
		}
		comulativeGold += additional1Price * additional1Value + additional2Price * additional2Value + additional3Price * additional3Value;


		++comulativeCount;
		++currentCount;
		ll cur = probability[currentLevel];


		ud d(0, 9999);
		if (d(gen) < GetCurrentProbability()) {
			sprintf(msg, "(%d회) %s +%d강화 성공(%d회)\r\n", comulativeCount, curSel < 1 ? "무기" : "방어구", currentLevel + 1, currentCount);
			reinforcementLog += msg;
			++currentLevel;
			curCom = 0;
			if (currentLevel > 15)
				setAdditional4Control.EnableWindow(0);
			if (currentLevel < 25)
				curProb = probability[currentLevel];
			else
				curProb = 0;
			currentCount = 0;


			setAdditional4 = FALSE;
			additionalMax = 0;

			UpdateData(FALSE);

			UpdateSlider();
		}
		else {
			if (!printFailLog) {
				sprintf(msg, "(%d회) %s +%d강화 실패\r\n", comulativeCount, curSel < 1 ? "무기" : "방어구", currentLevel + 1, currentCount);
				reinforcementLog += msg;
			}
			curCom = min({ 10000LL, curCom + (ll)(GetCurrentProbability() * 0.465) });
			curProb = min({ curProb + cur / 10, cur * 2, 10000LL });
			if (curCom >= 10000)
				++meetMrJang;

			UpdateData(FALSE);

			if (!additionalMax)
				UpdateSlider();
		}
		UpdateCurrentValue();
	}
	else {
		MessageBox("강화할 장비를 선택해주세요.");
	}
	UpdateData(FALSE);
	reinforcementLogControl.LineScroll(reinforcementLogControl.GetLineCount());
}

void CReinforceSimulator::UpdateCurrentValue() {
	sprintf(msg, "%lld.%lld%%", curCom / 100, curCom % 100);
	currentComulative = msg;
	sprintf(msg, "%lld.%lld%%", curProb / 100, curProb % 100);
	currentProbability = msg;
}


void CReinforceSimulator::OnBnClickedInitializing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Initialize();
}


void CReinforceSimulator::OnCbnSelchangeSelectEquip()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Initialize();
}


void CReinforceSimulator::OnBnClickedSetAdditional4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (setAdditional4) {
		setAdditional4 = 0;
		curProb = max(curProb - 1000, 0LL);
	}
	else {
		setAdditional4 = 1;
		curProb = min(curProb + 1000, 10000LL);
	}
	UpdateCurrentValue();
	UpdateData(FALSE);
}


void CReinforceSimulator::OnBnClickedChangeCurrentLevel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (currentLevelChange) {
		UpdateData(TRUE);
		Initialize(currentLevel);
		UpdateData(FALSE);
		currentLevelControl.SetReadOnly(TRUE);
		currentLevelChange = 0;
	}
	else {
		currentLevelControl.SetReadOnly(FALSE);
		currentLevelChange = 1;
	}
}


void CReinforceSimulator::OnNMCustomdrawAdditional1Slider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	UpdateSliderString();
	*pResult = 0;
	UpdateData(FALSE);
}

void CReinforceSimulator::OnNMCustomdrawAdditional2Slider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	UpdateSliderString();
	*pResult = 0;
	UpdateData(FALSE);
}

void CReinforceSimulator::OnNMCustomdrawAdditional3Slider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	UpdateSliderString();
	*pResult = 0;
	UpdateData(FALSE);
}

void CReinforceSimulator::UpdateSlider() {
	additional1Slider.SetPos(0);
	additional2Slider.SetPos(0);
	additional3Slider.SetPos(0);

	additional1Value = additional2Value = additional3Value = 0;

	additional1Slider.SetRangeMax(additionalLimit[currentLevel]);
	additional2Slider.SetRangeMax(additionalLimit[currentLevel] / 2);
	additional3Slider.SetRangeMax(additionalLimit[currentLevel] / 6);

	UpdateSliderString();
}
void CReinforceSimulator::UpdateSliderString() {
	sprintf(msg, "%d/%d", additional1Value, additionalLimit[currentLevel]);
	additional1String = msg;

	sprintf(msg, "%d/%d", additional2Value, additionalLimit[currentLevel] / 2);
	additional2String = msg;

	sprintf(msg, "%d/%d", additional3Value, additionalLimit[currentLevel] / 6);
	additional3String = msg;

	additionalProb = additional1Value * additional1Probability[currentLevel]
		+ additional2Value * additional2Probability[currentLevel]
		+ additional3Value * additional3Probability[currentLevel];

	additionalProb = min(additionalProb, additionalLimitProbability[currentLevel]);
	UpdateProbability();

}

void CReinforceSimulator::UpdateProbability() {
	ll prob = GetCurrentProbability();
	sprintf(msg, "%lld.%lld%%%", prob / 100, prob % 100);
	currentProbability = msg;
}
ll CReinforceSimulator::GetCurrentProbability() {
	if (curCom >= 10000) return 10000;
	
	ll res = curProb + (setAdditional4 ? 1000 : 0) + additionalProb;

	if (res < 0)
		res = 0LL;
	if (res > 10000)
		res = 10000;

	return res;
}