﻿
// Lostark_SimulatorDlg.h: 헤더 파일
//
#include"CStoneSimulator.h"
#include"CReinforceSimulator.h"
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
public:
	BOOL currentLevelChange;
	CTabCtrl tabControl;

	CReinforceSimulator* pDlg1;
	CStoneSimulator* pDlg2;


	afx_msg void OnTcnSelchangeTabControl(NMHDR* pNMHDR, LRESULT* pResult);
};
