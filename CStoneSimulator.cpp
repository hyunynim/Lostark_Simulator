// CStoneSimulator.cpp: 구현 파일
//

#include "pch.h"
#include "Lostark_Simulator.h"
#include "CStoneSimulator.h"
#include "afxdialogex.h"


// CStoneSimulator 대화 상자

IMPLEMENT_DYNAMIC(CStoneSimulator, CDialogEx)

CStoneSimulator::CStoneSimulator(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STONE_SIMULATOR, pParent)
	, activity(0)
	, option1Activity(0)
	, option1Remain(0)
	, option2Remain(0)
	, option3Remain(0)
	, option2Activity(0)
	, option3Activity(0)
	, probabilityString(_T(""))
	, stoneLog(_T(""))
{

}

CStoneSimulator::~CStoneSimulator()
{
}

void CStoneSimulator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACTIVITY, activityControl);
	DDX_Text(pDX, IDC_ACTIVITY, activity);
	DDX_Text(pDX, IDC_OPTION1_ACTIVITY, option1Activity);
	DDX_Control(pDX, IDC_REINFORCE1, reinforce1Control);
	DDX_Control(pDX, IDC_REINFORCE2, reinforce2Control);
	DDX_Control(pDX, IDC_REINFORCE3, reinforce3Control);
	DDX_Text(pDX, IDC_OPTION1_REMAIN, option1Remain);
	DDX_Text(pDX, IDC_OPTION2_REMAIN, option2Remain);
	DDX_Text(pDX, IDC_OPTION3_REMAIN, option3Remain);
	DDX_Text(pDX, IDC_OPTION2_ACTIVITY, option2Activity);
	DDX_Text(pDX, IDC_OPTION3_ACTIVITY, option3Activity);
	DDX_Control(pDX, IDC_APPLY_ACTIVITY, applyControl);
	DDX_Text(pDX, IDC_PROBABILITY, probabilityString);
	DDX_Text(pDX, IDC_STONE_LOG, stoneLog);
	DDX_Control(pDX, IDC_STONE_LOG, stoneLogControl);
}


BEGIN_MESSAGE_MAP(CStoneSimulator, CDialogEx)
	ON_BN_CLICKED(IDC_APPLY_ACTIVITY, &CStoneSimulator::OnBnClickedApplyActivity)
	ON_BN_CLICKED(IDC_REINFORCE1, &CStoneSimulator::OnBnClickedReinforce1)
	ON_BN_CLICKED(IDC_REINFORCE2, &CStoneSimulator::OnBnClickedReinforce2)
	ON_BN_CLICKED(IDC_REINFORCE3, &CStoneSimulator::OnBnClickedReinforce3)
	ON_BN_CLICKED(IDC_INITIALIZE, &CStoneSimulator::OnBnClickedInitialize)
END_MESSAGE_MAP()


// CStoneSimulator 메시지 처리기

void CStoneSimulator::UpdateProbability() {
	sprintf(msg, "%lld%%", probability / 100);
	probabilityString = msg;
}
void CStoneSimulator::OnBnClickedApplyActivity()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (activity <= 0) {
		MessageBox("활성도를 0 이하로 설정할 수 없습니다.");
		return;
	}
	activityControl.SetReadOnly(1);
	option1Activity = option2Activity = option3Activity = 0;
	option1Remain = option2Remain = option3Remain = activity;
	
	reinforce1Control.EnableWindow(1);
	reinforce2Control.EnableWindow(1);
	reinforce3Control.EnableWindow(1);
	applyControl.EnableWindow(0);
	probability = 7500;

	UpdateProbability();

	UpdateData(FALSE);
}


void CStoneSimulator::OnBnClickedReinforce1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	ud d(0, 10000);
	if (d(gen) < probability) {
		sprintf(msg, "옵션1 성공(확률 %lld%%)\r\n", probability / 100);
		++option1Activity;
		probability = max(2500LL, probability - 1000);
	}
	else {
		sprintf(msg, "옵션1 실패(확률 %lld%%)\r\n", probability / 100);
		probability = min(7500LL, probability + 1000);
	}
	--option1Remain;
	if (option1Remain == 0)
		reinforce1Control.EnableWindow(0);

	stoneLog += msg;
	stoneLogControl.LineScroll(stoneLogControl.GetLineCount());

	UpdateProbability();

	UpdateData(FALSE);
}


void CStoneSimulator::OnBnClickedReinforce2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	ud d(0, 10000);
	if (d(gen) < probability) {
		sprintf(msg, "옵션2 성공(확률 %lld%%)\r\n", probability / 100);
		++option2Activity;
		probability = max(2500LL, probability - 1000);
	}
	else {
		sprintf(msg, "옵션2 실패(확률 %lld%%)\r\n", probability / 100);
		probability = min(7500LL, probability + 1000);
	}
	--option2Remain;
	if (option2Remain == 0)
		reinforce2Control.EnableWindow(0);

	stoneLog += msg;
	stoneLogControl.LineScroll(stoneLogControl.GetLineCount());

	UpdateProbability();

	UpdateData(FALSE);
}


void CStoneSimulator::OnBnClickedReinforce3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	ud d(0, 10000);
	if (d(gen) < probability) {
		sprintf(msg, "옵션3 성공(확률 %lld%%)\r\n", probability / 100);
		++option3Activity;
		probability = max(2500LL, probability - 1000);
	}
	else {
		sprintf(msg, "옵션3 실패(확률 %lld%%)\r\n", probability / 100);
		probability = min(7500LL, probability + 1000);
	}
	--option3Remain;
	if (option3Remain == 0)
		reinforce3Control.EnableWindow(0);

	stoneLog += msg;
	stoneLogControl.LineScroll(stoneLogControl.GetLineCount());

	UpdateProbability();

	UpdateData(FALSE);
}


void CStoneSimulator::OnBnClickedInitialize()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	applyControl.EnableWindow(1);
	reinforce1Control.EnableWindow(0);
	reinforce2Control.EnableWindow(0);
	reinforce3Control.EnableWindow(0);

	activityControl.SetReadOnly(0);
	option1Activity = option2Activity = option3Activity = 0;
	option1Remain = option2Remain = option3Remain = 0;

	reinforce1Control.EnableWindow(0);
	reinforce2Control.EnableWindow(0);
	reinforce3Control.EnableWindow(0);
	probability = 7500;

	UpdateProbability();

	stoneLog = "";

	UpdateData(FALSE);
}
