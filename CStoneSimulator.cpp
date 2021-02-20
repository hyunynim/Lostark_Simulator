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
{

}

CStoneSimulator::~CStoneSimulator()
{
}

void CStoneSimulator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStoneSimulator, CDialogEx)
END_MESSAGE_MAP()


// CStoneSimulator 메시지 처리기
